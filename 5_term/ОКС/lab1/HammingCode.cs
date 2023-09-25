using System;
using System.Collections.Generic;
using System.Diagnostics.Metrics;
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
            var positionsCount = Math.Floor(Math.Log(dataLength, 2));

            for (int i = 0; i <= positionsCount; i++)
               positions.Add((int)Math.Pow(2.0, i) - 1);

            return positions;
        }

        public byte[] DeleteHammingCodes(byte[] recivedDataBytes)
        {
            var str = DataOperations.BytesToBitString(recivedDataBytes);
            List<int> positions = GetHammingCodePositionIndexes((int)Math.Floor((double)str.Length));
            string withoutHammings = str;

            for (int i = positions.Count - 1; i >= 0; i--)
            {
                withoutHammings = withoutHammings.Remove(positions[i], 1);
            }

            return DataOperations.BitStringToBytes(withoutHammings);
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

            for (int pos = 0; pos < positions.Count; pos++)
            {
                number = 0;
                jump = 2 * (positions[pos] + 1);

                for (int i = positions[pos]; i < dataBitsStringWithZeroBits.Length; i += jump)
                {
                    for(int j = i; j <= i + positions[pos] && j < dataBitsStringWithZeroBits.Length; j++)
                    {
                        if (dataBitsStringWithZeroBits[j] == '1')
                            number += 1;
                    }
                }

                if (number % 2 != 0)
                    answer[positions[pos]] = '1';
                else answer[positions[pos]] = '0';
            }


            return answer.ToString();
        }
        public byte[] Encode(byte[] data)
        {
            var dataBitsString = DataOperations.BytesToBitString(data);

            var positions = GetHammingCodePositionIndexes(dataBitsString.Length);
            var stringWithZeros = SetZeroBitsIntoPositions(dataBitsString, positions);
            var encodedString = SetHammingCodesValues(stringWithZeros, positions);

            var bytes = DataOperations.BitStringToBytes(encodedString);

            return bytes;
        }

        public byte[] FixError(byte[] data, int errorIndex)
        {
            Console.WriteLine($"Data are damage in index {errorIndex}, try to fix");

            var str = DataOperations.BytesToBitString(data);

            StringBuilder damageString = new StringBuilder(str);

            damageString[errorIndex] = damageString[errorIndex] == '1' ? '0' : '1'; // заменяем поломанный бит на противоположный

            var withoutHammingsCodeString = DeleteHammingCodes(DataOperations.BitStringToBytes(damageString.ToString())); // удаляем коды хеминга

            return withoutHammingsCodeString; // возвращаем правильную строку
        }

        public byte[] EmulateError(byte[] data)
        {
            var str = DataOperations.BytesToBitString(data);
            StringBuilder damageString = new StringBuilder(str);

            damageString[8] = damageString[8] == '1' ? '0' : '1'; // меняем значение какого-то бита на противоположное

            return DataOperations.BitStringToBytes(damageString.ToString());
        }

        public byte[] Decode(byte[] data)
        {
            var dataWithErrorBytes = EmulateError(data); // добавляем в данные ошибку

            var dataWithErrorString = DataOperations.BytesToBitString(dataWithErrorBytes); // строка данные с ошибкой
            var dataWithError = DeleteHammingCodes(dataWithErrorBytes); // байты данные с ошибкой без кодов хеминга

            Console.WriteLine($"Data with error: {Encoding.ASCII.GetString(dataWithError)}");

            var encodedWithErrorString = DataOperations.BytesToBitString(Encode(dataWithError)); // данные с ошибкой закодированные (с кодами хеминга)

            var positions = GetHammingCodePositionIndexes(data.Length*8);
            int counter = 0;

            Console.WriteLine($"Recive bit with error:   {dataWithErrorString}");
            Console.WriteLine($"Decoded bit with error:   {DataOperations.BytesToBitString(dataWithError)}");
            Console.WriteLine($"Encoding bit with error: {encodedWithErrorString}");

            foreach (int pos in positions)
            {
                if (dataWithErrorString[pos] != encodedWithErrorString[pos]) // сравниваем пришедшую строку с ошибкой и вновь закодированную строку с ошибкой
                {
                    counter += pos;
                }
            }

            if (counter == 0)
            {
                Console.WriteLine($"Data recieve correct!");

                return DeleteHammingCodes(data);
            }
            else
            {
                var afterFix = FixError(dataWithErrorBytes, counter+1);

                Console.WriteLine($"After fix: {DataOperations.BytesToBitString(afterFix)}");

                return afterFix;
            }
        }
    }
}
