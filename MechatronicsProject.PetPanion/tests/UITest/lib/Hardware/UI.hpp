#ifndef DEPS_H
    #define DEPS_H
    #include "deps.hpp"
#endif

class UI
{
    private:
        long _freqOpts[4];
        long _defaultFreqOpts[4] = {3, 4, 5, 6};
        long _pin1;
        long _pin2;
        long _freq;
        void DetermineFrequency(void);
    public:
        UI(long,long);
        void Setup(void);
        long GetFrequency(void);
        void SetFrequencyOptions(long[4]);
};
