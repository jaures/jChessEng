/// Chess Engine History Class
// Description: Manages holding a history of all the game states
//				and organizing them to facilate searching for specific game
//				states and checking for 3 fold repetition as well as holding
//				game information for each of those game states, such as:
//					>En Passant-able Pawns
//					>Castling rights
//					>Check Status
//					>Game Score (Value of captured pieces)
//					>Time Spent per move
//					>Last Move made
//
// Responsibilities:
//		>Hold Attack Masks for Both Players
//		>Hold Position Masks for Each Peice 
//

#pragma once
#include "auxFuncts.h"
#include "chessEngConst.h"

class engHistory
{
private:
#pragma region Private Functions and Variables
	//Chess Engine History Layout
	//[0] -> White Attack Mask
	//[1] -> Black Attack Mask
	//[2] -> King Mask
	//[3] -> Queen Mask
	//[4] -> Bishop Mask
	//[5] -> Knight Mask
	//[6] -> Rook Mask
	//[7] -> Pawns Mask
	//[8] -> White Mask
	//[9] -> GameInformation Mask
	//		>> [0:7]	->	White En Passantable Pawns
	//		>> [8:15]	->	Black En Passantable Pawns
	//		>> [16:18]	->	White Cstlble Status
	//		>> [19]		->	White Check Status
	//		>> [20:22]	->	Black Cstlble Status
	//		>> [23]		->	Black Check Status
	//		>> [24:31]	->	White Game Value (0 to [39,103])
	//		>> [32:39]	->	Black Game Value 0 to [39,103]
	//		>> [40]		->	Time Unit (0=sec, 1=min)
	//		>> [41:47]	->	Time Spent During move 
	//							in sec/min [0,128]
	//		>> [48:55]	->	Upper Bit position of MV
	//		>> [56:63]	->	Lower Bit position of MV
	//						

	//Chronologically Ordered Game States
	uint64_t hist[HIST_MAX][HIST_STATE_SIZE];

	//Array Holding Set of states to search for 3-fold repetition
	int arr[HIST_MAX];

	int hist_size;	//Size of history
	int	a_size;		//Size of array holding ordered states

#pragma endregion

public:

#pragma region Public Functions

	///Default Constructor
	//	states[]	-> The Game States and Game State Information
	//					-if null, initialize private variables with 0's
	//
	//Modifies:		>hist[0]
	//				>arr[0]
	//				>hist_size
	//				>a_size
	engHistory(uint64_t state[HIST_STATE_SIZE] = nullptr);

	///Default Deconstructor
	~engHistory();
	
	///Reset arr and a_size
	//Will be called after the move is made/added to history and
	//	after the move has been determined to be a condition that
	//	resets the arr[], such as:
	//		-Castle-ability status changes
	//		-Pawn move
	//		-Pawn Promotion
	//		-Any Capture
	//	*Note that it does not do any adding to either arrays,
	//		but rather just updates a_size
	//
	//Modifies:		>arr[0]
	//				>a_size
	void reset();

	///Add a New Game History State
	//Takes care of adding gamestates to the history
	//
	//Modifies:		>hist
	//				>arr
	//				>hist_size
	//				>a_size
	void add(uint64_t state[HIST_STATE_SIZE]);

	///Binary Insert Function
	//Returns index of Inserted Game History State or 
	// location of its duplicate
	//		-If @return < 0, then key wasn't found, but was inserted at
	//		 index (~return)
	//		-If @return >= 0, then the key was found at index return
	//
	//Modifies:		>arr[]
	//				>a_size
	int bInsert(int id = INT16_MIN);

	///Binary Search Function
	//@Returns index of where key first iteration of the key 
	// was inserted or found.
	//		-If return < 0, key wasn't found & should 
	//		 be inserted at index ~return
	//		-If return >= 0, then key was found and 
	//		 its first copy is found at index return
	//
	//Modifies:
	//
	int bSearch(int id);

	///Reset Flag for state at id of hist[]
	//Returns a boolean of whether or not the 
	// specified state should trigger a reset of
	// arr[] and a_size
	//		-True If:
	//			>Capture Made
	//			>Pawn Moved
	//			>Pawn Promotion
	//			>Castle-ability Change
	//		*Note: The function uses the state from
	//			the player's current move (i.e. last index)
	//			and compares it to the state from the player's 
	//			last move (i.e. 3rd to last index)
	//
	//Modifies:
	//
	_inline bool resetable(int id = INT16_MIN);

	///White-Black Attack Hash Function
	//Returns a u64 of the XOR of the white and black attack mask
	// from the state at hist index key_id
	//
	//Modifies:
	//
	_inline uint64_t w_b_attk_hash(int key_id);

	///Appropriate Index of First Ducplicate
	//Returns the index of the first duplicate of the
	// the state at hist index key_id
	//		>@m represents the starting index to searching
	//		>@dir respesents the direction/step to search in.
	//			-Default value of -1
	//
	//Modifies:
	//
	_inline int appropIndx(int m, int dir = -1);

	///Shift-Inserts into arr[]
	//Shifts-inserts a value val into arr[] at position indx
	//
	//Modifies:		>arr[]
	//				>a_size
	//
	_inline void shiftArr(int indx, int val);
	///Search For Partial Keys in both directions
	//Returns the index of a fully matching key,
	// otherwise return -1*mid
	//		-Note, will return first full match on lower end 
	//		 even if others might exist on other side of mid
	//
	//Modifies:		
	//
	int searchForPartialKeys(int mid, int key_id = INT16_MIN);

	///Compare the two history game states
	//Returns a boolean of whether or not if all the elements are
	// all equal between the two states
	//
	//Modifies:
	//
	bool statecmp(uint64_t stateA[HIST_STATE_SIZE], uint64_t stateB[HIST_STATE_SIZE]);

	///Get History Elements at indx x (and of type msk)
	//Returns a history element at indx n
	//		-If indx is not specified then return pointer to the
	//		 last history element
	//		-If indx is specified
	//			>If indx <  0, returns index from the back
	//			>If indx >= 0, reuturn index from the front
	//		-If msk is specified, then return a pointer to a single
	//		 u64 or the hist[indx][msk]	
	//		
	//
	//Modifies:
	//
	uint64_t* getHist(int indx = INT16_MIN, int msk = INT16_MIN);

	///Check for Three Fold Repition
	//Searches the history Eng for any three fold-repetition
	//		-If there are less than 3 exact matches, return
	//		 the  (# of matches)*(-1)
	//		-If there are equal to or more than 3 exact matches, 
	//		 return the (# of matches)
	//
	//Modifies:
	//
	int checkForTriples(int key_id = INT16_MIN);

#pragma endregion

};

///Default Constructor
//	states[]	-> The Game States and Game State Information
//					-if null, initialize private variables with 0's
//
//Modifies:		>hist[0]
//				>arr[0]
//				>hist_size
//				>a_size
engHistory::engHistory(uint64_t state[HIST_STATE_SIZE])
{
	if (state == nullptr)
	{
		hist_size = a_size = 0;
	}
	else
	{
		//Copies new state into history's first element
		std::copy_n(state, HIST_STATE_SIZE, hist[0]);
		hist_size = a_size = 1;
	}

	arr[0] = 0;

}

///Default Deconstructorr
engHistory::~engHistory()
{

}


///Reset arr and a_size
//Will be called after the move is made/added to history and
//	after the move has been determined to be a condition that
//	resets the arr[], such as:
//		-Castle-ability status changes
//		-Pawn move
//		-Pawn Promotion
//		-Any Capture
//	*Note that it does not do any adding to either arrays,
//		but rather just updates a_size
//
//Modifies:		>arr[0]
//				>a_size
void engHistory::reset()
{
	//Resets arr[] and a_size to only point to the last element added to history
	arr[0] = hist_size - 1;
	a_size = 1;
}

///Add a New Game History State
//Takes care of adding gamestates to the history
//
//Modifies:		>hist
//				>arr
//				>hist_size
//				>a_size
void engHistory::add(uint64_t state[HIST_STATE_SIZE])
{
	//Copies new state into history & increment hist_size
	std::copy_n(state, HIST_STATE_SIZE, hist[hist_size]);
	hist_size++;

	//Either Reset or insert new state into hist 
	(resetable()) ? (reset()) : (bInsert());
}

///Binary Insert Function
//Returns index of Inserted Game History State or 
// location of its duplicate
//		-If @return < 0, then key wasn't found, but was inserted at
//		 index ~return
//		-If @return >= 0, then the key was found at index return
//
//Modifies:		>arr[]
//				>a_size
int engHistory::bInsert(int id) 
{
	//if id is default, set it to last item in hist[]
	if (id == INT16_MIN) id = hist_size - 1;

	//Search for the key
	int res = bSearch(id);

	if ( res < 0) 
	{
		//Fix sign on res and shift the value into arr[]
		shiftArr(~res, id);
	}
	else
	{
		//Shift (-1)*id (to indicate it is a duplicate), into arr[] right
		// after first duplicate
		shiftArr(res+1, id*(-1));
	}
	
	return res;
}

///Binary Search Function
//@Returns index of where key first iteration of the key 
// was inserted or found.
//		-If return < 0, key wasn't found & should 
//		 be inserted at index ~return
//		-If return >= 0, then key was found and 
//		 its first copy is found at index return
//
//Modifies:
//
int engHistory::bSearch(int id)
{
	int lo, hi;
	
	lo = 0;
	hi = a_size - 1;

	//Create a lookup key for id
	uint64_t key_id = w_b_attk_hash(id);

	//Loop to search for the key
	while (lo < hi)
	{
		//Set the middle index
		int mi = (lo + hi) / 2;

		//Adjust mi so it points at first duplicate
		mi = appropIndx(mi);

		//Check to see if mi is a possible key

		//The key_id doesn't match the key generated at mi
		if (key_id ^ w_b_attk_hash(arr[mi]))
		{
			if (key_id > w_b_attk_hash(arr[mi]))
			{
				//Set lo to next highest non-duplicate index
				lo = appropIndx(mi + 1, 1); 
			}
			else
			{
				//Set hi to next lowest non-duplicate index 
				hi = appropIndx(mi - 1);
			}
		}
		else //The key_id matches the key generated at mi
		{
			//Check for a complete match
			if (statecmp(hist[id], hist[arr[mi]]))
			{
				//Returns index of the first copy
				return mi;
			}
			else //Only a Partial match was found for the key
			{
				//Peek in both directions to see if there are
				// any potential other partial matches
				return searchForPartialKeys(mi, id);
			}
		}
	}


	//Fix for bug when lo == hi
	if (!(key_id ^ w_b_attk_hash(arr[lo])))
	{
		if (statecmp(hist[id], hist[arr[lo]]))
		{
			//Return first duplicate
			return lo;
		}
		else
		{
			//Peek in both directions for more partial keys
			return searchForPartialKeys(lo, id);
		}
	}
	else
	{
		//If it exits the loop, then the key was not found in arr
		//	and its value lies between the index of now hi and lo
		//	:. The new hist index needs to be inserted at at lo. 
		return (~lo);
	}
}

///Search For Partial Keys in both directions
//Returns the index of a fully matching key,
// otherwise return ~mid
//		-Note, will return first full match on lower end 
//		 even if others might exist on other side of mid
//
//Modifies:		
//
int engHistory::searchForPartialKeys(int mid, int key_id)
{
	//If defualt, then set indx to last state in hist[]
	if (key_id == INT16_MIN) key_id = hist_size - 1;

	int lm, um;

	lm = mid - 1;
	um = mid + 1;

	//Check Lower Half
	while (lm >= 0)
	{
		//Skip the Duplicates
		lm = appropIndx(lm);

		//Check to make sure lm and mid are partial keys
		// otherwise break out of the loop
		if (w_b_attk_hash(key_id) ^ w_b_attk_hash(arr[lm]))
		{
			break;
		}
		else
		{
			//If they are a partial match, check to see
			// if the two are full matches
			if (statecmp(hist[arr[mid]], hist[arr[lm]]))
			{
				return lm;
			}
		}
	}

	//Check Upper Half
	while (um < hist_size)
	{
		//Skip the duplicates
		um = appropIndx(um, 1);

		//Check to make sure um and mid are partial keys
		// otherwise break out of the loop
		if (w_b_attk_hash(key_id) ^ w_b_attk_hash(arr[um]))
		{
			break;
		}
		else
		{
			//If they are a partial match, check to see
			// if the two are full matches
			if (statecmp(hist[arr[mid]], hist[arr[um]]))
			{
				return um;
			}
		}
	}

	//If Neither Branch returns a result, then there 
	// was no perfect match found
	return ~mid;
}

///Compare the two history game states
//Returns a boolean of whether or not if all the elements are
// all equal between the two states
//
//Modifies:
//
bool engHistory::statecmp(uint64_t stateA[HIST_STATE_SIZE], uint64_t stateB[HIST_STATE_SIZE])
{
	//Loop Through Elements of the states
	//	*Note, starts at 1 since only one of the
	//	 first 2 elements need to be checked (white and black)
	for (int i = 1; i < HIST_STATE_SIZE; i++)
	{
		//If they don't match, return false
		if (stateA[i] ^ stateB[i])
		{
			return false;
		}
	}

	return true;
}

///Get History Elements at indx x (and of type msk)
//Returns a history element at indx n
//		-If indx is not specified then return pointer to the
//		 last history element
//		-If indx is specified
//			>If indx <  0, returns index from the back
//			>If indx >= 0, reuturn index from the front
//		-If msk is specified, then return a pointer to a single
//		 u64 or the hist[indx][msk]	
//
//Modifies:
//
uint64_t* engHistory::getHist(int indx, int msk)
{
	//If defualt, then set indx to last state in hist[]
	if (indx == INT16_MIN)
	{
		indx = hist_size - 1;
	}
	else //Adjust for indx's sign
	{
		indx += (indx < 0) ? (hist_size) : 0;
	}

	//If msk is the default, return whole state, 
	// otherwise return pointer to state[msk]
	return (msk == INT16_MIN) ? (hist[indx]) :
		(&(hist[indx][msk]));
}

///Check for Three Fold Repition
//Searches the history Eng for any three fold-repetition
//		-If there are less than 3 exact matches, return
//		 the  (# of matches)*(-1)
//		-If there are equal to or more than 3 exact matches, 
//		 return the (# of matches)
//
//Modifies:
//
int engHistory::checkForTriples(int key_id)
{
	//If default, set key_id to last item in hist[]
	if (key_id == INT16_MIN) key_id = hist_size - 1;

	//Search for the key;
	int res = bSearch(key_id);

	if (res < 0) //Key was not found
	{
		return 0;
	}
	else //Key was found
	{
		//Get the number of copies of key
		int cnt = 1;


		while (arr[res + cnt] < 0 && (res + cnt) < a_size)
		{
			cnt++;
		}

		//Return negative count of duplicates if less than 3,
		// otherwise, return the count 
		return (cnt < 3) ? ((-1)*cnt) : (cnt);
	}
}

///Shift-Inserts into arr[]
//Shifts-inserts a value v into arr[] at position indx
//
//Modifies:		>arr[]
//				>a_size
//
_inline void engHistory::shiftArr(int indx, int val)
{
	//Shift over all elements after indx
	for (int i = a_size; i > indx; i--)
	{
		arr[i] = arr[i - 1];
	}

	//Insert new value into indx
	arr[indx] = val;

	//Increment a_size since a new items been added
	a_size++;
}

///Reset Flag for state at id of hist[]
//Returns a boolean of whether or not the 
// specified state should trigger a reset of
// arr[] and a_size
//		-True If:
//			>Capture Made
//			>Pawn Moved
//			>Pawn Promotion
//			>Castle-ability Change
//		*Note: The function uses the state from
//			the player's current move (i.e. last index)
//			and compares it to the state from the player's 
//			last move (i.e. 3rd to last index)
//
//Modifies:
//
_inline bool engHistory::resetable(int id)
{
	//Return False if arr[] doesn't contain at least 
	// 2 moves by one player
	if (a_size < 3) return false;

#ifndef RSTBL_GAME_INFO_MASK 
	//Mask for bits related to determining
	// the resetability
#define RSTBL_GAMEINFO_MASK 0xffff000000ffffff
#endif

	//If id is default, set it to last index
	if (id == INT16_MIN)
	{
		id = hist_size - 1;
	}
	else
	{
		//Otherwise Adjust for the id's sign
		id += (id < 0) ? (hist_size) : (0);
	}

	//Return Boolean of Resetability
	// Curr_State = hist[id] 
	// Past_State = hist[id-2]
	return bool(
		// (Compare Relevent bits of GameInfo)
		((hist[id][HIST_STATE_SIZE -1] ^ hist[id - 2][HIST_STATE_SIZE - 1]) & RSTBL_GAMEINFO_MASK));

#undef RSTBL_GAME_INFO_MASK 
}

///White-Black Attack Hash Function
//Returns a u64 of the XOR of the white and black attack mask
// from the state at hist[id]
//
//Modifies:
//
_inline uint64_t engHistory::w_b_attk_hash(int id)
{
	return (hist[id][0] ^ hist[id][1]);
}

///Appropriate Index of First Ducplicate
//Returns the index of the first positive duplicate of
// the state at hist index key_id
//		>@m represents the starting index to searching
//		>@dir respesents the direction/step to search in.
//			-Default value of -1
//
//Modifies:
//
_inline int engHistory::appropIndx(int m, int dir)
{
	while (arr[m] < 0)
	{
		m += dir;
	}
	
	return m;
}