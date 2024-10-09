using Domain.Core.Postgres;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;

namespace Insfrastructure.Data.Postgres
{
    public class GenreRepository : IGenreRepository
    {
        private readonly AppDbContext _dbContext;

        public GenreRepository(AppDbContext dbContext)
        {
            _dbContext = dbContext;
        }

        public IGenre Create(string name, string instruments)
        {
            var entity = new GenreEntity();
            entity.Name = name;
            entity.Instruments = instruments;

            var genre = _dbContext.Add(entity);

            _dbContext.SaveChanges();

            return genre.Entity;
        }

        public void Delete(IGenre genre)
        {
            _dbContext.Genre.Remove((GenreEntity)genre);
            _dbContext.SaveChanges();
        }

        public IGenre Get(string name)
        {
            return _dbContext.Genre.FirstOrDefault(g => g.Name.Equals(name));
        }

        public IEnumerable<IGenre> Get()
        {
            return _dbContext.Genre.ToList();
        }
    }
}
