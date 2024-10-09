using App.ModelBuilders;
using App.Models.Room;
using Domain.Interfaces.Repository;
using Microsoft.AspNetCore.Mvc;

namespace App.Controllers
{
    [ApiController]
    [Route("room")]
    public class RoomController : ControllerBase
    {
        private readonly IRoomRepository _roomRepository;

        public RoomController(IRoomRepository roomRepository)
        {
            _roomRepository = roomRepository;
        }

        [HttpGet]
        public IEnumerable<RoomModel> Get()
        {
            return _roomRepository.Get().Select(RoomModelBuilder.Build);
        }

        [HttpPost]
        public RoomModel Create(RoomModel model)
        {
            var room = _roomRepository.Create(model.Number, model.Square, model.PersonsCount, model.Rent);

            return RoomModelBuilder.Build(room);
        }

        [HttpDelete]
        public HttpResponseMessage Delete(RoomDeleteModel model)
        {
            var room = _roomRepository.Get(model.Number);

            _roomRepository.Delete(room);

            return new HttpResponseMessage(System.Net.HttpStatusCode.OK);
        }
    }
}
