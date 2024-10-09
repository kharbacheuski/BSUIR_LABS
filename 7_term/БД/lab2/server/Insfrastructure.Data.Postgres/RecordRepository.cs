using Domain.Core.Postgres;
using Domain.Interfaces.Entity;
using Domain.Interfaces.Repository;
using Microsoft.EntityFrameworkCore;

namespace Insfrastructure.Data.Postgres
{
    public class RecordRepository : IRecordRepository
    {
        private readonly AppDbContext _dbContext;

        public RecordRepository(AppDbContext dbContext)
        {
            _dbContext = dbContext;
        }

        public IRecord Create(string number, DateTime date, int hours, IRoom room, IGroup group)
        {
            var entity = new RecordEntity();
            entity.Number = number;
            entity.Date = new DateTime(date.Ticks, DateTimeKind.Utc);
            entity.Hours = hours;
            entity.Room = room;
            entity.Group = group;

            var record = _dbContext.Add(entity);

            _dbContext.SaveChanges();

            return record.Entity;
        }

        public void Delete(IRecord record)
        {
            _dbContext.Record.Remove((RecordEntity)record);
            _dbContext.SaveChanges();
        }

        public IRecord Get(string number)
        {
            return _dbContext.Record.Include(r => r.GroupEntity).Include(r => r.RoomEntity).FirstOrDefault(r => r.Number.Equals(number));
        }

        public IEnumerable<IRecord> Get()
        {
            return _dbContext.Record.Include(r => r.GroupEntity).Include(r => r.RoomEntity).ToList();
        }
    }
}
