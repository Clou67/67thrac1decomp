#ifndef READ_H
#define READ_H

#include "videodec.h"

int videoCallback(sceMpeg *mpeg, sceMpegCbData *event, void *argument);
int pcmCallback(sceMpeg *mpeg, sceMpegCbDataStr *event, void *argument);

#endif
