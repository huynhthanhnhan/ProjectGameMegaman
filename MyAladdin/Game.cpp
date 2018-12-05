#include "Game.h"


Game::Game()
{
	keyBoard = KeyBoard::Instance();
}

Game::~Game()
{
}

void Game::LoadResource()
{
}

void Game::ProcessKeyBoard()
{
}

void Game::ProcessInput()
{
	SenceManager::Instance()->GetCurrentSence()->ProcessInput();
}

void Game::Initialize()
{
	ViewPort::Instance()->Init(0, WORLD_Y);

	this->LoadResource();
}

void Game::Run(float deltaTime)
{
	Graphics* graphics = Graphics::Instance();						//get graphics
	LPDIRECT3DDEVICE9 device = graphics->GetDirectDevice();			//get device
	LPD3DXSPRITE spriteHandler = graphics->GetSpriteHandler();		//get spriteHandler

	if (device->BeginScene())										//Begin draw
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);				//Begin draw sprite
		device->ColorFill(											//Fill backbuffer
			Graphics::Instance()->GetBackBuffer() ,
			NULL,
			D3DCOLOR_XRGB(123, 255, 255));
		//-----------------------------------------------------------------------------

		SenceManager::Instance()->GetCurrentSence()->Render();				//Render
		this->ProcessInput();												//Input
		SenceManager::Instance()->GetCurrentSence()->Update(deltaTime);		//Update sence

		//-----------------------------------------------------------------------------
		spriteHandler->End();
		device->EndScene();
	}
	device->Present(NULL, NULL, NULL, NULL);
}

void Game::AddSence(ISence * sence)
{
	this->mListSence.push_back(sence);
	sence->LoadContent();
}
