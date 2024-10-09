namespace Domain.Interfaces.Entity
{
    public interface IRoom
    {
        string Number { get; set; }

        int Square { get; set; }

        decimal Rent { get; set; }

        int PersonsCount { get; set; }
    }
}
