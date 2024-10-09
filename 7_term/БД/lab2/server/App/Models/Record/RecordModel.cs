using System.Text.Json.Serialization;

namespace App.Models.Record
{
    public class RecordModel
    {
        [JsonPropertyName("number")]
        public string Number { get; set; }

        [JsonPropertyName("date")]
        public DateTime Date { get; set; }

        [JsonPropertyName("hours")]
        public int Hours { get; set; }

        [JsonPropertyName("roomNumber")]
        public string RoomNumber { get; set; }

        [JsonPropertyName("groupName")]
        public string GroupName { get; set; }
    }
}
