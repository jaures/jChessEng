#include "../chessEng.h"

//Rook Functions
//	Returns uint64_t[4] with all directions
//	where @pos represents the position of set bit on U64 msk
uint64_t* chssEng::rkMsk(uint_fast8_t loc)
{
	uint64_t msk[4] = {
		rkR(loc),		//Rook Right ->LSB
		rkL(loc),		//Rook Left  ->MSB
		rkU(loc),		//Rook UP    ->LSB
		rkD(loc) };		//Rook Down  ->MSB

	return msk;
}

//Left Side of the Mask
uint64_t chssEng::rkL(uint_fast8_t loc)		
{
	uint64_t mask = 0;

	//Left Along the Rank (Horz)
	for (int j = loc - 1; LEFT_OF(loc, j) && (j >= 0); j--)
	{
		mask |= (uint64_t{ 1 } << j);
	}

	return mask;
}

//Right Side of the Mask
uint64_t chssEng::rkR(uint_fast8_t loc)		
{
	uint64_t mask = 0;

	//Right Along the Rank (Horz)
	for (int j = loc + 1; RIGHT_OF(loc, j) && (j < 64); j++)
	{
		mask |= (uint64_t{ 1 } << j);
	}

	return mask;
}

//Upper part of the Mask
uint64_t chssEng::rkU(uint_fast8_t loc)		
{
	uint64_t mask = 0;

	//Upward Along the File (Vert)
	for (int j = loc + 8; j < 64; j += 8)
	{
		mask |= (uint64_t{ 1 } << j);
	}

	return mask;
}

//Lower part of the Mask
uint64_t chssEng::rkD(uint_fast8_t loc)		
{
	uint64_t mask = 0;

	//Downward Along the File (Vert)
	for (int j = loc - 8; j >= 0; j -= 8)
	{
		mask |= (uint64_t{ 1 } << j);
	}

	return mask;
}