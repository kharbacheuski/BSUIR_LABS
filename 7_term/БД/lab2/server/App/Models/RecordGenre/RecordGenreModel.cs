using System.Text.Json.Serialization;

namespace App.Models.GroupGenre
{
    public class RecordGenreModel
    {
        [JsonPropertyName("recordNumber")]
        public string RecordNumber { get; set; }

        [JsonPropertyName("genreName")]
        public string GenreName { get; set; }
    }
}
