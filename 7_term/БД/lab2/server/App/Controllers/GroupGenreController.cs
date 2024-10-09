using App.ModelBuilders;
using App.Models.GroupGenre;
using Domain.Interfaces.Repository;
using Microsoft.AspNetCore.Mvc;

namespace App.Controllers
{
    [ApiController]
    [Route("group/genre")]
    public class GroupGenreController : ControllerBase
    {
        private readonly IGenreRepository _genreRepository;
        private readonly IGroupRepository _groupRepository;
        private readonly IGroupGenreRepository _groupGenreRepository;

        public GroupGenreController(IGroupRepository groupRepository, IGenreRepository genreRepository, IGroupGenreRepository groupGenreRepository)
        {
            _groupRepository = groupRepository;
            _genreRepository = genreRepository;
            _groupGenreRepository = groupGenreRepository;
        }

        [HttpGet]
        public IEnumerable<GroupGenreModel> Get()
        {
            return _groupGenreRepository.Get().Select(GroupGenreModelBuilder.Build);
        }

        [HttpPost]
        public GroupGenreModel Create(GroupGenreModel model)
        {
            var group = _groupRepository.Get(model.GroupName);
            var genre = _genreRepository.Get(model.GenreName);

            var groupGenre = _groupGenreRepository.Create(group, genre);

            return GroupGenreModelBuilder.Build(groupGenre);
        }

        [HttpDelete]
        public HttpResponseMessage Delete(GroupGenreModel model)
        {
            var group = _groupRepository.Get(model.GroupName);
            var genre = _genreRepository.Get(model.GenreName);

            var groupGenre = _groupGenreRepository.Get(group, genre);

            _groupGenreRepository.Delete(groupGenre);

            return new HttpResponseMessage(System.Net.HttpStatusCode.OK);
        }
    }
}
