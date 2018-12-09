#ifndef __GLOBAL_H__
#define	__GLOBAL_H__
#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<dinput.h>
#include<Windows.h>
#define	GameName			"Aladdin"
#define _FPS				30
#define GL_KEY_BUFFER_SIZE	1024
#define FRAME_PER_SECOND	35

//Maximum of World port
#define WORLD_Y				7933
#define WORLD_X				7933

#define MAP_WIDTH			7933 //(4771*2 trong đó 4771 là chiều rộng thực sự của map, 2 là scale
#define MAP_HEIGHT			2039 //(688* 2.5 trong đó 688 là chiều cao thực sự của map 2.5 là vector scale)

//Gia tốc trọng trường trong môi trường game
#define ACCELERATION		8000

class Global
{
public:
	Global();
	~Global();
	//--------------------------------------------------------------
	static bool					isGameRunning;
	static void					GLPostMessage(char* msg);
	//--------------------------------------------------------------

	struct Transform
	{
		Transform() :
			_translation(D3DXVECTOR2(0, 0)), _scale(D3DXVECTOR2(1, 1)), _rotation(0), _rotationCenter(D3DXVECTOR2()) {}
		D3DXVECTOR3					_position;
		D3DXVECTOR3					_translation;
		D3DXVECTOR2					_scale;
		float						_rotation;
		D3DXVECTOR2					_rotationCenter;
	};

	enum EState
	{
		
		
		
		PushWall,
		StopRun,

		JumpRun,
		JumpStand,
		JumpClimb,
		JumpSwing,
		JumpRotate,
		Fall,
		StopJump,

		HitStand,
		HitStand2,
		HitRun,
		HitSitDown,
		HitJump,
		HitClimb,
		HitSwing,
		HitFall,

		ThrowStand,
		ThrowSitDown,
		ThrowJump,
		ThrowClimb,
		ThrowSwing,
		ThrowFall,
		ThrowRun,

		OnTrap,
		Attack,

		Revival,

		Hp0,
		Hp1,
		Hp2,
		Hp3,
		Hp4,
		Hp5,
		Hp6,
		Hp7,
		Hp8,

		Gem,
		A_Deal,

		Hurting,
		Dead,
		Alive,
		Snake,
		NoneAction,
		Victory1,
		Victory2,
		Dead1,
		Dead2,
		Knife,

		Appearance,
		Stand,
		Stand_shoot,
		Run,
		Run_shoot,
		Climb,
		Jump,
		Jump_shoot,
		In_climb,
		Out_climb,
		In_climb_shoot,
		Out_climb_shoot,
		Climb_ladder,
		Climb_ladder_shoot,
		Dash,
		Dash_shoot,
		Destroyed,
		Hurt,
		Defense_hurt,
		Weak_sit,
	};

	enum EControl
	{
		NoneControl,
		LeftControl,
		RightControl,
		DownControl,
		UpControl,
		JumpControl,
		ThrowControl,
		HitControl
	};

	enum EDirection
	{
		Right,
		Left,
		Up,
		Down,
		None
	};

	enum EObject
	{
		GROUND,
		GROUND_DROP,
		ROPE,
		WALL,
		LEVERAGE,
		COLUMN,
		BAR,
		STAIR,

		ALADDIN,
		CAMEL,
		GUARD1,
		GUARD2,
		GUARD3,
		CIVILIAN1,
		CIVILIAN2,
		CIVILIAN3,
		CIVILIAN4,
		PEDDLER,

		CAMELBULLET,
		SWORDBULLET,
		APPLEBULLET,
		CIVILIANBULLET,
		APPLEITEM,
		TEAPOTITEM,
		GENIEITEM,
		GEMITEM,
		ALADDINITEM,
		HEARTITEM,
		MONKEYITEM,
		JARITEM,
		STICKITEM,
		ABUITEM,
		TRAP,
		JAFAR,
		SNAKE,
		JAFARBULLET,
		SNAKEBULLET,
		PLATFORM,
		FIRE
	};
	enum ETypeObject
	{
		Static,
		Enemy,
		AladdinParty
	};
	//--------------------------------------------------------------
private:

};

#endif __GLOBAL_H__