#pragma once
#include <JuceHeader.h>


class Note : public juce::Component {
public:

    Note()
    {
    }


    void setLength(int length)
    {

        note_length = length;

    }

    void setHeight(int height)
    {

        note_height = height;

    }

    void setNote(int note)
    {

        note_num = note;

    }

    void setTimeStamp(double thisTime, double nextTime)
    {
        thisTimeStamp = thisTime;

        nextTimeStamp = nextTime;

    }

    double getThisTime()
    {

        return thisTimeStamp;
    }

    double getNextTime()
    {

        return nextTimeStamp;
    }

    int getNote()
    {

        return note_num;
    }


    ~Note() noexcept override = default;
    
    void paint(juce::Graphics& g) override {

        g.setColour(juce::Colours::orangered);

        g.fillRect(0, 0, note_length, note_height);

        g.setColour(juce::Colours::green);

        g.drawText(message.getMidiNoteName(note_num, true, true, 1), 0, 0, note_length, 20, juce::Justification::centred, true);

    }

    void resized() override {

        //constrainer.setMinimumOnscreenAmounts(getHeight(), getWidth(),
          //  getHeight(), getWidth());


        //constrainer.setMaximumSize(100, 100);


    }

    void mouseDown(const juce::MouseEvent& event) override
    {

        //mouse_down = true;
        //xx = event.x;
        //yy = event.y;

        myDragger.startDraggingComponent(this, event);

        //beginLasso(event, this);

    }


    void mouseDrag(const juce::MouseEvent& event) override
    {



        //myConstraint.setMaximumHeight(event.y);
        //        dragLasso(event);


    

        myDragger.dragComponent(this, event, &constrainer);

        //myDragger.dragComponent(this, event, nullptr);
        /**f(mouse_down)
        {
            x_width = event.x;
            y_height = event.y;

            repaint();

        }
        */

        //repaint();

    }


private:

    int note_length = 0;

    int note_height = 0;

    double thisTimeStamp = 0;

    double nextTimeStamp = 0;

    juce::MidiMessage message;

    int note_num = 1;

    juce::ComponentDragger myDragger;

    juce::ComponentBoundsConstrainer constrainer;

};


