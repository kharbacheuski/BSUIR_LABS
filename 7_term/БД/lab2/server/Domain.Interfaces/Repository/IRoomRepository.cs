using Domain.Interfaces.Entity;

namespace Domain.Interfaces.Repository
{
    public interface IRoomRepository
    {
        IRoom Get(string number);

        IEnumerable<IRoom> Get();

        IRoom Create(string number, int square, int personsCount, decimal rent);

        void Delete(IRoom room);
    }
}
