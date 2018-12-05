#include "BossScene.h"
#include "DeadScene.h"
#include"BulletManager.h"
#include "LevelCompleteScene.h"

BossScene::BossScene()
{
	this->_application = Application::Instance();
	this->LoadContent();
}

BossScene::~BossScene()
{
}

void BossScene::Render()
{

	this->_mapboss->Render(MapBoss::MapBoss1);	//Draw Map Level1
    this->_mapboss->Render(MapBoss::MapBoss2);	//Draw Map Level2

	for each (auto obj in this->_listObject)
	{
		if (!obj)
			return;
		switch (obj->getId())
		{
		case Global::GROUND:
		case Global::PLATFORM:
		case Global::TRAP:
		case Global::WALL:break;
		default:
		{
			ActionObject* object = (ActionObject*)obj;
			object->render();
			break;
		}
		}
	}
	BulletManager::Instance()->render();
	this->_aladdin->render();
	this->_listObject.clear();
	this->_display->render(_aladdin->getHp(), _aladdin->getLife(), _aladdin->getNumberOfApple(), _aladdin->getNumberOfGem(), _aladdin->getScore());
}

void BossScene::LoadContent()
{

	this->_aladdin = Aladdin::getInstance();
	this->_aladdin->Init(1400, 8000, 99, 8, 3);

	this->_camera = Camera::Instance();

	float wndWidth = _application->getWidth();
	float wndHeight = _application->getHeight();

	this->_camera->setPosition(_aladdin->getX() - wndWidth / 2, _aladdin->getY() + wndHeight / 2);

	this->_mapboss = new MapBoss();

	this->_mapboss->SetCamera(this->_camera);

	this->_quadtree = QuadTree::Instance();
	this->_quadtree->buildTree("Map\\MapBoss.txt");
	this->_display = DisPlay::Instance();
	this->_camera->update(this->_aladdin);
	this->_sound = Sound::Instance();
	this->_sound->playBackGround(SOUND_BACKGROUND_BOSS, 100, true);
	this->_sound->play(SOUND_JAFAR_LAUGH);
}

void BossScene::Update(float delta)
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
		case Global::JAFAR:
		{
			for each (auto bullet in BulletManager::Instance()->getListBullet())
			{				
				if (!bullet)
					continue;
				if (bullet->getTypeObject() == Global::AladdinParty)
					obj->processCollision(bullet);
				else
					this->_aladdin->processCollision(bullet);
			}
			this->_aladdin->processCollision(obj);
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
		//for each (auto obj in this->_listObject)
		//{
		//	//set lại hành động của enemy
		//	if (obj->getTypeObject() == Global::Enemy)
		//	{
		//		Enemy* enemy = (Enemy*)obj;
		//		enemy->setDead(false);
		//		enemy->takeAction(Global::Stand);
		//	}
		//}
	}
	if (_aladdin->getLife() < 0)
	{
		this->_sound->stop();
		DeadScene* scene = new DeadScene();
		SenceManager::Instance()->ReplaceSence(scene);
		return;
	}
	if (this->_aladdin->isVictory2())
	{
		this->_sound->stop();
		LevelCompleteScene* scene = new LevelCompleteScene();
		SenceManager::Instance()->ReplaceSence(scene);
		return;
	}
}

void BossScene::ProcessInput()
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

	/*if (key->isKeyPress(DIK_UP))
		controller = Global::UpControl;

	if (key->isKeyPress(DIK_DOWN))
		controller = Global::DownControl;*/


	/*if (key->isKeyDown(DIK_S))
		controller = Global::HitControl;*/

	/*if (key->isKeyDown(DIK_A))
	{
		controller = Global::ThrowControl;
	}
*/
	if (key->isKeyDown(DIK_D))
		controller = Global::JumpControl;

	Global::EState nextState = statemanager->getNewState(currentState, controller);
	this->AladdinTakeAction(nextState);
}

void BossScene::OnKeyDown(int keyCode)
{
}

void BossScene::OnKeyUp(int keyCode)
{
}

void BossScene::IsDead()
{
}

void BossScene::AladdinTakeAction(Global::EState currentState)
{
	switch (currentState)
	{
	case Global::Stand: this->_aladdin->Stand(); break;
	case Global::Run: this->_aladdin->Running(); break;
	case Global::Climb: this->_aladdin->Climb(); break;
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

