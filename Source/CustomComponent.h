#pragma once
#include <JuceHeader.h>

#include "Note.h"

class CustomComponent : public juce::Component, public juce::Timer, public juce::ChangeBroadcaster {
public:

    CustomComponent()
    {




        addMouseListener(this, true);


        //startTimer(10);

    }


    ~CustomComponent() noexcept override = default;

    void paintOverChildren(juce::Graphics& g) override {

        //g.drawRect(getLocalBounds(), 1);

        //if (midi_down)
        // {
        //    g.drawText("Midi Key Pressed", getLocalBounds(), juce::Justification::left, true);
        //}

              /*  if (keypress)
                {

                    g.setColour(juce::Colours::orangered);

                    g.fillRect(xstart, (note_number - 36) * zoom, width, zoom);
                    g.drawText(juce::String(note_number), getLocalBounds(), juce::Justification::left, true);

                }
              */

                g.setColour(juce::Colours::orange);

                juce::Line<float> line(juce::Point<float>(x, 0),
                    juce::Point<float>(x, 800));

                g.drawLine(line, 1.0f);

                //g.fillRect(0, 0, 200, 200);

            //juce::Line<float> line(juce::Point<float>(0, 620),
            //juce::Point<float>(800, 620));

            line.setStart(0, 620);

            line.setEnd(800, 620);

        g.setColour(juce::Colours::grey);

        g.drawLine(line, 1.0f);

        xtime = 0;

        for (int i = 0; i < 100; i++)
        {

            xtime += 20;

            line.setStart(xtime, 600);

            line.setEnd(xtime, 640);


            g.drawLine(line, 1.0f);

        }


        for (int i = 0; i < 10; i++)
        {

            g.drawText(juce::String(tenseconds) + "s", xten, 580, 20, 10, juce::Justification::centredLeft, true);

            tenseconds += 10;

            xten += 200;


        }



    }

    void resized() override {



        //gxstart = note_down[0][cur_note];

        //note_width = note_up[0][cur_note] - gxstart;

        //newnotes[cur_note].setBounds(gxstart, 20, note_width, height);
    }

    void mouseDown(const juce::MouseEvent& event) override
    {

        mouse_down = true;
        xx = event.x;
        yy = event.y;

        //myDragger.startDraggingComponent(this, event);

        //beginLasso(event, this);

    }


    void mouseDrag(const juce::MouseEvent& event) override
    {

//        dragLasso(event);

        //myDragger.dragComponent(this, event, nullptr);
        /**f(mouse_down)
        {
            x_width = event.x;
            y_height = event.y;

            repaint();

        }
        */

      //  repaint();

    }

    

    void timerCallback() override
    {


        x++;

        if (x >= 799)
        {
            //x = 0;

            scroll_page = true;

            sendChangeMessage();

        }

        repaint();

        if (midi_down)
        {

            width++;

        }

        time_stamp++;
    }


    void MidiNoteOn(int noteNumber)
    {

        note_number = noteNumber;

        note_down[0][cur_note] = time_stamp;

        xstart = time_stamp;

        width = 0;

        keypress = true;

        midi_down = true;

    }

    void MidiNoteOff(int noteNumber)
    {
        note_number = noteNumber;

        note_up[0][cur_note] = time_stamp;

        note_done = true;

        keypress = false;

        midi_down = false;

        gxstart = note_down[0][cur_note];

        note_width = note_up[0][cur_note] - gxstart;

        note.add(new Note());

        note[cur_note]->setLength(note_width);

        note[cur_note]->setBounds(gxstart, (note_number - 36) * zoom, note_width, zoom);

        //resized();
        note[cur_note]->setNote(noteNumber);

        addAndMakeVisible(note[cur_note]);

        cur_note++;

    }


    void addNote(int notenumber, double thisTime, double nextTime)
    {

        note.add(new Note());

        int length = (int)nextTime - thisTime;

        note[cur_note]->setLength(length);

        note[cur_note]->setHeight(zoom);

        note[cur_note]->setTimeStamp(thisTime, nextTime);

        gxstart = (int)thisTime;

        note[cur_note]->setBounds(gxstart, notenumber * zoom, length, zoom);

        note[cur_note]->setNote(notenumber);

        addAndMakeVisible(note[cur_note]);

        cur_note++;

        //repaint();
    }



    void startClock()
    {

        startTimer(50);

    }


    void stopClock()
    {

        stopTimer();

    }

    void focus()
    {

        grabKeyboardFocus();

    }

    bool scrollMidi()
    {

        return scroll_page;

    }

    void reset_Scroll(bool scroll)
    {

        scroll_page = scroll;

    }

    void set_zoom(double zoom_value)
    {

        zoom = zoom_value;

        for (auto comp : note)
        {

            comp->setHeight(zoom);

            rect = comp->getBounds();

            rect.setHeight(zoom);

            int width = (int)(comp->getNextTime() - comp->getThisTime()) * zoom;

            comp->setLength(width);

            rect.setWidth(width);

            rect.setX(comp->getThisTime() * zoom);

            rect.setY(comp->getNote() * zoom);

            comp->setBounds(rect);

        }


        repaint();

    }


private:

//    Note* newnotes = nullptr;
 

    juce::OwnedArray<Note> note;

    juce::Rectangle<int> rect;

    //Note newnotes[1000];

    int cur_note = 0;

    float x = 0, y = 0;

    int xstart = 0;

    bool keypress = false;

    int width = 0;
    int height = 20;

    int note_down[8][128] = { 0 };

    int note_up[8][128] = { 0 };

    int time_stamp = 0;

    int gxstart = 0;
    int gxfin = 0;

    bool note_drawing = false;

    bool note_done = false;

    int note_width = 0;

    int xx = 0;
    int yy = 0;
    int x_width = 0;
    int y_height = 0;

    int midi_note = 0;

    juce::Array<char> keymap = { 'q', 'w', 'e', 'r', 't', 'y', 'u'};

    bool mouse_down = false;

    bool midi_down = false;

    bool scroll_page = false;

    int note_number = 0;

    double zoom = 20;

    int xtime = 0;
   
    juce::Line<float> line;

    int tenseconds = 10;

    int xten = 20;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomComponent)

};
