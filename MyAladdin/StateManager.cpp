#include "StateManager.h"

StateManager*		StateManager::__instance = nullptr;

StateManager * StateManager::Instance()
{
	if (!__instance)
		__instance = new StateManager();
	return __instance;
}

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

Global::EState StateManager::getNewState(Global::EState oldState, Global::EControl controller)
{
	Global::EState newState = oldState;

	switch (oldState)
	{
	case Global::Run:
	{
		newState = this->getRun(controller);
		break;
	}
	case Global::Stand:
	{
		newState = this->getStand(controller);
		break;
	}
	case Global::Climb:
	{
		newState = this->getClimb(controller);
		break;
	}
	//case Global::Fall:
	//{
	//	newState = this->getFalling(controller);
	//	break;
	//}
	case Global::Appearance:
	{
		newState = this->getAppearance(controller);
		break;
	}
	case Global::Stand_shoot:
	{
		newState = this->getStand_shoot(controller);
		break;
	}
	case Global::Run_shoot:
	{
		newState = this->getRun_shoot(controller);
		break;
	}
	case Global::Jump_shoot:
	{
		newState = this->getJump_shoot(controller);
		break;
	}
	case Global::In_climb:
	{
		newState = this->getIn_climb(controller);
		break;
	}
	case Global::Out_climb:
	{
		newState = this->getOut_climb(controller);
		break;
	}
	case Global::In_climb_shoot:
	{
		newState = this->getIn_climb_shoot(controller);
		break;
	}
	case Global::Out_climb_shoot:
	{
		newState = this->getOut_climb_shoot(controller);
		break;
	}
	case Global::Climb_ladder:
	{
		newState = this->getClimb_ladder(controller);
		break;
	}
	case Global::Climb_ladder_shoot:
	{
		newState = this->getClimb_ladder_shoot(controller);
		break;
	}
	case Global::Destroyed:
	{
		newState = this->getDestroyed(controller);
		break;
	}
	case Global::Defense_hurt:
	{
		newState = this->getDefense_hurt(controller);
		break;
	}
	case Global::Weak_sit:
	{
		newState = this->getWeak_sit(controller);
		break;
	}
	case Global::Dash:
	{
		newState = this->getDash(controller);
		break;
	}
	case Global::Dash_shoot:
	{
		newState = this->getDash_shoot(controller);
		break;
	}
	case Global::Jump:
	{
		newState = this->getJump(controller);
		break;
	}
	//case Global::PushWall:
	//{
	//	newState = this->getPushWall(controller);
	//	break;
	//}
	default: newState = oldState; break;
	}
	return newState;
}
//==============================================================
//state trigger
//==============================================================
#pragma region StateTrigger
Global::EState StateManager::getRun(Global::EControl controller)
{
	Global::EState newState = Global::Run;

	switch (controller)
	{
	case Global::NoneControl: newState = Global::Stand; break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: newState = Global::Run_shoot; break;
	case Global::HitControl: newState = Global::Dash; break;
	case Global::JumpControl: newState = Global::Jump; break;
	}
	return newState;
}

Global::EState StateManager::getStand(Global::EControl controller)
{
	Global::EState newState = Global::Stand;

	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: newState = Global::Run; break;
	case Global::RightControl: newState = Global::Run; break;
	case Global::ThrowControl: newState = Global::Stand_shoot; break;
	case Global::HitControl: newState = Global::Dash; break;
	case Global::JumpControl: newState = Global::Jump; break;
	}
	return newState;
}

Global::EState StateManager::getJump(Global::EControl controller)
{
	Global::EState newState = Global::Jump;

	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::ThrowControl: newState = Global::Jump_shoot; break;
	case Global::HitControl: break;
	case Global::JumpControl: break;
	}
	return newState;
}
//
Global::EState StateManager::getClimb(Global::EControl controller)
{
	Global::EState newState = Global::Climb;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl:	break;
	case Global::ThrowControl: break;
	case Global::HitControl: break;
	case Global::JumpControl: break;
	}
	return newState;
}
//
//Global::EState StateManager::getReadyStopRun(Global::EControl controller)
//{
//	Global::EState newState = Global::StopRun;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: newState = Global::Run; break;
//	case Global::RightControl: newState = Global::Run; break;
//	case Global::ThrowControl: newState = Global::ThrowStand; break;
//	case Global::HitControl: newState = Global::HitStand; break;
//	case Global::JumpControl: newState = Global::JumpStand; break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getJumpStand(Global::EControl controller)
//{
//	Global::EState newState = Global::JumpStand;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: newState = Global::Jump_shoot; break;
//	case Global::HitControl: newState = Global::Jump_shoot; break;
//	case Global::JumpControl:break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getJumpRun(Global::EControl controller)
//{
//	Global::EState newState = Global::JumpRun;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: newState = Global::ThrowJump; break;
//	case Global::HitControl: newState = Global::HitJump; break;
//	case Global::JumpControl:break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getJumpClimb(Global::EControl controller)
//{
//	Global::EState newState = Global::JumpClimb;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: newState = Global::ThrowJump; break;
//	case Global::HitControl: newState = Global::HitJump; break;
//	case Global::JumpControl:break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getJumpSwing(Global::EControl controller)
//{
//	Global::EState newState = Global::JumpSwing;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: newState = Global::Throw-; break;
//	case Global::HitControl: newState = Global::HitFall; break;
//	case Global::JumpControl:break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getFalling(Global::EControl controller)
//{
//	Global::EState newState = Global::Fall;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: newState = Global::ThrowFall; break;
//	case Global::HitControl: newState = Global::HitFall; break;
//	case Global::JumpControl:break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getStopJump(Global::EControl controller)
//{
//	Global::EState newState = Global::StopJump;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: newState = Global::Run; break;
//	case Global::RightControl: newState = Global::Run; break;
//	case Global::ThrowControl: newState = Global::ThrowStand; break;
//	case Global::HitControl: newState = Global::HitStand; break;
//	case Global::JumpControl:newState = Global::JumpStand; break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getHitStand(Global::EControl controller)
//{
//	Global::EState newState = Global::HitStand;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: newState = Global::Run; break;
//	case Global::RightControl: newState = Global::Run; break;
//	case Global::ThrowControl: newState = Global::ThrowStand; break;
//	case Global::HitControl: break;
//	case Global::JumpControl: newState = Global::JumpStand; break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getHitStand2(Global::EControl controller)
//{
//	Global::EState newState = Global::HitStand2;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: newState = Global::Run; break;
//	case Global::RightControl: newState = Global::Run; break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: newState = Global::ThrowStand; break;
//	case Global::HitControl: break;
//	case Global::JumpControl: newState = Global::JumpStand; break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getHitRun(Global::EControl controller)
//{
//	Global::EState newState = Global::HitRun;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::ThrowControl: newState = Global::ThrowRun; break;
//	case Global::HitControl: break;
//	case Global::JumpControl: newState = Global::JumpStand; break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getHitSitDown(Global::EControl controller)
//{
//	Global::EState newState = Global::HitSitDown;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::ThrowControl: newState = Global::ThrowSitDown;  break;
//	case Global::HitControl: break;
//	case Global::JumpControl: newState = Global::JumpStand; break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getHitJump(Global::EControl controller)
//{
//	Global::EState newState = Global::HitJump;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: newState = Global::ThrowJump; break;
//	case Global::HitControl: break;
//	case Global::JumpControl: break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getHitClimb(Global::EControl controller)
//{
//	Global::EState newState = Global::HitClimb;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: newState = Global::ThrowClimb; break;
//	case Global::HitControl: break;
//	case Global::JumpControl: newState = Global::JumpClimb; break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getHitSwing(Global::EControl controller)
//{
//	Global::EState newState = Global::HitSwing;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: newState = Global::ThrowSwing; break;
//	case Global::HitControl: break;
//	case Global::JumpControl: newState = Global::JumpSwing; break;
//	}
//	return newState;
//}

//
//Global::EState StateManager::getThrowRun(Global::EControl controller)
//{
//	Global::EState newState = Global::ThrowRun;
//	switch (controller)
//	{
//	case Global::NoneControl: newState = Global::Stand; break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::ThrowControl: break;
//	case Global::HitControl: newState = Global::HitRun; break;
//	case Global::JumpControl: newState = Global::JumpRun; break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getThrowSitDown(Global::EControl controller)
//{
//	Global::EState newState = Global::ThrowSitDown;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: break;
//	case Global::HitControl: newState = Global::HitSitDown; break;
//	case Global::JumpControl: newState = Global::JumpStand;  break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getThrowJump(Global::EControl controller)
//{
//	Global::EState newState = Global::ThrowJump;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: break;
//	case Global::HitControl: newState = Global::HitJump; break;
//	case Global::JumpControl: break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getThrowClimb(Global::EControl controller)
//{
//	Global::EState newState = Global::ThrowClimb;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: break;
//	case Global::HitControl: newState = Global::HitClimb; break;
//	case Global::JumpControl: newState = Global::JumpClimb; break;
//	}
//	return newState;
//}
//
//Global::EState StateManager::getThrowSwing(Global::EControl controller)
//{
//	Global::EState newState = Global::ThrowSwing;
//	switch (controller)
//	{
//	case Global::NoneControl: break;
//	case Global::LeftControl: break;
//	case Global::RightControl: break;
//	case Global::DownControl: break;
//	case Global::UpControl: break;
//	case Global::ThrowControl: break;
//	case Global::HitControl: newState = Global::HitSwing; break;
//	case Global::JumpControl: newState = Global::JumpSwing; break;
//	}
//	return newState;
//}
//Global::EState StateManager::getPushWall(Global::EControl controller)
//{
//	//Global::EState newState = Global::PushWall;
//	//switch (controller)
//	//{
//	//case Global::NoneControl: newState = Global::Stand; break;
//	//case Global::LeftControl: break;
//	//case Global::RightControl: break;
//	//case Global::DownControl: break;
//	//case Global::UpControl: break;
//	//case Global::ThrowControl: break;
//	//case Global::HitControl: break;
//	//case Global::JumpControl: newState = Global::JumpStand; break;
//	//}
//	//return newState;
//}

Global::EState StateManager::getAppearance(Global::EControl controller)
{
	Global::EState newState = Global::Appearance;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: break;
	case Global::JumpControl: break;
	}
	return newState;
}
Global::EState StateManager::getStand_shoot(Global::EControl controller)
{
	Global::EState newState = Global::Stand_shoot;
	switch (controller)
	{
	case Global::NoneControl:newState = Global::Stand; break;
	case Global::LeftControl: newState = Global::Run_shoot; break;
	case Global::RightControl:newState = Global::Run_shoot; break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: newState = Global::Dash; break;
	case Global::JumpControl:newState = Global::Jump; break;
	}
	return newState;
}
Global::EState StateManager::getRun_shoot(Global::EControl controller)
{
	Global::EState newState = Global::Run_shoot;
	switch (controller)
	{
	case Global::NoneControl:newState = Global::Stand; break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl:newState = Global::Dash_shoot; break;
	case Global::JumpControl:newState = Global::Jump_shoot; break;
	}
	return newState;
}
Global::EState StateManager::getJump_shoot(Global::EControl controller)
{
	Global::EState newState = Global::Jump_shoot;
	switch (controller)
	{
	case Global::NoneControl: newState = Global::Stand; break;
	case Global::LeftControl:  break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: newState = Global::Dash; break;
	case Global::JumpControl: break;
	}
	return newState;
}
Global::EState StateManager::getIn_climb(Global::EControl controller)
{
	Global::EState newState = Global::In_climb;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: 
	{
		break;
	}
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl:newState = Global::In_climb_shoot; break;
	case Global::HitControl:newState = Global::Dash; break;
	case Global::JumpControl:newState = Global::Jump; break;
	}
	return newState;
}
Global::EState StateManager::getOut_climb(Global::EControl controller)
{
	Global::EState newState = Global::ThrowSwing;
	switch (controller)
	{
	case Global::NoneControl:newState = Global::Stand; break;
	case Global::LeftControl: newState = Global::Run; break;
	case Global::RightControl:newState = Global::Run; break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl:newState = Global::Out_climb_shoot; break;
	case Global::HitControl:newState = Global::Dash; break;
	case Global::JumpControl:newState = Global::Jump; break;
	}
	return newState;
}
Global::EState StateManager::getIn_climb_shoot(Global::EControl controller)
{
	Global::EState newState = Global::In_climb_shoot;
	switch (controller)
	{
	case Global::NoneControl:newState = Global::Stand; break;
	case Global::LeftControl:newState = Global::Out_climb; break;
	case Global::RightControl:newState = Global::Out_climb; break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl:newState = Global::Dash; break;
	case Global::JumpControl:newState = Global::Jump; break;
	}
	return newState;
}
Global::EState StateManager::getOut_climb_shoot(Global::EControl controller)
{
	Global::EState newState = Global::Out_climb_shoot;
	switch (controller)
	{
	case Global::NoneControl:newState = Global::Stand; break;
	case Global::LeftControl:newState = Global::Run; break;
	case Global::RightControl:newState = Global::Run; break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl:newState = Global::Dash; break;
	case Global::JumpControl:newState = Global::Jump; break;
	}
	return newState;
}
Global::EState StateManager::getClimb_ladder(Global::EControl controller)
{
	Global::EState newState = Global::Climb_ladder;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: break;
	case Global::JumpControl: break;
	}
	return newState;
}
Global::EState StateManager::getClimb_ladder_shoot(Global::EControl controller)
{
	Global::EState newState = Global::ThrowSwing;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: break;
	case Global::JumpControl: break;
	}
	return newState;
}
Global::EState StateManager::getDestroyed(Global::EControl controller)
{
	Global::EState newState = Global::ThrowSwing;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: break;
	case Global::JumpControl: break;
	}
	return newState;
}
Global::EState StateManager::getDefense_hurt(Global::EControl controller)
{
	Global::EState newState = Global::Defense_hurt;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: break;
	case Global::JumpControl: break;
	}
	return newState;
}
Global::EState StateManager::getWeak_sit(Global::EControl controller)
{
	Global::EState newState = Global::ThrowSwing;
	switch (controller)
	{
	case Global::NoneControl: break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: break;
	case Global::JumpControl: break;
	}
	return newState;
}
Global::EState StateManager::getDash(Global::EControl controller)
{
	Global::EState newState = Global::Dash;
	switch (controller)
	{
	case Global::NoneControl: newState = Global::Stand; break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl:newState = Global::Dash_shoot; break;
	case Global::HitControl: break;
	case Global::JumpControl:newState = Global::Jump; break;
	}
	return newState;
}
Global::EState StateManager::getDash_shoot(Global::EControl controller)
{
	Global::EState newState = Global::Dash_shoot;
	switch (controller)
	{
	case Global::NoneControl: newState = Global::Stand; break;
	case Global::LeftControl: break;
	case Global::RightControl: break;
	case Global::DownControl: break;
	case Global::UpControl: break;
	case Global::ThrowControl: break;
	case Global::HitControl: break;
	case Global::JumpControl:break;
	}
	return newState;
}
#pragma endregion