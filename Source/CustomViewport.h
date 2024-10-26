#pragma once

#include <JuceHeader.h>

class CustomViewport : public juce::Viewport
{

public:


	CustomViewport()
	{

		//addAndMakeVisible(border);

	}

	bool keyPressed(const juce::KeyPress& key) override
	{

	    //	k = key.getKeyCode();

		//repaint();


		return 0;
	}

	void resized() override
	{

		//border.setBounds(0, 0, 800, 800);

	}



private:
	
	juce::GroupComponent border;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomViewport)


};

