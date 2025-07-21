#include "Game.h"
#include "Pet.h"
#include "Timer.h"
#include "Input.h"
#include "Functions.h"
#include "Critter.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

void Game::UpdateTime(Game::Time time, void(*function)(int&, int), int modifier)
{
	switch (time)
	{
	case Game::Time::Seconds:		function(m_SecondsPassed, modifier);		break;
	case Game::Time::Minutes:		function(m_MinutesPassed, modifier);		break;
	case Game::Time::Hours:			function(m_HoursPassed, modifier);			break;
	case Game::Time::TotalSeconds:	function(m_TotalSecondsPassed, modifier);	break;
	case Game::Time::TotalMinutes:	function(m_TotalMinutesPassed, modifier);	break;
	case Game::Time::TotalHours:	function(m_TotalHoursPassed, modifier);		break;
	}
}
int Game::GetTime(Game::Time time)
{
	switch (time)
	{
	case Game::Time::Seconds:			return m_SecondsPassed;
	case Game::Time::Minutes:			return m_MinutesPassed;
	case Game::Time::Hours:				return m_HoursPassed;
	case Game::Time::TotalSeconds:		return m_TotalSecondsPassed;
	case Game::Time::TotalMinutes:		return m_TotalMinutesPassed;
	case Game::Time::TotalHours:		return m_TotalHoursPassed;
	}
}
void Game::SetToggle(Game::Toggle toggle, bool set)
{
	switch (toggle)
	{
	case Game::Toggle::Second:	m_secondTick = set;		break;
	case Game::Toggle::Minute:	m_minuteTick = set;		break;
	case Game::Toggle::Hour:	m_hourTick = set;		break;
	case Game::Toggle::Play:	m_playCooldown = set;	break;
	case Game::Toggle::Feed:	m_feedCooldown = set;	break;
	case Game::Toggle::Wash:	m_washCooldown = set;	break;
	}
}
bool Game::GetToggle(Game::Toggle toggle)
{
	switch (toggle)
	{
	case Game::Toggle::Second:	return m_secondTick;
	case Game::Toggle::Minute:	return m_minuteTick;
	case Game::Toggle::Hour:	return m_hourTick;
	case Game::Toggle::Play:	return m_playCooldown;
	case Game::Toggle::Feed:	return m_feedCooldown;
	case Game::Toggle::Wash:	return m_washCooldown;
	}
}
Game::State Game::GetState()
{
	return m_state;
}
void Game::ChangeState(Game::State state)
{
	m_state = state;
}
void Game::UpdateState()
{
	m_input.GetInput();
	switch (m_input.GetKey())
	{
	case 'g':	ChangeState(Game::State::Game);			break;
	case 'p':	ChangeState(Game::State::Playing);		break;
	case 'f':	ChangeState(Game::State::Feeding);		break;
	case 'w':	ChangeState(Game::State::Washing);		break;
	case 'r':	ChangeState(Game::State::Fighting);		break;
	case 's':	ChangeState(Game::State::Stats);		break;
	case 'm':	ChangeState(Game::State::Menu);			break;
	}
}
void Game::PlayPet()
{
	if (!GetToggle(Game::Toggle::Play))
	{
		std::cout << "[A] to Play with pet." << '\n';
		if (m_input.GetKey() == 'a')
		{
			m_pet.AdjustValue(Pet::Value::Mood, Funct::RaiseValue, m_PlayValue);
			m_pet.AdjustValue(Pet::Value::Mood, Funct::MaxValue, m_pet.GetLimit(Pet::Limit::MaxMood));
			SetToggle(Game::Toggle::Play, true);
		}
	}
	else
	{
		std::cout << "Playing on cooldown" << '\n';
	}
}
void Game::FeedPet()
{
	if (!GetToggle(Game::Toggle::Feed))
	{
		std::cout << "[A] to Feed pet" << '\n';
		if (m_input.GetKey() == 'a')
		{
			m_pet.AdjustValue(Pet::Value::Hunger, Funct::RaiseValue, m_FoodValue);
			m_pet.AdjustValue(Pet::Value::Hunger, Funct::MaxValue, m_pet.GetLimit(Pet::Limit::MaxHunger));
			SetToggle(Game::Toggle::Feed, true);
		}
	}
	else
	{
		std::cout << "Feeding on cooldown" << '\n';
	}
}
void Game::WashPet()
{
	if (!GetToggle(Game::Toggle::Wash))
	{
		std::cout << "[A] to Wash pet" << '\n';
		if (m_input.GetKey() == 'a')
		{
			m_pet.AdjustValue(Pet::Value::Hygiene, Funct::RaiseValue, m_WashValue);
			m_pet.AdjustValue(Pet::Value::Hygiene, Funct::MaxValue, m_pet.GetLimit(Pet::Limit::MaxHygiene));
			SetToggle(Game::Toggle::Wash, true);
		}
	}
	else
	{
		std::cout << "Washing on cooldown" << '\n';
	}
}
void Game::PetMinuteUpdates()
{
	if (GetToggle(Game::Toggle::Minute))
	{
		m_pet.AdjustValue(Pet::Value::Mood, Funct::LowerValue, m_MoodDecay);
		m_pet.AdjustValue(Pet::Value::Mood, Funct::MinValue, m_pet.GetLimit(Pet::Limit::MinMood));
		m_pet.AdjustValue(Pet::Value::Hunger, Funct::LowerValue, m_HungerDecay);
		m_pet.AdjustValue(Pet::Value::Hunger, Funct::MinValue, m_pet.GetLimit(Pet::Limit::MinHunger));
		m_pet.AdjustValue(Pet::Value::Hygiene, Funct::LowerValue, m_HygieneDecay);
		m_pet.AdjustValue(Pet::Value::Hygiene, Funct::MinValue, m_pet.GetLimit(Pet::Limit::MinHygiene));
		m_pet.AdjustValue(Pet::Value::Health, Funct::RaiseValue, m_HealthTick);
		m_pet.AdjustValue(Pet::Value::Health, Funct::MaxValue, m_pet.GetLimit(Pet::Limit::MaxHealth));
		m_pet.AdjustValue(Pet::Value::Energy, Funct::RaiseValue, m_EnergyTick);
		m_pet.AdjustValue(Pet::Value::Energy, Funct::MaxValue, m_pet.GetLimit(Pet::Limit::MaxEnergy));

	}
}
void Game::TickUpdate()
{
	if (m_timer.OneSecondPassed())
	{
		SetToggle(Game::Toggle::Second, true);
	}
	else
	{
		SetToggle(Game::Toggle::Second, false);
	}
	if (GetTime(Game::Time::Seconds) > 60)
	{
		SetToggle(Game::Toggle::Minute, true);
		UpdateTime(Game::Time::Seconds, Funct::SetValue, 1);
	}
	else
	{
		SetToggle(Game::Toggle::Minute, false);
	}
	if (GetTime(Game::Time::Minutes) > 60)
	{
		SetToggle(Game::Toggle::Hour, true);
		UpdateTime(Game::Time::Minutes, Funct::SetValue, 1);
	}
	else
	{
		SetToggle(Game::Toggle::Hour, false);
	}
}
void Game::TimerUpdate()
{
	if (GetToggle(Game::Toggle::Second))
	{
		UpdateTime(Game::Time::Seconds, Funct::RaiseValue, 1);
		UpdateTime(Game::Time::TotalSeconds, Funct::RaiseValue, 1);
	}
	if (GetToggle(Game::Toggle::Minute))
	{
		UpdateTime(Game::Time::Minutes, Funct::RaiseValue, 1);
		UpdateTime(Game::Time::TotalMinutes, Funct::RaiseValue, 1);
	}
	if (GetToggle(Game::Toggle::Hour))
	{
		UpdateTime(Game::Time::Hours, Funct::RaiseValue, 1);
		UpdateTime(Game::Time::TotalHours, Funct::RaiseValue, 1);
	}
}
void Game::CooldownUpdates()
{
	if (GetToggle(Game::Toggle::Minute))
	{
		SetToggle(Game::Toggle::Play, false);
		SetToggle(Game::Toggle::Feed, false);
		SetToggle(Game::Toggle::Wash, false);
	}
}
void Game::LevelPet()
{
	m_pet.AdjustValue(Pet::Value::Level, Funct::RaiseValue, 1);
	m_pet.AdjustValue(Pet::Value::Experience, Funct::SetValue, 0);
	m_pet.AdjustValue(Pet::Value::ExperienceCap, Funct::SetValue, (m_pet.GetValue(Pet::Value::Level) * 50));
	m_pet.AdjustValue(Pet::Value::StatPoints, Funct::SetValue, 1); 
	system("cls");
	std::cout << "You Leveled!\n";
	std::cout << "[" << m_pet.GetValue(Pet::Value::StatPoints) << "] Stat Point left\n";
	std::cout << "[A] Allocate Str\n";
	std::cout << "[I] Allocate Int\n";
	std::cout << "[H] Allocate Sta\n";
	while (m_pet.GetValue(Pet::Value::StatPoints) != 0)
	{
		m_input.GetInput();
		switch (m_input.GetKey())
		{
		case 'a':
			m_pet.AdjustValue(Pet::Value::Str, Funct::RaiseValue, 1);
			m_pet.AdjustValue(Pet::Value::StatPoints, Funct::LowerValue, 1);
			break;
		case 'i':
			m_pet.AdjustValue(Pet::Value::Int, Funct::RaiseValue, 1);
			m_pet.AdjustValue(Pet::Value::StatPoints, Funct::LowerValue, 1);
			//Energy Recovery Rate Adjustment
			break;
		case 'h':
			m_pet.AdjustValue(Pet::Value::Sta, Funct::RaiseValue, 1);
			m_pet.AdjustValue(Pet::Value::StatPoints, Funct::LowerValue, 1);
			//Health Recovery Rate Adjustment
			break;
		}
			
		//if (m_input.GetKey() == ' ') { Pressed = false; }
	}
	m_pet.AdjustValue(Pet::Value::MaxEnergy, Funct::SetValue, m_pet.GetLimit(Pet::Limit::MaxEnergy) + (m_pet.GetValue(Pet::Value::Int) * 2));
	m_pet.AdjustValue(Pet::Value::MaxHealth, Funct::SetValue, m_pet.GetLimit(Pet::Limit::MaxHealth) + (m_pet.GetValue(Pet::Value::Sta) * 2));
	m_HealthTick = m_HealthTick + m_pet.GetValue(Pet::Value::Sta);
	m_EnergyTick = m_EnergyTick + m_pet.GetValue(Pet::Value::Int);
	//system("cls");
	ChangeState(Game::State::Game);
}
void Game::SaveGame()
{
	std::ofstream outputFile("PetData.txt", std::ios::trunc);
	if (outputFile.is_open())
	{
		//Game Values
		outputFile << m_SecondsPassed << '\n';
		outputFile << m_TotalSecondsPassed << '\n';
		outputFile << m_MinutesPassed << '\n';
		outputFile << m_TotalMinutesPassed << '\n';
		outputFile << m_HoursPassed << '\n';
		outputFile << m_TotalHoursPassed << '\n';
		outputFile << m_secondTick << '\n';
		outputFile << m_minuteTick << '\n';
		outputFile << m_hourTick << '\n';
		outputFile << m_playCooldown << '\n';
		outputFile << m_feedCooldown << '\n';
		outputFile << m_washCooldown << '\n';
		//Pet Values
		outputFile << m_pet.GetValue(Pet::Value::Health) << '\n';
		outputFile << m_pet.GetLimit(Pet::Limit::MaxHealth) << '\n';
		outputFile << m_pet.GetValue(Pet::Value::Energy) << '\n';
		outputFile << m_pet.GetLimit(Pet::Limit::MaxEnergy) << '\n';
		outputFile << m_pet.GetValue(Pet::Value::Mood) << '\n';
		outputFile << m_pet.GetValue(Pet::Value::Hunger) << '\n';
		outputFile << m_pet.GetValue(Pet::Value::Hygiene) << '\n';
		outputFile << m_pet.GetValue(Pet::Value::Str) << '\n';
		outputFile << m_pet.GetValue(Pet::Value::Int) << '\n';
		outputFile << m_pet.GetValue(Pet::Value::Sta) << '\n';
		outputFile << m_pet.GetValue(Pet::Value::Level) << '\n';
		outputFile << m_pet.GetValue(Pet::Value::Experience) << '\n';
		outputFile << m_pet.GetLimit(Pet::Limit::ExperienceCap) << '\n';
	}
	outputFile.close();
}
void Game::LoadGame()
{
	std::ifstream inputFile("PetData.txt");
	if (inputFile.is_open())
	{
		int SP{ 0 }, TSP{ 0 }, MP{ 0 }, TMP{ 0 }, HP{ 0 }, THP{ 0 };
		bool ST{ 0 }, MT{ 0 }, HT{ 0 }, PC{ 0 }, FC{ 0 }, WC{ 0 };
		//Pet Values
		int PtH{ 0 }, PtMH{ 0 }, PtE{ 0 }, PtME{ 0 }, PtMo{ 0 }, PtHu{ 0 }, PtHy{ 0 }, PtSTR{ 0 }, PtINT{ 0 }, PtSTA{ 0 };
		int PLVL{ 0 }, PEXP{ 0 }, PEXPC{ 0 };
		std::string line{};
		while (std::getline(inputFile, line))
		{
			if (!SP)
			{
				m_SecondsPassed = std::stoi(line);
				SP = 1;
			}
			else if(!TSP)
			{
				m_TotalSecondsPassed = std::stoi(line);
				TSP = 1;
			}
			else if (!MP)
			{
				m_MinutesPassed = std::stoi(line);
				MP = 1;
			}
			else if (!TMP)
			{
				m_TotalMinutesPassed = std::stoi(line);
				TMP = 1;
			}
			else if (!HP)
			{
				m_HoursPassed = std::stoi(line);
				HP = 1;
			}
			else if (!THP)
			{
				m_TotalHoursPassed = std::stoi(line);
				THP = 1;
			}
			else if (!ST)
			{
				m_secondTick = std::stoi(line);
				ST = 1;
			}
			else if (!MT)
			{
				m_minuteTick = std::stoi(line);
				MT = 1;
			}
			else if (!HT)
			{
				m_hourTick = std::stoi(line);
				HT = 1;
			}
			else if (!PC)
			{
				m_playCooldown = std::stoi(line);
				PC = 1;
			}
			else if (!FC)
			{
				m_feedCooldown = std::stoi(line);
				FC = 1;
			}
			else if (!WC)
			{
				m_washCooldown = std::stoi(line);
				WC = 1;
			}
			else if (!PtH)
			{
				m_pet.AdjustValue(Pet::Value::Health, Funct::SetValue, std::stoi(line));
				PtH = 1;
			}
			else if (!PtMH)
			{
				m_pet.AdjustValue(Pet::Value::MaxHealth, Funct::SetValue, std::stoi(line));
				PtMH = 1;
			}
			else if (!PtE)
			{
				m_pet.AdjustValue(Pet::Value::Energy, Funct::SetValue, std::stoi(line));
				PtE = 1;
			}
			else if (!PtME)
			{
				m_pet.AdjustValue(Pet::Value::MaxEnergy, Funct::SetValue, std::stoi(line));
				PtME = 1;
			}
			else if (!PtMo)
			{
				m_pet.AdjustValue(Pet::Value::Mood, Funct::SetValue, std::stoi(line));
				PtMo = 1;
			}
			else if (!PtHu)
			{
				m_pet.AdjustValue(Pet::Value::Hunger, Funct::SetValue, std::stoi(line));
				PtHu = 1;
			}
			else if (!PtHy)
			{
				m_pet.AdjustValue(Pet::Value::Hygiene, Funct::SetValue, std::stoi(line));
				PtHy = 1;
			}
			else if (!PtSTR)
			{
				m_pet.AdjustValue(Pet::Value::Str, Funct::SetValue, std::stoi(line));
				PtSTR = 1;
			}
			else if (!PtINT)
			{
				m_pet.AdjustValue(Pet::Value::Int, Funct::SetValue, std::stoi(line));
				PtINT = 1;
			}
			else if (!PtSTA)
			{
				m_pet.AdjustValue(Pet::Value::Sta, Funct::SetValue, std::stoi(line));
				PtSTA = 1;
			}
			else if (!PLVL)
			{
				m_pet.AdjustValue(Pet::Value::Level, Funct::SetValue, std::stoi(line));
				PLVL = 1;
			}
			else if (!PEXP)
			{
				m_pet.AdjustValue(Pet::Value::Experience, Funct::SetValue, std::stoi(line));
				PEXP = 1;
			}
			else if (!PEXPC)
			{
				m_pet.AdjustValue(Pet::Value::ExperienceCap, Funct::SetValue, std::stoi(line));
				PEXPC = 1;
			}
		}
	}
	inputFile.close();
}
void Game::RunGame()
{
	LoadGame();
	std::cout << "Controls" << '\n';
	std::cout << "[G] Game Screen" << '\n';
	std::cout << "[P] Play Screen" << '\n';
	std::cout << "[F] Feed Screen" << '\n';
	std::cout << "[W] Wash Screen" << '\n';
	std::cout << "[R] Battle Screen" << '\n';
	std::cout << "[S] Stat Screen" << '\n';
	std::cout << "[M] Menu Screen" << '\n';
	ChangeState(Game::State::Game);
	while (m_state != Game::State::Quit)
	{
		TickUpdate();
		TimerUpdate();
		CooldownUpdates();
		PetMinuteUpdates();
		m_pet.UpdateStates();
		UpdateState();
		//Display current State Screen
		//Gameloop
		if (m_keyLast != m_input.GetKey())
		{
			m_keyLast = m_input.GetKey();
			system("cls");
			switch (m_state)
			{
			case Game::State::Game:
				std::cout << "[Game]" << '\n';
				std::cout << "Pet Health: " << m_pet.GetValue(Pet::Value::Health) << '\n';
				std::cout << "Pet Energy: " << m_pet.GetValue(Pet::Value::Energy) << '\n';
				std::cout << "Pet mood is: " << m_pet.StateToString(Pet::Value::Mood) << '\n';
				std::cout << "Pet Hunger is: " << m_pet.StateToString(Pet::Value::Hunger) << '\n';
				std::cout << "Pet Hygiene is: " << m_pet.StateToString(Pet::Value::Hygiene) << '\n';
				std::cout << "[M] Menu Screen" << '\n';
				break;
			case Game::State::Playing:
				std::cout << "[Play]" << '\n';
				PlayPet();
				//if(m_input.GetKey() == 'a') ChangeState(Game::State::Game);
				std::cout << "Pet mood is: " << m_pet.StateToString(Pet::Value::Mood) << '\n';
				std::cout << "Mood level: " << m_pet.GetValue(Pet::Value::Mood) << '\n';
				std::cout << "[M] Menu Screen" << '\n';
				break;
			case Game::State::Feeding:
				std::cout << "[Feed]" << '\n';
				FeedPet();
				//if (m_input.GetKey() == 'a') ChangeState(Game::State::Game);
				std::cout << "Pet Hunger is: " << m_pet.StateToString(Pet::Value::Hunger) << '\n';
				std::cout << "Hunger level: " << m_pet.GetValue(Pet::Value::Hunger) << '\n';
				std::cout << "[M] Menu Screen" << '\n';
				break;
			case Game::State::Washing:
				std::cout << "[Wash]" << '\n';
				WashPet();
				//if (m_input.GetKey() == 'a') ChangeState(Game::State::Game);
				std::cout << "Pet Hygiene is: " << m_pet.StateToString(Pet::Value::Hygiene) << '\n';
				std::cout << "Hygiene level: " << m_pet.GetValue(Pet::Value::Hygiene) << '\n';
				std::cout << "[M] Menu Screen" << '\n';
				break;
			case Game::State::Fighting:
				std::cout << "[Fighting]" << '\n';
				std::cout << "[A] To Battle Critters\n";
				if (m_pet.GetValue(Pet::Value::Health) <= 10)
				{
					std::cout << "Pet too weak to battle\n";
				}
				else if (m_pet.GetValue(Pet::Value::Energy) <= 10)
				{
					std::cout << "Pet too weak to battle\n";
				}
				else
				{
					if (m_input.GetKey() == 'a')
					{
						CritterBattle();
						m_pet.AdjustValue(Pet::Value::Energy, Funct::LowerValue, m_BattleEnergy);
						m_pet.AdjustValue(Pet::Value::Energy, Funct::MinValue, 0);
						if (m_pet.GetValue(Pet::Value::Experience) >= m_pet.GetLimit(Pet::Limit::ExperienceCap))
						{
							LevelPet();
							system("cls");
							ChangeState(Game::State::Game);
							//m_level = false;
						}
					}
				}
				std::cout << "[M] Menu Screen" << '\n';
				break;
			case Game::State::Stats:
				std::cout << "Stats" << '\n';
				std::cout << "Level: " << m_pet.GetValue(Pet::Value::Level) << '\n';
				std::cout << "Exp: " << m_pet.GetValue(Pet::Value::Experience) << '\n';
				std::cout << "Exp Needed: " << m_pet.GetLimit(Pet::Limit::ExperienceCap) << '\n';
				std::cout << "Str: " << m_pet.GetValue(Pet::Value::Str) << '\n';
				std::cout << "Int: " << m_pet.GetValue(Pet::Value::Int) << '\n';
				std::cout << "Sta: " << m_pet.GetValue(Pet::Value::Sta) << '\n';
				std::cout << "Seconds: " << GetTime(Game::Time::Seconds) << " ";
				std::cout << "Minutes: " << GetTime(Game::Time::Minutes) << " ";
				std::cout << "Hours: " << GetTime(Game::Time::Hours) << '\n';
				std::cout << "[M] Menu Screen" << '\n';
				break;
			case Game::State::Menu:
				std::cout << "[Menu]" << '\n';
				std::cout << "Controls" << '\n';
				std::cout << "[G] Game Screen" << '\n';
				std::cout << "[P] Play Screen" << '\n';
				std::cout << "[F] Feed Screen" << '\n';
				std::cout << "[W] Wash Screen" << '\n';
				std::cout << "[R] Battle Screen" << '\n';
				std::cout << "[S] Stat Screen" << '\n';
				std::cout << "[Q] Save and Quit" << '\n';
				if (m_input.GetKey() == 'q')
				{
					SaveGame();
					ChangeState(Game::State::Quit);
				}
				break;
			case Game::State::Quit:
				break;
			}
		}
	}
	std::cout << "Closing Game" << '\n';
	system("pause");
}
void Game::CritterBattle()
{
	bool BattleOver = false;
	bool BattleOne = false;
	bool BattleTwo = false;
	bool BattleThree = false;
	Critter critter1{ m_pet.GetValue(Pet::Value::Level) };
	Critter critter2{ m_pet.GetValue(Pet::Value::Level) };
	Critter critter3{ m_pet.GetValue(Pet::Value::Level) };
	int ExpValue1{ critter1.GetValue(Critter::Value::Health) + critter1.GetValue(Critter::Value::Str) };
	int ExpValue2{ critter2.GetValue(Critter::Value::Health) + critter2.GetValue(Critter::Value::Str) };
	int ExpValue3{ critter3.GetValue(Critter::Value::Health) + critter3.GetValue(Critter::Value::Str) };
	std::cout << "Select a Critter to battle\n";
	std::cout << "[1] Critter One\n";
	std::cout << "Health: " << critter1.GetValue(Critter::Value::Health) << ' ' << "Str: " << critter1.GetValue(Critter::Value::Str) << '\n';
	std::cout << "[2] Critter Two\n";																								 
	std::cout << "Health: " << critter2.GetValue(Critter::Value::Health) << ' ' << "Str: " << critter1.GetValue(Critter::Value::Str) << '\n';
	std::cout << "[3] Critter Three\n";																								 
	std::cout << "Health: " << critter3.GetValue(Critter::Value::Health) << ' ' << "Str: " << critter1.GetValue(Critter::Value::Str) << '\n';
	while (BattleOver == false)
	{
		m_input.GetInput();
		if (m_input.GetKey() == '1')
		{
			while (critter1.GetValue(Critter::Value::Health) >= 0)
			{
				m_pet.AdjustValue(Pet::Value::Health, Funct::LowerValue, (critter1.GetValue(Critter::Value::Str) * 2));
				critter1.AdjustValue(Critter::Value::Health, Funct::LowerValue, (m_pet.GetValue(Pet::Value::Str) * 2));
			}
			BattleOver = true;
			BattleOne = true;
		}
		if (m_input.GetKey() == '2')
		{
			while (critter2.GetValue(Critter::Value::Health) >= 0)
			{
				m_pet.AdjustValue(Pet::Value::Health, Funct::LowerValue, (critter2.GetValue(Critter::Value::Str) * 2));
				critter2.AdjustValue(Critter::Value::Health, Funct::LowerValue, (m_pet.GetValue(Pet::Value::Str) * 2));
			}
			BattleOver = true;
			BattleTwo = true;
		}
		if (m_input.GetKey() == '3')
		{
			while (critter3.GetValue(Critter::Value::Health) >= 0)
			{
				m_pet.AdjustValue(Pet::Value::Health, Funct::LowerValue, (critter3.GetValue(Critter::Value::Str) * 2));
				critter3.AdjustValue(Critter::Value::Health, Funct::LowerValue, (m_pet.GetValue(Pet::Value::Str) * 2));
			}
			BattleOver = true;
			BattleThree = true;
		}
		
	}
	if (m_pet.GetValue(Pet::Value::Health) < 1)
	{
		std::cout << "You Lost the Battle\n";
		m_pet.AdjustValue(Pet::Value::Health, Funct::MinValue, 1);
		std::cout << "[G] or any key to return\n";
		system("pause");
		return;
	}
	if (BattleOne == true)
	{
		std::cout << "You Won the Battle\n";
		//Gain Exp = to Critter Health + Str
		m_pet.AdjustValue(Pet::Value::Experience, Funct::RaiseValue, ExpValue1);
	}
	
	if (BattleTwo == true)
	{
		std::cout << "You Won the Battle\n";
		//Gain Exp = to Critter Health + Str
		m_pet.AdjustValue(Pet::Value::Experience, Funct::RaiseValue, ExpValue2);
	}
	if (BattleThree == true)
	{
		std::cout << "You Won the Battle\n";
		//Gain Exp = to Critter Health + Str
		m_pet.AdjustValue(Pet::Value::Experience, Funct::RaiseValue, ExpValue3);
	}
	m_pet.AdjustValue(Pet::Value::Health, Funct::MinValue, 1);
	std::cout << "[G] or any key to return\n";
	system("pause");
}