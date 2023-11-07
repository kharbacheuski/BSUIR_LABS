
namespace lab1
{
    public class Package
    {
        public byte flag;
        public byte destinationAddress;
        public byte sourceAddress;
        public int length;
        public byte[] data;
        public byte FCS;

        public Package() {
            flag = 128;
            destinationAddress = 0; 
            sourceAddress = 0;
            length = 10;
            data = new byte[length];
            FCS = 0;
        }

        public byte[] Serialize()
        {
            List<byte> dataBytes = new List<byte> { };

            dataBytes.Add(flag);
            dataBytes.Add(destinationAddress);
            dataBytes.Add(sourceAddress);
            dataBytes.AddRange(BitConverter.GetBytes(length));
            dataBytes.AddRange(data);
            dataBytes.Add(FCS);

            return dataBytes.ToArray();
        }

        public Package Deserialize(byte[] dataBytes)
        {
            flag = dataBytes[0]; // 0
            destinationAddress = dataBytes[1]; // 1
            sourceAddress = dataBytes[2]; // 2
            data = new byte[length]; // 7 8 9 10 11 12 13 14 15 16

            Array.Copy(dataBytes, 7, data, 0, length);
            FCS = dataBytes.Last();

            return this;
        }
    }
}

