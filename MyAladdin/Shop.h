#pragma once
#ifndef __SHOP_H__
#define __SHOP_H__
#include"Animation.h"
class Shop
	:public Animation
{
public:
	Shop();
	~Shop();

	virtual void Render(Global::EDirection direct,
		Global::EState state,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scale = D3DXVECTOR2(1, 1),
		D3DXVECTOR2 translation = D3DXVECTOR2(0, 0),
		float		rotation = 0,
		D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void UpdateRender(Global::EState currentState) override;
	// Inherited via Animation
	virtual void Refresh() override;
private:
	virtual void LoadResource() override;

};

#endif __SHOP_H__