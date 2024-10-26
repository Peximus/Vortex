#pragma once
#include <JuceHeader.h>

class Settings : public juce::Component {

public:

	Settings() 
	{

        audioSetupComp.reset(new juce::AudioDeviceSelectorComponent(audioDeviceManager,
            0, 256, 0, 256, true, true, true, false));
        addAndMakeVisible(audioSetupComp.get());

        setSize(500, 600);

	}  



~Settings() override
{
}


void resized() override
{
    auto r = getLocalBounds().reduced(4);
    audioSetupComp->setBounds(r.removeFromTop(proportionOfHeight(0.65f)));
}

private:

juce::AudioDeviceManager audioDeviceManager;

std::unique_ptr<juce::AudioDeviceSelectorComponent> audioSetupComp;

};