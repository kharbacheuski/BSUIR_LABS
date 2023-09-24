using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    public class HammingCode
    {
        public List<int> GetHammingCodePositionIndexes(int dataLength)
        {
            List<int> positions = new List<int> { };
            var positionsCount = Math.Sqrt(dataLength) + 1;

            for(int i = 0; i < positionsCount; i++)
               positions.Add((int)Math.Pow(2.0, i) - 1);

            return positions;
        }

        public string DeleteHammingCodes(string recivedDataBitString)
        {
            List<int> positions = GetHammingCodePositionIndexes((recivedDataBitString.Length - 6)/8);
            string withoutHammings = recivedDataBitString;
            for (int i = 0; i < positions.Count; i++)
            {
                withoutHammings = withoutHammings.Remove(positions[i], 1);
            }

            return withoutHammings;
        }
        public string SetZeroBitsIntoPositions(string dataBitsString, List<int> positions)
        {
            string dataBitsStringWithZeroBits = dataBitsString;

            for (int i = 0; i < positions.Count; i++)
            {
                dataBitsStringWithZeroBits = dataBitsStringWithZeroBits.Insert(positions[i], "1");
            }

            return dataBitsStringWithZeroBits;
        }
        public string SetHammingCodesValues(string dataBitsStringWithZeroBits, List<int> positions)
        {
            StringBuilder answer = new StringBuilder(dataBitsStringWithZeroBits);

            int number;
            int jump;

            foreach (int pos in positions)
            {
                number = 0;
                jump = 2*(pos + 1);
                for (int i = pos; i < dataBitsStringWithZeroBits.Length; i += jump)
                {
                    for(int j = i; j <= i + pos; j++)
                    {
                        if (dataBitsStringWithZeroBits[j] == '1')
                            number += 1;
                    }
                }

                if (number % 2 != 0)
                    answer[pos] = '1';
            }


            return answer.ToString();
        }
        public byte[] Encode(byte[] data)
        {
            var dataBitsString = DataOperations.BytesToBitString(data);

            Console.WriteLine($"without hamming codes: {dataBitsString}");

            var positions = GetHammingCodePositionIndexes(data.Length);
            var stringWithZeros = SetZeroBitsIntoPositions(dataBitsString, positions);
            var encodedString = SetHammingCodesValues(stringWithZeros, positions);

            Console.WriteLine($"with hamming codes:    {encodedString}");

            var bytes = DataOperations.BitStringToBytes(encodedString);

            return bytes;
        }

        public byte[] Decode(byte[] data)
        {
            var dataBitsString = DataOperations.BytesToBitString(data);
            var without = DeleteHammingCodes(dataBitsString);

            var bytes = DataOperations.BitStringToBytes(without);

            Console.WriteLine($"Decode hamming: {Encoding.ASCII.GetString(bytes)}");

            return bytes;
        }
    }
}
