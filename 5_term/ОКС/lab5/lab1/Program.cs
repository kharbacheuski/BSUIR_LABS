using System.Diagnostics;
using System.IO.Ports;

namespace lab1 {
    internal class Program 
    {
        private static void StartNode()
        {
            var ports = GetFreeSerialPorts();

            //Console.WriteLine($"Enter com-port speed");
            //var speed = Convert.ToInt32(Console.ReadLine());

            Console.WriteLine($"Is this node monitor? (1/0):");
            var isMonitor = Convert.ToInt32(Console.ReadLine());

            var node = new Port(ports.Item2, ports.Item1, isMonitor == 1, 19200);

            Console.WriteLine($"Consumer on port {ports.Item2}");
            Console.WriteLine($"Producer on port {ports.Item1}");

            node.Do();
        }

        static void Main(string[] args) 
        {
            StartNode();
        }

        private static (string, string) GetFreeSerialPorts() 
        {
            var serialPortNames = SerialPort.GetPortNames().Order().ToArray();

            int i;

            for (i = 0; i < serialPortNames.Length; i+=2) 
            {
                var portNameRead = serialPortNames[i+1];
                var portNameWrite = serialPortNames[i];

                try
                {
                    var port = new Port(portNameRead, portNameWrite, false);
                    port.Dispose();

                    break;
                }
                catch {}
            }

            return (serialPortNames[i], serialPortNames[i+1]);
        }
    }
}