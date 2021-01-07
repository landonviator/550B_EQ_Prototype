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
    
    //High slider track, for frequency
    addAndMakeVisible(highSliderTrack);
    highSliderTrack.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    highSliderTrack.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
    highSliderTrack.setRange(0, 6, 1);
    highSliderTrack.setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    highSliderTrack.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    highSliderTrack.setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
    highSliderTrack.setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
    highSliderTrack.setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));

    //High Label
    addAndMakeVisible(highSliderLabel);
    highSliderLabel.setText("High", juce::dontSendNotification);
    highSliderLabel.setJustificationType(juce::Justification::centred);
    highSliderLabel.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5f));
    highSliderLabel.attachToComponent(&highSliderTrack, false);
//------------------------------------------------------------------------------------------
    
    //Low mid slider track, for frequency
    addAndMakeVisible(lowMidSliderTrack);
    lowMidSliderTrack.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    lowMidSliderTrack.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
    lowMidSliderTrack.setRange(0, 6, 1);
    lowMidSliderTrack.setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    lowMidSliderTrack.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    lowMidSliderTrack.setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
    lowMidSliderTrack.setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
    lowMidSliderTrack.setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));

    //Low Mid Label
    addAndMakeVisible(lowMidSliderLabel);
    lowMidSliderLabel.setText("Low Mid", juce::dontSendNotification);
    lowMidSliderLabel.setJustificationType(juce::Justification::centred);
    lowMidSliderLabel.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5f));
    lowMidSliderLabel.attachToComponent(&lowMidSliderTrack, false);
//------------------------------------------------------------------------------------------
    
    //Drive slider
    addAndMakeVisible(driveSliderTrack);
    driveSliderTrack.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    driveSliderTrack.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
    driveSliderTrack.setRange(0, 24, 0.5f);
    driveSliderTrack.setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    driveSliderTrack.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    driveSliderTrack.setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
    driveSliderTrack.setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
    driveSliderTrack.setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));

    //Drive Label
    addAndMakeVisible(driveSliderLabel);
    driveSliderLabel.setText("Drive", juce::dontSendNotification);
    driveSliderLabel.setJustificationType(juce::Justification::centred);
    driveSliderLabel.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5f));
    driveSliderLabel.attachToComponent(&driveSliderTrack, false);
//------------------------------------------------------------------------------------------
    
    //Trim slider
    addAndMakeVisible(trimSliderTrack);
    trimSliderTrack.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    trimSliderTrack.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
    trimSliderTrack.setRange(-36, 36, 0.5f);
    trimSliderTrack.setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
    trimSliderTrack.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    trimSliderTrack.setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
    trimSliderTrack.setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
    trimSliderTrack.setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));

    //Trim Label
    addAndMakeVisible(trimSliderLabel);
    trimSliderLabel.setText("Trim", juce::dontSendNotification);
    trimSliderLabel.setJustificationType(juce::Justification::centred);
    trimSliderLabel.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5f));
    trimSliderLabel.attachToComponent(&trimSliderTrack, false);
//------------------------------------------------------------------------------------------

    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(256, 192, 1024, 768);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(1.3);
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
    
    //Left column of gui
    juce::FlexBox flexboxLeftThird;
    flexboxLeftThird.flexDirection = juce::FlexBox::Direction::column;
    flexboxLeftThird.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxLeftThird.alignContent = juce::FlexBox::AlignContent::stretch;
    
    juce::Array<juce::FlexItem> itemArrayLeftThird;
    itemArrayLeftThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, highMidSliderTrack).withMargin(juce::FlexItem::Margin(48, 0, 0, 0)));
    itemArrayLeftThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, lowSliderTrack).withMargin(juce::FlexItem::Margin(0, 0, 0, 0)));
    
    flexboxLeftThird.items = itemArrayLeftThird;
    flexboxLeftThird.performLayout(bounds.removeFromLeft(bounds.getWidth() / 3));
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    //Middle column of gui
    juce::FlexBox flexboxMiddleThird;
    flexboxMiddleThird.flexDirection = juce::FlexBox::Direction::column;
    flexboxMiddleThird.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxMiddleThird.alignContent = juce::FlexBox::AlignContent::stretch;
    
    juce::Array<juce::FlexItem> itemArrayMiddleThird;
    itemArrayMiddleThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, highSliderTrack).withMargin(juce::FlexItem::Margin(48, 0, 0, 0)));
    itemArrayMiddleThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, lowMidSliderTrack).withMargin(juce::FlexItem::Margin(0, 0, 0, 0)));
    
    flexboxMiddleThird.items = itemArrayMiddleThird;
    flexboxMiddleThird.performLayout(bounds.removeFromLeft(bounds.getWidth() / 2));
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    //Right column of gui
    juce::FlexBox flexboxRightThird;
    flexboxRightThird.flexDirection = juce::FlexBox::Direction::column;
    flexboxRightThird.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxRightThird.alignContent = juce::FlexBox::AlignContent::stretch;
    
    juce::Array<juce::FlexItem> itemArrayRightThird;
    itemArrayRightThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, driveSliderTrack).withMargin(juce::FlexItem::Margin(48, 0, 0, 0)));
    itemArrayRightThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, trimSliderTrack).withMargin(juce::FlexItem::Margin(0, 0, 0, 0)));
    
    flexboxRightThird.items = itemArrayRightThird;
    flexboxRightThird.performLayout(bounds.removeFromLeft(bounds.getWidth()));
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void Viator550BPrototyperAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
//    for (size_t i {0}; i < sliders.size(); i++) {
//        if (slider == tracks[i]){
//            sliders[i]->setValue(tracks[i]->getValue());
//        }
//    }
}
