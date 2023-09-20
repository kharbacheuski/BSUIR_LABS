using System.Collections;
using System.Text;

namespace test
{
    internal class Program
    {
        static void Main(string[] args)
        {

            var data = "cx"; // 10000000
            // 01111000

            var x = new BitArray(Encoding.ASCII.GetBytes(data));

            var s = ToBitString(x);

            Console.ReadLine();
        }

        public static string ToBitString(BitArray bits)
        {
            var sb = new StringBuilder();

            for (int i = 0; i < bits.Length; i++)
            {
                char c = bits[i] ? '1' : '0';
                sb.Append(c);
            }

            return sb.ToString();
        }
    }
}