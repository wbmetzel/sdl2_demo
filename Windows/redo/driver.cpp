
#include "Game.h"

int main(int argc, char* args[])
{
  Game newGame;
  bool quit = false;

  if(newGame.initialize())
  {
    do
    {

      quit = newGame.eventHandler();
      newGame.refresh();

      //environment.loadBackground();

      newGame.renderScreen();
    }while(!quit);
  }

  return 0;
}
