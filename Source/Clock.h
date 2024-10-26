#pragma once
#include <JuceHeader.h>




class Clock : public juce::Component, public juce::Timer {
public:


    Clock() {
    
        setMouseClickGrabsKeyboardFocus(false);
 
    
    }


    void paint(juce::Graphics& g) override {


        g.setColour(juce::Colours::green);
        //g.fillRect(x, y, 20, 20);
        g.setFont(48.0f);

        output.clear();

        output = juce::String::formatted("%.2d:%.2d:%.2d:%.2d", hours, minutes, seconds, milli);

        g.drawText(output, getLocalBounds(), juce::Justification::centred, true);



    }

    void resized() override {


    }


    void startClock()
    {

        startTimer(10);


    }

    void stopClock()
    {

        stopTimer();


    }
    void timerCallback() override
    {


        milli++;
        
        if (milli >= 99)
        {
        
            milli = 0;
        
            seconds++;

        }

        if (seconds >= 60)
        {
            seconds = 0;

            minutes++;

        }


        if (minutes >= 60)
        {

            hours++;

        }


        repaint();

    }

    


  private:

    int freq = 100;

    int milli = 0;

    int seconds = 0;

    int minutes = 0;

    int hours = 0;

    juce::String output;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Clock)


};