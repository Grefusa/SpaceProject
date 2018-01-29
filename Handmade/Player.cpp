#include "Player.h"
#include "InputManager.h"
#include "DebugManager.h"


Player::Player() {

	m_velocity = 0.16f;
}

void Player::SetVelocity(float vel) {

	m_velocity = vel;

}

glm::vec3 Player::GetPos() {
	
	return m_position;
}

void Player::Update() {

	const Uint8* keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_LEFT]) {

		m_direction = glm::vec3(-1.0f, 0.0f, 0.0f);
	}

	else if (keys[SDL_SCANCODE_RIGHT]) {

		m_direction = glm::vec3(1.0f, 0.0f, 0.0f);
	}

	else if (keys[SDL_SCANCODE_UP]) {

		m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	}

	else if (keys[SDL_SCANCODE_DOWN]) {

		m_direction = glm::vec3(0.0f, 0.0f, 1.0f);
	}

	//If keys are not pressed, player doesn't move.
	else {

		m_direction = glm::vec3(0.0f);
	
	}

	m_position += m_direction * m_velocity;
	
}


Player::~Player()
{
}

void Player::Draw() {

	GameObject::SetIdentity();
	GameObject::Translate(m_position.x, m_position.y, m_position.z);
	TheDebug::Instance()->DrawSphere3D(1, 0, 0, 1);
}
