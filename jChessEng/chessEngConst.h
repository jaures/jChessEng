#pragma once
//Using Layout:
//	56	57	58	59	60	61	62	63
//	48	49	50	51	52	53	54	55
//	40	41	42	43	44	45	46	47
//	32	33	34	35	36	37	38	39
//	24	25	26	27	28	29	30	31
//	16	17	18	19	20	21	22	23
//	08	09	10	11	12	13	14	15
//	00	01	02	03	04	05	06	07

//

//Initial Standard Board Position Constants
#define INIT_WHITE		0xffff
#define INIT_BLACK		0xffff000000000000
#define INIT_KINGS		0x1000000000000010
#define INIT_QUEENS		0x800000000000008
#define INIT_BISHOPS	0x2400000000000024
#define INIT_KNIGHTS	0x4200000000000042
#define INIT_ROOKS		0x8100000000000081
#define INIT_PAWNS		0xff00000000ff00

//Initial Attack Masks for Standard Board
#define KG_INIT_ATK		0x2838000000003828
#define QN_INIT_ATK		0x141c000000001c14
#define BP_INIT_ATK		0x5a000000005a00
#define KN_INIT_ATK		0x18a50000a51800
#define RK_INIT_ATK		0x4281000000008142
#define PN_INIT_ATK		0xff0000ff0000

//Other Constants

#define WHITE			0
#define BLACK			1

//Board Square Colors
#define WHITE_SQUARES	0x552ad52ad52ad52a
#define BLACK_SQUARES	0xaa55aa55aa55aa55


//Default History Limit
//	Gives each player 72 moves
//	which is sufficiently higher than
//	average moves per game (~40 moves/player)
#define HIST_MAX		144						

//Size of Each Engine History State
#define HIST_STATE_SIZE 10

//Number of Types of Pieces
#define NUM_OF_PTYPES 6