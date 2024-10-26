#pragma once
#include <JuceHeader.h>

#include "DocumentWindow.h"

//#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
//#define MAKEINT(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
//#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
//#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
//#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
//#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))


#define MAKELONG(a, b) ((long long)(a) << 32 | (long long)(b) & 0Xffffffff)

#define MAKEINT(a, b) ((int)(a) << 16 | (int)(b) & 0xffff)

#define MAKEWORD(a, b) ((short)(a) << 8 | (short)(b) & 0x00ff)

#define LOBYTE(w) ((short)(w) & 0xff)
#define HIBYTE(w) (((short)(w) >> 8) & 0xff)

#define LOWORD(w) ((int)(w) & 0x0ffff)
#define HIWORD(w) (((int)(w) >> 16) & 0xffff)

#define LOINT(w) ((long long)(w) & 0xffffffff)
#define HIINT(w) (((long long)(w) >> 32) & 0xffffffff)


#define MAKENIB(a, b) (a << 4 | b & 0x0f)

#define HINIB(w) (w >> 4 & 0x0f)
#define LONIB(w) (w & 0x0f)


class Tracker : public juce::ActionBroadcaster, private juce::MidiInputCallback, public juce::Thread, private juce::ScrollBar::Listener, public juce::AudioAppComponent, public juce::Timer
{
public:

    Tracker() : Thread("Midi Player")
    {


        //z = MAKEWORD(10, 20);

      

        //a = HIBYTE(z);

        //b = LOBYTE(z);
        

      //  z = MAKEINT(MAKEWORD(10, 20), MAKEWORD(30, 40));

      //  a = HIBYTE(HIWORD(z));

      //  b = LOBYTE(HIWORD(z));

      //  c = HIBYTE(LOWORD(z));

      //  d = LOBYTE(LOWORD(z));

          z = MAKELONG(MAKEINT(MAKEWORD(10, 20), MAKEWORD(30, 40)), MAKEINT(MAKEWORD(50, 60), MAKEWORD(70, 80)));

          a = HIBYTE(HIWORD(HIINT(z)));

          b = LOBYTE(HIWORD(HIINT(z)));

          c = HIBYTE(LOWORD(HIINT(z)));
          
          d = LOBYTE(LOWORD(HIINT(z)));


          e = HIBYTE(HIWORD(LOINT(z)));

          f = LOBYTE(HIWORD(LOINT(z)));

          gg = HIBYTE(LOWORD(LOINT(z)));

          h = LOBYTE(LOWORD(LOINT(z)));

          //  a = HIINT(HIWORD(LOBYTE(z)));

        //z = MAKEWORD(10, 20);


        //a = HIBYTE(z);

        //b = LOBYTE(z);


       // z = 0xffffffff;

//        z = MAKELONG(10, 20);
//
 //       a = HIINT(z);
//        b = LOINT(z);


      //  z = MAKEINT(10, 20);

      //  a = HIWORD(z);
      //  b = LOWORD(z);

        //        z = MAKELONG(10, 20);

//        a = HIINT(z);

       // z = MAKELONG(10, 20);

        //z = MAKEINT(10, 20);

        //a = HIWORD(z);
        //b = LOWORD(z);

        


        // Some platforms require permissions to open input channels so request that here
        if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
            && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
        {
            juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
                [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
        }
        else
        {
            // Specify the number of input and output channels that we want to open
            setAudioChannels(2, 2);
        }



        for (int i = 0; i < 10; i++)
        {

            instruments[i] = 1;

        }


        miditrackseq = new juce::MidiMessageSequence[numTracks];


        for (int i = 0; i < numTracks; i++)
        {
            tracks.add(new juce::Array<long long>);

        }
    

        int note_init = MAKEINT(MAKEWORD(BLANK, 0), MAKEWORD(0, 0));

        long long data = MAKELONG(0, note_init);

        for (int i = 0; i < numTracks; i++)
        {
            for (int j = 0; j < 64; j++)
            {
                tracks[i]->add(data);

            }
        }
        midi_tracks.add(new juce::MidiBuffer);
        midi_tracks.add(new juce::MidiBuffer);
        midi_tracks.add(new juce::MidiBuffer);
        midi_tracks.add(new juce::MidiBuffer);

        
        
        //plugins.add(new std::unique_ptr<juce::AudioPluginInstance>);
        //plugins.add(new std::unique_ptr<juce::AudioPluginInstance>);

        //racks.getUnchecked(0) = { 1, 2, 3 }; // Example initialization
        //auto midiInputs = juce::MidiInput::getAvailableDevices();

        //midiIn = juce::MidiInput::openDevice(0, this);

        //midiIn->start();

        //miditrackseq = new juce::MidiMessageSequence[numTracks];

        midiOut = juce::MidiOutput::openDevice(0);

        // addChord(63, 64, 65, 0);

        // addChord(73, 74, 75, 1);

        //addKeyListener(this);


        scrollbar.setAutoHide(false);

        addAndMakeVisible(scrollbar);

        scrollbar.setVisible(true);

        scrollbar.addListener(this);

        scrollbar.setRangeLimits(0, 63, juce::NotificationType::sendNotification);

        setWantsKeyboardFocus(true);

        juce::Timer::callAfterDelay(100, [&] { grabKeyboardFocus(); });

        scrollbar.toFront(true);

        //startTimer(50);

    }


    ~Tracker() override
    {

        shutdownAudio();


        scrollbar.removeListener(this);

        stopThread(2000);
    }

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {




        sampleRateHost = sampleRate;

        samplesPerBlock = samplesPerBlockExpected;

       // loadPluginInstance();

       // plugin_instance1->prepareToPlay(sampleRate, samplesPerBlockExpected);

      //  plugin_instance2->prepareToPlay(sampleRate, samplesPerBlockExpected);


        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()
    }

    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
    {

        
        auto proxy = juce::AudioBuffer<float>(bufferToFill.buffer->getArrayOfWritePointers(), bufferToFill.buffer->getNumChannels(), bufferToFill.startSample, bufferToFill.numSamples);


        auto buffer = juce::AudioBuffer<float>(bufferToFill.buffer->getNumChannels(), bufferToFill.numSamples);


     //   auto second = juce::AudioBuffer<float>(bufferToFill.buffer->getNumChannels(), bufferToFill.numSamples);

       

      //  plugin_instance1->processBlock(first, *midi_tracks[1]);


      //  plugin_instance2->processBlock(second, *midi_tracks[2]);

        
        for(int track = 0; track < 16; track++)

        { 
            if (plugins[track])
            {

                plugins[track]->processBlock(buffer, *midi_tracks[track]);

                for (int i = 0; i < bufferToFill.numSamples; i++)
                {

                    float input1 = proxy.getSample(0, i);

                    float input2 = buffer.getSample(0, i);

                    float output = input1 + input2;

                    output *= 0.6f;

                    proxy.setSample(0, i, output);
                }

            }
        }
        
        


        

        // Your audio-processing code goes here!

        // For more details, see the help for AudioProcessor::getNextAudioBlock()

        // Right now we are not producing any data, in which case we need to clear the buffer
        // (to prevent the output of random noise)
        //bufferToFill.clearActiveBufferRegion();
    }

    void releaseResources()
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
    }


    void paint(juce::Graphics& g) override
    {


        g.setColour(juce::Colours::red);

        g.drawRect(getLocalBounds(), 1);
       // g.setColour(juce::Colours::red);

        //int i = tracks[1]->getUnchecked(0);

     //   int index = tracks[0]->getUnchecked(1);
//
       int size = tracks[0]->size();

        //tracks[0]->set(1, 64);

      //  int numtracks = tracks.size();


    //    g.drawText("Int = " + juce::String(i), 900, 200, 250, 10, juce::Justification::left, true);
        //g.drawText("Instrument Type =  " + juce::String(track_type[cursor_track]), 700, 200, 450, 10, juce::Justification::left, true);


        //g.drawText(juce::String(plugin_file[0]), 700, 220, 450, 10, juce::Justification::left, true);

        //g.drawText(error_message, 700, 240, 450, 10, juce::Justification::left, true);

      //  g.drawText(juce::String(numOutputChannels), 700, 260, 450, 10, juce::Justification::left, true);



       // g.drawText(juce::String::formatted("%.8x", z), 700, 260, 450, 10, juce::Justification::left, true);

       // g.drawText(juce::String(a), 700, 280, 450, 10, juce::Justification::left, true);

       // g.drawText(juce::String(b), 700, 300, 450, 10, juce::Justification::left, true);

       // g.drawText(juce::String(c), 700, 320, 450, 10, juce::Justification::left, true);

       // g.drawText(juce::String(d), 700, 340, 450, 10, juce::Justification::left, true);

       // g.drawText(juce::String(e), 700, 360, 450, 10, juce::Justification::left, true);

       // g.drawText(juce::String(f), 700, 380, 450, 10, juce::Justification::left, true);

       // g.drawText(juce::String(gg), 700, 400, 450, 10, juce::Justification::left, true);

       // g.drawText(juce::String(h), 700, 420, 450, 10, juce::Justification::left, true);
        //   g.drawText("Index = " + juce::String(index), 900, 240, 250, 10, juce::Justification::left, true);

     //   g.drawText("numtracks = " + juce::String(numtracks), 900, 260, 250, 10, juce::Justification::left, true);

        // g.drawText("Start Col = " + juce::String(start_col), 900, 240, 250, 10, juce::Justification::left, true);
     //   g.drawText("Start Note = " + juce::String(start_note), 900, 260, 250, 10, juce::Justification::left, true);

     //   g.drawText("Screen Rows = " + juce::String(screen_rows), 900, 280, 250, 10, juce::Justification::left, true);

   //     g.drawText("Note Row = " + juce::String(note_row), 900, 300, 250, 10, juce::Justification::left, true);
        

      // g.setColour(juce::Colour::fromRGB(169, 169, 169));
        
      //  g.drawLine(0, 0, 0, 800, 1.0f);

      //  g.drawRect(36, 0, track_width, 800);

      //  g.drawRect(track_width + 36, 0, track_width, 800);

      //  g.drawRect(track_width * 2 + 36, 0, track_width, 800);

      //  g.drawRect(track_width * 3 + 36, 0, track_width, 800);

        /*  xbord = 0;

        for (int i = 0; i < 6; i++)
        {
            g.fillRect(xbord, 0, 10, 800);

            xbord += 165;

        }
      */
      


            g.setColour(juce::Colours::grey);

            g.setFont(24.0f);

            
            int num_note = 0;

            long long note_data = 0;

            int status = 0;

            int y_cell = 0;


            int index = index_start;

            for (int y_cell = 0; y_cell < draw_end; y_cell++)
            {


                if (y_cell > draw_start)
                {

                    //g.drawText(juce::String(index), 400, ycell * cell_height, cell_width, cell_height, juce::Justification::left, true);
                   



                    for (x_cell = 0; x_cell < tracks.size(); x_cell++)
                    {

                        cell.setX((x_cell * cell_width) + window_offset);

                        cell.setY(y_cell * cell_height);

                        cell.setWidth(cell_width);

                        cell.setHeight(cell_height);


                        //if (index <= tracks[x_cell]->size())
                       // {
                        note_data = tracks[x_cell]->getUnchecked(index);



                        num_note = LOBYTE(HIWORD(LOINT(note_data)));

                        status = HIBYTE(HIWORD(LOINT(note_data)));




                        //  status = LOBYTE(LOWORD(HIINT(note_data)));

                        note = midi_message.getMidiNoteName(num_note, true, true, 3);


                        switch (status) {

                        case MIDI:
                            g.setColour(juce::Colours::grey);
                            g.drawText(note, cell, juce::Justification::left, true);
                            break;

                        case INST:
                            g.setColour(juce::Colours::blue);
                            g.drawText(note, cell, juce::Justification::left, true);
                            break;
                        case CHANGE:
                            g.setColour(juce::Colours::red);
                            g.drawText(note, cell, juce::Justification::left, true);
                            break;
                        case BLANK:
                            g.setColour(juce::Colours::grey);
                            g.drawText("---", cell, juce::Justification::left, true);
                            break;

                            //default:
                        }

                        // note_off = MAKEINT(MAKEWORD(NOTE_OFF, note), MAKEWORD(0, 0));

                        int note_display = HIBYTE(HIWORD(HIINT(note_data)));

                        if (note_display == NOTE_OFF)
                        {
                            g.setColour(juce::Colours::aquamarine);
                            g.drawText("---", cell, juce::Justification::left, true);


                        }


                        if (note_display == NOTE_OFF_SYNTH)
                        {
                            g.setColour(juce::Colours::aquamarine);
                            g.drawText("---", cell, juce::Justification::left, true);


                        }




                    }

                    


                    if (index >= tracks[0]->size())
                    {
                        break;
                    }

                    else
                    {

                        

                        g.drawText(juce::String::formatted("%.4d", index), 0, y_cell * cell_height, cell_width, cell_height, juce::Justification::left, true);
                        index++;
                    }




                }
            

               // if (index < tracks[x_cell]->size())
             //   {

                //    index++;

             //   }
           

            }
                   
                

              //  index++;
            

        //    for (int x_col = 0; x_col < 5; ++x_col);
          //  {


                

                //drawCell(g, x, d_start, tracks[i]->getUnchecked(0));
             //   drawCell(g, x_col, 2, 63);

                //x += 4;

            //}

         /*/   for (int v = 10; v < 12; ++v)
            { 
            
                drawCell(g, v, 10, 63);
            
            }
            int x = 10;
            
           
  
            x++;

            drawCell(g, x, 10, 63);


           // drawTracks(g, draw_start);
           */
          
             
            g.setColour(juce::Colours::black);

            g.setOpacity(0.5f);

            g.fillRect(cur_x, font_height * 16, cell_width, 20);

            /*
            

            xcell = (xx / 175) * 175;

            ycell = (yy / 20) * 20;

            xclip = xx / 175;

            yclip = yy / 20;

            dcell_x = ((xx - xcell ) + xdrag) / 175;

            dcell_y = ydrag / 20;

            width = 175 + (dcell_x * 175);

            height = 20 + (dcell_y * 20);

            g.setColour(juce::Colours::blue);

            g.setOpacity(0.5f);

            //g.fillRect(xx / 175, ycell, width, height);

            g.fillRect(xcell, ycell, width, height);
            */

        if (cursor_draw)
        {
            cursor_draw = false;

            xcell = (xx / 40) * 40;

            ycell = (yy / 20) * 20;

            g.setColour(juce::Colours::blue);

            g.setOpacity(0.5f);

            g.fillRect(xcell, ycell, cell_width * 3, font_height);


        }



    }

/*/    bool drawTracks(juce::Graphics& g, int d_start)
    {

        for (int i = 0; i < tracks.size(); i++);
        {

            int x = 0;
            
            //drawCell(g, x, d_start, tracks[i]->getUnchecked(0));
            drawCell(g, 0, x, 63);

            x+=4;

        }

        
        /*int numtracks = tracks.size();


        int i = tracks[1]->getUnchecked(0);

        int index = tracks[0]->getUnchecked(1);

        int size = tracks[0]->size();

        tracks[0]->set(1, 64);

        int numtracks = tracks.size();
        

        return true;

    }
    */
   
    void drawCell(juce::Graphics& g, int x_cell, int y_cell, int num_note)
    {

        g.saveState();

//        cell.setX((x_cell * cell_width) + window_offset);
        cell.setX(x_cell * cell_width);

        cell.setY(y_cell * cell_height);

        cell.setWidth(cell_width);

        cell.setHeight(cell_height);
     
        note = midi_message.getMidiNoteName(num_note, true, true, 3);

        g.drawText(note, cell, juce::Justification::left, true);

        g.restoreState();

    }

/*/    bool drawTrack(juce::Graphics& g, int x_cell, int y_cell)
    {
        int i = 0;

        int cell_y = y_cell;

        while (i < tracks[0]->size())
        {

            cell.setX((x_cell * cell_width) + window_offset);

            cell.setY(cell_y * cell_height);

            cell.setWidth(cell_width);


            cell.setHeight(cell_height);

            cell_y++;
            if (cell_y > draw_end)
                break;

           // note = midi_message.getMidiNoteName(track[i], true, true, 3);

            g.drawText(note, cell, juce::Justification::left, true);
        }
        return true;

    }
    */

    void setup(juce::Graphics& g)
    {
        int xbord = 0;

        for (int i = 0; i < 6; i++)
        {
            g.fillRect(xbord, 0, 10, 800);

            xbord += 165;
        }

        g.setColour(juce::Colours::grey);

        g.setFont(24.0f);

        g.setColour(juce::Colours::black);

        g.setOpacity(0.5f);

        g.fillRect(cur_x, font_height * 15, cell_width, 20);

        g.setColour(juce::Colours::red);

        g.drawText("Row = " + juce::String(row), 900, 200, 250, 10, juce::Justification::left, true);
        g.drawText("Col = " + juce::String(col), 900, 220, 250, 10, juce::Justification::left, true);

        g.drawText("Start Col = " + juce::String(start_col), 900, 240, 250, 10, juce::Justification::left, true);
        g.drawText("Start Note = " + juce::String(start_note), 900, 260, 250, 10, juce::Justification::left, true);

        g.drawText("Screen Rows = " + juce::String(screen_rows), 900, 280, 250, 10, juce::Justification::left, true);

        g.drawText("Note Row = " + juce::String(note_row), 900, 300, 250, 10, juce::Justification::left, true);

        g.drawText("Num Rows = " + juce::String(num_rows), 900, 320, 250, 10, juce::Justification::left, true);


        g.setColour(juce::Colour::fromRGB(169, 169, 169));

        g.drawLine(0, 0, 0, 800, 1.0f);

        g.drawRect(36, 0, track_width, 800);

        g.drawRect(track_width + 36, 0, track_width, 800);

        g.drawRect(track_width * 2 + 36, 0, track_width, 800);

        g.drawRect(track_width * 3 + 36, 0, track_width, 800);
    }


    void resized() override {


        auto bounds = getLocalBounds();

        scrollbar.setBounds(bounds.removeFromRight(20));

    }

/*/    void MainComponent::releaseResources()
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
    }
*/

    //bool keyPressed(const juce::KeyPress& key, Component* originatingComponent) override
    bool keyPressed(const juce::KeyPress& key) override
    {

        k = key.getKeyCode();
        
        bool ctrl = (key.getModifiers().isCtrlDown());


        switch (k)
        {
            case 88: // X
            {
            
                if (ctrl)
                {
                    
                    clip_true = true;

                    cut_clip();

                }


            }
            break;

            case 67: // C
            {

                if (ctrl)
                {

                    clip_true = true;

                    copy_clip();


                }


            }
            break;

            case 86: // V
            {

                if (ctrl)
                {

                    if (clip_true)
                    {

                        paste_clip();

                        clip_true = false;

                    }


                }


            }
            break;

        }

        ctrl = false;

        switch (k)
        {
            case 65573: // left
            {


                cursor_track--;

                cursor_track < 0 ? cursor_track = numTracks - 1: cursor_track = cursor_track;

                cur_x = (cursor_track * track_width) + window_offset;
                
                /*/cur_index--;

                cur_index < 0 ? (cursor_track--, cur_index = 2) : cursor_track = cursor_track;

                cursor_track < 0 ? (cursor_track = 3, cur_index = 2) : cursor_track = cursor_track;

                cur_x = (cursor_track * track_width) + (cur_index * 65) + 44;
                */

            }
            break;

            case 65575: // right
            {


                cursor_track++;

                cursor_track >= numTracks ? cursor_track = 0 : cursor_track = cursor_track;

                cur_x = (cursor_track * track_width) + window_offset;

               

                /**cur_index++;

                cur_index > 2 ? (cursor_track++, cur_index = 0) : cursor_track = cursor_track;

                cursor_track > 3 ? (cursor_track = 0, cur_index = 0) : cursor_track = cursor_track;

                cur_x = (cursor_track * track_width) + (cur_index * 65) + 44;
                */

            }
            break;

            case 65574: // up
            {

        

                if (note_index > 0)
                {

                    note_index--;

                    scrollDown();

                }


            }
            break;

            case 65576: // down
            {

                if (note_index < tracks[0]->size() - 1)

                {
                    note_index++;

                    scrollUp();
                }

            }
            break;

            case 81: // q
            {
                notenumber = 63;
                
                keydown = true;

            }
            break;

            case 50: // 2
            {
                notenumber = 64;

                keydown = true;

            }
            break;

            case 87: // W
            {
                notenumber = 65;

                keydown = true;

            }
            break;

            case 51: // 3
            {
                notenumber = 66;

                keydown = true;

            }
            break;

            case 69: // E
            {
                notenumber = 67;

                keydown = true;

            }
            break;

            case 52: // 4
            {
                notenumber = 68;

                keydown = true;

            }
            break;

            case 82: // R
            {
                notenumber = 69;

                keydown = true;

            }
            break;

            case 53: // 5
            {
                notenumber = 70;

                keydown = true;

            }
            break;

            case 84: // T
            {
                notenumber = 71;

                keydown = true;

            }
            break;

            case 54: // 6
            {
                notenumber = 72;

                keydown = true;

            }
            break;

            case 89: // Y 
            {
                notenumber = 73;

                keydown = true;

            }
            break;

            case 55: // 7 
            {
                notenumber = 74;

                keydown = true;

            }
            break;

            case 85: // U 
            {
                notenumber = 74;

                keydown = true;

            }
            break;

            case 56: // 8 
            {
                notenumber = 74;

                keydown = true;

            }
            break;

            case 73: // I 
            {
                notenumber = 74;

                keydown = true;

            }
            break;

            case 57: // 9 
            {
                notenumber = 74;

                keydown = true;

            }
            break;

            case 79: // O 
            {
                notenumber = 74;

                keydown = true;

            }
            break;

            case 48: // 0 
            {
                notenumber = 74;

                keydown = true;

            }
            break;

            case 80: // P 
            {
                notenumber = 74;

                keydown = true;

            }
            break;

        }


        if (keydown)
        {


            if (!chord_mode)
            {


                if (track_type[cursor_track] == 1)
                {

                    auto msg = juce::MidiMessage::noteOn(0, notenumber, (juce::uint8)100);

                    midi_tracks[cursor_track]->addEvent(msg, 0);


                    note_on = MAKELONG(MAKEINT(MAKEWORD(0, 0), MAKEWORD(0, 0)), MAKEINT(MAKEWORD(INST, notenumber), MAKEWORD(0, 0)));

                    notedata = MAKELONG(0, note_on);

                    tracks[cursor_track]->setUnchecked(note_index, notedata);


                    note_off = MAKEINT(MAKEWORD(NOTE_OFF_SYNTH, notenumber), MAKEWORD(0, 0));

                    notedata = MAKELONG(note_off, MAKEINT(MAKEWORD(BLANK, 0), MAKEWORD(0, 0)));

                    tracks[cursor_track]->setUnchecked(note_index + 4, notedata);


                }

                else

                {

                    auto msg = juce::MidiMessage::noteOn(0, notenumber, (juce::uint8)100);

                    note_on = MAKEINT(MAKEWORD(MIDI, notenumber), MAKEWORD(0, 0));

                    
                    note_off = MAKEINT(MAKEWORD(NOTE_OFF, notenumber), MAKEWORD(0, 0));

                    notedata = MAKELONG(0, note_on);

                    tracks[cursor_track]->setUnchecked(note_index, notedata);

                    notedata = MAKELONG(note_off, 0);

                    tracks[cursor_track]->setUnchecked(note_index + 4, notedata);

                    midiOut->sendMessageNow(msg);
                }


                
                
                //midi.addEvent(msg, 0);

                //midiOut->sendMessageNow(msg);


                //midi_track[cursor_track][cur_index][note_row] = notenumber;

                //msg = juce::MidiMessage::noteOff(cursor_track, notenumber, (juce::uint8)100);

                notebuffer.add(notenumber);


            }

            else
            {

                switch (chordIndex)
                {
                case 0:
                {
                    auto msg = juce::MidiMessage::noteOn(cursor_track, notenumber, (juce::uint8)100);

                    midiOut->sendMessageNow(msg);

                    msg = juce::MidiMessage::noteOn(cursor_track, notenumber + 2, (juce::uint8)100);

                    midiOut->sendMessageNow(msg);

                    msg = juce::MidiMessage::noteOn(cursor_track, notenumber + 7, (juce::uint8)100);

                    midiOut->sendMessageNow(msg);

                    note_on = MAKELONG(MAKEINT(MAKEWORD(0, 0), MAKEWORD(0, 0)), MAKEINT(MAKEWORD(CHORD, notenumber), MAKEWORD(notenumber + 2, notenumber + 7)));

             

                }
                break;

                case 1:
                {
                    auto msg = juce::MidiMessage::noteOn(cursor_track, notenumber, (juce::uint8)100);

                    midiOut->sendMessageNow(msg);

                    msg = juce::MidiMessage::noteOn(cursor_track, notenumber + 5, (juce::uint8)100);

                    midiOut->sendMessageNow(msg);

                    msg = juce::MidiMessage::noteOn(cursor_track, notenumber + 7, (juce::uint8)100);

                    midiOut->sendMessageNow(msg);

                    note_on = MAKELONG(MAKEINT(MAKEWORD(0, 0), MAKEWORD(0, 0)), MAKEINT(MAKEWORD(CHORD, notenumber), MAKEWORD(notenumber + 5, notenumber + 7)));



                }
                break;

                default:
                    break;
                }


                //msg = juce::MidiMessage::noteOff(cursor_track, notenumber, (juce::uint8)100);




            }


            juce::Timer::callAfterDelay(1000, [&] {

                noteremove = notebuffer[0];

                notebuffer.remove(0);

                auto msgoff = juce::MidiMessage::noteOff(0, noteremove, (juce::uint8)100);

                midi_tracks[cursor_track]->addEvent(msgoff, 0);
                
                //midi.addEvent(msgoff, 0);

                //midiOut->sendMessageNow(msgoff);
                
                });

                keydown = false;

        }


        repaint();

        return 0;
    }


    /*/bool keyStateChanged(bool isKeyDown, Component* originatingComponent) override
    {
        if (isKeyDown)
        {


            //            for (int i = 0; i < 5; i++)
              //          {
/*            if (juce::KeyPress::isKeyCurrentlyDown()
            {

                if (!keypress)
                {
                    keypress = true;


                }

            }
            
        }
        else
        {
            /*
            if (!juce::KeyPress::isKeyCurrentlyDown(keymap[0]))
            {


            }
            
        }

        return false;
    }
    */


    void print(juce::String string)
    {

        message.add(string);

        row = 0;

        repaint();

    }

    void addChord(int note1, int note2, int note3, int row)
    {
        auto msg = juce::MidiMessage::noteOn(midiChannel, note1, (juce::uint8)100);

        timeStamp = (60000 / bpm) * row;

        msg.setTimeStamp(timeStamp);

        miditrackseq[0].addEvent(msg);

        msg = juce::MidiMessage::noteOn(midiChannel, note2, (juce::uint8)100);

        msg.setTimeStamp(timeStamp);

        miditrackseq[0].addEvent(msg);

        msg = juce::MidiMessage::noteOn(midiChannel, note3, (juce::uint8)100);

        msg.setTimeStamp(timeStamp);

        miditrackseq[0].addEvent(msg);

    }

    void addMidiMsg(juce::MidiMessage msg)
    {
        miditrackseq[0].addEvent(msg);
    }

    void trackerRepaint()
    {
        repaint();
    }


    void grabFocus()
    {
        setWantsKeyboardFocus(true);
        grabKeyboardFocus();
    }

    int Round(int toRound)
    {

        int rem = toRound % 10;

        return rem >= 5 ? toRound - rem + 10 : toRound - rem;
    }

    void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message) override
    {

        midi.addEvent(message, 0);


        if (message.isNoteOn())
        {

            //midiOut->sendMessageNow(message);

        }

        if (message.isNoteOff())
        {

          //  auto msg = juce::MidiMessage::programChange(message.getChannel(), 100);

            //midiOut->sendMessageNow(message);
        }

    }

    void changeInstrument(int channel, int instNum)
    {

        auto msg = juce::MidiMessage::programChange(channel, instNum);

        midiOut->sendMessageNow(msg);

        grabKeyboardFocus();

    }

   
    void setTrackInstrument()
    {

        auto msg = juce::MidiMessage::programChange(cursor_track, instruments[cursor_track]);

        midiOut->sendMessageNow(msg);

    }


    void run() override
    {        
        
        i = 0;

        numTrackEvents = alltracks.getNumEvents();
        
        
        while (i < numTrackEvents -1)
        {

            juce::MidiMessage currMsg = alltracks.getEventPointer(i)->message;

            juce::MidiMessage nextMsg = alltracks.getEventPointer(i + 1)->message;

            thisMessageTimestamp = currMsg.getTimeStamp();

            nextMessageTimestamp = nextMsg.getTimeStamp();

            waitTime = nextMessageTimestamp - thisMessageTimestamp;


            if (currMsg.isNoteOn())
            {

                midiOut->sendMessageNow(currMsg);

                sendActionMessage("PEAK");

            }

            if (currMsg.isNoteOff())
            {

                midiOut->sendMessageNow(currMsg);

            }


            wait((int)waitTime);

            i++;
        
        }

        return;
    }


 
    void startPlaying()
    {

        for (int cur_track = 0; cur_track < 2; cur_track++)
        {

            for (int i = 0; i < track_length; i++)
            {

                for (int j = 0; j < 3; j++)
                {

                    int note = midi_track[cur_track][j][i];

                    if (note > 0)
                    {

                        timeStamp = i * ms_beat;

                        msg = juce::MidiMessage::noteOn(midiChannel, note, (juce::uint8)100);

                        msg.setTimeStamp(timeStamp);

                        alltracks.addEvent(msg);

                        if (i == 0)
                        {
                            timeStamp = ms_duration;
                        }

                        else
                        {
                            timeStamp = i * ms_duration;
                        }

                        msg = juce::MidiMessage::noteOff(midiChannel, note, (juce::uint8)100);

                        msg.setTimeStamp(timeStamp);

                        alltracks.addEvent(msg);

                    }


                }
            }
        }

        

        msg = juce::MidiMessage::programChange(0, 1);

        alltracks.addEvent(msg);


            startThread();

    }


    void playMidi()
    {

        startTimer(200);
    }


    void stopMidi()
    {

        stopTimer();

    }

    void saveMidi()
    {


       for (int cur_track = 0; cur_track < numTracks; cur_track++)
       {

            for (int i = 0; i < track_length; i++)
            {

                for (int j = 0; j < 3; j++)
                {

                    int note = midi_track[cur_track][j][i];

                    if (note > 0)
                    {

                        timeStamp = i * ms_beat;

                        auto msg = juce::MidiMessage::noteOn(midiChannel, note, (juce::uint8)100);

                        msg.setTimeStamp(timeStamp);

                        miditrackseq[cur_track].addEvent(msg);

                        timeStamp = i * ms_duration;

                        msg = juce::MidiMessage::noteOff(midiChannel, note, (juce::uint8)100);

                        msg.setTimeStamp(timeStamp);

                        miditrackseq[cur_track].addEvent(msg);

                    }

                }
            }

            auto msg = juce::MidiMessage::noteOn(midiChannel, 0, (juce::uint8)100);

            miditrackseq[cur_track].addEvent(msg);

       }



            juce::File file = "C:\\Juce Projects\\tracker.mid";

            if (file.exists()) {

//                file.deleteFile();

            }

            for (int cur_track = 0; cur_track < numTracks; cur_track++)
            {
                theMidiFile.addTrack(miditrackseq[cur_track]);

               
            }

            juce::FileOutputStream outputStream(file);
            
            theMidiFile.writeTo(outputStream, 2);



    }

    void saveMidiExp()
    {


        for (int cur_track = 0; cur_track < numTracks; cur_track++)
        {

            for (int i = 0; i < tracks[cur_track]->size(); i++)
            {

      
                int note = tracks[cur_track]->getUnchecked(i);

                    if (note > 0)
                    {

                        timeStamp = i * ms_beat;

                        auto msg = juce::MidiMessage::noteOn(midiChannel, note, (juce::uint8)100);

                        msg.setTimeStamp(timeStamp);

                        miditrackseq[cur_track].addEvent(msg);

                        timeStamp = i * ms_duration;

                        msg = juce::MidiMessage::noteOff(midiChannel, note, (juce::uint8)100);

                        msg.setTimeStamp(timeStamp);

                        miditrackseq[cur_track].addEvent(msg);

                    }

                
            }

          

        }



        juce::File file = "C:\\Juce Projects\\tracker.mid";

        if (file.exists()) {

  //          file.deleteFile();

        }

        for (int cur_track = 0; cur_track < numTracks; cur_track++)
        {
            theMidiFile.addTrack(miditrackseq[cur_track]);


        }

        juce::FileOutputStream outputStream(file);

        theMidiFile.writeTo(outputStream, 2);



    }


    void loadMidiFile(juce::File filename)
    {

        juce::File file = filename;

        int note = 0;

        if (file.exists()) {

            juce::FileInputStream inputStream(file);
            theMidiFile.readFrom(inputStream);
            theMidiFile.convertTimestampTicksToSeconds();

            numTracks = theMidiFile.getNumTracks();

            miditrackseq = new juce::MidiMessageSequence[numTracks];

            for (int i = 0; i < numTracks; i++)
                miditrackseq[i] = *theMidiFile.getTrack(i);


            tracks.clear(true);


            for (int i = 0; i < numTracks; i++)
            {
                  

                if (miditrackseq[i].getNumEvents() > max_track_old)
                {
                    max_track_length = miditrackseq[i].getNumEvents();
                }


                max_track_old = miditrackseq[i].getNumEvents();

            }


            int note_init = MAKEINT(MAKEWORD(BLANK, 0), MAKEWORD(0, 0));

            long long data = MAKELONG(0, note_init);


            for (int i = 0; i < numTracks; i++)
            {
                tracks.add(new juce::Array<long long>);

                for (int j = 0; j < max_track_length; j++)
                {
                    tracks[i]->add(data);
                }


            }


            for (int cur_track = 0; cur_track < numTracks; cur_track++)
            {

                for (int i = 0; i < miditrackseq[cur_track].getNumEvents(); i++)
                {

                    juce::MidiMessage currMsg = miditrackseq[cur_track].getEventPointer(i)->message;



                    if (currMsg.isNoteOn())
                    {

                        int stamp = (int)(currMsg.getTimeStamp() * 1000.0f) / 200.0f;
                        //int stamp = currMsg.getTimeStamp();


                        note = currMsg.getNoteNumber();
                     
                        if (inst_change)
                        {
                            note_on = MAKEINT(MAKEWORD(CHANGE, note), MAKEWORD(0, 0));


                            inst_change = false;
                        }
                        else
                        {
                            note_on = MAKEINT(MAKEWORD(MIDI, note), MAKEWORD(0, 0));

                        }

                        long long data = tracks[cur_track]->getUnchecked(stamp);

                        notedata = MAKELONG(HIINT(data), note_on);

                        tracks[cur_track]->setUnchecked(stamp, notedata);

                    }



                    if (currMsg.isNoteOff())
                    {
                        int stamp = (int)(currMsg.getTimeStamp() * 1000.0f) / 200.0f;

                        note = currMsg.getNoteNumber();

                        note_off = MAKEINT(MAKEWORD(NOTE_OFF, note), MAKEWORD(0, 0));

                        long long data = tracks[cur_track]->getUnchecked(stamp);

                        notedata = MAKELONG(note_off, LOINT(data));

                        tracks[cur_track]->setUnchecked(stamp, notedata);

                    
                    }

                    if (currMsg.isProgramChange())
                    {
                        programChangeNum = currMsg.getProgramChangeNumber();

                        inst_change = true;

                    }



                }
            }

        }

        repaint();
        
    
       
   }


   int getTrackerNote(int track, int index)
   {

       return tracks[track]->getUnchecked(index);

   }


   void mouseDown(const juce::MouseEvent& event) override
   {


       xx = event.x;
       yy = event.y;

       mouse_down = true;

       mouse_up = false;

       cursor_draw = true;


       repaint();

       
   }


   void mouseUp(const juce::MouseEvent& event) override
   {

       mouse_up = true;

       if (mouse_drag)
       {

           save_cells();

           mouse_drag = false;


       }

       
       height = 0;

       width = 0;

       dcell_x = 0;

       dcell_y = 0;

       xcell = 0;

       ycell = 0;

       xdrag = 0;

       ydrag = 0;
       
       

   }

   void mouseDrag(const juce::MouseEvent& event) override
   {


       cursor_draw = false;

       mouse_drag = true;

       xw = event.x;
       yh = event.y;

       xdrag = event.getDistanceFromDragStartX();

       ydrag = event.getDistanceFromDragStartY();

       repaint();

   }

   void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails & wheel) override
   {


       y_wheel = wheel.deltaY;

       if (y_wheel > y_wheel_old)
       {

           start_col > 0 ? start_col-- : (start_col = 0, start_note++);

           screen_rows += 2;

       }


       y_wheel_old = wheel.deltaY;


       repaint();

   }


   void scrollBarMoved(juce::ScrollBar* scrollBarThatHasMoved, double	newRangeStart) override
   {

       
       newRangeStart < oldRange ? start_col++ : start_col--;

       oldRange = newRangeStart;


   }

   void setInstrument(int track, int instnum)
   {

       track_instrument[track] = instnum;

       auto msg = juce::MidiMessage::programChange(track, instnum);

       midiOut->sendMessageNow(msg);


   }
      

   void cut_clip()
   {


       for (int cur_track = xcell_copy; cur_track < dcell_x_copy; cur_track++)
       {

           for (int i = 0; i < dcell_y_copy; i++)
           {

               for (int j = 0; j < 3; j++)
               {

                   int note = midi_track[cur_track][j][i];

                   if (note > 0)
                   {
                       midi_track_clip[cur_track][j][i] = midi_track[cur_track][j][i];

                       midi_track[cur_track][j][i] = 0;

                   }

               }
           }

       }

       repaint();


   }

   void copy_clip()
   {


       for (int cur_track = xcell_copy; cur_track < dcell_x_copy; cur_track++)
       {

           for (int i = 0; i < dcell_y_copy; i++)
           {

               for (int j = 0; j < 3; j++)
               {

                   int note = midi_track[cur_track][j][i];

                   if (note > 0)
                   {
                       midi_track_clip[cur_track][j][i] = midi_track[cur_track][j][i];

                   }

               }
           }

       }

       repaint();


   }

   void paste_clip()
   {

       int x_track = xclip;

       for (int cur_track = xcell_copy; cur_track < dcell_x_copy; cur_track++)
       {

           for (int i = 0; i < dcell_y_copy; i++)
           {

               for (int j = 0; j < 3; j++)
               {

                   int note = midi_track_clip[cur_track][j][i];

                   if (note > 0)
                   {
                       midi_track[x_track][j][i] = note;


                   }

               }
           }


           x_track++;
       }

       repaint();


   }


   void save_cells()
   {

       xcell_copy = xclip;

       ycell_copy = yclip;

       dcell_x_copy = xclip + dcell_x + 1;

       dcell_y_copy = dcell_y + 1;

   }

   void enableChords(bool state)
   {

       chord_mode = state;

   }

   void setChord(int value)
   {

       chordIndex = value;

   }

   void loadPluginInstance()
   {
       pluginmanager.addDefaultFormats();
       // the single .vst3 file may have multiple plugin types, so we need to deal with an array
       // of PluginDescriptions
       juce::VST3PluginFormat v3format;
       v3format.findAllTypesForFile(descs,
           R"(C:\Program Files\Common Files\VST3\JX11.vst3)");
       if (descs.size() > 0)
       {
           juce::String error;
           
           plugin_instance1 = pluginmanager.createPluginInstance(*descs[0], 44100, 512, error);
           
          
           
           
           
           
           if (!plugin_instance1)
           {
               
               //plugins.insert(0, (pluginmanager.createPluginInstance(*descs[0], 44100, 512, error)));
               //std::cout << error << "\n";
           }
           else
           {
               //std::cout << "created " << descs[0]->descriptiveName << "\n";



           }

       }

       // the single .vst3 file may have multiple plugin types, so we need to deal with an array
       // of PluginDescriptions
       v3format.findAllTypesForFile(descs2,
           R"(C:\Program Files\Common Files\VST3\bass.vst3)");
       if (descs.size() > 0)
       {
           juce::String error;

           plugin_instance2 = pluginmanager.createPluginInstance(*descs2[0], 44100, 512, error);






           if (!plugin_instance2)
           {

               //plugins.insert(0, (pluginmanager.createPluginInstance(*descs[0], 44100, 512, error)));
               //std::cout << error << "\n";
           }
           else
           {
               //std::cout << "created " << descs[0]->descriptiveName << "\n";



           }

       }

   }



   void loadPluginChannel(int file_index, int track)
   {
      
       pluginmanager.addDefaultFormats();


       descs.clear();

       // the single .vst3 file may have multiple plugin types, so we need to deal with an array
       // of PluginDescriptions
       juce::VST3PluginFormat v3format;
       v3format.findAllTypesForFile(descs, plugin_file[file_index]);
       if (descs.size() > 0)
       {
         

           plugins[track] = pluginmanager.createPluginInstance(*descs[0], 44100, 512, error);






           if (!plugins[track])
           {

               //plugins.insert(0, (pluginmanager.createPluginInstance(*descs[0], 44100, 512, error)));
               //std::cout << error << "\n";
           }
           else
           {
              error_message = descs[0]->descriptiveName;

              plugins[track]->prepareToPlay(sampleRateHost, samplesPerBlock);

              numOutputChannels = plugins[track]->getNumOutputChannels();

              audioprocessoreditor1 = plugins[track]->createEditor();


              bounds = audioprocessoreditor1->getBounds();

              auto* basicWindow = new BasicWindow(descs[0]->descriptiveName, juce::Colours::black, 7, true);

              //basicWindow->setBounds(720, 280, 600, 400);

              basicWindow->centreWithSize(bounds.getWidth(), bounds.getHeight());

              basicWindow->setContentComponent(audioprocessoreditor1, false);

              basicWindow->setVisible(true);

           }

       }

       repaint();

   }

   void addPlugin(juce::String plugin)
   {


       plugin_file.add(plugin);

   }


   void loadPluginGUI()
   {

       //info.print(descs[0]->descriptiveName);

       //info.print(descs[0]->pluginFormatName);

       //info.print(descs[0]->manufacturerName);

       audioprocessoreditor1 = plugin_instance1->createEditor();


       bounds = audioprocessoreditor1->getBounds();

       auto* basicWindow = new BasicWindow(descs[0]->descriptiveName, juce::Colours::black, 7, true);

       //basicWindow->setBounds(720, 280, 600, 400);

       basicWindow->centreWithSize(bounds.getWidth(), bounds.getHeight());

       basicWindow->setContentComponent(audioprocessoreditor1, false);

       basicWindow->setVisible(true);





       audioprocessoreditor2 = plugin_instance2->createEditor();


       bounds = audioprocessoreditor2->getBounds();

       auto* basicWindow2 = new BasicWindow(descs2[0]->descriptiveName, juce::Colours::black, 7, true);

       //basicWindow->setBounds(720, 280, 600, 400);

       basicWindow2->centreWithSize(bounds.getWidth(), bounds.getHeight());

       basicWindow2->setContentComponent(audioprocessoreditor2, false);

       basicWindow2->setVisible(true);


       
   }

   void scanPlugins()
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

       }


       num_plugin = pluginlist.size();

   }


   void timerCallback() override
   {
       


       for (int cur_track = 0; cur_track < tracks.size(); cur_track++)
       {

          long long note_data  = tracks[cur_track]->getUnchecked(note_playing);
           

          int num_note = LOBYTE(HIWORD(LOINT(note_data)));

          int status = HIBYTE(HIWORD(LOINT(note_data)));

          int data = HIBYTE(HIWORD(HIINT(note_data)));




              auto msg = juce::MidiMessage::noteOn(cur_track, num_note, (juce::uint8)100);

              auto change = juce::MidiMessage::programChange(cur_track, LOBYTE(LOWORD(HIINT(note_data))));

              status = HIBYTE(HIWORD(LOINT(note_data)));

              switch (status) {
              case INST:
                  midi_tracks[cur_track]->addEvent(msg, 0);
                  break;
              case MIDI:
                  midiOut->sendMessageNow(msg);
                  break;
              case CHANGE:
                  midiOut->sendMessageNow(change);

                  midiOut->sendMessageNow(msg);
                  break;

                  
                  //default:
              }
          

              if (data == NOTE_OFF)
              {

                  int note_remove = LOBYTE(HIWORD(HIINT(note_data)));

                  msg = juce::MidiMessage::noteOff(cur_track, note_remove, (juce::uint8)100);

                      midiOut->sendMessageNow(msg);

              }

              if (data == NOTE_OFF_SYNTH)
              {

                  int note_remove = LOBYTE(HIWORD(HIINT(note_data)));

                  msg = juce::MidiMessage::noteOff(cur_track, note_remove, (juce::uint8)100);

                  midi_tracks[cur_track]->addEvent(msg, 0);

              }

           

       }

       scrollUp();

     

       note_playing++;

       if (note_playing >= tracks[0]->size())
       {

           note_playing = 0;

           draw_start = 15;

           note_index = 0;


       }

       repaint();
       /*
       
       if (arrows.size() > 0)
       {
           arrows.remove(0);

           if (draw_start > 0)
           {
               draw_start--;
           }
           else
           {
               index_start++;
           }
           repaint();
       }
       */

   }


   void scrollDown()
   {
       if (draw_start == 0 && index_start > 0)
       {
           index_start--;
       }
       else
       {
           draw_start++;
       }

   }


   void scrollUp()
   {
       

       if (draw_start > 0)
       {
           draw_start--;
       }
       else
       {
           index_start++;
       }

   }

   void setInstType(bool type)
   {

       InstType = type;
   }


   void trackType(int track, int type)
   {

       track_type[track] = type;
   }

   enum Level {
       MIDI,
       INST,
       BLANK,
       CHANGE,
       NOTE_OFF,
       CHORD,
       NOTE_OFF_SYNTH
      
       
   };

private:


    int max_track_length = 0;

    int max_track_old = 0;

    int note_playing = 0;

    int note_index = 0;

    juce::Array<int> arrows;
    
    int x_cell = 0;

    int index = 0;

    int x_col = 0;


    juce::OwnedArray<juce::Array<long long>> tracks;

    juce::Rectangle<int> cell;

    int cell_width = 55; 

    int cell_height = 20; 

    int draw_start = 15;

    int draw_end = 42;

    int index_start = 0;

    int window_offset = 70;

    int v = 0;

    std::unique_ptr<juce::MidiInput> midiIn;

    std::unique_ptr<juce::MidiOutput> midiOut;

    juce::VST3PluginFormat pluginFormat;

    std::unique_ptr<juce::PluginDirectoryScanner> scanner;

    juce::KnownPluginList knownPluginList;

    juce::StringArray plugin_file;

    juce::String error_message;

    int numOutputChannels = 0;

    //KnownPluginList& knownPlugins;

    juce::FileSearchPath searchPath = "C:\\Program Files\\Common Files\\VST3";

    juce::String plugin;

    juce::StringArray pluginlist;

    int num_plugin = 0;

    juce::AudioPluginFormatManager audiopluginformatmanager;

    juce::PluginDescription plugindescription;

    juce::PluginDescription vstplugin;

    juce::String error;

    std::unique_ptr<juce::AudioPluginInstance> plugin_instance1;

    std::unique_ptr<juce::AudioPluginInstance> plugin_instance2;


    std::unique_ptr<juce::AudioPluginInstance> plugins[16];

    //juce::OwnedArray <std::unique_ptr<juce::AudioPluginInstance>> plugins;

   // juce::OwnedArray <juce::AudioPluginInstance> plugins;

   // juce::PluginDescription* desc;

  //  juce::PluginDescription* desc2;

    juce::DocumentWindow* dw;

    juce::AudioProcessorEditor* audioprocessoreditor1;

    juce::AudioProcessorEditor* audioprocessoreditor2;


    juce::OwnedArray<juce::PluginDescription> descs;

    juce::OwnedArray<juce::PluginDescription> descs2;


    juce::Rectangle<int> bounds;

    juce::MidiBuffer midi;

    juce::OwnedArray<juce::MidiBuffer> midi_tracks;
    //juce::MidiMessage midi;


    juce::AudioPluginFormatManager pluginmanager;


    juce::Array<int> notebuffer;

    juce::Array<int> trackbuffer;


    juce::StringArray message;

    //juce::MidiBuffer midibuffer;

    juce::MidiMessageSequence *miditrackseq;

    juce::MidiMessageSequence alltracks;

    juce::MidiMessage midi_message;
        
    juce::MidiMessage msg;
    
    juce::String note;

    int note_on = 0;

    int note_off = 0;
   
    long long notedata = 0;

    int sampleRateHost = 0;

    int samplesPerBlock = 0;
 
    int track_type[16] = { 0 };

    int track_instrument[16] = { 0 };

    int row = 0;

    int col = 0;

    int k = 0;

    int notenumber = 0;

    int noteremove = 0;

    bool keypress = false;

    int cur_index = 0;

    int cur_x = 70;

    int cur_y = 20 * 15;

    int cursor_track = 0;

    int midiChannel = 0;

    double timeStamp = 0;

    double bpm = 120.0f;

    int milliRows = 0;

    bool keydown = false;

    juce::MidiFile theMidiFile;

    int numTracks = 16;

    int numTrackEvents;

    double thisMessageTimestamp = 0;

    double nextMessageTimestamp = 0;

    double waitTime = 0;

    int i = 0;

    int j = 0;

    int notes_chord = 0;

    int notedbg = 0;

    int num_notes = 0;

    int midi_track[8][3][2048]; // = { 0, 0, 0 };

    int midi_track_clip[8][3][2048]; //= { 0 };

    double ms_beat = 500;

    double ms_duration = 1000;

    juce::Line<float> line;

    int xbord = 0;

    int start_row = 0;

    int start_col = 15;

    int screen_rows = 25;

    int start_note = 0;

    int num_rows = 25;

    int cur_row = 0;

    int note_row = 0;

    bool start_pattern = false;

    bool end_pattern = false;

    int font_height = 20;

    // real width 45

    int track_width = 55;

    int track_length = 64;

    int track_pos = 0;

    int xx = 0, yy = 0;

    int xw = 0, yh = 0;

    bool mouse_down = false;

    bool mouse_drag = false;

    bool mouse_up = false;

    bool clip_true = false;

    bool cursor_draw = false;

    juce::ScrollBar scrollbar { true };

    double oldRange = 0;

    int xdrag = 0;

    int ydrag = 0;

    int instruments[20];

    int xcell = 0, ycell = 0;

    int width = 0;
    
    int height = 0;

    int dcell_x = 0;

    int dcell_y = 0;

    int track_x = 0;

    int xclip = 0;

    int yclip = 0;

    int xcell_copy = 0;

    int ycell_copy = 0;

    int dcell_x_copy = 0;

    int dcell_y_copy = 0;

    bool chord_mode = false;

    int chordIndex = 0;

    float y_wheel = 0;

    float y_wheel_old = 0;

    int pat_len = 63;

    bool InstType = false;

    long long z;

    int a, b, c, d, e, f, gg, h;

    bool inst_change = false;

    int programChangeNum = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tracker)
};


