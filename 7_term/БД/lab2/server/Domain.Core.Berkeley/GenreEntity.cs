using Domain.Interfaces.Entity;
using System.Text.Json.Serialization;

namespace Domain.Core.Berkeley
{
    public class GenreEntity : IGenre
    {
        [JsonPropertyName("name")]
        public string Name { get; set; }

        [JsonPropertyName("instruments")]
        public string Instruments { get; set; }
    }
}
