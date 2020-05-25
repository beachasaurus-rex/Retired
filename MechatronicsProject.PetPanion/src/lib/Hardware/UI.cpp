#ifndef UI_H
    #define UI_H
    #include "UI.hpp"
#endif

//PRIVATE

void UI::DetermineFrequency()
{
    boolean pin1IsActive = digitalRead(this->_pin1);
    boolean pin2IsActive = digitalRead(this->_pin2);

    if (pin1IsActive && !pin2IsActive)
    {
        this->_freq = this->_freqOpts[1];
    }
    else if (!pin1IsActive && pin2IsActive)
    {
        this->_freq = this->_freqOpts[2];
    }
    else if (pin1IsActive && pin2IsActive)
    {
        this->_freq = this->_freqOpts[3];
    }
    else if (!pin1IsActive && !pin2IsActive)
    {
        this->_freq = this->_freqOpts[0];
    }
}

//PUBLIC

UI::UI(long pin1, long pin2)
{
    this->_pin1 = pin1;
    this->_pin2 = pin2;
    this->SetFrequencyOptions(this->_defaultFreqOpts);
    this->_freq = this->_freqOpts[0];
}

void UI::Setup()
{
    pinMode(this->_pin1, INPUT);
    pinMode(this->_pin2, INPUT);
}

long UI::GetFrequency()
{
    this->DetermineFrequency();
    return this->_freq;
}

void UI::SetFrequencyOptions(long newOpts[4])
{
    for (int i = 0; i < 4; i++)
    {
        this->_freqOpts[i] = newOpts[i];
    }
    this->DetermineFrequency();
}
