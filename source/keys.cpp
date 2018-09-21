#include "main.h"

// Variables

bool g_KeyStates[256], g_KeyToggled[256];
std::list <int> g_KeyList;

// Functions

string GetKeyName(unsigned int virtualKey)
{
	unsigned int scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

	switch (virtualKey)
	{
	case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN: // arrow keys
	case VK_PRIOR: case VK_NEXT: // page up and page down
	case VK_END: case VK_HOME:
	case VK_INSERT: case VK_DELETE:
	case VK_DIVIDE: // numpad slash
	case VK_NUMLOCK:
	{
		scanCode |= 0x100; // set extended bit
		break;
	}
	case VK_LBUTTON: return "LMB";
	case VK_RBUTTON: return "RMB";
	case VK_MBUTTON: return "MMB";
	case VK_XBUTTON1: return "XMB1";
	case VK_XBUTTON2: return "XMB2";
	}

	char keyName[50];
	if (GetKeyNameTextA(scanCode << 16, keyName, sizeof(keyName)) != 0) return keyName;

	sprintf(keyName, "Unknown [%d]", virtualKey);
	return keyName;
}

// Natives

cell AMX_NATIVE_CALL n_IsLocalKeyDown(AMX *amx, cell *params)
{
	return (GetAsyncKeyState(params[1]) & (1 << 16));
}

cell AMX_NATIVE_CALL n_GetVKName(AMX* amx, cell* params)
{
	cell* addr = NULL;
	amx_GetAddr(amx, params[2], &addr);
	amx_SetString(addr, GetKeyName(params[1]).c_str(), 0, 0, params[3]);

	return 1;
}

cell AMX_NATIVE_CALL n_ToggleKey(AMX *amx, cell *params)
{
	if (params[1] < 0 || params[1] >= 256) return 0;

	int key = params[1], tstate = params[2];

	if (!g_KeyToggled[key] && tstate != 0)
	{
		g_KeyList.push_back(key);
		g_KeyToggled[key] = true;
	}
	else if (g_KeyToggled[key] && tstate == 0)
	{
		g_KeyList.remove(key);
		g_KeyToggled[key] = false;
	}
	return 1;
}

cell AMX_NATIVE_CALL n_IsKeyToggled(AMX *amx, cell *params)
{
	if (params[1] < 0 || params[1] >= 256) return 0;

	return (cell)g_KeyToggled[params[1]];
}

// EOF