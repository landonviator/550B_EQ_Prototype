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
treeState (*this, nullptr, "PARAMETER", createParameterLayout()),
lowFilter(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100.0f, 30.0f, 1.0f, 1.0f)),
lowMidFilter(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100.0f, 75, 1.0f, 1.0f)),
highMidFilter(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100.0f, 800.0f, 1.0f, 1.0f)),
highFilter(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100.0f, 2500.0f, 1.0f, 1.0f))
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
    
    auto lowGainParam = std::make_unique<juce::AudioParameterFloat>(lowBandGainSliderId, lowBandGainSliderName, -15, 15, 0);
    auto lowMidGainParam = std::make_unique<juce::AudioParameterFloat>(lowMidBandGainSliderId, lowMidBandGainSliderName, -15, 15, 0);
    auto highMidGainParam = std::make_unique<juce::AudioParameterFloat>(highMidBandGainSliderId, highMidBandGainSliderName, -15, 15, 0);
    auto highGainParam = std::make_unique<juce::AudioParameterFloat>(highBandGainSliderId, highBandGainSliderName, -15, 15, 0);
    
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
    lastSampleRate = sampleRate;
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    lowFilter.prepare(spec);
    lowMidFilter.prepare(spec);
    highMidFilter.prepare(spec);
    highFilter.prepare(spec);
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
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block (buffer);
    
    auto* rawLowFrequency = treeState.getRawParameterValue(lowFrequencySliderId);
    auto* rawLowMidFrequency = treeState.getRawParameterValue(lowMidFrequencySliderId);
    auto* rawHighMidFrequency = treeState.getRawParameterValue(highMidFrequencySliderId);
    auto* rawHighFrequency = treeState.getRawParameterValue(highFrequencySliderId);
    
    auto* rawLowGain = treeState.getRawParameterValue(lowBandGainSliderId);
    auto* rawLowMidGain = treeState.getRawParameterValue(lowMidBandGainSliderId);
    auto* rawHighMidGain = treeState.getRawParameterValue(highMidBandGainSliderId);
    auto* rawHighGain = treeState.getRawParameterValue(highBandGainSliderId);
    
    updateLowFilter(*rawLowGain, *rawLowFrequency);
    updateLowMidFilter(*rawLowMidGain, *rawLowMidFrequency);
    updateHighMidFilter(*rawHighMidGain, *rawHighMidFrequency);
    updateHighFilter(*rawHighGain, *rawHighFrequency);
    
    lowFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    lowMidFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    highMidFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
    highFilter.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void Viator550BPrototyperAudioProcessor::updateLowFilter(float gain, int rawFreqKnob){
    
    //The frequency knob has 7 values, so each one is assigned to a vector of the frequencies
    auto frequency = rawLowFrequencySliderValues[rawFreqKnob];
    float quality;
    
    if (rawFreqKnob >= 4){
        if (abs(gain) < 6.0) {
            quality = lowFilterQValues[rawFreqKnob];
        } else {
            quality = pow(10, (abs(gain) - 6.0) * 0.055) - 0.7f;
        }
    } else {
        quality = lowFilterQValues[rawFreqKnob];
    }
    
    *lowFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, frequency, quality, pow(10, gain * 0.09f));
    //std::cout << "Low Band Frequency: " << frequency << std::endl;
//    std::cout << "Low Band Gain: " << gain << std::endl;
    std::cout << "Low Band Q: " << quality << std::endl;
    //std::cout << "F: " << rawFreqKnob << std::endl;
}

void Viator550BPrototyperAudioProcessor::updateLowMidFilter(float gain, int rawFreqKnob){
    auto frequency = rawLowMidFrequencySliderValues[rawFreqKnob];
    *lowMidFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, frequency, 1.0, pow(10, gain * 0.09f));
    //std::cout << "Low Mid Band Frequency: " << frequency << std::endl;
}

void Viator550BPrototyperAudioProcessor::updateHighMidFilter(float gain, int rawFreqKnob){
    auto frequency = rawHighMidFrequencySliderValues[rawFreqKnob];
    *highMidFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, frequency, 1.0, pow(10, gain * 0.09f));
    //std::cout << "High Mid Band Frequency: " << frequency << std::endl;
}

void Viator550BPrototyperAudioProcessor::updateHighFilter(float gain, int rawFreqKnob){
    auto frequency = rawHighFrequencySliderValues[rawFreqKnob];
    *highFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, frequency, 1.0, pow(10, gain * 0.09f));
    //std::cout << "High Band Frequency: " << frequency << std::endl;
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
