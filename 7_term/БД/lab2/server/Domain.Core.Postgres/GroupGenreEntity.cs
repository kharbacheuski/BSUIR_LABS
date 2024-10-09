using Domain.Interfaces.Entity;
using System.ComponentModel.DataAnnotations.Schema;

namespace Domain.Core.Postgres
{
    [Table("group_genre")]
    public class GroupGenreEntity : IGroupGenre
    {
        [Column("id")]
        public int Id { get; set; }

        #region [ Group ]

        [Column("groupId")]
        public int GroupId { get; set; }

        [ForeignKey("GroupId")]
        public GroupEntity GroupEntity { get; set; }

        [NotMapped]
        public IGroup Group { get => GroupEntity; set => GroupEntity = (GroupEntity)value; }

        #endregion

        #region [ Genre ]

        [Column("genreId")]
        public int GenreId { get; set; }

        [ForeignKey("GenreId")]
        public GenreEntity GenreEntity { get; set; }

        [NotMapped]
        public IGenre Genre { get => GenreEntity; set => GenreEntity = (GenreEntity)value; }

        #endregion
    }
}
