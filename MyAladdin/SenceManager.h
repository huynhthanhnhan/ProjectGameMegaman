#pragma once
#ifndef __SENCE_MANAGER_H__
#define __SENCE_MANAGER_H__
#include"ISence.h"

class SenceManager
{
public:
	~SenceManager();
	static SenceManager*			Instance();
	ISence*							GetCurrentSence();
	void							Update(float dt);
	void							ReplaceSence(ISence* sence);
private:
	SenceManager();
	static SenceManager				*mInstance;
	ISence							*mCurrentSence;
};

#endif __SENCE_MANAGER_H__