#pragma once

#include "../../SDK/plugin.h"
#include "windows.h"
#include <list>
#include <stdio.h>
#include <string>
using std::string;

#include "keys.h"
#include "cursor.h"
#include "tiles.h"

// Defines

#define INVALID_TILE_ID					-1
#define INVALID_TILE_TYPE				-1

#define TILE_TYPE_RECT					0
#define TILE_TYPE_ELLIPSE				1

// Variables

typedef void(*logprintf_t)(char* format, ...);
extern logprintf_t logprintf;

extern std::list <AMX *> g_AMXList;

AMX_NATIVE_INFO PluginNatives[];

// Functions

string GetActiveWindowTitle();

bool IsSAMPFocused();
void SetSAMPFocused(bool focused);

bool GetWindowPos(int &x, int &y);
bool GetWindowSize(int &size_x, int &size_y);

// Natives

cell AMX_NATIVE_CALL n_IsSAMPFocused(AMX *amx, cell *params);

cell AMX_NATIVE_CALL n_GetSAMPWindowPos(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_GetSAMPWindowSize(AMX *amx, cell *params);

// EOF