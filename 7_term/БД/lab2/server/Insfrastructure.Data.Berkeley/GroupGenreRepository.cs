using BerkeleyDB;
using Domain.Core.Berkeley;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;
using Insfrastructure.Data.Berkeley.Extensions;
using System.Text.Json;

namespace Insfrastructure.Data.Berkeley
{
    public class GroupGenreRepository : IGroupGenreRepository
    {
        private readonly Database _database;

        private DatabaseEntry _key;

        public GroupGenreRepository(Database database)
        {
            _database = database;
            _key = new DatabaseEntry();
            _key.SetValue("group-genre");
        }

        public IGroupGenre Create(IGroup group, IGenre genre)
        {
            var groupGenre = new GroupGenreEntity { Group = group, Genre = genre };

            var tariffServices = Get().Cast<GroupGenreEntity>().ToList();
            tariffServices.Add(groupGenre);

            var json = JsonSerializer.Serialize(tariffServices);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();

            return groupGenre;
        }

        public void Delete(IGroupGenre groupGenre)
        {
            var collection = Get().Cast<GroupGenreEntity>().ToList();
            collection.RemoveAll(gg => gg.Group.Name.Equals(groupGenre.Group.Name) && gg.Genre.Name.Equals(groupGenre.Genre.Name));

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();
        }

        public IGroupGenre Get(IGroup group, IGenre genre)
        {
            return Get().FirstOrDefault(gg => gg.Group.Name.Equals(group.Name) && gg.Genre.Name.Equals(genre.Name));
        }

        public IEnumerable<IGroupGenre> Get()
        {
            IEnumerable<IGroupGenre> result = null;

            if (_database.Exists(_key))
            {
                var json = _database.Get(_key).Value.AsString();

                result = JsonSerializer.Deserialize<IEnumerable<GroupGenreEntity>>(json);
            }

            return result ?? Enumerable.Empty<IGroupGenre>();
        }
    }
}
