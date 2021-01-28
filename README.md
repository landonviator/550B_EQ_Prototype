# Viator 550B Prototype

![alt text](https://github.com/landonviator/550B_EQ_Prototype/blob/main/550B.png "550B")
 
In refining my JUCE and C++ skills, I'm continuing to create plugins based on famous hardware units. Here is my take on the API 550B eq. 

This plugin re-creation features four filter bands with the same set of frequencies as the hardware version and a button under each one which turns the corresponding knob into either the Gain parameter or the Frequency parameter depending on the button's state. The actual hardware unit features concentric potentiometers to achieve this without needing to rely on button. It is certainly possible to emulate this in software, but I'll leave that for another day.

This plugin also features a proportional Q function. Every band features a decently wide Q setting to start, but narrows with the boost/attenuation of gain for each band. As you pull the gain up or down, the Q gets narrow. This is a behavior of the hardware 550B and is a great feature to have. It promotes smaller boosts/attenuations for color, and only boosting/attenuating large amount to identify and remove harsh frequencies. 

![alt text](https://d30pueezughrda.cloudfront.net/juce/JUCE_banner.png "JUCE")

JUCE is an open-source cross-platform C++ application framework used for rapidly
developing high quality desktop and mobile applications, including VST, AU (and AUv3),
RTAS and AAX audio plug-ins. JUCE can be easily integrated with existing projects or can
be used as a project generation tool via the [Projucer](https://juce.com/discover/projucer),
which supports exporting projects for Xcode (macOS and iOS), Visual Studio, Android Studio,
Code::Blocks, CLion and Linux Makefiles as well as containing a source code editor and
live-coding engine which can be used for rapid prototyping.

## Getting Started
The JUCE repository contains a [master](https://github.com/weareroli/JUCE/tree/master)
and [develop](https://github.com/weareroli/JUCE/tree/develop) branch. The develop branch
contains the latest bugfixes and features and is periodically merged into the master
branch in stable [tagged releases](https://github.com/WeAreROLI/JUCE/releases)
(the latest release containing pre-built binaries can be also downloaded from the
[JUCE website](https://shop.juce.com/get-juce)).

The repository doesn't contain a pre-built Projucer so you will need to build it
for your platform - Xcode, Visual Studio and Linux Makefile projects are located in
[extras/Projucer/Builds](/extras/Projucer/Builds)
(the minumum system requirements are listed in the __System Requirements__ section below).
The Projucer can then be used to create new JUCE projects, view tutorials and run examples.
It is also possible to include the JUCE modules source code in an existing project directly,
or build them into a static or dynamic library which can be linked into a project.

For further help getting started, please refer to the JUCE
[documentation](https://juce.com/learn/documentation) and
[tutorials](https://juce.com/learn/tutorials).

## Minimum System Requirements
#### Building JUCE Projects
- __macOS__: macOS 10.11 and Xcode 7.3.1
- __Windows__: Windows 8.1 and Visual Studio 2015 64-bit
- __Linux__: GCC 4.8

#### Deployment Targets
- __macOS__: macOS 10.7
- __Windows__: Windows Vista
- __Linux__: Mainstream Linux distributions

## Contributing
For bug reports and features requests, please visit the [JUCE Forum](https://forum.juce.com/) -
the JUCE developers are active there and will read every post and respond accordingly. When
submitting a bug report, please ensure that it follows the
[issue template](/.github/ISSUE_TEMPLATE.txt).
We don't accept third party GitHub pull requests directly due to copyright restrictions
but if you would like to contribute any changes please contact us.

## License
The core JUCE modules (juce_audio_basics, juce_audio_devices, juce_blocks_basics, juce_core
and juce_events) are permissively licensed under the terms of the
[ISC license](http://www.isc.org/downloads/software-support-policy/isc-license/).
Other modules are covered by a
[GPL/Commercial license](https://www.gnu.org/licenses/gpl-3.0.en.html).

There are multiple commercial licensing tiers for JUCE 5, with different terms for each:
- JUCE Personal (developers or startup businesses with revenue under 50K USD) - free
- JUCE Indie (small businesses with revenue under 200K USD) - $35/month
- JUCE Pro (no revenue limit) - $65/month
- JUCE Educational (no revenue limit) - free for bona fide educational institutes

For full terms see [LICENSE.md](LICENSE.md).
