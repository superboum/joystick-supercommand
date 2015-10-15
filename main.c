#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#define BUTTON_PLAYER_1 9
#define BUTTON_PLAYER_2 18
#define BUTTON_CREDIT 8

/**
 * List available joysticks
 */
void list() {
  printf("Detected %d joysticks\n\nList: \n", SDL_NumJoysticks());

  int i;
  for(i=0;i<SDL_NumJoysticks();i++) {
    SDL_Joystick *joystick = SDL_JoystickOpen(i);
    printf("\t[id: %d] %s || Has %d buttons\n", i, SDL_JoystickName(joystick), SDL_JoystickNumButtons(joystick));
  }
}

void watch(int i) {
  SDL_Joystick *joystick = SDL_JoystickOpen(i);
  int num_button = SDL_JoystickNumButtons(joystick);
  while(1) {
    sleep(1);
    int cur_button = 0;
    for (; cur_button < num_button; cur_button++) {
      int state = SDL_JoystickGetButton(joystick, cur_button);
      printf("State of %d is %d\n",cur_button, state);
    }
    printf("----------------------\n");
    /*printf("Checking button for controller %d\n1P: %d, 2P: %d, CRED: %d\n----\n", i, bp1, bp2, credit);*/
  }
}

/**
 * Main CLI function
 */
int main(int argc, char **argv) {
  if(SDL_Init(SDL_INIT_JOYSTICK) < 0) {
    printf("Can't init SDL");
    return EXIT_FAILURE;
  }

  if (argc == 2 && strcmp(argv[1],"list") == 0) {
    list();
  }
  else if (argc == 3 && strcmp(argv[1], "watch") == 0) {
    watch((int) argv[2][0] - 48);
  }
  else {
    printf("Usage:\n");
    printf("kill_game list\t\tDisplay available controllers\n");
    printf("kill_game watch <id>\tWatch for hot key(s) on selected controller and kill the launched games\n");
  }
}
