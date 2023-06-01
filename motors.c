#include "motors.h"
/* motors_counter and battery_value are accessed here
 * motor numbers : 1 = Left ; 2 = Right ;
 */

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
    if(motor == 1) // Left
    {
        CCPR1L = (duty_value >> 2) & 0xFF; // 8 MSbs Left motor
        CCP1CONbits.DC1B = duty_value & 0b11; // 2 LSbs Left motor
    }
    else if(motor == 2) // Right
    {
        CCPR2L = (duty_value >> 2) & 0xFF; // 8 MSbs Right motor
        CCP2CONbits.DC2B = duty_value & 0b11; // 2 LSbs Right motor
    }
}

// Sets the speed of both motors to be the same.
void motorsSetSpeed(int speed/*unit ?*/)
{
    // Calculate duty cycle, divide by current battery level to try to adapt and keep a constant speed
    duty_cycle_percent = SPEED_MULTIPLIER * speed / battery_value; // should be less than 100

    if(duty_cycle_percent > 50) // Limit duty cycle to 50% (6V motors on 12V battery)
        duty_cycle_percent = 50;

    /* With our settings : Duty cycle 100% -> Duty value PR2 : proportionnality (approximated) */
    setDutyCycle(1, duty_cycle_percent * PR2 / 100); // Left motor
    setDutyCycle(2, duty_cycle_percent * PR2 / 100); // Right motor
}

void motorsTest(int duty_cycle_percent, int timer, int dir_left, int dir_right)
{
    PORTAbits.RA6 = dir_right; // Right motor Direction : ???
    PORTAbits.RA7 = dir_left; // Left motor Direction : ???

    motors_counter = timer;
    setDutyCycle(1, duty_cycle_percent * PR2 / 100); // Left motor
    setDutyCycle(2, duty_cycle_percent * PR2 / 100); // Right motor
}

void motorsForward(int max_distance, int speed/*unit ?*/)
{
    PORTAbits.RA6 = 1; // Right motor Direction : ???
    PORTAbits.RA7 = 1; // Left motor Direction : ???

    motors_counter = FORWARD_TIME_MULTIPLIER * max_distance / speed;
    motorsSetSpeed(speed);
}

void motorsTurnLeft(int angle, int speed)
{
    PORTAbits.RA6 = 1; // Right motor Direction : ???
    PORTAbits.RA7 = 0; // Left motor Direction : ???

    motors_counter = ROTATION_TIME_MULTIPLIER * angle / speed;
    motorsSetSpeed(speed);
}

void motorsTurnRight(int angle, int speed)
{
    PORTAbits.RA6 = 0; // Right motor Direction : ???
    PORTAbits.RA7 = 1; // Left motor Direction : ???

    motors_counter = ROTATION_TIME_MULTIPLIER * angle / speed;
    motorsSetSpeed(speed);
}

