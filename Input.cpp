#include "Input.h"
#include <conio.h>


void Input::GetInput()
{
	if (_kbhit())
	{
		SetKey(_getch());
	}
}
char Input::GetKey()
{
	return m_key;
}
void Input::SetKey(char key)
{
	m_key = key;
}