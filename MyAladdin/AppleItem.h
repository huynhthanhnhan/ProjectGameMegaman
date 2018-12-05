#pragma once
#ifndef __APPLE_ITEM_H__
#define __APPLE_ITEM_H__
#include"ItemObject.h"
#include"Aladdin.h"
#include"Sound.h"
#define APPLE_WIDTH  28
#define APPLE_HEIGHT 32.5

class AppleItem
	:public ItemObject
{
public:
	Sound* _sound;
	AppleItem(int x, int y);
	~AppleItem();
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
};

#endif __APPLE_ITEM_H__