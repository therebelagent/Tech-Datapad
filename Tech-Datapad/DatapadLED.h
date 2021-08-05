#ifndef DatapadLED_h
#define DatapadLED_h

class DatapadLED
{
public:
    DatapadLED(uint8_t pin);
    void turnOn();
    void turnOff();

private:
    uint8_t _pin;
};

#endif