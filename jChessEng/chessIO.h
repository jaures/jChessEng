#pragma once
#include "chessEng.h"

//PGN Notation
/*

Event:	the name of the tournament or match event.
Site:	the location of the event. This is in "City, Region COUNTRY" format, 
		where COUNTRY is the three-letter International Olympic Committee code
		for the country. An example is "New York City, NY USA".
Date:	the starting date of the game, in YYYY.MM.DD form. "??" are used for 
		unknown values.
Round:	the playing round ordinal of the game within the event.
White:	the player of the white pieces, in "last name, first name" format.
Black:	the player of the black pieces, same format as White.
Result:	the result of the game. This can only have four possible values: 
		"1-0" (White won), "0-1" (Black won), "1/2-1/2" (Draw), or "*" (other, 
		e.g., the game is ongoing).

FEN:	The FEN Notation for how initial board setup
*/

//FEN NOTATION:
/*
<FEN> ::=  <Piece Placement>
			' ' <Side to move>
			' ' <Castling ability>
			' ' <En passant target square>
			' ' <Halfmove clock>
			' ' <Fullmove counter>
*/



// Standard Algebraic Notation (SAN) - 
//<move descriptor> :: = <from square><to square>[<promoted to>]
//<square>        :: = <file letter><rank number>
//<file letter>   :: = 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h'
//<rank number>   :: = '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8'
//<promoted to>   :: = 'q' | 'r' | 'b' | 'n'

