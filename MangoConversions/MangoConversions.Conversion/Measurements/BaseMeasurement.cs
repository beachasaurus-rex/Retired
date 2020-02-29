using System.Collections.Generic;
using MangoConversions.Conversion.Units;

namespace MangoConversions.Conversion.Measurements
{
    public class BaseMeasurement : Measurement
    {
        #region Fields

        private readonly List<BaseUnit> _uList;

        #endregion Fields

        #region Properties

        public List<BaseUnit> Units { get { return _uList; } }

        #endregion Properties

        #region Constructors

        public BaseMeasurement() : base() { }

        public BaseMeasurement(string type, string symbol, List<BaseUnit> uList)
            : base(type, symbol)
        {
            _uList = uList;
        }

        #endregion Constructors
    }
}
