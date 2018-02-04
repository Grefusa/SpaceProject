#include "Planet.h"
#include "DebugManager.h"



Planet::Planet(){
	
	m_velocity = 0.05f;
}

void Planet::SetVelocity(float vel) {

	m_velocity = vel;

}

glm::vec3 Planet::GetPos() {

	return m_position;

}

void Planet::Update() {

	m_direction = glm::vec3(0, 1, 1);

	m_position += m_direction * m_velocity;


}

void Planet::Draw() {

	GameObject::SetIdentity();

	GameObject::Translate(m_position.x, m_position.y, m_position.z);
	TheDebug::Instance()->DrawSphere3D(3.0f, 1, 1, 0);


}


Planet::~Planet() {


}
