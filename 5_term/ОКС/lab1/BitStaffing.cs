
using System.Collections;
using System.Text;

namespace lab1 {

    public class BitStaffing 
    {
        string flag = "00011110"; // 120
        string stringInitiator = "0011110";
        string stringEncoded =   "10011110";

        public string BytesToBitString(byte[] bytes)
        {
            var bitArray = new BitArray(bytes);
            var bitString = new StringBuilder();

            for (int i = 0; i < bitArray.Length; i++)
            {
                char c = bitArray[i] ? '1' : '0';
                bitString.Append(c);
            }

            return bitString.ToString();
        }

        public byte[] BitStringToBytes(string text)
        {
            var bitArray = new BitArray(text.Length);
                
            for (int i = 0; i < text.Length; i++)
                bitArray[i] = text[i] == '1';

            var bytes = new byte[(int)Math.Ceiling(bitArray.Length / 8.0)];

            bitArray.CopyTo(bytes, 0);

            return bytes;
        }


        public byte[] EncodeData(string data) 
        {
            var dataBitsString = BytesToBitString(Encoding.ASCII.GetBytes(data));

            Console.WriteLine("before encoding " + dataBitsString);

            var encodedBitsString = dataBitsString.Replace(stringInitiator, stringEncoded);

            Console.WriteLine("after  encoding " + encodedBitsString);

            var bytes = BitStringToBytes(encodedBitsString);

            return bytes;
        }

        public string DecodeData(byte[] data) 
        {
            var dataBitsString = BytesToBitString(data);
            
            var decodedBitsString = dataBitsString.Replace(stringEncoded, stringInitiator);

            var bytes = BitStringToBytes(decodedBitsString);
            
            return Encoding.ASCII.GetString(bytes);
        }
    }
}