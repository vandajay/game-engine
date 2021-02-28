#ifndef			__HPP__SPRITE__
#define			__HPP__SPRITE__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Interfaces.hpp"
#include "Utility.hpp"
#include "Scene.hpp"
#include "Projectile.hpp"

class Sprite : public DUGameObject {
	public:
		Sprite(std::string path);
		Sprite(SDL_Surface *surface);
		Sprite();
		~Sprite();
		void update(double delta);
		void draw();	
		void left(double delta);
		void right(double delta);
		void up(double delta);
		void down(double delta);
		void fire(double delta);
		void setScene(Scene* scene);
	private:
		Vector3 velocity;
		Scene* scene;
		const char *path;
};

#endif
