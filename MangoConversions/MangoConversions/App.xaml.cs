using System.Windows;
using MangoConversions.UI.Windows;

using System;
using System.Windows.Interop;

namespace MangoConversions
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            ConversionWindow cnvWin = new ConversionWindow();
            cnvWin.Show();
        }
    }
}
