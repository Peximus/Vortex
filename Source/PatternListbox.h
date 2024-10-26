#pragma once
#include <JuceHeader.h>


class PatternListBox : public juce::Component, private juce::ListBoxModel
{
public:
    PatternListBox()
    {

        setWantsKeyboardFocus(false);


        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        addAndMakeVisible(listBox);
        listBox.setRowHeight(30);
        listBox.setModel(this);   // Tell the listbox where to get its data model
        listBox.setColour(juce::ListBox::textColourId, juce::Colours::black);
        listBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::white);
        
        setSize(100, 400);


      




    }

    ~PatternListBox()
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
        return patterns.size(); //you should probably derive this from whatever source data you end up using
    }

    void paintListBoxItem(int rowNumber, juce::Graphics& g,
        int width, int height, bool rowIsSelected) override
    {

        if (rowIsSelected)
            g.fillAll(juce::Colours::lightblue);

        g.setColour(juce::Colours::black);
        g.setFont(height * 0.7f);

        g.drawText(patterns[rowNumber], 5, 0, width, height,
            juce::Justification::centredLeft, true);

      //  g.drawText("Row Number " + juce::String(rowNumber + 1), 5, 0, width, height,
        //    juce::Justification::centredLeft, true);

    }

    void selectedRowsChanged(int /*lastRowselected*/) override
    {
        //do stuff when selection changes
    }
        

    void addPattern(int pat_num)
    {

        output = juce::String::formatted("%.2d", pat_num);

        patterns.add(output);

        listBox.updateContent();
    }



private:
    juce::ListBox listBox;

    int i = 0;

    juce::String output;

    juce::StringArray patterns;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatternListBox)
};

