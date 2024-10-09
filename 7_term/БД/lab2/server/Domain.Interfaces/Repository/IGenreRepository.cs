using Domain.Interfaces.Entity;

namespace Domain.Interfaces.Repository
{
    public interface IGenreRepository
    {
        IGenre Get(string name);

        IEnumerable<IGenre> Get();

        IGenre Create(string name, string instruments);

        void Delete(IGenre genre);
    }
}
