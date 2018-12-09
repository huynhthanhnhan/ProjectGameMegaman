#pragma once
#ifndef _ALADDIN_H__
#define _ALADDIN_H__

#pragma region Library
#include"ActionObject.h"
#include"Global.h"
#include"SpriteManager.h"
#include<vector>
#include"KeyBoard.h"
#include"Apple.h"
#include"Application.h"
#include"AladdinAction.h"
#include"Sound.h"
#include"BulletManager.h"
#include<math.h>
#pragma endregion

//Quảng đường đi được trong một bước chân của Aladdin
#define	DISTANCE	15
#define ALADDIN_WIDTH 80
#define ALADDIN_HEIGHT_NORMAL 120
#define ALADDIN_HEIGHT_SITDOWN 60
#define ALADDIN_HEIGHT_CLIMB 150
#define ALADDIN_HEIGHT_SWING 200

class Aladdin :public ActionObject
{
private: 
	static Aladdin*				_instance;
	AladdinAction*				_aladdinAction;
	Sound*						_sound;
	std::vector<Apple*>			_listApple;
	//Time from first frametime to last frametime
	float						_deltaTime;
	//Đếm số bước chạy của nhân vật
	int							_countRun;

	int _countDash;
	
	int _countJump;
	//Hình chữ nhật dành để xét va chạm với cầu thang, đất, dây...
	WRect						_rectBound2;
	//hình chữ nhật dành riêng để xét va chạm với thanh bar giúp game mượt hơn khi nhảy lên thanh bar
	WRect						_rectWithBar;
	//Biến xác định đi cầu thang nào dùng trong cầu thang ghép
	int							_decideStair;
	//Biến báo hiệu reset khi bị trừ máu
	bool						_isReset;
	int							_countReset;
	bool						_drawReset;
	D3DXVECTOR2					_startPosition;		//Vị trí bắt đầu của aladdin
	bool						_startPosition_;
	int							_numberOfApple;		//Số lượng táo của aladdin có được
	int							_numberOfGem;		//Số lượng đá quý
	int							_score;
	int							_life;
	bool						_isVictory1;
	bool						_isVictory2;
	bool						_isGameOver;
public:
	bool bDash;
	//=====================================================
	//Init
	//=====================================================
	static Aladdin*   getInstance();
	void Init(int x, int y, int number_apple, int hp, int life);
	Aladdin();
	~Aladdin();
	//=====================================================
	//Core
	//=====================================================
	virtual void				update(float deltaTime);
	virtual void				render();
	virtual void				updateBody();
	virtual Collision::ResultCollision
								processCollision(Object* obj);
#pragma region Action Method
	void						Stand();
	void						Running();
	bool						IsPushWall();
	void						PushWall();
	void						Climb();

	void						Hurting();

	bool						IsHit();
	void						HitStand();
	void						HitStand2();
	void						HitRun();
	void						HitSitDown();
	void						HitJump();
	void						HitClimb();
	void						HitSwing();
	void						HitFall();

	void						ThrowStand();
	void						ThrowSitDown();
	void						ThrowJump();
	void						ThrowClimb();
	void						ThrowSwing();
	void						ThrowFall();
	void						ThrowRun();

	bool						IsJump();
	void						JumpStand();
	void						JumpRun();
	void						JumpClimb();
	void						JumpSwing();
	void						JumpRotate();
	
	void						Fall();

	void						Revival();

	
	void						StopJump();
	void						StopRun();

	void						Appearance();
	void Stand_shoot();
	void Run();
	void Run_shoot();
	void Jump();
	void Jump_shoot();
	void In_climb();
	void Out_climb();
	void In_climb_shoot();
	void Out_climb_shoot();
	void Climb_ladder();
	void Climb_ladder_shoot();
	void Dash();
	void Destroyed();
	void Hurt();
	void Defense_hurt();
	void Weak_sit();
	void Dash_shoot();

#pragma endregion
	//====================================================
	//get action
	//====================================================
	AladdinAction*				getAladdinAction();
	WRect						getRectBound2();
	WRect						getRectWithBar();
	int							getDecideStair();
	void						setDecideStair(int decide);
	bool						isReset();
	bool						isVictory1();
	bool						isVictory2();
	void						setReset(bool flag = true);
	void						setVictory1(bool flag = true);
	void						setVictory2(bool flag = true);
	void						setStartPosition(int x, int y);
	void						increaseApple();
	void						setHp(int hp);
	void						setGem(int Gem);
	void						increaseGem();
	void						increaseScore(int score);
	void						setLife(int life);

	int							getHp();
	int							getNumberOfApple();
	int							getNumberOfGem();
	int							getScore();
	int							getLife();

	void getXY() {
		cout << this->_x
			<< this->_y;
	}
private:
	void						loadResource();
	void						caculateSpeed(float deltaTime);
};

#endif _ALADDIN_H__