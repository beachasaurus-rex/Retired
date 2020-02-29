using MySql.Data.MySqlClient;
using System;
using GucciFinances.Models.MySql.Connections.MySqlDbConnectionInfo;

namespace GucciFinances.Models.Connections
{
    public class MySqlDbConnection : Connection
    {
        #region Fields

        private MySqlConnection _connection;
        private readonly AccountLogin _accountCredentials;
        private readonly DatabaseLogin _databaseCredentials;
        private readonly string _conInfo;
        private bool _canConnect;

        #endregion Fields

        #region Properties

        public AccountLogin AccountCredentials { get { return _accountCredentials; } }
        public DatabaseLogin DatabaseCredentials { get { return _databaseCredentials; } }
        public MySqlConnection Connection { get { return _connection; } }
        public override bool CanConnect { get { return _canConnect; } }

        #endregion Properties

        #region Constructors

        /// <summary>
        /// Gets the connection information needed to establish a connection to a MySQL database.
        /// </summary>
        public MySqlDbConnection()
        {
            //These objects will get the settings that are in
            //DatabaseSettings.Settings during construction
            _accountCredentials = new AccountLogin();
            _databaseCredentials = new DatabaseLogin();

            MySqlConnectionStringBuilder _connectionInformation = new MySqlConnectionStringBuilder();
            _connectionInformation.Server = DatabaseCredentials.Server;
            _connectionInformation.UserID = AccountCredentials.Username;
            _connectionInformation.Password = AccountCredentials.Password;
            _connectionInformation.Database = DatabaseCredentials.DatabaseName;
            _connectionInformation.Port = uint.Parse(DatabaseCredentials.Port);

            _conInfo = _connectionInformation.ToString();

            MySqlConnection testCon = new MySqlConnection(_conInfo);
            _canConnect = TryConnection(testCon);
        }

        #endregion Constructors

        #region Exposed Connection Members

        /// <summary>
        /// Establishes a connection to a MySQL database using the DatabaseSettings.settings file.
        /// </summary>
        public override void Connect()
        {
            if (((MySqlDbConnection)this).IsConnected())
            {
                return;
            }

            if (_canConnect)
            {
                _connection.Open();
            }
        }
        /// <summary>
        /// Determines if there is a database connection.
        /// </summary>
        /// <returns></returns>
        public override bool IsConnected()
        {
            if (_connection != null)
            {
                return true;
            }

            return false;
        }
        public override void Close()
        {
            if (((MySqlDbConnection)this).IsConnected())
            {
                _connection.Close();
                Console.WriteLine("Disconnected from {0}.", DatabaseCredentials.DatabaseName);
            }
        }
        public override void Dispose()
        {
            ((MySqlConnection)_connection)?.Dispose();
        }

        #endregion Exposed Connection Members

        #region Private Helpers

        private bool TryConnection(MySqlConnection dbConnection)
        {
            bool pass = true;
            if (((MySqlDbConnection)this).IsConnected())
            {
                Console.WriteLine(String.Format($"Already connected to {DatabaseCredentials.DatabaseName}."));
                return pass;
            }

            try
            {
                Console.WriteLine(String.Format($"Connecting to {DatabaseCredentials.DatabaseName}..."));
                dbConnection.Open();
                Console.WriteLine(String.Format($"Connection to {DatabaseCredentials.DatabaseName} established."));
                _connection = new MySqlConnection(_conInfo);
                Console.WriteLine("Disconnected from {0}.", DatabaseCredentials.DatabaseName);
            }
            catch (Exception ex)
            {
                string _err = String.Format($"Exception: {ex.ToString()}");
                Console.WriteLine(_err);
                pass = false;
                Console.WriteLine("Disconnected from {0}.", DatabaseCredentials.DatabaseName);
            }
            finally
            {
                dbConnection.Close();
            }
            return pass;

        }

        #endregion Private helpers
    }
}
