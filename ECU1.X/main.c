
#include <xc.h>
#include "adc.h"
#include "matrix_keypad.h"
#include "can.h"
#include "msg_id.h"

#define _XTAL_FREQ 20000000

void main(void){
    unsigned int speed;
    unsigned char key;
    unsigned char gear_index = 0;
    unsigned char sp[3];

    const char gear[8][3] ={"ON","GN","G1","G2","G3","G4","G5","GR"};

    init_matrix_keypad();
    init_adc();
    init_can();

    while (1){
        key = read_switches(STATE_CHANGE);
        if (key == MK_SW1){
            if (gear_index < 7){
                gear_index++;
            }
        }else if (key == MK_SW2){
            if (gear_index > 0){
                gear_index--;
            }
        }
        speed = (unsigned int)(read_adc(CHANNEL4) / 10.33);

        if (speed > 99){
            speed = 100;
        }

        sp[0] = (unsigned char)(speed / 10) + '0';
        sp[1] = (unsigned char)(speed % 10) + '0';
        sp[2] = '\0';

        can_transmit(SPEED_MSG_ID, sp, 2);
        __delay_ms(80);

        can_transmit(GEAR_MSG_ID, (const uint8_t *)gear[gear_index], 2);
        __delay_ms(80);
    }
}
