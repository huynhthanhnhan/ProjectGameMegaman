#pragma once
#ifndef __ALADDIN_GAME_H__
#define __ALADDIN_GAME_H__

#include"Game.h"
#include"Global.h"

class AladdinGame :public Game
{
public:
	static AladdinGame*				Instance();
	AladdinGame();
	~AladdinGame();
	virtual	void					LoadResource();
protected:
	static AladdinGame				*mInstance;

	virtual	void					ProcessInput(int deltaTime);
	virtual void					OnKeyDown(int keyCode);
	virtual void					UpKeyDown(int keyCode);
};

#endif __ALADDIN_GAME_H__