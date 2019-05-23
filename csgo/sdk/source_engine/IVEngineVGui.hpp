#pragma once

enum VGuiPanel_t
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

// In-game panels are cropped to the current engine viewport size
enum PaintMode_t
{
	PAINT_UIPANELS = ( 1 << 0 ),
	PAINT_INGAMEPANELS = ( 1 << 1 ),
	PAINT_CURSOR = ( 1 << 2 ), // software cursor, if appropriate
};

struct IVEngineVGui
{
	
};