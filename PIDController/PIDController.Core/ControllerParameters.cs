using System;
using System.Diagnostics;
using System.Linq;

namespace PIDController.Core
{
    public sealed class ControllerParameters
    {

        //properties
        public double IntegralGain { get; set; }
        public double DerivativeGain { get; set; }
        public double ErrorGain { get; set; }
        public double[] Gains
        {
            get
            {
                return new double[]
                {
                    IntegralGain,
                    DerivativeGain,
                    ErrorGain
                };
            }
        }
        public double[] InitialValues { get; set; }
        public long CountIterations { get; private set; }
        public long SamplingRateTicks { get; set; }
        public double SamplingRateMilliseconds { get; set; }
        public TimeSpan SimulationDuration { get; private set; }
        public DateTime StartDateTime { get; private set; }
        public DateTime EndDateTime { get; private set; }
        public double[] TimeSeriesArray { get; set; }

        //constructors
        /// <summary>
        /// When sampling rate is in milliseconds.
        /// </summary>
        /// <param name="intGain"></param>
        /// <param name="derivGain"></param>
        /// <param name="errGain"></param>
        /// <param name="startDateTime"></param>
        /// <param name="endDateTime"></param>
        /// <param name="samplingRate"></param>
        /// <param name="calcY"></param>
        /// <param name="calcYDot"></param>
        /// <param name="calcYDDot"></param>
        /// <param name="tResp"></param>
        public ControllerParameters(double intGain,
                                    double derivGain,
                                    double errGain,
                                    double[] inits,
                                    DateTime startDateTime,
                                    DateTime endDateTime,
                                    double samplingRate)
        {
            CheckStartEndDateTimes(startDateTime, endDateTime);

            InitialValues = inits;
            IntegralGain = intGain;
            DerivativeGain = derivGain;
            ErrorGain = errGain;
            StartDateTime = startDateTime;
            EndDateTime = endDateTime;
            SimulationDuration = new TimeSpan(endDateTime.Ticks - startDateTime.Ticks);
            SamplingRateMilliseconds = samplingRate;
            SamplingRateTicks = (long)(samplingRate * 10000);
            CountIterations = SimulationDuration.Ticks / SamplingRateTicks;
            TimeSeriesArray = CalcTimeSeries();
        }

        //private helpers
        /// <summary>
        /// Calculates each step of the simulation and returns a
        /// long array which represents the time series.
        /// </summary>
        /// <param name="tStart"></param>
        /// <param name="tEnd"></param>
        /// <returns></returns>
        private double[] CalcTimeSeries()
        {
            long[] tSeries = new long[CountIterations];
            long j = 0;

            for (long i = 0; i < CountIterations * SamplingRateTicks; i = i + SamplingRateTicks)
            {
                tSeries[j] = i;
                j = j + 1;
            }

            double[] newSeries = tSeries.Select(x => (double)x / 10000).ToArray();

            return newSeries;
        }
        private void CheckStartEndDateTimes(DateTime tStart, DateTime tEnd)
        {
            if (tStart.Ticks > tEnd.Ticks)
            {
                Debug.WriteLine("Error: Start DateTime > end DateTime.");
                return;
            }
            else if (tStart.Ticks == tEnd.Ticks)
            {
                Debug.WriteLine("Error: Start DateTime = end DateTime.");
                return;
            }
        }
    }
}
