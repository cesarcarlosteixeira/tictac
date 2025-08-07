#ifndef GAME_H
#define GAME_H
#include <stdio.h>

enum ToeError {
  NO_ERROR,
	OUT_OF_BOUNDS,
	ALREADY_FILLED
};

/*
 * Represents an state of an point and
 * victory condition
*/
enum ToeState {
	STATE_EMPTY,
	STATE_TIC,
	STATE_TAC,
	STATE_DRAW
};

struct Toe {
  enum ToeState table[3][3];
	int turn;
};

/*
 * Sets the state of a point in the game
 * table. if the point is in an invalid state 
 * (e.g, a1 = STATE_DRAW, b2 = 10) then the behaviour 
 * is undefined.
*/
enum ToeError toe_move(
	struct Toe *g,
  char v, 
  char h
);

enum ToeState toe_victory(
  struct Toe const *const t
);

void toe_display(
	struct Toe const *const t
);

inline void toe_clear_screen() {
	fputs("\033[2J\033[H", stdout);
}

inline void toe_presentation(
	struct Toe const *const t
) {
	toe_clear_screen();
	toe_display(t);
}

/*
 * returns a static allocated string representation for 
 * the victory condition, behaviour is undefined 
 * if victory is in an invalid state.
*/ 
const char *toe_winner(enum ToeState victory);
#endif
