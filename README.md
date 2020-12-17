# ATTINY85 Delayed Off

This project uses an ATTINY85 to control a battery powered LED light source.  
It detects if there is an input voltage coming from the mains side and turn on the LED.  
If the input voltage drops away, the LED will stay on for a while longer and dim in stages before turning off.  
When the LED is off, the microcontroller goes into deep sleep to not drain the battery.


## Schematics

*TODO*

## Programming the ATTINY85

For the programming of the ATTINY85, a standard, official arduino UNO was used as ISP.

The following guide was used to be able to program the ATTINY85 via the Arduino uno:  
https://www.instructables.com/id/How-to-Program-an-Attiny85-From-an-Arduino-Uno/

Which I assume was based of this guide:  
http://highlowtech.org/?p=1695
