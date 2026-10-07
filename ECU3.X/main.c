
#include <xc.h>
#include "clcd.h"
#include "can.h"
#include "msg_id.h"

#if 1
void init_config()
{
    TRISB = 0;
    PORTB = 0x00;
}

void main(void)
{   
    init_config();
    init_clcd();
    init_can();
    
    int rx_msg_id = 0;
    int rx_len = 0;
    char rx_data[5];

    int delay = 0;
    
    clcd_print("SPD",  LINE1(0));
    clcd_print("GEAR", LINE1(4));
    clcd_print("RPM",  LINE1(9));
    clcd_print("IND",  LINE1(13));

    while (1)
    {
        can_receive(&rx_msg_id, rx_data, &rx_len);

        if (rx_msg_id == SPEED_MSG_ID)
        {
            rx_data[2] = '\0';
            clcd_print(rx_data, LINE2(0));
        }

        else if (rx_msg_id == GEAR_MSG_ID)
        {
            rx_data[2] = '\0';
            clcd_print(rx_data, LINE2(4));
        }
          
        else if (rx_msg_id == RPM_MSG_ID)
        {
            rx_data[4] = '\0';
            clcd_print(rx_data, LINE2(9));
        }

        else if (rx_msg_id == INDICATOR_MSG_ID)
        {
            rx_data[2] = '\0';
            clcd_print(rx_data, LINE2(13));

            if (rx_data[0] == '<')
            {
                if (delay < 40)
                {
                    PORTB = 0x03;
                }
                else if (delay < 80)
                {
                    PORTB = 0x00;
                }
                else
                {
                    delay = 0;
                }

                delay++;
            }

            else if (rx_data[1] == '>')
            {
                if (delay < 40)
                {
                    PORTB = 0xC0;
                }
                else if (delay < 80)
                {
                    PORTB = 0x00;
                }
                else
                {
                    delay = 0;
                }

                delay++;
            }

            else
            {
                PORTB = 0x00;
                delay = 0;
            }
        }
    }
}
#endif