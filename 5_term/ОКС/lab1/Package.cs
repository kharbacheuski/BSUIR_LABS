using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    public class Package
    {
        public byte flag = (byte)128;
        public byte[] destinationAddress;
        public byte[] sourceAddress;
        public int length = 10;
        public byte[] data;
        public byte FCS;

        public Package()
        {
            destinationAddress = new byte[4];
            sourceAddress = new byte[4];
        }

        public byte[] Serialize()
        {
            List<byte> dataBytes = new List<byte> { };

            dataBytes.Add(this.flag);
            dataBytes.AddRange(this.destinationAddress);
            dataBytes.AddRange(this.sourceAddress);
            dataBytes.AddRange(BitConverter.GetBytes(this.length));
            dataBytes.AddRange(this.data);
            dataBytes.Add(this.FCS);

            return dataBytes.ToArray();
        }

        public Package Deserialize(byte[] dataBytes)
        {
            this.flag = dataBytes[0];
            this.length = BitConverter.ToInt32(dataBytes, 9);
            this.data = new byte[this.length];
            Array.Copy(dataBytes, 13, this.data, 0, this.length);

            return this;
        }
    }
}

