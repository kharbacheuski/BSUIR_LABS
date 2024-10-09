using Domain.Core.Postgres;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;

namespace Insfrastructure.Data.Postgres
{
    public class RoomRepository : IRoomRepository
    {
        private readonly AppDbContext _dbContext;

        public RoomRepository(AppDbContext dbContext)
        {
            _dbContext = dbContext;
        }

        public IRoom Create(string number, int square, int personsCount, decimal rent)
        {
            var entity = new RoomEntity();
            entity.Number = number;
            entity.Square = square;
            entity.PersonsCount = personsCount;
            entity.Rent = rent;

            var room = _dbContext.Add(entity);

            _dbContext.SaveChanges();

            return room.Entity;
        }

        public void Delete(IRoom room)
        {
            _dbContext.Room.Remove((RoomEntity)room);
            _dbContext.SaveChanges();
        }

        public IRoom Get(string number)
        {
            return _dbContext.Room.FirstOrDefault(r => r.Number.Equals(number));
        }

        public IEnumerable<IRoom> Get()
        {
            return _dbContext.Room.ToList();
        }
    }
}
