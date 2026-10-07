#ifndef DKP_H
#define DKP_H

#define LEVEL 1
#define EDGE 2

#define DKP1 0x0E
#define DKP2 0x0D
#define DKP3 0x0B
#define DKP4 0x07

void init_dkp(void);
char read_dkp(char state);

#endif