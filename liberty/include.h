#pragma once
#define ull unsigned long long
#pragma comment(linker, "/MERGE:.rdata=INIT")
#pragma comment(linker, "/MERGE:.pdata=INIT")

#define _FI __forceinline

#include <ntifs.h>
#include <intrin.h>
#include "sdk.h"
#include "utils.h"

#include "math.h"
#include "p_pointer.h"
p_pointers pointers;

#include "gameasL.h"
#include "GameAssambly.h"
#pragma code_seg("INIT")
extern "C" int _fltused = 0;
#include "p_enum.h"
#include "p_PlayerWalkMovement.h"
#include "p_BaseProjectile.h"

#include "p_weapon.h"
#include "p_BasePlayer.h"
#include "p_LocalPlayer.h"
#include "p_TOD_Sky.h"
#include "p_OcclusionCulling.h"
#include "p_ConVar_Graphics.h"

TOD_Sky* TOD;
p_LocalPlayer* P_player;
BasePlayer* BasePlayer_c;
OcclusionCulling_c* Oclusion;
PlayerWalkMovement* WalkMov;
p_ConVar_Graphics* Graphics;
BasePlayer* active = 0;

#include "func.h"