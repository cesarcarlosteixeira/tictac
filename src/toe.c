#include "toe.h"
#include <stddef.h>

extern void toe_clear_screen();
extern void toe_presentation(struct Toe const *const);
static inline bool bounded_(int x) { return x >= 0 && x <= 2; }

static inline enum ToeState
check_triple_(enum ToeState const tbl[const static 3]) {
  if (tbl[0] == tbl[1] && tbl[1] == tbl[2])
    return tbl[0];
  return STATE_EMPTY;
}

static inline bool all_filled_(enum ToeState const tbl[const static 3][3]) {
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      if (tbl[i][j] == STATE_EMPTY)
        return false;
    }
  }

  return true;
}

static inline char state_repr_(enum ToeState ts) {
  switch (ts) {
  case STATE_EMPTY:
    return ' ';

  case STATE_TIC:
    return 'T';

  case STATE_TAC:
    return 'C';

  default:
    unreachable();
  }
}

enum ToeError toe_move(struct Toe *t, char v, char h) {
  int x = h - '1';
  int y = v - 'a';

  if (!bounded_(x) || !bounded_(y)) {
    return OUT_OF_BOUNDS;
  }

  switch (t->table[x][y]) {
  case STATE_TIC:
  case STATE_TAC:
    return ALREADY_FILLED;

  case STATE_EMPTY:
    if (t->turn % 2 == 0) {
      t->table[x][y] = STATE_TIC;
    } else {
      t->table[x][y] = STATE_TAC;
    }

    t->turn++;

    return NO_ERROR;

  default:
    unreachable();
  }
}

enum ToeState toe_victory(struct Toe const *const t) {
  for (size_t i = 0; i < 3; i++) {
    enum ToeState const collumn[] = {t->table[0][i], t->table[1][i],
                                     t->table[2][i]};

    auto victory = check_triple_(collumn);

    if (victory != STATE_EMPTY)
      return victory;
  }

  for (size_t i = 0; i < 3; i++) {
    auto victory = check_triple_(t->table[i]);

    if (victory != STATE_EMPTY)
      return victory;
  }

  enum ToeState d1[] = {t->table[0][0], t->table[1][1], t->table[2][2]};

  enum ToeState d2[] = {t->table[0][2], t->table[1][1], t->table[2][0]};

  auto victory_d1 = check_triple_(d1);
  auto victory_d2 = check_triple_(d2);

  if (victory_d1 != STATE_EMPTY) {
    return victory_d1;
  }

  if (victory_d2 != STATE_EMPTY) {
    return victory_d2;
  }

  if (all_filled_(t->table)) {
    return STATE_DRAW;
  }

  return STATE_EMPTY;
}

void toe_display(struct Toe const *const t) {
  constexpr char values[] = "%c: %c | %c | %c\n";
  constexpr char letters[] = "abc";

  for (size_t i = 0; i < 3; i++) {
    printf(values, letters[i], state_repr_(t->table[0][i]),
           state_repr_(t->table[1][i]), state_repr_(t->table[2][i]));
  }
}

const char *toe_winner(enum ToeState victory) {
  static const char *texts[] = {"TIC", "TAC", "DRAW"};

  switch (victory) {
  case STATE_TIC:
    return texts[0];

  case STATE_TAC:
    return texts[1];

  case STATE_DRAW:
    return texts[2];

  default:
    unreachable();
  }
}
