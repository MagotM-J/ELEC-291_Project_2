#ifndef JOY_STICK_H
#define JOY_STICK_H

typedef struct {
    int vrx;
    int vry;
} js_reads;

void joy_stick_init();
void read_joystick(js_reads* reads, unsigned int count);

#endif