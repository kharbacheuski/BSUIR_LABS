using System.IO.Ports;
using System.Text;

namespace lab1 {
    public class Port : IDisposable 
    {
        protected SerialPort readPort;
        protected SerialPort writePort;

        private Queue<TokenRingPackage> packagesQueue;
        private readonly List<TokenRingPackage> readedPackages;
        private bool isMonitor;
        private byte priority = 1;

        public Port(string serialPortRead, string serialPortWrite, bool isMonitor, int speed = 19200) 
        {
            this.isMonitor = isMonitor;
            readedPackages = new List<TokenRingPackage>();
            packagesQueue = new Queue<TokenRingPackage>();
            readPort = new SerialPort(serialPortRead, speed, Parity.None, 8, StopBits.One);
            readPort.DataReceived += new SerialDataReceivedEventHandler(OutputData);
            readPort.Open();

            readPort.ReadTimeout = 200;
            readPort.WriteTimeout = 500;

            writePort = new SerialPort(serialPortWrite, speed, Parity.None, 8, StopBits.One);
            writePort.Open();

            writePort.ReadTimeout = 200;
            writePort.WriteTimeout = 500;

            Console.WriteLine($"Consumer on port {serialPortRead}");
            Console.WriteLine($"Producer on port {serialPortWrite}");
        }

        private void OutputData(object sender, SerialDataReceivedEventArgs e) 
        {
            var buffer = new byte[18];

            readPort.Read(buffer, 0, 18);

            var recievedPackage = TokenRingPackage.Deserialize(buffer);
            TokenRingPackage packageToSend = recievedPackage;

            var isToken = recievedPackage.AC.tokenBit;
            var imInReservation = priority >= recievedPackage.AC.reservationBits;
            var imInPriority = priority >= recievedPackage.AC.priorityBits;

            if (!isToken)
            {
                // package for me
                if (recievedPackage.package.destinationAddress.Equals((byte)readPort.GetPortNumber()))
                {
                    readedPackages.Add(recievedPackage);

                    packageToSend.FS.addressRecognizedBit = true;
                    packageToSend.FS.frameCopied = true;

                    if (recievedPackage.package.flag.Equals(37)) // end of data packages
                    {
                        PrintData(readedPackages);
                        readedPackages.Clear();
                    }

                    WritePackage(packageToSend);
                    return;
                }

                // im sender
                if (recievedPackage.package.sourceAddress.Equals((byte)writePort.GetPortNumber()))
                {
                    // remake token
                    packageToSend.AC.tokenBit = true;
                    packageToSend.AC.priorityBits = recievedPackage.AC.reservationBits;
                    packageToSend.AC.reservationBits = 0;

                    WritePackage(packageToSend);
                    return;
                }

                // проходной for frame
                if (packagesQueue.Any() && imInReservation)
                {
                    packageToSend.AC.reservationBits = priority;
                }

                WritePackage(packageToSend);
                return;
            }
            else if (packagesQueue.Any())
            {
                // token
                if (imInPriority)
                {
                    var newPackage = packagesQueue.Dequeue();
                    newPackage.AC = new AccessControl()
                    {
                        tokenBit = false,
                        priorityBits = priority,
                        reservationBits = 0
                    };
                    newPackage.FS = new FrameStatus();

                    packageToSend = newPackage;
                }
                else if (imInReservation)
                    recievedPackage.AC.reservationBits = priority;
            }

            WritePackage(packageToSend);
            return;
        }

        private static void PrintData(IEnumerable<TokenRingPackage> tokenRingPackages)
        {
            var packages = tokenRingPackages.Select(p => p.package);
            var hammingsCode = new HammingCode();
            var bitStaffing = new BitStaffing();

            Console.WriteLine("Packages count:" + packages.Count());
            var dataBytes = new List<byte>();

            foreach (var package in packages)
            {
                dataBytes.AddRange(package.data);
            }

            var bytesArray = dataBytes.ToArray();

            var decodeStaffing = bitStaffing.DecodeData(bytesArray);
            var decodeHamming = hammingsCode.Decode(decodeStaffing, packages.First().FCS);

            Console.WriteLine($"Message = {Encoding.ASCII.GetString(decodeHamming)}");
        }

        public void InputData()
        {
            while (true)
            {
                Console.Write("\n\nWrite target: ");
                var target = Convert.ToInt32(Console.ReadLine());
                Console.Write("\n\nWrite message: ");
                var data = Console.ReadLine();

                var bitStaffing = new BitStaffing();
                var hammingsCode = new HammingCode();

                var hammingBytes = hammingsCode.Encode(Encoding.ASCII.GetBytes(data));
                var staffingBytes = bitStaffing.EncodeData(hammingBytes);

                int dataLength = 10;
                var countOfPackage = Math.Ceiling(data.Length / (double)dataLength);

                Console.WriteLine($"\n\nPackages count: {countOfPackage}");

                for (int i = 0; i < countOfPackage; i++)
                {
                    var partOfData = staffingBytes.Skip(i * dataLength).Take(dataLength).ToArray();

                    var package = new Package();
                    package.data = partOfData;
                    package.destinationAddress = (byte)target;
                    package.sourceAddress = (byte)writePort.GetPortNumber();
                    package.length = package.data.Length;
                    package.FCS = hammingsCode.GetFCS(hammingBytes);

                    if (i == countOfPackage - 1)
                        package.flag = 37;

                    var tokenRingPackage = new TokenRingPackage();

                    tokenRingPackage.package = package;
                    tokenRingPackage.AC = new AccessControl { tokenBit = false };
                    tokenRingPackage.FS = new FrameStatus();

                    packagesQueue.Enqueue(tokenRingPackage);
                }
            }
        }

        public void Do()
        {
            if(isMonitor)
                Task.Run(Monitoring);

            InputData();
        }

        private void Monitoring()
        {
            while (true)
            {
                var accessControl = new AccessControl();
                accessControl.monitorBit = true;
                accessControl.tokenBit = true;

                var _package = new Package { destinationAddress = 0 };
                var tokenPackage = new TokenRingPackage { AC =  accessControl, FS = new FrameStatus(), package = _package };

                WritePackage(tokenPackage);

                Thread.Sleep(500000);
            }
        }

        private void WritePackage(TokenRingPackage package)
        {
            var packageBytes = package.Serialize();

            writePort.Write(packageBytes, 0, packageBytes.Length);

            if (!package.AC.tokenBit)
                Console.WriteLine($"{packageBytes.Length} bytes sended");
        }

        public void Dispose()
        {
            readPort.Dispose();
            writePort.Dispose();
        }
    }
}
