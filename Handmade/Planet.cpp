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


Planet::~Planet()
{
}
