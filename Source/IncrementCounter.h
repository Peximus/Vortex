#pragma once
#include <JuceHeader.h>

class IncrementCounter : public juce::Component, public juce::Button::Listener
{


public:

    IncrementCounter()
    {

        juce::Image upimage = juce::ImageCache::getFromMemory(BinaryData::up_png, BinaryData::up_pngSize);
        juce::Image downimage = juce::ImageCache::getFromMemory(BinaryData::down_png, BinaryData::down_pngSize);
        matrix = juce::ImageCache::getFromMemory(BinaryData::matrix_png, BinaryData::matrix_pngSize);

        up.setImages(false, false, true, upimage, 1.0f, {}, upimage, 1.0f, {}, upimage, 1.0f, {});
        down.setImages(false, false, true, downimage, 1.0f, {}, downimage, 1.0f, {}, downimage, 1.0f, {});

        up.addListener(this);
        down.addListener(this);

        addAndMakeVisible(up);
        addAndMakeVisible(down);

    }



    ~IncrementCounter() noexcept override = default;


    void setup(int digits, int startvalue) 
    {
        num_digits = digits;
        inc_value = startvalue;
    }

    int getinc()
    {

        return inc_value;

    }

    void paint(juce::Graphics& g) override {

            //g.setColour(juce::Colours::green);
            //g.fillRect(0, 0, 20, 20);

        switch (num_digits)
        {

        case 1:
            g.drawImage(matrix, 32, 38, 16, matrix.getHeight(), (inc_value % 10) * 16, 0, 16, matrix.getHeight(), false);
            break;

        case 2:
            g.drawImage(matrix, 32, 38, 16, matrix.getHeight(), (inc_value % 10) * 16, 0, 16, matrix.getHeight(), false);
            g.drawImage(matrix, 16, 38, 16, matrix.getHeight(), (inc_value % 100 / 10) * 16, 0, 16, matrix.getHeight(), false);
            break;

        case 3:
            g.drawImage(matrix, 32, 38, 16, matrix.getHeight(), (inc_value % 10) * 16, 0, 16, matrix.getHeight(), false);
            g.drawImage(matrix, 16, 38, 16, matrix.getHeight(), (inc_value % 100 / 10) * 16, 0, 16, matrix.getHeight(), false);
            g.drawImage(matrix, 0, 38, 16, matrix.getHeight(), (inc_value % 1000 / 100) * 16, 0, 16, matrix.getHeight(), false);
            break;

        }



    }
    void buttonClicked(juce::Button* button) override
    {
        if (button == &up)
        {

            inc_value++;
            repaint();

        }

        if (button == &down)
        {

            inc_value--;

            if (inc_value <= 0) inc_value = 0;

            repaint();

        }
    }

    void resized() override {

        up.setBounds(16, 0, 32, 37);
        down.setBounds(16, 60, 32, 37);

    }


private:

     juce::ImageButton up;
     juce::ImageButton down;
     juce::Image matrix;

     bool clicked = false;

     int inc_value = 0;

     int num_digits = 0;

     JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IncrementCounter)


};