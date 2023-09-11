using System.IO.Ports;
using System.Text;

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

        private void OutputData(object sender, SerialDataReceivedEventArgs e) {
            var buffer = new byte[1024];
            serialPort.Read(buffer, 0, 1024);

            var valueBuffer = buffer.TakeWhile(b => b != 0).ToArray();

            var data = Encoding.ASCII.GetString(valueBuffer);

            Console.WriteLine($"Message = {data} ({data.Length} bytes)");
        }
    }
    public class Producer : Port {
        public Producer(string serialPortName, int speed) : base(serialPortName, speed) { }

        public override void Do() {
            Console.WriteLine($"Producer on port {serialPort.PortName}");

            while (true) {
                Console.Write("\n\nWrite message: ");
                var data = Console.ReadLine();

                var bytes = Encoding.ASCII.GetBytes(data);

                var valueBytes = bytes.Append((byte)0).ToArray();

                serialPort.Write(valueBytes, 0, valueBytes.Length);
            }
        }
    }
}
