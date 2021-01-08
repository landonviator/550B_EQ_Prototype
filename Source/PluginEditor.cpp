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
    
    buttons.reserve(4);
    buttons = {
            &lowToggle, &lowMidToggle, &highMidToggle, &highToggle
        };
    
    tracks.reserve(6);
    tracks = {
        &lowSliderTrack, &lowMidSliderTrack, &highMidSliderTrack, &highSliderTrack, &driveSliderTrack, &trimSliderTrack
    };
    
    labels.reserve(6);
    labels = {
        &lowSliderLabel, &lowMidSliderLabel, &highMidSliderLabel, &highSliderLabel, &driveSliderLabel, &trimSliderLabel
    };
    
    labelTexts.reserve(6);
    labelTexts = {
        lowSliderLabelText, lowMidSliderLabelText, highMidSliderLabelText, highSliderLabelText, driveSliderLabelText, trimSliderLabelText
    };
    
    sliders.reserve(4);
    sliders = {
        &lowSlider, &lowMidSlider, &highMidSlider, &highSlider
    };
    
    //Slider tracks, gain
    for (auto i = 0; i < tracks.size(); i++) {
        addAndMakeVisible(tracks[i]);
        tracks[i]->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        tracks[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
        tracks[i]->setRange(-18, 18, 1.5);
        tracks[i]->setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        tracks[i]->setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
        tracks[i]->setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
        tracks[i]->setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
        tracks[i]->setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));
        tracks[i]->setLookAndFeel(&otherLookAndFeel2);
    }
    
    driveSliderTrack.setRange(0, 24, 0.5f);
    driveSliderTrack.setDoubleClickReturnValue(true, 0);
    trimSliderTrack.setRange(-36, 36, 0.5f);
    trimSliderTrack.setDoubleClickReturnValue(true, 0);
    
    //Sliders, frequency
    for (auto i = 0; i < sliders.size(); i++) {
        addAndMakeVisible(sliders[i]);
        sliders[i]->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
        sliders[i]->setRange(0, 6, 1);
        sliders[i]->setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        sliders[i]->setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
        sliders[i]->setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
        sliders[i]->setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
        sliders[i]->setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));
        sliders[i]->setLookAndFeel(&otherLookAndFeel);
    }
    
    for (auto i = 0; i < labels.size(); i++) {
        addAndMakeVisible(labels[i]);
        labels[i]->setText(labelTexts[i], juce::dontSendNotification);
        labels[i]->setJustificationType(juce::Justification::centred);
        labels[i]->setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5f));
    }
    
    for (auto i = 0; i < buttons.size(); i++) {
        addAndMakeVisible(buttons[i]);
        buttons[i]->addListener(this);
        buttons[i]->setButtonText("Gain");
        buttons[i]->setColour(0x1000100, juce::Colour::fromFloatRGBA(0, 0, 0, .75));
        buttons[i]->setColour(0x1000c00, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        buttons[i]->setColour(0x1000101, juce::Colour::fromFloatRGBA(0, 0, 0, .15));
        buttons[i]->setColour(0x1000102, juce::Colour::fromFloatRGBA(1, 1, 1, 0.35));
        buttons[i]->setColour(0x1000103, juce::Colour::fromFloatRGBA(.23, .77, 1, 0.5));
        buttons[i]->setClickingTogglesState(true);
        buttons[i]->changeWidthToFitText();
        
        if (buttons[i]->getToggleState() == true) {
            tracks[i]->setVisible(false);
            sliders[i]->setVisible(true);
        } else {
            tracks[i]->setVisible(true);
            sliders[i]->setVisible(false);
        }
    }

    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(384, 288, 640, 480);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(1.3);
    setSize (512, 384);
}

Viator550BPrototyperAudioProcessorEditor::~Viator550BPrototyperAudioProcessorEditor()
{
}

//==============================================================================
void Viator550BPrototyperAudioProcessorEditor::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colour::fromFloatRGBA(0.14f, 0.16f, 0.2f, 1.0));
    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::eqBackground_png, BinaryData::eqBackground_pngSize);
    //g.drawImageAt (background, 0, 0);
    //g.drawImage(background, 0, 0, AudioProcessorEditor::getWidth(), AudioProcessorEditor::getHeight(), 0, 0, AudioProcessorEditor::getWidth(), AudioProcessorEditor::getHeight());
    g.drawImageWithin(background, 0, 0, AudioProcessorEditor::getWidth(), AudioProcessorEditor::getHeight(), juce::RectanglePlacement::stretchToFit);
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
    itemArrayLeftThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, highMidSliderTrack).withMargin(juce::FlexItem::Margin(AudioProcessorEditor::getWidth() * 0.1f, 0, 0, 0)));
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
    itemArrayMiddleThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, highSliderTrack).withMargin(juce::FlexItem::Margin(AudioProcessorEditor::getWidth() * 0.1f, 0, 0, 0)));
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
    itemArrayRightThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, driveSliderTrack).withMargin(juce::FlexItem::Margin(AudioProcessorEditor::getWidth() * 0.1f, 0, 0, 0)));
    itemArrayRightThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, trimSliderTrack).withMargin(juce::FlexItem::Margin(0, 0, 0, 0)));
    
    flexboxRightThird.items = itemArrayRightThird;
    flexboxRightThird.performLayout(bounds.removeFromLeft(bounds.getWidth()));
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    
    lowSliderLabel.setBounds(lowSliderTrack.getX() + (lowSliderTrack.getWidth() * 0.25), lowSliderTrack.getY() * .75, lowSliderTrack.getWidth() * .5, lowSliderTrack.getHeight() * .75);
    lowMidSliderLabel.setBounds(lowMidSliderTrack.getX() + (lowMidSliderTrack.getWidth() * 0.25), lowMidSliderTrack.getY() * .75, lowMidSliderTrack.getWidth() * .5, lowMidSliderTrack.getHeight() * .75);
    trimSliderLabel.setBounds(trimSliderTrack.getX() + (trimSliderTrack.getWidth() * 0.25), trimSliderTrack.getY() * .75, trimSliderTrack.getWidth() * .5, trimSliderTrack.getHeight() * .75);
    
    highMidSliderLabel.setBounds(highMidSliderTrack.getX() + (highMidSliderTrack.getWidth() * 0.25), (highMidSliderTrack.getY() * .95) - AudioProcessorEditor::getWidth() * 0.1f, highMidSliderTrack.getWidth() * .5, highMidSliderTrack.getHeight() * .75);
    highSliderLabel.setBounds(highSliderTrack.getX() + (highSliderTrack.getWidth() * 0.25), (highSliderTrack.getY() * .95) - AudioProcessorEditor::getWidth() * 0.1f, highSliderTrack.getWidth() * .5, highSliderTrack.getHeight() * .75);
    driveSliderLabel.setBounds(driveSliderTrack.getX() + (driveSliderTrack.getWidth() * 0.25), (driveSliderTrack.getY() * .95) - AudioProcessorEditor::getWidth() * 0.1f, driveSliderTrack.getWidth() * .5, driveSliderTrack.getHeight() * .75);
    
    lowToggle.setBounds(lowSliderTrack.getX() + (lowSliderTrack.getWidth() * .32), lowSliderTrack.getY() + (lowSliderTrack.getHeight() * .75), lowSliderLabel.getWidth() * .75, lowSliderLabel.getHeight() * .25);
    lowMidToggle.setBounds(lowMidSliderTrack.getX() + (lowMidSliderTrack.getWidth() * .32), lowMidSliderTrack.getY() + (lowMidSliderTrack.getHeight() * .75), lowMidSliderLabel.getWidth() * .75, lowMidSliderLabel.getHeight()* .25);
    highMidToggle.setBounds(highMidSliderTrack.getX() + (highMidSliderTrack.getWidth() * .32), highMidSliderTrack.getY() + (highMidSliderTrack.getHeight() * .75), highMidSliderLabel.getWidth() * .75, highMidSliderLabel.getHeight()* .25);
    highToggle.setBounds(highSliderTrack.getX() + (highSliderTrack.getWidth() * .32), highSliderTrack.getY() + (highSliderTrack.getHeight() * .75), highSliderLabel.getWidth() * .75, highSliderLabel.getHeight()* .25);
    
    for (auto i = 0; i < sliders.size(); i++) {
        sliders[i]->setBounds(tracks[i]->getX(), tracks[i]->getY(), tracks[i]->getWidth(), tracks[i]->getHeight());
    }
}

void Viator550BPrototyperAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){

}

void Viator550BPrototyperAudioProcessorEditor::buttonClicked(juce::Button *button){
    
    for (auto i = 0; i < buttons.size(); i++) {
        if (button == buttons[i]){
            if (buttons[i]->getToggleState() == true){
                buttons[i]->setButtonText("Freq");
                sliders[i]->setVisible(true);
                tracks[i]->setVisible(false);
            } else {
                buttons[i]->setButtonText("Gain");
                tracks[i]->setVisible(true);
                sliders[i]->setVisible(false);

            }
        }
    }
}
