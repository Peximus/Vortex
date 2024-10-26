#pragma once
#include <JuceHeader.h>

#include "Variables.h"

class Info : public juce::Component {
public:

    Info()
    {


    }


    ~Info() noexcept override = default;

    void paint(juce::Graphics& g) override {

        g.setColour(juce::Colours::red);

        g.drawRect(getLocalBounds(), 1);

        /*
        g.drawRect(getLocalBounds(), 1);
       // g.setFont(24.0f);

       /* g.drawText(juce::String(timestamp), 0, 0, 250, 10, juce::Justification::left, true);

       // timestamp = round(timestamp);
        int milli = timestamp * 1000;


        g.drawText(juce::String(milli), 0, 20, 250, 10, juce::Justification::left, true);

        int beat = Round(milli);

        g.drawText(juce::String(beat), 0, 40, 250, 10, juce::Justification::left, true);
        */

        row = 0;

        for (auto var : stamps)
        {
            g.drawText(juce::String(var), 0, row, 250, 10, juce::Justification::left, true);

            row += 20;

        }
        


    }

    void resized() override {

    }

    void mouseDown(const juce::MouseEvent& event) override
    {


    }

    void print(juce::String string)
    {

        message.add(string);

        row = 0;

        repaint();

    }

    void printdouble(double thedouble)
    {

        timestamp = thedouble;

        stamps.add(thedouble);

        repaint();

    }

    int RoundDown(int toRound)
    {
        return toRound - toRound % 10;
    }

    int Round(int toRound)
    {

        int rem = toRound % 10;

        return rem >= 5 ? toRound - rem + 10 : toRound - rem;
    }

    void setVariable(juce::String string, int value)
    {

        var = new Variables();

        var->name = string;

        var->value = value;

        variables.add(var);

    }



private:


    juce::Array<double> stamps;

    juce::StringArray message;

    int row = 0;

    double timestamp;

    juce::OwnedArray<Variables> variables;

    Variables *var;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Info)

};













