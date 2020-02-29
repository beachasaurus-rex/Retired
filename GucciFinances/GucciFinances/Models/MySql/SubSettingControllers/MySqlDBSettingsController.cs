using System.Windows.Input;
using GucciFinances.Models.Commands;
using GucciFinances.Models.Connections;

namespace GucciFinances.Models.MySql.SubSettingControllers
{
    public class MySqlDBSettingsController
    {
        #region Fields

        private ICommand _testDbConnect;
        private bool _conTestResult;

        #endregion Fields

        #region Properties

        public ICommand TestDBConnection
        {
            get
            {
                if (_testDbConnect == null)
                {
                    _testDbConnect = new RelayCommand(
                        param => DBTestConnect()
                        );
                }
                return _testDbConnect;
            }
        }
        public bool TestConnectSuccess
        {
            get { return _conTestResult; }
        }

        #endregion Properties

        #region Constructors

        public MySqlDBSettingsController()
        {
        }

        #endregion Constructors

        #region Private Helpers
        
        private void DBTestConnect()
        {
            bool pass = false;
            using (MySqlDbConnection _dbCon = new MySqlDbConnection())
            {
                if (_dbCon.CanConnect)
                {
                    pass = true;
                }
            }   
            _conTestResult = pass;
        }

        #endregion Private Helpers
    }
}
