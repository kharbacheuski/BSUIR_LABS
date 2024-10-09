using App.Models.GroupGenre;
using Domain.Interfaces.Entity;

namespace App.ModelBuilders
{
    public class GroupGenreModelBuilder
    {
        public static GroupGenreModel Build(IGroupGenre groupGenre)
        {
            return new GroupGenreModel
            {
                GroupName = groupGenre.Group.Name,
                GenreName = groupGenre.Genre.Name
            };
        }
    }
}
