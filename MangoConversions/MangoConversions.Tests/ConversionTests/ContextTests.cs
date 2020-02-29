using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MangoConversions.Conversion;
using MangoConversions.Conversion.Measurements;
using MangoConversions.Conversion.Units;
using MangoConversions.Conversion.UnitSystems;
using FluentAssertions.Collections;

namespace MangoConversions.Tests.ConversionTests
{
    /// <summary>
    /// Tests for Context
    /// </summary>
    [TestClass]
    public class ContextTests
    {
        #region Constructors

        public ContextTests()
        {
        }

        #endregion Constructors

        #region Additional test attributes
        //
        // You can use the following additional attributes as you write your tests:
        //
        // Use ClassInitialize to run code before running the first test in the class
        // [ClassInitialize()]
        // public static void MyClassInitialize(TestContext testContext) { }
        //
        // Use ClassCleanup to run code after all tests in a class have run
        // [ClassCleanup()]
        // public static void MyClassCleanup() { }
        //
        // Use TestInitialize to run code before running each test 
        // [TestInitialize()]
        // public void MyTestInitialize() { }
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion
        
        //artifact this once Context is complete.
        //next step is to blackbox test Context.
        [TestMethod]
        public void Context_DevelopmentTests()
        {
            BaseMeasurement meas1u1 = new BaseMeasurement("Mass", "M", new List<BaseUnit>{ new BaseUnit("gram", "g") });
            BaseMeasurement meas2u1 = new BaseMeasurement("Length", "L", new List<BaseUnit>{new BaseUnit("meter", "m") });
            BaseMeasurement meas3u1 = new BaseMeasurement("Time", "T", new List<BaseUnit> { new BaseUnit("second", "s") });
            DerivedMeasurement meas4u1 = new DerivedMeasurement("Velocity", "v", new List<DerivedUnit> { new DerivedUnit("MeterPerSec", "mps", new Dictionary<string, string> { { "meter", "m" }, { "second", "s" } }) }, @"([L])\([T])");
            UnitSystem u1 = new UnitSystem("SI", new List<Measurement>
            {
                meas1u1,
                meas2u1,
                meas3u1,
                meas4u1
            });

            BaseMeasurement meas1u2 = new BaseMeasurement("Mass", "M", new List<BaseUnit> { new BaseUnit("slug", "sl") });
            BaseMeasurement meas2u2 = new BaseMeasurement("Length", "L", new List<BaseUnit> { new BaseUnit("foot", "ft") });
            BaseMeasurement meas3u2 = new BaseMeasurement("Time", "T", new List<BaseUnit> { new BaseUnit("second", "s") });
            DerivedMeasurement meas4u2 = new DerivedMeasurement("Velocity", "v", new List<DerivedUnit> { new DerivedUnit("FootPerSec", "ftps", new Dictionary<string, string> { { "foot", "ft" }, { "second", "s" } }) }, @"([L])\([T])");
            UnitSystem u2 = new UnitSystem("English", new List<Measurement>
            {
                meas1u2,
                meas2u2,
                meas3u2,
                meas4u2
            });

            BaseMeasurement meas1u3 = new BaseMeasurement("Mass", "M", new List<BaseUnit> { new BaseUnit("blarg", "bl") });
            BaseMeasurement meas2u3 = new BaseMeasurement("Length", "L", new List<BaseUnit> { new BaseUnit("scant", "sc") });
            BaseMeasurement meas3u3 = new BaseMeasurement("Time", "T", new List<BaseUnit> { new BaseUnit("second", "s") });
            DerivedMeasurement meas4u3 = new DerivedMeasurement("Velocity", "v", new List<DerivedUnit> { new DerivedUnit("BlargPerSec", "blps", new Dictionary<string, string> { { "blarg", "bl" }, { "second", "s" } }) }, @"([L])\([T])");
            UnitSystem u3 = new UnitSystem("Other", new List<Measurement>
            {
                meas1u3,
                meas2u3,
                meas3u3,
                meas4u3
            });

            List<UnitSystem> usysList = new List<UnitSystem>
            {
                u1,
                u2,
                u3
            };

            //List<Dictionary<BaseMeasurement, UnitSystem>> expGrouping = new List<Dictionary<BaseMeasurement, UnitSystem>>
            //{
            //    {
            //        new Dictionary<BaseMeasurement, UnitSystem>
            //        {
            //            { meas1u1, u1 },
            //            { meas2u1, u1 },
            //            { meas3u1, u1 }
            //        }
            //    },
            //    {
            //        new Dictionary<BaseMeasurement, UnitSystem>
            //        {
            //            { meas1u2, u2 },
            //            { meas2u2, u2 },
            //            { meas3u2, u2 }
            //        }
            //    },
            //                    {
            //        new Dictionary<BaseMeasurement, UnitSystem>
            //        {
            //            { meas1u3, u3 },
            //            { meas2u3, u3 },
            //            { meas3u3, u3 }
            //        }
            //    }
            //};

            Context cntx = new Context(usysList);
            //getting base measurements works -- x
            //grouping base measurements by measurement type works -- x
            Dictionary<BaseMeasurement, string> testDicts = cntx.GetBaseMeasurementDictionaries();
            List<List<BaseMeasurement>> testGroups = cntx.GroupBaseMeasurements(testDicts);

            

            //for (int i = 0; i < testGrouping.Count; i++)
            //{
            //    GenericDictionaryAssertions<BaseMeasurement, UnitSystem>.Equals(testGrouping[i], expGrouping[i]);
            //}


        }
    }
}
