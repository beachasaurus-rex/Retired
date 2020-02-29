namespace MangoConversions.Conversion.Units
{
    public class BaseUnit : Unit
    {
        #region Fields

        //conversion factor from this unit to a SI unit
        protected readonly double _siRefConv;

        #endregion Fields

        #region Constructors

        //default
        public BaseUnit(string name, string symbol, double siRefConv, double val = 0) 
            : base(name, symbol, val)
        {
            _siRefConv = siRefConv;
        }

        #endregion Constructors
    }
}
