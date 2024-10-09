using Domain.Interfaces.Entity;
using System.Text.Json.Serialization;

namespace Domain.Core.Berkeley
{
    public class GroupEntity : IGroup
    {
        [JsonPropertyName("name")]
        public string Name { get; set; }

        [JsonPropertyName("persons_count")]
        public int PersonsCount { get; set; }

        [JsonPropertyName("popularity")]
        public int Popularity { get; set; }
    }
}
