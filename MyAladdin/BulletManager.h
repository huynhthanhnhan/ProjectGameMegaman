#pragma once
#ifndef __BULLETMANAGER_H__
#define __BULLETMANAGER_H__
#include"Bullet.h"
#include<vector>
#include<list>
#include"Sound.h"
class BulletManager
{
private:
	BulletManager();
	static BulletManager*		__instance;
	std::list<Bullet*>			_listBullet;
	Sound* _sound;
public:
	~BulletManager();
	static BulletManager*		Instance();
	void						addBullet(Bullet* bullet);
	std::list<Bullet*>			getListBullet();
	void						render();
	void						update(float deltaTime);
private:
	void						refresh();
};

#endif __BULLETMANAGER_H__