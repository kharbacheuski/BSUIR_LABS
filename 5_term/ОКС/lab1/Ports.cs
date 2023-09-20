using System.IO.Ports;
using System.Text;
using lab1;

namespace lab1 {
    public class Port : IDisposable {
        protected SerialPort serialPort;

        public Port(string serialPortName, int speed = 19200) {
            serialPort = new SerialPort(serialPortName, speed, Parity.None, 8, StopBits.One);
            serialPort.Open();

            serialPort.ReadTimeout = 500;
            serialPort.WriteTimeout = 500;
        }

        public void Dispose() {
            serialPort.Dispose();
        }

        public virtual void Do() { }
    }
    public class Consumer : Port {
        public Consumer(string serialPortName, int speed) : base(serialPortName, speed) {
            serialPort.DataReceived += new SerialDataReceivedEventHandler(OutputData);
        }

        public override void Do() {
            Console.WriteLine($"Consumer on port {serialPort.PortName}");
            while (true);
        }

        private void OutputData(object sender, SerialDataReceivedEventArgs e) 
        {
            var buffer = new byte[1024];
            serialPort.Read(buffer, 0, 1024);

            var bitStaffing = new BitStaffing();

            var recievePackage = bitStaffing.Deserialize(buffer);

            var dataString = bitStaffing.DecodeData(recievePackage.data);

            Console.WriteLine($"Message = {dataString} ({dataString.Length} bytes)");
        }
    }
    public class Producer : Port {
        public Producer(string serialPortName, int speed) : base(serialPortName, speed) { }

        public override void Do() {
            Console.WriteLine($"Producer on port {serialPort.PortName}");

            while (true) {
                Console.Write("\n\nWrite message: ");
                var data = Console.ReadLine();

                var package = new Package();
                var bitStaffing = new BitStaffing();

                package.flag = (byte)128;
                package.data = bitStaffing.EncodeData(data);
                package.length = package.data.Length;

                var packageBytes = bitStaffing.Serialize(package);

                Console.WriteLine("I send " + Encoding.ASCII.GetString(package.data));

                serialPort.Write(packageBytes, 0, packageBytes.Length);
            }
        }
    }
}
