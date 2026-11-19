#ifndef FASTFUNC_H
#define FASTFUNC_H

struct Vec4;
struct BSphere;

// Stops in the debugger; used when a save is bigger than its buffer.
void FastTrap(void);
int FastScaleRoundInt(int value);
int FastTweenColor(int from, int to, float fraction);
int FastFloatToInt(float value);
float FastIntToFloat(int value);
float FastAngleCosF(float angle);
float FastAngleSinF(float angle);
float FastAddRots(float angle, float delta);
float FastArcTan(float x, float y);
float FastDiffRots(float first, float second);
float FastVec3Dist(Vec4 *first, Vec4 *second);
// Nonzero when the sphere (w is its radius) overlaps the bounding sphere.
int FastVec3AddSubLen(Vec4 *sphere, BSphere *bounds);
void FastScaleVec4(Vec4 *out, Vec4 *in, float scale);
// Counts a timer down to zero; returns nonzero once it has run out.
int FastDecTimer(int &timer);
float FastVec3Length(float *vec);
void FastMemCopy32(void *destination, void *source, int size);
void FastMemSet(void *destination, int value, int size);

#endif
