using Domain.Interfaces.Entity;
using System.Text.Json.Serialization;

namespace Domain.Core.Berkeley
{
    public class RecordEntity : IRecord
    {
        [JsonPropertyName("number")]
        public string Number { get; set; }

        [JsonPropertyName("date")]
        public DateTime Date { get; set; }

        [JsonPropertyName("hours")]
        public int Hours { get; set; }

        [JsonPropertyName("room")]
        public RoomEntity RoomEntity { get; set; }

        [JsonPropertyName("group")]
        public GroupEntity GroupEntity { get; set; }

        [JsonIgnore]
        public IRoom Room { get => RoomEntity; set => RoomEntity = (RoomEntity)value; }

        [JsonIgnore]
        public IGroup Group { get => GroupEntity; set => GroupEntity = (GroupEntity)value; }
    }
}
