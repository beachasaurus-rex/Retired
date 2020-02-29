using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using MLApp;
using RemakeSchoolMatlabProject.MatLabObjects;

namespace RemakeSchoolMatlabProject
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void btnCalc_Click(object sender, RoutedEventArgs e)
        {
            MLApp.MLApp session = new MLApp.MLApp();
            MatLabController.AddMatLabFilesToPath(session);
            string filePath = MatLabController.RunScript(session, GetInputs());
            Uri imgUri = new Uri(filePath);
            BitmapImage imgBmp = new BitmapImage(imgUri);

            imgGraph.Source = imgBmp;
        }

        private object[] GetInputs()
        {
            object[] _UI = new object[]
                {
                    double.Parse(tbxTestMass.Text),
                    double.Parse(tbxDuration.Text),
                    double.Parse(tbxDampRatio.Text),
                    double.Parse(tbxSpringConst.Text),
                    double.Parse(tbxInitPosi.Text),
                    double.Parse(tbxInitVelo.Text)
                };
            return _UI;
        }
    }
}
