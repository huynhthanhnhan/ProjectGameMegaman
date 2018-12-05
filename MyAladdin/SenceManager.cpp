#include "SenceManager.h"

SenceManager*	SenceManager::mInstance = nullptr;

SenceManager::SenceManager()
{
	mCurrentSence = nullptr;
}


SenceManager::~SenceManager()
{
	delete this->mCurrentSence;
}

SenceManager * SenceManager::Instance()
{
	if (!mInstance)
		mInstance = new SenceManager();

	return SenceManager::mInstance;
}

ISence * SenceManager::GetCurrentSence()
{
	return this->mCurrentSence;
}

void SenceManager::Update(float dt)
{
	this->mCurrentSence->Update(dt);
}

void SenceManager::ReplaceSence(ISence * sence)
{
	if(this->mCurrentSence)
		delete(this->mCurrentSence);
	this->mCurrentSence = sence;
}
