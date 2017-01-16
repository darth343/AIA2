#ifndef MESSAGEBOARD_H
#define MESSAGEBOARD_H
#include <vector>
#include <string>
#include "AI\CCharacter.h"

class MessageBoard
{
public:
	MessageBoard();
	~MessageBoard();
	static MessageBoard* GetInstance();
	void Add(CCharacter* source, const std::string& _message);
	void SetFontSize(int size);
	void Update();
	void Render();

private:
	static MessageBoard* m_instance;
	std::vector<std::string> mb;
	int fontSize;
	int ScrollOffsetY;
};

#endif