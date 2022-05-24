#pragma once

enum class EntityType
{
	Player,
	MeleeCharacter,
	RangedCharacter,
	misc

};

enum class CellType
{
	Empty,
	Edge,
	Floor,
	OuterCorner,
	InnerCorner,
	TConnector,
	XConnector
};

enum class CellID
{
	N = 0,
	F = 1,
	W_N = 2,
	W_E = 3,
	W_S = 4,
	W_W = 5,
	IC_NW = 6,
	IC_NE = 7,
	IC_SW = 8,
	IC_SE = 9,
	OC_NW = 10,
	OC_NE = 11,
	OC_SW = 12,
	OC_SE = 13,


	W_T = 13,
	C_TR = 14,
	C_TL = 15,


	WC_HS = 16,
	WC_HN = 17,
	WC_VE = 18,
	WC_VW = 19,


};

struct CT_PropData
{
	CT_PropData(int ID, int Coordinate)
	{
		propID = ID;
		coordinate = Coordinate;
	}
	int propID;
	Vector3 coordinate;
};


#define tileScale 32
#define	mapScale 64
#define tileScaleMultiplier 2