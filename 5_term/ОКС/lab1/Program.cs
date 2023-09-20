using System.Diagnostics;
using System.IO.Ports;

namespace lab1 {
    internal class Program 
    {
        static void Main(string[] args) 
        {
            Port port = null;

            if (args.Length == 0) 
            {
                var ports = GetFreeSerialPorts();

                Console.WriteLine($"Enter com-port speed");

                var speed = Convert.ToInt32(Console.ReadLine());

                port = new Producer(ports.Item1, speed);

                StartConsumer(ports.Item2, speed);
            }
            else port = new Consumer(args[0], Convert.ToInt32(args[1]));

            port.Do();
        }

        private static (string, string) GetFreeSerialPorts() 
        {
            var serialPortNames = SerialPort.GetPortNames();
            int i;
            int j;

            for (i = 0; i < serialPortNames.Length; i++) 
            {
                var portName = serialPortNames[i];

                if(i % 2 == 0) 
                {
                    try 
                    {
                        var port = new Port(portName);
                        port.Dispose();

                        break;
                    }
                    catch {}
                } 

            }
            for (j = serialPortNames.Length - 1; j >= 0; j--) 
            {
                var portName = serialPortNames[j];

                if (j % 2 != 0) 
                {
                    try 
                    {
                        var port = new Port(portName);
                        port.Dispose();

                        break;
                    }
                    catch {}
                }
            }

            return (serialPortNames[i], serialPortNames[j]);
        }

        private static void StartConsumer(string portName, int speed) 
        {
            using (var p = new Process()) 
            {
                p.StartInfo.FileName = $"D:\\Education\\BGUIR__LABS\\5_term\\ОКС\\lab1\\bin\\Debug\\net7.0\\lab1.exe";
                p.StartInfo.UseShellExecute = true;
                p.StartInfo.Arguments = string.Join(" ", portName, speed);
                p.Start();
            }
        }
    }
}