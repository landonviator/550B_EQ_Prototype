/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Viator550BPrototyperAudioProcessorEditor::Viator550BPrototyperAudioProcessorEditor (Viator550BPrototyperAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //Low slider track, for frequency
    addAndMakeVisible(lowSliderTrack);
    lowSliderTrack.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    lowSliderTrack.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
    lowSliderTrack.setRange(0, 6, 1);
    lowSliderTrack.setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    lowSliderTrack.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    lowSliderTrack.setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
    lowSliderTrack.setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
    lowSliderTrack.setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));

    //Low Label
    addAndMakeVisible(lowSliderLabel);
    lowSliderLabel.setText("Low", juce::dontSendNotification);
    lowSliderLabel.setJustificationType(juce::Justification::centred);
    lowSliderLabel.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5f));
    lowSliderLabel.attachToComponent(&lowSliderTrack, false);
//------------------------------------------------------------------------------------------
    
    //High mid slider track, for frequency
    addAndMakeVisible(highMidSliderTrack);
    highMidSliderTrack.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    highMidSliderTrack.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
    highMidSliderTrack.setRange(0, 6, 1);
    highMidSliderTrack.setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    highMidSliderTrack.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    highMidSliderTrack.setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
    highMidSliderTrack.setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
    highMidSliderTrack.setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));

    //High Mid Label
    addAndMakeVisible(highMidSliderLabel);
    highMidSliderLabel.setText("High Mid", juce::dontSendNotification);
    highMidSliderLabel.setJustificationType(juce::Justification::centred);
    highMidSliderLabel.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5f));
    highMidSliderLabel.attachToComponent(&highMidSliderTrack, false);
//------------------------------------------------------------------------------------------

    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(256, 192, 1024, 768);
    setSize (512, 384);
}

Viator550BPrototyperAudioProcessorEditor::~Viator550BPrototyperAudioProcessorEditor()
{
}

//==============================================================================
void Viator550BPrototyperAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromFloatRGBA(0.14f, 0.16f, 0.2f, 1.0));

}

void Viator550BPrototyperAudioProcessorEditor::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    
    juce::FlexBox flexboxLeftThird;
    flexboxLeftThird.flexDirection = juce::FlexBox::Direction::column;
    flexboxLeftThird.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxLeftThird.alignContent = juce::FlexBox::AlignContent::stretch;
    
    juce::Array<juce::FlexItem> itemArrayLeftThird;
    itemArrayLeftThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, highMidSliderTrack).withMargin(36));
    itemArrayLeftThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, lowSliderTrack));
    
    flexboxLeftThird.items = itemArrayLeftThird;
    flexboxLeftThird.performLayout(bounds.removeFromLeft(bounds.getWidth() / 3));
}

void Viator550BPrototyperAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
//    for (size_t i {0}; i < sliders.size(); i++) {
//        if (slider == tracks[i]){
//            sliders[i]->setValue(tracks[i]->getValue());
//        }
//    }
}
