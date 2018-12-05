#include "PlaySence.h"
#include"BulletManager.h"
#include "LevelCompleteScene.h"
#include "DeadScene.h"

PlaySence::PlaySence()
{
	this->_application = Application::Instance();
	this->_pastLevel1 = false;
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
	this->_aladdin->Init(200, 9000, 10, 8, 3);
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
	this->_sound = Sound::Instance();
	this->_sound->playBackGround(SOUND_BACKGOUND, 100, true);
}

void PlaySence::Update(float delta)
{
	this->_camera->update(this->_aladdin);

	if (!this->_pastLevel1)
	{
		WRect finishRect(9542, 9254, 8, 240);
		if (Collision::Instance()->sweptAABB(_aladdin->getRectBound(), _aladdin->getVx(), _aladdin->getVy(), finishRect, 0, 0).flag)
		{
			this->_sound->stop();
			this->_pastLevel1 = true;
			Aladdin* _aladdin;
			_aladdin = Aladdin::getInstance();
			_aladdin->setVictory1();
			LevelCompleteScene* scene = new LevelCompleteScene();
			SenceManager::Instance()->ReplaceSence(scene);
			return;
		}
	}
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
		case Global::TEAPOTITEM:
		{
			TeaPotItem* tea = (TeaPotItem*)obj;
			if (tea->isReach())
			{
				for each (auto obj in this->_listObject)
					tea->clearEnemy(obj);
				tea->setReach(false);
			}
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
		DeadScene* scene = new DeadScene();
		SenceManager::Instance()->ReplaceSence(scene);
		return;
	}
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
		if (this->_aladdin->IsPushWall() && this->_aladdin->getDirect() == Global::Right)
		{
			this->_aladdin->setDirect(Global::Left);
			this->_aladdin->Running();
			return;
		}
		this->_aladdin->setDirect(Global::Left);
	}

	if (key->isKeyPress(DIK_RIGHT))
	{
		controller = Global::RightControl;
		if (this->_aladdin->IsPushWall() && this->_aladdin->getDirect() == Global::Left)
		{
			this->_aladdin->setDirect(Global::Right);
			this->_aladdin->Running();
			return;
		}
		this->_aladdin->setDirect(Global::Right);
	}

	//if (key->isKeyPress(DIK_UP))
	//	controller = Global::UpControl;

	//if (key->isKeyPress(DIK_DOWN))
	//	controller = Global::DownControl;


	/*if (key->isKeyDown(DIK_S))
		controller = Global::HitControl;
*/
	/*if (key->isKeyDown(DIK_A))
	{
		controller = Global::ThrowControl;
	}*/

	if (key->isKeyDown(DIK_D))
		controller = Global::JumpControl;

	if (KeyBoard::Instance()->isKeyPress(DIK_SPACE))
	{
		this->_aladdin->setCurrentLocation(5200, 9300);
		this->_aladdin->updateBody();
		this->_aladdin->Stand();
		this->_aladdin->refreshTime();
		return;
	}

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
	case Global::Run: this->_aladdin->Running(); break;
	case Global::Climb: this->_aladdin->Climb(); break;
	case Global::Climb_Drop: this->_aladdin->Climb_Drop(); break;
	case Global::Swing: this->_aladdin->Swing();  break;
	case Global::LookUp: this->_aladdin->LookUp(); break;
	case Global::LookDown: this->_aladdin->LookDown(); break;
	case Global::SitDown: this->_aladdin->SitDown(); break;
	case Global::StandUp: this->_aladdin->StandUp(); break;

	case Global::HitStand: this->_aladdin->HitStand(); break;
	case Global::HitStand2: this->_aladdin->HitStand2(); break;
	case Global::HitRun: this->_aladdin->HitRun(); break;
	case Global::HitSitDown: this->_aladdin->HitSitDown(); break;
	case Global::HitJump: this->_aladdin->HitJump(); break;
	case Global::HitClimb: this->_aladdin->HitClimb(); break;
	case Global::HitSwing: this->_aladdin->HitSwing(); break;
	case Global::HitFall: this->_aladdin->HitFall(); break;

	case Global::ThrowStand: this->_aladdin->ThrowStand(); break;
	case Global::ThrowSitDown: this->_aladdin->ThrowSitDown(); break;
	case Global::ThrowJump: this->_aladdin->ThrowJump(); break;
	case Global::ThrowClimb: this->_aladdin->ThrowClimb(); break;
	case Global::ThrowSwing: this->_aladdin->ThrowSwing(); break;
	case Global::ThrowFall: this->_aladdin->ThrowFall(); break;
	case Global::ThrowRun: this->_aladdin->ThrowRun(); break;

	case Global::JumpStand: this->_aladdin->JumpStand(); break;
	case Global::JumpRun: this->_aladdin->JumpRun(); break;
	case Global::JumpClimb: this->_aladdin->JumpClimb(); break;
	case Global::JumpSwing: this->_aladdin->JumpSwing(); break;
	case Global::StopJump: this->_aladdin->StopJump(); break;
	case Global::JumpRotate: this->_aladdin->JumpRotate(); break;
	}
}

