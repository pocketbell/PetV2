#pragma once

class Input
{
private:
	char m_key{};
public:
	void GetInput();
	char GetKey();
	void SetKey(char key);
};