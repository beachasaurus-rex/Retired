using System;
using System.Windows.Input;
using GucciFinances.Models.Commands;
using GucciFinances.Models.DatabaseObjects.Gateways;
using GucciFinances.Views;
using GucciFinances.Views.Forms;

namespace GucciFinances.Models.Controllers
{
    public class TransactionsPageController
    {
        #region Fields

        private readonly TransactionsPage _transPage;
        
        private ICommand _displayPostTransForm;

        #endregion Fields

        #region Properties

        public ICommand DisplayPostForm
        {
            get
            {
                if (_displayPostTransForm == null)
                {
                    Uri relPath = new Uri("/Views/Forms/PostTransactionForm.xaml", UriKind.Relative);
                    _displayPostTransForm = new RelayCommand(
                        param => FormNavigate(relPath)
                        );
                }
                return _displayPostTransForm;

            }
        }

        #endregion Properties

        #region Constructors

        public TransactionsPageController(TransactionsPage transPage)
        {
            _transPage = transPage;
        }

        #endregion Constructors

        #region Private Helpers

        private void FormNavigate(Uri relPath)
        {
            _transPage.frameForm.Source = relPath;
        }

        #endregion Private Helpers
    }
}
