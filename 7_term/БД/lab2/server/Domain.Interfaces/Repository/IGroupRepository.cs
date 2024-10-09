using Domain.Interfaces.Entity;

namespace Domain.Interfaces.Repository
{
    public interface IGroupRepository
    {
        IGroup Get(string name);

        IEnumerable<IGroup> Get();

        IGroup Create(string name, int personsCount, int popularity);

        void Delete(IGroup group);
    }
}
