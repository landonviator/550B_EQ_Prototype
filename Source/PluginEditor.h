/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/

class OtherLookAndFeel : public juce::LookAndFeel_V4{
public:
    void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider) override{
        
        float diameter = fmin(width, height) * 0.65;
        float radius = diameter * 0.5;
        float centerX = x + width * 0.5;
        float centerY = y + height * 0.5;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
        
        juce::Rectangle<float> dialArea (rx, ry, diameter, diameter);
        g.setColour(juce::Colour::fromFloatRGBA(0.133, 0.133, 0.133, 1)); //center
        g.fillEllipse(dialArea);
        g.setColour(juce::Colour::fromFloatRGBA(.2, .77, 1, .5)); //tick color
        
        juce::Path dialTick;
        dialTick.addRectangle(0, -radius + 3, 3.0f, radius * .5);
        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));
        g.setColour(juce::Colour::fromFloatRGBA(0, 0, 0, .25)); //outline
        g.drawEllipse(rx, ry, diameter, diameter, 1.0f);
    }
};

class OtherLookAndFeel2 : public juce::LookAndFeel_V4{
public:
    void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider) override{
        
        float diameter = fmin(width, height) * 0.65;
        float radius = diameter * 0.5;
        float centerX = x + width * 0.5;
        float centerY = y + height * 0.5;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
        
        juce::Rectangle<float> dialArea (rx, ry, diameter, diameter);
        g.setColour(juce::Colour::fromFloatRGBA(0.133, 0.133, 0.133, 1)); //center
        g.fillEllipse(dialArea);
        g.setColour(juce::Colour::fromFloatRGBA(1, 1, 1, .5)); //tick color
        
        juce::Path dialTick;
        dialTick.addRectangle(0, -radius + 3, 3.0f, radius * .5);
        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centerX, centerY));
        g.setColour(juce::Colour::fromFloatRGBA(0, 0, 0, .25)); //outline
        g.drawEllipse(rx, ry, diameter, diameter, 1.0f);
    }
};

class Viator550BPrototyperAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Slider::Listener, juce::Button::Listener
{
public:
    Viator550BPrototyperAudioProcessorEditor (Viator550BPrototyperAudioProcessor&);
    ~Viator550BPrototyperAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;


private:
    juce::Slider lowSlider, lowMidSlider, highMidSlider, highSlider;
    std::vector<juce::Slider*> sliders;
    
    juce::Slider lowSliderTrack, lowMidSliderTrack, highMidSliderTrack, highSliderTrack, driveSliderTrack, trimSliderTrack;
    std::vector<juce::Slider*> tracks;
    
    juce::Label lowSliderLabel, lowMidSliderLabel, highMidSliderLabel, highSliderLabel, driveSliderLabel, trimSliderLabel;
    std::vector<juce::Label*> labels;
    
    juce::TextButton lowToggle, lowMidToggle, highMidToggle, highToggle;
    std::vector<juce::TextButton*> buttons;
    
    std::string lowSliderLabelText = "Low";
    std::string lowMidSliderLabelText = "Low Mid";
    std::string highMidSliderLabelText = "High Mid";
    std::string highSliderLabelText = "High";
    std::string driveSliderLabelText = "Drive";
    std::string trimSliderLabelText = "Trim";

    std::vector<std::string> labelTexts;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lowSliderAttach, lowMidSliderAttach, highMidSliderAttach, highSliderAttach;
    
    OtherLookAndFeel otherLookAndFeel;
    OtherLookAndFeel2 otherLookAndFeel2;

    Viator550BPrototyperAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Viator550BPrototyperAudioProcessorEditor)
};
