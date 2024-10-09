using App.Models.Group;
using Domain.Interfaces.Entity;

namespace App.ModelBuilders
{
    public class GroupModelBuilder
    {
        public static GroupModel Build(IGroup group)
        {
            return new GroupModel
            {
                Name = group.Name,
                PersonsCount = group.PersonsCount,
                Popularity = group.Popularity
            };
        }
    }
}
