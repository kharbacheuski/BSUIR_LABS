using Domain.Interfaces.Entity;

namespace Domain.Interfaces.Repository
{
    public interface IRecordGenreRepository
    {
        IRecordGenre Get(IRecord record, IGenre genre);

        IEnumerable<IRecordGenre> Get();

        IRecordGenre Create(IRecord record, IGenre genre);

        void Delete(IRecordGenre recordGenre);
    }
}
