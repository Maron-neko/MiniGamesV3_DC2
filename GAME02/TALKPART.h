#pragma once
namespace GAME02 {
	class TALKPART
	{
	private:
		int Img[2]{};
		int Px[2]{}, Py[2]{};
		int Vx = 0, Vy = 0;
		int talkNow;
	public:
		enum class State{
			none,
			talkPartIn,
			talkPartNow,
			talkPartOut,
		};
		State state = State::none;
		int NowPart = 0;
		int Mendoune = 0;
		int Kaisuu = 1;
		void create();
		void init();
		void start();
		void update();
		void draw();
		void drawbox();
		void talkout();
		bool talkend();
		
	};
}

