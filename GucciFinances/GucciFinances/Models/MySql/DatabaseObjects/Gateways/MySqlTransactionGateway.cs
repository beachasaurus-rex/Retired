using System;
using GucciFinances.Models.Connections;
using GucciFinances.Models.DatabaseObjects.Records;
using GucciFinances.Models.DatabaseObjects.Gateways;
using MySql.Data.MySqlClient;

namespace GucciFinances.Models.MySql.DatabaseObjects.Gateways
{
    public class MySqlTransactionGateway : Gateway
    {
        #region Constructors

        public MySqlTransactionGateway() : base()
        {
        }

        #endregion Constructors

        #region Methods

        public override void Post(TransactionRecord rec)
        {
            string sqlString = BuildPostSQLStatement(rec);

            //if the connection fails for whatever reason during the post, then i don't want
            //the app to crash
            try
            {
                //i dont want these objects just lying around on the stack
                using (MySqlDbConnection dbCon = new MySqlDbConnection())
                using (MySqlCommand cmd = new MySqlCommand(sqlString))
                {
                    cmd.Connection = dbCon.Connection;
                    cmd.Connection.Open();
                    cmd.ExecuteNonQuery();

                    string msg = String.Format($"Post success.");
                    Console.WriteLine(msg);
                }
            }
            catch (Exception ex)
            {
                string _err = String.Format($"Post failed: {ex.ToString()}");
                Console.WriteLine(_err);
            }
        }

        #endregion Methods

        #region SQL Commands

        //this adds a record to the transactions table
        protected override string BuildPostSQLStatement(TransactionRecord transRec)
        {
            string sqlPostStatement = string.Format("INSERT INTO finances.transactions (Merchant, Amount, IsWork, TransactionDate, " +
                                                    "PaymentMethod, CardName, IsSubscription, DocumentFolderPath, Comment)\n" +
                                                    "VALUES ('{0}', {1}, {2}, STR_TO_DATE('{3}', '%m/%d/%Y'), '{4}', '{5}', {6}, '{7}', '{8}');",
                                                    transRec.Merchant,
                                                    transRec.Amount,
                                                    transRec.IsWork,
                                                    transRec.TransactionDate.ToString("MM/dd/yyyy"),
                                                    transRec.MethodOfPayment.ToString(),
                                                    transRec.CardName,
                                                    transRec.IsSubscription,
                                                    transRec.DocumentFolderPath,
                                                    transRec.Comment
                                                    );

            return sqlPostStatement;
        }

        #endregion SQL Commands
    }
}
