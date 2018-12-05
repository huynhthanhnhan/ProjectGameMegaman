#pragma once
#ifndef __PEDDLER_ITEM_H__
#define __PEDDLER_ITEM_H__
#include"ItemObject.h"
#include"Sound.h"
#include"Graphics.h"
#define PEDDLER_WIDTH 145
#define PEDDLER_HEIGHT 69
class Peddler
	:public ItemObject
{
private:
	int						_index;
	int						_index1;
	int						_index2;
	std::vector<Rect*>		_listSourceRect1;
	std::vector<Rect*>		_listSourceRect2;
	std::vector<Rect*>		_listSourceRect3;
	std::vector<Rect*>		_listSourceRect4;
	std::vector<Rect*>		_listSourceRect5;
	bool					_start;
	WRect					_rectPeddler;
	Graphics*				_graphic;
public:
	Sound* _sound;
	Peddler(int x, int y);
	~Peddler();
private:
	virtual void getItem() override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual Collision::ResultCollision processCollision(Object * obj);
};

#endif __PEDDLER_ITEM_H__