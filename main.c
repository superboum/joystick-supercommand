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

void launch_command() {
  printf("EVENT TRIGGERED\n");
  system("killall -9 emulationstation mame SkullGirls.x86_64-pc-linux-gnu LethalLeague");
}

void watch(int i) {
  SDL_Joystick *joystick = SDL_JoystickOpen(i);
  SDL_bool done = SDL_FALSE;
  SDL_Event event;
  int trigger[3] = {0,0,0};
  while(!done) {
    usleep(200);
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_JOYBUTTONDOWN:
          printf("Joystick %d button %d down\n",
            event.jbutton.which, event.jbutton.button);
          if (event.jbutton.button == BUTTON_PLAYER_1) trigger[0] = 1;
          if (event.jbutton.button == BUTTON_PLAYER_2) trigger[1] = 1;
          if (event.jbutton.button == BUTTON_CREDIT)   trigger[2] = 1;
          break;
        case SDL_JOYBUTTONUP:
          printf("Joystick %d button %d up\n",
            event.jbutton.which, event.jbutton.button);
          if (event.jbutton.button == BUTTON_PLAYER_1) trigger[0] = 0;
          if (event.jbutton.button == BUTTON_PLAYER_2) trigger[1] = 0;
          if (event.jbutton.button == BUTTON_CREDIT)   trigger[2] = 0;
          break;
        case SDL_QUIT:
          done = SDL_TRUE;
          break;
        default:
          break;
      }
    }

    if (trigger[0] && trigger[1] && trigger[2]) {
      launch_command();
    }
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
