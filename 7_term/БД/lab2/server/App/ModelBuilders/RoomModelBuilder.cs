using App.Models.Room;
using Domain.Interfaces.Entity;

namespace App.ModelBuilders
{
    public class RoomModelBuilder
    {
        public static RoomModel Build(IRoom room)
        {
            return new RoomModel
            {
                Number = room.Number,
                Square = room.Square,
                PersonsCount = room.PersonsCount,
                Rent = room.Rent
            };
        }
    }
}
