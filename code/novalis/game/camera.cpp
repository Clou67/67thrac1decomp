#include "common.h"
#include "vtbl.h"
#include "camera.h"

void Camera_ClearPolar(float *polar)
{
    polar[0] = 0.0f;
    polar[1] = 0.0f;
    polar[2] = 0.0f;
    polar[3] = 0.0f;
    polar[4] = 0.0f;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Cam_CopyRotWrapped);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", BackupCurrentCam);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", ExecuteCamPostUpdFuncs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_FindCameraOfType);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_0020CE30);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Cam_InterpValues);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Cam_InterpAngles);

void Camera_DeactivateCurrent(void)
{
    GameCamera.pCurrentUpdCam->activation.deactivate = 1;
    GameCamera.pCurrentUpdCam->activation.activate = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", camera_HandleCollWithHero);

void Camera_runSetupToNewCam(UpdateCam *camera)
{
    void (*callback)(UpdateCam *) = cameraupdate_vtbl[camera->funcIdx].activate;

    if (callback)
        callback(camera);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_switchtoNewCam);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_ActivationCheckPriority);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_Exit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", UpdateAllCameras);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_Pos2Polar3d);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_InitBlenderPolarHero);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_CopyLastQuatToPolar);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_CopyLastPolarToQuat);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_InitBlender);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_BlendCamsPosQuat);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_BlendCamsPolQuat);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_BlendCams);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", HandleCameraShake);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_UpdateHeroInfo);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_UpdateUnderWater);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_0020EB38);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_SetCollFlags);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_HandleScreenFade);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", UpdateCameras);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_GetFuncIdx);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_resetToFollow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", InitCameras);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_Polar2Pos);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_Pos2Polar);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_CollSphereBump);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_0020F478);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_DrawReticule);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", DrawCrosshairSprite);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_0020FB58);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", DrawTargetCrosshair);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", TargetCrosshairDraw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_CollPrimTest);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", IsPntInCollPrim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_UpdateFog);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_00210448);
