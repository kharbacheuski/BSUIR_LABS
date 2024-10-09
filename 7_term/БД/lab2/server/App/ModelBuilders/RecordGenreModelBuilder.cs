using App.Models.GroupGenre;
using Domain.Interfaces.Entity;

namespace App.ModelBuilders
{
    public class RecordGenreModelBuilder
    {
        public static RecordGenreModel Build(IRecordGenre recordGenre)
        {
            return new RecordGenreModel
            {
                RecordNumber = recordGenre.Record.Number,
                GenreName = recordGenre.Genre.Name
            };
        }
    }
}
