#pragma once
#include "ISence.h"
#include "KeyBoard.h"
#include "Application.h"
#include "Map.h"
#include "Camera.h"
class PlaySceneIntro : public ISence
{
private:
	Application*	_application;
	Map*			_map;
	Camera*			_camera;
public:
	PlaySceneIntro();
	~PlaySceneIntro();

	void Render();
	void LoadContent();
	void ProcessInput();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void IsDead();
	void Update(float delta);
};

