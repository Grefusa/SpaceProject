#include "Enemy.h"
#include "DebugManager.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Draw() {

	GameObject::Translate(5, 0, 1);
	TheDebug::Instance()->DrawCube3D(1, 0.5, 3, 0, 1, 0);
}
