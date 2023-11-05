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

        public byte GetFCS(byte[] data) // isEven
        {
            var str = DataOperations.BytesToBitString(data);
            var parity = 0;

            foreach (var item in str)
            {
                parity += item == '1' ? 1 : 0;
            }

            return (byte)Convert.ToInt32(parity % 2 == 0);
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

        public byte[] FixError(byte[] data, int errorIndex, int countOfErrors)
        {
            Console.WriteLine($"Data are damage! Detected {countOfErrors} errors.");

            if(countOfErrors == 1)
            {
                Console.WriteLine($"{errorIndex} index is wrong. Try to fix...");

                var str = DataOperations.BytesToBitString(data);

                StringBuilder damageString = new StringBuilder(str);

                damageString[errorIndex] = damageString[errorIndex] == '1' ? '0' : '1'; // заменяем поломанный бит на противоположный

                var withoutHammingsCodeString = DeleteHammingCodes(DataOperations.BitStringToBytes(damageString.ToString())); // удаляем коды хеминга

                return withoutHammingsCodeString; // возвращаем правильную строку
            }
            else
            {
                Console.WriteLine($"We cant fix this...");

                return data;
            }
        }

        public byte[] EmulateError(byte[] data)
        {
            var str = DataOperations.BytesToBitString(data);

            Random r = new Random();
            int randomIndex = r.Next(0, str.Length - 2);
            int secondRandomIndex = r.Next(0, str.Length - 2);

            StringBuilder damageString = new StringBuilder(str);

            var temp = damageString[randomIndex];
            damageString[randomIndex] = '0'; // меняем значение какого-то бита на 1 (шанс - 50%)

            if(temp == '1')
            {
                damageString[secondRandomIndex] = '0'; // еще один бит - шанс 25%
            } 

            return DataOperations.BitStringToBytes(damageString.ToString());
        }

        public int GetCountOfErrors(byte[] data, byte FCS)
        {
            int countOfErrors = 1;

            if (GetFCS(data) == FCS) // если четность совпадает, то изменилось 2 бита (две ошибки)
            {
                countOfErrors = 2;
            }

            return countOfErrors;
        }

        public byte[] Decode(byte[] data, byte FCS)
        {
            var dataWithErrorBytes = EmulateError(data); // добавляем в данные ошибку

            int countOfErrors = GetCountOfErrors(dataWithErrorBytes, FCS);

            var dataWithErrorString = DataOperations.BytesToBitString(dataWithErrorBytes); // строка данные с ошибкой

            var dataWithError = DeleteHammingCodes(dataWithErrorBytes); // байты данные с ошибкой без кодов хеминга
            var encodedWithErrorString = DataOperations.BytesToBitString(Encode(dataWithError)); // данные с ошибкой закодированные (с кодами хеминга)

            var positions = GetHammingCodePositionIndexes(data.Length*8);
            int errorPosition = 0;

            foreach (int pos in positions)
            {
                if (dataWithErrorString[pos] != encodedWithErrorString[pos]) // сравниваем пришедшую строку с ошибкой и вновь закодированную строку с ошибкой
                {
                    errorPosition += pos + 1;
                } 
            }

            if (errorPosition == 0)
            {
                Console.WriteLine($"Recieve data is correct!");

                return DeleteHammingCodes(data);
            }
            else
            {
                var afterFix = FixError(dataWithErrorBytes, errorPosition - 1, countOfErrors);

                return afterFix;
            }
        }
    }
}
