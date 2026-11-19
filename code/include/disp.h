#ifndef DISP_H
#define DISP_H

void startDisplay(int wait);
void endDisplay(void);
int vblankHandler(int cause);
int handler_endimage(int channel);

#endif
