using System.Windows.Controls;
using GucciFinances.Models.Controllers;

namespace GucciFinances.Views
{
    /// <summary>
    /// Interaction logic for TransactionsPage.xaml
    /// </summary>
    public partial class TransactionsPage : Page
    {
        public TransactionsPage()
        {
            InitializeComponent();
            this.DataContext = new TransactionsPageController(this);
        }
    }
}
