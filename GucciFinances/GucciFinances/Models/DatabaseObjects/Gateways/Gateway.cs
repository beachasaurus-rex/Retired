using GucciFinances.Models.DatabaseObjects.Records;

namespace GucciFinances.Models.DatabaseObjects.Gateways
{
    //i'll be using its children to communicate between the database and the UI
    public abstract class Gateway
    {
        //constructor
        protected Gateway()
        {
        }

        //exposed methods
        public abstract void Post(TransactionRecord rec);

        //protected methods
        protected abstract string BuildPostSQLStatement(TransactionRecord rec);
    }
}
