#pragma once
namespace GAME02 {
	
	class FADE
	{
	private:
		int Red = 0, Green = 0, Blue = 0, Alpha = 0;
	public:
		float FadeSpeed = 0.5;
		enum class FadeState {
			none,
			FadeIn,
			FadeOut,
		};
		FadeState State = FadeState::none;
		void fadein();
		void fadeout();
		void fadeoutonly();
		void draw();
		void startFade();
		void update();
		bool fadeend();
		void show();
	};
}

