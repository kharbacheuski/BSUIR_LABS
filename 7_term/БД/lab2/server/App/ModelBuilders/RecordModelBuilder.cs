using App.Models.Record;
using Domain.Interfaces.Entity;

namespace App.ModelBuilders
{
    public class RecordModelBuilder
    {
        public static RecordModel Build(IRecord record)
        {
            return new RecordModel
            {
                Number = record.Number,
                Date = record.Date,
                Hours = record.Hours,
                RoomNumber = record.Room.Number,
                GroupName = record.Group.Name
            };
        }
    }
}
