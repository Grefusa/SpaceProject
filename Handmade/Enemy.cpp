#include "Enemy.h"
#include "DebugManager.h"



Enemy::Enemy(){

	m_velocity = 0.16f;
	m_position = glm::vec3(0, 0, -10);
}


Enemy::~Enemy(){
}

void Enemy::SetVelocity(float vel) {

	m_velocity = vel;

}

glm::vec3 Enemy::GetPos() {
	
	return m_position;
}

void Enemy::Update(){

	m_direction = glm::vec3(0, 0, 1);


	m_position += m_direction * m_velocity;



}

void Enemy::Draw() {

	GameObject::SetIdentity();

	GameObject::Translate(m_position.x, m_position.y, m_position.z);
	TheDebug::Instance()->DrawCube3D(1, 0.5, 3, 0, 1, 0);
}
