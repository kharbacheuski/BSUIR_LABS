namespace lab1
{
    public class FrameStatus
    {
        public bool addressRecognizedBit;
        public bool frameCopied;

        public byte ToByte()
        {
            byte acByte = 0;

            if (addressRecognizedBit) acByte = (byte)(acByte | 0b10001000);
            if (frameCopied) acByte = (byte)(acByte | 0b01000100);

            return acByte;
        }

        public static FrameStatus FromByte(byte frameStatusByte)
        {
            var frameControl = new FrameStatus();

            frameControl.addressRecognizedBit = (frameStatusByte & 0b10001000) > 0;
            frameControl.frameCopied = (frameStatusByte & 0b01001000) > 0;

            return frameControl;
        }
    }
}
