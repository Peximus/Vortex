#pragma once

#include <JuceHeader.h>

class CustomScrollBar : public juce::ScrollBar, public juce::ScrollBar::Listener
{

public:


	CustomScrollBar()
	{

		//addAndMakeVisible(border);

	}

	~CustomScrollBar() override
	{

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
	

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomScrollBar)


};

