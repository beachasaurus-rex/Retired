using System.Windows.Input;
using GucciFinances.Models.Commands;
using GucciFinances.Models.MySql.SubSettingControllers;
using GucciFinances.Properties;
using GucciFinances.Views;

namespace GucciFinances.Models.Controllers
{
    //Use this to expose controller methods for subsettings
    public class SettingsController
    {
        #region Fields

        private SettingsPage _set;

        //DBSettingsController Fields
        private MySqlDBSettingsController _mySqlDbConCont;
        private ICommand _saveDbSettings;
        private ICommand _testDbCon;

        #endregion Fields

        #region Properties
        
        //DBSettingsController Properties
        public ICommand SaveDBSettings
        {
            get
            {
                if (_saveDbSettings == null)
                {
                    _saveDbSettings = new RelayCommand(
                        param => SaveAllDBSettings()
                        );
                }
                return _saveDbSettings;
            }
        }
        public ICommand TestDBConnection
        {
            get
            {
                if (_testDbCon == null)
                {
                    _testDbCon = new RelayCommand(
                        param => DBTestConnection()
                        );
                }
                return _testDbCon;
            }
        }


        #endregion Properties

        #region Constructor

        public SettingsController(SettingsPage _inputSet)
        {
            _set = _inputSet;

            _mySqlDbConCont = new MySqlDBSettingsController();
            //load saved DBSettings into textboxes
            DatabaseSettings _dbsets = DatabaseSettings.Default;
            _set.txtbxAccName.Text = _dbsets.AccountUsername;
            _set.pwbxAccPw.Password = _dbsets.AccountPassword;
            _set.txtbxDBName.Text = _dbsets.DatabaseName;
            _set.txtbxPort.Text = _dbsets.Port;
            _set.txtbxServer.Text = _dbsets.Server;
            _set.lblTestDBCon.Content = "Untested";
        }

        #endregion Constructor

        #region Private Helpers

        private void SaveAllDBSettings()
        {
            DatabaseSettings _dbsets = DatabaseSettings.Default;
            _dbsets.AccountUsername = _set.txtbxAccName.Text;
            _dbsets.AccountPassword = _set.pwbxAccPw.Password;
            _dbsets.DatabaseName = _set.txtbxDBName.Text;
            _dbsets.Port = _set.txtbxPort.Text;
            _dbsets.Server = _set.txtbxServer.Text;
            _dbsets.Save();
        }

        private void DBTestConnection()
        {
            _mySqlDbConCont.TestDBConnection.Execute(null);

            if (_mySqlDbConCont.TestConnectSuccess)
            {
                string msg = string.Format("Test Successful");
                _set.lblTestDBCon.Content = msg;
            }
            else
            {
                string msg = string.Format("Test Unsuccessful");
                _set.lblTestDBCon.Content = msg;
            }
        }

        #endregion Private Helpers
    }
}
