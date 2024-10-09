using Domain.Core.Postgres;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;
using Microsoft.EntityFrameworkCore;

namespace Insfrastructure.Data.Postgres
{
    public class RecordGenreRepository : IRecordGenreRepository
    {
        private readonly AppDbContext _dbContext;

        public RecordGenreRepository(AppDbContext dbContext)
        {
            _dbContext = dbContext;
        }

        public IRecordGenre Create(IRecord record, IGenre genre)
        {
            var entity = new RecordGenreEntity();
            entity.Record = record;
            entity.Genre = genre;

            var recordGenre = _dbContext.Add(entity);

            _dbContext.SaveChanges();

            return recordGenre.Entity;
        }

        public void Delete(IRecordGenre recordGenre)
        {
            _dbContext.RecordGenre.Remove((RecordGenreEntity)recordGenre);
            _dbContext.SaveChanges();
        }

        public IRecordGenre Get(IRecord record, IGenre genre)
        {
            return _dbContext.RecordGenre.Include(rg => rg.RecordEntity).Include(rg => rg.GenreEntity).FirstOrDefault(rg => rg.Record.Equals(record) && rg.Genre.Equals(genre));
        }

        public IEnumerable<IRecordGenre> Get()
        {
            return _dbContext.RecordGenre.Include(rg => rg.RecordEntity).Include(rg => rg.GenreEntity).ToList();
        }
    }
}
