#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy();
	virtual ~Enemy();

public:
	virtual bool Create() { return true; }
	virtual void Update() {};
	virtual void Draw();
	virtual void Destroy() {};
};


#endif
