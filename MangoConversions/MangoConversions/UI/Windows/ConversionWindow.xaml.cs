using System;
using System.Windows;
using MangoConversions.UI.Views;

namespace MangoConversions.UI.Windows
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class ConversionWindow : Window
    {
        public ConversionWindow()
        {
            InitializeComponent();

            Uri relPath = new Uri("/UI/Views/ConversionPage.xaml", UriKind.Relative);
            this.frameContent.Source = relPath;
        }
    }
}
