#ifndef PLANET_H
#define PLANET_H

#include<glm.hpp>
#include"GameObject.h"


class Planet : Public GameObject {

public:
	Planet();
	virtual ~Planet();
	
	void SetVelocity(float vel);
	glm::vec3 GetPos();

public:
	virtual bool Create() { return true; }
	virtual void Update();
	virtual void Draw();
	virtual void Destroy() {};

private:

	float m_velocity;
	glm::vec3 m_position;
	glm::vec3 m_direction;


};

#endif