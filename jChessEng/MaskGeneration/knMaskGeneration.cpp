#include "../chessEng.h"

///Knight Mask Generation Function
//	- @Returns a U64 of Knight's Full attack at position loc 
//
uint64_t chssEng::knMsk(uint_fast8_t loc)
{
	uint64_t mask = 0;
	const uint_fast8_t knShifts[4] = { 10, 17, 6, 15, };

	for (int i = 0; i < 4; i++)
	{
		if (i < 2)
		{
			//Positive Shift
			mask |= (IN_RANGE(loc + knShifts[i]) && RIGHT_OF(loc, loc + knShifts[i])) ?
				(uint64_t{ 1 } << loc + knShifts[i]) : (0);

			//Negative Shifts
			mask |= (IN_RANGE(loc - knShifts[i]) && LEFT_OF(loc, loc - knShifts[i])) ?
				(uint64_t{ 1 } << loc - knShifts[i]) : (0);
		}
		else
		{
			//Positive Shift
			mask |= (IN_RANGE(loc + knShifts[i]) && LEFT_OF(loc, loc + knShifts[i])) ?
				(uint64_t{ 1 } << loc + knShifts[i]) : (0);

			//Negative Shifts
			mask |= (IN_RANGE(loc - knShifts[i]) && RIGHT_OF(loc, loc - knShifts[i])) ?
				(uint64_t{ 1 } << loc - knShifts[i]) : (0);

		}
	}

	return mask;

}