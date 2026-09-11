#include "GAME02.h"
#include "../MAIN/MAIN.h"
#include "../../libOne/inc/input.h"
namespace GAME02
{
	int GAME::create()
	{
		Promane.AllCreate();
		return 0;
	}

	void GAME::Title() {
		Promane.TitleProcess();
	}
	void GAME::Option() {
		Promane.OptionProcess();
	}
	void GAME::Play() {
		Promane.PlayProcess();
	}
	void GAME::GameOver() {
		Promane.GameOverProcess();
	}

	void GAME::GameClear() {
		Promane.GameClearProcess();
	}

	void GAME::destroy()
	{

	}

	void GAME::proc()
	{
		//clear(255, 255, 255);
		if (isTrigger(KEY_M)) {
			main()->backToMenu();
		}
		if (Promane.State == Promane.TITLE) {
			Title();
		}
		else if (Promane.State == Promane.OPTION) {
			Option();
		}
		else if (Promane.State == Promane.PLAY) {
			Play();
		}
		else if (Promane.State == Promane.HARD) {
			Play();
		}
		
		else if (Promane.State == Promane.GAMEOVER) {
			GameOver();
		}
		else if (Promane.State == Promane.HARDOVER) {
			GameOver();
		}
		else if (Promane.State == Promane.CLEAR) {
			GameClear();
		}
		
	}

}