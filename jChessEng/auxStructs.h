#pragma once
#include "auxFuncts.h"

#pragma region Enums

//Piece Types
enum pType
{
	//White,
	//Black,
	King,
	Queen,
	Bishop,
	Knight,
	Rook,
	Pawn,
	Custom,	//Allows for Engine to extend to custom types
	Empty	//Simple Place Holder for Empty Squares
};

//Possible States the game can be in
//	Either inPlay or in
//	One of seven end of game outcomes
enum gState
{
	inPlay,
	checkmate,
	draw,
	draw_stalemate,
	draw_fiftyMove,
	draw_threefoldRep,
	draw_insufficient,
	out_of_time			//For Losses due to time running out
};

#pragma endregion


//typedef void* (*funct_ptr)(void* argVal, int argCnt);

//typedef void* (*funct_ptr3)(void*, void*, void*, void*);


//funct_ptr functGen( )

//Position Structure
//	({ x,y } -> {'a' - 'h', '1' - '8'}
//	It handles conversions between
//	Chess Board positions and ints and 
//	converting into linear index ({a} -> {0-63}) 
typedef struct pos
{
	char x;	//a-h
	char y;	//1-8

	//Constructor for Position where {x,y} are init to {'a','1'}
	pos(int _x = 'a', int _y = '1') :x('a'), y('1')
	{
		//If both Parameters are within the correct range
		//	Then set {x,y} = {_x,_y}
		if (((_x >= 'a') && (_x <= 'h'))
			&&
			((_y >= '1') && (_y <= '8')))
		{
			x = _x;
			y = _y;
		}
	}

#pragma region Conversion Functions
	//Conversions to Position

	//Return a position given a uint64_t mask
	static const pos U64toPos(uint64_t a)
	{
		return pos{ 'a' + bitpos(a) % 8,'1' + bitpos(a) / 8 };
	}

	//Returns a const uint64_t mask to the position 
	const uint64_t toU64()
	{
		return uint64_t{ 1 } << (toInt());
	}

	//Returns a const uint8_t/int to the position
	const uint8_t toInt()
	{
		return ((x - 'a') + (y - '1') * 8);
	}

#pragma endregion
}pos;