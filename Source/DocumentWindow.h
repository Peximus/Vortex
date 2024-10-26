#pragma once
#include <JuceHeader.h>

class BasicWindow : public juce::DocumentWindow
{
public:
    BasicWindow(const juce::String& name, juce::Colour backgroundColour, int buttonsNeeded, bool add)
        : DocumentWindow(name, backgroundColour, buttonsNeeded, add)
    {}

    void closeButtonPressed() override
    {
  
        setVisible(false);
        
        //delete this;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BasicWindow)
};