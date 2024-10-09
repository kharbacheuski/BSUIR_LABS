namespace Domain.Interfaces.Entity
{
    public interface IGroupGenre
    {
        IGroup Group { get; set; }

        IGenre Genre { get; set; }
    }
}
