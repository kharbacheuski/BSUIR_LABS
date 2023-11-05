
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

            var encodedBitsString = dataBitsString.Replace(stringInitiator, stringEncoded);

            var bytes = DataOperations.BitStringToBytes(encodedBitsString);

            return bytes;
        }

        public byte[] DecodeData(byte[] data) 
        {
            var dataBitsString = DataOperations.BytesToBitString(data);

            var decodedBitsString = dataBitsString.Replace(stringEncoded, stringInitiator);

            var bytes = DataOperations.BitStringToBytes(decodedBitsString);
            
            return bytes;
        }
    }
}