#include "chessEng.h"

//Bishop Functions
//	Returns uint64_t[4] with all directions
//	where @pos represents the position of set bit on U64 msk
uint64_t* chssEng::bpMsk(uint_fast8_t loc)
{
	uint64_t msk[4] = 
	{
		bpNW(loc),		//Bishop NW ->LSB
		bpSE(loc),		//Bishop SE ->MSB
		bpNE(loc),		//Bishop NE ->LSB
		bpSW(loc)		//Bishop SW ->MSB
	};		

	return msk;
}

//NorthWest portion of the Mask
uint64_t chssEng::bpNW(uint_fast8_t loc)	
{
	uint64_t mask = 0;

	//NW Direction
	for (int j = loc + 7; LEFT_OF(loc, j) && (j < 64); j += 7)
	{
		mask |= (uint64_t{ 1 } << j);
	}

	return mask;
}

//SouthEast portion of the Mask
uint64_t chssEng::bpSE(uint_fast8_t loc)	
{
	uint64_t mask = 0;

	//SE Direction
	for (int j = loc - 7; RIGHT_OF(loc, j) && (j >= 0); j -= 7)
	{
		mask |= (uint64_t{ 1 } << j);
	}

	return mask;
}

//NorthEast portion of the Mask
uint64_t chssEng::bpNE(uint_fast8_t loc)	
{
	uint64_t mask = 0;

	//NE Direction
	for (int j = loc + 9; RIGHT_OF(loc, j) && (j < 64); j += 9)
	{
		mask |= (uint64_t{ 1 } << j);
	}

	return mask;
}

//SouthWest portion of the Mask
uint64_t chssEng::bpSW(uint_fast8_t loc)	
{
	uint64_t mask = 0;

	//SW Direction
	for (int j = loc - 9; LEFT_OF(loc, j) && (j >= 0); j -= 9)
	{
		mask |= (uint64_t{ 1 } << j);
	}

	return mask;
}