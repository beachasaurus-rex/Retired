using System;
using System.Windows.Controls;
using GucciFinances.Models.Controllers;
using GucciFinances.Models.Enums;

namespace GucciFinances.Views.Forms
{
    /// <summary>
    /// Interaction logic for PostTransactionForm.xaml
    /// </summary>
    public partial class PostTransactionForm : Page
    {
        public PostTransactionForm()
        {
            InitializeComponent();
            ConvertEnums();
            this.DataContext = new TransactionFormsController(this);
            
        }

        private void ConvertEnums()
        {
            this.cmboMop.ItemsSource = Enum.GetValues(typeof(PaymentMethod));
        }
    }
}
