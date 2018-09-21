#pragma once

#include "main.h"

using std::string;

// Natives

cell AMX_NATIVE_CALL n_GetCursorPos(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_SetCursorPos(AMX *amx, cell *params);

// EOF