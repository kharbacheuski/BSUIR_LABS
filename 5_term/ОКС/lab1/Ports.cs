using System.IO.Ports;
using System.Text;

namespace lab1 {
    public class Port : IDisposable
    {
        protected SerialPort serialPort;

        public Port(string serialPortName, Parity parity = Parity.None)
        {
            serialPort = new SerialPort(serialPortName, 19200, parity, 8, StopBits.One);
            serialPort.Open();

            serialPort.ReadTimeout = 500;
            serialPort.WriteTimeout = 500;
        }

        public void Dispose()
        {
            serialPort.Dispose();
        }

        public virtual void Do()
        {
            Console.WriteLine($"Node starting on port {serialPort.PortName}");
        }
    }
    public class Consumer : Port {
        public Consumer(string serialPortName) : base(serialPortName) {
            serialPort.DataReceived += new SerialDataReceivedEventHandler(OutputData);
        }

        public override void Do() {
            Console.WriteLine($"Consumer on port {serialPort.PortName}");
            Console.WriteLine("\n\nMessage: ");
            while (true);
        }

        private void OutputData(object sender, SerialDataReceivedEventArgs e) {
            var buffer = new byte[1024];
            serialPort.Read(buffer, 0, 1024);

            var valueBuffer = buffer.TakeWhile(b => b != 0).ToArray();

            var data = Encoding.ASCII.GetString(valueBuffer);

            Console.Write(data);
        }
    }
    public class Producer : Port
    {
        public Producer(string serialPortName, Parity parity = Parity.None) : base(serialPortName, parity) { }

        public override void Do()
        {
            Console.WriteLine($"Producer on port {serialPort.PortName}");
            Console.WriteLine("\n\nWrite message: ");

            while (true)
            {
                var data = Console.ReadLine();

                var bytes = Encoding.ASCII.GetBytes(data);

                var valueBytes = bytes.Append((byte)0).ToArray();

                serialPort.Write(valueBytes, 0, valueBytes.Length);

                Console.WriteLine($"{valueBytes.Length} bytes sended");
            }
        }
    }
}
