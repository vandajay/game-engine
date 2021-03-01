#include "Engine.hpp"
#include "Sprite.hpp"
#include "Properties.hpp"
#include "Projectile.hpp"

/**********************************************************************
/
/ Sprite.cpp
/
**********************************************************************/

// Overloaded constructors
Sprite::Sprite(std::string path){
	this->path = path.c_str();

	surface = IMG_Load(this->path);
	if( surface == NULL ){
		SDL_Log("Unable to load sprite.");
		exit(1);
	}

	// Convert surface -> texture (surface = software rendered, texture = hardware)
	texture = SDL_CreateTextureFromSurface(Engine::getRenderer(), surface);
	if( texture == NULL ){
		SDL_Log("-----> HAVE YOU CREATED THE ENGINE YET? <-----");
		SDL_Log("Unable to create texture. %s", SDL_GetError());
	}
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
	velocity.setX(0);
	velocity.setY(0);
	velocity.setZ(0);
}

Sprite::Sprite(SDL_Surface *surface){
	texture = SDL_CreateTextureFromSurface(Engine::getRenderer(), surface);
	if( texture == NULL ){
		SDL_Log("-----> HAVE YOU CREATED THE ENGINE YET? <-----");
		SDL_Log("Unable to create texture. %s", SDL_GetError());
	}
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
	velocity.setX(0);
	velocity.setY(0);
	velocity.setZ(0);
}

Sprite::Sprite(){
	surface = IMG_Load("./assets/banana.png");
	if( surface == NULL ){
		SDL_Log("Unable to load Sprite.");
		exit(1);
	}
	texture = SDL_CreateTextureFromSurface(Engine::getRenderer(), surface);
	if( texture == NULL ){
		SDL_Log("-----> HAVE YOU CREATED THE ENGINE YET? <-----");
		SDL_Log("Unable to create texture. %s", SDL_GetError());
	}
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
	velocity.setX(0);
	velocity.setY(0);
	velocity.setZ(0);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

/****************************************
/
/ Update Sprite
/
****************************************/
void Sprite::update(double delta){
	// So we stop getting the compiler warning for now.
	position.setX(position.getX() + velocity.getX() * delta);
	position.setY(position.getY() + velocity.getY() * delta);
	if(position.getX() > WIN_W - rect->w || position.getX() < 0){
		velocity.setX(- velocity.getX());
	}
	if(position.getY() > WIN_H - rect->h || position.getY() < 0){
		velocity.setY(- velocity.getY());
	}
}

/****************************************
/
/ Draw Sprite
/
****************************************/
void Sprite::draw(){
	SDL_Rect* dst = new SDL_Rect();
	dst->x = position.getX();
	dst->y = position.getY();
	dst->w = rect->w;
	dst->h = rect->h;
	SDL_RenderCopy(Engine::getRenderer(), texture, NULL, dst);
}

// Set scene for sprite
void Sprite::setScene(Scene* scene){
	this->scene = scene;
}

/****************************************
/
/ Controls
/
****************************************/
// WEST
void Sprite::left(double delta){
	if(velocity.getX() > -200){
		velocity.setX(velocity.getX() - 10);
	}
}

// EAST
void Sprite::right(double delta){
	if(velocity.getX() < 200){
		velocity.setX(velocity.getX() + 10);
	}
}

// NORTH
void Sprite::up(double delta){
	if(velocity.getY() > -200 ){
		velocity.setY(velocity.getY() - 10);
	}
}

// SOUTH
void Sprite::down(double delta){
	if(velocity.getY() < 200 ){
		velocity.setY(velocity.getY() + 10);
	}
}

// Fire
void Sprite::fire(double delta){
	Projectile* p = new Projectile();
	p->position.setX( position.getX() );
	p->position.setY( position.getY() );
	p->velocity.setX(velocity.getX() * 2);
	p->velocity.setY(velocity.getY() * 2);
	this->scene->addDrawable(p);
	this->scene->addUpdateable(p);
}
