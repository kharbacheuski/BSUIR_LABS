using BerkeleyDB;
using Domain.Core.Berkeley;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;
using Insfrastructure.Data.Berkeley.Extensions;
using System.Text.Json;

namespace Insfrastructure.Data.Berkeley
{
    public class GroupRepository : IGroupRepository
    {
        private readonly Database _database;

        private DatabaseEntry _key;

        public GroupRepository(Database database)
        {
            _database = database;
            _key = new DatabaseEntry();
            _key.SetValue("group");
        }

        public IGroup Create(string name, int personsCount, int popularity)
        {
            var group = new GroupEntity { Name = name, PersonsCount = personsCount, Popularity = popularity };

            var collection = Get().Cast<GroupEntity>().ToList();
            collection.Add(group);

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();

            return group;
        }

        public void Delete(IGroup group)
        {
            var collection = Get().Cast<GroupEntity>().ToList();
            collection.RemoveAll(g => g.Name.Equals(group.Name));

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();
        }

        public IGroup Get(string name)
        {
            return Get().FirstOrDefault(g => g.Name.Equals(name));
        }

        public IEnumerable<IGroup> Get()
        {
            IEnumerable<IGroup> result = null;

            if (_database.Exists(_key))
            {
                var json = _database.Get(_key).Value.AsString();

                result = JsonSerializer.Deserialize<IEnumerable<GroupEntity>>(json);
            }

            return result ?? Enumerable.Empty<IGroup>();
        }
    }
}
