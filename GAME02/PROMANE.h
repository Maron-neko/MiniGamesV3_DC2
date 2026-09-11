#pragma once
#include "PLAYER.h"
#include "ENEMY.h"
#include "haikei.h"
#include "BULLET.h"
#include "DEFINES.h"
#include "ITEM.h"
#include "EBULLET.h"
#include "SHOT_POINT.h"
#include "Saveload.h"
#include "ENEMY2.h"
#include "BBULLET.h"
#include "SOUNDS.h"
#include "BBULLET2.h"
#include "ENEMY3.h"
#include "ZIKINERAI.h"
#include "FADE.h"
#include "TALKPART.h"
#include<windows.h>
namespace GAME02 {
    //Project Manager
    class PROMANE 
    {
    private:
        int Vy = -5;//ステージ移動用

        enum { NOPOP, BOSSPOP, BOSSEND };
        int NextState;
        int BossState;
        bool IsChangingState = false;
        float ShotDelay;
        float Time;
        //float Timer;
        float Delay;
        float Hdelay;
        int ShotCount;
        int ShotPoint;
        int Wave;
        int Score;
        int HighScore;
        int Stage = 0;
        float Deg[2]{};
        int offsetx[SHOT_POINT] =
        {
            30,-30,55,-55
        };
        int offsety[SHOT_POINT] =
        {
            50, 50, 0, 0
        };
        int Cur = 0;
        int Choose[3];
        char buf[128];
        //char m[10];
        POINT mouse;
        PLAYER Player;
        ITEM Item[ITEM_NUM];
        ENEMY Enemy[ENEMY_NUM];
        ENEMY3 Enemy3[ENEMY3_NUM];
        BOSS Boss;
        BACK Background;
        BULLET Bullet[BULLET_NUM];
        EBULLET Ebullet[BULLET_ENUM];
        ZIKINERAI Zikinerai[ZIKINERAI_NUM];
        SHOTPOINT Shotpoint[SHOT_POINT];
        SAVELOAD Save;
        BBULLET Bbullet[BULLET_BNUM];
        BBULLET2 Bbullet2[BULLET_BNUM];
        SOUNDS Sound;
        FADE Fade;
        TALKPART Talk;
    public:
        enum { TITLE, PLAY, OPTION, HARD, HARDOVER, GAMEOVER, CLEAR, };
        int State;
        void TitleMainText();
        void PlayTexts();
        void GameOverTexts();
        void GameClearTexts();

        void Init();

        bool AllDead();
        void AllInit();
        void AllDraw();
        void AllUpdate();
        void AllCreate();

        void Hits();
        void Waves();

        void TitleProcess();
        void OptionProcess();
        void PlayProcess();
        void AmmoProcess();
        void BossProcess();
        void GameClearProcess();
        void GameOverProcess();
        void Bossshot();
    };
}