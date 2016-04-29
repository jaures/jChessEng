#pragma once
#include "auxStructs.h"


class chssEng
{
public:
	chssEng();
	~chssEng();

private:
#pragma region Variables
	///Variables

	//Move Generation Masks
	uint64_t kgMask[64];	//King Mask
	uint64_t bpMask[64][4];	//Bishop Mask
	uint64_t knMask[64];	//Knight Mask	
	uint64_t rkMask[64][4];	//Rook Mask
	uint64_t pwMask[2][56][2];	//Pawn Mask

	//GameBoard
	//gBB gameBoard;
	


#pragma endregion


#pragma region Mask Generation Functions
	//Generates Masks for Lookup Arrays 


	///King Functions
	//	Returnns a U64 of the Kings Moveable Mask at position loc
	uint64_t kgMsk(uint_fast8_t loc);


	///Bishop Functions
	//	Returns U64[4] of the Bishops Moveable Mask at position loc
	//		- { NW, SE, NE, SW }
	uint64_t* bpMsk(uint_fast8_t loc);

	uint64_t bpNW(uint_fast8_t loc);	//NorthWest portion of the Mask
	uint64_t bpSE(uint_fast8_t loc);	//SouthEast portion of the Mask
	uint64_t bpNE(uint_fast8_t loc);	//NorthEast portion of the Mask
	uint64_t bpSW(uint_fast8_t loc);	//SouthWest portion of the Mask


	///Knight Functions
	//	Returns a U64 of the Knights Moveable Mask at position loc
	uint64_t knMsk(uint_fast8_t loc);


	///Rook Functions
	//	Returns U64[4] of the Rook Moveable Mask at position loc
	//		- { L, R, U, D }
	uint64_t* rkMsk(uint_fast8_t loc);
	
	//	Returns U64 of Rooks Movable Mask in a Direction
	uint64_t rkL(uint_fast8_t loc);		//Left Side of the Mask
	uint64_t rkR(uint_fast8_t loc);		//Right Side of the Mask
	uint64_t rkU(uint_fast8_t loc);		//Upper part of the Mask
	uint64_t rkD(uint_fast8_t loc);		//Lower part of the Mask


	///Pawn Functions

	//	Returns U64[2] of White Pawn Attack and Moveable Mask at position loc
	uint64_t* W_pwMsk(uint_fast8_t loc);

	//	Returns U64[2] of Black Pawn Attack and Moveable Mask at position loc
	uint64_t* B_pwMsk(uint_fast8_t loc);

	//	Returns U64 of Pawns Moveable Mask
	uint64_t pwMV(uint_fast8_t loc);

	//	Returns U64 of Pawns Attackable Mask
	uint64_t pwATK(uint_fast8_t loc);

#pragma endregion

#pragma region Mask Initialization Functions
	//Initialize all the Masks
	void initMasks();

	void initBP();		//Initialize the Bishop Masks
	void initKN();		//Initialize the Knight Masks
	void initRK();		//Initialize the Rook Masks
	void initPW();		//Initialize the Pawn Masks

#pragma endregion

#pragma region Move Generation Functions
	//Generate The Actual Move Mask Based on Current GameBoard

	//King & Knight	

	//Generate Castle Masks for the King depending on color
	//
	//Modifies:
	//
	uint64_t _genCastle(uint_fast8_t loc, uint_fast8_t color, uint_fast8_t side);

	//Generate Attack Mask for King or Knight
	//
	//Modifies:
	//
	uint64_t _genAttk_KgKn(uint_fast8_t loc, uint_fast8_t type);


	//Rook & Bishop		

	//Generate Attack Mask for Bishop or Rook
	//
	//Modifies
	//
	uint64_t _genAttk_BpRk(uint_fast8_t loc, uint_fast8_t type);


	//Queen

	//Generate Attack Mask For Queen or (Bishop || Rook)
	//
	//Modifies:
	//
	uint64_t _genAttk_qn(uint_fast8_t loc);


	//Pawn

	//Generate Attack
	uint64_t _genAttk_pw(uint_fast8_t loc, uint_fast8_t color);

	//Generate Mask of Movable Locations for the Pawn
	uint64_t _genMv_pw(uint_fast8_t loc, uint_fast8_t color);

#pragma endregion

};

