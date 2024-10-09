namespace Domain.Interfaces.Entity
{
    public interface IRecord
    {
        string Number { get; set; }

        DateTime Date { get; set; }

        int Hours { get; set; }

        IRoom Room { get; set; }

        IGroup Group { get; set; }
    }
}
