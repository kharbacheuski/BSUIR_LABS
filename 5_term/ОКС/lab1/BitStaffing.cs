
using System.Collections;
using System.Text;
using static System.Net.Mime.MediaTypeNames;

namespace lab1 {

    public struct Package 
    {
        public byte flag;
        public byte[] destinationAddress;
        public byte[] sourceAddress;
        public int length;
        public byte[] data;
        public byte FCS;

        public Package()
        {
            destinationAddress = new byte[4];
            sourceAddress = new byte[4];
        }
    }

    public class BitStaffing 
    {
        string stringInitiator = "0011110";
        string stringEncoded =   "10011110";

        public string ToBitString(BitArray bits)
        {
            var sb = new StringBuilder();

            for (int i = 0; i < bits.Length; i++)
            {
                char c = bits[i] ? '1' : '0';
                sb.Append(c);
            }

            return sb.ToString();
        }

        public BitArray StringToBits(string text)
        {
            var bitArray = new BitArray(text.Length);
                
            for (int i = 0; i < text.Length; i++)
                bitArray[i] = text[i] == '1';

            return bitArray;
        }

        public byte[] ToByteArray(BitArray bitArray)
        {
            var bytes = new byte[(int)Math.Ceiling(bitArray.Length / 8.0)];
            
            bitArray.CopyTo(bytes, 0);

            return bytes;
        }

        public byte[] EncodeData(string data) 
        {
            var dataBits = new BitArray(Encoding.ASCII.GetBytes(data));

            var dataBitsString = ToBitString(dataBits);

            Console.WriteLine("before encoding " + dataBitsString);

            var encodedData = dataBitsString.Replace(stringInitiator, stringEncoded);

            Console.WriteLine("after  encoding " + encodedData);

            var bits = StringToBits(encodedData);
            var bytes = ToByteArray(bits);

            return bytes;
        }

        public string DecodeData(byte[] data) 
        {
            Console.WriteLine("data len " + data.Length);

            var dataBits = new BitArray(data);
            var dataBitsString = ToBitString(dataBits);

            Console.WriteLine("recieve encoded " + dataBitsString);
            
            var decodedBitsString = dataBitsString.Replace(stringEncoded, stringInitiator);

            Console.WriteLine("recieve decoded " + decodedBitsString);

            var bitArray = StringToBits(decodedBitsString);

            var byteArray = ToByteArray(bitArray);
            
            return Encoding.ASCII.GetString(byteArray);
        }

        public byte[] Serialize(Package pack)
        {
            List<byte> dataBytes = new List<byte>
            {
                pack.flag
            };

            dataBytes.AddRange(pack.destinationAddress);
            dataBytes.AddRange(pack.sourceAddress);
            dataBytes.AddRange(BitConverter.GetBytes(pack.length));
            dataBytes.AddRange(pack.data);
            dataBytes.Add(pack.FCS);

            return dataBytes.ToArray();
        }

        public Package Deserialize(byte[] dataBytes)
        {
            var recievePackage = new Package();

            recievePackage.flag = dataBytes[0];
            recievePackage.length = BitConverter.ToInt32(dataBytes, 9);
            recievePackage.data = new byte[recievePackage.length];
            Array.Copy(dataBytes, 13, recievePackage.data, 0, recievePackage.length);

            return recievePackage;
        }
    }
}