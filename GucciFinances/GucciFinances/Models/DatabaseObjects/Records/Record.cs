namespace GucciFinances.Models.DatabaseObjects.Records
{
    public abstract class Record
    {
        #region Fields

        //all records must have a unique identifier associated with their tables
        public int? _id;

        #endregion Fields

        #region Properties

        //all records need a way to expose the unique identifier
        public abstract int? ID { get; }

        #endregion Properties
    }
}
