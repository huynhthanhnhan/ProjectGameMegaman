#pragma once
#ifndef __ABU_ITEM_H__
#define __ABU_ITEM_H__
#include "ItemObject.h"
#include"Sound.h"
#define ABU_WIDTH 0
#define ABU_HEIGHT 0
class AbuItem :
	public ItemObject
{
private:
	std::vector<Rect*>			_listSourceRect;
	int							_index;
	int							_time;
	int							_reach;
public:
	Sound* _sound;
	AbuItem(int x, int y);
	~AbuItem();
private:
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
};

#endif __ABU_ITEM_H__