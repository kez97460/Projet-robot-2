#include "motors.h"

extern volatile int motors_counter; // counts time for the motors. Can be modified by motors.c and main.c
extern volatile int battery_value; // mean of all 4 measurements, accessed by motor.c, modified by main.c 
int duty_cycle_percent; // between 0 and 100

void motorsStop()
{
    CCPR1L = 0; // duty cycle 1 = 0
    CCP1CONbits.DC1B = 0;
    
    CCPR2L = 0; // duty cycle 2 = 0
    CCP2CONbits.DC2B = 0;

    motors_counter = 0;
}

// Sets the duty cycle control registers for the specified motor. Duty values are between 0 and 500 here normally
void setDutyCycle(int motor, int duty_value)
{
    if(motor == 1)
    {
        CCPR1L = (duty_value >> 2) & 0xFF; // 8 MSbs motor 1
        CCP1CONbits.DC1B = duty_value & 0b11; // 2 LSbs motor 1
    }
    else if(motor == 2)
    {
        CCPR2L = (duty_value >> 2) & 0xFF; // 8 MSbs motor 2
        CCP2CONbits.DC2B = duty_value & 0b11; // 2 LSbs motor 2
    }
}


void moteursSetSpeed(int speed/*unit� ?*/)
{
    // Calculate duty cycle, divide by current battery level to try to adapt and keep a constant speed
    duty_cycle_percent = SPEED_MULTIPLIER * speed / battery_value; // should be less than 100

    if(duty_cycle_percent > 50) // Limit duty cycle to 50% (6V motors on 12V battery)
        duty_cycle_percent = 50;

    /* With our settings : Duty cycle 100% -> Duty value 500 */
    setDutyCycle(1, 5 * duty_cycle_percent); // motor 1
    setDutyCycle(2, 5 * duty_cycle_percent); // motor 2
}

void moteursForward(int max_distance, int speed/*unit� ?*/)
{
    
}