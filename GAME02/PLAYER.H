#pragma once
#include"ENEMY.h"
#include "ENEMY3.h"
namespace GAME02
{
	class PLAYER {
	private:
		int Img=0;
		int Now=1;
	public:
		float Px, Py, Vx, Vy;
		int Bom;
		int Shotlevel;
		int ControlMode[2]{1,1};
		bool ControlOut = false;
		void create();
		void init();
		void update();
		void draw();
		void hardupdate();
		
		float left();
		float right();
		float top();
		float bottom();

		bool hit(ENEMY&);
		bool hit(ENEMY3&);
	};
}