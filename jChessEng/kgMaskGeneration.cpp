#include "chessEng.h"

///King Mask Generation Function
//	- @Returns a U64 of King's Full attack at position loc
//
uint64_t chssEng::kgMsk(uint_fast8_t loc)
{
	uint64_t mask = 0;

	const uint_fast8_t kgShifts[4] = { 1,7,8,9 };

	//Left 
	mask |= IN_RANGE(loc - kgShifts[0]) ? 
		(uint64_t{ 1 } << (loc - kgShifts[0])) : (0);
	//Right 
	mask |= IN_RANGE(loc + kgShifts[0]) ? 
		(uint64_t{ 1 } << (loc + kgShifts[0])) : (0);

	//Lower Left
	mask |= (IN_RANGE(loc - kgShifts[1]) && LEFT_OF(loc, loc - kgShifts[1])) ?
		(uint64_t{ 1 } << (loc - kgShifts[1])) : (0);
	//Upper Right
	mask |= (IN_RANGE(loc + kgShifts[1]) && RIGHT_OF(loc, loc + kgShifts[1])) ?
		(uint64_t{ 1 } << (loc + kgShifts[1])) : (0);

	//Down 
	mask |= IN_RANGE(loc - kgShifts[2]) ? 
		(uint64_t{ 1 } << (loc - kgShifts[2])) : (0);
	//Up 
	mask |= IN_RANGE(loc + kgShifts[2]) ? 
		(uint64_t{ 1 } << (loc + kgShifts[2])) : (0);

	//Lower Right
	mask |= (IN_RANGE(loc - kgShifts[3]) && RIGHT_OF(loc, loc - kgShifts[3])) ?
		(uint64_t{ 1 } << (loc - kgShifts[3])) : (0);
	//Upper Left
	mask |= (IN_RANGE(loc + kgShifts[3]) && LEFT_OF(loc, loc + kgShifts[3])) ?
		(uint64_t{ 1 } << (loc + kgShifts[3])) : (0);

	return mask;
}