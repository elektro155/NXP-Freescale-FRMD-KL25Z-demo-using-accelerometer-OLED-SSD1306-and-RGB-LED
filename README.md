NXP Freescale FRMD-KL25Z demo using accelerometer, SSD1306 128*32 OLED display  and RGB LED. The display shows the readings of all 3 accelerometer axes values, 
the RGB LED changes the color according to physical position of the board. Moreover, due to the same value of all 3 cathode resistors for RGB led (all 220 ohm), the colors were 
uneven (e.g. the yellow was orange due to domination of red) and it was corrected by using PWM to dim the LEDs that were too bright.

Built with Mbed.com online compiler with NXP Freescale FRMD-KL25Z board chosen as build target
