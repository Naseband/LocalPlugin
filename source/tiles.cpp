#include "main.h"

// Variables

int g_MaxTiles = 100;
s_tiles *g_Tiles = NULL;

// Functions

bool AllocTiles()
{
	if (g_Tiles != NULL) return false;

	g_Tiles = (s_tiles *)calloc(g_MaxTiles, sizeof(s_tiles));

	if (g_Tiles == NULL) return false;

	return true;
}
bool DeallocTiles()
{
	if (g_Tiles == NULL) return false;

	free(g_Tiles);
	g_Tiles = NULL;

	return true;
}

bool SetMaxTiles(int max_tiles)
{
	if (max_tiles <= 0 || g_MaxTiles == max_tiles) return false;

	if (g_Tiles == NULL)
	{
		g_MaxTiles = max_tiles;

		return true;
	}

	s_tiles *temp = (s_tiles*)realloc(g_Tiles, (max_tiles * sizeof(s_tiles)));

	if (temp == NULL) return false;

	if (max_tiles > g_MaxTiles)
	{
		for (int i = g_MaxTiles; i < max_tiles; i++) temp[i].exists = false; // New memory has indeterminate content, make sure the tiles do not exist!
	}

	g_Tiles = temp;
	g_MaxTiles = max_tiles;

	return true;
}
int GetMaxTiles()
{
	return g_MaxTiles;
}

int CreateTile(int x, int y, int type, int size_x, int size_y, bool keys[256], AMX* amx, bool is_private, int extra = 0) // Creates a tile. is_private determines whether or not this tile will call all callbacks or just the parent script's
{
	int id = -1;
	for (int i = 0; i < g_MaxTiles; i++) if (!g_Tiles[i].exists)
	{
		id = i;

		break;
	}

	if (id == -1) return INVALID_TILE_ID;

	g_Tiles[id].x = x;
	g_Tiles[id].y = y;

	g_Tiles[id].size_x = size_x;
	g_Tiles[id].size_y = size_y;

	g_Tiles[id].type = type;

	g_Tiles[id].is_private = is_private;
	g_Tiles[id].amx = amx;

	memcpy(g_Tiles[id].keys, keys, 256 * sizeof(bool));

	for (int i = 0; i < 256; i++) if (keys[i])
	{
		logprintf("Key %d", i);
	}

	logprintf("vs");

	for (int i = 0; i < 256; i++) if (g_Tiles[id].keys[i])
	{
		logprintf("Key %d", i);
	}

	g_Tiles[id].extra = extra;

	g_Tiles[id].exists = true;

	return id;
}
bool DestroyTile(int id)
{
	if(!IsValidTile(id)) return false;

	g_Tiles[id].exists = false;

	return true;
}
bool IsValidTile(int id)
{
	if (id < 0 || id >= g_MaxTiles || !g_Tiles[id].exists) return false;

	return true;
}

bool SetTileType(int id, int type)
{
	if (!IsValidTile(id)) return false;

	switch (type)
	{
		case TILE_TYPE_RECT:
		case TILE_TYPE_ELLIPSE:
		{
			g_Tiles[id].type = type;

			return true;
		}
	}

	return false;
}
int GetTileType(int id)
{
	if (!IsValidTile(id)) return INVALID_TILE_TYPE;

	return g_Tiles[id].type;
}

void SetTilePos(int id, int x, int y)
{
	if (!IsValidTile(id)) return;

	g_Tiles[id].x = x;
	g_Tiles[id].y = y;
}
void GetTilePos(int id, int &x, int &y)
{
	if (!IsValidTile(id)) return;

	x = g_Tiles[id].x;
	y = g_Tiles[id].y;
}

void SetTileSize(int id, int size_x, int size_y)
{
	if (!IsValidTile(id)) return;

	g_Tiles[id].size_x = size_x;
	g_Tiles[id].size_y = size_y;
}
void GetTileSize(int id, int &size_x, int &size_y)
{
	if (!IsValidTile(id)) return;

	size_x = g_Tiles[id].size_x;
	size_y = g_Tiles[id].size_y;
}

void DetectTile(int x, int y, int key)
{
	if (key < 0 || key >= 256) return;

	for (int i = 0; i < g_MaxTiles; i ++) if (g_Tiles[i].exists && g_Tiles[i].keys[key])
	{
		switch (g_Tiles[i].type)
		{
			case TILE_TYPE_RECT:
			{
				if (x >= g_Tiles[i].x && x <= g_Tiles[i].x + g_Tiles[i].size_x && y >= g_Tiles[i].y && y <= g_Tiles[i].y + g_Tiles[i].size_y)
				{
					TriggerTile(i, x, y, key);
				}
			}
		}
	}

	return;
}
void TriggerTile(int id, int x, int y, int key)
{
	if (!IsValidTile(id)) return;

	int funcidx;

	if (g_Tiles[id].amx != NULL && g_Tiles[id].is_private)
	{
		AMX * call_amx = g_Tiles[id].amx;

		if (!amx_FindPublic(call_amx, "OnClickTile", &funcidx))
		{
			amx_Push(call_amx, key);
			amx_Push(call_amx, y);
			amx_Push(call_amx, x);
			amx_Push(call_amx, id);

			amx_Exec(call_amx, NULL, funcidx);
		}
	}
	else
	{
		for (std::list <AMX *>::iterator i = g_AMXList.begin(); i != g_AMXList.end(); i++) if (!amx_FindPublic(*i, "OnClickTile", &funcidx))
		{
			amx_Push(*i, key);
			amx_Push(*i, y);
			amx_Push(*i, x);
			amx_Push(*i, id);

			amx_Exec(*i, NULL, funcidx);
		}
	}
}

void SetTileExtra(int id, int extra)
{
	if (!IsValidTile(id)) return;

	g_Tiles[id].extra = extra;
}
int GetTileExtra(int id)
{
	if (!IsValidTile(id)) return 0;

	return g_Tiles[id].extra;
}

bool SetTilePrivate(int id, bool is_private)
{
	if (!IsValidTile(id)) return false;

	g_Tiles[id].is_private = is_private;

	return true;
}
bool IsTilePrivate(int id)
{
	if (!IsValidTile(id)) return false;

	return g_Tiles[id].is_private;
}
AMX* GetTileAMX(int id)
{
	if (!IsValidTile(id)) return NULL;

	return g_Tiles[id].amx;
}
bool SetTileAMX(int id, AMX* amx)
{
	if (!IsValidTile(id)) return false;

	g_Tiles[id].amx = amx;

	return true;
}

// Natives

// native AllocTiles();
cell AMX_NATIVE_CALL n_AllocTiles(AMX *amx, cell *params)
{
	return (cell)AllocTiles();
}

// native DeallocTiles();
cell AMX_NATIVE_CALL n_DeallocTiles(AMX *amx, cell *params)
{
	return (cell)DeallocTiles();
}


// native SetMaxTiles(max_tiles);
cell AMX_NATIVE_CALL n_SetMaxTiles(AMX *amx, cell *params)
{
	return (cell)SetMaxTiles(params[1]);
}

// native GetMaxTiels();
cell AMX_NATIVE_CALL n_GetMaxTiles(AMX *amx, cell *params)
{
	return (cell)GetMaxTiles();
}


// native CreateTile(x, y, type, size_x, size_y, const keys[], extra = 0, bool:private = false, keys_num = sizeof keys);
cell AMX_NATIVE_CALL n_CreateTile(AMX *amx, cell *params)
{
	bool keys[256] = {};
	
	cell *keys_address;

	amx_GetAddr(amx, params[6], &keys_address);
	int size = params[9];

	if (size > 0)
	{
		for (int i = 0; i < size; i++) if (keys_address[i] >= 0 && keys_address[i] < 256)
		{
			keys[keys_address[i]] = true;
		}
	}
	else keys[VK_LBUTTON] = true;

	int id = CreateTile(params[1], params[2], params[3], params[4], params[5], keys, amx, params[8] ? true : false, params[7]);

	return (cell)id;
}

// native DestroyTile(id);
cell AMX_NATIVE_CALL n_DestroyTile(AMX *amx, cell *params)
{
	return (cell)DestroyTile(params[1]);
}

// native IsValidTile(id);
cell AMX_NATIVE_CALL n_IsValidTile(AMX *amx, cell *params)
{
	return (cell)IsValidTile(params[1]);
}


// native SetTileType(id, type);
cell AMX_NATIVE_CALL n_SetTileType(AMX *amx, cell *params)
{
	return (cell)SetTileType(params[1], params[2]);
}

// native GetTileType(id) // ret
cell AMX_NATIVE_CALL n_GetTileType(AMX *amx, cell *params)
{
	return (cell)GetTileType(params[1]);
}


// native SetTilePos(id, x, y);
cell AMX_NATIVE_CALL n_SetTilePos(AMX *amx, cell *params)
{
	SetTilePos(params[1], params[2], params[3]);

	return 1;
}

// native GetTilePos(id, &x, &y);
cell AMX_NATIVE_CALL n_GetTilePos(AMX *amx, cell *params)
{
	cell *address_x = NULL, *address_y = NULL;

	amx_GetAddr(amx, params[2], &address_x);
	amx_GetAddr(amx, params[3], &address_y);

	int x, y;

	GetTilePos(params[1], x, y);

	*address_x = x;
	*address_y = y;

	return 1;
}


// native SetTileSize(id, size_x, size_y);
cell AMX_NATIVE_CALL n_SetTileSize(AMX *amx, cell *params)
{
	SetTileSize(params[1], params[2], params[3]);

	return 1;
}

// native GetTileSize(id, &size_x, &size_y);
cell AMX_NATIVE_CALL n_GetTileSize(AMX *amx, cell *params)
{
	cell *address_x = NULL, *address_y = NULL;

	amx_GetAddr(amx, params[2], &address_x);
	amx_GetAddr(amx, params[3], &address_y);

	int size_x, size_y;

	GetTileSize(params[1], size_x, size_y);

	*address_x = size_x;
	*address_y = size_y;

	return 1;
}


// native SetTileExtra(id, extra);
cell AMX_NATIVE_CALL n_SetTileExtra(AMX *amx, cell *params)
{
	SetTileExtra(params[1], params[2]);

	return 1;
}

// native GetTileExtra(id); // ret
cell AMX_NATIVE_CALL n_GetTileExtra(AMX *amx, cell *params)
{
	return (cell)GetTileExtra(params[1]);
}


// native SetTilePrivate(id, bool:is_private);
cell AMX_NATIVE_CALL n_SetTilePrivate(AMX *amx, cell *params)
{
	return (cell)SetTilePrivate(params[1], params[2] ? true : false);
}

// native IsTilePrivate(id);
cell AMX_NATIVE_CALL n_IsTilePrivate(AMX *amx, cell *params)
{
	return (cell)IsTilePrivate(params[1]);
}

// native IsMyTile(id);
cell AMX_NATIVE_CALL n_IsMyTile(AMX *amx, cell *params)
{
	return (cell)(amx == GetTileAMX(params[1]));
}

// native UpdateTileAMX(id);
cell AMX_NATIVE_CALL n_UpdateTileAMX(AMX *amx, cell *params)
{
	return (cell)SetTileAMX(params[1], amx);
}

// EOF