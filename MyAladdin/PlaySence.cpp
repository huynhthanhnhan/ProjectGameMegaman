#include "PlaySence.h"
#include"BulletManager.h"

PlaySence::PlaySence()
{
	this->_application = Application::Instance();
	this->LoadContent();
}

PlaySence::~PlaySence()
{
}

void PlaySence::Render()
{

	this->_map->Render(Map::MapLevel1);	//Draw Map Level1

	for each (auto obj in this->_listObject)
	{
		if (!obj)
			return;
		switch (obj->getId())
		{
		case Global::GROUND:
		case Global::ROPE:
		case Global::COLUMN:
		case Global::BAR:
		case Global::STAIR:
		case Global::WALL:
		case Global::TRAP:break;
		default:
		{
			ActionObject* object = (ActionObject*)obj;
			//object->render();
			break;
		}
		}
	}
	BulletManager::Instance()->render();
	this->_aladdin->render();			//Draw Aladdin
	this->_map->Render(Map::MapLevel2);	//Draw Map Level2

	this->_listObject.clear();
	//this->_display->render(_aladdin->getHp(), _aladdin->getLife(), _aladdin->getNumberOfApple(), _aladdin->getNumberOfGem(), _aladdin->getScore());
}

void PlaySence::LoadContent()
{

	this->_aladdin = Aladdin::getInstance();
	this->_aladdin->Init(200, 7150, 10, 8, 3);
	this->_camera = Camera::Instance();

	float wndWidth = _application->getWidth();
	float wndHeight = _application->getHeight();

	this->_camera->setPosition(0, WORLD_Y - MAP_HEIGHT - Application::Instance()->getHeight());//(this->_aladdin->GetCurrentLocation().x - wndWidth / 2, this->_aladdin->GetCurrentLocation().y + wndHeight / 2);

	this->_map = new Map();
	this->_map->SetCamera(this->_camera);

	this->_quadtree = QuadTree::Instance();
	this->_quadtree->buildTree("Map\\map.txt");
	this->_display = DisPlay::Instance();
	this->_camera->update(this->_aladdin);
	//this->_sound = Sound::Instance();
	//this->_sound->playBackGround(SOUND_BACKGOUND, 100, true);
}

void PlaySence::Update(float delta)
{
	this->_camera->update(this->_aladdin);

	this->_listObject = this->_quadtree->getListObject(this->_camera->getBound());

	StaticObject::Instance()->clear();
	for each (auto obj in this->_listObject)
	{
		if (!obj)
			return;
		if (obj->getTypeObject() != Global::Static)
			obj->processCollision(_aladdin);

		switch (obj->getId())
		{
		case Global::GUARD1:
		case Global::GUARD2:
		case Global::GUARD3:
		case Global::CIVILIAN1:
		case Global::CIVILIAN2:
		case Global::CIVILIAN3:
		{
			for each (auto bullet in BulletManager::Instance()->getListBullet())
			{
				if (!bullet)
					continue;
				//if (bullet->getTypeObject() == Global::AladdinParty)
					//obj->processCollision(bullet);
				//else
				//	this->_aladdin->processCollision(bullet);
			}
			//this->_aladdin->processCollision(obj);
			break;
		}
		}
		obj->update(delta);
	}
	BulletManager::Instance()->update(delta);

	this->_aladdin->update(delta);
	if (_aladdin->getHp() < 0 && _aladdin->getLife() >= 0)
	{
		_aladdin->Revival();
		_aladdin->setLife(_aladdin->getLife() - 1);
		_aladdin->setHp(8);
		/*for each (auto obj in this->_listObject)
		{
		if (obj->getTypeObject() == Global::Enemy)
		{
		Enemy* enemy = (Enemy*)obj;
		enemy->setDead(false);
		enemy->takeAction(Global::Stand);
		}
		}*/
	}
	if (_aladdin->getLife() < 0)
	{
		this->_sound->stop();

		return;
	}
	//_aladdin->getXY();
}

void PlaySence::ProcessInput()
{
	KeyBoard* key = KeyBoard::Instance();						//get KeyBoard

	StateManager* statemanager = StateManager::Instance();		//get State Manager
	Global::EState currentState = this->_aladdin->getState();	//get Current State
	Global::EControl controller = Global::NoneControl;

	key->update();

	if (key->isKeyPress(DIK_LEFT))
	{
		controller = Global::LeftControl;
		//if (this->_aladdin->IsPushWall() && this->_aladdin->getDirect() == Global::Right)
		//{
		//	this->_aladdin->setDirect(Global::Left);
		//	this->_aladdin->Running();
		//	return;
		//}
		this->_aladdin->setDirect(Global::Left);
	}

	if (key->isKeyPress(DIK_RIGHT))
	{
		controller = Global::RightControl;
		//if (this->_aladdin->IsPushWall() && this->_aladdin->getDirect() == Global::Left)
		//{
		//	this->_aladdin->setDirect(Global::Right);
		//	this->_aladdin->Running();
		//	return;
		//}
		this->_aladdin->setDirect(Global::Right);
	}

	//if (key->isKeyPress(DIK_UP))
	//	controller = Global::UpControl;

	//if (key->isKeyPress(DIK_DOWN))
	//	controller = Global::DownControl;


	if (key->isKeyPress(DIK_S))
		controller = Global::HitControl;
	else
		Aladdin::getInstance()->bDash = true;

	if (key->isKeyDown(DIK_A))
	{
		controller = Global::ThrowControl;
	}

	if (key->isKeyDown(DIK_D))
		controller = Global::JumpControl;

	//if (KeyBoard::Instance()->isKeyPress(DIK_SPACE))
	//{
	//	this->_aladdin->setCurrentLocation(5200, 9300);
	//	this->_aladdin->updateBody();
	//	this->_aladdin->Stand();
	//	this->_aladdin->refreshTime();
	//	return;
	//}

	Global::EState nextState = statemanager->getNewState(currentState, controller);
	this->AladdinTakeAction(nextState);
}

void PlaySence::OnKeyDown(int keyCode)
{
}

void PlaySence::OnKeyUp(int keyCode)
{
}

void PlaySence::IsDead()
{
}

void PlaySence::AladdinTakeAction(Global::EState currentState)
{
	switch (currentState)
	{
	case Global::Stand: this->_aladdin->Stand(); break;
	case Global::Appearance: this->_aladdin->Appearance(); break;
	case Global::Run: this->_aladdin->Running(); break;
	case Global::Climb: this->_aladdin->Climb(); break;


	case Global::StopJump: this->_aladdin->StopJump(); break;
	case Global::Stand_shoot: this->_aladdin->Stand_shoot(); break;
	case Global::Run_shoot: this->_aladdin->Run_shoot(); break;
	case Global::Jump: this->_aladdin->Jump(); break;
	case Global::Jump_shoot: this->_aladdin->Jump_shoot(); break;
	case Global::In_climb: this->_aladdin->In_climb(); break;
	case Global::Out_climb: this->_aladdin->Out_climb(); break;
	case Global::In_climb_shoot: this->_aladdin->In_climb_shoot(); break;
	case Global::Out_climb_shoot: this->_aladdin->Out_climb_shoot(); break;
	case Global::Climb_ladder: this->_aladdin->Climb_ladder(); break;
	case Global::Climb_ladder_shoot: this->_aladdin->Climb_ladder_shoot(); break;
	case Global::Dash: this->_aladdin->Dash(); break;
	case Global::Dash_shoot: this->_aladdin->Dash_shoot(); break;
	case Global::Destroyed: this->_aladdin->Destroyed(); break;
	case Global::Hurt: this->_aladdin->Hurt(); break;
	case Global::Defense_hurt: this->_aladdin->Defense_hurt(); break;
	case Global::Weak_sit: this->_aladdin->Weak_sit(); break;

	}
}

