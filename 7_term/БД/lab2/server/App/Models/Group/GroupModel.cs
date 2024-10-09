using System.Text.Json.Serialization;

namespace App.Models.Group
{
    public class GroupModel
    {
        [JsonPropertyName("name")]
        public string Name { get; set; }

        [JsonPropertyName("personsCount")]
        public int PersonsCount { get; set; }

        [JsonPropertyName("popularity")]
        public int Popularity { get; set; }
    }
}
