using BerkeleyDB;
using Domain.Core.Berkeley;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;
using Insfrastructure.Data.Berkeley.Extensions;
using System.Text.Json;

namespace Insfrastructure.Data.Berkeley
{
    public class RecordGenreRepository : IRecordGenreRepository
    {
        private readonly Database _database;

        private DatabaseEntry _key;

        public RecordGenreRepository(Database database)
        {
            _database = database;
            _key = new DatabaseEntry();
            _key.SetValue("record-genre");
        }

        public IRecordGenre Create(IRecord record, IGenre genre)
        {
            var recordGenre = new RecordGenreEntity { Record = record, Genre = genre };

            var tariffServices = Get().Cast<RecordGenreEntity>().ToList();
            tariffServices.Add(recordGenre);

            var json = JsonSerializer.Serialize(tariffServices);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();

            return recordGenre;
        }

        public void Delete(IRecordGenre recordGenre)
        {
            var collection = Get().Cast<RecordGenreEntity>().ToList();
            collection.RemoveAll(rg => rg.Record.Number.Equals(recordGenre.Record.Number) && rg.Genre.Name.Equals(recordGenre.Genre.Name));

            var json = JsonSerializer.Serialize(collection);

            var data = new DatabaseEntry();
            data.SetValue(json);

            _database.Put(_key, data);
            _database.Sync();
        }

        public IRecordGenre Get(IRecord record, IGenre genre)
        {
            return Get().FirstOrDefault(rg => rg.Record.Number.Equals(record.Number) && rg.Genre.Name.Equals(genre.Name));
        }

        public IEnumerable<IRecordGenre> Get()
        {
            IEnumerable<IRecordGenre> result = null;

            if (_database.Exists(_key))
            {
                var json = _database.Get(_key).Value.AsString();

                result = JsonSerializer.Deserialize<IEnumerable<RecordGenreEntity>>(json);
            }

            return result ?? Enumerable.Empty<IRecordGenre>();
        }
    }
}
