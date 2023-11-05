
namespace lab1
{
    public class Package
    {
        public byte flag = (byte)128;
        public byte destinationAddress;
        public byte sourceAddress;
        public int length = 10;
        public byte[] data;
        public byte FCS;

        public Package() {
            data = new byte[length];
        }

        public byte[] Serialize()
        {
            List<byte> dataBytes = new List<byte>();

            dataBytes.Add(this.flag);
            dataBytes.Add(this.destinationAddress);
            dataBytes.Add(this.sourceAddress);
            dataBytes.AddRange(BitConverter.GetBytes(this.length));
            dataBytes.AddRange(this.data);
            dataBytes.Add(this.FCS);

            return dataBytes.ToArray();
        }

        public Package Deserialize(byte[] dataBytes)
        {
            this.flag = dataBytes[0];
            this.length = BitConverter.ToInt32(dataBytes, 3);
            this.data = new byte[this.length];

            Console.WriteLine("Len=" + this.length);
            Array.Copy(dataBytes, 7, this.data, 0, this.length);

            return this;
        }
    }
}

