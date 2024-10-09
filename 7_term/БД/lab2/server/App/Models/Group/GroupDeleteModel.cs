using System.Text.Json.Serialization;

namespace App.Models.Group
{
    public class GroupDeleteModel
    {
        [JsonPropertyName("name")]
        public string Name { get; set; }
    }
}
