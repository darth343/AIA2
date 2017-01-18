#ifndef TEAM_H
#define TEAM_H
#include "CCharacter.h"
#include <vector>

class Team
{
public:
	Team();
	~Team();
	std::vector<CCharacter*> MemberList;
};

#endif