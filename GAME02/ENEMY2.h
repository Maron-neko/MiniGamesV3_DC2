#pragma once
#include"ENEMY_BASE.h"
#include "BULLET.h"
namespace GAME02 {
    class BOSS :
        public ENEMY_BASE
    {
	private:

		float Vy2;
		float Deg;
		enum BossPattern
		{
			Pop,
			Pattern1,
			Pattern2,
			Pattern3,
			Pattern4,
		};
		BossPattern Pattern = Pop;
	public:
		int Cnt1, Cnt2, Cnt3, Cnt4;
		int LimitTime;
		bool hit(BULLET& bullet);
		void create();
		void init();
		void update();
		void draw();
		void bosspop();
		void bossPattern1();
		void bossPattern2();
		void bossPattern3();


		float left();
		float right();
		float top();
		float bottom();
    };
}

