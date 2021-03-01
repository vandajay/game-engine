#include "Engine.hpp"
#include "Properties.hpp"
#include "Scene.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**********************************************************************
/
/ Engine.cpp
/
**********************************************************************/

// For linking purposes, we need to declare this static member in the cpp file.
SDL_Renderer* Engine::renderer = nullptr;

Engine::Engine(int _width, int _height){
	// Define abstracted variables
	this->width = _width;
	this->height = _height;

	// FPS defined in Properties.hpp
	frameRate = 1000.0 / FPS;
	SDL_Init(SDL_INIT_EVERYTHING);

	// SDL Audio
	TTF_Init();

	// Initialize SDL_Window
	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	// Confirm SDL_Window
	if( window == nullptr ){
		SDL_Log("Could not create a window. %s", SDL_GetError());
	}

	// Initialize SDL_Renderer
	Engine::renderer = SDL_CreateRenderer(window, -1, 0);
	if( Engine::renderer == nullptr ){
		SDL_Log("Could not create a renderer. %s", SDL_GetError());
	}

	SDL_Log("Initialized. Frame rate set to %f.", frameRate);
}

// Engine destructor
Engine::~Engine(){
	SDL_Log("Destroying renderer.");
	SDL_DestroyRenderer(Engine::renderer);
	SDL_Log("Destroying window.");
	SDL_DestroyWindow(window);
	SDL_Log("Shutting down...");
	TTF_Quit();
	SDL_Quit();
	SDL_Log("Shutdown complete.");
}

/**************************************************
/
/ run()
/
**************************************************/

void Engine::run(){
	if(currentScene == nullptr){
		SDL_Log("No scene added yet to engine! - Aborting.");
		return;
	}

	/****************************************
	/
	/ GAME LOOP
	/
	****************************************/
	bool quit = false;
	SDL_Event event;
	last = SDL_GetTicks();
	cumulative = 0;
	while(!quit){
		if(cumulative>=1000){
			SDL_Log("Framerate is %f (%d frames).", (double)framecount / (cumulative / 1000), framecount);
			cumulative = 0;
			framecount = 0;
		}
		last = current;
		current = SDL_GetTicks();
		int delta = current - last;

		// Delta should be atleast the target framerate before we continue
		while(delta < frameRate) {
			SDL_Delay(frameRate - delta);
			current = SDL_GetTicks();
			delta = current - last;
		}

		cumulative += delta;
		double gameDelta = delta / 1000.0;

		/******************************
		/
		/ GET EVENTS
		/
		******************************/
		// process all events for each frame		
		while(SDL_PollEvent(&event) > 0){
			if(event.type == SDL_QUIT){
				quit = true;
			}

			// Check for keyboard events
			if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP){
				for(auto f = currentScene->keyEvents.begin(); f != currentScene->keyEvents.end(); ++f){
					if(event.key.keysym.sym == (*f).first){
						(*f).second(gameDelta);
						//SDL_Log("Dispatched event. %d, %f", delta, gameDelta);
					}
				}
			}

		}

		/******************************
		/
		/ UPDATE OBJECTS
		/
		******************************/
		for(std::vector<Updateable*>::iterator it = currentScene->updateables.begin(); it != currentScene->updateables.end(); ++it){ // ++it uses less memory
			(*it)->update(gameDelta);
		}			
	
		
		/******************************
		/
		/ RENDER
		/
		******************************/

				SDL_SetRenderDrawColor(Engine::renderer, BGR, BGG, BGB, BGA);
		SDL_RenderClear(Engine::renderer);

		for(std::vector<Drawable*>::iterator it = currentScene->drawables.begin(); it != currentScene->drawables.end(); ++it){
			(*it)->draw();
		}

		// FLIP image, replace currently displayed image with buffer
		SDL_RenderPresent(Engine::renderer);

		framecount++;
	}
} // end Engine::run()

void Engine::setFrameRate(double _frameRate){
	this->frameRate = _frameRate;
}

void Engine::setScene(Scene* scene){
	this->currentScene = scene;	
}

SDL_Renderer* Engine::getRenderer(){
	return Engine::renderer;
}
