
#include <xc.h>
#include "dkp.h"

void init_dkp()
{
    TRISC = TRISC | 0x0F;
    PORTC = PORTC | 0x0F; 
}

char read_dkp(char state)
{
    if(state == LEVEL)
    {
        return PORTC & 0x0F;
    }
    else if(state == EDGE)
    {
        static char once = 1;
        if(((PORTC & 0x0F) != 0x0F) && (once == 1))
        {
            once = 0;
            return PORTC & 0x0F;
        }
        else if((PORTC & 0x0F) == 0x0F)
        {
            once = 1;
        }
    }
    return 0x0F;
}
