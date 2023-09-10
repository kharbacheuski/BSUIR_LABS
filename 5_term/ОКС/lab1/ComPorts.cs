using System.Diagnostics;
using System.IO.Ports;

namespace lab1 {
    internal class ComPorts {
        static void Main(string[] args) {
            Port node = null;

            if (args.Length == 0) {
                var ports = GetFreeSerialPorts();

                node = new Producer(ports.Item1);

                StartConsumer(ports.Item2);
            }
            else node = new Consumer(args[0]);

            node.Do();
        }

        private static (string, string) GetFreeSerialPorts() {
            var serialPortNames = SerialPort.GetPortNames();
            int i;
            int j;

            for (i = 0; i < serialPortNames.Length; i++) {
                var portName = serialPortNames[i];

                if(i % 2 == 0) {
                    try {
                        var node = new Port(portName);
                        node.Dispose();

                        break;
                    }
                    catch {}
                } 

            }
            for (j = serialPortNames.Length - 1; j >= 0; j--) {
                var portName = serialPortNames[j];

                if (j % 2 != 0) {
                    try {
                        var node = new Port(portName);
                        node.Dispose();

                        break;
                    }
                    catch {}
                }
            }

            return (serialPortNames[i], serialPortNames[j]);
        }

        private static void StartConsumer(string portName) {
            using (var p = new Process()) {
                p.StartInfo.FileName = $"D:\\Education\\BGUIR__LABS\\5_term\\ОКС\\lab1\\bin\\Debug\\net7.0\\lab1.exe";
                p.StartInfo.UseShellExecute = true;
                p.StartInfo.Arguments = portName;
                p.Start();
            }
        }
    }
}