#include <a_samp>
#include <LocalPlugin>

//#define PRINT_KEYS
#define PRINT_CURSOR
#define PRINT_TILES
#define PRINT_WINDOW

#if defined PRINT_CURSOR
new cursor_x, cursor_y;
#endif

main()
{

}

public OnGameModeInit()
{
	SetTimer("CursorTimer", 100, 1);
	SetTimer("WindowTimer", 5000, 1);

	ToggleKey(VK_LBUTTON);
	ToggleKey(VK_RBUTTON);
	ToggleKey(VK_ALT);

	new tile_id = CreateTile(1, 5, TILE_TYPE_RECT, 5, 7, {VK_LBUTTON, VK_ALT}, 666, false);

	if(IsValidTile(tile_id))
	{
		new x, y, size_x, size_y;

		GetTilePos(tile_id, x, y);
		GetTileSize(tile_id, size_x, size_y);
		printf("ID: %d  Type: %d  x: %d  y: %d  size_x: %d  size_y: %d  extra: %d private: %b mytile: %d", tile_id, GetTileType(tile_id), x, y, size_x, size_y, GetTileExtra(tile_id), IsTilePrivate(tile_id), IsMyTile(tile_id));

		SetTilePos(tile_id, 0, 0);
		SetTileSize(tile_id, 1920, 1000);
		SetTileExtra(tile_id, 5);

		SetTilePrivate(tile_id, true);

		GetTilePos(tile_id, x, y);
		GetTileSize(tile_id, size_x, size_y);
		printf("ID: %d  Type: %d  x: %d  y: %d  size_x: %d  size_y: %d  extra: %d private: %b mytile: %d", tile_id, GetTileType(tile_id), x, y, size_x, size_y, GetTileExtra(tile_id), IsTilePrivate(tile_id), IsMyTile(tile_id));
	}

	new c;
	for(new i = 0; i < GetMaxTiles(); i ++) if(IsValidTile(i)) c ++;
	
	printf("Tiles: %d/%d", c, GetMaxTiles());

	SetMaxTiles(5000);

	c = 0;
	for(new i = 0; i < GetMaxTiles(); i ++) if(IsValidTile(i)) c ++;

	printf("Tiles: %d/%d", c, GetMaxTiles());

	return 1;
}

public CursorTimer()
{
	#if defined PRINT_CURSOR

	new x, y;

	GetCursorPos(x, y);

	if(IsLocalKeyDown(VK_ALT)) SetCursorPos(x, y + 1);

	if(cursor_x != x || cursor_y != y)
	{
		printf("CURSOR    x: %d  y: %d", x, y);

		cursor_x = x;
		cursor_y = y;
	}

	#endif
}

public WindowTimer()
{
	#if defined PRINT_WINDOW

	if(!IsSAMPFocused()) return;

	new x, y, size_x, size_y;

	GetSAMPWindowPos(x, y);
	GetSAMPWindowSize(size_x, size_y);

	printf("WINDOW    x: %d  y: %d  size_x: %d  size_y: %d", x, y, size_x, size_y);

	#endif
}

public OnLocalKeyStateChange(key, newstate)
{
	#if defined PRINT_KEYS
	printf("KEY       key: %d  state: %d", key, newstate);
	#endif
}

public OnClickTile(id, x, y, key)
{
	#if defined PRINT_TILES
	printf("TILE_C    id: %d  x: %d  y: %d  key: %d  extra: %d", id, x, y, key, GetTileExtra(id));
	#endif
}