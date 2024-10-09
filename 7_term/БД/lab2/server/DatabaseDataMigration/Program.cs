using BerkeleyDB;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;

namespace DatabaseDataMigration
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var builder = new ConfigurationBuilder().SetBasePath(Directory.GetCurrentDirectory()).AddJsonFile("appsettings.json", optional: false).AddEnvironmentVariables();
            IConfiguration configuration = builder.Build();

            var berkeleyDbPath = configuration.GetConnectionString("Berkeley");
            var postgresConnectionString = configuration.GetConnectionString("Postgres");

            var database = Database.Open(berkeleyDbPath, new BTreeDatabaseConfig
            {
                Creation = CreatePolicy.IF_NEEDED,
                CacheSize = new CacheInfo(0, 64 * 1024, 1),
                PageSize = 8 * 1024
            });

            var optionsBuilder = new DbContextOptionsBuilder<Insfrastructure.Data.Postgres.AppDbContext>();
            optionsBuilder.UseNpgsql(postgresConnectionString);
            var dbContext = new Insfrastructure.Data.Postgres.AppDbContext(optionsBuilder.Options);

            var pgenreRepository = new Insfrastructure.Data.Postgres.GenreRepository(dbContext);
            var pgroupGenreRepository = new Insfrastructure.Data.Postgres.GroupGenreRepository(dbContext);
            var pgroupRepository = new Insfrastructure.Data.Postgres.GroupRepository(dbContext);
            var precordGenreRepository = new Insfrastructure.Data.Postgres.RecordGenreRepository(dbContext);
            var precordRepository = new Insfrastructure.Data.Postgres.RecordRepository(dbContext);
            var proomRepository = new Insfrastructure.Data.Postgres.RoomRepository(dbContext);

            var bgenreRepository = new Insfrastructure.Data.Berkeley.GenreRepository(database);
            var bgroupGenreRepository = new Insfrastructure.Data.Berkeley.GroupGenreRepository(database);
            var bgroupRepository = new Insfrastructure.Data.Berkeley.GroupRepository(database);
            var brecordGenreRepository = new Insfrastructure.Data.Berkeley.RecordGenreRepository(database);
            var brecordRepository = new Insfrastructure.Data.Berkeley.RecordRepository(database);
            var broomRepository = new Insfrastructure.Data.Berkeley.RoomRepository(database);

            var genres = pgenreRepository.Get();
            foreach (var g in genres)
                bgenreRepository.Create(g.Name, g.Instruments);

            var groupGenres = pgroupGenreRepository.Get();
            foreach (var gg in groupGenres)
            {
                var group = bgroupRepository.Get(gg.Group.Name);
                var genre = bgenreRepository.Get(gg.Genre.Name);

                bgroupGenreRepository.Create(group, genre);
            }

            var groups = pgroupRepository.Get();
            foreach (var g in groups)
                bgroupRepository.Create(g.Name, g.PersonsCount, g.Popularity);

            var recordGenres = precordGenreRepository.Get();
            foreach (var rg in recordGenres)
            {
                var record = brecordRepository.Get(rg.Record.Number);
                var genre = bgenreRepository.Get(rg.Genre.Name);

                brecordGenreRepository.Create(record, genre);
            }

            var records = precordRepository.Get();
            foreach(var r in records)
            {
                var room = broomRepository.Get(r.Room.Number);
                var group = bgroupRepository.Get(r.Group.Name);

                brecordRepository.Create(r.Number, r.Date, r.Hours, room, group);
            }

            var rooms = proomRepository.Get();
            foreach (var r in rooms)
                broomRepository.Create(r.Number, r.Square, r.PersonsCount, r.Rent);

            database.Dispose();
            dbContext.Dispose();
        }
    }
}
