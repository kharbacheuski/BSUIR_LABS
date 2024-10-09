using System.Text.Json.Serialization;

namespace App.Models.Room
{
    public class RoomModel
    {
        [JsonPropertyName("number")]
        public string Number { get; set; }

        [JsonPropertyName("square")]
        public int Square { get; set; }

        [JsonPropertyName("personsCount")]
        public int PersonsCount { get; set; }

        [JsonPropertyName("rent")]
        public decimal Rent { get; set; }
    }
}
