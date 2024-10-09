using BerkeleyDB;
using Domain.Core.Berkeley;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;
using Insfrastructure.Data.Berkeley.Extensions;
using System.Text.Json;

namespace Insfrastructure.Data.Berkeley
{
    public class GenreRepository : IGenreRepository
    {
        private readonly Database _database;

        private DatabaseEntry _key;

        public GenreRepository(Database database)
        {
            _database = database;
            _key = new DatabaseEntry();
            _key.SetValue("genre");
        }

        public IGenre Create(string name, string instruments)
        {
            var genre = new GenreEntity { Name = name, Instruments = instruments };

            var collection = Get().Cast<GenreEntity>().ToList();
            collection.Add(genre);

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();

            return genre;
        }

        public void Delete(IGenre genre)
        {
            var collection = Get().Cast<GenreEntity>().ToList();
            collection.RemoveAll(g => g.Name.Equals(genre.Name));

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();
        }

        public IGenre Get(string name)
        {
            return Get().FirstOrDefault(g => g.Name.Equals(name));
        }

        public IEnumerable<IGenre> Get()
        {
            IEnumerable<IGenre> result = null;

            if (_database.Exists(_key))
            {
                var json = _database.Get(_key).Value.AsString();

                result = JsonSerializer.Deserialize<IEnumerable<GenreEntity>>(json);
            }

            return result ?? Enumerable.Empty<IGenre>();
        }
    }
}
