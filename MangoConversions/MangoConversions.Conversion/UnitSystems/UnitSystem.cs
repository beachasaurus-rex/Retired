using System.Collections.Generic;
using MangoConversions.Conversion.Measurements;

namespace MangoConversions.Conversion.UnitSystems
{
    public class UnitSystem
    {
        private readonly string _name;
        private readonly List<Measurement> _meas;

        #region Properties

        public List<Measurement> Measurements { get { return _meas; } }
        public string Name { get { return _name; } }

        #endregion Properties

        #region Constructors

        //default
        public UnitSystem(string name, List<Measurement> meas)
        {
            _name = name;
            _meas = meas;
        }

        #endregion Constructors
    }
}
