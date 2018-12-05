#pragma once
#ifndef __ACTIONGROUND_H__
#define __ACTIONGROUND_H__
#include"Ground.h"
#include"Animation.h"
#include"ActionObject.h"
//Biểu diễn mảnh đật khi nhân vật đứng lên tự động rớt
class ActionGround :public ActionObject, private Animation
{
private:
	bool								_drop;
	int									_x0;
	int									_y0;
public:
	ActionGround();
	ActionGround(int x, int y, int width, int height);
	~ActionGround();
	virtual void						update(float deltaTime);
	virtual void						render();
	virtual Collision::ResultCollision	processCollision(Object* obj);
private:
	virtual void						Render(Global::EDirection direct,
										Global::EState state,
										D3DXVECTOR3 position,
										D3DXVECTOR2 scale = D3DXVECTOR2(1, 1),
										D3DXVECTOR2 translation = D3DXVECTOR2(0, 0),
										float		rotation = 0,
										D3DXVECTOR2 rotationCenter = D3DXVECTOR2());

	virtual void						Refresh();
	virtual	void						LoadResource();
	virtual void						UpdateRender(Global::EState currentState);
};

#endif __ACTIONGROUND_H__