using System.Text.Json.Serialization;

namespace App.Models.GroupGenre
{
    public class GroupGenreModel
    {
        [JsonPropertyName("groupName")]
        public string GroupName { get; set; }

        [JsonPropertyName("genreName")]
        public string GenreName { get; set; }
    }
}
