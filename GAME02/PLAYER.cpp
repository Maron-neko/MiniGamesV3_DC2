#include"../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "PLAYER.h"
namespace GAME02 {
	void PLAYER::create() {
		Img = loadImage("../main\\assets\\game02\\reimu.png");
	}
	void PLAYER::init() {
		Px = width-width/3;
		Py = height -220;
		Bom = 1;
		Shotlevel = 1;
		ControlOut = false;
	}

	void PLAYER::update() {	
		if (!ControlOut) {
			if (ControlMode[0] == 1) {
				Vx = 4.0f;
				Vy = 4.0f;
				if (isPress(KEY_SHIFT)) {
					Vx = 1.5f;
					Vy = 1.5f;
				}
				if (isPress(MOUSE_RBUTTON)) {
					Vx = 1.5f;
					Vy = 1.5f;
				}
			}
			if (ControlMode[0] == 2) {
				if (Now == 1) {
					Vx = 4.0f;
					Vy = 4.0f;
				}
				if (isTrigger(KEY_SHIFT)) {
					Vx = 1.5f;
					Vy = 1.5f;
					Now *= -1;
				}
				if (isTrigger(MOUSE_RBUTTON)) {
					Vx = 1.5f;
					Vy = 1.5f;
					Now *= -1;
				}
			}

			if (ControlMode[1] == 1) {
				if (isPress(KEY_A)) {
					Px -= Vx;
				}
				if (isPress(KEY_D)) {
					Px += Vx;
				}
				if (isPress(KEY_W)) {
					Py -= Vy;
				}
				if (isPress(KEY_S)) {
					Py += Vy;
				}
				if (isPress(KEY_LEFT)) {
					Px -= Vx;
				}
				if (isPress(KEY_RIGHT)) {
					Px += Vx;
				}
				if (isPress(KEY_UP)) {
					Py -= Vy;
				}
				if (isPress(KEY_DOWN)) {
					Py += Vy;
				}
			}
			if (ControlMode[1] == 2) {
				Px = MouseX;
				Py = MouseY;
			}
			if (Px < 640 + 24) {
				SetCursorPos(641 + 24, MouseY);
				Px = 641 + 24;
			}
			if (Px > 1920 - 24) {
				Px = 1895;
			}
			if (Py < 0) {
				Py = 1;
			}
			if (Py > 1080) {
				Py = 1079;
			}
		}
	}
	void PLAYER::hardupdate() {
		if (!ControlOut) {
			Vx = 5.0f;
			Vy = 5.0f;
			if (isPress(KEY_SHIFT)) {
				Vx = 2.5f;
				Vy = 2.5f;
			}
			if (isTrigger(KEY_SHIFT)) {
				Vx = 2.5f;
				Vy = 2.5f;
			}
			if (ControlMode[1] == 1) {
				if (isPress(KEY_A)) {
					Px -= Vx;
				}
				if (isPress(KEY_D)) {
					Px += Vx;
				}
				if (isPress(KEY_W)) {
					Py -= Vy;
				}
				if (isPress(KEY_S)) {
					Py += Vy;
				}
				if (isPress(KEY_LEFT)) {
					Px -= Vx;
				}
				if (isPress(KEY_RIGHT)) {
					Px += Vx;
				}
				if (isPress(KEY_UP)) {
					Py -= Vy;
				}
				if (isPress(KEY_DOWN)) {
					Py += Vy;
				}
			}
			if (ControlMode[1] == 2) {
				Px = MouseX;
				Py = MouseY;
			}
			if (Px < 640 + 24) {
				SetCursorPos(641 + 24, MouseY);
				Px = 641 + 24;
			}
			if (Px > 1920 - 24) {
				Px = 1895;
			}
			if (Py < 0) {
				Py = 1;
			}
			if (Py > 1080) {
				Py = 1079;
			}
		}

	}
	void PLAYER::draw() {
		rectMode(CENTER);
		image(Img, Px, Py);
	}
	float PLAYER::left() { return Px-0.5f; }
	float PLAYER::right() { return Px + 1.0f; }
	float PLAYER::top() { return Py-1.0f; }
	float PLAYER::bottom() { return Py + 1.0f; }
	bool PLAYER::hit(ENEMY& enemy) {
		if (left() < enemy.right() &&
			right() > enemy.left() &&
			top() < enemy.bottom() &&
			bottom() > enemy.top()) {
			return true;
		}
		return false;
	}
	bool PLAYER::hit(ENEMY3& enemy) {
		if (left() < enemy.right() &&
			right() > enemy.left() &&
			top() < enemy.bottom() &&
			bottom() > enemy.top()) {
			return true;
		}
		return false;
	}
}