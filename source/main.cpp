/*
Default Output: $(OutDir)$(TargetName)$(TargetExt)
				$(SolutionDir)$(Configuration)\
*/

#include "main.h"

using std::string;

extern void *pAMXFunctions;

// Variables

logprintf_t logprintf;

int g_ProcessTick = 0;
bool g_Focused = false;

std::list <AMX *> g_AMXList;

// Functions

string GetActiveWindowTitle()
{
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow();
	GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
	return wnd_title;
}

bool IsSAMPFocused()
{
	return g_Focused;
}
void SetSAMPFocused(bool focused)
{
	g_Focused = focused;
}

bool GetWindowPos(int &x, int &y)
{
	if (!IsSAMPFocused()) return false;

	HWND window;
	window = GetForegroundWindow();

	if (window == NULL) return false;

	RECT window_rect;
	GetWindowRect(window, &window_rect);

	x = window_rect.left;
	y = window_rect.top;

	return true;
}
bool GetWindowSize(int &size_x, int &size_y)
{
	if (!IsSAMPFocused()) return false;

	HWND window;
	window = GetForegroundWindow();

	if (window == NULL) return false;

	RECT window_rect;
	GetWindowRect(window, &window_rect);

	size_x = window_rect.right - window_rect.left;
	size_y = window_rect.bottom - window_rect.top;

	return true;
}

// Internal

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	// General

	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	// Keys

	for (int i = 0; i < sizeof(g_KeyStates); i++)
	{
		g_KeyStates[i] = false;
		g_KeyToggled[i] = false;
	}

	// Clickable Tiles

	AllocTiles();

	logprintf("** LocalKeys Plugin by NaS (c) 2016-2018\n   LOADED!");
	logprintf("** Max tiles: %i", GetMaxTiles());

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	DeallocTiles();

	logprintf("** LocalKeys Plugin by NaS (c) 2016-2018\n   UNLOADED!");
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | 0x20000;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	g_AMXList.push_back(amx);

	return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	g_AMXList.remove(amx);

	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	int idx;

	if(++ g_ProcessTick % 10 != 0) return;
	
	if(g_ProcessTick >= 100)
	{
		if(_stricmp(GetActiveWindowTitle().c_str(), "GTA:SA:MP") == 0) g_Focused = true;
		else g_Focused = false;

		g_ProcessTick = 0;
	}

	if(g_KeyList.size() == 0) return;

	for(std::list <int>::iterator i = g_KeyList.begin(); i != g_KeyList.end(); i ++)
	{
		bool kstate = (GetAsyncKeyState(*i) & (1 << 16) ? true : false);

		if(kstate == g_KeyStates[*i]) continue;

		if (kstate)
		{
			POINT cursor;
			GetCursorPos(&cursor);

			DetectTile(cursor.x, cursor.y, *i);
		}
			
		g_KeyStates[*i] = kstate;

		for(std::list <AMX *>::iterator a = g_AMXList.begin(); a != g_AMXList.end(); a ++) if(!amx_FindPublic(*a, "OnLocalKeyStateChange", &idx)) 
		{
			amx_Push(*a, (kstate ? 1 : 0));
			amx_Push(*a, *i);
			amx_Exec(*a, NULL, idx);
		}
	}

	return;
}

AMX_NATIVE_INFO PluginNatives[] =
{
	// Main
	{ "IsSAMPFocused", n_IsSAMPFocused },
	{ "GetSAMPWindowPos", n_GetSAMPWindowPos },
	{ "GetSAMPWindowSize", n_GetSAMPWindowSize },

	// Keys
	{ "IsLocalKeyDown", n_IsLocalKeyDown },
	{ "GetVKName", n_GetVKName },
	{ "ToggleKey", n_ToggleKey },
	{ "IsKeyToggled", n_IsKeyToggled },

	// Cursor
	{ "GetCursorPos", n_GetCursorPos },
	{ "SetCursorPos", n_SetCursorPos },

	// Tiles
	{ "AllocTiles", n_AllocTiles },
	{ "DeallocTiles", n_DeallocTiles },
	{ "SetMaxTiles", n_SetMaxTiles },
	{ "GetMaxTiles", n_GetMaxTiles },
	{ "CreateTile", n_CreateTile },
	{ "DestroyTile", n_DestroyTile },
	{ "IsValidTile", n_IsValidTile },
	{ "SetTileType", n_SetTileType },
	{ "GetTileType", n_GetTileType },
	{ "SetTilePos", n_SetTilePos },
	{ "GetTilePos", n_GetTilePos },
	{ "SetTileSize", n_SetTileSize },
	{ "GetTileSize", n_GetTileSize },
	{ "SetTileExtra", n_SetTileExtra },
	{ "GetTileExtra", n_GetTileExtra },
	{ "SetTilePrivate", n_SetTilePrivate },
	{ "IsTilePrivate", n_IsTilePrivate },
	{ "IsMyTile", n_IsMyTile },
	{ "UpdateTileAMX", n_UpdateTileAMX },
	{ 0, 0 }
};

// Natives

// native IsSAMPFocused();
cell AMX_NATIVE_CALL n_IsSAMPFocused(AMX *amx, cell *params)
{
	return (cell)IsSAMPFocused();
}

// native GetSAMPWindowPos(&x, &y);
cell AMX_NATIVE_CALL n_GetSAMPWindowPos(AMX *amx, cell *params)
{
	cell *address_x = NULL, *address_y = NULL;

	amx_GetAddr(amx, params[1], &address_x);
	amx_GetAddr(amx, params[2], &address_y);

	int x, y;

	if (!GetWindowPos(x, y)) return 0;

	*address_x = x;
	*address_y = y;

	return 1;
}

// native GetSAMPWindowSize(&size_x, &size_y);
cell AMX_NATIVE_CALL n_GetSAMPWindowSize(AMX *amx, cell *params)
{
	cell *address_x = NULL, *address_y = NULL;

	amx_GetAddr(amx, params[1], &address_x);
	amx_GetAddr(amx, params[2], &address_y);

	int size_x, size_y;

	if (!GetWindowSize(size_x, size_y)) return 0;

	*address_x = size_x;
	*address_y = size_y;

	return 1;
}

// EOF