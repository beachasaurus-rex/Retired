using System;
using System.Windows;
using GucciFinances.Views.Windows;

namespace GucciFinances
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        /// <summary>
        /// Application startup logic.
        /// </summary>
        /// <param name="e"></param>
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            //load the home page
            Uri defaultPage = new Uri("/Views/HomePage.xaml", UriKind.Relative);
            MainWindow viewCont = new MainWindow();
            viewCont.frameContent.Source = defaultPage;
            viewCont.Show();
        }
    }
}
