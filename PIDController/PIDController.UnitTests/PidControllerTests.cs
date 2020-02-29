using System;
using System.IO;
using System.Text;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PIDController.Core;

namespace PIDController.UnitTests
{
    [TestClass]
    public class PidControllerTests
    {
        [TestMethod]
        public void TestMethod()
        {
            ControllerParameters cParams = new ControllerParameters(0,0,0,
                                                                    new double[] { 0, 0 },
                                                                    new DateTime(1, 1, 1, 0, 0, 0),
                                                                    new DateTime(1, 1, 1, 0, 0, 30),
                                                                    1);
            PidController cont = new PidController(cParams, Transients);
            cont.SolveSimulation();
            ResultsToCsv(cont);
        }

        private void ResultsToCsv(PidController cont)
        {
            StringBuilder csvContent = new StringBuilder();
            string filePath = @"D:\My_Data\GithubRepos\Active\PIDController\PIDController.UnitTests\test.csv";
            
            for (long i = 0; i < cont.TimeValuesMilliseconds.LongLength; i++)
            {
                string curRow = string.Format($"{cont.TimeValuesMilliseconds[i]},{cont.YValues[i]},{cont.YDotValues[i]},{cont.YDoubleDotValues[i]}");
                csvContent.AppendLine(curRow);
            }
            
            File.WriteAllText(filePath, csvContent.ToString());
        }

        private double[] Transients(double tMs, double[] gains, double[] inits)
        {
            double[] vals = new double[4];
            double t = tMs / 1000;
            double tms = tMs;
            double x0 = inits[0];
            double xd0 = inits[1];

            vals[0] = tMs;
            vals[1] = (2 * Math.Sqrt(3) * Math.Exp(-t / 2) * Math.Sin((Math.Sqrt(3) * t) / 2)) / 3;
            vals[2] = Math.Exp(-t / 2) * Math.Cos((Math.Sqrt(3) * t) / 2) - (Math.Sqrt(3) * Math.Exp(-t / 2) * Math.Sin((Math.Sqrt(3) * t) / 2)) / 3;
            vals[3] = -Math.Exp(-t / 2) * Math.Cos((Math.Sqrt(3) * t) / 2) - (Math.Sqrt(3) * Math.Exp(-t / 2) * Math.Sin((Math.Sqrt(3) * t) / 2)) / 3;

            return vals;
        }
    }
}
