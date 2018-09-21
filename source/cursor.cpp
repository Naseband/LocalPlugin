#include "main.h"

// Natives

cell AMX_NATIVE_CALL n_GetCursorPos(AMX *amx, cell *params)
{
	POINT position;

	if (!GetCursorPos(&position)) return 0;

	cell* address[2] = { NULL, NULL };

	amx_GetAddr(amx, params[1], &address[0]);
	amx_GetAddr(amx, params[2], &address[1]);

	*address[0] = position.x;
	*address[1] = position.y;

	return 1;
}

cell AMX_NATIVE_CALL n_SetCursorPos(AMX *amx, cell *params)
{
	POINT position;

	position.x = params[1];
	position.y = params[2];

	if (!SetCursorPos(position.x, position.y)) return 0;

	return 1;
}

// EOF