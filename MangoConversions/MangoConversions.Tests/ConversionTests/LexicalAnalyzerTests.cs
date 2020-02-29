using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MangoConversions.Conversion;

namespace MangoConversions.Tests.ConversionTests
{
    /// <summary>
    /// Tests the logic for the LexicalAnalyzer
    /// </summary>
    [TestClass]
    public class LexicalAnalyzerTests
    {
        #region Constructor

        public LexicalAnalyzerTests()
        {
        }

        #endregion Constructor

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

        #region Class Initializers

        

        #endregion Class Initializers

        #region Tests
        
        //artifact this test when LexicalAnalyzer is complete
        [TestMethod]
        public void TestSimpleGrouping()
        {
            List<string> control = new List<string> { @"[L]", @"\", @"[T]" };
            List<string> test = LexicalAnalyzer.GroupConversionTokens(@"([L])\([T])");
            
            CollectionAssert.AreEqual(test, control);
        }

        #endregion Tests
    }
}
