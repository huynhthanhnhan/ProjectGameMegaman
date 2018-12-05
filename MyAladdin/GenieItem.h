#pragma once
#ifndef __GENIE_ITEM_H__
#define __GENIE_ITEM_H__
#include "ItemObject.h"
#include"Sound.h"
#define GENIE_WIDTH 80
#define GENIE_HEIGHT 130
class GenieItem :
	public ItemObject
{
private:
	std::vector<Rect*>			_listSourceRect;
	int							_index;
	int							_time;
	int							_reach;
public:
	Sound* _sound;
	GenieItem(int x, int y);
	~GenieItem();
private:
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
};

#endif __GENIE_ITEM_H__