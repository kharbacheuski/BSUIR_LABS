using Domain.Interfaces.Entity;
using System.ComponentModel.DataAnnotations.Schema;

namespace Domain.Core.Postgres
{
    [Table("record_genre")]
    public class RecordGenreEntity : IRecordGenre
    {
        [Column("id")]
        public int Id { get; set; }

        #region [ Group ]

        [Column("recordId")]
        public int RecordId { get; set; }

        [ForeignKey("RecordId")]
        public RecordEntity RecordEntity { get; set; }

        [NotMapped]
        public IRecord Record { get => RecordEntity; set => RecordEntity = (RecordEntity)value; }

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
