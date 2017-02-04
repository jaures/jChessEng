#pragma once
#include <cstdint>
#include <algorithm>
#include "chessEngConst.h"

#pragma region Auxillary Function

#pragma region Bit Magic Functions

///LeastSignificantBit
//	Returns U64 of the position of least significant set bit
_inline static uint64_t lsb(uint64_t a)
{
	return uint64_t(a & -(int64_t)a);
}

///MostSignificantBit
//	Returns a U64 of the position of most significant set bit 
_inline static uint64_t msb(uint64_t a)
{
	for (int i = 0; i < 6; i++)
	{
		a |= (a >> (1 << i));
	}
	return uint64_t((a + 1) >> 1);
}

///BitCount
//	Returns U8 of the count of bits set in a
_inline static uint_fast8_t bitCount(uint64_t a)
{
	a = a - ((a >> 1) & 0x5555555555555555UL);
	a = (a & 0x3333333333333333UL) + ((a >> 2) & 0x3333333333333333UL);
	a = (int)(uint64_t(((a + (a >> 4)) & 0xF0F0F0F0F0F0F0FUL) * 0x101010101010101UL) >> 56);

	return a;
}

///BitPosition 
//	Returns a U8 of the position index of set bit in a
_inline static uint_fast8_t bitpos(uint64_t a)
{
	return (64 - bitCount(-int64_t(a)));
}

///BitboardVerticalFlip
//	Returns a U64 of the vertical flip of a
_inline static uint64_t bitVertFlip(uint64_t a)
{
	return ((a << 56)) |
		((a << 40) & (0x00ff000000000000)) |
		((a << 24) & (0x0000ff0000000000)) |
		((a << 8) & (0x000000ff00000000)) |
		((a >> 8) & (0x00000000ff000000)) |
		((a >> 24) & (0x0000000000ff0000)) |
		((a >> 40) & (0x000000000000ff00)) |
		((a >> 56));

}

///BitboardHorizontalFlip
//	Returns a U64 of the horizantal flip of a
_inline static uint64_t bitHorzFlip(uint64_t a)
{
	a = ((a >> 1) & 0x5555555555555555) + 2 * (a & 0x5555555555555555);
	a = ((a >> 2) & 0x3333333333333333) + 4 * (a & 0x3333333333333333);
	a = ((a >> 4) & 0x0f0f0f0f0f0f0f0f) + 16 * (a & 0x0f0f0f0f0f0f0f0f);

	return a;
}

///BitInverse
//	Returns a U64 of the 180 degree rotation of bitboard a
_inline static uint64_t bit_180Rot(uint64_t a)
{
	return bitHorzFlip(bitVertFlip(a));
}

#pragma endregion

#pragma region Other Functions
///InRange
//	Return bool of whether @x is on the interval [@a,@b)
_inline static bool IN_RANGE(uint_fast8_t x, uint_fast8_t b = 64, uint_fast8_t a = 0)
{
	return bool{ (x >= a) && (x < b) };
}

///LeftOf
//	Returns bool of whether or not @a is to the left of @x on a row
_inline static bool LEFT_OF(uint_fast8_t a, uint_fast8_t x)
{
	return bool{ (x%8) > (a%8) };
}

///RightOf
//	Returns bool of whether or not @a is to the right of @x on a row
_inline static bool RIGHT_OF(uint_fast8_t a, uint_fast8_t x)
{
	return bool{ (x % 8) < (a % 8) };
}

///Rank
//	Returns U64 of the @rth rank with respect to white
_inline static uint64_t RANK(uint_fast8_t r)
{
	return uint64_t{ 0xff } << 8*(r-1);
}

///File
//	Returns U64 of the @fth file with respect to white
_inline static uint64_t FILE(uint_fast8_t f)
{
	return uint64_t{ 0x101010101010101 } << (f-1)%8;
}

///PositionToU64
//	Returns a u64 with the @ath bit set
_inline static uint64_t U8PosToU64(uint_fast8_t a)
{
	return uint64_t{ 1 } << a;
}

#pragma endregion

#pragma endregion
