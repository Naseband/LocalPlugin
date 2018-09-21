#if defined __LOCAL_KEYS_INCLUDED__
#endinput
#endif
#define __LOCAL_KEYS_INCLUDED__ "Yes, it is."

/****
*
*	LocalKeys Plugin by NaS (c) 2016-2018
*	IMPORTANT: Only works for the client that runs the samp-server.exe (Windows)!
*
*////

// Natives (General)

native IsSAMPFocused();

native GetSAMPWindowPos(&x, &y);
native GetSAMPWindowSize(&size_x, &size_y);

// Natives (Keys, including Mouse Keys)

native IsLocalKeyDown(key);
native GetVKName(key, const name[], maxlen = sizeof name);
native ToggleKey(key, toggle = 1);
native IsKeyToggled(key);

// Natives (Cursor)

native GetCursorPos(&x, &y);
native SetCursorPos(x, y);

// Natives (Clickable Tiles) Note: These aren't visible. Just virtual zones which trigger OnClickTile when clicked. Useful for non-rectangle UI elements etc.

native AllocTiles();
native DeallocTiles();

native SetMaxTiles(max_tiles);
native GetMaxTiles();

native CreateTile(x, y, type, size_x, size_y, const keys[], extra = 0, bool:prvate = false, keys_num = sizeof keys);
native DestroyTile(id);
native IsValidTile(id);

native SetTileType(id, type);
native GetTileType(id); // ret

native SetTilePos(id, x, y);
native GetTilePos(id, &x, &y);

native SetTileSize(id, size_x, size_y);
native GetTileSize(id, &size_x, &size_y);

native SetTileExtra(id, extra);
native GetTileExtra(id); // ret

native SetTilePrivate(id, bool:is_private); // Does not change the parent AMX, only toggles it.
native IsTilePrivate(id);
native IsMyTile(id);
native UpdateTileAMX(id); // Updates the AMX instance to the one which calls it.

// Callbacks

forward OnLocalKeyStateChange(key, newstate);
forward OnClickTile(id, x, y, key);

// Defines

#define INVALID_TILE_ID					-1
#define INVALID_TILE_TYPE				-1

#define TILE_TYPE_RECT					0
#define TILE_TYPE_ELLIPSE				1

// Key Defines - From WinUser.h, also added A-Z, 0-9

#define VK_LBUTTON				0x01
#define VK_RBUTTON				0x02
#define VK_CANCEL				0x03
#define VK_MBUTTON				0x04    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON1				0x05    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON2				0x06    /* NOT contiguous with L & RBUTTON */

#define VK_LMB					VK_LBUTTON
#define VK_RMB					VK_RBUTTON
#define VK_MMB					VK_MBUTTON
#define VK_XMB1					VK_XBUTTON1
#define VK_XMB2					VK_XBUTTON2

#define VK_BACK					0x08
#define VK_TAB					0x09

#define VK_CLEAR				0x0C
#define VK_RETURN				0x0D

#define VK_SHIFT				0x10
#define VK_CONTROL				0x11
#define VK_MENU					0x12
#define VK_ALT					VK_MENU
#define VK_PAUSE				0x13
#define VK_CAPITAL				0x14

#define VK_KANA					0x15
#define VK_HANGEUL				VK_KANA  /* old name - should be here for compatibility */
#define VK_HANGUL				VK_KANA
#define VK_JUNJA				0x17
#define VK_FINAL				0x18
#define VK_HANJA				0x19
#define VK_KANJI				VK_HANJA

#define VK_ESCAPE				VK_FINAL

#define VK_CONVERT				0x1C
#define VK_NONCONVERT			0x1D
#define VK_ACCEPT				0x1E
#define VK_MODECHANGE			0x1F

#define VK_SPACE				0x20
#define VK_PRIOR				0x21
#define VK_NEXT					0x22
#define VK_END					0x23
#define VK_HOME					0x24
#define VK_LEFT					0x25
#define VK_UP					0x26
#define VK_RIGHT				0x27
#define VK_DOWN					0x28
#define VK_SELECT				0x29
#define VK_PRINT				0x2A
#define VK_EXECUTE				0x2B
#define VK_SNAPSHOT				0x2C
#define VK_INSERT				0x2D
#define VK_DELETE				0x2E
#define VK_HELP					0x2F

#define VK_KEYB0				0x30
#define VK_KEYB1				0x31
#define VK_KEYB2				0x32
#define VK_KEYB3				0x33
#define VK_KEYB4				0x34
#define VK_KEYB5				0x35
#define VK_KEYB6				0x36
#define VK_KEYB7				0x37
#define VK_KEYB8				0x38
#define VK_KEYB9				0x39

#define VK_A					0x41
#define VK_B					0x42
#define VK_C					0x43
#define VK_D					0x44
#define VK_E					0x45
#define VK_F					0x46
#define VK_G					0x47
#define VK_H					0x48
#define VK_I					0x49
#define VK_J					0x4A
#define VK_K					0x4B
#define VK_L					0x4C
#define VK_M					0x4D
#define VK_N					0x4E
#define VK_O					0x4F
#define VK_P					0x50
#define VK_Q					0x51
#define VK_R					0x52
#define VK_S					0x53
#define VK_T					0x54
#define VK_U					0x55
#define VK_V					0x56
#define VK_W					0x57
#define VK_X					0x58
#define VK_Y					0x59
#define VK_Z					0x5A

#define VK_LWIN					0x5B
#define VK_RWIN					0x5C
#define VK_APPS					0x5D

#define VK_SLEEP				0x5F

#define VK_NUMPAD0				0x60
#define VK_NUMPAD1				0x61
#define VK_NUMPAD2				0x62
#define VK_NUMPAD3				0x63
#define VK_NUMPAD4				0x64
#define VK_NUMPAD5				0x65
#define VK_NUMPAD6				0x66
#define VK_NUMPAD7				0x67
#define VK_NUMPAD8				0x68
#define VK_NUMPAD9				0x69
#define VK_MULTIPLY				0x6A
#define VK_ADD					0x6B
#define VK_SEPARATOR			0x6C
#define VK_SUBTRACT				0x6D
#define VK_DECIMAL				0x6E
#define VK_DIVIDE				0x6F
#define VK_F1					0x70
#define VK_F2					0x71
#define VK_F3					0x72
#define VK_F4					0x73
#define VK_F5					0x74
#define VK_F6					0x75
#define VK_F7					0x76
#define VK_F8					0x77
#define VK_F9					0x78
#define VK_F10					0x79
#define VK_F11					0x7A
#define VK_F12					0x7B
#define VK_F13					0x7C
#define VK_F14					0x7D
#define VK_F15					0x7E
#define VK_F16					0x7F
#define VK_F17					0x80
#define VK_F18					0x81
#define VK_F19					0x82
#define VK_F20					0x83
#define VK_F21					0x84
#define VK_F22					0x85
#define VK_F23					0x86
#define VK_F24					0x87

#define VK_NUMLOCK				0x90
#define VK_SCROLL				0x91

#define VK_OEM_NEC_EQUAL		0x92   // '=' key on numpad

#define VK_OEM_FJ_JISHO			0x92   // 'Dictionary' key
#define VK_OEM_FJ_MASSHOU		0x93   // 'Unregister word' key
#define VK_OEM_FJ_TOUROKU		0x94   // 'Register word' key
#define VK_OEM_FJ_LOYA			0x95   // 'Left OYAYUBI' key
#define VK_OEM_FJ_ROYA			0x96   // 'Right OYAYUBI' key

#define VK_LSHIFT				0xA0
#define VK_RSHIFT				0xA1
#define VK_LCONTROL				0xA2
#define VK_RCONTROL				0xA3
#define VK_LMENU				0xA4
#define VK_RMENU				0xA5

#define VK_BROWSER_BACK			0xA6
#define VK_BROWSER_FORWARD		0xA7
#define VK_BROWSER_REFRESH		0xA8
#define VK_BROWSER_STOP			0xA9
#define VK_BROWSER_SEARCH		0xAA
#define VK_BROWSER_FAVORITES	0xAB
#define VK_BROWSER_HOME			0xAC

#define VK_VOLUME_MUTE			0xAD
#define VK_VOLUME_DOWN			0xAE
#define VK_VOLUME_UP			0xAF
#define VK_MEDIA_NEXT_TRACK		0xB0
#define VK_MEDIA_PREV_TRACK		0xB1
#define VK_MEDIA_STOP			0xB2
#define VK_MEDIA_PLAY_PAUSE		0xB3
#define VK_LAUNCH_MAIL			0xB4
#define VK_LAUNCH_MEDIA_SELECT	0xB5
#define VK_LAUNCH_APP1			0xB6
#define VK_LAUNCH_APP2			0xB7

#define VK_OEM_1				0xBA   // ';:' for US
#define VK_OEM_PLUS				0xBB   // '+' any country
#define VK_OEM_COMMA			0xBC   // ',' any country
#define VK_OEM_MINUS			0xBD   // '-' any country
#define VK_OEM_PERIOD			0xBE   // '.' any country
#define VK_OEM_2				0xBF   // '/?' for US
#define VK_OEM_3				0xC0   // '`~' for US

#define VK_OEM_4				0xDB  //  '[{' for US
#define VK_OEM_5				0xDC  //  '\|' for US
#define VK_OEM_6				0xDD  //  ']}' for US
#define VK_OEM_7				0xDE  //  ''"' for US
#define VK_OEM_8				0xDF

#define VK_OEM_AX				0xE1  //  'AX' key on Japanese AX kbd
#define VK_OEM_102				0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define VK_ICO_HELP				0xE3  //  Help key on ICO
#define VK_ICO_00				0xE4  //  00 key on ICO

#define VK_PROCESSKEY			0xE5

#define VK_ICO_CLEAR			0xE6

#define VK_PACKET				0xE7

#define VK_OEM_RESET			0xE9
#define VK_OEM_JUMP				0xEA
#define VK_OEM_PA1				0xEB
#define VK_OEM_PA2				0xEC
#define VK_OEM_PA3				0xED
#define VK_OEM_WSCTRL			0xEE
#define VK_OEM_CUSEL			0xEF
#define VK_OEM_ATTN				0xF0
#define VK_OEM_FINISH			0xF1
#define VK_OEM_COPY				0xF2
#define VK_OEM_AUTO				0xF3
#define VK_OEM_ENLW				0xF4
#define VK_OEM_BACKTAB			0xF5

#define VK_ATTN					0xF6
#define VK_CRSEL				0xF7
#define VK_EXSEL				0xF8
#define VK_EREOF				0xF9
#define VK_PLAY					0xFA
#define VK_ZOOM					0xFB
#define VK_NONAME				0xFC
#define VK_PA1					0xFD
#define VK_OEM_CLEAR			0xFE

 // EOF