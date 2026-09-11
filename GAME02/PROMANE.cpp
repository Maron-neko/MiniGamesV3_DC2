#include "PROMANE.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/mathUtil.h"
#include "../../libOne/inc/window.h"
namespace GAME02 {
	void PROMANE::Init() {
		Time = 0;
		//Timer = 120;
		IsChangingState = false;
		ShotDelay = 0;
		Wave = 1;
		Stage = 1;
		Score = 0;
		Delay = 9;
		Hdelay = 12;
		BossState = NOPOP;
	}

	//Text全般。一部例外あり
	void PROMANE::TitleMainText() {
		fill(0, 0, 0);
		text("Title", 0, 50);
		textSize(50);
		text("PLAY", width / 2 - 50, 450);
		text("HARD", width / 2 - 50, 550);
		text("OPTION", width / 2 - 50, 650);
		text("WASD/矢印キー : 移動", 2, 975);
		text("SHIFTキー : 低速移動", 0, 1020);
		text("左クリック/SPACEキー : 射撃", 0, 1075);
		text(" Mキー : メニュー画面に戻る ", 1240, 50);
	}
	void PROMANE::PlayTexts() {
		fill(255, 255, 255);
		sprintf_s(buf, "Time %.0fs", Time);
		text(buf, 0, 50);
		//sprintf_s(m, "Timer %.0f", Timer);
		//text(m, 0, 350);
		text((let)"Score " + Score, 0, 100);
		text((let)"HighScore " + HighScore, 0, 150);
		text((let)"Delay " + ShotDelay, 0, 200);
		if (State == PLAY) {
			text("GameMode:Normal ", 0, 250);
		}
		if (State == HARD) {
			text("GameMode:HARD", 0, 250);
		}
		text((let)"Wave" + Wave, 0, 300);

	}
	void PROMANE::GameOverTexts() {
		fill(255, 0, 0);
		text("GameOver", 0, 50); textSize(50);
		sprintf_s(buf, "Time %.0fs", Time);
		text(buf, 0, 100);
		text((let)"Score " + Score, 0, 150);
		text((let)"HighScore " + HighScore, 0, 200);
		if (BossState == BOSSPOP) {
			text((let)"BossHp " + Boss.Hp, 0, 250);
		}
		text((let)"NextState " + NextState, 0, 300);
		text("Rキーでリトライ", 0, 1080);
	}
	void PROMANE::GameClearTexts() {
		rectMode(CENTER);
		fill(0, 255, 0);
		sprintf_s(buf,"Time %.0fs",Time);
		text(buf, 0, 50);
		strokeWeight(10);
		text((let)"Score " + Score, 0, 100);
		text((let)"HighScore " + HighScore, 0, 150);

		text("GameClear", width / 3, height / 3);
		text("ENTERでタイトルに戻る", width / 3, height / 2);
	}

	//Allとか書いてるけど一部は別
	void PROMANE::AllCreate() {
		Player.create();
		Boss.create();
		Background.create();
		Sound.create();
		Talk.create();
		for (int i = 0; i < ITEM_NUM; i++) {
			Item[i].create();
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			Bullet[i].create();
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			Ebullet[i].create();
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			Enemy[i].create();
		}
		for (int i = 0; i < ENEMY3_NUM; i++) {
			Enemy3[i].create();
		}
		for (int i = 0; i < ZIKINERAI_NUM; i++) {
			Zikinerai[i].create();
		}
		for (int i = 0; i < SHOT_POINT; i++) {
			Shotpoint[i].create();
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			Bbullet[i].create();
			Bbullet2[i].create();
		}

		HighScore = Save.loadscore();
	}
	bool PROMANE::AllDead() {
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (Enemy[i].Alive) {
				return false;
			}
		}
		for (int i = 0; i < ENEMY3_NUM; i++) {
			if (Enemy3[i].Alive) {
				return false;
			}
		}
		return true;
	}
	void PROMANE::AllInit() {
		Player.init();
		Boss.init();
		Talk.init();
		for (int i = 0; i < BULLET_NUM; i++) {
			Bullet[i].init();
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			Ebullet[i].init();
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			Bbullet[i].init();
			Bbullet2[i].init();
		}
		for (int i = 0; i < ZIKINERAI_NUM; i++) {
			Zikinerai[i].init();
		}
		for (int i = 0; i < SHOT_POINT; i++) {
			Shotpoint[i].init();
		}
		for (int i = 0; i < ITEM_NUM; i++) {
			Item[i].init();
		}

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			bool retry;
			do
			{
				retry = false;
				Enemy[i].init();

				for (int j = 0; j < i; j++)
				{
					if (Enemy[i].hit(Enemy[j]))
					{
						retry = true;
						break;
					}
				}
			} while (retry);
		}
		bool retry;
		for (int i = 0; i < ENEMY3_NUM; i++)
		{
			do
			{
				retry = false;
				Enemy3[i].init();
				for (int j = 0; j < i; j++)
				{
					if (Enemy3[i].hit(Enemy3[j]))
					{
						retry = true;
						break;
					}
				}
				if (!retry) {
					for (int e = 0; e < ENEMY_NUM; e++)
					{
						if (Enemy3[i].hit(Enemy[e]))
						{
							retry = true;
							break;
						}
					}
				}
			} while (retry);
		}
		/*for (int i = 0; i < ENEMY3_NUM; i++)
		{
			bool retry;
			do
			{
				retry = false;
				Enemy3[i].init();

				for (int j = 0; j < i; j++)
				{
					if (Enemy3[i].hit(Enemy3[j]))
					{
						retry = true;
						break;
					}
				}
			} while (retry);
		}*/
		Enemy->Buf = 0;
		Enemy3->Buf = 0;
		Init();
		GetCursorPos(&mouse);
		ClientToScreen(HWnd, &mouse);
		SetCursorPos(1280, 880);
	}
	void PROMANE::AllDraw() {
		Player.draw();
		Talk.draw();
		for (int i = 0; i < BULLET_NUM; i++) {
			Bullet[i].draw();
		}
		for (int i = 0; i < SHOT_POINT; i++) {
			Shotpoint[i].draw();
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			Ebullet[i].draw();
		}
		for (int i = 0; i < ZIKINERAI_NUM; i++) {
			Zikinerai[i].draw();
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			Bbullet[i].draw();
			Bbullet2[i].draw();
		}
		for (int i = 0; i < ITEM_NUM; i++) {
			Item[i].draw();
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (!Enemy[i].Alive) {
				continue;
			}
			Enemy[i].draw();
		}
		for (int i = 0; i < ENEMY3_NUM; i++) {
			if (!Enemy3[i].Alive) {
				continue;
			}
			Enemy3[i].draw();
		}
		Fade.draw();
	}
	void PROMANE::AllUpdate(){
		if (State == PLAY) {
			Player.update();
		}
		if (State == HARD) {
			Player.hardupdate();
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			Bullet[i].update();
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			Ebullet[i].update();
		}
		for (int i = 0; i < ZIKINERAI_NUM; i++) {
			Zikinerai[i].update();
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			Bbullet[i].update();
			Bbullet2[i].update();
		}
		for (int i = 0; i < ITEM_NUM; i++) {
			Item[i].update();
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (!Enemy[i].Alive) {
				continue;
			}
			Enemy[i].update();
		}
		for (int i = 0; i < ENEMY3_NUM; i++) {
			if (!Enemy3[i].Alive) {
				continue;
			}
			Enemy3[i].update();
		}
		Fade.update();
		Talk.update();
		Time+=DeltaTime;
		//Timer -= DeltaTime;
	}


	//当たり判定とスコアとウェーブ
	void PROMANE::Hits() {

		//自分の弾が敵に当たったら
		for (int b = 0; b < BULLET_NUM; b++)
		{
			if (!Bullet[b].Alive)
			{
				continue;
			}
			for (int e = 0; e < ENEMY_NUM; e++)
			{
				if (!Enemy[e].Alive)
				{
					continue;
				}
				if (Bullet[b].hit(Enemy[e]))
				{
					Enemy[e].Hp--;
					if (Enemy[e].Hp == 0)
					{
						Enemy[e].Alive = false;
						if (State == PLAY) {
							Score += 1000;
						}
						else if (State == HARD) {
							Score += 1800;
						}
						if (Enemy[e].drop())
						{
							for (int i = 0; i < ITEM_NUM; i++)
							{
								if (!Item[i].Alive)
								{
									Item[i].set(Enemy[e].Px, Enemy[e].Py);
									break;
								}
							}
						}
					}
					Bullet[b].Alive = false;
					ShotCount--;

				}

			}

		}
		for (int b = 0; b < BULLET_NUM; b++)
		{
			if (!Bullet[b].Alive)
			{
				continue;
			}
			for (int e = 0; e < ENEMY3_NUM; e++)
			{
				if (!Enemy3[e].Alive)
				{
					continue;
				}
				if (Bullet[b].hit(Enemy3[e]))
				{
					Enemy3[e].Hp--;
					if (Enemy3[e].Hp == 0)
					{
						Enemy3[e].Alive = false;
						if (State == PLAY) {
							Score += 1000;
						}
						else if (State == HARD) {
							Score += 1800;
						}
						if (Enemy3[e].drop())
						{
							for (int i = 0; i < ITEM_NUM; i++)
							{
								if (!Item[i].Alive)
								{
									Item[i].set(Enemy3[e].Px, Enemy3[e].Py);
									break;
								}
							}
						}
					}
					Bullet[b].Alive = false;
					ShotCount--;

				}

			}

		}
		//敵本体に当たったら
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (Enemy[i].Alive) {
				if (Player.hit(Enemy[i])) {
					Sound.gameoversound();
					Save.savescore(Score);
					if (State == PLAY) {
						State = GAMEOVER;
					}
					else if (State == HARD) {
						State = HARDOVER;
					}
				}
			}
		}
		for (int i = 0; i < ENEMY3_NUM; i++) {
			if (Enemy3[i].Alive) {
				if (Player.hit(Enemy3[i])) {
					Sound.gameoversound();
					Save.savescore(Score);
					if (State == PLAY) {
						State = GAMEOVER;
					}
					else if (State == HARD) {
						State = HARDOVER;
					}
				}
			}
		}
		//敵弾と自分
		for (int i = 0; i < BULLET_ENUM; i++) {
			if (Ebullet[i].Alive) {
				if (Ebullet[i].hit(Player)) {
					Save.savescore(Score);
					Sound.gameoversound();
					if (State == PLAY) {
						State = GAMEOVER;
					}
					else if (State == HARD) {
						State = HARDOVER;
					}
				}
			}
		}
		for (int i = 0; i < ZIKINERAI_NUM; i++) {
			if (Zikinerai[i].Alive) {
				if (Zikinerai[i].hit(Player)) {
					Save.savescore(Score);
					Sound.gameoversound();
					if (State == PLAY) {
						State = GAMEOVER;
					}
					else if (State == HARD) {
						State = HARDOVER;
					}
				}
			}
		}
		//アイテム
		for (int i = 0; i < ITEM_NUM; i++) {
			if (Item[i].Alive) {
				if (Item[i].hit(Player)) {
					Sound.getitemsound();
					Item[i].Alive = false;
					if (State == PLAY) {
						if (Player.Shotlevel < 4) {
							Player.Shotlevel++;
						}
						else if (Player.Shotlevel >= 4 && ShotDelay > 1) {
							Delay -= 0.5f;
						}
					}
					if (State == HARD) {
						if (Player.Shotlevel < 4) {
							Player.Shotlevel++;
						}
						else if (Player.Shotlevel >= 4 && ShotDelay > 1) {
							Hdelay -= 0.5f;
						}
					}

				}
			}
		}
		//ボス
		for (int i = 0; i < BULLET_BNUM; i++) {
			if (Bbullet[i].Alive) {
				if (Bbullet[i].hit(Player)) {
					Save.savescore(Score);
					Sound.gameoversound();
					if (State == PLAY) {
						State = GAMEOVER;
					}
					else if (State == HARD) {
						State = HARDOVER;
					}
				}
			}
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			if (Bbullet2[i].Alive) {
				if (Bbullet2[i].hit(Player)) {
					Save.savescore(Score);
					Sound.gameoversound();
					if (State == PLAY) {
						State = GAMEOVER;
					}
					else if (State == HARD) {
						State = HARDOVER;
					}
				}
			}
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			if (Bullet[i].Alive) {
				if (Boss.hit(Bullet[i])) {
					Bullet[i].Alive = false;
				}
			}
		}
	}
	void PROMANE::Waves() {
		if (Wave > 0) {
			if (AllDead()) {
				Wave -= 1;
				Enemy->Buf += 5;
				for (int i = 0; i < ENEMY_NUM; i++)
				{
					if (Wave == 0) {
						break;
					}
					bool retry;
					do
					{
						retry = false;
						Enemy[i].init();

						for (int j = 0; j < i; j++)
						{
							if (Enemy[i].hit(Enemy[j]))
							{
								retry = true;
								break;
							}
						}

					} while (retry);
					Enemy[i].Hp += Enemy->Buf;
					if (Enemy[i].Delay > 10) {
						Enemy[i].Delay -= 2;
					}
				}

				Enemy3->Buf += 5;
				for (int i = 0; i < ENEMY3_NUM; i++)
				{
					if (Wave == 0) {
						break;
					}
					bool retry;
					do
					{
						retry = false;
						Enemy3[i].init();

						for (int j = 0; j < i; j++)
						{
							if (Enemy3[i].hit(Enemy3[j]))
							{
								retry = true;
								break;
							}
						}
						if (!retry) {
							for (int e = 0; e < ENEMY_NUM; e++) {
								if (Enemy3[i].hit(Enemy[e]))
								{
									retry = true;
									break;
								}
							}
						}
					
					} while (retry);
					Enemy3[i].Hp += Enemy3->Buf;
					if (Enemy3[i].Delay > 10) {
						Enemy3[i].Delay -= 2;
					}
				}
			}
		}
	}

	//ボスの弾
	void PROMANE::Bossshot() {
		if (Boss.Delay <= 0)
		{
			if (Player.ControlMode[1] == 1)
			{
				static float offset = 0;
				for (int i = 0; i < 16; i++)
				{
					float angle = (360.0f / 16.0f) * i + offset;
					Deg[0] = angle;
					Deg[0] += 1;
					float Vx = Sin(Deg[0]) * 3;
					float Vy = -Cos(Deg[0]) * 3;
					for (int j = 0; j < BULLET_BNUM; j++)
					{
						if (!Bbullet[j].Alive)
						{
							Bbullet[j].set(Boss.Px, Boss.Py, Vx, Vy);
							offset += 1;
							break;
						}

					}
				}
				if (Boss.Hp < 2500)
				{
					if (Player.ControlMode[1] == 1)
					{
						static float offset = 0;
						for (int i = 0; i < 4; i++)
						{
							float angle = (360.0f / 4.0f) * i + offset;
							Deg[1] = angle;
							Deg[1] += 1;
							float Vx = Sin(Deg[1]) * 4;
							float Vy = -Cos(Deg[1]) * 4;
							for (int j = 0; j < BULLET_BNUM; j++)
							{
								if (!Bbullet2[j].Alive)
								{
									Bbullet2[j].set(Boss.Px, Boss.Py, Vx, Vy);
									offset -= 3;
									break;
								}
							}
						}
					}
				}
				Boss.Delay = 28;
				if (Boss.Hp < 2500) {
					Boss.Delay = 26;
				}
			}
			if (Player.ControlMode[1] == 2) {
				static float offset = 0;
				for (int i = 0; i < 48; i++)
				{
					float angle = (360.0f / 48.0f) * i + offset;
					Deg[0] = angle;
					Deg[0] += 1;
					float Vx = Sin(Deg[0]) * 3;
					float Vy = -Cos(Deg[0]) * 3;
					for (int j = 0; j < BULLET_BNUM; j++)
					{
						if (!Bbullet[j].Alive)
						{
							Bbullet[j].set(Boss.Px, Boss.Py, Vx, Vy);
							offset += 1;
							break;
						}

					}
				}
				if (Boss.Hp < 2500) 
				{
					if (Player.ControlMode[1] == 2) 
					{
						static float offset = 0;
						for (int i = 0; i < 8; i++) 
						{
							float angle = (360.0f / 8.0f) * i + offset;
							Deg[1] = angle;
							Deg[1] += 1;
							float Vx = Sin(Deg[1]) * 4;
							float Vy = -Cos(Deg[1]) * 4;
							for (int j = 0; j < BULLET_BNUM; j++)
							{
								if (!Bbullet2[j].Alive)
								{
									Bbullet2[j].set(Boss.Px, Boss.Py, Vx, Vy);
									offset -= 3;
									break;

								}

							}
						}
					}
				}
				Boss.Delay = 28;
				if (Boss.Hp < 2500) {
					Boss.Delay = 26;
				}

			}
			if (State == HARD) {
				Boss.Delay = 23;
			}

		}
		Boss.Delay--;
	}

	//メイン処理群
	void PROMANE::TitleProcess() {
		showCursor();
		clear(255, 0, 255);
		Background.titledraw();
		TitleMainText();
		Fade.draw();
		//PLAY
		if (!IsChangingState) {
			if (MouseX > width / 2 - 50 && MouseX < width / 2 + 50 && MouseY > 400 && MouseY < 450) {
				fill(255, 255, 255);
				text("PLAY", width / 2 - 50, 450);
			}
			if (MouseX > width / 2 - 50 && MouseX < width / 2 + 50 && MouseY > 400 && MouseY < 450 && isTrigger(MOUSE_LBUTTON)) {
				Sound.clicksound();
				Fade.startFade();
				IsChangingState = true;
				NextState = PLAY;
			}

			//HARD
			if (MouseX > width / 2 - 50 && MouseX < width / 2 + 65 && MouseY > 500 && MouseY < 550) {
				fill(255, 255, 255);
				text("HARD", width / 2 - 50, 550);
			}
			if (MouseX > width / 2 - 50 && MouseX < width / 2 + 65 && MouseY > 500 && MouseY < 550 && isTrigger(MOUSE_LBUTTON))
			{
				Sound.clicksound();
				Fade.startFade();
				IsChangingState = true;
				NextState = HARD;
				
			}

			//OPTION
			if (MouseX > width / 2 - 50 && MouseX < width / 2 + 100 && MouseY > 600 && MouseY < 650) {
				fill(255, 255, 255);
				text("OPTION", width / 2 - 50, 650);
			}
			if (MouseX > width / 2 - 50 && MouseX < width / 2 + 100 && MouseY > 600 && MouseY < 650 && isTrigger(MOUSE_LBUTTON)) {
				Sound.clicksound();
				Fade.startFade();
				IsChangingState = true;
				NextState = OPTION;
			}
		}
		Fade.fadeoutonly();
		if (IsChangingState && Fade.fadeend())
		{
			if (NextState != OPTION) {
				AllInit();
				Sound.playsound();
			}
			Fade.show();
			IsChangingState = false;
			State = NextState;

		}
	}
	void PROMANE::OptionProcess() {
		Background.titledraw();
		text("Tでタイトルに戻る", 0, 100);
		text("操作をマウスにすると難易度が上がります(簡単すぎたので)", 0, 50);
		if (Choose[0] == 0) {
			text("低速移動:長押し", width / 2 - 150, 450);
			Player.ControlMode[0] = 1;
		}
		if (Choose[1] == 0) {
			text("操作モード:WASD/矢印キー", width / 2 - 150, 550);
		}
		if (Choose[2] == 0) {
			text("オーディオ:あり", 0, 1080);
		}
		if (MouseX > width / 2 - 150 && MouseX < width / 2 + 220 && MouseY > 400 && MouseY < 450 && Choose[0] == 0) {
			fill(255, 255, 255);
			text("低速移動:長押し", width / 2 - 150, 450);
		}


		if (MouseX > width / 2 - 150 && MouseX < width / 2 + 220 && MouseY > 400 && MouseY < 450 && isTrigger(MOUSE_LBUTTON)) {
			Sound.clicksound();
			Cur = 1;
			if (Choose[0] == 0)
				Choose[0] = 1;
		}
		if (MouseX > width / 2 - 150 && MouseX < width / 2 + 180 && MouseY > 500 && MouseY < 550 && isTrigger(MOUSE_LBUTTON)) {
			Sound.clicksound();
			Cur = 2;
			if (Choose[1] == 0)
				Choose[1] = 1;
		}
		if (MouseX < 375 && MouseY > 1030 && isTrigger(MOUSE_LBUTTON)) {
			Sound.clicksound();
			Cur = 3;
			if (Choose[2] == 0)
				Choose[2] = 1;
		}
		if (isTrigger(KEY_ENTER) || isTrigger(MOUSE_RBUTTON)) {
			Cur = 0;
		}
		if (Cur != 1) {
			fill(0, 0, 0);
			if (Choose[0] == 1) {
				text("低速移動:長押し", width / 2 - 150, 450);
			}
			if (Choose[0] == 2) {
				text("低速移動:切り替え", width / 2 - 150, 450);
			}
		}
		if (MouseX > width / 2 - 150 && MouseX < width / 2 + 220 && MouseY > 400 && MouseY < 450 && Choose[0] == 1) {
			fill(255, 255, 255);
			text("低速移動:長押し", width / 2 - 150, 450);
		}
		else if (MouseX > width / 2 - 150 && MouseX < width / 2 + 220 && MouseY > 400 && MouseY < 450 && Choose[0] == 2) {
			fill(255, 255, 255);
			text("低速移動:切り替え", width / 2 - 150, 450);
		}
		if (Cur == 1) {
			if (Choose[0] == 1) {
				fill(255, 0, 0);
				text("低速移動:長押し", width / 2 - 150, 450);
			}
			if (Choose[0] == 2) {
				fill(255, 0, 0);
				text("低速移動:切り替え", width / 2 - 150, 450);
			}
			if (Choose[0] == 1 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Player.ControlMode[0] = 2;
				Choose[0] = 2;
			}
			else if (Choose[0] == 2 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Player.ControlMode[0] = 1;
				Choose[0] = 1;
			}
		}
		if (Cur != 2) {
			fill(0, 0, 0);
			if (Choose[1] == 1) {
				text("操作モード:WASD/矢印キー", width / 2 - 150, 550);
			}
			if (Choose[1] == 2) {
				text("操作モード:マウス", width / 2 - 150, 550);
			}
		}
		//
		if (MouseX > width / 2 - 150 && MouseX < width / 2 + 180 && MouseY > 500 && MouseY < 550 && Choose[1] == 0) {
			fill(255, 255, 255);
			text("操作モード:WASD/矢印キー", width / 2 - 150, 550);
		}
		if (MouseX > width / 2 - 150 && MouseX < width / 2 + 180 && MouseY > 500 && MouseY < 550 && Choose[1] == 1) {
			fill(255, 255, 255);
			text("操作モード:WASD/矢印キー", width / 2 - 150, 550);
		}
		else if (MouseX > width / 2 - 150 && MouseX < width / 2 + 180 && MouseY > 500 && MouseY < 550 && Choose[1] == 2) {
			fill(255, 255, 255);
			text("操作モード:マウス", width / 2 - 150, 550);
		}
		if (Cur == 2) {
			if (Choose[1] == 1) {
				fill(255, 0, 0);
				text("操作モード:WASD/矢印キー", width / 2 - 150, 550);
			}
			if (Choose[1] == 2) {
				fill(255, 0, 0);
				text("操作モード:マウス", width / 2 - 150, 550);
			}
			if (Choose[1] == 1 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Player.ControlMode[1] = 2;
				Choose[1] = 2;
			}
			else if (Choose[1] == 2 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Player.ControlMode[1] = 1;
				Choose[1] = 1;
			}
		}
		if (Cur != 3) {
			fill(0, 0, 0);
			if (Choose[2] == 1) {
				text("オーディオ:あり", 0, 1080);
			}
			else if (Choose[2] == 2) {
				text("オーディオ:半分...かもしれないね", 0, 1080);
			}
			else if (Choose[2] == 3) {
				text("オーディオ:なし", 0, 1080);
			}
		}

		if (MouseX < 375 && MouseY > 1030 && Choose[2] == 0) {
			fill(255, 255, 255);
			text("オーディオ:あり", 0, 1080);
		}
		if (MouseX < 375 && MouseY > 1030 && Choose[2] == 1) {
			fill(255, 255, 255);
			text("オーディオ:あり", 0, 1080);
		}
		else if (MouseX < 375 && MouseY > 1030 && Choose[2] == 2) {
			fill(255, 255, 255);
			text("オーディオ:半分...かもしれないね", 0, 1080);
		}
		else if (MouseX < 375 && MouseY > 1030 && Choose[2] == 3) {
			fill(255, 255, 255);
			text("オーディオ:なし", 0, 1080);
		}
		if (Cur == 3) {
			if (Choose[2] == 1) {
				fill(255, 0, 0);
				text("オーディオ:あり", 0, 1080);
			}
			else if (Choose[2] == 2) {
				fill(255, 0, 0);
				text("オーディオ:半分...かもしれないね", 0, 1080);
			}
			else if (Choose[2] == 3) {
				fill(255, 0, 0);
				text("オーディオ:なし", 0, 1080);
			}
			if (Choose[2] == 1 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Sound.halfsound();
				Choose[2] = 2;
			}
			else if (Choose[2] == 2 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Sound.mutesound();
				Choose[2] = 3;
			}
			else if (Choose[2] == 3 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Sound.setsound();
				Choose[2] = 1;
			}
		}

		if (isTrigger(KEY_T)) {
			State = TITLE;
			Cur = 0;
		}
	}
	void PROMANE::PlayProcess() {
		hideCursor();
		HighScore = Save.loadscore();
		//////////////////////////////////////////////////////////////////////////////////////////////
		//更新と表示
		Background.draw();
		AllDraw();
		AllUpdate();
		
		//////////////////////////////////////////////////////////////////////////////////////////////
		//弾処理
		AmmoProcess();

		//////////////////////////////////////////////////////////////////////////////////////////////
		//当たったら～
		Hits();

		//////////////////////////////////////////////////////////////////////////////////////////////
		//ウェーブ
		Waves();

		//////////////////////////////////////////////////////////////////////////////////////////////
		

		Background.secdraw();
		PlayTexts();
		//ボス
		BossProcess();
	}
	void PROMANE::AmmoProcess() {
		ShotCount = 0;
		ShotPoint = 0;

		if (ShotDelay > 0) {
			ShotDelay--;
		}
		if (ShotDelay <= 0) {
			for (int i = 0; i < BULLET_NUM; i++)
			{
				if (!Bullet[i].Alive)
				{
					if (isPress(KEY_SPACE) || isPress(MOUSE_LBUTTON))
					{
						Bullet[i].shoot(Player.Px + offsetx[ShotCount], Player.Py + offsety[ShotCount]);
						ShotCount++;
						if (State == PLAY) {
							if (ShotCount >= Player.Shotlevel) {
								ShotDelay = Delay;
								break;
							}
						}
						else if (State == HARD) {
							if (ShotCount >= Player.Shotlevel) {
								ShotDelay = Hdelay;
								break;
							}
						}
					}
				}
			}
		}
		for (int e = 0; e < ENEMY_NUM; e++)
		{
			if (!Enemy[e].Alive) continue;

			if (Enemy[e].Delay <= 0)
			{
				for (int i = 0; i < BULLET_ENUM; i++)
				{
					if (!Ebullet[i].Alive)
					{
						
						if (State == PLAY) {
							if (Player.ControlMode[1] == 1) {
								Ebullet[i].shoot(Enemy[e].Px, Enemy[e].Py);
								Enemy[e].Delay = rand() % 40 + 40;
								break;
							}
							if (Player.ControlMode[1] == 2) {
								Ebullet[i].shoot(Enemy[e].Px, Enemy[e].Py);
								Enemy[e].Delay = rand() % 30 + 30;
								break;
							}
						}
						else if (State == HARD) {
							if (Player.ControlMode[1] == 1) {
								Ebullet[i].shoot(Enemy[e].Px, Enemy[e].Py);
								Enemy[e].Delay = rand() % 35 + 35;
								break;
							}
							if (Player.ControlMode[1] == 2) {
								Ebullet[i].shoot(Enemy[e].Px, Enemy[e].Py);
								Enemy[e].Delay = rand() % 25 + 25;
								break;
							}
						}

					}
				}
			}
			Enemy[e].Delay--;
		}
		for (int e = 0; e < ENEMY3_NUM; e++)
		{
			if (!Enemy3[e].Alive) continue;

			if (Enemy3[e].Delay <= 0)
			{
				for (int i = 0; i < ZIKINERAI_NUM; i++)
				{
					if (!Zikinerai[i].Alive)
					{
						if (State == PLAY) {
							if (Player.ControlMode[1] == 1) {
								Zikinerai[i].shoot(Player, Enemy3[e]);
								Enemy3[e].Delay = rand() % 130 + 130;
								break;
							}
							if (Player.ControlMode[1] == 2) {
								Zikinerai[i].shoot(Player, Enemy3[e]);
								Enemy3[e].Delay = rand() % 100 + 100;
								break;
							}
						}
						else if (State == HARD) {
							if (Player.ControlMode[1] == 1) {
								Zikinerai[i].shoot(Player, Enemy3[e]);
								Enemy3[e].Delay = rand() % 120 + 120;
								break;
							}
							if (Player.ControlMode[1] == 2) {
								Zikinerai[i].shoot(Player, Enemy3[e]);
								Enemy3[e].Delay = rand() % 90 + 90;
								break;
							}
						}
					}
				}
			}
			Enemy3[e].Delay--;
		}
		for (int i = 0; i < SHOT_POINT; i++) {
			Shotpoint[i].setPosition(Player.Px + offsetx[ShotPoint], Player.Py + offsety[ShotPoint]);
			ShotPoint++;
			if (ShotPoint >= Player.Shotlevel) {
				break;
			}
		}

		if (Player.Bom > 0 && isTrigger(KEY_B)) {
			for (int i = 0; i < BULLET_ENUM; i++) {
				Ebullet[i].Alive = false;
			}
		}

	}
	void PROMANE::BossProcess() {
		if (Wave == 0) {
			if (BossState == NOPOP) {
				Sound.playstopsound();
				Sound.bosssound();
				BossState = BOSSPOP;
			}
		}
		if (BossState==BOSSPOP) {
			//敵の弾消してからボス召喚
			for (int i = 0; i < BULLET_ENUM; i++) {
				Ebullet[i].Alive = false;
			}
			for (int i = 0; i < ZIKINERAI_NUM; i++) {
				Zikinerai[i].Alive = false;
			}
			Boss.draw();
			Boss.update();
			if (Boss.Cnt4 < 0) {
				Bossshot();
			}

		}
		if (Boss.Hp <= 0) {
			BossState = BOSSEND;
			if (Boss.Alive == true) {
				if (State == PLAY) {
					Score += 100000;
				}
				if (State == HARD) {
					Score += 200000;
				}
				Boss.Alive = false;
			}
			for (int i = 0; i < BULLET_BNUM; i++) {
				Bbullet[i].Alive = false;
			}
			for (int i = 0; i < BULLET_BNUM; i++) {
				Bbullet2[i].Alive = false;
			}
			if (Talk.Kaisuu == 1) {
				if (Talk.Mendoune == 0) {
					Save.savescore(Score);
					if (!Talk.talkend()) {
						if (BossState = BOSSEND) {
							Sound.bossStopSound();
							Player.ControlOut = true;
							Player.Px = width - width / 3;
							Player.Py = height - 400;
							Talk.start();
						}
						Talk.draw();
					}
					else if (Talk.talkend()) {
						if (!IsChangingState) {
							Fade.FadeSpeed = 2;
							Fade.startFade();
							IsChangingState = true;
						}
						Player.Py += Vy -= 0.1f;
						if (Player.Py <= -100 && IsChangingState) {
							IsChangingState = false;
							Fade.FadeSpeed = 0.5;
							Talk.talkout();
							AllInit();
							Sound.playsound();
							Stage = 1;
							State == PLAY;
						}
					}
				}
			}
		}
		if (isTrigger(KEY_T)) {
			Save.savescore(Score);
			Sound.playstopsound();
			State = TITLE;
		}

	}
	void PROMANE::GameOverProcess(){
		clear(0, 0, 0);
		HighScore = Save.loadscore();
		Background.gameoverdraw();
		Sound.bossStopSound();
		Sound.playstopsound();
		GameOverTexts();
		AllDraw();

		//すべて初期化してリトライ
		if (!IsChangingState) {
			if (isTrigger(KEY_R))
			{
				if (State == GAMEOVER)
				{
					NextState = PLAY;
				}
				else if (State == HARDOVER)
				{
					NextState = HARD;
				}

				Fade.startFade();

				IsChangingState = true;
			}
			if (isTrigger(KEY_T)) {
				State = TITLE;
			}
		}
		Fade.fadeoutonly();
		if (IsChangingState && Fade.fadeend())
		{
			AllInit();
			Background.Take = 0;
			State = NextState;
			Sound.playsound();
			Fade.show();
			IsChangingState = false;
		}
		
	}
	void PROMANE::GameClearProcess(){
		HighScore = Save.loadscore();
		Background.cleardraw();
		Sound.playstopsound();
		Sound.bossStopSound();
		GameClearTexts();
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
	}	
}