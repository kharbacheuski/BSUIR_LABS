namespace Domain.Interfaces.Entity
{
    public interface IGroup
    {
        string Name { get; set; }

        int PersonsCount { get; set; }

        int Popularity { get; set; }
    }
}
