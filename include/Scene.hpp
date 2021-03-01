#ifndef			__HPP__SCENE__
#define			__HPP__SCENE__

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include <functional>
#include "Interfaces.hpp"
#include "Utility.hpp"

/**********************************************************************
/
/ Scene.hpp
/
**********************************************************************/

class Scene {
	public:
		Scene();
		~Scene();
		void addUpdateable(Updateable* obj);
		void addDrawable(Drawable* obj);

		// Callback to fn and define in game loop
		void addKeyEvent(SDL_Keycode key, Callback fn);

		// TODO Add a remove method		

	private:
		// Scene data is stored in vectors
		std::vector<Updateable*> updateables;
		std::vector<Drawable*> drawables;

		// Key Events
		std::vector<std::pair<SDL_Keycode, Callback > > keyEvents;
	
	// Friend class can access Scene.hpp, one way relationship
	friend class Engine;
}; 

#endif
