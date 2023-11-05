using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    public class DataOperations
    {
        public static byte[] BitStringToBytes(string text)
        {
            var bitArray = new BitArray(text.Length);

            for (int i = 0; i < text.Length; i++)
                bitArray[i] = text[i] == '1';

            var bytes = new byte[(int)Math.Ceiling(bitArray.Length / 8.0)];

            bitArray.CopyTo(bytes, 0);

            return bytes;
        }

        public static string BytesToBitString(byte[] bytes)
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
    }
}
