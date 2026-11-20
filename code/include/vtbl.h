#ifndef VTBL_H
#define VTBL_H

// Per-level dispatch tables: which update functions this level's mobys,
// cameras and ambient sounds use. Each table sits in its own lvl.* section.

struct MobyInstance;
struct UpdateCam;
struct AmbientSound;

// The per-class callbacks a moby class can override. RC1 has six where DL's
// mobyfuncs has eight; the signatures are read off the asm and unconfirmed.
struct MobyHandlers {
    int (*handler0)(MobyInstance *moby);    // the overrides call MB_Sucking here
    int (*handler1)(MobyInstance *moby);
    int (*handler2)(MobyInstance *moby, int arg1, int arg2, float amount);
    int (*handler3)(MobyInstance *moby);
    int (*handler4)(MobyInstance *moby);
    void (*remove)(MobyInstance *moby);
};

struct MobyUpdateEntry {
    int oClass;
    void (*update)(MobyInstance *moby);
    const MobyHandlers *handlers;
};

struct CameraUpdateEntry {
    int id;
    int (*init)(UpdateCam *camera);
    void (*activate)(UpdateCam *camera);
    void (*update)(UpdateCam *camera);
    void (*exit)(UpdateCam *camera);
};

struct SoundUpdateEntry {
    int id;
    void (*update)(AmbientSound *sound);
};

// Novalis's moby table: one entry per moby class (the last has oClass -1),
// followed by the handler sets the entries point at.
#define MOBY_UPDATE_ENTRY_COUNT 185
#define MOBY_HANDLER_SET_COUNT 5

struct MobyUpdateTable {
    MobyUpdateEntry entries[MOBY_UPDATE_ENTRY_COUNT];
    MobyHandlers handlerSets[MOBY_HANDLER_SET_COUNT];
};

extern const MobyUpdateTable mobyupdate_vtbl;
extern const CameraUpdateEntry cameraupdate_vtbl[];
extern const SoundUpdateEntry soundupdate_vtbl[];

void UpdateMoby_11(MobyInstance *moby);
void UpdateMoby_13(MobyInstance *moby);
void UpdateMoby_27(MobyInstance *moby);
void UpdateMoby_71(MobyInstance *moby);
void UpdateMoby_74(MobyInstance *moby);
void UpdateMoby_112(MobyInstance *moby);
void UpdateMoby_121(MobyInstance *moby);
void UpdateMoby_122(MobyInstance *moby);
void UpdateMoby_149(MobyInstance *moby);
void UpdateMoby_153(MobyInstance *moby);
void UpdateMoby_156(MobyInstance *moby);
void UpdateMoby_157(MobyInstance *moby);
void UpdateMoby_163(MobyInstance *moby);
void UpdateMoby_166(MobyInstance *moby);
void UpdateMoby_167(MobyInstance *moby);
void UpdateMoby_168(MobyInstance *moby);
void UpdateMoby_172(MobyInstance *moby);
void UpdateMoby_175(MobyInstance *moby);
void UpdateMoby_176(MobyInstance *moby);
void UpdateMoby_177(MobyInstance *moby);
void UpdateMoby_179(MobyInstance *moby);
void UpdateMoby_180(MobyInstance *moby);
void UpdateMoby_185(MobyInstance *moby);
void UpdateMoby_186(MobyInstance *moby);
void UpdateMoby_188(MobyInstance *moby);
void UpdateMoby_190(MobyInstance *moby);
void UpdateMoby_192(MobyInstance *moby);
void UpdateMoby_203(MobyInstance *moby);
void UpdateMoby_204(MobyInstance *moby);
void UpdateMoby_208(MobyInstance *moby);
void UpdateMoby_209(MobyInstance *moby);
void UpdateMoby_229(MobyInstance *moby);
void UpdateMoby_230(MobyInstance *moby);
void UpdateMoby_270(MobyInstance *moby);
void UpdateMoby_280(MobyInstance *moby);
void UpdateMoby_304(MobyInstance *moby);
void UpdateMoby_305(MobyInstance *moby);
void UpdateMoby_428(MobyInstance *moby);
void UpdateMoby_433(MobyInstance *moby);
void UpdateMoby_437(MobyInstance *moby);
void UpdateMoby_454(MobyInstance *moby);
void UpdateMoby_457(MobyInstance *moby);
void UpdateMoby_459(MobyInstance *moby);
void UpdateMoby_479(MobyInstance *moby);
void UpdateMoby_500(MobyInstance *moby);
void UpdateMoby_530(MobyInstance *moby);
void UpdateMoby_531(MobyInstance *moby);
void UpdateMoby_562(MobyInstance *moby);
void UpdateMoby_567(MobyInstance *moby);
void UpdateMoby_572(MobyInstance *moby);
void UpdateMoby_577(MobyInstance *moby);
void UpdateMoby_585(MobyInstance *moby);
void UpdateMoby_604(MobyInstance *moby);
void UpdateMoby_605(MobyInstance *moby);
void UpdateMoby_607(MobyInstance *moby);
void UpdateMoby_613(MobyInstance *moby);
void UpdateMoby_618(MobyInstance *moby);
void UpdateMoby_639(MobyInstance *moby);
void UpdateMoby_641(MobyInstance *moby);
void UpdateMoby_660(MobyInstance *moby);
void UpdateMoby_665(MobyInstance *moby);
void UpdateMoby_666(MobyInstance *moby);
void UpdateMoby_676(MobyInstance *moby);
void UpdateMoby_678(MobyInstance *moby);
void UpdateMoby_679(MobyInstance *moby);
void UpdateMoby_686(MobyInstance *moby);
void UpdateMoby_688(MobyInstance *moby);
void UpdateMoby_695(MobyInstance *moby);
void UpdateMoby_696(MobyInstance *moby);
void UpdateMoby_700(MobyInstance *moby);
void UpdateMoby_701(MobyInstance *moby);
void UpdateMoby_703(MobyInstance *moby);
void UpdateMoby_704(MobyInstance *moby);
void UpdateMoby_705(MobyInstance *moby);
void UpdateMoby_709(MobyInstance *moby);
void UpdateMoby_722(MobyInstance *moby);
void UpdateMoby_724(MobyInstance *moby);
void UpdateMoby_726(MobyInstance *moby);
void UpdateMoby_729(MobyInstance *moby);
void UpdateMoby_730(MobyInstance *moby);
void UpdateMoby_737(MobyInstance *moby);
void UpdateMoby_746(MobyInstance *moby);
void UpdateMoby_750(MobyInstance *moby);
void UpdateMoby_751(MobyInstance *moby);
void UpdateMoby_754(MobyInstance *moby);
void UpdateMoby_760(MobyInstance *moby);
void UpdateMoby_761(MobyInstance *moby);
void UpdateMoby_768(MobyInstance *moby);
void UpdateMoby_774(MobyInstance *moby);
void UpdateMoby_775(MobyInstance *moby);
void UpdateMoby_778(MobyInstance *moby);
void UpdateMoby_779(MobyInstance *moby);
void UpdateMoby_787(MobyInstance *moby);
void UpdateMoby_804(MobyInstance *moby);
void UpdateMoby_805(MobyInstance *moby);
void UpdateMoby_806(MobyInstance *moby);
void UpdateMoby_809(MobyInstance *moby);
void UpdateMoby_815(MobyInstance *moby);
void UpdateMoby_832(MobyInstance *moby);
void UpdateMoby_849(MobyInstance *moby);
void UpdateMoby_1007(MobyInstance *moby);
void UpdateMoby_1042(MobyInstance *moby);
void UpdateMoby_1134(MobyInstance *moby);
void UpdateMoby_1135(MobyInstance *moby);
void UpdateMoby_1138(MobyInstance *moby);
void UpdateMoby_1143(MobyInstance *moby);
void UpdateMoby_1225(MobyInstance *moby);
void UpdateMoby_1251(MobyInstance *moby);
void UpdateMoby_1289(MobyInstance *moby);
void UpdateMoby_1290(MobyInstance *moby);
void UpdateMoby_1341(MobyInstance *moby);
void UpdateMoby_1504(MobyInstance *moby);
void UpdateMoby_1510(MobyInstance *moby);
void UpdateMoby_1546(MobyInstance *moby);
void UpdateMoby_1633(MobyInstance *moby);
void UpdateMoby_1736(MobyInstance *moby);
void UpdateMoby_1813(MobyInstance *moby);
void UpdateMoby_1816(MobyInstance *moby);
void UpdateMoby_1818(MobyInstance *moby);
void UpdateMoby_1848(MobyInstance *moby);

int FUN_003040b8(MobyInstance *moby);
int FUN_003040c0(MobyInstance *moby);
int FUN_003040c8(MobyInstance *moby, int damageKind, int flags, float amount);
int FUN_003040d0(MobyInstance *moby);
int FUN_003040f8(MobyInstance *moby);
void DeleteMoby_Thunk(MobyInstance *moby);
int FUN_002e0a28(MobyInstance *moby);
int FUN_002e0a78(MobyInstance *moby);
int FUN_002e0ac8(MobyInstance *moby, int arg1, int arg2, float amount);
int FUN_002e0b78(MobyInstance *moby);
int func_002E0BA8(MobyInstance *moby);
int FUN_002efa88(MobyInstance *moby);
int FUN_002efaf8(MobyInstance *moby);
int FUN_002efb48(MobyInstance *moby, int arg1, int arg2, float amount);
int FUN_002efb98(MobyInstance *moby);
int FUN_002efbc8(MobyInstance *moby);
int FUN_002f1c78(MobyInstance *moby);
int FUN_002f1cc8(MobyInstance *moby);
int FUN_002f1d18(MobyInstance *moby, int arg1, int arg2, float amount);
int FUN_002f1dc8(MobyInstance *moby);
int func_002F1DF8(MobyInstance *moby);

int InitCamera_0(UpdateCam *camera);
void ActivateCamera_0(UpdateCam *camera);
void UpdateCamera_0(UpdateCam *camera);
void ExitCamera_0(UpdateCam *camera);
int InitCamera_3(UpdateCam *camera);
void ActivateCamera_3(UpdateCam *camera);
void UpdateCamera_3(UpdateCam *camera);
void ExitCamera_3(UpdateCam *camera);
int InitCamera_4(UpdateCam *camera);
void ActivateCamera_4(UpdateCam *camera);
void UpdateCamera_4(UpdateCam *camera);
void ExitCamera_4(UpdateCam *camera);
int InitCamera_5(UpdateCam *camera);
void ActivateCamera_5(UpdateCam *camera);
void UpdateCamera_5(UpdateCam *camera);
void ExitCamera_5(UpdateCam *camera);
int InitCamera_6(UpdateCam *camera);
void ActivateCamera_6(UpdateCam *camera);
void UpdateCamera_6(UpdateCam *camera);
void ExitCamera_6(UpdateCam *camera);
int InitCamera_7(UpdateCam *camera);
void ActivateCamera_7(UpdateCam *camera);
void UpdateCamera_7(UpdateCam *camera);
void ExitCamera_7(UpdateCam *camera);
int InitCamera_17(UpdateCam *camera);
void ActivateCamera_17(UpdateCam *camera);
void UpdateCamera_17(UpdateCam *camera);
void ExitCamera_17(UpdateCam *camera);

void UpdateSound_0(AmbientSound *sound);
void UpdateSound_1(AmbientSound *sound);
void UpdateSound_2(AmbientSound *sound);
void UpdateSound_3(AmbientSound *sound);
void UpdateSound_5(AmbientSound *sound);
void UpdateSound_6(AmbientSound *sound);

void M676_DrawWaterSheets(MobyInstance *moby);

int M806_IsActive(MobyInstance *moby);

void M751_DrawWaterTiles(MobyInstance *moby);

void M678_DrawWaterSheets(MobyInstance *moby);

void M761_DrawWaterSheets(MobyInstance *moby);

void M280_BeginSucking(MobyInstance *moby);

#endif
