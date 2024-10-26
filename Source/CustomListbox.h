#pragma once
#include <JuceHeader.h>


class BasicListBox : public juce::Component, public juce::DragAndDropContainer, public juce::ListBoxModel
{
public:
    BasicListBox()
    {

        setWantsKeyboardFocus(false);

        


        for (int i = 0; i <= 127; i++)
        {

            instruments.add(message.getGMInstrumentName(i));

        }
        


        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        addAndMakeVisible(listBox);
        listBox.setRowHeight(30);
        listBox.setModel(this);   // Tell the listbox where to get its data model
        listBox.setColour(juce::ListBox::textColourId, juce::Colours::black);
        listBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::white);
        
        setSize(120, 600);


      




    }

    ~BasicListBox()
    {
    }

    void paint(juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */
        g.fillAll(juce::Colours::lightgrey);   // clear the background

    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

        //listBox.setBounds(0, 0, getParentWidth(), getParentHeight());

        listBox.setBounds(0, 0, getWidth(), getHeight());

    }

    // The following methods implement the ListBoxModel virtual methods:
    int getNumRows() override
    {
        return 128; //you should probably derive this from whatever source data you end up using
    }

    void paintListBoxItem(int rowNumber, juce::Graphics& g,
        int width, int height, bool rowIsSelected) override
    {

        if (rowIsSelected)
            g.fillAll(juce::Colours::lightblue);

        g.setColour(juce::Colours::black);
        g.setFont(height * 0.7f);


        g.drawText(pluginlist[rowNumber], 5, 0, width, height,
            juce::Justification::centredLeft, true);

      //  g.drawText("Row Number " + juce::String(rowNumber + 1), 5, 0, width, height,
        //    juce::Justification::centredLeft, true);

    }

    void selectedRowsChanged(int /*lastRowselected*/) override
    {
        //do stuff when selection changes
    }

    juce::var getDragSourceDescription(const juce::SparseSet<int>& selectedRows) override
    {
        // for our drag description, we'll just make a comma-separated list of the selected row
        // numbers - this will be picked up by the drag target and displayed in its box.
        juce::StringArray rows;

        for (int i = 0; i < selectedRows.size(); ++i)
            rows.add(juce::String(selectedRows[i] + 1));

        return rows.joinIntoString(", ");


    }


    void addPlugin(juce::String plugin)
    {

        pluginlist.add(plugin);

    }

    void clearListBox()
    {

        pluginlist.clear();
    }

    void updateListBox()
    {
        listBox.updateContent();
        repaint();
    }

private:
    juce::ListBox listBox;

    int i = 0;

    juce::StringArray pluginlist;

    juce::MidiMessage message;

    juce::StringArray instruments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BasicListBox)
};

