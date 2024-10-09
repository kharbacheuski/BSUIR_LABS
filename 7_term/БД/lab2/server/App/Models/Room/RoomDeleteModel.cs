using System.Text.Json.Serialization;

namespace App.Models.Room
{
    public class RoomDeleteModel
    {
        [JsonPropertyName("number")]
        public string Number { get; set; }
    }
}
