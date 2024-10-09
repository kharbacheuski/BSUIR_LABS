using App.ModelBuilders;
using App.Models.Genre;
using Domain.Interfaces.Repository;
using Microsoft.AspNetCore.Mvc;

namespace App.Controllers
{
    [ApiController]
    [Route("genre")]
    public class GenreController : ControllerBase
    {
        private readonly IGenreRepository _genreRepository;

        public GenreController(IGenreRepository genreRepository)
        {
            _genreRepository = genreRepository;
        }

        [HttpGet]
        public IEnumerable<GenreModel> Get()
        {
            return _genreRepository.Get().Select(GenreModelBuilder.Build);
        }

        [HttpPost]
        public GenreModel Create(GenreModel model)
        {
            var genre = _genreRepository.Create(model.Name, model.Instruments);

            return GenreModelBuilder.Build(genre);
        }

        [HttpDelete]
        public HttpResponseMessage Delete(GenreDeleteModel model)
        {
            var genre = _genreRepository.Get(model.Name);

            _genreRepository.Delete(genre);

            return new HttpResponseMessage(System.Net.HttpStatusCode.OK);
        }
    }
}
