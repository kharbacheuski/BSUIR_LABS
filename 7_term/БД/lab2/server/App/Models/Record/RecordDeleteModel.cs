using System.Text.Json.Serialization;

namespace App.Models.Record
{
    public class RecordDeleteModel
    {
        [JsonPropertyName("number")]
        public string Number { get; set; }
    }
}
