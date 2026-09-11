#include "ENEMY2.h"
#include "../../libOne/inc/graphic.h"
namespace GAME02 {
	void BOSS::create() {
		Img = loadImage("../main\\assets\\game02\\Fran.png");
	}
	void BOSS::init() {
		Px = width - width / 3;
		Py = -100;
		Vx = 2.0f;
		Vy = 2.0f;
		Vy2 = 8.0f;
		Hp = 5000;
		Deg = 0;
		Cnt1 = 120;
		Cnt2 = 300;
		Cnt3 = 100;
		Cnt4 = 200;

		Delay = rand() % 30 + 60;
		Alive = true;
		Pattern = Pop;
		LimitTime = 6000;
	}

	void BOSS::bosspop() {
		if (Cnt1 > 0) {
			Py += Vy;
			Cnt1--;
		}
		if (Hp <= 4000) {
			Pattern=Pattern1;
		}
	}
	void BOSS::bossPattern1(){
			
			if (Cnt2 > 200) {
				Px -= Vx;
				Py += Vy;
				Cnt2--;
			}
			else if (Cnt2 > 0) {
				Px += Vx;
				Cnt2--;
			}
			if (Cnt2 == 0) {
				Px += Vx;
				if (Px > 1920-72 || Px < 640+72) {
					Vx *= -1;
				}
			}
			

			if (Hp <= 3000) {
				Pattern = Pattern2;
		}
	}
	void BOSS::bossPattern2(){
		Px += Vx;
		if (Px > 1920-72 || Px < 640+72) {
			Vx *= -1;
		}


		if (Hp <= 2500) {
			Pattern = Pattern3;
			Vx = 1;
		}
	}
	void BOSS::bossPattern3(){
		
		Px += Vx;
		if (Px > 1920-72 || Px < 640+72) {
			Vx *= -1;
		}

	}
	void BOSS::update() {
		LimitTime--;
		Cnt4--;
		switch (Pattern)
		{
		case Pop:
			bosspop();
			break;
		case Pattern1:
			bossPattern1();
			break;
		case Pattern2:
			bossPattern2();
			break;
		case Pattern3:
			bossPattern3();
			break;
		}
		//Hp -= 1;
		if (Py < 1280) {
			-200;
		}
	}
	void BOSS::draw() {
		
		rectMode(CENTER);
		image(Img, Px, Py, 0, 3);
		noStroke();
		if (Hp > 0) {
			fill(0, 255, 0);
			rectMode(CORNER);
			int wid = Hp / 4;
			rect(642, 0, wid, 10);
		}
	}
	float BOSS::left() { return Px - 72.0f; }
	float BOSS::right() { return Px + 72.0f; }
	float BOSS::top() { return Py - 72.0f; }
	float BOSS::bottom() { return Py + 72.0f; }
	bool BOSS::hit(BULLET& bullet) {
		if (left() < bullet.right() &&
			right() > bullet.left() &&
			top() < bullet.bottom() &&
			bottom() > bullet.top()) {
			Hp -= 1000;
			return true;
			
		}
		return false;
	}
}