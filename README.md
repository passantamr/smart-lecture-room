# smart-lecture-room
embedded project using Atmega32 created by bassant amr in this project we make our lecture room smart if a student enters the room there will be two condition 
<p>
first -> if the light intensity is low the lamp is automatic light up and if light intensity is high the lamp never be on
second -> if (temp < 30c) ==> the fan is off else the fan is on in specific speed depend on reading of temp 
--->if temp >= 120c ==> the fan will rotate by maximuim speed 
--->else if (temp >= 90) ==> the fan will rotate by 75% from maximuim speed 
--->else if (temp >= 60) ==> the fan will rotate by 50% from maximuim speed 
--->else if (temp >= 30) ==> the fan will rotate by 25% from maximuim speed
if the student comes out from that room the fan & lamp automatic turn off
</p>
<h3>microcontroller </h3>
in this project we will use ATmega32 which have 4 port and 8 pins for each port
<h2>Drivers used</h2>
<h3>relay</h3>
when we need to turn lamp on we write logic high on pin of relay
and two turn it off we write logic low
<h3>pir sensor</h3>
there are two pir sensors one to detect enter of an student and another to detect coming out
when detecting, it gives logic high else it gives logic low
<h3>ldr sensor</h3>
it is used to detect intensity of illumination 
<p>if there is high intensity of illumination the voltage will be nearly zero</p>
<p>if there is low intensity of illumination the voltage will be nearly 5v</p>
<h3>10 bit ADC</h3>
we need to use 10-bit ADC (analog to digital converter) to convert analog input from LM35 & from ldr sensors into digital value (0-1023)
in atmega32 we have 8 pins (PORT A) analog and one ADC which can convert only one channel at a time
<h3>Temperature sensor </h3>
we need to use LM35 temp sensor which return analog value (0-5v) connected to PA2 (PORT A - PIN_num 2) (channel 2)
<h3>FAN (DC-Motor) </h3>
the aim of this project is to enable fan based on temperature so we need DC-Motor which will act as fan
but before this we need to use H-bridge chip which control two importand parameter of DC-motor 
first is speed. we can control speed of Motor by apply different voltages Level (0-5v in our case)
second parameter is direction of rotate controlled by polarity of volt ( + / - )
L293D (H-brige chip used ) connected to microcontroller on 3 pins PB0 & PB1 to control rotate direction
and PB3 to apply PWM with different duty cycle. the chip will take average vale of PWM and apply it to dc motor
<h3>PWM</h3>
we generate PWM(Pulse Width Modulation) with different duty cycles to control speed of motor
if we have in our case PWM with duty cycle 
-> 0% = avr voltage = 0
-> 25% = avr voltage 1.25 apply to dc motor
-> 50% = avr voltage 2.5 apply to dc motor
-> 75% = avr voltage 3.75 
-> 100% = avr voltage 5v
<h3> LCD</h3>
we need to use 16X2 8-bit mode LCD to display two lines
-> first: state of fan (ON - OFF)
-> second: sensor reading (temp)
we connect data path to PORTC
RS -> PD0
E -> PD1
R/W & VSS -> GND
VDD -> 5v
