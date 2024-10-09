using BerkeleyDB;
using Domain.Interfaces.Repository;
using Microsoft.EntityFrameworkCore;

namespace App
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);

            builder.Services.AddControllers();
            builder.Services.AddEndpointsApiExplorer();
            builder.Services.AddSwaggerGen();

            var connectionString = builder.Configuration.GetConnectionString("App");
            UsePostgres(builder.Services, connectionString);

            var app = builder.Build();

            app.UseSwagger();
            app.UseSwaggerUI();

            app.UseCors(builder => builder.AllowAnyOrigin().AllowAnyHeader().AllowAnyMethod().SetPreflightMaxAge(TimeSpan.MaxValue));

            app.UseAuthorization();

            app.MapControllers();

            app.Run();
        }

        public static void UseBerkley(IServiceCollection services, string connectionString)
        {
            var databaseConfig = new BTreeDatabaseConfig
            {
                Creation = CreatePolicy.IF_NEEDED,
                CacheSize = new CacheInfo(0, 64 * 1024, 1),
                PageSize = 8 * 1024
            };

            var database = Database.Open(connectionString, databaseConfig);

            services.AddSingleton(database);
            services.AddSingleton<IGenreRepository, Insfrastructure.Data.Berkeley.GenreRepository>();
            services.AddSingleton<IGroupRepository, Insfrastructure.Data.Berkeley.GroupRepository>();
            services.AddSingleton<IRecordRepository, Insfrastructure.Data.Berkeley.RecordRepository>();
            services.AddSingleton<IRoomRepository, Insfrastructure.Data.Berkeley.RoomRepository>();
            services.AddSingleton<IRecordGenreRepository, Insfrastructure.Data.Berkeley.RecordGenreRepository>();
            services.AddSingleton<IGroupGenreRepository, Insfrastructure.Data.Berkeley.GroupGenreRepository>();
        }

        public static void UsePostgres(IServiceCollection services, string connectionString)
        {
            services.AddDbContext<Insfrastructure.Data.Postgres.AppDbContext>(options =>
            {
                options.UseNpgsql(connectionString);
            });

            services.AddScoped<IGenreRepository, Insfrastructure.Data.Postgres.GenreRepository>();
            services.AddScoped<IGroupRepository, Insfrastructure.Data.Postgres.GroupRepository>();
            services.AddScoped<IRecordRepository, Insfrastructure.Data.Postgres.RecordRepository>();
            services.AddScoped<IRoomRepository, Insfrastructure.Data.Postgres.RoomRepository>();
            services.AddScoped<IRecordGenreRepository, Insfrastructure.Data.Postgres.RecordGenreRepository>();
            services.AddScoped<IGroupGenreRepository, Insfrastructure.Data.Postgres.GroupGenreRepository>();
        }
    }
}
