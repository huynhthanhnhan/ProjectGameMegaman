#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__
#include<dsound.h>
#include<Windows.h>
#include<map>
#include"Application.h"
#include"Global.h"
//============================================================
//BackGround
//============================================================
#define SOUND_BACKGOUND "Audio//PrinceAli.wav"
#define SOUND_BACKGROUND_BOSS "Audio//BossTune.wav"
#define SOUND_BACKGROUND_MENU "Audio//AWholeNewWorld.wav"
#define SOUND_LEVELCOMPLETE "Audio//LevelComplete.wav"
#define SOUND_BOXBELL "Audio//BoxingBell.wav"


//============================================================
//Map
//============================================================
#define SOUND_STICK "Audio//Flagpole.wav"
#define SOUND_FIRE_FROM_COAL "Audio//FireFromCoal.wav"
//============================================================
//Action
//============================================================
#define SOUND_HIGH_SWORD "Audio//HighSword.wav"
#define SOUND_LOW_SWORD "Audio//LowSword.wav"
#define SOUND_SWORD_CHING "Audio//SwordChing.wav"
#define SOUND_OBJECT_THROW "Audio//ObjectThrow.wav"
#define SOUND_REACH_APPLE "Audio//AppleSplat.wav"
#define SOUND_CLAY_POT "Audio//ClayPot.wav"
#define SOUND_SWORD_SPINNING "Audio//SwordSpinning.wav"
#define SOUND_CLOUD_POOF "Audio//CloudPoof.wav"
#define SOUND_ABU_WAVING "Audio//AbuWaving.wav"

//============================================================
//Select
//============================================================
#define SOUND_MENU_CHANGE "Audio//MenuChange.wav"
#define SOUND_MENU_SELECT "Audio//MenuSelect.wav"
//============================================================
//Speak
//============================================================
#define SOUND_ALADDIN_HURT "Audio//AladdinHurt.wav"
#define SOUND_ALADDIN_OOF "Audio//AladdinOof.wav"
#define SOUND_ALADDIN_PUSH "Audio//AladdinPush.wav"
#define SOUND_ALADDIN_CONTINUE_POINT "Audio//ContinuePoint.wav"
#define SOUND_ALADDIN_COMING "Audio//ComingOut.wav"
#define SOUND_COMEON "Audio//GuardBeckon.wav"
#define SOUND_GUARD_HIT1 "Audio//GuardHit1.wav"
#define SOUND_GUARD_HIT2 "Audio//GuardHit2.wav"
#define SOUND_GUARD_PAINTS "Audio//GuardPants.wav"
#define SOUND_GUARD_A "Audio//Aaah.wav"
#define SOUND_GUARD_E "Audio//Eeeh.wav"
#define SOUND_GUARD_O "Audio//Oooh.wav"
#define SOUND_JAFAR_LAUGH "Audio//JafarLaugh.wav"
#define SOUND_JAFAR_SNAKE "Audio//JafarSnake.wav"
#define SOUND_CAMEL "Audio//CamelSpit.wav"
//============================================================
//Item
//============================================================
#define SOUND_PEDDLER_SHOP "Audio//PeddlerShop.wav"
#define SOUND_TAKE_GEM "Audio//GemCollect.wav"
#define SOUND_TAKE_APPLE "Audio//AppleCollect.wav"
#define SOUND_TAKE_HEART "Audio//ExtraHealth.wav"
#define SOUND_TAKE_JAR "Audio//ContinuePoint.wav"
#define SOUND_GENIE_FUMES "Audio//Wow!.wav"
#define SOUND_TAKE_TEAPOT "Audio//GenieFumes.wav"
#define SOUND_TAKE_ABU "Audio//Wow!.wav"
#define SOUND_A_DEAL "Audio//CashRegister.wav"

class Sound
{
public:
	struct WaveHeader
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
private:
	static Sound*				__instance;
	std::map<std::string, IDirectSoundBuffer8*> _listSoundBuffer;
	bool						_isMute;
	IDirectSoundBuffer*			_primaryBuffer;
	IDirectSound8*				_soundDevice;
	float						_volumne;
	std::string					_currentBackGround;//Lưu tên nhạc background
public:
	~Sound();
	static Sound*				Instance();
	float						getVolumne();
	void						setVolume(float percentage, std::string name = "");
	void						playBackGround(std::string name,  float volumne = -1, bool isLoop = true);
	void						play(std::string name, bool isLoop = false, int times = 1, float volumne = -1);
	void						stop(std::string name = "");
	void						mute();
	void						unMute();
	bool						isMute();
private:
	Sound();
	void						init();
	void						loadSound(char* path);

};

#endif __SOUND_H__