#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.h"
#include "Graphics.h"
#include "Input.h"


namespace{
    const int FPS = 60;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game(){   
    //Intialize the game and start the game loop
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game(){

}

void Game::gameLoop(){
    Graphics graphics;
    Input input;
    SDL_Event event;

    TTF_Init();

    this->_player = Player(graphics,100,100);
    this->_level = Level("Map 1", Vector2(100, 100), graphics);

    int LAST_UPDATE_TIME = SDL_GetTicks();
    //Start the game loop
    while(true){
		input.BeginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.KeyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.KeyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
			this->_player.moveLeft();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
			this->_player.moveRight();
		}

		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->_player.stopMoving();
		}

        const int CURRENT_TIME = SDL_GetTicks();
        int ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE_TIME;
        //this->fpsCounter.SetText(std::to_string(std::min(ELAPSED_TIME,MAX_FRAME_TIME)));
        /*Limit the frames by getting the minimum between the Max Framerate and the current Framerate
            Ex: If the time of the gameloop is less than the max framerate then the game adds the current framerate to the update function.
            Ex: If the time of the gameloop is greater than the max framerate then the game adds the max framerate to the update with that limiting the game framerate (FPS).
        */
        this->update(std::min(ELAPSED_TIME,MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME;

        this->draw(graphics);
    }
}

void Game::draw(Graphics &graphics){
    graphics.clear();

    this->_level.draw(graphics);
    this->_player.draw(graphics);

    graphics.flip();
}

void Game::update(float elapsedTime){
    this->_player.update(elapsedTime);
    this->_level.update(elapsedTime);
}