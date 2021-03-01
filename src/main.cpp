#include "Engine.hpp"
#include "Sprite.hpp"
#include "HUD.hpp"
#include "Properties.hpp"
#include <SDL2/SDL.h>

int main(int argc, char** argv){
	SDL_Log("Starting up, with following arguments:");
	for(int i=0; i<argc; ++i){
		SDL_Log("%d = %s", i, argv[i]);
	}

	// Create an engine.  Must happen early, creates the renderer.
	Engine engine( WIN_W, WIN_H );

	// Create a scene
	Scene one;

	// Make green tank sprite
	Sprite* g = new Sprite("./assets/80x80_Tank_Green_R.png");

	// Make red tank sprite
	SDL_Surface *surface = IMG_Load("./assets/80x80_Tank_Red_L.png");
	Sprite* r = new Sprite(surface);

	// Make a Sprite and add to scene. Should update and draw.
	g->setScene(&one);
	one.addUpdateable(g);
	one.addDrawable(g);

	// Initialize green tank controls
	auto g_up = [g](double delta) { g->up(delta); };
	auto g_down = [g](double delta) { g->down(delta); };
	auto g_left = [g](double delta) { g->left(delta); };
	auto g_right = [g](double delta) { g->right(delta); };
	auto g_fire = [g](double delta) { g->fire(delta); };
	one.addKeyEvent( SDLK_w, g_up );
	one.addKeyEvent( SDLK_a, g_left );
	one.addKeyEvent( SDLK_d, g_right );
	one.addKeyEvent( SDLK_s, g_down );
	one.addKeyEvent( SDLK_SPACE, g_fire );

	// Make a Sprite and add to scene. Should update and draw.	
	r->setScene(&one);
	one.addUpdateable(r);
	one.addDrawable(r);

	// Initialize green tank controls
	auto r_up = [r](double delta) { r->up(delta); };
	auto r_down = [r](double delta) { r->down(delta); };
	auto r_left = [r](double delta) { r->left(delta); };
	auto r_right = [r](double delta) { r->right(delta); };
	auto r_fire = [r](double delta) { r->fire(delta); };
	one.addKeyEvent( SDLK_UP, r_up );
	one.addKeyEvent( SDLK_LEFT, r_left );
	one.addKeyEvent( SDLK_RIGHT, r_right );
	one.addKeyEvent( SDLK_DOWN, r_down );
	one.addKeyEvent( SDLK_RSHIFT, r_fire );

	// Add the HUD
	HUD* h = new HUD();
	one.addUpdateable(h);
	one.addDrawable(h);

	// Set the scene in the engine
	engine.setScene(&one);
	
	// Get the engine running.
	engine.run();
}
