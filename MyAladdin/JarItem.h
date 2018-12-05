#pragma once
#ifndef __JAR_ITEM_H__
#define __JAR_ITEM_H__
#include"ItemObject.h"
#include"Sound.h"
#define JAR_WIDTH 44
#define JAR_HEIGHT 87
class JarItem             //Cái lọ hồi sinh
	:public ItemObject
{
private:
	int						_time;
	int						_index;
	std::vector<Rect*>		_listSourceRect;
	bool					_start;
public:
	Sound* _sound;
	JarItem(int x, int y);
	~JarItem();
private:
	// Inherited via ItemObject
	virtual void getItem() override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual Collision::ResultCollision processCollision(Object * obj);
};

#endif __JAR_ITEM_H__