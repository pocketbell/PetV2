#pragma once
#include <string>

class Pet
{
private:
	const int m_MaxMood{ 100 };
	const int m_MinMood{ 1 };
	const int m_MaxHunger{ 100 };
	const int m_MinHunger{ 1 };
	const int m_MaxHygiene{ 100 };
	const int m_MinHygiene{ 1 };
public:
	enum class Limit
	{
		MaxMood,
		MinMood,
		MaxHunger,
		MinHunger,
		MaxHygiene,
		MinHygiene,
		MaxHealth,
		MaxEnergy,
		ExperienceCap
	};
	enum class Value
	{
		Health,
		Energy,
		Mood,
		Hunger,
		Hygiene,
		Str,
		Int,
		Sta,
		MaxHealth,
		MaxEnergy,
		Level,
		Experience,
		ExperienceCap,
		StatPoints
	};
	enum class Mood
	{
		Happy,
		Okay,
		Aggravated,
		Sad
	};
	enum class Hunger
	{
		Full,
		Fine,
		Hungry,
		Starving
	};
	enum class Hygiene
	{
		Clean,
		Normal,
		Dirty,
		Filthy
	};
private:
	std::string m_name{};
	int m_health{ 50 };
	int m_maxHealth{ 100 };
	int m_energy{ 50 };
	int m_maxEnergy{ 100 };
	Mood m_moodState{};
	Hunger m_hungerState{};
	Hygiene m_hygieneState{};
	//State
	int m_mood{ 80 };
	int m_hunger{ 80 };
	int m_hygiene{ 80 };
	//Stat
	int m_level{ 1 };
	int m_experience{ 51 };
	int m_experienceCap{ 50 };
	int m_str{ 5 };
	int m_int{ 5 };
	int m_sta{ 5 };
	int m_statPoints{ 0 };
public:
	Pet(std::string name)
		: m_name(name) {};
	void AdjustValue(Value value, void(*function)(int&, int), int modifier);
	int GetValue(Value value);
	int GetLimit(Limit limit);
	void SetState(Value value, int state);
	std::string StateToString(Pet::Value value);
	void UpdateStates();
	Pet::Mood GetMood();
	Pet::Hunger GetHunger();
	Pet::Hygiene GetHygiene();
};