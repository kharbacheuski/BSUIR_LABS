using BerkeleyDB;
using Domain.Core.Berkeley;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;
using Insfrastructure.Data.Berkeley.Extensions;
using System.Text.Json;

namespace Insfrastructure.Data.Berkeley
{
    public class RoomRepository : IRoomRepository
    {
        private readonly Database _database;

        private DatabaseEntry _key;

        public RoomRepository(Database database)
        {
            _database = database;
            _key = new DatabaseEntry();
            _key.SetValue("room");
        }

        public IRoom Get(string number)
        {
            return Get().FirstOrDefault(r => r.Number.Equals(number));
        }

        public IEnumerable<IRoom> Get()
        {
            IEnumerable<IRoom> result = null;

            if (_database.Exists(_key))
            {
                var json = _database.Get(_key).Value.AsString();

                result = JsonSerializer.Deserialize<IEnumerable<RoomEntity>>(json);
            }

            return result ?? Enumerable.Empty<IRoom>();
        }

        public IRoom Create(string number, int square, int personsCount, decimal rent)
        {
            var room = new RoomEntity { Number = number, Square = square, PersonsCount = personsCount, Rent = rent };

            var collection = Get().Cast<RoomEntity>().ToList();
            collection.Add(room);

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();

            return room;
        }

        public void Delete(IRoom room)
        {
            var collection = Get().Cast<RoomEntity>().ToList();
            collection.RemoveAll(s => s.Number.Equals(room.Number));

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();
        }
    }
}
