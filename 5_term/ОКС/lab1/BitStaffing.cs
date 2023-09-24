
using System.Collections;
using System.Text;

namespace lab1 {

    public class BitStaffing 
    {
        string flag = "00011110"; // "x" (120 reverse)
        string stringInitiator = "0011110";
        string stringEncoded =   "10011110";

        public byte[] EncodeData(byte[] data) 
        {
            var dataBitsString = DataOperations.BytesToBitString(data);
            
            Console.WriteLine("before encoding " + dataBitsString);

            var encodedBitsString = dataBitsString.Replace(stringInitiator, stringEncoded);

            Console.WriteLine("after  encoding " + encodedBitsString);

            var bytes = DataOperations.BitStringToBytes(encodedBitsString);

            return bytes;
        }

        public byte[] DecodeData(byte[] data) 
        {
            var dataBitsString = DataOperations.BytesToBitString(data);

            Console.WriteLine("recieve  encoding " + dataBitsString);

            var decodedBitsString = dataBitsString.Replace(stringEncoded, stringInitiator);

            var bytes = DataOperations.BitStringToBytes(decodedBitsString);
            
            return bytes;
        }
    }
}