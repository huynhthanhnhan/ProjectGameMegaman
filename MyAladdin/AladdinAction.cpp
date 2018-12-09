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

void AladdinAction::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Aladdin* aladdin = Aladdin::getInstance();
	switch (state)
	{
	/*case Global::Climb:
	{
		position.y -= aladdin->getHeight() / 2;
		Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
		this->UpdateRender(state);
		break;
	}*/
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
	
}

#pragma region LoadResource
void AladdinAction::LoadResource()
{
	this->LoadResourceStand();
	//this->LoadResourceHurt();
	this->LoadResourceRun();
	//this->LoadResourcePushWall();
	this->LoadResourceJump();
	//this->LoadResourceClimb();
	//this->LoadResourceClimb_Drop();
	//this->LoadResourceThrow();
	//this->LoadResourceHit();
	//this->LoadResourceRevival();

	this->LoadResourceAppearance();
	this->LoadResourceStand_shoot();
	this->LoadResourceRun_shoot();
	this->LoadResourceJump_shoot();
	this->LoadResourceIn_climb();
	this->LoadResourceOut_climb();
	this->LoadResourceIn_climb_shoot();
	this->LoadResourceOut_climb_shoot();
	this->LoadResourceClimb_ladder();
	this->LoadResourceClimb_ladder_shoot();
	this->LoadResourceDestroyed();
	this->LoadResourceDefense_hurt();
	this->LoadResourceWeak_sit();
	this->LoadResourceDash();

}

void AladdinAction::LoadResourceStand()
{
	std::vector<Rect*> _listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "Stand");
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listSourceRect);
}

void AladdinAction::LoadResourceHurt()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "hurt");
	this->mListSprite[Global::Hurting] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		listSourceRect);
}

void AladdinAction::LoadResourceRun()
{
	vector<Rect*> run = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "Run");
	this->mListSprite[Global::Run] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(), run);
}

void AladdinAction::LoadResourceJump()
{
	ResourceFile* reader = ResourceFile::Instance();
	this->mListSprite[Global::Jump] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		reader->LoadXML(RESOURCE_RECT_MEGAMAN, "jump"));
}
void AladdinAction::LoadResourceAppearance()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "appearance");
	this->mListSprite[Global::Appearance] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}

void AladdinAction::LoadResourceStand_shoot()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "stand_shoot");
	this->mListSprite[Global::Stand_shoot] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceRun_shoot()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "run_shoot");
	this->mListSprite[Global::Run_shoot] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceJump_shoot()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "jump_shoot");
	this->mListSprite[Global::Jump_shoot] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceIn_climb()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "in_climb");
	this->mListSprite[Global::In_climb] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceOut_climb()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "out_climb");
	this->mListSprite[Global::Out_climb] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceIn_climb_shoot()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "in_climb_shoot");
	this->mListSprite[Global::In_climb_shoot] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceOut_climb_shoot()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "out_climb_shoot");
	this->mListSprite[Global::Out_climb_shoot] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceClimb_ladder()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "climb_ladder");
	this->mListSprite[Global::Climb_ladder] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceClimb_ladder_shoot()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "climb_ladder_shoot");
	this->mListSprite[Global::Climb_ladder_shoot] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceDestroyed()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "destroyed");
	this->mListSprite[Global::Destroyed] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceDefense_hurt()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "defense_hurt");
	this->mListSprite[Global::Defense_hurt] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceWeak_sit()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "weak_sit");
	this->mListSprite[Global::Weak_sit] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceDash()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "dash");
	this->mListSprite[Global::Dash] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
void AladdinAction::LoadResourceDash_shoot()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_MEGAMAN, "dash_shoot");
	this->mListSprite[Global::Dash_shoot] = new SpriteManager(ResourceImage::Instance()->getMegamanSprite(),
		listSourceRect);
}
#pragma endregion

void AladdinAction::UpdateRender(Global::EState state)
{
	switch (state)
	{
	case Global::Stand: this->UpdateRenderStand(state); break;
	case Global::Hurting:this->UpdateRenderHurt(state); break;
	case Global::StopRun:
	case Global::Run:this->UpdateRenderRun(state); break;
	//case Global::PushWall:this->UpdateRenderPushWall(state); break;
	case Global::Fall:
	case Global::Climb:this->UpdateRenderClimb(state); break;
	case Global::Revival: this->UpdateRenderRevival(state); break;
	case Global::Jump: this->UpdateRenderJump(state); break;
	case Global::Dash:this->UpdateRenderDash(state); break;
	case Global::Dash_shoot:this->UpdateRenderDash_shoot(state); break;

	}
}

void AladdinAction::UpdateRenderStand(Global::EState state)
{
	switch (state)
	{
	case Global::Stand:
	{
		if (this->GetCurrentFrame(state) == 6)
		{
			this->SetCurrentFrame(state, this->GetCurrentFrame(state));
		}
		break;
			
	}
	default: break;
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
void AladdinAction::UpdateRenderRun(Global::EState state)
{
	switch (state)
	{
	case Global::Stand:
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

void AladdinAction::UpdateRenderJump(Global::EState state)
{
	Aladdin* aladdin = Aladdin::getInstance();
	bool isGround = aladdin->isGround();

	switch (state)
	{
	case Global::Jump:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
			break;
		}

		//Lặp lại các hành động với số lần time
		if (this->GetCurrentFrame(state) >= 2 && this->GetCurrentFrame(state) <= 5 && this->_time < 1)
		{
			this->_time += 1;
			this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
		}
		else
			this->_time = 0;

		if (aladdin->getVy() > 0 && this->GetCurrentFrame(state) == 3)
			this->SetCurrentFrame(state, 2);

		if (this->GetCurrentFrame(state) == 0 || this->GetCurrentFrame(state) == 6 && !isGround)
			this->SetCurrentFrame(state, 0);

		if (isGround)
		{
			if (abs(aladdin->getVy()) >= 50)
				aladdin->setState(Global::Stand);
			else if (this->GetCurrentFrame(state) < 7)
				this->SetCurrentFrame(state, 0);
		}
		break;
	}
	}
}

void AladdinAction::UpdateRenderClimb(Global::EState state)
{
	//int index = this->GetCurrentFrame(state);
	//int size = this->mListSprite[state]->GetListRect().size();
	//if (this->_direct == Global::Up)
	//	index = (index + 1) % size;
	//else if (this->_direct == Global::Down)
	//{
	//	index--;
	//	if (index < 0)
	//		index = size - 1;
	//}
	//this->SetCurrentFrame(state, index);
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
	case Global::Stand_shoot:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->Stand();
		}
		break;
	}
	case Global::Jump_shoot:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Jump);
			this->SetCurrentFrame(Global::Jump, 4);
		}

		if (aladdin->isGround())
		{
			aladdin->setState(Global::Stand);
		}
		break;
	}
	case Global::In_climb_shoot:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::In_climb);
			this->Refresh();
		}
		break;
	}
	case Global::Out_climb_shoot:
	{
		if (this->GetCurrentFrame(state) == 0)
		{
			aladdin->setState(Global::Out_climb);
			this->Refresh();
		}
		break;
	}
	case Global::Run_shoot:
	{
		if (this->GetCurrentFrame(state) == 0 || !(KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT)))
		{
			aladdin->Stand();
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

void AladdinAction::UpdateRenderAppearance(Global::EState state)
{

}
void AladdinAction::UpdateRenderStand_shoot(Global::EState state)
{

}
void AladdinAction::UpdateRenderRun_shoot(Global::EState state)
{

}
void AladdinAction::UpdateRenderJump_shoot(Global::EState state)
{

}
void AladdinAction::UpdateRenderIn_climb(Global::EState state)
{

}
void AladdinAction::UpdateRenderOut_climb(Global::EState state)
{

}
void AladdinAction::UpdateRenderIn_climb_shoot(Global::EState state)
{

}
void AladdinAction::UpdateRenderOut_climb_shoot(Global::EState state)
{

}
void AladdinAction::UpdateRenderClimb_ladder(Global::EState state)
{

}
void AladdinAction::UpdateRenderClimb_ladder_shoot(Global::EState state)
{

}
void AladdinAction::UpdateRenderDestroyed(Global::EState state)
{

}
void AladdinAction::UpdateRenderDefense_hurt(Global::EState state)
{

}
void AladdinAction::UpdateRenderWeak_sit(Global::EState state)
{

}
void AladdinAction::UpdateRenderDash(Global::EState state)
{
	static bool endDash = false;
	switch (state)
	{
	case Global::Dash:
	{
		if (this->GetCurrentFrame(state) == 0 && endDash  /*&& this->_time < 2*/)
		{
			//this->_time++;
			this->SetCurrentFrame(state, 1);
		}
		else if (this->GetCurrentFrame(state) == 1)
			endDash = true;
		else
			this->_time = 0;

		/*if (this->GetCurrentFrame(state) == 1)
		{
			Aladdin* aladdin = Aladdin::getInstance();
			aladdin->Stand();
		}*/
		break;
	}

	default:
		endDash = false;
		break;
	}
}
void AladdinAction::UpdateRenderDash_shoot(Global::EState state)
{
	switch (state)
	{
	case Global::Dash_shoot:
	{
		if (this->GetCurrentFrame(state) == 1 && this->_time < 2)
		{
			this->_time++;
			this->SetCurrentFrame(state, this->GetCurrentFrame(state) - 1);
		}
		else
			this->_time = 0;

		/*if (this->GetCurrentFrame(state) == 1)
		{
			Aladdin* aladdin = Aladdin::getInstance();
			aladdin->Stand();
		}*/
		break;
	}
	}
}

//Xác định hướng
void AladdinAction::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	switch (state)
	{
	case Global::ThrowClimb:
	case Global::ThrowSwing:
	case Global::HitSwing:
	case Global::HitClimb: this->mListSprite[state]->FlipVertical(direct == Global::Right); break;
	default: this->mListSprite[state]->FlipVertical(direct == Global::Left); break;
	}
}
