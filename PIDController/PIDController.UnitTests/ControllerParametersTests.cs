using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PIDController.Core;

namespace PIDController.UnitTests
{
    [TestClass]
    public class ControllerParametersTests
    {
        [TestMethod]
        public void ControllerParameters_test_time_series_calculation()
        {
            //ControllerParameters cParams = new ControllerParameters(5, 5, 5,
            //                                                        new DateTime(1, 1, 1, 0, 0, 0),
            //                                                        new DateTime(1, 1, 1, 1, 0, 0),
            //                                                        1.0);
            //Assert.AreEqual(3600000, cParams.CountIterations);
            //Assert.AreEqual(3600000, cParams.TimeSeriesArray.LongLength);
        }
    }
}
