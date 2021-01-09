/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Viator550BPrototyperAudioProcessor::Viator550BPrototyperAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), false)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState (*this, nullptr, "PARAMETER", createParameterLayout())
#endif
{
}

Viator550BPrototyperAudioProcessor::~Viator550BPrototyperAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout Viator550BPrototyperAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    params.reserve(14);
    
    auto lowFrequencyParam = std::make_unique<juce::AudioParameterInt>(lowFrequencySliderId, lowFrequencySliderName, 0, 6, 0);
    auto lowMidFrequencyParam = std::make_unique<juce::AudioParameterInt>(lowMidFrequencySliderId, lowMidFrequencySliderName, 0, 6, 0);
    auto highMidFrequencyParam = std::make_unique<juce::AudioParameterInt>(highMidFrequencySliderId, highMidFrequencySliderName, 0, 6, 0);
    auto highFrequencyParam = std::make_unique<juce::AudioParameterInt>(highFrequencySliderId, highFrequencySliderName, 0, 6, 0);
    
    auto lowGainParam = std::make_unique<juce::AudioParameterFloat>(lowBandGainSliderId, lowBandGainSliderName, -18.0f, 18.0f, 0.0f);
    auto lowMidGainParam = std::make_unique<juce::AudioParameterFloat>(lowMidBandGainSliderId, lowMidBandGainSliderName, -24, 24, 0);
    auto highMidGainParam = std::make_unique<juce::AudioParameterFloat>(highMidBandGainSliderId, highMidBandGainSliderName, -24, 24, 0);
    auto highGainParam = std::make_unique<juce::AudioParameterFloat>(highBandGainSliderId, highBandGainSliderName, 0, 24, 0);
    
    auto lowToggleParam = std::make_unique<juce::AudioParameterBool>(lowToggleId, lowToggleName, false);
    auto lowMidToggleParam = std::make_unique<juce::AudioParameterBool>(lowMidToggleId, lowMidToggleName, false);
    auto highMidToggleParam = std::make_unique<juce::AudioParameterBool>(highMidToggleId, highMidToggleName, false);
    auto highToggleParam = std::make_unique<juce::AudioParameterBool>(highToggleId, highToggleName, false);
    
    auto driveParam = std::make_unique<juce::AudioParameterFloat>(driveSliderId, driveSliderName, 0, 24, 0);
    auto trimParam = std::make_unique<juce::AudioParameterFloat>(trimSliderId, trimSliderName, -24, 24, 0);
    
    params.push_back(std::move(lowFrequencyParam));
    params.push_back(std::move(lowMidFrequencyParam));
    params.push_back(std::move(highMidFrequencyParam));
    params.push_back(std::move(highFrequencyParam));
    
    params.push_back(std::move(lowGainParam));
    params.push_back(std::move(lowMidGainParam));
    params.push_back(std::move(highMidGainParam));
    params.push_back(std::move(highGainParam));
    
    params.push_back(std::move(lowToggleParam));
    params.push_back(std::move(lowMidToggleParam));
    params.push_back(std::move(highMidToggleParam));
    params.push_back(std::move(highToggleParam));
    
    params.push_back(std::move(driveParam));
    params.push_back(std::move(trimParam));
    
    return { params.begin(), params.end() };
}

//==============================================================================
const juce::String Viator550BPrototyperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Viator550BPrototyperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Viator550BPrototyperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Viator550BPrototyperAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Viator550BPrototyperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Viator550BPrototyperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Viator550BPrototyperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Viator550BPrototyperAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Viator550BPrototyperAudioProcessor::getProgramName (int index)
{
    return {};
}

void Viator550BPrototyperAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Viator550BPrototyperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Viator550BPrototyperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Viator550BPrototyperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Viator550BPrototyperAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Viator550BPrototyperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Viator550BPrototyperAudioProcessor::createEditor()
{
    return new Viator550BPrototyperAudioProcessorEditor (*this);
}

//==============================================================================
void Viator550BPrototyperAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream stream(destData, false);
        treeState.state.writeToStream (stream);
}

void Viator550BPrototyperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ValueTree tree = juce::ValueTree::readFromData (data, size_t (sizeInBytes));
        if (tree.isValid()) {
            treeState.state = tree;
        }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Viator550BPrototyperAudioProcessor();
}
