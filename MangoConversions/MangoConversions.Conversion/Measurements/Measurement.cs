using System.Collections.Generic;
using MangoConversions.Conversion.Units;

namespace MangoConversions.Conversion.Measurements
{
    public abstract class Measurement
    {
        #region Fields

        private readonly string _type;
        private readonly string _symbol;

        #endregion Fields

        #region Properties

        public string Type { get { return _type; } }
        public string Symbol { get { return _symbol; } }

        #endregion Properties

        #region Constructors

        //default
        protected Measurement() { }

        protected Measurement(string type, string symbol)
        {
            _type = type;
            _symbol = symbol;
        }

        #endregion Constructors
    }
}
