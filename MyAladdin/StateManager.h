#pragma once
#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include"Global.h"

//Quản lý các trạng thái của nhân vật
//Quản lý việc chuyển đổi qua lại giữa các trạng thái
class StateManager
{
private:
	static StateManager*				__instance;
	StateManager();
public:
	~StateManager();
	static StateManager*				Instance();
	Global::EState						getNewState(Global ::EState oldState,Global::EControl control);
private:
	Global::EState						getRun(Global::EControl controller);
	Global::EState						getStand(Global::EControl controller);
	Global::EState						getClimb(Global::EControl controller);
	Global::EState						getReadyStopRun(Global::EControl controller);
	Global::EState						getJumpStand(Global::EControl controller);
	Global::EState						getJumpRun(Global::EControl controller);
	Global::EState						getJumpClimb(Global::EControl controller);
	Global::EState						getJumpSwing(Global::EControl controller);
	Global::EState						getFalling(Global::EControl controller);
	Global::EState						getStopJump(Global::EControl controller);
	Global::EState						getHitStand(Global::EControl controller);
	Global::EState						getHitStand2(Global::EControl controller);
	Global::EState						getHitRun(Global::EControl controller);
	Global::EState						getHitSitDown(Global::EControl controller);
	Global::EState						getHitJump(Global::EControl controller);
	Global::EState						getHitClimb(Global::EControl controller);
	Global::EState						getHitSwing(Global::EControl controller);
	Global::EState						getThrowStand(Global::EControl controller);
	Global::EState						getThrowSitDown(Global::EControl controller);
	Global::EState						getThrowJump(Global::EControl controller);
	Global::EState						getThrowClimb(Global::EControl controller);
	Global::EState						getThrowSwing(Global::EControl controller);
	Global::EState						getThrowRun(Global::EControl controller);
	Global::EState						getPushWall(Global::EControl controller);

	Global::EState                       getAppearance(Global::EControl controler);
	Global::EState						getStand_shoot(Global::EControl controler);
	Global::EState						getRun_shoot(Global::EControl controler);
	Global::EState						getJump(Global::EControl controler);
	Global::EState						getJump_shoot(Global::EControl controler);
	Global::EState						getIn_climb(Global::EControl controler);
	Global::EState						getOut_climb(Global::EControl controler);
	Global::EState						getIn_climb_shoot(Global::EControl controler);
	Global::EState						getOut_climb_shoot(Global::EControl controler);
	Global::EState						getClimb_ladder(Global::EControl controler);
	Global::EState						getClimb_ladder_shoot(Global::EControl controler);
	Global::EState						getDestroyed(Global::EControl controler);
	Global::EState						getDefense_hurt(Global::EControl controler);
	Global::EState						getWeak_sit(Global::EControl controler);
	Global::EState						getDash(Global::EControl controler);
	Global::EState						getDash_shoot(Global::EControl controler);
};

#endif __STATEMANAGER_H__