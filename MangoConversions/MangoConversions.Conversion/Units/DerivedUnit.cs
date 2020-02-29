using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace MangoConversions.Conversion.Units
{
    public class DerivedUnit : Unit
    {
        #region Fields

        //this is needed to determine which units within the context
        //this unit is made of
        //KEYS: base unit names
        //VALUES: base unit symbol
        private readonly ReadOnlyDictionary<string, string> _baseUnits;

        #endregion Fields

        #region Constructors

        //default
        public DerivedUnit(string name, string symbol, Dictionary<string, string> baseUnits, double val = 0)
            : base(name, symbol, val)
        {
            _baseUnits = new ReadOnlyDictionary<string, string>(baseUnits);
        }

        #endregion Constructors
    }
}
