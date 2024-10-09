namespace Domain.Interfaces.Entity
{
    public interface IRecordGenre
    {
        IRecord Record { get; set; }

        IGenre Genre { get; set; }
    }
}
