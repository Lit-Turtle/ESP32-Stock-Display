# Assembly Instructions

## 1. Prepare the Case

3D print all three pieces of the case:

- Base
- Roof
- Cap

Remove all supports from the three pieces.

<img width="3449" height="2046" alt="3DPrintedPieces1" src="https://github.com/user-attachments/assets/c40bf4ee-0255-492a-a235-3a4a6d14d59e" />

## 2. Order the PCB and Components

Order the PCB using the included BOM and CPL files. JLCPCB is recommended if using these files.
You will also need to order the following components:

- Switch
- PD module
- ESP32 development board
- Photoresistor
- Dot matrix display
- Screen filter or tint
- Screen

The screen can be glass, plexiglass, acrylic, or a similar material. The recommended dimensions are: 147 mm x 41 mm x 4 mm

<img width="3291" height="2063" alt="Components2" src="https://github.com/user-attachments/assets/c6f9428d-ea1c-4c9d-b0a1-99ddf131cc68" />

## 3. Check the Fit

Before assembling anything, make sure all of the components fit properly in the case.

The PD module should slide between the blocks in the power section and fit underneath the PD module cap. Make sure the USB-C port lines up with the opening on the side of the case.
Check that the switch fits properly in its opening.

The dot matrix should fit between the screen and the case. Also make sure the screen can slide into its slot with the dot matrix positioned behind it.

<img width="3468" height="2154" alt="Placement3" src="https://github.com/user-attachments/assets/ebea3287-1d28-4578-b6e0-92a406626845" />

## 4. Prepare the PCB

Solder all of the required components onto the PCB.

If you are using JLCPCB with the included BOM and CPL files, most of the components will already be assembled. You will only need to solder the 10k ohm photoresistor and the wires for Vin, Vout, and GND.

Leave the Vout and GND wires longer than the Vin wire. The extra length will make the later assembly easier.

Your finished PCB should look similar to the reference image.

<img width="2411" height="2537" alt="Board4" src="https://github.com/user-attachments/assets/dc8685f9-13d7-4df5-b667-9ff5ddac33a0" />

You may also need to solder the screw terminal onto the PD module if it does not already have one installed.

## 5. Install the PD Module and PCB

All of the electronics will be installed inside the base.

Start with the power section. Place the PD module into its designated location and adjust it so the USB-C port is as flush with the side of the case as possible.

<img width="663" height="416" alt="CaseBaseShaded" src="https://github.com/user-attachments/assets/c7e52567-67ac-4303-8ae8-de12c5da1353" />

Place the PCB on top of the two rails in the base. The Vin side of the PCB should face the switch and outside of the case, while the Vout side should face the ESP32 and center of the case.

## 6. Connect the Power Switch

Before connecting the wires to the switch, connect the wire from the PD module to the VCC screw terminal.

A red wire is recommended for this connection to make the wiring easier to identify, although the color is not required.

Insert the exposed copper strands into the VCC screw terminal and tighten the screw until the wire is secure.

Do not connect the other end of this wire to the switch yet. Leaving the wire disconnected makes it easier to install the switch later.

Next, solder the other switch wire to the Vin connection on the PCB. You can solder the wire directly into the Vin hole, but using a separate connection point may make the assembly easier to work with.

Connect the GND wire next to Vin to the GND screw terminal on the PD module.

At this point, the PD module should have its VCC connected to the switch wire and its GND connected to the PCB GND. The two switch wires should still be disconnected from the physical switch.

Place the PD module cap over the module and adjust both pieces until the USB-C port is properly aligned with the opening in the case.

## 7. Install the Switch

Slide the switch into its opening with the switch facing outward.

Make sure the tabs on the switch are vertical. The outer tab should be closer to the screen side of the case and farther away from the back wall.

Once the switch is positioned correctly, connect the red wire from the PD module VCC terminal to the outer tab.

Connect the black wire from PCB Vin to the middle tab.

<img width="1808" height="2809" alt="PowerArea5" src="https://github.com/user-attachments/assets/de412606-3c79-4529-a66e-1c872be2109a" />

## 8. Connect the ESP32 Power

Route the Vout and GND wires from the PCB through the circular hole into the ESP32 section.

The ESP32 and dot matrix will share the same power connections, so the Vout and GND wires need to be split into parallel connections.

Strip a small section of insulation from the middle of the Vout wire. Take another wire, preferably the same color, and wrap the exposed end around this section. Solder the connection.

Repeat the same process for the GND wire.

<img width="2470" height="2599" alt="Splits6" src="https://github.com/user-attachments/assets/1b5bf6d7-2bb2-4622-b9a5-21153870c3d3" />

The resulting connections should provide power to both the ESP32 and the dot matrix.

Vout should connect to ESP32 Vin and dot matrix VCC.

GND should connect to ESP32 GND and dot matrix GND.

## 9. Connect the ESP32 to the Dot Matrix

There are two ways to connect the ESP32 to the dot matrix.

### Jumper Wires

This method is recommended if your dot matrix already has pin headers installed.

Install the required pin headers on the ESP32 and use jumper wires to connect the ESP32 to the corresponding pins on the dot matrix.

<img width="1773" height="2325" alt="PinHeader7" src="https://github.com/user-attachments/assets/27426311-04d3-4c6e-a4c4-34e39a35625e" />

Route the wires through the narrow section on the side of the case where the dot matrix is located. The connections should remain toward the ESP32 side.

<img width="2527" height="3358" alt="WirePass8" src="https://github.com/user-attachments/assets/ff1394d9-800d-42f0-a443-0e02e9cb04ad" />

### Direct Wiring

Alternatively, you can solder wires directly between the ESP32 and the dot matrix.

The wires can be routed through the side opening or through the gap between the ESP32 and dot matrix sections.

Make sure the DATA, CS, and CLK connections match the pins specified in the code.

## 10. Install the Screen

Make sure the screen can slide completely into its slot with the dot matrix positioned behind it.

Do not force the screen into place. If it does not fit properly, check the position of the dot matrix and the screen dimensions.

<img width="3573" height="1950" alt="AllPieces8" src="https://github.com/user-attachments/assets/e6bd7521-89a0-4f98-84e3-e8c8ebc38b07" />

## 11. Program the ESP32

Install the Arduino IDE on your computer and set up the ESP32 board through the Arduino IDE Board Manager.

Connect the ESP32 to your computer using a USB to USB-C data cable. If your ESP32 uses Micro-USB, use a Micro-USB data cable instead.

Download or copy the project code from the GitHub repository and open it in Arduino IDE. 

Make sure you have the following libaries downloaded from Arduino IDE:
- ArduinoJson by Benoit Blanchon
- MD_MAX72XX by majicDesigns
- MD_Parola by majicDesigns

Before uploading the code, enter your Wi-Fi information in the following variables:
1. network_name
2. wifi_password

Enter your Wi-Fi network name for `network_name` and your Wi-Fi password for `wifi_password`.

<img width="844" height="343" alt="Code to Edit" src="https://github.com/user-attachments/assets/4c88e8af-96e1-4e53-b90d-056cd3ad30b4" />

This connection is required for the ESP32 to retrieve data from the internet.

Select the correct ESP32 board and COM port, then upload the code.

The upload may take a few moments. Once the ESP32 connects successfully, the Serial Monitor should provide a link to the device's web interface.

## 12. Test the Display

The display should show a pair of eyes after the code has been uploaded.

<img width="4032" height="2419" alt="EyeScreen9" src="https://github.com/user-attachments/assets/f8c12c15-a43e-45ef-8b3c-6a8211cf57a1" />

Open the web interface on another device connected to the same Wi-Fi network. From this page, you can change the information displayed on the matrix.

<img width="599" height="401" alt="NetworkWebsite" src="https://github.com/user-attachments/assets/52f04e38-8972-4b76-abe0-3715fac76d38" />

If the dot matrix turns on with every LED illuminated, the DATA, CS, or CLK connections are most likely incorrect. Check that these connections match the pins defined in the ESP32 code.

<img width="727" height="508" alt="ESP32-Pinout" src="https://github.com/user-attachments/assets/bfb42905-1f78-4c77-a019-50e7b42ac114" />

Do not continue with the final assembly until the display and web interface are working correctly.

## 13. Final Assembly

Once everything has been tested, press the components into their proper locations inside the base.

Make sure all components are below the top of the case so the roof can be installed. The photoresistor should remain exposed so it can pass through the opening in the roof.

If you are using heat-set threaded inserts, install them into the four holes on the top of the base.

<img width="3704" height="2185" alt="Heat Threads" src="https://github.com/user-attachments/assets/c4640e1d-159f-4c83-80d5-95382b529df1" />

Place the roof onto the base and guide the photoresistor through its opening. The photoresistor opening is slightly different from the four screw holes.

<img width="4032" height="2604" alt="PhotoThrough Roof" src="https://github.com/user-attachments/assets/e132deeb-4a90-4e77-9eb0-681ddc3a42fb" />

Install a screw into each of the four screw holes and tighten them until the roof is secure.

The assembly is now complete.
