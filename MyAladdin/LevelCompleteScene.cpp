#include "LevelCompleteScene.h"
#include "Timer.h"
#include "BossScene.h"
#include "SenceManager.h"
#include "SelectScene.h"
LevelCompleteScene::LevelCompleteScene()
{
	this->_application = Application::Instance();
	this->LoadContent();
	this->LoadResource();
}

LevelCompleteScene::~LevelCompleteScene()
{
}

void LevelCompleteScene::Render()
{
	this->_mapcomplete->Render(MapLevelComplete::MapComplete);
	this->_sprite_victory = new SpriteManager(ResourceImage::Instance()->getVictoryTexture(), std::vector<Rect*>(), false);
	_victoryRect.update(0, 0, 232, 141);
	this->_sprite_victory->Draw(-1, Location3D(400, 380, 0), _victoryRect);
	this->Render(Global::Right, Global::Victory2, abu);
	this->UpdateRender(Global::Victory2);
	this->Render(Global::Right, Global::Victory1, aladdin);
	this->UpdateRender(Global::Victory1);
}

void LevelCompleteScene::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	if (mListSprite.find(state) == mListSprite.end())
		return;
	this->mListSprite[state]->SetPosition(position);
	this->mListSprite[state]->SetTranslation(translation);
	this->mListSprite[state]->SetRotaion(rotation);
	this->mListSprite[state]->SetRotationCenter(rotationCenter);
	this->DetermineDirection(state, direct);
	this->mListSprite[state]->Draw();
}

void LevelCompleteScene::LoadResource()
{
	std::vector<Rect*> listSourceRect_0 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "aladdin_victory");
	this->mListSprite[Global::Victory1] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		listSourceRect_0, false);
	std::vector<Rect*> listSourceRect_1 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "abu_victory");
	this->mListSprite[Global::Victory2] = new SpriteManager(ResourceImage::Instance()->getAbuVictoryTexture(),
		listSourceRect_1, false);

}

void LevelCompleteScene::Refresh()
{
}

void LevelCompleteScene::UpdateRender(Global::EState currentState)
{
	if (currentState == Global::Victory1)
	{
		int size0 = this->mListSprite[Global::Victory1]->GetListRect().size();
		this->SetCurrentFrame(Global::Victory1, (this->GetCurrentFrame(Global::Victory1) + 1) % size0);
	}
	if (currentState == Global::Victory2)
	{
		int size1 = this->mListSprite[Global::Victory2]->GetListRect().size();
		this->SetCurrentFrame(Global::Victory2, (this->GetCurrentFrame(Global::Victory2) + 1) % size1);
	}
}


void LevelCompleteScene::LoadContent()
{
	this->_camera = Camera::Instance();
	float wndWidth = _application->getWidth();
	float wndHeight = _application->getHeight();
	this->_camera->setPosition(0, 9000);
	this->_mapcomplete = new MapLevelComplete();	
	this->_mapcomplete->SetCamera(this->_camera);
	this->_sound = Sound::Instance();
	this->_sound->playBackGround(SOUND_LEVELCOMPLETE, 100, false);
}

void LevelCompleteScene::Update(float delta)
{
	abu.x -= 15;
	aladdin.x -= 15;
	Aladdin* _aladdin;
	_aladdin = Aladdin::getInstance();
	if (aladdin.x < -150 && _aladdin->isVictory1())
	{
		_aladdin->setVictory1(false);
		BossScene* scene = new BossScene();
		SenceManager::Instance()->ReplaceSence(scene);
		return;
	}
	if (aladdin.x < -150 && _aladdin->isVictory2())
	{
		_aladdin->setVictory2(false);
		SelectScene* scene = new SelectScene();
		SenceManager::Instance()->ReplaceSence(scene);
		return;
	}
}

void LevelCompleteScene::ProcessInput()
{

}

void LevelCompleteScene::OnKeyDown(int keyCode)
{
}

void LevelCompleteScene::OnKeyUp(int keyCode)
{
}

void LevelCompleteScene::IsDead()
{
}