namespace MangoConversions.Conversion.Units
{
    public abstract class Unit
    {
        #region Fields

        private readonly string _name;
        private readonly string _symbol;
        private double _val;

        #endregion Fields

        #region Properties

        public string Name { get; }
        public string Symbol { get; }
        public double Value
        {
            get { return _val; }
            set
            {
                if (_val != value)
                {
                    _val = value;
                }
            }
        }

        #endregion Properties

        #region Constructors

        //base
        protected Unit(string name, string symbol, double val = 0)
        {
            _name = name;
            _symbol = symbol;
            _val = val;
        }

        #endregion Constructors
    }
}
