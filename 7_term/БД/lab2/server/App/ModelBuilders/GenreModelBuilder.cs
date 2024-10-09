using App.Models.Genre;
using Domain.Interfaces.Entity;

namespace App.ModelBuilders
{
    public class GenreModelBuilder
    {
        public static GenreModel Build(IGenre genre)
        {
            return new GenreModel
            {
                Name = genre.Name,
                Instruments = genre.Instruments
            };
        }
    }
}
