using Domain.Interfaces.Entity;
using System.Text.Json.Serialization;

namespace Domain.Core.Berkeley
{
    public class GroupGenreEntity : IGroupGenre
    {
        [JsonPropertyName("group")]
        public GroupEntity GroupEntity { get; set; }

        [JsonPropertyName("genre")]
        public GenreEntity GenreEntity { get; set; }

        [JsonIgnore]
        public IGroup Group { get => GroupEntity; set => GroupEntity = (GroupEntity)value; }

        [JsonIgnore]
        public IGenre Genre { get => GenreEntity; set => GenreEntity = (GenreEntity)value; }
    }
}
