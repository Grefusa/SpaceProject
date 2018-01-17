#include "Player.h"
#include "DebugManager.h"




Player::Player()
{
}


Player::~Player()
{
}

void Player::Draw() {

	GameObject::Translate(1, 0, 1);
	TheDebug::Instance()->DrawSphere3D(1, 0, 0, 1);
}
