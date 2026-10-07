
#include <xc.h>
#include "can.h"
typedef enum _CanOpMode {
    e_can_op_mode_normal = 0x00,
    e_can_op_mode_loop = 0x40,
    e_can_op_mode_config = 0x80
} CanOpMode;

void init_can(void) {
    TRISB2 = 0; // CAN TX
    TRISB3 = 1; // CAN RX
    CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_config); 
    while (CANSTAT != 0x80);

    ECANCON = 0x00;
    BRGCON1 = 0xE1; /* 1110 0001, SJW=4, TQ, BRP 4 */
    BRGCON2 = 0x1B; /* 0001 1011, SEG2PHTS 1 sampled once PS1=4TQ PropagationT 4TQ */
    BRGCON3 = 0x03; /* 0000 0011, PS2, 4TQ */

    RXFCON0 = 0x00;
    CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_normal);

    RXB0CON = 0x00;
    RXB0CONbits.RXM0 = 1;
    RXB0CONbits.RXM1 = 1;
}

static uint16_t get_msg_id_std(void) {
    uint16_t id = 0;
    id = ((RXB0SIDL >> 5) & 0x7) | (RXB0SIDH << 3);
    return id;
}

static void set_msg_id_std(unsigned int id) {
    TXB0SIDL = (id & 0x7) << 5;
    TXB0SIDH = (id >> 3);
}


void can_transmit(uint16_t msg_id, const uint8_t *data, uint8_t len) {
    uint8_t *ptr;
    TXB0EIDH = 0x00;
    TXB0EIDL = 0x00;

    // Set MSG ID
    set_msg_id_std(msg_id);

    // Set data length
    TXB0DLC = len;
    ptr = (uint8_t *) & TXB0D0;
    for (int i = 0; i < len; i++) {
        ptr[i] = data[i];
    }
    TXB0REQ = 1; 
}

void can_receive(uint16_t *msg_id, uint8_t *data, uint8_t *len) {
    uint8_t *ptr;

    if (RXB0FUL) {
        *msg_id = get_msg_id_std();
        *len = RXB0DLC;

        ptr = (uint8_t *) & RXB0D0;
        for (int i = 0; i < *len; i++) {
            data[i] = ptr[i];
        }

        RXB0FUL = 0; // reset buffer flag
        RXB0IF = 0; // reset interrupt flag  
    }
}
