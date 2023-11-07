
namespace lab1
{
    public class TokenRingPackage
    {
        public Package package { get; set; }
        public AccessControl AC;
        public FrameStatus FS;

        public byte[] Serialize()
        {
            var bytes = new List<byte> { };
            var innerPackageBytes = package.Serialize();

            bytes.Add(AC.ToByte());
            bytes.Add(FS.ToByte());

            bytes.AddRange(innerPackageBytes);

            return bytes.ToArray();
        }

        public static TokenRingPackage Deserialize(byte[] dataBytes)
        {
            var innerPackage = new Package().Deserialize(dataBytes.Skip(2).ToArray());
            
            var package = new TokenRingPackage();

            package.package = innerPackage;
            package.AC = AccessControl.FromByte(dataBytes[0]);
            package.FS = FrameStatus.FromByte(dataBytes[1]);

            return package;
        }
    }
}
