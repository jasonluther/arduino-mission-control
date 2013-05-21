## Parts

* Any Arduino will do. I used the [Arduino Uno](https://www.sparkfun.com/products/11021). 
* The enclosure is a [wine box](http://www.plumpjackwines.com/)
* Assorted resistors
* The RADAR display cover is a yogurt lid
* [Misc.](http://www.radioshack.com/product/index.jsp?productId=2103799) [proto](https://www.sparkfun.com/products/8815) [boards](http://www.radioshack.com/product/index.jsp?productId=2104052&locale=en_US)
* Salvaged speaker

### Sparkfun

* Arcade-style buttons: [Red](https://www.sparkfun.com/products/9336), [Green](https://www.sparkfun.com/products/9341), [Yellow](https://www.sparkfun.com/products/9338)
* [Key switch](https://www.sparkfun.com/products/11473) &mdash; I have already lost the keys)
* [Missile switch cover](https://www.sparkfun.com/products/9278) &mdash; Doesn't stay open very well
* [Toggle switches](https://www.sparkfun.com/products/9276)
* [Rotary pots](https://www.sparkfun.com/products/9939) and [knob](https://www.sparkfun.com/products/10001) & [knob](https://www.sparkfun.com/products/10002)
* 4 x [TPIC6B595 shift registers](https://www.sparkfun.com/products/734) to drive the 16-segment display and other outputs
* [16-segment LED display](https://www.sparkfun.com/products/9934)
* [Launch button](https://www.sparkfun.com/products/9181)
* [RGB LED](https://www.sparkfun.com/products/11120) &mdash; common-cathode, using a 100 ohm resistor for green, 100 for blue and 220 for red with the 5v PWM output
* A whole bunch of plain old [green LEDs](https://www.sparkfun.com/products/9855) for the RADAR display
* [10mm LED holders](https://www.sparkfun.com/products/11148)
* [DIP sockets](https://www.sparkfun.com/products/7940) because I'm too chicken to solder the shift registers and 16-segment display (I cut [this](https://www.sparkfun.com/products/9095) up).
* [Power switch](https://www.sparkfun.com/products/11138)
* [Battery holder](https://www.sparkfun.com/products/552)

### Adafruit

* [Common-anode RGB LED](https://www.adafruit.com/products/848) &mdash; this LED is controlled by 3 of the shift register outputs, giving you red, green, blue, cyan, magenta, yellow, and "white." It's a very bright LED, so I connected the anode to a PWM output on the Arduino, which lets me use a lower duty cycle to dim it. 

### Amazon

* [DC setup-up converter](http://www.amazon.com/gp/product/B00AMZEUYU/ref=oh_details_o05_s03_i02?ie=UTF8&psc=1) &mdash; I designed the RADAR display to run from a 9v source, which was probably a mistake (though it saved on resistors and soldering), so I need to go from the regulated 5v supply from the Arduino (or the 6v from the batteries) to 9v. This also drives the launch button LED, which I think is meant for 12v. 
* Random 5v relay. This was a last-minute addition. I recommend buying a relay with a datasheet so you don't waste your time trying to figure out what each pin does. 
