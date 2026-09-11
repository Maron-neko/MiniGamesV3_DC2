#include "ZIKINERAI.h"
#include "../../libOne/inc/graphic.h"
#include"../../libOne/inc/mathUtil.h"
namespace GAME02 {
	void ZIKINERAI::create() {
		Img = loadImage("../main\\assets\\game02\\bluebullet.png");

	}
	void ZIKINERAI::init() {
		Alive = false;
	}
	void ZIKINERAI::shoot(PLAYER& player,ENEMY3& enemy) {
		Bx = enemy.Px;
		By = enemy.Py;
		float vx = player.Px - enemy.Px;
		float vy = player.Py - enemy.Py;
		float length = Sqrt(vx * vx + vy * vy);
		Vx = vx / length * 5;
		Vy = vy / length * 5;
		Alive = true;
	}
	void ZIKINERAI::update() {
		if (!Alive) {
			return;
		}
		Bx += Vx;
		By += Vy;
		if (By > 1080) {
			Alive = false;
		}
		if (By < 0) {
			Alive = false;
		}
		if (Bx > 1920) {
			Alive = false;
		}
		if (Bx < 640) {
			Alive = false;
		}
	}
	void ZIKINERAI::draw() {
		if (Alive) {
			image(Img, Bx, By, -90);
		}

	}
	float ZIKINERAI::left() { return Bx - 8.0f; }
	float ZIKINERAI::right() { return Bx + 8.0f; }
	float ZIKINERAI::top() { return By - 8.0f; }
	float ZIKINERAI::bottom() { return By + 8.0f; }

	bool ZIKINERAI::hit(PLAYER& player) {
		if (left() <= player.right() &&
			right() >= player.left() &&
			top() <= player.bottom() &&
			bottom() >= player.top()) {
			return true;
		}
		return false;
	}
	
}