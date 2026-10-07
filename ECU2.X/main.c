

#include <xc.h>
#include "adc.h"
#include "dkp.h"
#include "can.h"
#include "msg_id.h"
#define _XTAL_FREQ 20000000

#if 1
void main(void)
{
    init_dkp();
    init_adc();
    init_can();

    int rpm;
    char rpm_data[5];
    char ind_data[3];

    int left = 0;
    int right = 0;

    while (1)
    {
        rpm = read_adc(CHANNEL4) / 0.1705;

        rpm_data[0] = rpm / 1000 + '0';
        rpm_data[1] = (rpm / 100) % 10 + '0';
        rpm_data[2] = (rpm / 10) % 10 + '0';
        rpm_data[3] = rpm % 10 + '0';
        rpm_data[4] = '\0';

        char key = read_dkp(EDGE);

        if (key == DKP1)
        {
            left = 1;
            right = 0;
        }
        else if (key == DKP2)
        {
            right = 1;
            left = 0;
        }
        else if (key == DKP3)
        {
            left = 0;
            right = 0;
        }

        if (left == 1)
        {
            ind_data[0] = '<';
            ind_data[1] = '-';
            ind_data[2] = '\0';
        }
        else if (right == 1)
        {
            ind_data[0] = '-';
            ind_data[1] = '>';
            ind_data[2] = '\0';
        }
        else
        {
            ind_data[0] = ' ';
            ind_data[1] = ' ';
            ind_data[2] = '\0';
        }

        can_transmit(RPM_MSG_ID, rpm_data, 4);

        __delay_ms(80);

        can_transmit(INDICATOR_MSG_ID, ind_data, 2);

        __delay_ms(80);
    }
}
#endif