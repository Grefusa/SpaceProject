#include <iostream>
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
//------------------------------------------------------------------------------------------------------
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

	const Uint8* keys;

	keys = TheInput::Instance()->GetKeyStates();

	if (keys[SDL_SCANCODE_LEFT]) {

		std::cout << "LEFT" << std::endl;
	}

	if (keys[SDL_SCANCODE_RIGHT]) {

		std::cout << "RIGHT" << std::endl;
	}

	if (keys[SDL_SCANCODE_UP]) {

		std::cout << "UP" << std::endl;

	}

	if (TheInput::Instance()->GetLeftButtonState() == InputManager::DOWN) {

		std::cout << "left button click" << std::endl;
	}
	
	if (TheInput::Instance()->IsKeyPressed()) {

		std::cout << "key pressed!" << std::endl;
	}

	float x = TheInput::Instance()->GetMouseMotion().x;

	std::cout << x << std::endl;

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
	////
	////TheDebug::Instance()->DrawVertex3D(2, 0, -3, 10, 1, 0, 0); //Draw a point

	////TheDebug::Instance()->DrawVector3D(-1, 1, 0, 5.0f, 0, 0, 1); //draws a vevtor from the center

	////TheDebug::Instance()->DrawLine3D(1, 0, 1, 2, 0, -2, 5.0f, 0, 1, 0); //draws a line

	////TheDebug::Instance()->DrawCube3D(1, 2, 3, 1, 0, 0, 0.4); //Draws a cube

	////TheDebug::Instance()->DrawSphere3D(4, 0, 1, 0, 0.4); //Draws a sphere.


	////The order matters.

	//static float angle = 0.0f;

	//angle += 0.6f;

	//static float y = 0.0f;

	//if (y <= 2.0f) {
	//	y += 0.1f;
	//}
	//else {
	//	y -= 0.1f;
	//}

	//GameObject::Translate(2, y, 4); //To move the objects throught the grid
	//GameObject::Rotate(angle, 1, 0, 0); //Rotate the object
	//GameObject::Scale(2, 2, 2); //Scale the object, never scale all to 0.
	//TheDebug::Instance()->DrawCube3D(1, 1, 1, 0, 1, 1);

	//GameObject::SetIdentity(); // Reset the game object settings to draw a second object.

	//GameObject::Translate(2, 3, 7);
	//GameObject::Rotate(55, 0, 1, 0);
	//GameObject::Scale(1, 1, 1);
	//TheDebug::Instance()->DrawSphere3D(1.3f, 0, 1, 0, 1);

	m_player->Draw();
	m_enemy->Draw();



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