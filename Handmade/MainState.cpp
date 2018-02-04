#include <iostream>
#include <glm.hpp>
#include <gtx\vector_angle.hpp>
#include <gtx\euler_angles.hpp>
#include <gtx\projection.hpp>
#include <gtc\matrix_transform.hpp>
#include <math.h>
#include "DebugManager.h"
#include "EndState.h"
#include "InputManager.h"
#include "Game.h"
#include "GameObject.h"
#include "MainState.h"
#include "PipelineManager.h"
#include "ScreenManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------5
MainState::MainState(GameState* state) : GameState(state)
{

	m_HUD = nullptr;
	m_HUDCamera = nullptr;
	m_mainCamera = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that creates the cameras and HUD objects
//------------------------------------------------------------------------------------------------------
bool MainState::OnEnter()
{

	//create the main camera to control the main view
	m_mainCamera = new MainCamera();

	//create the 2D camera for HUDs and sprite objects
	m_HUDCamera = new HUDCamera();

	//create a heads-up display object
	m_HUD = new HUD();
	m_HUD->Create();

	m_player = new Player;
	m_enemy = new Enemy;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates all active game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Update()
{

	//store keyboard key states in a temp variable for processing below
	const Uint8* keyState = TheInput::Instance()->GetKeyStates();

	//update main camera
	m_mainCamera->Update();

	//if ESCAPE key was pressed, return flag to end game 
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		m_isActive = m_isAlive = false;
		TheGame::Instance()->ChangeState(new EndState(this));
	}

	//ADD YOUR CODE HERE...

	m_player->Update();
	m_enemy->Update();


	//Calculate the distance between enemy and player

	glm::vec3 distanceVec = m_player->GetPos() - m_enemy->GetPos();

	float distance = sqrt((distanceVec.x * distanceVec.x) + (distanceVec.y * distanceVec.y) + 
		(distanceVec.z * distanceVec.z));

	std::cout << distance << std::endl;

	if (distance <= 2.0f) {

		std::cout << "Aah Colission!" << std::endl;
	}

	else {

		std::cout << "You are safe!" << std::endl;
	}


	return true;

}
//------------------------------------------------------------------------------------------------------
//function that displays all active and visible game objects in game state
//------------------------------------------------------------------------------------------------------
bool MainState::Draw()
{

	//first set up camera which sets the view accordingly
	//make sure this is called BEFORE displaying the grid
	m_mainCamera->Draw();

#ifdef GAME_3D

	TheScreen::Instance()->Set3DScreen(60.0f, 0.1f, 1000.0f);

#ifdef DEBUG

	TheDebug::Instance()->DrawGrid3D();
	TheDebug::Instance()->DrawCoordSystem3D(15.0f);

#endif

#endif

#ifdef GAME_2D

	TheScreen::Instance()->Set2DScreen(ScreenManager::BOTTOM_LEFT);

#ifdef DEBUG

	TheDebug::Instance()->DrawGrid2D();
	TheDebug::Instance()->DrawCoordSystem2D(15.0f);

#endif

#endif

	//ADD YOUR CODE HERE...
	

	m_player->Draw();
	m_enemy->Draw();


	glm::vec2 vertex(2, 5);
	glm::mat4 translation = glm::translate(translation, glm::vec3(-3, -1, 0));

	TheDebug::Instance()->DrawVertex3D(vertex.x, vertex.y, -0, 20.0f, 0.7f, 0.1f, 0.8f);

	glm::vec4 homogenous = glm::vec4(vertex, 0.0f, 1.0f);

	homogenous = translation * homogenous;

	vertex = glm::vec2(homogenous);

	TheDebug::Instance()->DrawVector3D(vertex.x, vertex.y, 0, 20.0f, 0.4f, 0.7f, 0.2f);

	glm::vec3 vertex3(2, 2, 3);

	glm::mat4 rotation;

	TheDebug::Instance()->DrawVector3D(vertex3.x, vertex3.y, vertex3.z, 5.0f, 0.7f, 0.1f, 0.8f);

	rotation = glm::rotate(rotation, glm::radians(30.0f), glm::vec3(0, 1, 0));

	vertex3 = glm::vec3(rotation * glm::vec4(vertex3, 1.0f));

	TheDebug::Instance()->DrawVector3D(vertex3.x, vertex3.y, vertex3.z, 5.0f, 1.0f, 0.1f, 0.8f);



	glm::vec2 vertC(2, 3);
	glm::mat4 scaling;

	scaling = glm::scale(scaling, glm::vec3(0.25, 2, 0));

	TheDebug::Instance()->DrawVector3D(vertC.x, vertC.y, 0, 5.0f, 0.7f, 0.1f, 0.8f);













#ifdef DEBUG

	//set the 2D camera and render the heads-up display last
	m_HUDCamera->Draw();
	m_HUD->Draw();

#endif

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that destroys all the game objects for the state
//------------------------------------------------------------------------------------------------------
void MainState::OnExit()
{

	//destroy the HUD, camera and grid objects
	m_HUD->Destroy();
	delete m_HUD;
	delete m_HUDCamera;
	delete m_mainCamera;

	delete m_player;
	delete m_enemy;

}