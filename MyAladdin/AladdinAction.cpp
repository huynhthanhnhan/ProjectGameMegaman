#include "AladdinAction.h"
#include"Aladdin.h"


AladdinAction::AladdinAction()
{
	this->LoadResource();
}

AladdinAction::~AladdinAction()
{
}

void AladdinAction::setDirect(Global::EDirection direct)
{
	this->_direct = direct;
}

void AladdinAction::setRope(WRect rope)
{
	this->_rope.update(rope.getX(), rope.getY(), rope.getWidth(), rope.getHeight());
}

void AladdinAction::setColumn(WRect column)
{
	this->_column.update(column.getX(), column.getY(), column.getWidth(), column.getHeight());
}

void AladdinAction::setBar(WRect bar)
{
	this->_bar.update(bar.getX(), bar.getY(), bar.getWidth(), bar.getHeight());
}

WRect AladdinAction::getRope()
{
	return this->_rope;
}

WRect AladdinAction::getColumn()
{
	return this->_column;
}

WRect AladdinAction::getBar()
{
	return this->_bar;
}

void AladdinAction::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Aladdin* aladdin = Aladdin::getInstance();
	switch (state)
	{
	case Global::Stand: this->RenderStand(direct, state, position, scale, translation, rotation, rotationCenter); break;
	case Global::ThrowSwing:
	case Global::ThrowClimb:
	case Global::HitSwing:
	case Global::HitClimb:
	case Global::StopSwing:
	case Global::Swing:
	{
		position.y -= aladdin->getHeight();
		Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
		this->UpdateRender(state);
		break;
	}
	case Global::Climb:
	{
		position.y -= aladdin->getHeight() / 2;
		Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
		this->UpdateRender(state);
		break;
	}
	case Global::JumpSwing:
	{
		state = Global::Fall;
	}
	default:
	{
		Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
		this->UpdateRender(state);
	}
	}
}

void AladdinAction::Refresh()
{
	for (auto i = this->mListSprite.begin(); i != this->mListSprite.end(); ++i)
		i->second->SetCurrentFrame(0);
	this->_typeStand = Global::Stand;
}

void AladdinAction::RenderStand(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	switch (_typeStand)
	{
	case Global::Stand:
	{
		if (this->GetCurrentFrame(_typeStand) == 0)
			this->_count++;
		if (_count >= 12)
		{
			this->_maxCount = 2 + rand() % 2;
			this->_count = 0;
			this->_typeStand = Global::Stand;
			this->SetCurrentFrame(_typeStand, 0);
		}
		break;
	}
	//case Global::Stand1:
	//{
	//	if (this->GetCurrentFrame(_typeStand) == 2)
	//		this->_count++;
	//	if (_count >= _maxCount)
	//	{
	//		this->_maxCount = 2 + rand() % 2;
	//		this->_count = 0;
	//		this->_typeStand = Global::Stand2;
	//		this->SetCurrentFrame(_typeStand, 0);
	//	}
	//	break;
	//}
	//case Global::Stand2:
	//{
	//	if (this->GetCurrentFrame(_typeStand) == 5)
	//		this->_count++;
	//	if (_count >= _maxCount)
	//	{
	//		this->_maxCount = 2 + rand() % 2;
	//		this->_count = 0;
	//		this->_typeStand = Global::Stand3;
	//		this->SetCurrentFrame(_typeStand, 0);
	//	}
	//	break;
	//}
	//case Global::Stand3:
	//{
	//	if (this->GetCurrentFrame(_typeStand) == 0)
	//		this->_count++;
	//	if (_count >= _maxCount)
	//	{
	//		this->_maxCount = 2 + rand() % 2;
	//		this->_count = 0;
	//		int selection = rand() % 2;
	//		if (selection == 0)
	//		{
	//			this->SetCurrentFrame(_typeStand, 0);
	//			this->_typeStand = Global::RecoveryStand;
	//		}
	//		else
	//			this->_typeStand = Global::Stand2;
	//	}
	//	break;
	//}
	case Global::RecoveryStand:
	{
		if (this->GetCurrentFrame(_typeStand) == 0)
			this->_count++;
		if (this->_count >= 1)
		{
			this->_typeStand = Global::Stand;
			this->SetCurrentFrame(_typeStand, 0);
		}
	}
	}

	Animation::Render(direct, _typeStand, position, scale, translation, rotation, rotationCenter);
	this->UpdateRender(_typeStand);
}

#pragma region LoadResource
void AladdinAction::LoadResource()
{
	this->LoadResourceStand();
	this->LoadResourceSitDown();
	this->LoadResourceStandUp();
	this->LoadResourceLookUp();
	this->LoadResourceLookDown();
	this->LoadResourceHurt();
	this->LoadResourceSwing();
	this->LoadResourceRun();
	this->LoadResourcePushWall();
	this->LoadResourceJump();
	this->LoadResourceClimb();
	this->LoadResourceClimb_Drop();
	this->LoadResourceThrow();
	this->LoadResourceHit();
	this->LoadResourceRevival();

	this->LoadResourceAppearance();
}

void AladdinAction::LoadResourceStand()
{
	//==========================================================
	//Stand
	//==========================================================
	//vector<Rect*> _listSourceRect;
	std::vector<Rect*> _listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "Stand");
	//_listSourceRect.push_back(new Rect(67, 5, 30+5, 34+67));
	//_listSourceRect.push_back(new Rect(67, 50, 50+20, 34 + 67));
	//_listSourceRect.push_back(new Rect(67, 75, 75+23, 35 + 67));
	//_listSourceRect.push_back(new Rect(67, 105, 105+32, 34 + 68));
	//_listSourceRect.push_back(new Rect(67, 145, 145+34, 33 + 68));
	//_listSourceRect.push_back(new Rect(67, 190, 190+26, 33 + 69));

	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect);
	//==========================================================
	//Stand1
	//==========================================================
	/*this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "Run"));*/
	//==========================================================
	//Stand2
	//==========================================================
	//std::vector<Rect*> _listSourceStand2 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "StandWithApple1");
	//_listSourceStand2[0]->setCenter(19);
	//_listSourceStand2[1]->setCenter(27);
	//_listSourceStand2[2]->setCenter(27);
	//_listSourceStand2[3]->setCenter(12);
	//_listSourceStand2[4]->setCenter(12);
	//_listSourceStand2[5]->setCenter(12);
	//_listSourceStand2[6]->setCenter(12);
	//_listSourceStand2[7]->setCenter(12);
	//_listSourceStand2[8]->setCenter(12);
	//_listSourceStand2[9]->setCenter(12);
	//_listSourceStand2[10]->setCenter(12);
	//_listSourceStand2[11]->setCenter(12);
	//_listSourceStand2[12]->setCenter(12);
	//_listSourceStand2[13]->setCenter(12);
	//_listSourceStand2[14]->setCenter(12);
	//this->mListSprite[Global::Stand2] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
	//	_listSourceStand2);
	////==========================================================
	////Stand3
	////==========================================================
	//std::vector<Rect*> _listSourceStand3 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "StandWithApple2");
	//_listSourceStand3[0]->setCenter(12);
	//_listSourceStand3[1]->setCenter(12);
	//_listSourceStand3[2]->setCenter(12);
	//_listSourceStand3[3]->setCenter(12);
	//_listSourceStand3[4]->setCenter(11);
	//_listSourceStand3[5]->setCenter(11);
	//_listSourceStand3[6]->setCenter(10);
	//_listSourceStand3[7]->setCenter(10);
	//_listSourceStand3[8]->setCenter(10);
	//_listSourceStand3[9]->setCenter(8);
	//_listSourceStand3[10]->setCenter(8);
	//_listSourceStand3[11]->setCenter(8);
	//_listSourceStand3[12]->setCenter(10);
	//_listSourceStand3[13]->setCenter(12);
	//_listSourceStand3[14]->setCenter(12);
	//_listSourceStand3[15]->setCenter(12);
	//_listSourceStand3[16]->setCenter(12);
	//this->mListSprite[Global::Stand3] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
	//	_listSourceStand3);
	//==========================================================
	//RecoveryStand
	//==========================================================
	std::vector<Rect*> _listSourceRecovery = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "Stand");
	//_listSourceRecovery[0]->setCenter(12);
	//_listSourceRecovery[1]->setCenter(12);
	//_listSourceRecovery[2]->setCenter(27);
	//_listSourceRecovery[3]->setCenter(27);
	//_listSourceRecovery[4]->setCenter(19);
	this->mListSprite[Global::RecoveryStand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRecovery);
}

void AladdinAction::LoadResourceSitDown()
{
	vector<Rect*> _listSourceRect;
	//float top = 498, bottom = 550;
	//_listSourceRect.push_back(new Rect(top, 204, 257, bottom));
	//_listSourceRect.push_back(new Rect(top, 257, 314, bottom));
	//_listSourceRect.push_back(new Rect(top, 314, 373, bottom));
	//_listSourceRect.push_back(new Rect(top, 376, 434, bottom));
	_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "SitDown");
	_listSourceRect[0]->setCenter(26, 48);
	_listSourceRect[1]->setCenter(29, 39);
	_listSourceRect[2]->setCenter(32, 29);
	_listSourceRect[3]->setCenter(27, 34);
	this->mListSprite[Global::SitDown] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect);
}

void AladdinAction::LoadResourceStandUp()
{
	vector<Rect*> _listSourceRect;
	float top = 498, bottom = 550;
	_listSourceRect.push_back(new Rect(top, 376, 434, bottom));
	_listSourceRect.push_back(new Rect(top, 314, 373, bottom));
	_listSourceRect.push_back(new Rect(top, 257, 314, bottom));
	_listSourceRect.push_back(new Rect(top, 204, 257, bottom));
	this->mListSprite[Global::StandUp] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect);
}

void AladdinAction::LoadResourceLookUp()
{
	vector<Rect*> _listSourceRect;
	_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "LookUp");
	_listSourceRect[0]->setCenter(18);
	_listSourceRect[1]->setCenter(22);
	_listSourceRect[2]->setCenter(26);
	this->mListSprite[Global::LookUp] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect);
}

void AladdinAction::LoadResourceLookDown()
{
	vector<Rect*> _listSourceRect;
	_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "LookDown");
	_listSourceRect[0]->setCenter(26);
	_listSourceRect[1]->setCenter(22);
	_listSourceRect[2]->setCenter(18);
	this->mListSprite[Global::LookDown] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect);
}

void AladdinAction::LoadResourceHurt()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "hurt");
	this->mListSprite[Global::Hurting] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		listSourceRect);
}

void AladdinAction::LoadResourceAppearance()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "appearance");
	this->mListSprite[Global::Appearance] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}

void AladdinAction::LoadResourceSwing()
{
	std::vector<Rect*>	_listSourceSwing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "Swing");

	_listSourceSwing[0]->setCenter(17, 3);
	_listSourceSwing[1]->setCenter(27, 3);
	_listSourceSwing[2]->setCenter(24, 3);
	_listSourceSwing[3]->setCenter(16, 3);
	_listSourceSwing[4]->setCenter(10, 3);
	_listSourceSwing[5]->setCenter(19, 4);
	_listSourceSwing[6]->setCenter(23, 3);
	_listSourceSwing[7]->setCenter(29, 3);
	_listSourceSwing[8]->setCenter(15, 3);
	_listSourceSwing[9]->setCenter(9, 3);

	this->mListSprite[Global::Swing] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceSwing);

	std::vector<Rect*> _listSourceStop = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "StopSwing");
	_listSourceStop[0]->setCenter(12, 3);
	_listSourceStop[1]->setCenter(12, 3);

	_listSourceStop[2]->setCenter(15, 3);
	_listSourceStop[3]->setCenter(15, 3);

	_listSourceStop[4]->setCenter(18, 3);
	_listSourceStop[5]->setCenter(21, 3);

	_listSourceStop[6]->setCenter(22, 3);
	_listSourceStop[7]->setCenter(21, 3);
	_listSourceStop[8]->setCenter(21, 3);
	_listSourceStop[9]->setCenter(18, 3);
	_listSourceStop[10]->setCenter(15, 3);

	this->mListSprite[Global::StopSwing] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceStop);
}

void AladdinAction::LoadResourceRun()
{
	vector<Rect*> run = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "Run");
	//run[12]->setCenter(-1, 53);
	this->mListSprite[Global::Run] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(), run);
		
		
	
	//======================================================
	//StopRun
	//======================================================
	vector<Rect*> source;
	source = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "Stand");

	/*source[0]->setCenter(17, 53);
	source[1]->setCenter(14, 52);
	source[2]->setCenter(30, 61);
	source[3]->setCenter(25, 62);
	source[4]->setCenter(19, 59);
	source[5]->setCenter(18, 38);
	source[6]->setCenter(17, 35);
	source[7]->setCenter(18, 44);
	source[8]->setCenter(18, 49);*/

	this->mListSprite[Global::StopRun] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		source);
}

void AladdinAction::LoadResourcePushWall()
{
	Aladdin* aladdin = Aladdin::getInstance();
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "PushWall");
	listSourceRect[0]->setCenter(listSourceRect[0]->getWidth() - 10, 46);
	for each (auto rect in listSourceRect)
	{
		rect->setCenter(rect->getWidth() - aladdin->getRectBound().getWidth() / 3, 45);
	}
	this->mListSprite[Global::PushWall] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		listSourceRect);
}

void AladdinAction::LoadResourceJump()
{
	ResourceFile* reader = ResourceFile::Instance();
	//====================================================================
	//Running and jump
	//====================================================================
	this->mListSprite[Global::JumpRun] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		reader->LoadXML(RESOURCE_RECT_MEGAMAN, "jump"));
	//====================================================================
	//Standing and jump
	//====================================================================
	this->mListSprite[Global::JumpStand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		reader->LoadXML(RESOURCE_RECT_MEGAMAN, "jump"));
	//====================================================================
	//Climbing and jump
	//====================================================================
	this->mListSprite[Global::JumpClimb] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		reader->LoadXML(RESOURCE_RECT_MEGAMAN, "jump"));
	//====================================================================
	//Fall
	//====================================================================
	this->mListSprite[Global::Fall] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		reader->LoadXML(RESOURCE_RECT_MEGAMAN, "Stand"));
	//====================================================================
	//Stop Jump
	//====================================================================
	std::vector<Rect*> _listResource = reader->LoadXML(RESOURCE_RECT_MEGAMAN, "Stand");
	this->mListSprite[Global::StopJump] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listResource);
	//====================================================================
	//Jump and rotate
	//====================================================================
	std::vector<Rect*>	listSourceRectJumpRotate = reader->LoadXML(RESOURCE_RECT_MEGAMAN, "jump");
	this->mListSprite[Global::JumpRotate] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		listSourceRectJumpRotate);
}

void AladdinAction::LoadResourceClimb()
{
	vector<Rect*> _listSourceRect;
	_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "in_climb");

	this->mListSprite[Global::Climb] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect,
		false);
}

void AladdinAction::LoadResourceClimb_Drop()
{
	vector<Rect*> _listSourceRect;
	_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "Climb_Drop");

	_listSourceRect[0]->setCenter(16, 47);

	this->mListSprite[Global::Climb_Drop] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect,
		false);
}

void AladdinAction::LoadResourceThrow()
{
	//============================================================================================
	//Aladdin Standing and Throw Apple
	//============================================================================================
	vector<Rect*>	_listSourceRectStand;
	_listSourceRectStand = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowStand");

	this->mListSprite[Global::ThrowStand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectStand);
	//============================================================================================
	//Aladdin Sitdown and throw apple
	//============================================================================================
	vector<Rect*>	_listSourceRectSitDown;
	_listSourceRectSitDown = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowSitDown");
	_listSourceRectSitDown[0]->setCenter(24, 44);
	_listSourceRectSitDown[1]->setCenter(24, 47);
	_listSourceRectSitDown[2]->setCenter(23, 44);
	_listSourceRectSitDown[3]->setCenter(34, 37);
	_listSourceRectSitDown[4]->setCenter(30, 37);

	this->mListSprite[Global::ThrowSitDown] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectSitDown);
	//============================================================================================
	//Aladdin Jump and throw apple
	//============================================================================================
	vector<Rect*>	_listSourceRectJump;
	_listSourceRectJump = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowJump");

	this->mListSprite[Global::ThrowJump] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectJump);
	//============================================================================================
	//Aladdin Climb and throw apple
	//============================================================================================
	vector<Rect*> _listSourceRectClimb;
	_listSourceRectClimb = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowClimb");

	_listSourceRectClimb[0]->setCenter(11, 3);
	_listSourceRectClimb[1]->setCenter(11, 3);
	_listSourceRectClimb[2]->setCenter(10, 3);
	_listSourceRectClimb[3]->setCenter(10, 3);
	_listSourceRectClimb[4]->setCenter(31, 3);

	this->mListSprite[Global::ThrowClimb] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectClimb);
	//============================================================================================
	//Aladdin Swing and throw apple
	//============================================================================================
	vector<Rect*> _listSourceRectSwing;
	_listSourceRectSwing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowClimb");

	_listSourceRectSwing[0]->setCenter(11, 3);
	_listSourceRectSwing[1]->setCenter(11, 3);
	_listSourceRectSwing[2]->setCenter(10, 3);
	_listSourceRectSwing[3]->setCenter(10, 3);
	_listSourceRectSwing[4]->setCenter(31, 3);

	this->mListSprite[Global::ThrowSwing] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectSwing);
	//============================================================================================
	//Aladdin Jump and throw apple
	//============================================================================================
	vector<Rect*>	_listSourceRectFall;
	_listSourceRectFall = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowJump");

	this->mListSprite[Global::ThrowFall] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectFall);
	//============================================================================================
	//Aladdin running and throw apple
	//============================================================================================
	vector<Rect*> _listSourceRectRun;
	_listSourceRectRun = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "ThrowRun");
	this->mListSprite[Global::ThrowRun] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture3(),
		_listSourceRectRun);
}

void AladdinAction::LoadResourceHit()
{
	ResourceFile* reader = ResourceFile::Instance();
	//====================================================================================
	//Standing and Hit
	//====================================================================================
	vector<Rect*>	_listRectSourceStand;

	_listRectSourceStand = reader->LoadXML(RESOURCE_RECT_MEGAMAN, "stand_shoot");
	this->mListSprite[Global::HitStand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listRectSourceStand);
	//====================================================================================
	//LookUp and Hit
	//====================================================================================
	vector<Rect*>	_listRectSourceStand2;
	_listRectSourceStand2 = reader->LoadXML(RESOURCE_RECT_MEGAMAN, "stand_shoot");
	//_listRectSourceStand2[0]->setCenter(17);
	//_listRectSourceStand2[1]->setCenter(17);
	//_listRectSourceStand2[2]->setCenter(46);
	//_listRectSourceStand2[3]->setCenter(25);
	//_listRectSourceStand2[4]->setCenter(25);
	//_listRectSourceStand2[5]->setCenter(33);
	//_listRectSourceStand2[6]->setCenter(17);
	//_listRectSourceStand2[7]->setCenter(17);
	//_listRectSourceStand2[8]->setCenter(17);
	//_listRectSourceStand2[9]->setCenter(17);
	//_listRectSourceStand2[10]->setCenter(46);
	//_listRectSourceStand2[11]->setCenter(25);
	//_listRectSourceStand2[12]->setCenter(25);
	//_listRectSourceStand2[13]->setCenter(33);
	//_listRectSourceStand2[14]->setCenter(17);
	//_listRectSourceStand2[15]->setCenter(17);
	//_listRectSourceStand2[16]->setCenter(17);
	//_listRectSourceStand2[17]->setCenter(17);
	//_listRectSourceStand2[18]->setCenter(46);
	//_listRectSourceStand2[19]->setCenter(25);
	//_listRectSourceStand2[20]->setCenter(25);
	//_listRectSourceStand2[21]->setCenter(28);
	//_listRectSourceStand2[22]->setCenter(22);
	this->mListSprite[Global::HitStand2] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listRectSourceStand2);

	//====================================================================================
	//Running and Hit
	//====================================================================================

	vector<Rect*>	_listSourceRectRun;
	_listSourceRectRun = reader->LoadXML(RESOURCE_RECT_MEGAMAN, "run_shoot");
	this->mListSprite[Global::HitRun] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture2(),
		_listSourceRectRun);
	//====================================================================================
	//SitDown and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectSitDown;
	_listSourceRectSitDown = reader->LoadXML(RESOURCE_RECT_ALADDIN, "HitSitDown");
	_listSourceRectSitDown[0]->setCenter(24, 32);
	_listSourceRectSitDown[1]->setCenter(24, 30);
	_listSourceRectSitDown[2]->setCenter(24, 32);
	_listSourceRectSitDown[3]->setCenter(25, 33);
	_listSourceRectSitDown[4]->setCenter(24, 32);
	_listSourceRectSitDown[5]->setCenter(24, 32);
	_listSourceRectSitDown[6]->setCenter(24, 30);
	this->mListSprite[Global::HitSitDown] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectSitDown);

	//====================================================================================
	//Jump and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectJump;
	_listSourceRectJump = reader->LoadXML(RESOURCE_RECT_MEGAMAN, "jump_shoot");

	this->mListSprite[Global::HitJump] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectJump);
	//====================================================================================
	//Climb and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectClimb;
	_listSourceRectClimb = reader->LoadXML(RESOURCE_RECT_MEGAMAN, "in_climb_shoot");

	this->mListSprite[Global::HitClimb] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectClimb);
	//====================================================================================
	//Climb and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectSwing;
	_listSourceRectSwing = reader->LoadXML(RESOURCE_RECT_ALADDIN, "HitSwing");
	_listSourceRectSwing[0]->setCenter(9, 3);
	_listSourceRectSwing[1]->setCenter(10, 3);
	_listSourceRectSwing[2]->setCenter(45, 15);
	_listSourceRectSwing[3]->setCenter(41, 3);
	_listSourceRectSwing[4]->setCenter(16, 3);
	_listSourceRectSwing[5]->setCenter(37, 3);
	_listSourceRectSwing[6]->setCenter(9, 3);
	this->mListSprite[Global::HitSwing] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectSwing);
	//====================================================================================
	//Fall and Hit
	//====================================================================================
	vector<Rect*>	_listSourceRectFall;
	_listSourceRectFall = reader->LoadXML(RESOURCE_RECT_ALADDIN, "HitJump");

	_listSourceRectFall[0]->setCenter(24);
	_listSourceRectFall[1]->setCenter(23);
	_listSourceRectFall[2]->setCenter(21);
	_listSourceRectFall[3]->setCenter(24);
	_listSourceRectFall[4]->setCenter(22);
	_listSourceRectFall[5]->setCenter(24);

	this->mListSprite[Global::HitFall] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRectFall);
}
void AladdinAction::LoadResourceRevival()
{
	std::vector<Rect*> resource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "aladdinRevival");
	resource[0]->setCenter(28);
	resource[1]->setCenter(26);
	resource[2]->setCenter(9);
	resource[3]->setCenter(9);
	resource[4]->setCenter(9);
	resource[5]->setCenter(14);
	resource[6]->setCenter(19);
	resource[7]->setCenter(15);
	resource[8]->setCenter(21);
	resource[9]->setCenter(15);
	resource[10]->setCenter(26);
	resource[11]->setCenter(39);
	resource[12]->setCenter(33);
	resource[13]->setCenter(29);
	this->mListSprite[Global::Revival] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		resource, false);
}

#pragma endregion

void AladdinAction::UpdateRender(Global::EState state)
{
	switch (state)
	{
	case Global::Stand1:
	case Global::Stand2:
	case Global::Stand3:
	case Global::Stand: this->UpdateRenderStand(state); break;
	case Global::SitDown: this->UpdateRenderSitDown(state); break;
	case Global::StandUp: this->UpdateRenderStandUp(state); break;
	case Global::LookUp:this->UpdateRenderLookUp(state); break;
	case Global::LookDown:this->UpdateRenderLookDown(state); break;
	case Global::Hurting:this->UpdateRenderHurt(state); break;
	case Global::StopSwing:
	case Global::Swing:this->UpdateRenderSwing(state); break;
	case Global::StopRun:
	case Global::Run://this->UpdateRenderRun(state); break;
	case Global::PushWall:this->UpdateRenderPushWall(state); break;
	case Global::JumpStand:
	case Global::JumpRun:
	case Global::JumpClimb:
	case Global::Fall:
	case Global::JumpRotate:
	case Global::StopJump: this->UpdateRenderJump(state); break;
	case Global::Climb:this->UpdateRenderClimb(state); break;
	case Global::ThrowFall:
	case Global::ThrowStand:
	case Global::ThrowSitDown:
	case Global::ThrowJump:
	case Global::ThrowClimb:
	case Global::ThrowSwing:
	case Global::ThrowRun: this->UpdateRenderThrow(state); break;
	case Global::HitFall:
	case Global::HitStand:
	case Global::HitStand2:
	case Global::HitRun:
	case Global::HitSitDown:
	case Global::HitJump:
	case Global::HitClimb:
	case Global::HitSwing: this->UpdateRenderHit(state); break;
	case Global::Revival: this->UpdateRenderRevival(state); break;
	}
}

void AladdinAction::UpdateRenderStand(Global::EState state)
{
	switch (state)
	{
	//case Global::Stand: break;
	case Global::Stand:
	{
		if (this->GetCurrentFrame(state) == 6)
		{
			this->SetCurrentFrame(state, this->GetCurrentFrame(state));
		}
		break;
			
	}
	//case Global::Stand2:
	//{
	//	if (this->GetCurrentFrame(state) == 5 && this->_time <= 7)
	//	{
	//		this->_time += 1;
	//		this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
	//	}
	//	else
	//		this->_time = 0;

	//	if (this->mListSprite[state]->GetCurrentFrame() == 0)
	//		this->mListSprite[state]->SetCurrentFrame(4);
	//	break;
	//}
	//case Global::Stand3:
	//{
	//	if (this->GetCurrentFrame(state) == 0 && this->_time <= 7)
	//	{
	//		this->_time += 1;
	//		this->SetCurrentFrame(state, 16);
	//	}
	//	else
	//		this->_time = 0;
	//	break;
	//}
	default: break;
	}
}

void AladdinAction::UpdateRenderSitDown(Global::EState state)
{
	if (this->GetCurrentFrame(state) == 0)
		this->SetCurrentFrame(state, 3);
}

void AladdinAction::UpdateRenderStandUp(Global::EState state)
{
	if (this->GetCurrentFrame(state) == 0)
	{
		Aladdin* aladdin = Aladdin::getInstance();
		aladdin->Stand();
	}
}

void AladdinAction::UpdateRenderLookUp(Global::EState state)
{
	if (this->GetCurrentFrame(state) == 0)
		this->SetCurrentFrame(state, 2);
}

void AladdinAction::UpdateRenderLookDown(Global::EState state)
{
	if (this->GetCurrentFrame(state) == 0)
	{
		Aladdin* aladdin = Aladdin::getInstance();
		aladdin->Stand();
	}
}

void AladdinAction::UpdateRenderHurt(Global::EState state)
{

	if (this->GetCurrentFrame(state) == 0)
	{
		Aladdin* aladdin = Aladdin::getInstance();
		aladdin->Stand();
	}
}

void AladdinAction::UpdateRenderSwing(Global::EState state)
{
	switch (state)
	{
	case Global::Swing: break;
	case Global::StopSwing:
	{
		if ((this->GetCurrentFrame(state) == 1 || this->GetCurrentFrame(state) == 2 || this->GetCurrentFrame(state) == 7) && this->_time <= 9)
		{
			this->_time++;
			this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
		}
		else
			this->_time = 0;

		if (this->GetCurrentFrame(state) == 0)
			this->SetCurrentFrame(state, 1);
		break;
	}
	}
}

void AladdinAction::UpdateRenderRun(Global::EState state)
{
	switch (state)
	{
	case Global::StopRun:
	{
		if (this->GetCurrentFrame(state) == 3 && this->_time< 1)
		{
			this->_time++;
			this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
		}
		else
			this->_time = 0;

		if (this->GetCurrentFrame(state) == 0)
		{
			Aladdin* aladdin = Aladdin::getInstance();
			aladdin->Stand();
		}
		break;
	}
	case Global::Run:
	{
		if (this->GetCurrentFrame(state) == 0)
			this->SetCurrentFrame(state, 2);
		break;
	}
	}
}

void AladdinAction::UpdateRenderPushWall(Global::EState state)
{
	if (this->GetCurrentFrame(state) == 6)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_ALADDIN_PUSH);
	}
	if (this->GetCurrentFrame(state) > 1 && this->_time < 1)
	{
		this->_time++;
		this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
	}
	else
		this->_time = 0;

	if (this->mListSprite[state]->GetCurrentFrame() == 0)
		this->mListSprite[state]->SetCurrentFrame(2);
}

void AladdinAction::UpdateRenderJump(Global::EState state)
{
	Aladdin* aladdin = Aladdin::getInstance();
	bool isGround = aladdin->isGround();

	switch (state)
	{
	case Global::JumpStand:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
			break;
		}

		//Lặp lại các hành động với số lần time
		if (this->GetCurrentFrame(state) >= 2 && this->GetCurrentFrame(state) <= 4 && this->_time < 1)
		{
			this->_time += 1;
			this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
		}
		else
			this->_time = 0;

		if (aladdin->getVy() > 0 && this->GetCurrentFrame(state) == 3)
			this->SetCurrentFrame(state, 2);

		if (this->GetCurrentFrame(state) == 0 || this->GetCurrentFrame(state) == 10 && !isGround)
			this->SetCurrentFrame(state, 7);

		if (isGround)
		{
			if (abs(aladdin->getVy()) >= 50)
				aladdin->setState(Global::StopJump);
			else if (this->GetCurrentFrame(state) < 10)
				this->SetCurrentFrame(state, 10);
		}
		break;
	}
	case Global::JumpRun:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
			break;
		}

		//Lặp lại các hành động với số lần time
		if (this->GetCurrentFrame(state) >= 3 && this->GetCurrentFrame(state) <= 6 && this->_time < 2)
		{
			this->_time += 1;
			this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
		}
		else
			this->_time = 0;

		if (this->GetCurrentFrame(state) == 7 && !isGround)
			this->SetCurrentFrame(state, 6);


		if (isGround)
		{
			if (abs(aladdin->getVy()) >= 50)
				aladdin->setState(Global::StopJump);
			else if (this->GetCurrentFrame(state) < 7)
				this->SetCurrentFrame(state, 7);
		}
		else
		{
			if (this->GetCurrentFrame(state) == 6 && abs(aladdin->getVy()) >= 70)
			{
				aladdin->Fall();
			}
		}

		break;
	}
	case Global::JumpClimb:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::JumpStand);
			this->SetCurrentFrame(Global::JumpStand, 3);
			break;
		}

		if (aladdin->getVy() > 0 && this->GetCurrentFrame(state) == 3)
			this->SetCurrentFrame(state, 2);
		else
		{
			//Lặp lại các hành động với số lần time
			if (this->GetCurrentFrame(state) >= 3 && this->GetCurrentFrame(state) <= 7 && this->_time < 1)
			{
				this->_time += 1;
				this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
			}
			else
				this->_time = 0;
		}
		break;
	}
	case Global::Fall:
	{
		if (aladdin->isGround())
		{
			aladdin->setState(Global::StopJump);
			this->Refresh();
			break;
		}

		if (this->GetCurrentFrame(state) >= 2 && this->GetCurrentFrame(state) <= 4 && this->_time < 1)
		{
			this->_time += 1;
			this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
		}
		else
			this->_time = 0;

		if (this->GetCurrentFrame(state) == 0 && !isGround)
			this->SetCurrentFrame(state, 5);
		break;
	}
	case Global::JumpRotate:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			if (this->GetCurrentFrame(state) == 0)
			aladdin->Fall();
		}
		break;
	}
	case Global::StopJump:
	{
		if (this->GetCurrentFrame(state) == 3)
		{
			this->_sound = Sound::Instance();
			this->_sound->play(SOUND_ALADDIN_OOF);
		}
		if (this->GetCurrentFrame(state) == 0)
			aladdin->Stand();
		break;
	}
	}
}

void AladdinAction::UpdateRenderClimb(Global::EState state)
{
	int index = this->GetCurrentFrame(state);
	int size = this->mListSprite[state]->GetListRect().size();
	if (this->_direct == Global::Up)
		index = (index + 1) % size;
	else if (this->_direct == Global::Down)
	{
		index--;
		if (index < 0)
			index = size - 1;
	}
	this->SetCurrentFrame(state, index);
}

void AladdinAction::UpdateRenderThrow(Global::EState state)
{
	if (this->GetCurrentFrame(state) == 4)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_OBJECT_THROW);
	}
	Aladdin* aladdin = Aladdin::getInstance();
	switch (state)
	{
	case Global::ThrowStand:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
		}
		break;
	}
	case Global::ThrowSitDown:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			if (KeyBoard::Instance()->isKeyPress(DIK_DOWN))
			{
				if (KeyBoard::Instance()->isKeyPress(DIK_DOWN))
				{
					aladdin->setState(Global::SitDown);
					this->SetCurrentFrame(Global::SitDown, 2);
				}
				else
					aladdin->Stand();
			}
			else
			{
				aladdin->Stand();
			}
		}
		break;
	}
	case Global::ThrowFall:
	case Global::ThrowJump:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::JumpRun);
			this->SetCurrentFrame(Global::JumpRun, 4);
		}

		if (aladdin->isGround())
		{
			aladdin->setState(Global::Stand);
		}
		break;
	}
	case Global::ThrowClimb:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Climb);
			this->Refresh();
		}
		break;
	}
	case Global::ThrowSwing:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Swing);
			this->Refresh();
		}
		break;
	}
	case Global::ThrowRun:
	{
		if (this->GetCurrentFrame(state) == 0 || !(KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT)))
		{
			aladdin->Stand();
		}
		break;
	}
	}
}

void AladdinAction::UpdateRenderHit(Global::EState state)
{
	Aladdin* aladdin = Aladdin::getInstance();
	switch (state)
	{
	case Global::HitStand:
	{
		if (this->GetCurrentFrame(state) == 3)
		{
			this->_sound = Sound::Instance();
			this->_sound->play(SOUND_HIGH_SWORD);
		}
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
		}
		break;
	}
	case Global::HitStand2:
	{
		if (this->GetCurrentFrame(state) == 3 || this->GetCurrentFrame(state) == 7 || this->GetCurrentFrame(state) == 11 || this->GetCurrentFrame(state) == 15 || this->GetCurrentFrame(state) == 19)
		{
			this->_sound = Sound::Instance();
			this->_sound->play(SOUND_HIGH_SWORD);
		}
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
		}
		break;
	}
	case Global::HitRun:
	{
		if (this->GetCurrentFrame(state) == 5)
		{
			this->_sound = Sound::Instance();
			this->_sound->play(SOUND_HIGH_SWORD);
		}
		if (this->GetCurrentFrame(state) == 0 || !(KeyBoard::Instance()->isKeyPress(DIK_LEFT)|| KeyBoard::Instance()->isKeyPress(DIK_RIGHT)))
		{
			aladdin->Stand();
		}
		if (this->GetCurrentFrame(state) == 0 && (KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT)))
		{
			aladdin->Running();
		}
		break;
	}
	case Global::HitSitDown:
	{
		if (this->GetCurrentFrame(state) == 4)
		{
			this->_sound = Sound::Instance();
			this->_sound->play(SOUND_LOW_SWORD);
		}
		if (this->GetCurrentFrame(state) == 0)
		{
			if (KeyBoard::Instance()->isKeyPress(DIK_DOWN))
			{
				aladdin->setState(Global::SitDown);
				this->SetCurrentFrame(Global::SitDown, 2);
			}
			else
				aladdin->Stand();
		}
		break;
	}
	case Global::HitFall:
	case Global::HitJump:
	{
		if (this->GetCurrentFrame(state) == 5)
		{
			this->_sound = Sound::Instance();
			this->_sound->play(SOUND_HIGH_SWORD);
		}
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::JumpRun);
			this->SetCurrentFrame(Global::JumpRun, 4);
		}

		if (aladdin->isGround())
		{
			aladdin->Stand();
		}
		break;
	}
	case Global::HitClimb:
	{
		if (this->GetCurrentFrame(state) == 3 || this->GetCurrentFrame(state) == 6)
		{
			this->_sound = Sound::Instance();
			this->_sound->play(SOUND_LOW_SWORD);
		}
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Climb);
			this->Refresh();
		}
		break;
	}
	case Global::HitSwing:
	{
		if (this->GetCurrentFrame(state) == 3 || this->GetCurrentFrame(state) == 6)
		{
			this->_sound = Sound::Instance();
			this->_sound->play(SOUND_LOW_SWORD);
		}
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Swing);
			this->Refresh();
		}
		break;
	}
	}
}

void AladdinAction::UpdateRenderRevival(Global::EState state)
{
	if (this->GetCurrentFrame(state) == 1)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_ALADDIN_COMING);
	}
	if (this->GetCurrentFrame(state) == 7)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_ALADDIN_CONTINUE_POINT);
	}
	if (this->GetCurrentFrame(state) == 14)
		Aladdin::getInstance()->Stand();

	if (this->_time >= 1)
	{
		int index = (this->GetCurrentFrame(state) + 1) % this->mListSprite[state]->GetListRect().size();
		_time = 0;
		this->SetCurrentFrame(state, index);
	}
	else
		_time++;
}

//Xác định hướng
void AladdinAction::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	switch (state)
	{
	case Global::StopSwing:
	case Global::ThrowClimb:
	case Global::ThrowSwing:
	case Global::Swing:
	case Global::HitSwing:
	case Global::HitClimb: this->mListSprite[state]->FlipVertical(direct == Global::Right); break;
	default: this->mListSprite[state]->FlipVertical(direct == Global::Left); break;
	}
}
