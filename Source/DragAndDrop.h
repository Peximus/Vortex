#pragma once
#include <JuceHeader.h>


class DragAndDropTarget : public juce::Component, public juce::DragAndDropTarget, public juce::ChangeBroadcaster {
public:
    
    DragAndDropTarget()
    {

        for (int i = 0; i < 10; i++)
        {

            instruments[i] = 1;

        }

        
        setWantsKeyboardFocus(false);

    }
    
    ~DragAndDropTarget() noexcept override = default;

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::green.withAlpha(0.2f));

        // draw a red line around the comp if the user's currently dragging something over it..
        if (somethingIsBeingDraggedOver)
        {
            g.setColour(juce::Colours::red);
            g.drawRect(getLocalBounds(), 3);
        }

        g.setColour(getLookAndFeel().findColour(juce::Label::textColourId));
        g.setFont(14.0f);
      
        
        //g.drawFittedText(message, getLocalBounds().reduced(10, 0), juce::Justification::centred, 4);

        g.drawFittedText(midi_message.getGMInstrumentName(instruments[sel_track]), getLocalBounds().reduced(10, 0), juce::Justification::centred, 4);


    }

    //==============================================================================
    // These methods implement the DragAndDropTarget interface, and allow our component
    // to accept drag-and-drop of objects from other JUCE components..

    bool isInterestedInDragSource(const SourceDetails& /*dragSourceDetails*/) override
    {
        // normally you'd check the sourceDescription value to see if it's the
        // sort of object that you're interested in before returning true, but for
        // the demo, we'll say yes to anything..
        return true;
    }

    void itemDragEnter(const SourceDetails& /*dragSourceDetails*/) override
    {
        somethingIsBeingDraggedOver = true;
        repaint();
    }

    void itemDragMove(const SourceDetails& /*dragSourceDetails*/) override
    {
    }

    void itemDragExit(const SourceDetails& /*dragSourceDetails*/) override
    {
        somethingIsBeingDraggedOver = false;
        repaint();
    }

    void itemDropped(const SourceDetails& dragSourceDetails) override
    {
        message = dragSourceDetails.description.toString();

        inst_index = message.getIntValue() - 1;

        instruments[sel_track] = inst_index;

        inst_dropped = true;

        sendChangeMessage();

        somethingIsBeingDraggedOver = false;

        repaint();
    }

    bool instUpdate()
    {
        return inst_dropped;
    }

    int instNum()
    {

        return inst_index;
    }

    void instReset()
    {

        inst_dropped = false;

    }

    void setInstNum(int instnum)
    {

        inst_index = instnum;
        
        repaint();

    }

    void setTrack(int track)
    {

        sel_track = track;

        repaint();

    }

    int getTrack()
    {

        return sel_track;

    }



private:

    juce::String message{ "Drag-and-drop some rows from the top-left box onto this component!\n\n"
                  "You can also drag-and-drop files and text from other apps" };

    bool somethingIsBeingDraggedOver = false;

    int inst_index = 0;

    bool inst_dropped = false;

    int track_num = 0;

    juce::MidiMessage midi_message;

    int instruments[20];

    int sel_track = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DragAndDropTarget)
};




