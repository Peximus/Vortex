#pragma once

#include <JuceHeader.h>
#include "CustomViewport.h"
#include "Media.h"
#include "CustomComponent.h"
#include "CustomListbox.h"
#include "PatternListbox.h"
#include "IncrementCounter.h"
//#include "Settings.h"
#include "Clock.h"

#include "Tracker.h"

#include "PeakMeter.h"


#include "DragAndDrop.h"

//#include "CustomScrollBar.h"

#include "Info.h"

#include "Help.h"

#include "DocumentWindow.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public juce::ChangeListener, public juce::ActionListener, public juce::Slider::Listener, public juce::Timer
{
public:
    //==============================================================================
    MainComponent();


    ~MainComponent() override;

    //==============================================================================
 //   void releaseResources() override;
    //==============================================================================
    void paint (juce::Graphics& g) override;

    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void actionListenerCallback(const juce::String& message) override;
        
    void sliderValueChanged(juce::Slider* slider);

    void saveButtonClicked();

    void openButtonClicked();

    void insertButtonClicked();

    void helpButtonClicked();

    void LoadViewPort();

    void toggleButtonClicked();

    void toggleInstClicked();

    void playButtonClicked();

    void stopButtonClicked();

    void updateToggleState(juce::Button* button, juce::String name);

    void LoadMidiFile();

    void trackMenuChanged();

    void chordMenuChanged();

    void loadInstruments();

    void scanPlugins();

    void timerCallback() override;



    

private:


    CustomViewport viewport;

    CustomComponent child;

    juce::ScrollBar scrollbar{ false };

    DragAndDropTarget inst_target;

    BasicListBox listbox;

    IncrementCounter bpm;

    Clock clock;
       
   // Settings settings;

    Media media;

    Tracker tracker;

    Info info;

    PatternListBox patternlistbox;

    PeakMeter peakmeter;

    Help help;

  //  juce::LassoComponent<juce::Component> lasso;
    juce::VST3PluginFormat pluginFormat;

    std::unique_ptr<juce::PluginDirectoryScanner> scanner;

    juce::KnownPluginList knownPluginList;

    //KnownPluginList& knownPlugins;

    juce::FileSearchPath searchPath = "C:\\Program Files\\Common Files\\VST3";

    std::unique_ptr<juce::FileChooser> chooser;

    juce::String plugin;

    juce::StringArray pluginlist;

    juce::MidiMessage message;

    int num_plugin = 0;


    juce::AudioDeviceManager audioDeviceManager;


    juce::Slider zoom;

    double zoom_value;

    juce::TextButton openButton;

    juce::TextButton saveButton;

    juce::TextButton playButton;

    juce::TextButton stopButton;

    juce::TextButton toggleButton;

    juce::TextButton toggleInstType;

    int InstType = 0;

    juce::TextButton insertButton;

    juce::TextButton deleteButton;

    juce::TextButton helpButton;

    juce::ToggleButton chordButton;

    juce::ComboBox trackMenu;

    juce::ComboBox chordMenu;

    bool guimode = true;

    int viewport_y = 0;

    juce::Point<int> viewpos;

    bool toggleView = false;

    int track_length = 40;

    double ms_beat = 500;

    double thisTimeStamp = 0;

    double nextTmeStamp = 0;

    juce::MidiFile theMidiFile;

    juce::MidiMessageSequence *miditrackseq;

    int numTracks = 0;

  

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
