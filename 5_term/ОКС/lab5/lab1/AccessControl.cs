namespace lab1
{
    public class AccessControl
    {
        public bool tokenBit;
        public bool monitorBit;
        public byte priorityBits;
        public byte reservationBits;

        public byte ToByte()
        {
            byte acByte = 0;

            acByte = (byte)(acByte | reservationBits);

            if (tokenBit) acByte = (byte)(acByte | 0b00010000);

            if (monitorBit) acByte = (byte)(acByte | 0b00001000);

            acByte = (byte)(acByte | (priorityBits << 5));

            return acByte;
        }

        public static AccessControl FromByte(byte accessControlByte)
        {
            var accessControl = new AccessControl();

            accessControl.priorityBits = (byte)((accessControlByte & 0b11100000) >> 5);
            accessControl.tokenBit = (accessControlByte & 0b00010000) > 0;
            accessControl.monitorBit = (accessControlByte & 0b00001000) > 0;
            accessControl.reservationBits = (byte)(accessControlByte & 0b00000111);

            return accessControl;
        }
    }
}
