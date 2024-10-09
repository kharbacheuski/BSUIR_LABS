using App.ModelBuilders;
using App.Models.GroupGenre;
using Domain.Interfaces.Repository;
using Microsoft.AspNetCore.Mvc;

namespace App.Controllers
{
    [ApiController]
    [Route("record/genre")]
    public class RecordGenreController : ControllerBase
    {
        private readonly IRecordRepository _recordRepository;
        private readonly IGenreRepository _genreRepository;
        private readonly IRecordGenreRepository _recordGenreRepository;

        public RecordGenreController(IRecordRepository recordRepository, IGenreRepository genreRepository, IRecordGenreRepository recordGenreRepository)
        {
            _recordRepository = recordRepository;
            _genreRepository = genreRepository;
            _recordGenreRepository = recordGenreRepository;
        }

        [HttpGet]
        public IEnumerable<RecordGenreModel> Get()
        {
            return _recordGenreRepository.Get().Select(RecordGenreModelBuilder.Build);
        }

        [HttpPost]
        public RecordGenreModel Create(RecordGenreModel model)
        {
            var record = _recordRepository.Get(model.RecordNumber);
            var genre = _genreRepository.Get(model.GenreName);

            var recordGenre = _recordGenreRepository.Create(record, genre);

            return RecordGenreModelBuilder.Build(recordGenre);
        }

        [HttpDelete]
        public HttpResponseMessage Delete(RecordGenreModel model)
        {
            var record = _recordRepository.Get(model.RecordNumber);
            var genre = _genreRepository.Get(model.GenreName);

            var recordGenre = _recordGenreRepository.Get(record, genre);

            _recordGenreRepository.Delete(recordGenre);

            return new HttpResponseMessage(System.Net.HttpStatusCode.OK);
        }
    }
}
