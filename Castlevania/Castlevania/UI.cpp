#include "UI.h"



UI::UI(int x, int y)
{
	SetPosition(x, y);
	for (int i = 0; i < 6; i++) {
		Number * nb = new Number();
		nb->SetPosition(56 + i * 8, 11);
		Score_ani.push_back(nb);
	}
	UpDateNumber(Score_ani, FIRSTSCORE, Score);
	for (int i = 0; i < 4; i++) {
		Number * nb = new Number();
		nb->SetPosition(145 + i * 8, 11);
		Time_ani.push_back(nb);
	}
	UpDateNumber(Time_ani, FIRSTTIME/*Max time*/, Time);

	for (int i = 0; i < 2; i++) {
		Number * nb = new Number();
		nb->SetPosition(184 + i * 8, 22);
		LanDanhVuKhiDatBiet_ani.push_back(nb);
	}
	UpDateNumber(LanDanhVuKhiDatBiet_ani, FIRSTNUMBERATTACKING, NumberOfAttacking);
	for (int i = 0; i < 2; i++) {
		Number * nb = new Number();
		nb->SetPosition(184 + i * 8, 30);
		Life_ani.push_back(nb);
	}
	UpDateNumber(Life_ani, FIRSTLIFE, Life);
	for (int i = 0; i < 2; i++) {
		Number * nb = new Number();
		nb->SetPosition(230 + i * 8, 11);
		Stage_ani.push_back(nb);
	}
	UpDateNumber(Stage_ani, FIRSTSTAGE, Stage);
}
void UI::UpDateNumber(vector<Number*>&number, int num, int &ChaNum)
{
	ChaNum = num;
	for (int i = 0; i < number.size(); i++) {
		int temp = num % 10;
		number[number.size()-1-i]->SetValue(temp);
		num /= 10;
	}
}
void UI::Render(float camera_x, int SCREEN_WIDTH)
{

	animations[0]->Render(x, y+5);
	for (int i = 0; i < Score_ani.size(); i++) {
		Score_ani[i]->Render();
	}
	for (int i = 0; i < Time_ani.size(); i++) {
		Time_ani[i]->Render();
	}
	for (int i = 0; i < LanDanhVuKhiDatBiet_ani.size(); i++) {
		LanDanhVuKhiDatBiet_ani[i]->Render();
	}
	for (int i = 0; i < Life_ani.size(); i++) {
		Life_ani[i]->Render();
	}
	for (int i = 0; i < Stage_ani.size(); i++) {
		Stage_ani[i]->Render();
	}
}
void UI::Update(DWORD dt, int Score, int TurnAttack,int Life, int Stage, bool BigBatDie)
{
	bool First=false;
	if (!BigBatDie)
	{
		if (Stage != 0)
		{
			if (GetTickCount() - CurrentTime > 1000)
			{
				CurrentTime = GetTickCount();
				Time--;
				UpDateNumber(Time_ani, Time, Time);
			}
		}
	}
	else
	{
		if (BigBatDie)
		{
			if (GetTickCount() - CurrentTime > SCORE_MINUS_TIME)
			{
				if (Time > 0)
				{
					/*if (NumberOfAttacking < 0)
					{
						NumberOfAttacking = 0;
						this->Score -= 100;
					}*/
					CurrentTime = GetTickCount();
					Time--;
					//NumberOfAttacking--;
					this->Score += SCORE100;
					UpDateNumber(Time_ani, Time, Time);

				}
			}
			if (GetTickCount() - CurrentTime > NUMBERATTACKING_MINUS_TIME)
			{
				if (Time <= 0)
				{
				
					if (NumberOfAttacking > 0)
					{
						CurrentTime = GetTickCount();

						NumberOfAttacking--;
						this->Score += SCORE100;

						UpDateNumber(Time_ani, Time, Time);

					}
					

				}
			}

		}
	}

	this->NumberOfAttacking += TurnAttack;
	UpDateNumber(LanDanhVuKhiDatBiet_ani, this->NumberOfAttacking, this->NumberOfAttacking);
	
	this->Score += Score;
	UpDateNumber(Score_ani, this->Score, this->Score);

	this->Life = Life;
	UpDateNumber(Life_ani, this->Life, this->Life);

	this->Stage = Stage;
	UpDateNumber(Stage_ani, this->Stage, this->Stage);
}
void UI::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}
