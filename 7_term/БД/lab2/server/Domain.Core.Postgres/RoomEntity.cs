using Domain.Interfaces.Entity;
using System.ComponentModel.DataAnnotations.Schema;

namespace Domain.Core.Postgres
{
    [Table("room")]
    public class RoomEntity : IRoom
    {
        [Column("id")]
        public int Id { get; set; }

        [Column("number")]
        public string Number { get; set; }

        [Column("square")]
        public int Square { get; set; }

        [Column("rent")]
        public decimal Rent { get; set; }

        [Column("personsCount")]
        public int PersonsCount { get; set; }
    }
}
