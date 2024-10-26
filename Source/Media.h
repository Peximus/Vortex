#pragma once
#include <JuceHeader.h>


class Media : public juce::Component, public juce::Button::Listener, public juce::ChangeBroadcaster
{


public:

    Media()
    {

        play = juce::ImageCache::getFromMemory(BinaryData::Play_png, BinaryData::Play_pngSize);
        stop = juce::ImageCache::getFromMemory(BinaryData::Stop_png, BinaryData::Stop_pngSize);
        record = juce::ImageCache::getFromMemory(BinaryData::Record_png, BinaryData::Record_pngSize);
        record_red = juce::ImageCache::getFromMemory(BinaryData::Record_Red_png, BinaryData::Record_Red_pngSize);

        play_button.setImages(false, false, true, play, 1.0f, {}, play, 1.0f, {}, play, 1.0f, {});
        stop_button.setImages(false, false, true, stop, 1.0f, {}, stop, 1.0f, {}, stop, 1.0f, {});
        record_button.setImages(false, false, true, record, 1.0f, {}, record, 1.0f, {}, record_red, 1.0f, {});


        play_button.addListener(this);
        stop_button.addListener(this);
        record_button.addListener(this);



        addAndMakeVisible(play_button);
        addAndMakeVisible(stop_button);
        addAndMakeVisible(record_button);

    }


    ~Media()
    {


    }


    void paint(juce::Graphics& g) override {

           



    }
    void buttonClicked(juce::Button* button) override
    {
        if (button == &play_button)
        {

        }

        if (button == &stop_button)
        {
            recording = false;
            stop_recording = true;

        }

        if (button == &record_button)
        {
            recording = true;
        }


        sendChangeMessage();
    }

    void resized() override {

        play_button.setBounds(0, 0, 48, 48);
        stop_button.setBounds(48, 0, 48, 48);
        record_button.setBounds(96, 0, 48, 48);

    }


    bool isRecording()
    {

        if (recording) {
            return true;
        }
        
        else { 
                return false; };

    }


private:

    bool recording = false;
    bool stop_recording = false;



     juce::Image play;
     juce::Image stop;
     juce::Image record;
     juce::Image record_red;

     juce::ImageButton play_button;
     juce::ImageButton stop_button;
     juce::ImageButton record_button;

     JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Media)


};