/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define lowFrequencySliderId "low freq"
#define lowFrequencySliderName "Low Freq"
#define lowMidFrequencySliderId "low mid freq"
#define lowMidFrequencySliderName "Low Mid Freq"
#define highMidFrequencySliderId "high mid freq"
#define highMidFrequencySliderName "High Mid Freq"
#define highFrequencySliderId "high freq"
#define highFrequencySliderName "High Freq"

#define lowToggleId "low toggle"
#define lowToggleName "Low Toggle"
#define lowMidToggleId "low mid toggle"
#define lowMidToggleName "Low Mid Toggle"
#define highMidToggleId "high mid toggle"
#define highMidToggleName "High Mid Toggle"
#define highToggleId "high toggle"
#define highToggleName "High Toggle"

#define lowBandGainSliderId "low gain"
#define lowBandGainSliderName "Low Gain"
#define lowMidBandGainSliderId "low mid gain"
#define lowMidBandGainSliderName "Low Mid Gain"
#define highMidBandGainSliderId "high mid gain"
#define highMidBandGainSliderName "High Mid Gain"
#define highBandGainSliderId "high gain"
#define highBandGainSliderName "High Gain"

#define driveSliderId "drive"
#define driveSliderName "Drive"
#define trimSliderId "trim"
#define trimSliderName "Trim"

//==============================================================================
/**
*/
class Viator550BPrototyperAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Viator550BPrototyperAudioProcessor();
    ~Viator550BPrototyperAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState treeState;
    
private:
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Viator550BPrototyperAudioProcessor)
};
