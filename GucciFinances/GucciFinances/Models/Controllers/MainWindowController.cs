using System;
using System.Windows.Input;
using GucciFinances.Models.Commands;
using GucciFinances.Views.Windows;

namespace GucciFinances.Models.Controllers
{
    public class MainWindowController
    {
        #region Fields

        private ICommand _navHome;
        private ICommand _navTrans;
        private ICommand _navSettings;
        private readonly MainWindow _currWin;

        #endregion Fields

        #region Properties

        public ICommand NavigateHome
        {
            get
            {
                if (_navHome == null)
                {
                    Uri relPath = new Uri("/Views/HomePage.xaml", UriKind.Relative);
                    _navHome = new RelayCommand(
                        param => Navigate(relPath)
                        );
                }
                return _navHome;
            }
        }
        public ICommand NavigateTransactions
        {
            get
            {
                if (_navTrans == null)
                {
                    Uri relPath = new Uri("/Views/TransactionsPage.xaml", UriKind.Relative);
                    _navTrans = new RelayCommand(
                        param => Navigate(relPath)
                        );
                }
                return _navTrans;
            }
        }
        public ICommand NavigateSettings
        {
            get
            {
                if (_navSettings == null)
                {
                    Uri _relPath = new Uri("/Views/SettingsPage.xaml", UriKind.Relative);
                    _navSettings = new RelayCommand(
                        param => Navigate(_relPath)
                        );
                }
                return _navSettings;
            }
        }

        #endregion Properties

        #region Constructors

        public MainWindowController(MainWindow currWin)
        {
            _currWin = currWin;
        }

        #endregion Constructors

        #region Protected Helpers

        protected void Navigate(Uri relPath)
        {
            _currWin.frameContent.Source = relPath;
        }

        #endregion Protected Helpers
    }
}
