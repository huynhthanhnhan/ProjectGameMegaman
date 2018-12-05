#include "PlaySceneIntro.h"



PlaySceneIntro::PlaySceneIntro()
{
	this->_application = Application::Instance();
}


PlaySceneIntro::~PlaySceneIntro()
{
}

void PlaySceneIntro::Render()
{
	this->_map->Render(Map::MapLevel2);
}

void PlaySceneIntro::ProcessInput()
{
	KeyBoard* key = KeyBoard::Instance();			//get KeyBoard
	key->update();
}

void PlaySceneIntro::LoadContent()
{
	this->_camera = Camera::Instance();

	float wndWidth = _application->getWidth();
	float wndHeight = _application->getHeight();

	this->_camera->setPosition(0, WORLD_Y - MAP_HEIGHT - Application::Instance()->getHeight());
	this->_map = new Map();
	this->_map->SetCamera(this->_camera);
}

void PlaySceneIntro::OnKeyDown(int Keycode)
{
}

void PlaySceneIntro::OnKeyUp(int Keycode)
{
}


void PlaySceneIntro::IsDead()
{
}

void PlaySceneIntro::Update(float delta)
{

}
