using App.ModelBuilders;
using App.Models.Group;
using Domain.Interfaces.Repository;
using Microsoft.AspNetCore.Mvc;

namespace App.Controllers
{
    [ApiController]
    [Route("group")]
    public class GroupController : ControllerBase
    {
        private readonly IGroupRepository _groupRepository;

        public GroupController(IGroupRepository groupRepository)
        {
            _groupRepository = groupRepository;
        }

        [HttpGet]
        public IEnumerable<GroupModel> Get()
        {
            return _groupRepository.Get().Select(GroupModelBuilder.Build);
        }

        [HttpPost]
        public GroupModel Create(GroupModel model)
        {
            var group = _groupRepository.Create(model.Name, model.PersonsCount, model.Popularity);

            return GroupModelBuilder.Build(group);
        }

        [HttpDelete]
        public HttpResponseMessage Delete(GroupDeleteModel model)
        {
            var group = _groupRepository.Get(model.Name);

            _groupRepository.Delete(group);

            return new HttpResponseMessage(System.Net.HttpStatusCode.OK);
        }
    }
}
