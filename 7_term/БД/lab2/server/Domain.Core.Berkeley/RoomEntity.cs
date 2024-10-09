using Domain.Interfaces.Entity;
using System.Text.Json.Serialization;

namespace Domain.Core.Berkeley
{
    public class RoomEntity : IRoom
    {
        [JsonPropertyName("number")]
        public string Number { get; set; }

        [JsonPropertyName("square")]
        public int Square { get; set; }

        [JsonPropertyName("rent")]
        public decimal Rent { get; set; }

        [JsonPropertyName("persons_count")]
        public int PersonsCount { get; set; }
    }
}
