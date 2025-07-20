#pragma once
#include "Pet.h"
#include "Timer.h"
#include "Input.h"

class Game
{
private:
	int m_TotalSecondsPassed{};
	int m_TotalMinutesPassed{};
	int m_TotalHoursPassed{};
	const int m_PlayValue{ 20 };
	const int m_FoodValue{ 20 };
	const int m_WashValue{ 20 };
	const int m_MoodDecay{ 5 };
	const int m_HungerDecay{ 5 };
	const int m_HygieneDecay{ 5 };
public:
	enum class Time
	{
		Seconds,
		Minutes,
		Hours,
		TotalSeconds,
		TotalMinutes,
		TotalHours
	};
	enum class Toggle
	{
		Second,
		Minute,
		Hour,
		Play,
		Feed,
		Wash
	};
	enum class State
	{
		Main,
		Game,
		Playing,
		Feeding,
		Washing,
		Fighting,
		Stats,
		Menu,
		Quit
	};
private:
	State m_state{};
	Pet m_pet{ "Pet" };
	Timer m_timer{};
	Input m_input{};
	int m_SecondsPassed{};
	int m_MinutesPassed{};
	int m_HoursPassed{};
	bool m_secondTick{};
	bool m_minuteTick{};
	bool m_hourTick{};
	bool m_playCooldown{};
	bool m_feedCooldown{};
	bool m_washCooldown{};
	char m_keyLast{};
	bool m_level{ true };
public:
	void UpdateTime(Game::Time time, void(*function)(int&, int), int modifier);
	int GetTime(Game::Time time);
	void SetToggle(Game::Toggle toggle, bool set);
	bool GetToggle(Game::Toggle toggle);
	Game::State GetState();
	void ChangeState(Game::State state);
	void UpdateState();
	void PlayPet();
	void FeedPet();
	void WashPet();
	void PetMinuteUpdates();
	void TickUpdate();
	void TimerUpdate();
	void CooldownUpdates();
	void SaveGame();
	void LoadGame();
	void RunGame();
	void LevelPet();
};