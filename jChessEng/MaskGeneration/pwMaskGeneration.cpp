#include "../chessEng.h"

///Pawn Functions

//	Returns U64[2] of White Pawn Attack and Moveable Mask at position loc
uint64_t* chssEng::W_pwMsk(uint_fast8_t loc)
{
	uint64_t mask[2] = { pwMV(loc), pwATK(loc) };

	return mask;
}

//	Returns U64[2] of Black Pawn Attack and Moveable Mask at position loc
uint64_t* chssEng::B_pwMsk(uint_fast8_t loc)
{
	uint64_t mask[2] = { pwMV(63 - loc), pwATK(63 - loc) };
	return mask;
}

//	Returns U64 of Pawns Moveable Mask
uint64_t chssEng::pwMV(uint_fast8_t loc)
{
	uint64_t mask = 0;
	
	//Add Forward Advance as long as it is in range
	//	*Note: Pawns don't have moves for anything on the 8th Rank
	mask |= IN_RANGE(loc + 8) ? (U8PosToU64(loc + 8)) : (0);

	mask |= (U8PosToU64(loc)  && RANK(2)) ? (U8PosToU64(loc + 16)) : (0);
	

	return mask;
}

//	Returns U64 of Pawns Attackable Mask
uint64_t chssEng::pwATK(uint_fast8_t loc)
{
	uint64_t mask = 0;

	//Checks if In range & Is Left of pos a
		mask = (IN_RANGE(loc + 7) && LEFT_OF(loc ,loc + 7)) ? 
			(U8PosToU64(loc + 7)) : (0);
	
	//Checks if In range & Is Right of pos a
		mask |= (IN_RANGE(loc + 9) && RIGHT_OF(loc, loc + 9)) ? 
			(U8PosToU64(loc + 9)) : (0);

	return mask;
}