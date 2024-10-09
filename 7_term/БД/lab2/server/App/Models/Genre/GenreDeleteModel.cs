using System.Text.Json.Serialization;

namespace App.Models.Genre
{
    public class GenreDeleteModel
    {
        [JsonPropertyName("name")]
        public string Name { get; set; }
    }
}
