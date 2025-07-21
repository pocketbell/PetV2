#include "Pet.h"


void Pet::AdjustValue(Value value, void(*function)(int&, int), int modifier)
{
	switch (value)
	{
	case Pet::Value::Health:		function(m_health,			modifier);	break;
	case Pet::Value::Energy:		function(m_energy,			modifier);	break;
	case Pet::Value::Mood:			function(m_mood,			modifier);	break;
	case Pet::Value::Hunger:		function(m_hunger,			modifier);	break;
	case Pet::Value::Hygiene:		function(m_hygiene,			modifier);	break;
	case Pet::Value::Str:			function(m_str,				modifier);	break;
	case Pet::Value::Int:			function(m_int,				modifier);	break;
	case Pet::Value::Sta:			function(m_sta,				modifier);	break;
	case Pet::Value::MaxHealth:		function(m_maxHealth,		modifier);	break;
	case Pet::Value::MaxEnergy:		function(m_maxEnergy,		modifier);	break;
	case Pet::Value::Level:			function(m_level,			modifier);	break;
	case Pet::Value::Experience:	function(m_experience,		modifier);	break;
	case Pet::Value::ExperienceCap:	function(m_experienceCap,   modifier);	break;
	case Pet::Value::StatPoints:	function(m_statPoints,	    modifier);	break;
	}
}
int Pet::GetValue(Value value)
{
	switch (value)
	{
	case Pet::Value::Health:			return m_health;
	case Pet::Value::Energy:			return m_energy;
	case Pet::Value::Mood:				return m_mood;
	case Pet::Value::Hunger:			return m_hunger;
	case Pet::Value::Hygiene:			return m_hygiene;
	case Pet::Value::Str:				return m_str;
	case Pet::Value::Int:				return m_int;
	case Pet::Value::Sta:				return m_sta;
	case Pet::Value::Level:				return m_level;
	case Pet::Value::Experience:		return m_experience;
	case Pet::Value::StatPoints:		return m_statPoints;
	}
}
int Pet::GetLimit(Limit limit)
{
	switch (limit)
	{
	case Pet::Limit::MaxMood:			return m_MaxMood;
	case Pet::Limit::MinMood:			return m_MinMood;
	case Pet::Limit::MaxHunger:			return m_MaxHunger;
	case Pet::Limit::MinHunger:			return m_MinHunger;
	case Pet::Limit::MaxHygiene:		return m_MaxHygiene;
	case Pet::Limit::MinHygiene:		return m_MinHygiene;
	case Pet::Limit::MaxHealth:			return m_maxHealth;
	case Pet::Limit::MaxEnergy:			return m_maxEnergy;
	case Pet::Limit::ExperienceCap:		return m_experienceCap;
	}
}
void Pet::SetMoodState()
{
	if		(m_mood > 80)		m_moodState = Pet::Mood::Happy;
	else if (m_mood > 60)		m_moodState = Pet::Mood::Okay;
	else if (m_mood > 40)		m_moodState = Pet::Mood::Aggravated;
	else if (m_mood > 0)		m_moodState = Pet::Mood::Sad;
}
void Pet::SetHungerState()
{
	if		(m_hunger > 80)		m_hungerState = Pet::Hunger::Full;
	else if (m_hunger > 60)		m_hungerState = Pet::Hunger::Fine;
	else if (m_hunger > 40)		m_hungerState = Pet::Hunger::Hungry;
	else if (m_hunger > 0)		m_hungerState = Pet::Hunger::Starving;
}
void Pet::SetHygieneState()
{
	if		(m_hygiene > 80)	m_hygieneState = Pet::Hygiene::Clean;
	else if (m_hygiene > 60)	m_hygieneState = Pet::Hygiene::Normal;
	else if (m_hygiene > 40)	m_hygieneState = Pet::Hygiene::Dirty;
	else if (m_hygiene > 0)		m_hygieneState = Pet::Hygiene::Filthy;
}
void Pet::UpdateStates()
{
	SetMoodState();
	SetHungerState();
	SetHygieneState();
}
std::string Pet::StateToString(Pet::Value value)
{
	switch (value)
	{
	case Pet::Value::Mood:
		if		(m_mood > 80)		 return "[Happy]";
		else if (m_mood > 60)		 return "[Okay]";
		else if (m_mood > 40)		 return "[Aggravated]";
		else if (m_mood > 0)		 return "[Sad]";
		break;						 
	case Pet::Value::Hunger:		 
		if		(m_hunger > 80)		 return "[Full]";
		else if (m_hunger > 60)		 return "[Fine]";
		else if (m_hunger > 40)		 return "[Hungry]";
		else if (m_hunger > 0)		 return "[Starving]";
		break;
	case Pet::Value::Hygiene:
		if		(m_hygiene > 80)	 return "[Clean]";
		else if (m_hygiene > 60)	 return "[Normal]";
		else if (m_hygiene > 40)	 return "[Dirty]";
		else if (m_hygiene > 0)		 return "[Filthy]";
		break;
	}
	return "NoVal";
}
Pet::Mood Pet::GetMood() { return m_moodState; }
Pet::Hunger Pet::GetHunger() { return m_hungerState; }
Pet::Hygiene Pet::GetHygiene() { return m_hygieneState; }

