using System.Windows.Controls;
using GucciFinances.Models.Controllers;

namespace GucciFinances.Views
{
    /// <summary>
    /// Interaction logic for DatabaseSettings.xaml
    /// </summary>
    public partial class SettingsPage : Page
    {
        public SettingsPage()
        {
            InitializeComponent();
            this.DataContext = new SettingsController(this);
        }
    }
}
