using GucciFinances.Properties;

namespace GucciFinances.Models.MySql.Connections.MySqlDbConnectionInfo
{
    public class DatabaseLogin
    {
        #region Readonly Properties

        public string DatabaseName { get; }
        public string Server { get; }
        public string Port { get; }

        #endregion Readonly Properties

        #region Constructors

        /// <summary>
        /// Creates a DatabaseLogin object with the default settings.
        /// </summary>
        public DatabaseLogin()
        {
            DatabaseName = DatabaseSettings.Default.DatabaseName;
            Server = DatabaseSettings.Default.Server;
            Port = DatabaseSettings.Default.Port;
        }

        #endregion Constructors
    }
}
