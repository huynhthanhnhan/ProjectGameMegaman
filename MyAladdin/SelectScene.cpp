#include "SelectScene.h"
#include"PlaySence.h"
#include"BossScene.h"
SelectScene::SelectScene()
{
	this->_graphic = Graphics::Instance();
	this->_application = Application::Instance();
	this->LoadContent();
	this->LoadResource();
	GoKnife = true;
}

SelectScene::~SelectScene()
{
}

void SelectScene::Render()
{
	this->_mapmenu->Render(MapMenu::mapMenu);
	this->_sprite_menu = new SpriteManager(ResourceImage::Instance()->getMenu(), std::vector<Rect*>(), false);
	_menuRect.update(0, 0, 243, 90);
	this->_sprite_menu->Draw(-1, Location3D(400, 250, 0), _menuRect);

	Rect rect1;
	rect1._update(location.x - 100, location.y - 120, 400, 50);
	this->_graphic->DrawText_("Agrabah Market", &rect1, this->_graphic->GetSpriteHandler(), D3DCOLOR_XRGB(255, 255, 15));
	Rect rect2;
	rect2._update(location.x - 100, location.y - 70, 400, 50);
	this->_graphic->DrawText_("Boss Jafar", &rect2, this->_graphic->GetSpriteHandler(), D3DCOLOR_XRGB(255, 255, 15));
	Rect rect3;
	rect3._update(location.x - 100, location.y - 20, 400, 50);
	this->_graphic->DrawText_("Exit", &rect3, this->_graphic->GetSpriteHandler(), D3DCOLOR_XRGB(255, 255, 15));
	this->Render(Global::Right, Global::Knife, knife);
}

void SelectScene::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
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

void SelectScene::LoadResource()
{

	std::vector<Rect*> listSourceRect_0 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "knife");
	this->mListSprite[Global::Knife] = new SpriteManager(ResourceImage::Instance()->getKnifeMenu(),
		listSourceRect_0, false);

}

void SelectScene::Refresh()
{
}

void SelectScene::UpdateRender(Global::EState currentState)
{
	
}


void SelectScene::LoadContent()
{
	this->_camera = Camera::Instance();
	float wndWidth = _application->getWidth();
	float wndHeight = _application->getHeight();
	this->_camera->setPosition(0, 9542);
	this->_mapmenu = new MapMenu();
	this->_mapmenu->SetCamera(this->_camera);
	this->_sound = Sound::Instance();
	this->_sound->playBackGround(SOUND_BACKGROUND_MENU,100, true);
}

void SelectScene::Update(float delta)
{
	Aladdin* _aladdin;
	_aladdin = Aladdin::getInstance();

	if (knife.x <= 250 && GoKnife == true)
	{	
		knife.x = knife.x - 5;
		if (knife.x <= 220)
			GoKnife = false;
	}
	else
	{
		knife.x = knife.x + 5;
		if (knife.x >= 250)
			GoKnife = true;
	}

	this->_sound = Sound::Instance();
	if (KeyBoard::Instance()->isKeyDown(DIK_UP) && knife.y > 320)
	{
		this->_sound->play(SOUND_MENU_CHANGE);
		knife.y = knife.y - 50;
	}

	if (KeyBoard::Instance()->isKeyDown(DIK_DOWN) && knife.y < 420)
	{
		this->_sound->play(SOUND_MENU_CHANGE);
		knife.y = knife.y + 50;
	}

	if (KeyBoard::Instance()->isKeyDown(DIK_RETURN) && knife.y <= 420)
	{
		if (knife.y == 320)
		{
			this->_sound->stop(SOUND_BACKGROUND_MENU);
			this->_sound->play(SOUND_MENU_SELECT);
			PlaySence* scene = new PlaySence();
			SenceManager::Instance()->ReplaceSence(scene);
			return;
		}
		if (knife.y == 370)
		{
			this->_sound->stop(SOUND_BACKGROUND_MENU);
			this->_sound->play(SOUND_MENU_SELECT);
			BossScene* stage_jafar = new BossScene();
			SenceManager::Instance()->ReplaceSence(stage_jafar);
			return;
		}
		if (knife.y == 420)
		{
			this->_sound->stop(SOUND_BACKGROUND_MENU);
			this->_sound->play(SOUND_MENU_SELECT);
			Global::isGameRunning = false;
			PostQuitMessage(0);
		}
	}
}

void SelectScene::ProcessInput()
{
	KeyBoard* key = KeyBoard::Instance();						//get KeyBoard
	Global::EControl controller = Global::NoneControl;
	key->update();
}

void SelectScene::OnKeyDown(int keyCode)
{
}

void SelectScene::OnKeyUp(int keyCode)
{
}

void SelectScene::IsDead()
{
}