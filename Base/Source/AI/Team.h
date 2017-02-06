#ifndef TEAM_H
#define TEAM_H
#include "CCharacter.h"
#include <string>
#include <vector>
#include <map>

class Team
{
public:
	Team();
	~Team();
	static std::map<int, Team*> Teams;
	int teamID;
	Vector3 position;
	Vector3 defaultbase;
	float GetTeamHealth();
	std::map<std::string, std::vector<CCharacter*>> TeamComp;
	void TeamInit(int teamID, int numberofmelee, int numberofrange, int numberofmage, int numberofscout, int numberofhealer);
};

#endif