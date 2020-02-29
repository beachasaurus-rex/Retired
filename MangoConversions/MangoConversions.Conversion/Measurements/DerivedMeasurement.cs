using System.Collections.Generic;
using MangoConversions.Conversion.Units;

namespace MangoConversions.Conversion.Measurements
{
    public class DerivedMeasurement : Measurement
    {
        #region Fields

        private readonly string _convToken;
        private readonly List<DerivedUnit> _uList;

        #endregion Fields

        #region Properties

        //the conversion token specifies the base measurements that
        //comprise this derived measurement
        public string ConversionToken { get { return _convToken; } }
        public List<DerivedUnit> Units { get { return _uList; } }

        #endregion Properties

        #region Constructors

        //default
        public DerivedMeasurement() : base() { }

        public DerivedMeasurement(string type, string symbol, List<DerivedUnit> uList, string conversionToken)
            : base(type, symbol)
        {
            _convToken = conversionToken;
            _uList = uList;
        }

        #endregion Constructors
    }
}
