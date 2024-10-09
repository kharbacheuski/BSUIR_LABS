using System.Text.Json.Serialization;

namespace App.Models.Genre
{
    public class GenreModel
    {
        [JsonPropertyName("name")]
        public string Name { get; set; }

        [JsonPropertyName("instruments")]
        public string Instruments { get; set; }
    }
}
