using BerkeleyDB;
using System.Text;

namespace Insfrastructure.Data.Berkeley.Extensions
{
    public static class DatabaseEntryExtensions
    {
        public static string AsString(this DatabaseEntry databaseEntry)
        {
            return Encoding.ASCII.GetString(databaseEntry.Data);
        }

        public static void SetValue(this DatabaseEntry databaseEntry, string value)
        {
            databaseEntry.Data = Encoding.ASCII.GetBytes(value);
        }

        public static void Create(this DatabaseEntry databaseEntry, string value)
        {
            databaseEntry.Data = Encoding.ASCII.GetBytes(value);
        }
    }
}
