# ESP32-Stock-Display



https://github.com/user-attachments/assets/17d52d09-3d5c-4d5f-b84c-951d37e83fe0

This project displays live stock prices on a mirror-like display, with display specifics easily changeable through a local network(access point). The ESP32 acts as a STA mode enabling this to be a true IOT device. A robust power system allows this device to run on the recommended 9V from a USB-C input; switch on side to easily enable or disable the device; and a photoresistor to automatically turn off the device when the environment is dark. 

## Features

- 32 by 8 dot matrix display to easily display stock prices and animations.
- Mirror-like display that hides the grid pattern from dot matrix only allowing the powered lights to shine through.
- Wall anchors to easily setup display using screws or any wall hooks. 
- USB-C power plug, used for its widespread usage and that many people already have one.
- Robust power system, with side switch to quickly disable the display. Adjustable circuit that reactively cuts power if the surrounding environment is dark, for when sleeping or room lights or turned off. 
- Local network set up through the ESP32 allows any internet device connected to the same network to change what the display shows. 
- IOT device capabilities through the ESP32 connected to your wifi network, which grabs the live stock prices and the fear & greed index. 

## Tech Stack

**Hardware:** ESP32, MAX7219 32×8 LED Matrix, LM393 Comparator, NMOSFET, Photoresistor, USB-C PD Module  
**Software:** C++, Arduino IDE, HTML/CSS, JavaScript  
**CAD/PCB:** SolidWorks, KiCad  
**Manufacturing:** JLCPCB, 3D Printing  
**Connectivity:** Wi-Fi, REST APIs, Local Web Server

## Goal

The goal of this project is to develop a functional IoT device that can be easily integrated into users’ life. More specifically, creating an affordable stock ticker that can be easily customized to match individual financial strategies. 

## Why?

Being introduced to investing from a young age, I decided one day I want to see how much a stock ticker would be if I got one. So like most I searched it up on Amazon to see that prices ranged from $50 to $100 plus. When I got my hands on an ESP32 for the first time, I realized that a stock ticker would be something I can build. 

## System Architecture

<img width="1920" height="1080" alt="Stock Ticker System Arch" src="https://github.com/user-attachments/assets/70125a59-2791-4a41-9386-070c0a5d4818" />

## Design Process

### Initial Design

The general idea for the stock ticker has remained the same throughout, which is to use the ESP32 as the microcontroller in order to get data and the dot matrix for the display. I did consider a LCD screen, however I went with a dot matrix as I already had it on hand and it would be easier to see from afar.

The casing was not as set in stone, however I had some key features that I wanted to implement. Which is a compact case with straightforward wiring, easy to access ESP32, and secure dot matrix holder with screen holder in front. 

The PCB that disables and enables power depending on surrounding light level, was not initially part of the plan. However, the idea came in during the early design process while an improved light system was an improvement already being considered.

### Hardware Selection

ESP32 microcontroller for its wifi and web server capabilities. A perfect beginner microchip for IoT projects and ability to be programmed with C++ on Arduino IDE.  

MAX7219 dot matrix chosen for its financial aesthetic. Ability to display still and scrolling text without the need for fonts, with relatively simple ways to draw art.

JLCPCB for PCB fabrication as they have been reliable and affordable throughout the time I have used their service. For this project I also utilized their parts assembly service to have them solder the resistors, LM393, potentiometer, and mosfet. A PCB was used for the power system as it requires a decent amount of components, so PCB saves space and decreases opportunity for error.    

### PCB Development

The PCB board also had a couple iterations. Some were due to errors that either made the board faulty or gave unintended results. Other than errors some key changes were the use of a potentiometer with now facing upwards instead to the side for easier access when placed in a narrow case. Another change was the location of the 2 wires in and 2 wires out which were moved for easier assembly when in case, as power input is located on one side while the load is located on the opposite end. 

An annoying roadblock I ran into was regarding KiCad and its mosfets. Most mosfets use pinout gate, drain, source, however kiCad actually does not have a default footprint for that so you have to edit the pin number accordingly. Or else once you go into the PCB editor it will say you have it traced correctly but once you solder your mosfet it won’t work because the pins are different. For my situation the mosfet was drain, gate, source but my real life mosfet was gate, drain, source. So I had to flip the pin number for drain pin and gate pin in the schematic editor, when you click on component and edit footprint. 

### Enclosure Development

The case had 3 iterations, however each iteration had only minor iterations. The 1st to 2nd: adjusting wall mounting hole placement, lowered esp32 area to give space to wires from bottom of ESP32, addition of wire passing area from ESP32 to dot matrix, resizing of USB-C hole, and holding side walls for PD module. 2nd to final iteration is just the addition PCB holding ramps in the power section.

The PD module holding cap piece had quite a few iterations due to the fittings/holding method making it too snug or too loose. With such small dimensions and scenarios where proper fit was needed it of course can with some iterations. Other than small dimension changes the main change was a roof over the screw terminals which greatly benefitted the fit. 

### Screen Development

The screen is a glass piece. For my display I ordered a plexiglass due to it being cheaper. Though, any see-through material with the matching dimensions can be used. 

<img width="3252" height="2768" alt="Mirror Screen" src="https://github.com/user-attachments/assets/0b03bd67-8cc1-495b-83ea-764a066dd774" />

In order to hide the grid pattern from the dot matrix, I tested a couple different options. First, was frosted glass film, however, this blurred the light or had no effect due to the fact that the matrix was right next to the glass. A tint is also an optional film, however I found that it often blurs the light a bit too much, making text a bit difficult to read.

The recommended option is to use some sort of tint, the darkness varies to preference. However, for my project I decided to use a one way mirror tint as it completely hides the grid. Additionally, when turned off it looked like a regular mirror but when enabled gave a cool light in mirror effect. The exact ordered materials can be found below in the parts list. 
The screen was an area that proved to be sort of difficult. If the piece fits the dimensions 147mm x 41mm x 4mm it will be a great fit for the case. For my project I ordered plexiglass and a couple different filters. I will later mention what I tried but what worked was the tinted mirror filter. However, if your budget is greater, I would recommend getting glass instead of plexiglass. The plexiglass, at least that I ordered, has some uneven/bumpy surface which makes the tint difficult to apply, but even once applied some bumps are still noticeable. It does not make the text illegible however for a better look, a glass piece would be recommended. 


## Light ON/OFF PCB Board

The circuit was first designed on a breadboard to test the circuit design and concept.

<img width="4032" height="2516" alt="LightOnOFFBreadboard" src="https://github.com/user-attachments/assets/38e27949-839a-4953-bea3-9159770a92e0" />

<img width="626" height="227" alt="LightOnOffSchematic" src="https://github.com/user-attachments/assets/25261629-02e3-43a2-803a-49dff464c5dc" />

This circuit’s main component is the LM393 Comparator which compares the voltage between 2 input voltages. The 2 input voltages for our case will be determined by the photoresistor and potentiometer voltage dissipated. This means if potentiometer resistance is greater than photoresistor’s resistance then power is supplied and not supplied if reverse. Note that the photoresistor has increased resistance when dark. 

The 10k ohm resistor R3 acts as a pull-down resistor creating a potential difference to actually flow through the photoresistor so that there is voltage to be compared for the LM393, there must be a resistor in order to have the potential difference across be the full 9V through a voltage divider. The 10k ohm resistor R4 acts as a pull-up resistor because the LM393 is open-collector output. This is necessary for whenever the output is HIGH as it helps open the transistor gate. While the 1k ohm resistor R2 is necessary as the NMOSFET gate can cause current spikes and this resistor protects the comparator from these spikes. 

<img width="478" height="301" alt="LightOnOffPCBEditor" src="https://github.com/user-attachments/assets/79cdc7bd-29fe-491a-9ef0-502ef32f3f4b" />

Some key pieces to note are as follows. The vertical potentiometer though taking more space was selected for easier adjusting of potentiometer value due to the narrow width of the power area. Also the LM393 comparator has 2 comparators built in but only one was used. For my case I used pins 1, 2, and 3. It is key not to forget to connect pin 4 for ground and pin 8 for power in order to power the comparator. Another additional piece is the logo engraved in the top right, which was added for a more professional look and for copyright protection.

<img width="3024" height="2938" alt="SolderedPCB" src="https://github.com/user-attachments/assets/3716e39b-b25b-4d40-ae04-3fbd0c57269e" />

The PCB board was designed using kiCad and manufactured by JLCPCB. Some components were also soldered by JLCPCB.

## Enclosure

The shell of our display has 3 main pieces and one additional piece. Each part was designed in SolidWorks. 

<img width="663" height="416" alt="CaseBaseShaded" src="https://github.com/user-attachments/assets/e4be4b14-6455-4f25-b64c-c3742c4d3758" />

The first and most important piece is the base piece, which is the largest piece which holds all the components. The base piece has 3 main sections. The first is our power area which is where our switch, power input, and our pcb board will be located. The one connected to that is where our ESP32 will be located. The big area is then where our dot matrix display will be located and as you can see we have the small area to the right of that which is where the wiring between the ESP32 and dot matrix will pass through. 

<img width="600" height="454" alt="CaseCHolder" src="https://github.com/user-attachments/assets/f413ed08-676e-4a99-b7bc-139b7ca16b02" />

Some key features of the base is a cut out and shaping of our USB-C plug, which was designed to securely hold the PD lonely binary module.

<img width="391" height="410" alt="CaseIndent" src="https://github.com/user-attachments/assets/f5830c68-14fe-4ec1-a903-02024370abc0" />

<img width="560" height="255" alt="CaseWallMountShaded" src="https://github.com/user-attachments/assets/b4c79cba-b634-4dfc-aab4-da48cb5f1805" />

Another important area is the indent which will be important when it comes to our third piece. Lastly our wall mount which was designed for screws drilled into the wall or any similar mounting piece. This is an optional piece only for those who want to mount the display on a wall. However, this neat design allows for easy hooking of display if you choose to do so.  

<img width="695" height="369" alt="Screenshot 2026-08-09 214355" src="https://github.com/user-attachments/assets/f9126829-d6c3-4285-b98d-7d7968595c6f" />

The second piece is the roof of our case. This piece encloses the entire display. Attached to the base via the 4 aligning holes that were seen on the base. Which can then be connected using screws of your choice. There is one non-circular hole which is where you should pass the photoresistor through.

<img width="4032" height="2640" alt="DisplayScreen" src="https://github.com/user-attachments/assets/dddf1c0c-9b37-435a-9e84-2875f954471f" />

The last piece is a purchased piece and is the glass used to not only hold the matrix upright but also as a protector/screen for our display. This piece is also where chosen filters or tints can be applied onto. The main thing is the dimensions of the class, which is recommended to be 147mm x 41mm x 4mm. 

## Electrical/Wiring

The wiring of the display is relatively simple. Going by each section of the base it will be as follows.

For the power area, the power will first start from our PD USB-C module. This module was selected for its capabilities to easily switch between different voltage supplies. 

<img width="4032" height="2549" alt="PD Module" src="https://github.com/user-attachments/assets/6b8d3192-d376-4e19-b0f2-6b0b8f2ad2bf" />

This module will have 2 wires for power and ground. The positive end will then connect in series with the switch, which will connect to the PCB board along with our ground. Exiting the PCB board will be the load voltage out and load voltage back. These 2 wires will be the only 2 leaving from the power area.

These 2 wires will simply connect to the Vin and GND of the ESP32 located in the adjacent section.

Between the dot matrix and ESP32 will be 5 separate wires: VCC, GND, DIN, CS, and CLK. These should connect to the corresponding pins in the code, which will be discussed next.

## ESP32 Code

The ESP32 was programmed through the Arduino IDE. The entire details of the code will not be explained here as the code already contains comments.

The ESP32 is established as STA and AP mode, which means you will need to enter your own wifi network information for the ESP32 to function properly. You will also need to import some libraries for you to set up local sites and display everything text/images on the matrix. 

The key idea is that through the site users can select different modes that change what the display shows. If we are displaying stock prices or fear & greed indexes, the ESP32 will grab these prices or index through an api key and display the data.

You may easily add or modify existing modes to display what you would like. To add mode you would need to modify the 
```
enum DisplayMode { MODE_VOO, MODE_FEAR_GREED… };
```
Just add or remove any modes you would like. Then add or remove that option from our switch case.
```
switch(currentMode) {
	case MODE_VOO:
		html += “VOO Price”;
		break;
	case MODE_FEAR_GREED:
		html += “FEAR GREED INDEX”;
		break;
	…
}
```
A few lines down add options as well.
```
html += “<option value=’voo’” + String(currentMode == MODE_VOO ? “ selected” : “”) + “>VOO Price</option>”;
```

You will also need to add your new mode on line 265. 
```
If (mode == “voo”) 
	currentMode = MODE_VOO;
```
Lastly, in refreshData() you will also want to add another case for your new mode. 
```
void refreshData() {
 	String text;
  	switch (currentMode) {
    		case MODE_VOO:        
      		text = "" + getVOO();  
      		break;
```

If you are going to be grabbing data you may want to create a new get_() method. 

I will not bore you with the entire explanation but the code, with comments, will be included in this repository. 

## Final Assembly

https://youtu.be/V5j7vDCx7zQ

## Future Improvements

Some future improvements I would like to make is having a multi-color matrix display, so that way the color can indicate whether price is up or down and fear or greed. 

Another area is with the code, through the STA and AP mode with the matrix display, the display can really display any data you would like, just by modifying the code. Some examples are sport scores, Spotify listening/lyrics, weather, and any information you can grab data for.

## Parts List

[Filament](https://store.creality.com/products/hyper-pla-rfid-3d-printing-filament-1kg)

[Plexiglass](https://www.aliexpress.us/item/3256803346944118.html?spm=a2g0o.order_list.order_list_main.67.24181802kA2GZw&gatewayAdapt=glo2usa)
Specific dimensions may need to be requested.

[Regular Tint](https://www.aliexpress.us/item/3256806769429614.html?spm=a2g0o.order_list.order_list_main.31.24181802kA2GZw&gatewayAdapt=glo2usa) 

[Mirror Tint](https://www.aliexpress.us/item/3256805054544955.html?spm=a2g0o.order_list.order_list_main.25.24181802asub1n&gatewayAdapt=glo2usa)

[PD Module](https://www.amazon.com/dp/B0GTTTGJNX?ref=ppx_yo2ov_dt_b_fed_asin_title)

[ESP32 Dev Kit](https://www.amazon.com/AITRIP-ESP-WROOM-32-Development-Microcontroller-Integrated/dp/B0CR5Y2JVD/ref=sr_1_1?crid=3HMS0HGSKDNML&dib=eyJ2IjoiMSJ9.tlEgtodKxzuN0g415RvogJ9rYXJoO8upIYS5PvzufUholvvbgrSMoATy88YBrDUMsVK_267AtcxdVOMvpnRN3JxRdwY5ajE94o7FuF6kP8UbRQ_R5-6ZFWVuc79f6q9UmhrXJvAQKpqtLK7_ADqh7-EMpJ20e7kyqC10i0E8b1JLo6fzROLwCpDBxImSfZgF2OzIWKxzKatcezhrGymAoUku82l4rqt1Vv_y_vvpAdw.K2Tj7T_zjuJzlCoMA94YJDnd-WUprk-ZAKBdRV3rSrI&dib_tag=se&keywords=AITRIP%2B3PCS%2BType%2Bc%2B30pins%2BCP2102%2BESP-WROOM-32%2BESP32%2BESP-32S%2BDevelopment%2BBoard%2B2.4GHz%2BDual-Mode%2BWiFi%2B%2B%2BBluetooth%2BDual%2BCores%2BMicrocontroller%2BProcessor%2BIntegrated%2Bwith%2BAntenna%2BRF%2BAMP%2BFilter%2BAP%2BSTA&nsdOptOutParam=true&qid=1785213963&sprefix=aitrip%2B3pcs%2Btype%2Bc%2B30pins%2Bcp2102%2Besp-wroom-32%2Besp32%2Besp-32s%2Bdevelopment%2Bboard%2B2.4ghz%2Bdual-mode%2Bwifi%2B%2B%2Bbluetooth%2Bdual%2Bcores%2Bmicrocontroller%2Bprocessor%2Bintegrated%2Bwith%2Bantenna%2Brf%2Bamp%2Bfilter%2Bap%2Bsta%2Caps%2C204&sr=8-1&th=1)

[Dot Matrix](https://www.aliexpress.us/item/3256805668841965.html?spm=a2g0o.order_list.order_list_main.148.24181802kA2GZw&gatewayAdapt=glo2usa)

[Switch](https://www.aliexpress.us/item/3256809828963002.html?spm=a2g0o.order_list.order_list_main.103.24181802kA2GZw&gatewayAdapt=glo2usa)

[Photoresistor](https://www.amazon.com/dp/B0CM5YNGSF?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)

[Heat Press Thread Insert](https://www.amazon.com/dp/B0CTCH68LT?ref=ppx_yo2ov_dt_b_fed_asin_title)

[M3 8mm Screws](https://www.amazon.com/dp/B07CMSBQ11?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)

---

Part Number for Components

Potentiometer: LCSC Part # C116302

LM393 Comparator: LCSC Part # C5252905

NMOSFET: LCSC Part # C2557


