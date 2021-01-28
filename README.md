# Viator 550B Prototype

![alt text](https://github.com/landonviator/550B_EQ_Prototype/blob/main/550B.png "550B")
 
In refining my JUCE and C++ skills, I'm continuing to create plugins based on famous hardware units. Here is my take on the API 550B eq. 

This plugin re-creation features four filter bands with the same set of frequencies as the hardware version and a button under each one which turns the corresponding knob into either the Gain parameter or the Frequency parameter depending on the button's state. The actual hardware unit features concentric potentiometers to achieve this without needing to rely on button. It is certainly possible to emulate this in software, but I'll leave that for another day.

This plugin also features a proportional Q function. Every band features a decently wide Q setting to start, but narrows with the boost/attenuation of gain for each band. As you pull the gain up or down, the Q gets narrow. This is a behavior of the hardware 550B and is a great feature to have. It promotes smaller boosts/attenuations for color, and only boosting/attenuating large amount to identify and remove harsh frequencies. 
