#include "Camera.h"
#include"Graphics.h"

Camera*			Camera::__instance;

Camera * Camera::Instance()
{
	if (!__instance)
		__instance = new Camera();
	return __instance;
}

Camera::Camera()
{
	Application* apps = Application::Instance();

	this->_width = apps->getWidth();
	this->_height = apps->getHeight();
	this->_position = D3DXVECTOR3(0, 0, 0);
}

void Camera::ReviseCamera()
{
	D3DXVECTOR3 lt_position = this->_position;
	D3DXVECTOR3 lb_position = D3DXVECTOR3(this->_position.x, this->_position.y - this->_height, 0);
	D3DXVECTOR3 rt_position = D3DXVECTOR3(this->_position.x + this->_width, this->_position.y, 0);
	D3DXVECTOR3 rb_position = D3DXVECTOR3(this->_position.x + this->_width, this->_position.y - this->_height, 0);

	//=========================
	//Left Top
	//=========================
	if (lt_position.x < 0)
		this->_position.x = 0;
	if (lt_position.y > WORLD_Y)
		this->_position.y = WORLD_Y;
	//=========================
	//Left Bottom
	//=========================
	if (lb_position.x < 0)
		this->_position.x = 0;
	if (lb_position.y < WORLD_Y - MAP_HEIGHT)
		this->_position.y = WORLD_Y - MAP_HEIGHT + _height;
	//=========================
	//Right Top
	//=========================
	if (rt_position.x > WORLD_X)
		this->_position.x = WORLD_X - _width;
	if (rt_position.y > WORLD_Y)
		this->_position.y = WORLD_Y;
	//=========================
	//Right Bottom
	//=========================
	if (rb_position.x > WORLD_X)
		this->_position.x = WORLD_X - _width;
	if (rb_position.y < WORLD_Y - MAP_HEIGHT)
		this->_position.y = WORLD_Y - MAP_HEIGHT + _height;
}

Camera::~Camera()
{
}

void Camera::update(Aladdin* aladdin)
{
	//D3DXVECTOR3 aladdinPosition = ViewPort::Instance()->getViewPortPosition(D3DXVECTOR3(aladdin->GetCurrentLocation().x, aladdin->GetCurrentLocation().y, 0));
	
	float aladdinX = (aladdin->getDirect() == Global::Left) ? aladdin->getCurrentLocation().x : aladdin->getCurrentLocation().x;
	float aladdinY = aladdin->getCurrentLocation().y;

	float halfWidth = Application::Instance()->getWidth() / 2;
	float halfHeight = Application::Instance()->getHeight() / 2;

	D3DXVECTOR3 cameraPosition = ViewPort::Instance()->getViewPortPosition(_position);

	float cameraX = _position.x + halfWidth;
	float cameraY = _position.y - halfHeight;

	this->_vx = this->_vy = 0;

	//Left
	if (aladdinX < cameraX - DELTA_CAMERA)
	{
		this->_vx = aladdinX - cameraX + DELTA_CAMERA;
	}
	//Right
	if (aladdinX > cameraX + DELTA_CAMERA)
	{
		this->_vx = aladdinX - cameraX - DELTA_CAMERA;
	}
	//Top
	if (aladdinY < cameraY - DELTA_CAMERA)
	{
		this->_vy = aladdinY - (cameraY - DELTA_CAMERA);
	}
	//Bottom
	if (aladdinY > cameraY + DELTA_CAMERA)
	{
		this->_vy = aladdinY - (cameraY + DELTA_CAMERA);
	}
	this->_position.x += 0.3*_vx;
	this->_position.y +=  0.3*_vy;

	this->ReviseCamera();

	this->_rectBound.update(_position.x, _position.y, _width, _height);
}

void Camera::translation(D3DXVECTOR3 vector)
{
	this->_position += vector;
}

WRect Camera::getBound()
{
	return _rectBound;
}

int Camera::getWidth()
{
	return this->_width;
}

int Camera::getHeight()
{
	return this->_height;
}

void Camera::setWidth(int width)
{
	this->_width = width;
}

void Camera::setHeight(int height)
{
	this->_height = height;
}

D3DXVECTOR3 Camera::getPosition()
{
	return this->_position;
}

void Camera::setPosition(float x, float y, float z)
{
	this->_position = D3DXVECTOR3(x, y, z);
}

void Camera::setPosition(D3DXVECTOR3 position)
{
	this->_position = position;
}
