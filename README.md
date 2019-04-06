# Matrix LED display

## Hardware

| Type | Name | Link |
|---|---|---|
| Board | ESP32 Dev board | [Ebay](https://www.ebay.fr/itm/Espressif-ESP32-WLAN-Dev-Kit-Board-Development-Bluetooth-Wifi-v1-WROOM32-NodeMCU/253059783728?hash=item3aeb89dc30:g:5-8AAOSwAThb3MaZ) |
| GPS | Neo 7M | [Ebay](https://www.ebay.fr/itm/GYGPSV3-NEO7M-NEO-7M-000-GPS-Module-MWC-APM2-6-Replace-NEO-6M-GYGPS6MV2/263140805346?ssPageName=STRK%3AMEBIDX%3AIT&var=562139675590&_trksid=p2057872.m2749.l2649) |
| Display | 2 x MAX7219 Matrix Led 8*32 | [Ebay](https://www.ebay.fr/itm/MAX7219-Pois-Module-4-In-1-Affichage-Led-pour-Arduino-Microcontr%C3%B4leur-Pi%C3%A8ces/153358141494?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649) |
<!--| | |-->

## Pinout & wiring

*Coming soon*

## Features

- Draw a message with different effect
- Animate sprite over a text
- Draw a graphic
- Show GPS data (Altitude, Date, Time, Position, Speed)

**User interaction**

- Change the current mod on button press
- Manage the system over the Bluetooth (*Coming soon*)

## How it work

This project is developed around the `Mod` concept: 

- **MessageMod**: Include all things about the drawing of text 
- **GraphMod**: Include all things about the drawing of a graphic element 
- **TrackingMod**: Include all things about the GPS data

Each mod are a own system to manage the drawing on the Matrix Led display.

If you want to add a mod, you can just add another and let's play !

If you want to improve a mod, you can. They are no impact in another mod. 

## Gallery

*Coming soon*