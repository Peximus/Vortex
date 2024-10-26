#pragma once
#include <JuceHeader.h>


class Help : public juce::Component {
public:

    Help()
    {


    }


    ~Help() noexcept override = default;

    void paint(juce::Graphics& g) override {

        g.setColour(juce::Colours::white);

        g.setFont(24.0f);

        g.drawText("-=Keyboard Commands=-", 0, 0, 600, 30, juce::Justification::centred, true);

        g.drawText("CUT = Ctrl - X", 100, 40, 600, 30, juce::Justification::left, true);

        g.drawText("COPY = Ctrl - C", 100, 80, 600, 30, juce::Justification::left, true);


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


private:

    juce::StringArray message;

    int row = 0;

    double timestamp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Help)

};


