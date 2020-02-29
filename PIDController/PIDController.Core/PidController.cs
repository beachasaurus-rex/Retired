using System;
using System.Linq;

namespace PIDController.Core
{
    public class PidController
    {
        //delegates
        public delegate double[] TransientEquations(double t, double[] gains, double[] inits);

        //private constants
        private const int _numEqu = 3;

        //fields
        private TransientEquations _trans;
        private double[][] _results;

        //properties
        public ControllerParameters PidParameters { get; private set; }
        public double[] TimeValuesMilliseconds { get; private set; }
        public double[] YValues { get; private set; }
        public double[] YDotValues { get; private set; }
        public double[] YDoubleDotValues { get; private set; }

        //constructors
        public PidController(ControllerParameters cParams,
                             TransientEquations trans)
        {
            PidParameters = cParams;
            _trans = trans;

            TimeValuesMilliseconds = new double[cParams.CountIterations];
            YValues = new double[cParams.CountIterations];
            YDotValues = new double[cParams.CountIterations];
            YDoubleDotValues = new double[cParams.CountIterations];
        }

        //methods
        public void SolveSimulation()
        {
            double[][] results = new double[PidParameters.CountIterations][];

            for (long i = 0; i < PidParameters.CountIterations; i++)
            {
                double[] curResults = _trans(PidParameters.TimeSeriesArray[i], PidParameters.Gains, PidParameters.InitialValues);

                TimeValuesMilliseconds[i] = curResults[0];
                YValues[i] = curResults[1];
                YDotValues[i] = curResults[2];
                YDoubleDotValues[i] = curResults[3];

                results[i] = curResults;
            }

            _results = results;
        }
    }
}
