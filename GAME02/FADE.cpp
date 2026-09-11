#include "FADE.h"
#include "../../libOne/inc/window.h"
#include "../../libOne/inc/graphic.h"
namespace GAME02 {
	void FADE::fadeout() {
		if (State == FadeState::FadeOut) {
			if (FadeSpeed >= 0.5) {
				Alpha += static_cast<int>(255.0f * DeltaTime / FadeSpeed);
				if (Alpha >= 255) {
					Alpha = 255;
					State = FadeState::FadeIn;
				}
			}
			else {
				Alpha += static_cast<int>(255.0f * DeltaTime);
				if (Alpha >= 255) {
					Alpha = 255;
					State = FadeState::FadeIn;
				}
			}
		}
	}
	void FADE::fadeoutonly() {
		if (State == FadeState::FadeOut) {
			if (FadeSpeed >= 0.5) {
				Alpha += static_cast<int>(255.0f * DeltaTime / FadeSpeed);
				if (Alpha >= 255) {
					Alpha = 255;
					State = FadeState::none;
				}
			}
			else {
				Alpha += static_cast<int>(255.0f * DeltaTime);
				if (Alpha >= 255) {
					Alpha = 255;
					State = FadeState::none;
				}
			}
		}
	}
	void FADE::fadein() {
		if (State == FadeState::FadeIn) {
			if (FadeSpeed >= 0.5) {
				Alpha -= static_cast<int>(255.0f * DeltaTime / FadeSpeed + 4);
				if (Alpha <= 0) {
					Alpha = 0;
					State = FadeState::none;
				}
			}
			else {
				Alpha -= static_cast<int>(255.0f * DeltaTime);
				if (Alpha <= 0) {
					Alpha = 0;
					State = FadeState::none;
				}
			}
		}
	}
	void FADE::update() {
		fadein();
		fadeout();
	}
	void FADE::show() {
		Alpha = 0;
	}
	void FADE::startFade() {
		State = FadeState::FadeOut;
	}
	bool FADE::fadeend() {
		return State == FadeState::none;
	}
	void FADE::draw() {
		colorMode(RGB);
		fill(Red, Green, Blue, Alpha);
		rectMode(CORNER);
		rect(0, 0, 1920, 1080, 0);
	}
}