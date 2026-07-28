# ESP32-Stock-Display

This project displays live stock prices on a mirror-like display, with display specifics easily changeable through a local network(access point). The ESP32 acts as a STA mode enabling this to be a true IOT device. A robust power system allows this device to run on the recommended 9V from a USB-C input; switch on side to easily enable or disable the device; and a photoresistor to automatically turn off the device when the environment is dark. 

## Features

32 by 8 dot matrix display to easily display stock prices and animations.
Mirror-like display that hides the grid pattern from dot matrix only allowing the powered lights to shine through.
Wall anchors to easily setup display using screws or any wall hooks. 
USB-C power plug, used for its widespread usage and that many people already have one.
Robust power system, with side switch to quickly disable display. Adjustable circuit that reactively cuts power if the surrounding environment is dark, for when sleeping or room lights or turned off. 
Local network set up through the ESP32 allows any internet device connected to the same network to change what the display shows. 
IOT device capabilities through the ESP32 connected to your wifi network, which grabs the live stock prices and the fear & greed index. 

## Light On/OFF PCB Board

The circuit was first designed on a breadboard to test the circuit design and concept.

![Photo of Light On/Off Breadboard](<img width="4032" height="2516" alt="LightOnOFFBreadboard" src="https://github.com/user-attachments/assets/5451ab9d-7e8b-4a22-a078-aee2360ae3ae" />
)
