using LiveCharts;
using System.IO;
using System.Windows.Controls;

namespace GraphingExample
{
    /// <summary>
    /// Interaction logic for ScatterPlot.xaml
    /// </summary>
    public partial class ScatterPlot : UserControl
    {
        public ChartValues<double> XSeries { get; private set; }
        public ChartValues<double> YSeries { get; private set; }

        public ScatterPlot()
        {
            InitializeComponent();

            XSeries = new ChartValues<double>();
            YSeries = new ChartValues<double>();

            GetData();
            DataContext = this;
        }

        private void GetData()
        {
            using (var reader = new StreamReader(@"D:\MyData\GithubRepos\Tutorials\GraphingExample\GraphingExample\TestData.csv"))
            {
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');

                    XSeries.Add(double.Parse(values[0]));
                    YSeries.Add(double.Parse(values[1]));
                }
            }
        }
    }
}
