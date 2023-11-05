using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    public static class SerialPortExtension
    {
        public static int GetPortNumber(this SerialPort serialPort)
        {
            var lastCharacter = new string(serialPort.PortName.SkipWhile(c => c < '0' || c > '9').ToArray());
            return int.Parse(lastCharacter);
        }
    }
}
