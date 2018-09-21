# SAMP-LocalPlugin
Gives access to all keys. Only works for the LOCAL machine (the PC the server is running on). Only for debug purposes/Map Editors (etc).

Note: WINDOWS only!

# Natives (General)

native IsSAMPFocused();

native GetSAMPWindowPos(&x, &y);
native GetSAMPWindowSize(&size_x, &size_y);

# Natives (Keys, including Mouse Keys)

native IsLocalKeyDown(key);
native GetVKName(key, const name[], maxlen = sizeof name);
native ToggleKey(key, toggle = 1);
native IsKeyToggled(key);

# Natives (Cursor)

native GetCursorPos(&x, &y);
native SetCursorPos(x, y);

# Natives (Clickable Tiles)
	Note: These aren't visible. Just virtual zones which trigger OnClickTile when clicked. Useful for non-rectangle UI elements etc.

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

# Callbacks

forward OnLocalKeyStateChange(key, newstate);
forward OnClickTile(id, x, y, key);

# Defines

#define INVALID_TILE_ID					-1
#define INVALID_TILE_TYPE				-1

#define TILE_TYPE_RECT					0
#define TILE_TYPE_ELLIPSE				1

# Keys:

	All compatible keys and their definitions can be found in the include file.
