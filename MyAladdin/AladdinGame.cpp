#include "AladdinGame.h"
#include"PlaySence.h"
#include "BossScene.h"
#include "LevelCompleteScene.h"
#include "SelectScene.h"

AladdinGame*	AladdinGame::mInstance;

AladdinGame::AladdinGame()
{

}


AladdinGame::~AladdinGame()
{
}


AladdinGame* AladdinGame::Instance()
{
	if (!mInstance)
		mInstance = new AladdinGame();

	return AladdinGame::mInstance;
}

void AladdinGame::LoadResource()
{
	//PlaySence* sence = new PlaySence();
	//this->AddSence(sence);
	//SenceManager::Instance()->ReplaceSence(sence);

	PlaySence* sence = new PlaySence();
	this->AddSence(sence);
	SenceManager::Instance()->ReplaceSence(sence);

	//LevelCompleteScene* scene = new LevelCompleteScene();
	//this->AddSence(scene);
	//SenceManager::Instance()->ReplaceSence(scene);
}

void AladdinGame::ProcessInput(int deltaTime)
{
}

void AladdinGame::OnKeyDown(int keyCode)
{
}

void AladdinGame::UpKeyDown(int keyCode)
{
}
