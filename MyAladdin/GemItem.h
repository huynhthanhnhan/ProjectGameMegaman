#pragma once
#ifndef __GEM_ITEM_H__
#define __GEM_ITEM_H__
#include "ItemObject.h"
#include "Aladdin.h"
#include"Sound.h"
#define GEM_WIDTH 34
#define GEM_HEIGHT 37
class GemItem :
	public ItemObject
{
private:
	std::vector<Rect*>			_listSourceRect;
	int							_index;
	int							_time;
public:
	Sound* _sound;
	GemItem(int x, int y);
	~GemItem();
private:
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
};

#endif __GEM_ITEM_H__