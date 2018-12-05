#include "DeadScene.h"
#include"PlaySence.h"
#include "SelectScene.h"
DeadScene::DeadScene()
{
	this->_application = Application::Instance();
	this->LoadContent();
	this->LoadResource();
}

DeadScene::~DeadScene()
{
}

void DeadScene::Render()
{
	this->_mapdead->Render(MapDead::mapDead);
	this->Render(Global::Right, Global::Dead1, aladdin2);
	this->UpdateRender(Global::Dead1);
	this->Render(Global::Right, Global::Dead2, abu2);
	this->UpdateRender(Global::Dead2);
}

void DeadScene::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
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

void DeadScene::LoadResource()
{
	std::vector<Rect*> listSourceRect_0 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "aladdin_gameover");
	this->mListSprite[Global::Dead1] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		listSourceRect_0, false);
	std::vector<Rect*> listSourceRect_1 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "abu_gameover");
	this->mListSprite[Global::Dead2] = new SpriteManager(ResourceImage::Instance()->getAbuDeadTexture(),
		listSourceRect_1, false);
	aladdin2 = Location3D(380, 350, 0);
	abu2 = Location3D(520, 400, 0);
}

void DeadScene::Refresh()
{
}

void DeadScene::UpdateRender(Global::EState currentState)
{
	if (currentState == Global::Dead1 && this->GetCurrentFrame(Global::Dead1) == 19)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_TAKE_TEAPOT);
	}

	if (currentState == Global::Dead1 && this->GetCurrentFrame(Global::Dead1) == 21)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_BOXBELL);
	}

	if (currentState == Global::Dead2 && this->GetCurrentFrame(Global::Dead2) == 5)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_ABU_WAVING);
	}

	if (currentState == Global::Dead1)
	{
		int size0 = this->mListSprite[Global::Dead1]->GetListRect().size();
		this->SetCurrentFrame(Global::Dead1, (this->GetCurrentFrame(Global::Dead1) + 1) % size0);
	}
	if (currentState == Global::Dead2)
	{
		int size1 = this->mListSprite[Global::Dead2]->GetListRect().size();
		this->SetCurrentFrame(Global::Dead2, (this->GetCurrentFrame(Global::Dead2) + 1) % size1);
	}
}


void DeadScene::LoadContent()
{
	this->_camera = Camera::Instance();
	float wndWidth = _application->getWidth();
	float wndHeight = _application->getHeight();
	this->_camera->setPosition(0, 9000);
	this->_mapdead = new MapDead();
	this->_mapdead->SetCamera(this->_camera);
}

void DeadScene::Update(float delta)
{
	if (this->GetCurrentFrame(Global::Dead1) == 52)
	{
		SelectScene* scene = new SelectScene();
		SenceManager::Instance()->ReplaceSence(scene);
		return;
	}
}

void DeadScene::ProcessInput()
{
	KeyBoard* key = KeyBoard::Instance();						//get KeyBoard

	key->update();
}

void DeadScene::OnKeyDown(int keyCode)
{
}

void DeadScene::OnKeyUp(int keyCode)
{
}

void DeadScene::IsDead()
{
}
