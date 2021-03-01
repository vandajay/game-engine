#ifndef			__H__INTERFACES__
#define			__H__INTERFACES__

#include <SDL2/SDL.h>
#include "Utility.hpp"

/**********************************************************************
/
/ Interfaces.hpp
/
**********************************************************************/

class GameObject {
	protected:
		Vector3 position;

};

class Updateable {
	public:
		// Virtual, behaviour can be overridden in derived class
		virtual void update(double delta) = 0;	
		virtual ~Updateable() = default;
};

class Drawable {
	public:
		Drawable();
		virtual void draw() = 0;

		// Virtual destructor required for compilation
		virtual ~Drawable() = default;

	protected:
		// Rect defines area to draw
		SDL_Rect* rect;

		// SDL_Surface = software rendering
		SDL_Surface* surface;

		// SDL_Texture = hardware rendering (optimized)
		SDL_Texture* texture;
};

// Triggered events, score, time
class UGameObject : public GameObject, public Updateable {};

// Static objects, buildings, terrain
class DGameObject : public GameObject, public Drawable {};

// Players, enemies, npc
class DUGameObject : public GameObject, public Drawable, public Updateable {};

#endif
