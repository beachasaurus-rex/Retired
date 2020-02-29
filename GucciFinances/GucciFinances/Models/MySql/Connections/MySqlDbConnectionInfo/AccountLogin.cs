using GucciFinances.Properties;

namespace GucciFinances.Models.MySql.Connections.MySqlDbConnectionInfo
{
    public class AccountLogin
    {
        #region Readonly Properties

        public string Username { get; }
        public string Password { get; }

        #endregion Readonly Properties

        #region Constructors

        /// <summary>
        /// Creates an AccountLogin object with the default settings.
        /// </summary>
        public AccountLogin()
        {
            Username = DatabaseSettings.Default.AccountUsername;
            Password = DatabaseSettings.Default.AccountPassword;
        }

        #endregion Constructors
    }
}
