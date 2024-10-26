#pragma once
#include <JuceHeader.h>


class PeakMeter : public juce::Component, public juce::Timer {
public:

    PeakMeter()
    {

       startTimer(100);

    }




    ~PeakMeter() noexcept override = default;
    
    void paint(juce::Graphics& g) override {




        int draw_cells = height;

        y_pos = 252;

        blue = 0;

        while (draw_cells > 0)
        {

            draw_cells--;

            g.setColour(juce::Colour::fromRGB(red, green, blue));

            g.fillRect(0, y_pos, 20, cell);

            y_pos -= 6;


            blue += 6;




        }
    }

    void resized() override {


    }

    void timerCallback() override
    {

        height--;

        repaint();
    
    }


    void setHeight(int new_height)
    {


        height = new_height;

    }


private:

    int height = 0;

    int cell = 4;

    int num_cells = 42;

    int red = 10;

    int green = 0;

    int blue = 255;

    int y_pos = 0;
    



};


