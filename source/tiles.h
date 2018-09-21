#pragma once

#include "main.h"

using std::string;

// Variables

struct s_tiles
{
	bool exists;

	int type;
	int x, y, size_x, size_y;

	bool is_private;
	AMX* amx;

	bool keys[256];

	int extra;
};

// Functions

bool AllocTiles();
bool DeallocTiles();

bool SetMaxTiles(int max_tiles);
int GetMaxTiles();

int CreateTile(int x, int y, int type, int size_x, int size_y, bool keys[256], AMX* amx, bool is_private, int extra);
bool DestroyTile(int id);
bool IsValidTile(int id);

bool SetTileType(int id, int type);
int GetTileType(int id);

void SetTilePos(int id, int x, int y);
void GetTilePos(int id, int &x, int &y);

void SetTileSize(int id, int size_x, int size_y);
void GetTileSize(int id, int &size_x, int &size_y);

void DetectTile(int x, int y, int key);
void TriggerTile(int id, int x, int y, int key);

void SetTileExtra(int id, int extra);
int GetTileExtra(int id);

bool SetTilePrivate(int id, bool is_private);
bool IsTilePrivate(int id);
AMX* GetTileAMX(int id);
bool SetTileAMX(int id, AMX* amx);


// Natives

cell AMX_NATIVE_CALL n_AllocTiles(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_DeallocTiles(AMX *amx, cell *params);

cell AMX_NATIVE_CALL n_SetMaxTiles(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_GetMaxTiles(AMX *amx, cell *params);

cell AMX_NATIVE_CALL n_CreateTile(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_DestroyTile(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_IsValidTile(AMX *amx, cell *params);

cell AMX_NATIVE_CALL n_SetTileType(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_GetTileType(AMX *amx, cell *params);

cell AMX_NATIVE_CALL n_SetTilePos(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_GetTilePos(AMX *amx, cell *params);

cell AMX_NATIVE_CALL n_SetTileSize(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_GetTileSize(AMX *amx, cell *params);

cell AMX_NATIVE_CALL n_SetTileExtra(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_GetTileExtra(AMX *amx, cell *params);

cell AMX_NATIVE_CALL n_SetTilePrivate(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_IsTilePrivate(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_IsMyTile(AMX *amx, cell *params);
cell AMX_NATIVE_CALL n_UpdateTileAMX(AMX *amx, cell *params);

// EOF