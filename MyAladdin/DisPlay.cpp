#include "DisPlay.h"

DisPlay* DisPlay::__instance = nullptr;

DisPlay::DisPlay()
{
	this->_graphics = Graphics::Instance();
	this->_apps = Application::Instance();
	this->_hpLocation = Location3D(30, 100, 0);
	this->_shop = Location3D(200, 150, 0);
	this->_scoreLocation = Location3D(this->_apps->getWidth() - 100, 50, 0);
	this->_lifeLocation = Location3D(70, this->_apps->getHeight() - 30, 0);
	this->_numberOfAppleLocation = Location3D(this->_apps->getWidth() - 50, this->_apps->getHeight() - 30, 0);
	this->_gemLocation = Location3D(this->_apps->getWidth() - 120, this->_apps->getHeight() - 30, 0);
	this->_healthPoint = new HealthPoint();
	this->_Shop = new Shop();
	this->LoadResource();
}

DisPlay * DisPlay::Instance()
{
	if (!__instance)
		__instance = new DisPlay();
	return __instance;
}

void DisPlay::render(int hp, int life, int numberOfApple, int gem, int score)
{
	this->_sprite->Draw(-1, _lifeLocation, _lifeRect, D3DXVECTOR2(2, 2.5));
	if (hp == 0)
	{
		if (time0 % 3 == 0)
		{
			this->_healthPoint->Render(Global::Right, Global::Hp0, this->_hpLocation, D3DXVECTOR2(2, 2.5));
			this->_healthPoint->UpdateRender(Global::Hp0);
			time0 = 0;
		}
		time0++;
	}

	if (hp == 1)
	{
		if (time1 % 3 == 0)
		{
			this->_healthPoint->Render(Global::Right, Global::Hp1, this->_hpLocation, D3DXVECTOR2(2, 2.5));
			this->_healthPoint->UpdateRender(Global::Hp1);
			time1 = 0;
		}
		time1++;
	}

	if (hp == 2)
	{
		if (time2 % 3 == 0)
		{
			this->_healthPoint->Render(Global::Right, Global::Hp2, this->_hpLocation, D3DXVECTOR2(2, 2.5));
			this->_healthPoint->UpdateRender(Global::Hp2);
			time2 = 0;
		}
		time2++;
	}

	if (hp == 3)
	{
		this->_healthPoint->Render(Global::Right, Global::Hp3, this->_hpLocation, D3DXVECTOR2(2, 2.5));
		this->_healthPoint->UpdateRender(Global::Hp3);
	}

	if (hp == 4)
	{
		this->_healthPoint->Render(Global::Right, Global::Hp4, this->_hpLocation, D3DXVECTOR2(2, 2.5));
		this->_healthPoint->UpdateRender(Global::Hp4);
	}

	if (hp == 5)
	{
		this->_healthPoint->Render(Global::Right, Global::Hp5, this->_hpLocation, D3DXVECTOR2(2, 2.5));
		this->_healthPoint->UpdateRender(Global::Hp5);
	}

	if (hp == 6)
	{
		this->_healthPoint->Render(Global::Right, Global::Hp6, this->_hpLocation, D3DXVECTOR2(2, 2.5));
		this->_healthPoint->UpdateRender(Global::Hp6);
	}

	if (hp == 7)
	{
		this->_healthPoint->Render(Global::Right, Global::Hp7, this->_hpLocation, D3DXVECTOR2(2, 2.5));
		this->_healthPoint->UpdateRender(Global::Hp7);
	}

	if (hp == 8)
	{
		this->_healthPoint->Render(Global::Right, Global::Hp8, this->_hpLocation, D3DXVECTOR2(2, 2.5));
		this->_healthPoint->UpdateRender(Global::Hp8);
	}

	if (numberOfApple != 0)
	{
		if (numberOfApple <= 5)
		{
			if (timeapple % 3 == 0)
			{
				this->_sprite->Draw(-1, _numberOfAppleLocation, _appleRect, D3DXVECTOR2(3, 4));
				timeapple = 0;
			}
			timeapple++;
		}
		else
			this->_sprite->Draw(-1, _numberOfAppleLocation, _appleRect, D3DXVECTOR2(3, 4));
		this->RenderText(numberOfApple, _numberOfAppleLocation);
	}

	if (gem != 0)
	{
		this->_sprite->Draw(-1, _gemLocation, _gemRect, D3DXVECTOR2(2, 2.5));
		this->RenderText(gem, _gemLocation);
	}

	this->RenderText(life, _lifeLocation);
	if (score != 0)
		this->RenderText(score, _scoreLocation);

	if (Aladdin::getInstance()->isGems() == true && timegem % 5 < 4)
	{
		this->_Shop->Render(Global::Right, Global::Gem, this->_shop, D3DXVECTOR2(2, 2.5));
		this->_Shop->UpdateRender(Global::Gem);
	}
	timegem = (timegem + 1) % 5;

	if (Aladdin::getInstance()->isA_Deal() == true && timeadeal % 5 < 4)
	{
		this->_Shop->Render(Global::Right, Global::A_Deal, this->_shop, D3DXVECTOR2(2, 2.5));
		this->_Shop->UpdateRender(Global::A_Deal);
	}
	timeadeal = (timeadeal + 1) % 5;
}

DisPlay::~DisPlay()
{
}

void DisPlay::LoadResource()
{
	this->_sprite = new SpriteManager(ResourceImage::Instance()->getItemTexture(), std::vector<Rect*>(), false);
	this->_appleRect.update(16, 340, 352, 29, D3DXVECTOR3(12, 13, 0));
	this->_gemRect.update(111, 385, 404, 129, D3DXVECTOR3(18, 17, 0));
	this->_lifeRect.update(139, 339, 362, 164, D3DXVECTOR3(23, 25, 0));
}

void DisPlay::RenderText(int number, Location3D location)
{
	Rect rect;
	rect._update(location.x + 10, location.y - 40, 100, 100);
	this->_graphics->DrawText_(to_string(number).c_str(), &rect, this->_graphics->GetSpriteHandler(), D3DCOLOR_XRGB(255, 255, 255));
}
