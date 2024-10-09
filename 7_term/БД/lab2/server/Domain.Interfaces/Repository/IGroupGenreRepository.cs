using Domain.Interfaces.Entity;

namespace Domain.Interfaces.Repository
{
    public interface IGroupGenreRepository
    {
        IGroupGenre Get(IGroup group, IGenre genre);

        IEnumerable<IGroupGenre> Get();

        IGroupGenre Create(IGroup group, IGenre genre);

        void Delete(IGroupGenre groupGenre);
    }
}
