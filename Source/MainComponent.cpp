#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() 
{

  
    loadInstruments();

    scanPlugins();

    //loadPlugins();



    
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1920, 1080);


 //   addAndMakeVisible(scrollbar);
    //scrollbar.setAutoHide(true);



    addAndMakeVisible(viewport);


    viewport.setViewedComponent(&child, false);
    viewport.setScrollBarsShown(true, true);
    viewport.setScrollBarThickness(10);
    viewport.setWantsKeyboardFocus(false);

    viewport.setVisible(false);



    addAndMakeVisible(tracker);

    //tracker.setVisible(false);

 
    addAndMakeVisible(listbox);


    addAndMakeVisible(inst_target);

    addAndMakeVisible(media);

    addAndMakeVisible(clock);

    tracker.addActionListener(this);

    media.addChangeListener(this);

    inst_target.addChangeListener(this);

    bpm.setup(3, 1);


    addAndMakeVisible(bpm);
   
    addAndMakeVisible(info);

    addAndMakeVisible(trackMenu);

    trackMenu.addItem("Track 1", 1);
    trackMenu.addItem("Track 2", 2);
    trackMenu.addItem("Track 3", 3);
    trackMenu.addItem("Track 4", 4);
    trackMenu.addItem("Track 5", 5);
    trackMenu.addItem("Track 6", 6);
    trackMenu.addItem("Track 7", 7);
    trackMenu.addItem("Track 8", 8);

    trackMenu.setSelectedId(1);


    trackMenu.onChange = [this] { trackMenuChanged(); };


    addAndMakeVisible(chordMenu);

    chordMenu.addItem("Minor 1-2-7", 1);
    chordMenu.addItem("Major 1-5-7", 2);

    chordMenu.setSelectedId(1);

    chordMenu.onChange = [this] { chordMenuChanged(); };



    addAndMakeVisible(zoom);
    zoom.setRange(10.0f, 200.0f, 1);
    zoom.addListener(this);

    addAndMakeVisible(&playButton);
    playButton.setButtonText("Play");
    playButton.onClick = [this] { playButtonClicked(); };

    addAndMakeVisible(&stopButton);
    stopButton.setButtonText("Stop");
    stopButton.onClick = [this] { stopButtonClicked(); };


    addAndMakeVisible(&openButton);
    openButton.setButtonText("Open");
    openButton.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible(&saveButton);
    saveButton.setButtonText("Save");
    saveButton.onClick = [this] { saveButtonClicked(); };

    addAndMakeVisible(&toggleButton);
    toggleButton.setButtonText("Toggle View");
    toggleButton.onClick = [this] { toggleButtonClicked(); };
    
    addAndMakeVisible(&insertButton);
    insertButton.setButtonText("Insert");
    insertButton.onClick = [this] { insertButtonClicked(); };

    addAndMakeVisible(&helpButton);
    helpButton.setButtonText("Help");
    helpButton.onClick = [this] { helpButtonClicked(); };

    
    addAndMakeVisible(&toggleInstType);
    toggleInstType.setButtonText("Instrument - Plugin");
    toggleInstType.onClick = [this] { toggleInstClicked(); };

    addAndMakeVisible(&chordButton);

    chordButton.setButtonText("Auto Chords");
    chordButton.onClick = [this] { updateToggleState(&chordButton, "Auto Chords");   };
    chordButton.setClickingTogglesState(true);

    // addChildComponent(lasso);

    // addAndMakeVisible(settings);
    //addAndMakeVisible(viewport);

   // viewport.setViewedComponent(&child, false);
   // viewport.setScrollBarsShown(true, true);
   // viewport.setScrollBarThickness(10);

    //info.print("Test");
    //info.print("Test2");
    //LoadMidiFile();
  
    //juce::File file = "C:\\Juce Projects\\tracker.mid";

    //tracker.loadMidiFile(file);

    //LoadViewPort();

    //addAndMakeVisible(peakmeter);
    

    addAndMakeVisible(patternlistbox);

    //startTimer(2000);


}

MainComponent::~MainComponent()
{

    
    // This shuts down the audio device and clears the audio source.
}




//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
   g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.fillAll(juce::Colours::black);



}

void MainComponent::resized()
{

 // auto bounds = getLocalBounds();
 // scrollbar.setBounds(bounds);
 // scrollbar.setBounds(300, 100, 100, 40);

    viewport.setBounds(300, 120, 800, 650);
    
    child.setBounds(0, 0, 800 * 4, 20 * 127);

//    tracker.setBounds(300, 120, 960, 800);


    tracker.setBounds(300, 120, 1200, 800);

    info.setBounds(0, 500, 200, 400);

    media.setBounds(400, 0, 144, 48);

    inst_target.setBounds(1500, 600, 200, 80);

    trackMenu.setBounds(1500, 680, 200, 20);

    chordMenu.setBounds(1350, 780, 200, 20);

    bpm.setBounds(800, 0, 48, 96);

    clock.setBounds(60, 0, 400, 50);
  
    //peakmeter.setBounds(1300, 0, 20, 200);

    listbox.setBounds(1920 - 260, 0, 260, 600);

    patternlistbox.setBounds(0, 0, 100, 400);

    zoom.setBounds(200, 900, 200, 140);

    playButton.setBounds(900, 0, 80, 30);

    stopButton.setBounds(900, 30, 80, 30);

    openButton.setBounds(600, 0, 80, 30);

    saveButton.setBounds(680, 0, 80, 30);

    toggleButton.setBounds(600, 30, 80, 30);

    toggleInstType.setBounds(1580, 0, 80, 30);

    insertButton.setBounds(680, 30, 80, 30);

    helpButton.setBounds(980, 30, 80, 30);

    chordButton.setBounds(1350, 700, 80, 30);

    //auto rect = getLocalBounds();

    //settings.setBounds(rect.removeFromLeft(proportionOfWidth(0.6f)));

    //settings.setBounds();

    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}



void MainComponent::changeListenerCallback(juce::ChangeBroadcaster* source)  {


    if (media.isRecording())
    {
        clock.startClock();
        child.startClock();
        child.focus();
    }

    if (!media.isRecording())
    {
        clock.stopClock();
        child.stopClock();
    }

    if (child.scrollMidi())
    {
    //    viewport.setViewPosition(800, 0);

    }

    if (inst_target.instUpdate())
    {

        //tracker.changeInstrument(trackMenu.getSelectedItemIndex(), inst_target.instNum());


        if (InstType == 1)
        {
            tracker.loadPluginChannel(inst_target.instNum(), trackMenu.getSelectedItemIndex());
        }
       // tracker.setInstType(InstType);

        tracker.trackType(trackMenu.getSelectedItemIndex(), InstType);

        tracker.setInstrument(trackMenu.getSelectedItemIndex(), inst_target.instNum());

        inst_target.instReset();

    }

}

void MainComponent::actionListenerCallback(const juce::String& message)
{


    if (message == "PEAK")
    {

        peakmeter.setHeight(200);

    }


}





void MainComponent::sliderValueChanged(juce::Slider* slider)
{

    {
        zoom_value = (int) zoom.getValue() / 10;

        child.set_zoom(zoom_value);

    }

}


void MainComponent::toggleButtonClicked()
{

    toggleView = toggleView ==  0 ? 1 : 0;

    if (toggleView)
    {

        tracker.setVisible(false);

        viewport.setVisible(true);

        LoadViewPort();



    }

    else
    {

        tracker.setVisible(true);

        viewport.setVisible(false);

    }

}


void MainComponent::toggleInstClicked()
{
    
        listbox.clearListBox();

        InstType = InstType == 0 ? 1 : 0;



        if (InstType)
        {
            for (int i = 0; i < pluginlist.size(); i++)
            {
                listbox.addPlugin(pluginlist[i]);
            }

        }
        else
        {
            loadInstruments();

        }


        listbox.updateListBox();

        tracker.setInstType(InstType);

}

void MainComponent::playButtonClicked()
{

    //tracker.startPlaying();

    tracker.playMidi();

}

void MainComponent::stopButtonClicked()
{

    //tracker.startPlaying();

    tracker.stopMidi();

}

void MainComponent::updateToggleState(juce::Button* button, juce::String name)
{
    auto state = button->getToggleState();
    juce::String stateString = state ? "ON" : "OFF";
    juce::String selectedString = state ? " (selected)" : "";

    juce::Logger::outputDebugString(name + " Button changed to " + stateString);
    button->setButtonText(name + selectedString);


    state ? tracker.enableChords(true) : tracker.enableChords(false);


}


void MainComponent::saveButtonClicked()
{

    tracker.saveMidiExp();

}

void MainComponent::openButtonClicked()
{

    
    chooser = std::make_unique<juce::FileChooser>("Select a MIDI file to Load...",
        juce::File{},
        "*.mid");
    auto chooserFlags = juce::FileBrowserComponent::openMode
        | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file != juce::File{})
            {

                tracker.loadMidiFile(file);
            }
        
});
  //  double test = 0.05F;

  //  info.printdouble(test);


    
    


/*
    juce::File file = "C:\\Juce Projects\\mario.mid";

   if (file.exists()) {

        juce::FileInputStream inputStream(file);
        theMidiFile.readFrom(inputStream);
        theMidiFile.convertTimestampTicksToSeconds();

        numTracks = theMidiFile.getNumTracks();

        miditrackseq = new juce::MidiMessageSequence[numTracks];

        for (int i = 0; i < numTracks; i++)
            miditrackseq[i] = *theMidiFile.getTrack(i);


     //   for (int cur_track = 0; cur_track < numTracks; cur_track++)
    //    {

        //    j = 0;

          // for (int i = 0; i < miditrackseq[1].getNumEvents() - 2; i++)
            for (int i = 0; i < 40; i++)
            {

                juce::MidiMessage currMsg = miditrackseq[1].getEventPointer(i)->message;

                if (currMsg.isNoteOn())
           
                {

                    int stamp = (int)(currMsg.getTimeStamp() * 1000.0f);

        //            int stamp = (int) currMsg.getTimeStamp() / 500.0f;


                info.printdouble(stamp);

               // midi_track[cur_track][j][row] = currMsg.getNoteNumber();

               // if (currMsg.getTimeStamp() == nextMsg.getTimeStamp())

            }
        }
    }
  */  
}


void MainComponent::insertButtonClicked()
{
    patternlistbox.addPattern(bpm.getinc());

}

void MainComponent::helpButtonClicked()
{

    auto* basicWindow = new BasicWindow("Help", juce::Colours::black, 7, true);
    
    //basicWindow->setBounds(720, 280, 600, 400);

    basicWindow->centreWithSize(600, 400);

    basicWindow->setContentComponent(&help, false);

    basicWindow->setVisible(true);
   

}


// dw = new juce::DocumentWindow("Help", juce::Colours::black, 7, true);

   // dw->setUsingNativeTitleBar(true);
   // dw->setBounds(720, 280, 600, 400);
   // dw->setVisible(true);

   // dw->setContentComponent(&info, true);

    //basically you'd have another component you'd set as the Document Window's content component, and draw into that


void MainComponent::LoadViewPort()
{

//    for (int track = 0; track < 3; track++)
  //  {

        int track = 1;

        for (int index = 0; index < 127; index++)
        {

            int notedata = tracker.getTrackerNote(track, index);

            int note = LOBYTE(HIWORD(notedata));

            if (note > 0)
            {

                thisTimeStamp = index * ms_beat;

                nextTmeStamp = thisTimeStamp + 500;

                child.addNote(note, thisTimeStamp, nextTmeStamp);

            }

        }

   // }

}

void MainComponent::trackMenuChanged()
{
    juce::Colour textColour;

    inst_target.setTrack(trackMenu.getSelectedId());


}

void MainComponent::chordMenuChanged()
{

    int menu = chordMenu.getSelectedId();


}





void MainComponent::timerCallback()
{

    peakmeter.setHeight(42);

}


void MainComponent::loadInstruments()
{
    for (int i = 0; i <= 127; i++)
    {
        listbox.addPlugin(message.getGMInstrumentName(i));
    }
}

void MainComponent::scanPlugins()
{
    scanner.reset(new juce::PluginDirectoryScanner(knownPluginList,
        pluginFormat,
        searchPath,
        true,
        juce::File(),
        true));


    while (scanner->scanNextFile(true, plugin))

    {
        juce::File file = plugin;

        auto plugin_name = file.getFileNameWithoutExtension();

        //   listbox.addPlugin(plugin_name);

        pluginlist.add(plugin_name);

       // listbox.addPlugin(plugin_name);

        tracker.addPlugin(plugin);

    }


    num_plugin = pluginlist.size();

}

/*/void MainComponent::LoadMidiFile()
{

    juce::File file = "C:\\Juce Projects\\queen.mid";

    if (file.exists()) {

        juce::FileInputStream inputStream(file);
        theMidiFile.readFrom(inputStream);
        //theMidiFile.convertTimestampTicksToSeconds();

        numTracks = theMidiFile.getNumTracks();
        tracks = new juce::MidiMessageSequence[numTracks];

        for (int i = 0; i < numTracks; i++)
            tracks[i] = *theMidiFile.getTrack(i);

    }
    // });


/*    for (int i = 0; i < numTracks; i++)
    {
        int numTrackEvents = tracks[i].getNumEvents();
        info.print("Track #" + std::to_string(i) + " NumTrack Events #" + std::to_string(numTrackEvents));

        for (int j = 0; j < tracks[i].getNumEvents(); j++)

            info.print(juce::String(std::to_string(j)) + " @" + std::to_string(tracks[i].getEventPointer(j)->message.getTimeStamp()) + " " + tracks[i].getEventPointer(j)->message.getDescription());

     }
            


        info.printdouble(tracks[5].getEventPointer(1)->message.getTimeStamp());


    
    


    for (int i = 0; i < numTracks; i++)
    {


        for (int j = 0; j < tracks[i].getNumEvents(); j++)
        {

            juce::MidiMessage currMsg = tracks[i].getEventPointer(j)->message;

            if (currMsg.isNoteOn())
            {
                alltracks.addEvent(currMsg);

            }

            if (currMsg.isNoteOff())
            {
                alltracks.addEvent(currMsg);

            }
        }

    }


//    child.addNote(1, 1, 100);


//    for (int i = 0; i < numTracks; i++)
//    {

        tracks[5].updateMatchedPairs();


        for (int j = 0; j < tracks[5].getNumEvents(); j++)
        {

            juce::MidiMessage currMsg = tracks[5].getEventPointer(j)->message;

            thisMessageTimestamp = currMsg.getTimeStamp();

            nextMessageTimestamp = tracks[5].getTimeOfMatchingKeyUp(j);

            child.addNote(currMsg.getNoteNumber(), thisMessageTimestamp, nextMessageTimestamp);

            if (currMsg.isNoteOn())
            {
                tracker.addMidiMsg(currMsg);
            }

            if (currMsg.isNoteOff())
            {
                tracker.addMidiMsg(currMsg);
            }


        }

        tracker.trackerRepaint();
        
  //  }




        */







