# DISARMED!

Heavily inspired by (Keep Talking and Nobody Explodes)[https://keeptalkinggame.com/] and (Bomb Corp)[https://www.jackboxgames.com/bomb-corp/]
A physical "Bop-It for adults". 

This ammounts to a electroncs and software programming project, with a side-helping of game design and art!

## The SSD Module
The Seven Segment Display Module is soemthing I unfortunately based on the LD8041C/D series of 20mm seven segment displays.
Having bought several 10 years ago, I found that they seem to be no longer manufactured, so I just have the one board that is finished.
JCLPCB manufactures in minimum lots of 5, so I have 4 useless, large PCBs. At least the one works.

(For the REV2 board, the one I got manufactured, I accidently left out a single line segment of a trace when refactoring some of the runs... thankfully, I was able to bridge the gap with a single wire. This is fixed in REV3+).

In the future, I'll source some new SSD parts and update the boards, possibly with a denser layout.

The board uses MAX7219CNG LED/IO drivers over SPI. A MCP41010 is used to digitally control ISET, though in practice this was set to it's maximum value, and the SSD brightness is controlled via the Intensity register rin the MAX7219.

![](asset/SSD_Module.gif)
![](asset/SSD_Front.png)
![](asset/SSD_Back.png)

The test code was prototyped on a NodeMCU ESP8266 breakout, and then ported down to a Adafruit Trinket (ATTiny85). The TinySPI library was used to bridge the gaps.
I tried using libraries for both the MAX7219 and MCP41010 chip, but took exception to the complexity of the code and ended up implementing my own simple driving functions.
Future revisions of the board may implement an I2C interface and use an on-board MCU to drive the MAC7219 and MCP41010.