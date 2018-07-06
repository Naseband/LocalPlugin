#include "../../SDK/plugin.h"
#include "windows.h"
#include <list>
#include <stdio.h>
#include <string>
using std::string;

extern void *pAMXFunctions;

bool keystates[256], keytoggled[256], focused = false;
std::list <AMX *> g_pAmx;
std::list <int> keylist;
int pTick = 0;

typedef void  (*logprintf_t)(char* format, ...);
logprintf_t logprintf;

string GetActiveWindowTitle()
{
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow();
	GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
	return wnd_title;
}

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

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	for(int i = 0; i < sizeof(keystates); i++)
	{
		keystates[i] = false;
		keytoggled[i] = false;
	}

	logprintf("** LocalKeys Plugin by NaS (c) 2016\n   LOADED!");

	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() 
{
		logprintf("** LocalKeys Plugin by NaS (c) 2016\n   UNLOADED!");
}

cell AMX_NATIVE_CALL IsLocalKeyDown(AMX *amx, cell *params)
{
	return (GetAsyncKeyState(params[1]) & (1 << 16));
}

cell AMX_NATIVE_CALL IsSAMPFocused(AMX *amx, cell *params)
{
	return (focused ? 1 : 0);
}

cell AMX_NATIVE_CALL GetVKName(AMX* amx, cell* params)
{
	cell* addr = NULL;
	amx_GetAddr(amx, params[2], &addr);
	amx_SetString(addr, GetKeyName(params[1]).c_str(), 0, 0, params[3]);

	return 1;
}

cell AMX_NATIVE_CALL ToggleKey(AMX *amx, cell *params)
{
	if(params[1] < 0 || params[1] >= 256) return 0;

	int key = params[1], tstate = params[2];

	if(!keytoggled[key] && tstate != 0)
	{
		keylist.push_back(key);
		keytoggled[key] = true;
	}
	else if(keytoggled[key] && tstate == 0)
	{
		keylist.remove(key);
		keytoggled[key] = false;
	}
	return 1;
}

cell AMX_NATIVE_CALL IsKeyToggled(AMX *amx, cell *params)
{
	if(params[1] < 0 || params[1] >= 256) return 0;

	return (keytoggled[params[1]] ? 1 : 0);
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{"IsLocalKeyDown", IsLocalKeyDown},
	{"GetVKName", GetVKName},
	{"IsSAMPFocused", IsSAMPFocused},
	{"ToggleKey", ToggleKey},
	{"IsKeyToggled", IsKeyToggled},
	{0, 0}
};

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | 0x20000;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	g_pAmx.push_back(amx);
	return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	g_pAmx.remove(amx);
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	int idx;

	if(++ pTick % 10 != 0) return;
	
	if(pTick >= 100)
	{
		if(_stricmp(GetActiveWindowTitle().c_str(), "GTA:SA:MP") == 0) focused = true;
		else focused = false;

		pTick = 0;
	}

	if(keylist.size() == 0) return;

	for(std::list <int>::iterator i = keylist.begin(); i != keylist.end(); i ++)
	{
		bool kstate = (GetAsyncKeyState(*i) & (1 << 16) ? true : false);

		if(kstate == keystates[*i]) continue;
			
		keystates[*i] = kstate;

		for(std::list <AMX *>::iterator a = g_pAmx.begin(); a != g_pAmx.end(); a ++) if(!amx_FindPublic(*a, "OnLocalKeyStateChange", &idx)) 
		{
			amx_Push(*a, (kstate ? 1 : 0));
			amx_Push(*a, *i);
			amx_Exec(*a, NULL, idx);
		}
	}
	return;
}
