using BerkeleyDB;
using Domain.Core.Berkeley;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;
using Insfrastructure.Data.Berkeley.Extensions;
using System.Text.Json;

namespace Insfrastructure.Data.Berkeley
{
    public class RecordRepository : IRecordRepository
    {
        private readonly Database _database;

        private DatabaseEntry _key;

        public RecordRepository(Database database)
        {
            _database = database;
            _key = new DatabaseEntry();
            _key.SetValue("record");
        }

        public IRecord Create(string number, DateTime date, int hours, IRoom room, IGroup group)
        {
            var record = new RecordEntity { Number = number, Date = date, Hours = hours, Room = room, Group = group };

            var collection = Get().Cast<RecordEntity>().ToList();
            collection.Add(record);

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();

            return record;
        }

        public void Delete(IRecord record)
        {
            var collection = Get().Cast<RecordEntity>().ToList();
            collection.RemoveAll(r => r.Number.Equals(record.Number));

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();
        }

        public IRecord Get(string number)
        {
            return Get().FirstOrDefault(r => r.Number.Equals(number));
        }

        public IEnumerable<IRecord> Get()
        {
            IEnumerable<IRecord> result = null;

            if (_database.Exists(_key))
            {
                var json = _database.Get(_key).Value.AsString();

                result = JsonSerializer.Deserialize<IEnumerable<RecordEntity>>(json);
            }

            return result ?? Enumerable.Empty<IRecord>();
        }
    }
}
