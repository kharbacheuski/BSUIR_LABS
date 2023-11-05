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
        public int destinationAddress;
        public int sourceAddress;
        public int length = 10;
        public byte[] data;
        public byte FCS;

        public byte[] Serialize()
        {
            List<byte> dataBytes = new List<byte> { };

            dataBytes.Add(flag);
            dataBytes.AddRange(BitConverter.GetBytes(destinationAddress));
            dataBytes.AddRange(BitConverter.GetBytes(sourceAddress));
            dataBytes.AddRange(BitConverter.GetBytes(length));
            dataBytes.AddRange(data);
            dataBytes.Add(FCS);

            return dataBytes.ToArray();
        }

        public Package Deserialize(byte[] dataBytes)
        {
            flag = dataBytes[0];
            destinationAddress = BitConverter.ToInt32(dataBytes, 1);
            sourceAddress = BitConverter.ToInt32(dataBytes, 5); ;
            length = BitConverter.ToInt32(dataBytes, 9);
            data = new byte[length];
            Array.Copy(dataBytes, 13, data, 0, length);
            FCS = dataBytes[dataBytes.Length - 1];

            return this;
        }
    }
}

