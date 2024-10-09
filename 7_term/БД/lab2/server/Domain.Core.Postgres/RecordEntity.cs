using Domain.Interfaces.Entity;
using System.ComponentModel.DataAnnotations.Schema;

namespace Domain.Core.Postgres
{
    [Table("record")]
    public class RecordEntity : IRecord
    {
        [Column("id")]
        public int Id { get; set; }

        [Column("number")]
        public string Number { get; set; }

        [Column("date")]
        public DateTime Date { get; set; }

        [Column("hours")]
        public int Hours { get; set; }

        #region [ Room ] 

        [Column("roomId")]
        public int RoomId { get; set; }

        [ForeignKey("RoomId")]
        public RoomEntity RoomEntity { get; set; }

        [NotMapped]
        public IRoom Room { get => RoomEntity; set => RoomEntity = (RoomEntity)value; }

        #endregion

        #region [ Group ]

        [Column("groupId")]
        public int GroupId { get; set; }

        [ForeignKey("GroupId")]
        public GroupEntity GroupEntity { get; set; }

        [NotMapped]
        public IGroup Group { get => GroupEntity; set => GroupEntity = (GroupEntity)value; }

        #endregion
    }
}
