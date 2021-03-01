#ifndef			__HPP__PROJECTILE__
#define			__HPP__PROJECTILE__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Interfaces.hpp"
#include "Utility.hpp"
#include "Scene.hpp"

/**********************************************************************
/
/ Projectile.hpp
/
**********************************************************************/

class Projectile : public DUGameObject {
	public:
		Projectile();
		~Projectile();
		void update(double delta);
		void draw();
		
	private:
		Vector3 velocity;
	
	// Friend class has access to Projectile.hpp, one way relationship	
	friend class Sprite;
};

#endif
