using Domain.Interfaces.Entity;
using System.Text.Json.Serialization;

namespace Domain.Core.Berkeley
{
    public class RecordGenreEntity : IRecordGenre
    {
        [JsonPropertyName("record")]
        public RecordEntity RecordEntity { get; set; }

        [JsonPropertyName("genre")]
        public GenreEntity GenreEntity { get; set; }

        [JsonIgnore]
        public IRecord Record { get => RecordEntity; set => RecordEntity = (RecordEntity)value; }

        [JsonIgnore]
        public IGenre Genre { get => GenreEntity; set => GenreEntity = (GenreEntity)value; }
    }
}
