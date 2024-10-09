using Domain.Interfaces.Entity;

namespace Domain.Interfaces.Repository
{
    public interface IRecordRepository
    {
        IRecord Get(string number);

        IEnumerable<IRecord> Get();

        IRecord Create(string number, DateTime date, int hours, IRoom room, IGroup group);

        void Delete(IRecord record);
    }
}
