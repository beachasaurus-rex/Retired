using System.Collections.Generic;
using System.Linq;
using MoreLinq;
using MangoConversions.Conversion.Measurements;
using MangoConversions.Conversion.Units;
using MangoConversions.Conversion.UnitSystems;

namespace MangoConversions.Conversion
{
    public class Context
    {
        #region Fields

        //KEYS: fromBaseMeas "To" toBaseMeas
        //VALUES: base conversion factor value
        private Dictionary<string, double> _contextualBaseConvFactors;
        private List<UnitSystem> _sysList;

        //KEYS: conversion name
        //VALUES: conversion factor value
        private Dictionary<string, double> _contConv;

        //KEYS: symbol
        //VALUES: measure
        private Dictionary<string, BaseMeasurement> _baseMeasures;

        #endregion Fields

        #region Properties

        public List<UnitSystem> ContextualizedSystems { get { return _sysList; } }

        //KEYS: conversion name
        //VALUES: conversion factor value
        public Dictionary<string, double> ContextualConversions { get { return _contConv; } }

        #endregion Properties

        #region Constructors

        public Context(List<UnitSystem> sysList)
        {
            _sysList = sysList;
        }

        #endregion Constructors

        #region Private Methods

        private void BuildContextualConversions()
        {
            Dictionary<BaseMeasurement, string> baseDict = GetBaseMeasurementDictionaries();
            List<List<BaseMeasurement>> groupedMeasurements = GroupBaseMeasurements(baseDict);
        }

        //groups the base measurements by unit system
        public Dictionary<BaseMeasurement,string> GetBaseMeasurementDictionaries()
        {
            Dictionary<BaseMeasurement, string> baseMeasures = new Dictionary<BaseMeasurement, string>();
            //Dictionary<BaseMeasurement, string> measGroup = new Dictionary<BaseMeasurement, string>();

            //iterate through each unit system
            for (int i = 0; i < _sysList.Count; i++)
            {
                UnitSystem uSys = _sysList[i];

                //iterate through each measurement of each unit system
                for (int j = 0; j < uSys.Measurements.Count; j++)
                {
                    Measurement curMeas = uSys.Measurements[j];

                    //filter to only get base measurements
                    if (curMeas.GetType() == typeof(BaseMeasurement))
                    {
                        baseMeasures.Add((BaseMeasurement)curMeas, uSys.Name);
                    }
                }
                //var copied = new Dictionary<BaseMeasurement, string>(measGroup);
                //aggdDicts.Add(copied);
                //measGroup.Clear();
            }

            return baseMeasures;
        }

        //groups the base measurements by similar base measurements. (ex. group by mass measurements)
        public List<List<BaseMeasurement>> GroupBaseMeasurements(Dictionary<BaseMeasurement, string> baseDict)
        {
            List<BaseMeasurement> uniqueBases = baseDict.Keys.DistinctBy(x => x.Type).ToList();
            List<List<BaseMeasurement>> aggdLists = new List<List<BaseMeasurement>>();
            List<BaseMeasurement> measList = new List<BaseMeasurement>();

            for (int i = 0; i < uniqueBases.Count; i++)
            {
                aggdLists.Add( baseDict.Keys.Where( x => x.Type == uniqueBases[i].Type)
                                            .ToList()
                                            );
            }

            return aggdLists;
        }

        //KEYS: BaseMeasurement Type
        //VALUES: Dictionary of conversion mappings
        //  KEYS: fromUnit To toUnit
        //  VALUES: conversion factor
        public Dictionary<string,Dictionary<string, double>> MapConversionValues(List<List<BaseMeasurement>> groupedBases)
        {
            Dictionary<string, Dictionary<string, double>> measMaps = new Dictionary<string, Dictionary<string, double>>();
            Dictionary<string, double> curConvMap = new Dictionary<string, double>();
            List<BaseMeasurement> curList = new List<BaseMeasurement>();
            BaseMeasurement curMeas;
            BaseMeasurement subMeas;
            BaseUnit curUnit;
            BaseUnit subUnit;
            double convFact = 0;

            //go through the list
            for (int i = 0; i < groupedBases.Count; i++)
            {
                curList = groupedBases[i];

                //go through the sublists
                for (int j = 0; j < curList.Count; j++)
                {
                    curMeas = curList[j];

                    //go through sublists to create map
                    for (int k = 0; k < curList.Count; k++)
                    {
                        subMeas = curList[k];

                        if (subMeas != curMeas)
                        {
                            //go through the list of units in the measurement
                            for (int x = 0; x < subMeas.Units.Count; x++)
                            {
                                curUnit = subMeas.Units[x];

                                //go through the list of units to create
                                //inter-system conversions
                                for (int y = 0; y < subMeas.Units.Count; y++)
                                {
                                    subUnit = subMeas.Units[y];

                                    if (curUnit != subUnit)
                                    {

                                    }
                                }
                            }
                        }
                    }
                }
            }

            return null;
        }

        #endregion Private Methods

    }
}
