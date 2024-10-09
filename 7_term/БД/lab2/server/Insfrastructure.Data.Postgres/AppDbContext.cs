using Domain.Core.Postgres;
using Microsoft.EntityFrameworkCore;

namespace Insfrastructure.Data.Postgres
{
    public class AppDbContext : DbContext
    {
        public DbSet<GenreEntity> Genre { get; set; }
        public DbSet<GroupEntity> Group  { get; set; }
        public DbSet<GroupGenreEntity> GroupGenre { get; set; }
        public DbSet<RecordEntity> Record { get; set; }
        public DbSet<RecordGenreEntity> RecordGenre { get; set; }
        public DbSet<RoomEntity> Room { get; set; }

        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
        {

        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            modelBuilder.Entity<RecordEntity>()
                .HasOne(p => p.RoomEntity);

            modelBuilder.Entity<RecordEntity>()
               .HasOne(p => p.GroupEntity);

            modelBuilder.Entity<GroupGenreEntity>()
                .HasOne(p => p.GroupEntity);

            modelBuilder.Entity<GroupGenreEntity>()
               .HasOne(p => p.GenreEntity);

            modelBuilder.Entity<RecordGenreEntity>()
               .HasOne(p => p.RecordEntity);

            modelBuilder.Entity<RecordGenreEntity>()
               .HasOne(p => p.GenreEntity);
        }
    }
}
