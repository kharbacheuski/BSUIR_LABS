using Domain.Interfaces.Entity;
using System.ComponentModel.DataAnnotations.Schema;

namespace Domain.Core.Postgres
{
    [Table("group")]
    public class GroupEntity : IGroup
    {
        [Column("id")]
        public int Id { get; set; }

        [Column("name")]
        public string Name { get; set; }

        [Column("personsCount")]
        public int PersonsCount { get; set; }

        [Column("popularity")]
        public int Popularity { get; set; }
    }
}
