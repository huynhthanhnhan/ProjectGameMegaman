#pragma once
#ifndef __OBJECT_H__
#define __OBJECT_H__
#include"WRect.h"
#include"ViewPort.h"
#include"Application.h"
#include"Collision.h"

class Object
{
protected:
	Global::EObject			_id;
	//object position in worl port
	int						_x;
	int						_y;
	//object velocity
	float					_v0;
	float					_x0;
	float					_vx;
	float					_vy;
	//object width and height
	int						_width;
	int						_height;
	//rectangle bound object
	WRect					_rectBound;
	Global::Transform		_transform;
	Global::ETypeObject		_type;
public:
	Object();
	Object(int x, int y, int width = 0, int height = 0);
	~Object();

	Global::EObject			getId();
	int						getX();
	float					getX0();
	int						getY();
	float					getV0();
	float					getVx();
	float					getVy();
	int						getWidth();
	int						getHeight();
	D3DXVECTOR2				getCurrentLocation();
	WRect					getRectBound();
	Global::ETypeObject		getTypeObject();
	void					setCurrentLocation(int x, int y);
	void					setId(Global::EObject id);
	void					setX0(float x0);
	void					setV0(float v0);
	void					setVx(float vx);
	void					setVy(float vy);

	virtual	void			update(float detalTime) = 0;
	virtual D3DXVECTOR3		getViewPortPosition();
	virtual void			updateBody();
	virtual void			transform();
	virtual Collision::ResultCollision
							processCollision(Object* obj) = 0;
};

#endif __OBJECT_H__