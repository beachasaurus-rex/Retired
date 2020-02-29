
namespace MangoConversions.Conversion.Relationships
{
    public class AffineRelationship : Relationship
    {
        #region Fields

        protected readonly string _name;
        protected readonly double _scale;
        protected readonly double _offset;

        #endregion Fields

        #region Properties

        public override string Name { get { return _name; } }

        #endregion Properties

        #region Constructors

        //default
        public AffineRelationship() : base() { }
        public AffineRelationship(string name, double scale, double offset)
            : base()
        {
            _name = name;
            _scale = scale;
            _offset = offset;
        }

        #endregion Constructors
    }
}
