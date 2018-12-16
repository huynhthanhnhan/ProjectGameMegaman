﻿#pragma once
#ifndef __ALADDIN_ACTION_H__
#define __ALADDIN_ACTION_H__
#include"Animation.h"
#include"Sound.h"
class AladdinAction         //Quản lý trạng thái
	:public Animation
{
private:
	int							_time;
	Global::EState				_typeStand;
	Sound*						_sound;
	int							_count;
	int							_maxCount;
	Global::EDirection			_direct;
	WRect						_rope;
	WRect						_column;
	WRect						_bar;
public:
	AladdinAction();
	~AladdinAction();

	void setDirect(Global::EDirection direct);
	void setRope(WRect rope);
	void setColumn(WRect column);
	void setBar(WRect bar);
	WRect getRope();
	WRect getColumn();
	WRect getBar();

	virtual void Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(0, 0));

	// Inherited via Animation
	virtual void Refresh() override;
private:
	void RenderStand(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter);
	//===========================================================================
	//LoadResource
	//===========================================================================
	virtual void LoadResource() override;
	void LoadResourceStand();
	void LoadResourceSitDown();
	void LoadResourceStandUp();
	void LoadResourceLookUp();
	void LoadResourceLookDown();
	void LoadResourceHurt();
	void LoadResourceSwing();
	void LoadResourceRun();
	void LoadResourcePushWall();
	void LoadResourceJump();
	void LoadResourceClimb();
	void LoadResourceClimb_Drop();
	void LoadResourceThrow();
	void LoadResourceHit();
	void LoadResourceRevival();

	void LoadResourceAppearance();
	void LoadResourceDash();
	void LoadResourceIn_climb();
	void LoadResourceStand_shoot();
	void LoadResourceRun_shoot();
	void LoadResourceJump_shoot();
	void LoadResourceDash_shoot();
	void LoadResourceIn_climb_shoot();
	//===========================================================================
	//UpdateRender
	//===========================================================================
	virtual void UpdateRender(Global::EState currentState) override;
	void UpdateRenderStand(Global::EState state);
	void UpdateRenderSitDown(Global::EState state);
	void UpdateRenderStandUp(Global::EState state);
	void UpdateRenderLookUp(Global::EState state);
	void UpdateRenderLookDown(Global::EState state);
	void UpdateRenderHurt(Global::EState state);
	void UpdateRenderSwing(Global::EState state);
	void UpdateRenderRun(Global::EState state);
	void UpdateRenderPushWall(Global::EState state);
	void UpdateRenderJump(Global::EState state);
	void UpdateRenderClimb(Global::EState state);
	void UpdateRenderThrow(Global::EState state);
	void UpdateRenderHit(Global::EState state);
	void UpdateRenderRevival(Global::EState state);

	void UpdateRenderAppearance(Global::EState state);
	void UpdateRenderDash(Global::EState state);
	void UpdateRenderIn_climb(Global::EState state);
	void UpdateRenderStand_shoot(Global::EState state);
	void UpdateRenderRun_shoot(Global::EState state);
	void UpdateRenderJump_shoot(Global::EState state);
	void UpdateRenderDash_shoot(Global::EState state);
	void UpdateRenderIn_climb_shoot(Global::EState state);

	//===========================================================================
	//Determine Direction
	//===========================================================================
	virtual	void DetermineDirection(Global::EState state, Global::EDirection direct);
};

#endif __ALADDIN_ACTION_H__