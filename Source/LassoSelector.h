/*
  ==============================================================================

    LassoSelector.h
    Created: 6 Jul 2020 4:49:38pm
    Author:  maxime

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


template <class Type>
class LassoSelector : public LassoComponent<Type>
{
public:


    void paint(Graphics &g) override {
        Rectangle<int> outline(LassoComponent<Type>::getLocalBounds());

        Path p;
        p.addRectangle(outline);

        PathStrokeType strokeType(4);
        float dashLengths[2] = {10.0f, 10.0f};
        strokeType.createDashedStroke(p,p, dashLengths, 2);

        g.setColour(Colours::whitesmoke);
        g.fillPath(p);

        //LassoComponent<Type>::paint(g);
    }
};