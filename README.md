# ME3-ECM
Programming a microcontroller in Embedded C to drive an autonomous robot

*The following brief is part of an extended project brief provided to students in the last 3 weeks of the course.*

# 1. Scenario

A suspicious device has been discovered in the Mechanical Engineering foyer at Imperial College
London, South Kensington, UK. The area around the device has been cordoned off to a safe distance
and the evacuation of people in the immediate vicinity has begun.
Very little is known about the device at present except that it is emitting an infrared signal and is
probably set to detonate on a timer. An anonymous phone call to the police has led us to believe
that the device has a remote disarm capability; however, the disarm code is stored on the device
itself. It is too dangerous to send personnel in to retrieve the code and it is not known how long is
left before the device triggers.

# Challenge brief

Your task is to develop an autonomous robot that can enter a cordon, find the device, retrieve the
disarm code and return the code outside the cordon. Your robot must be able to perform the
following:
• Starting from outside the cordon (approximately 5 m in diameter) your robot must enter the
cordon and find the device
• Use the infrared pulses emitted from the device every 250 ms to locate the device
• Read and display a code from a 125 kHz RFID tag on the device
• Return to outside the cordon, as close to the starting position as possible
Your robot must also meet the following criteria:
• Powered by no more than 8 x AA NiMh batteries
• Be fully autonomous, i.e. no remote control
• Use the PIC18F4331 as supplied in the course
All components that have been used in the previous labs will be permitted for use in this challenge.
The following additional components will also be provided:
• 2 x IR proximity sensors
• RFID reader
• 8 x AA NiMh batteries, charger and battery clip
• Toggle switch for power
• 5V Voltage regulator and smoothing capacitors
