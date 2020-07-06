#include "mbed.h"
#include "MMA8451Q.h"
#include "Adafruit_SSD1306.h"

#define MMA8451_I2C_ADDRESS (0x1d<<1)

PinName const SDA = PTE25;
PinName const SCL = PTE24;

float logistic_function(float in)
{ 
    //y = 1 / (1 + exp(-(x-0,5)*10))
    double pow_to = ((-in)+0.5)*10;
    return (1/(1+(float)exp(pow_to)))-0.007;
}

int main(void)
{
    MMA8451Q acc(SDA, SCL, MMA8451_I2C_ADDRESS);

    PwmOut rled(LED1);
    PwmOut gled(LED2);
    PwmOut bled(LED3);
    rled = 1.0f;
    gled = 1.0f;
    bled = 1.0f;    

    printf("MMA8451 ID: %d\n", acc.getWhoAmI());
    
    I2C i2c(PTE0, PTE1);  // I2C i2c(DATA,CLOCK);
    Adafruit_SSD1306_I2c oled(i2c,NC,0x78,32,128);
    
    oled.begin();
    oled.clearDisplay();
    oled.splash();
    oled.display(); 
    
    wait(2.0f);
    
    uint16_t counter = 0U;

    while (true) 
    {
        float x, y, z;
        x = acc.getAccX();
        y = acc.getAccY();
        z = acc.getAccZ();
#if 0       
        rled = abs(x) > 0.5f ? 0.8f : 1.0f; //0.8 to adjust brightness
        gled = abs(y) > 0.5f ? 0.4f : 1.0f; //0.4 to adjust brightness
        bled = abs(z) > 0.5f ? 0.0f : 1.0f;
#else
        rled = abs(x) > 0.1f ? logistic_function(1.0f - abs((x - 0.1f) * 0.2f)) : 1.0f;
        gled = abs(y) > 0.1f ? logistic_function(1.0f - abs((y - 0.1f) * 0.6f)) : 1.0f;
        bled = abs(z) > 0.1f ? logistic_function(1.0f - abs (z - 0.1f)        ) : 1.0f;
#endif        
        if(counter > 2U) //true every third time
        {
            //printf("Accelerometer [m/s2]\r\nX: %3.2f\r\nY: %3.2f\r\nZ: %3.2f", x*10.0f, y*10.0f, z*10.0f);
            oled.clearDisplay();
            oled.setTextCursor(0, 0); 
            oled.printf("Accelerometer [m/s2]\r\nX: %3.2f\r\nY: %3.2f\r\nZ: %3.2f", x*10.0f, y*10.0f, z*10.0f);
            oled.display(); 
            counter = 0;
        }
        else
        {
            wait(0.1f);
            ++counter;
        }
    }
}
