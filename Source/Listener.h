#pragma once

#include <JuceHeader.h>

class Listener : public juce::ChangeListener
{

public:


	Listener()
	{


	}


	void changeListenerCallback(juce::ChangeBroadcaster* source);



private:
	

};

