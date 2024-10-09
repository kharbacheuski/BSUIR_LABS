using Domain.Core.Postgres;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;
using Microsoft.EntityFrameworkCore;

namespace Insfrastructure.Data.Postgres
{
    public class GroupGenreRepository : IGroupGenreRepository
    {
        private readonly AppDbContext _dbContext;

        public GroupGenreRepository(AppDbContext dbContext)
        {
            _dbContext = dbContext;
        }

        public IGroupGenre Create(IGroup group, IGenre genre)
        {
            var entity = new GroupGenreEntity();
            entity.Group = group;
            entity.Genre = genre;

            var groupGenre = _dbContext.Add(entity);

            _dbContext.SaveChanges();

            return groupGenre.Entity;
        }

        public void Delete(IGroupGenre groupGenre)
        {
            _dbContext.GroupGenre.Remove((GroupGenreEntity)groupGenre);
            _dbContext.SaveChanges();
        }

        public IGroupGenre Get(IGroup group, IGenre genre)
        {
            return _dbContext.GroupGenre.Include(gg => gg.GroupEntity).Include(gg => gg.GenreEntity).FirstOrDefault(gg => gg.Group.Equals(group) && gg.Genre.Equals(genre));
        }

        public IEnumerable<IGroupGenre> Get()
        {
            return _dbContext.GroupGenre.Include(gg => gg.GroupEntity).Include(gg => gg.GenreEntity).ToList();
        }
    }
}
