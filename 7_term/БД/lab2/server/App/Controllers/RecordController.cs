using App.ModelBuilders;
using App.Models.Record;
using Domain.Interfaces.Repository;
using Microsoft.AspNetCore.Mvc;

namespace App.Controllers
{
    [ApiController]
    [Route("record")]
    public class RecordController : ControllerBase
    {
        private readonly IRoomRepository _roomRepository;
        private readonly IGroupRepository _groupRepository;
        private readonly IRecordRepository _recordRepository;

        public RecordController(IRoomRepository roomRepository, IGroupRepository groupRepository, IRecordRepository recordRepository)
        {
            _roomRepository = roomRepository;
            _groupRepository = groupRepository;
            _recordRepository = recordRepository;
        }

        [HttpGet]
        public IEnumerable<RecordModel> Get()
        {
            return _recordRepository.Get().Select(RecordModelBuilder.Build);
        }

        [HttpPost]
        public RecordModel Create(RecordModel model)
        {
            var room = _roomRepository.Get(model.RoomNumber);
            var group = _groupRepository.Get(model.GroupName);

            var record = _recordRepository.Create(model.Number, model.Date, model.Hours, room, group);

            return RecordModelBuilder.Build(record);
        }

        [HttpDelete]
        public HttpResponseMessage Delete(RecordDeleteModel model)
        {
            var record = _recordRepository.Get(model.Number);

            _recordRepository.Delete(record);

            return new HttpResponseMessage(System.Net.HttpStatusCode.OK);
        }
    }
}
