using System;
using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace lab1
{
    internal class CSMA
    {
        private const byte JAM_SIGNAL = 125;
        private const byte END_OF_MESSAGE = 126;

        private Random random = new Random();
        public void Send(SerialPort serialPort, byte[] data)
        {
            foreach (byte item in data)
            {
                for (int numberOfAttempt = 0; ; numberOfAttempt++)
                {
                    waitFree();

                    serialPort.Write(new byte[] { item }, 0, 1);
                    Console.WriteLine("Sended byte: " + DataOperations.BytesToBitString(new byte[] { item }));

                    if (randomChance()) {
                        serialPort.Write(new byte[] { JAM_SIGNAL }, 0, 1);
                        Console.WriteLine("Collision detected, sended jam byte: " + DataOperations.BytesToBitString(new byte[] { JAM_SIGNAL }));

                        delaySending();
                    }
                    else break;
                }

            }

            serialPort.Write(new byte[] { END_OF_MESSAGE }, 0, 1);
        }

        public byte[] Read(SerialPort serialPort)
        {
            var receiveBuffer = new List<byte>();
            byte[] b = new byte[1];

            while (true)
            {
                if (serialPort.BytesToRead == 0) continue;     

                serialPort.Read(b, 0, 1);

                if (b[0] == END_OF_MESSAGE) break;

                Console.WriteLine("Readed byte: " + DataOperations.BytesToBitString(b));

                if (b[0] == JAM_SIGNAL)
                {
                    Console.WriteLine("Jam detected");
                    receiveBuffer.RemoveAt(receiveBuffer.Count - 1);
                    continue;
                }

                receiveBuffer.Add(b[0]);
            }

            return receiveBuffer.ToArray();
        }

        private void waitFree()
        {
            if (randomChance()) Thread.Sleep(100);
        }

        private bool randomChance()
        {
            return random.Next(100) > 50;
        }
        private void delaySending() => Thread.Sleep(random.Next(1000));
    }
}
