#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include <toe.h>

void handle_game_error(enum ToeError te) {
  switch (te) {
  case NO_ERROR:
    return;
    
  case OUT_OF_BOUNDS:
    log_error(
      "out of bounds move\n",
      __LINE__,
      __func__
    );
    
    return;
    
  case ALREADY_FILLED:
    log_error(
      "already occuped position\n", 
      __LINE__,
      __func__  
    );
    return;

  default:
    unreachable();
  }
};

int main() {
  constexpr auto input_len = 4;
  constexpr char input_req[] = "input should be 2 length long\n";
	char input[input_len];
	struct Toe game = {};
	enum ToeError error = NO_ERROR;
	
  while (true) {
    toe_presentation(&game);
    handle_game_error(error);  
    
    fputs("turn move: ", stdout);
    auto input_ptr = fgets(input, input_len, stdin);

    if (!input_ptr) {
      log_error(
        "could not get input",
        __LINE__,
        __func__
      );
      return EXIT_FAILURE;
    }

    if (input[0] == '\n') {
      error = NO_ERROR;
      continue;
    }

    if (input[1] == '\n') {
      log_error(input_req, __LINE__, __func__);
      continue;
    }
    
    if (input[strlen(input) - 1] != '\n') {
      log_error(input_req, __LINE__, __func__);
      int ch; 
      while ((ch = fgetc(stdin)) != '\n' && ch != EOF);
      continue;
    }

    error = toe_move(&game, input[0], input[1]);
    auto victory = toe_victory(&game);


    if (victory != STATE_EMPTY) {
      toe_presentation(&game);
      
      printf("winner: %s!\n", toe_winner(victory));
      return EXIT_SUCCESS;
    }
	}
}
