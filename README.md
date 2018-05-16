# Wemos Websocket LED

The Arduino's Wemos Websocket project, by Clever Cloud.

The Wemos is connected to a LED strip. This strip is a gradient defined by two colors. When a new color is selected, the gradient goes from the new color to the old one.

## Interact with the strip

You can change the color of the strip thanks to the interface given by the [wemos-ws-led-backend](https://github.com/CleverCloud/wemos-ws-led-backend) project.

The websocket client waits for a string that defines the color (format: RRRGGGBBB).

> :rotating_light: If the first LED flashes red, the connection is closed. Verify your network configuration and restart the Wemos.

## Installation

### Hardware

Connect the LED strip to the Wemos using the small cables:

 - Connect the red cable of the LED strip to the +5V of the Wemos
 - Connect the white cable of the LED strip to the GND (ground) of the Wemos
 - Connect the green cable of the LED strip to the D4 of the Wemos

Here is how it should look like: [howitshouldlooklike.jpg](https://raw.githubusercontent.com/CleverCloud/wemos-ws-led/master/howitshouldlooklike.jpg)

Now, plug the Wemos into your computer.

### Software

On Linux, it should work out of the box.

For Windows and Mac OS, you need to dowload a driver: https://wiki.wemos.cc/downloads

For Mac OS, here is a detailed article on how to get started with Wemos: https://blog.rjdlee.com/getting-started-with-wemos-d1-on-mac-osx/

#### Arduino IDE

Install the Arduino IDE: https://www.arduino.cc/en/Main/Software

In order to interact with the Wemos, you have to configure the Arduino IDE. If you can't find the `WeMos D1 R2 & mini` board in `Tools > Board`, do the following:

1. Open preferences `File > Preferences`.
2. Add the line "`http://arduino.esp8266.com/stable/package_esp8266com_index.json`" in the `Additional Boards Manager URLs` field and close `Preferences`.
3. Open `Tools > Board > Boards Manager` and search `ESP8266`.
4. Install the `ESP8266 by ESP8266 community`.
5. Choose the `WeMos D1 R2 & mini` in `Tools > Board`.

You also have to clone the two git repositories specified at the top of the file into the `libraries` folder. (open `File > Preferences` and look at the Sketchbook location to find the `libraries` path).

#### Upload to the board

1. Select the right USB port in `Tools > Port`.
2. Change the SSID, wifi password and the hostname (your_app_id.cleverapps.io).
3. Click on the `Verify` button.
4. If there is no error, `Upload` it to the Wemos.
