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
    
    bandGainSliders.reserve(6);
    bandGainSliders = {
        &lowBandGainSlider, &lowMidBandGainSlider, &highMidBandGainSlider, &highBandGainSlider, &driveSlider, &trimSlider
    };
    
    labels.reserve(2);
    labels = {
         &driveSliderLabel, &trimSliderLabel
    };
    
    labelTexts.reserve(2);
    labelTexts = {
         driveSliderLabelText, trimSliderLabelText
    };
    
    frequencySliders.reserve(4);
    frequencySliders = {
        &lowFrequencySlider, &lowMidFrequencySlider, &highMidFrequencySlider, &highFrequencySlider
    };
    
    props.radius = 15;
    props.offset = juce::Point<int> (-2, 6);
    shadowEffect.setShadowProperties (props);
    
    //Slider tracks, gain
    for (auto i = 0; i < bandGainSliders.size(); i++) {
        addAndMakeVisible(bandGainSliders[i]);
        bandGainSliders[i]->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        bandGainSliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 96, 32);
        bandGainSliders[i]->setRange(-15, 15, 1.5f);
        bandGainSliders[i]->setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        bandGainSliders[i]->setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
        bandGainSliders[i]->setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
        bandGainSliders[i]->setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
        bandGainSliders[i]->setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));
        bandGainSliders[i]->setLookAndFeel(&otherLookAndFeel2);
        bandGainSliders[i]->setComponentEffect(&shadowEffect);
        bandGainSliders[i]->setDoubleClickReturnValue(true, 0.0f);
    }
    
    //Slider attachments for parameters
    lowFrequencySliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, lowFrequencySliderId, lowFrequencySlider);
    lowMidFrequencySliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, lowMidFrequencySliderId, lowMidFrequencySlider);
    highMidFrequencySliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, highMidFrequencySliderId, highMidFrequencySlider);
    highFrequencySliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, highFrequencySliderId, highFrequencySlider);
    driveAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, driveSliderId, driveSlider);
    trimAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, trimSliderId, trimSlider);

    //Drive slider is processed differently than the band sliders
    driveSlider.setRange(0, 36, 0.5f);
    driveSlider.setDoubleClickReturnValue(true, 0);
    driveSlider.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, .5));
    driveSlider.setColour(0x1001500, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
    driveSlider.setTextValueSuffix(" dB");
    driveSlider.setLookAndFeel(&otherLookAndFeel);
    driveSlider.setComponentEffect(&shadowEffect);
    
    //Trim slider is processed differently from the band sliders
    trimSlider.setRange(-36, 36, 0.5f);
    trimSlider.setDoubleClickReturnValue(true, 0);
    trimSlider.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, .5));
    trimSlider.setColour(0x1001500, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
    trimSlider.setTextValueSuffix(" dB");
    trimSlider.setLookAndFeel(&otherLookAndFeel);
    trimSlider.setComponentEffect(&shadowEffect);
    
    //Sliders, frequency
    for (auto i = 0; i < frequencySliders.size(); i++) {
        addAndMakeVisible(frequencySliders[i]);
        frequencySliders[i]->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        frequencySliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
        frequencySliders[i]->setRange(0, 6, 1);
        frequencySliders[i]->setColour(0x1001700, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        frequencySliders[i]->setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
        frequencySliders[i]->setColour(0x1001300, juce::Colour::fromFloatRGBA(1, 1, 1, 0));
        frequencySliders[i]->setColour(0x1001312, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
        frequencySliders[i]->setColour(0x1001311, juce::Colour::fromFloatRGBA(.2, .77, 1, 0.5f));
        frequencySliders[i]->setLookAndFeel(&otherLookAndFeel);
        frequencySliders[i]->setComponentEffect(&shadowEffect);
        frequencySliders[i]->setDoubleClickReturnValue(true, 0);
    }
    
    //Attachments for parameters
    lowBandGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, lowBandGainSliderId, lowBandGainSlider);
    lowMidBandGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, lowMidBandGainSliderId, lowMidBandGainSlider);
    highMidBandGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, highMidBandGainSliderId, highMidBandGainSlider);
    highBandGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, highBandGainSliderId, highBandGainSlider);
    
    //Making the labels, turns out I only wanted the drive and trim label visible
    for (auto i = 0; i < labels.size(); i++) {
        //addAndMakeVisible(labels[i]);
        labels[i]->setText(labelTexts[i], juce::dontSendNotification);
        labels[i]->setJustificationType(juce::Justification::centred);
        labels[i]->setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.5f));
    }
    addAndMakeVisible(driveSliderLabel);
    addAndMakeVisible(trimSliderLabel);
    
    //Making the buttons
    for (auto i = 0; i < buttons.size(); i++) {
        addAndMakeVisible(buttons[i]);
        buttons[i]->addListener(this);
        buttons[i]->setButtonText("Gain");
        buttons[i]->setColour(0x1000100, juce::Colour::fromFloatRGBA(0, 0, 0, .25));
        buttons[i]->setColour(0x1000c00, juce::Colour::fromFloatRGBA(0, 0, 0, 0));
        buttons[i]->setColour(0x1000101, juce::Colour::fromFloatRGBA(0, 0, 0, .15));
        buttons[i]->setColour(0x1000102, juce::Colour::fromFloatRGBA(1, 1, 1, 0.35));
        buttons[i]->setColour(0x1000103, juce::Colour::fromFloatRGBA(.23, .77, 1, 0.5));
        buttons[i]->setColour(0x1000103, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 0.5f));
        buttons[i]->setClickingTogglesState(true);
        
        //Making sure the buttons show the correct value when opening the gui again
        if (buttons[i]->getToggleState() == true) {
            bandGainSliders[i]->setVisible(false);
            frequencySliders[i]->setVisible(true);
        } else {
            bandGainSliders[i]->setVisible(true);
            frequencySliders[i]->setVisible(false);
        }
    }
    
    //Button attachments for parameters
    lowBandToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, lowToggleId, lowToggle);
    lowMidBandToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, lowMidToggleId, lowMidToggle);
    highMidBandToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, highMidToggleId, highMidToggle);
    highBandToggleAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.treeState, highToggleId, highToggle);
    
    //Making the window resizable by aspect ratio and setting size
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
    //Background color
    g.fillAll(juce::Colour::fromFloatRGBA(0.14f, 0.16f, 0.2f, 1.0));
    
    //Image layer from Illustrator
    background = juce::ImageCache::getFromMemory(BinaryData::eqBackground_png, BinaryData::eqBackground_pngSize);
    g.drawImageWithin(background, 0, 0, AudioProcessorEditor::getWidth(), AudioProcessorEditor::getHeight(), juce::RectanglePlacement::stretchToFit);
}

void Viator550BPrototyperAudioProcessorEditor::resized()
{
    
    
    //Master bounds object
    juce::Rectangle<int> bounds = getLocalBounds();
    
    //Left column of gui
    juce::FlexBox flexboxLeftThird;
    flexboxLeftThird.flexDirection = juce::FlexBox::Direction::column;
    flexboxLeftThird.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxLeftThird.alignContent = juce::FlexBox::AlignContent::stretch;
    
    juce::Array<juce::FlexItem> itemArrayLeftThird;
    itemArrayLeftThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, highMidBandGainSlider).withMargin(juce::FlexItem::Margin(AudioProcessorEditor::getWidth() * 0.05f, 0, 0, 0)));
    itemArrayLeftThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, lowBandGainSlider).withMargin(juce::FlexItem::Margin(AudioProcessorEditor::getWidth() * 0.05f, 0, 0, 0)));
    
    flexboxLeftThird.items = itemArrayLeftThird;
    flexboxLeftThird.performLayout(bounds.removeFromLeft(bounds.getWidth() / 3));
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    //Middle column of gui
    juce::FlexBox flexboxMiddleThird;
    flexboxMiddleThird.flexDirection = juce::FlexBox::Direction::column;
    flexboxMiddleThird.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxMiddleThird.alignContent = juce::FlexBox::AlignContent::stretch;
    
    juce::Array<juce::FlexItem> itemArrayMiddleThird;
    itemArrayMiddleThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, highBandGainSlider).withMargin(juce::FlexItem::Margin(AudioProcessorEditor::getWidth() * 0.05f, 0, 0, 0)));
    itemArrayMiddleThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, lowMidBandGainSlider).withMargin(juce::FlexItem::Margin(AudioProcessorEditor::getWidth() * 0.05f, 0, 0, 0)));
    
    flexboxMiddleThird.items = itemArrayMiddleThird;
    flexboxMiddleThird.performLayout(bounds.removeFromLeft(bounds.getWidth() / 2));
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    //Right column of gui
    juce::FlexBox flexboxRightThird;
    flexboxRightThird.flexDirection = juce::FlexBox::Direction::column;
    flexboxRightThird.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexboxRightThird.alignContent = juce::FlexBox::AlignContent::stretch;
    
    juce::Array<juce::FlexItem> itemArrayRightThird;
    itemArrayRightThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, driveSlider).withMargin(juce::FlexItem::Margin(AudioProcessorEditor::getWidth() * 0.05f, 0, 0, 0)));
    itemArrayRightThird.add(juce::FlexItem(bounds.getWidth() / 3.5, bounds.getHeight() / 2.5, trimSlider).withMargin(juce::FlexItem::Margin(AudioProcessorEditor::getWidth() * 0.05f, 0, 0, 0)));
    
    flexboxRightThird.items = itemArrayRightThird;
    flexboxRightThird.performLayout(bounds.removeFromLeft(bounds.getWidth()));
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    //Makin the label bounds resize
    trimSliderLabel.setBounds(trimSlider.getX() + (trimSlider.getWidth() * 0.25), trimSlider.getY() * .75, trimSlider.getWidth() * .5, trimSlider.getHeight() * .75);
    driveSliderLabel.setBounds(driveSlider.getX() + (driveSlider.getWidth() * 0.25), (driveSlider.getY() * .95) - AudioProcessorEditor::getWidth() * 0.1f, driveSlider.getWidth() * .5, driveSlider.getHeight() * .75);
    
    //Making the buttons resize
    lowToggle.setBounds(lowBandGainSlider.getX() + (lowBandGainSlider.getWidth() * .33), lowBandGainSlider.getY() + (lowBandGainSlider.getHeight() * .8), driveSliderLabel.getWidth(), driveSliderLabel.getHeight() * .25);
    lowMidToggle.setBounds(lowMidBandGainSlider.getX() + (lowMidBandGainSlider.getWidth() * .33), lowMidBandGainSlider.getY() + (lowMidBandGainSlider.getHeight() * .8), driveSliderLabel.getWidth() * .75, driveSliderLabel.getHeight()* .25);
    highMidToggle.setBounds(highMidBandGainSlider.getX() + (highMidBandGainSlider.getWidth() * .33), highMidBandGainSlider.getY() + (highMidBandGainSlider.getHeight() * .8), driveSliderLabel.getWidth() * .75, driveSliderLabel.getHeight()* .25);
    highToggle.setBounds(highBandGainSlider.getX() + (highBandGainSlider.getWidth() * .33), highBandGainSlider.getY() + (highBandGainSlider.getHeight() * .8), driveSliderLabel.getWidth() * .75, driveSliderLabel.getHeight()* .25);
    
    //Making the sliders resize
    for (auto i = 0; i < frequencySliders.size(); i++) {
        frequencySliders[i]->setBounds(bandGainSliders[i]->getX(), bandGainSliders[i]->getY(), bandGainSliders[i]->getWidth(), bandGainSliders[i]->getHeight());
        buttons[i]->changeWidthToFitText();
    }
}

void Viator550BPrototyperAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){

}

void Viator550BPrototyperAudioProcessorEditor::buttonClicked(juce::Button *button){
    
    //Making sure the button's text changes based on it's state
    for (auto i = 0; i < buttons.size(); i++) {
        if (button == buttons[i]){
            if (buttons[i]->getToggleState() == true){
                buttons[i]->setButtonText("Freq");
                frequencySliders[i]->setVisible(true);
                bandGainSliders[i]->setVisible(false);
            } else {
                buttons[i]->setButtonText("Gain");
                bandGainSliders[i]->setVisible(true);
                frequencySliders[i]->setVisible(false);

            }
        }
    }
}
