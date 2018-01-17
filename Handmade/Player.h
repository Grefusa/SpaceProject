#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
class Player : 	public GameObject {

public:
	Player();
	virtual ~Player();

public:

	virtual bool Create() { return true; }
	virtual void Update() {};
	virtual void Draw();
	virtual void Destroy() {};

private:





};

#endif