using Domain.Core.Postgres;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;

namespace Insfrastructure.Data.Postgres
{
    public class GroupRepository : IGroupRepository
    {
        private readonly AppDbContext _dbContext;

        public GroupRepository(AppDbContext dbContext)
        {
            _dbContext = dbContext;
        }


        public IGroup Create(string name, int personsCount, int popularity)
        {
            var entity = new GroupEntity();
            entity.Name = name;
            entity.PersonsCount = personsCount;
            entity.Popularity = popularity;

            var group = _dbContext.Add(entity);

            _dbContext.SaveChanges();

            return group.Entity;
        }

        public void Delete(IGroup group)
        {
            _dbContext.Group.Remove((GroupEntity)group);
            _dbContext.SaveChanges();
        }

        public IGroup Get(string name)
        {
            return _dbContext.Group.FirstOrDefault(g => g.Name.Equals(name));
        }

        public IEnumerable<IGroup> Get()
        {
            return _dbContext.Group.ToList();
        }
    }
}
