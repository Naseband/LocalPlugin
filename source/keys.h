#pragma once

#include "main.h"

using std::string;

// Variables

extern bool g_KeyStates[256], g_KeyToggled[256];
extern std::list <int> g_KeyList;


// Functions

string GetKeyName(unsigned int virtualKey);

// Natives

cell AMX_NATIVE_CALL n_IsLocalKeyDown(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_IsSAMPFocused(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_GetVKName(AMX* amx, cell* params);
cell AMX_NATIVE_CALL n_ToggleKey(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_IsKeyToggled(AMX *amx, cell *params);

// EOF