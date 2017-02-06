#include "Team.h"
#include "Melee.h"
#include "Ranged.h"
#include "Mage.h"
#include "Scout.h"
#include "Healer.h"
#include "Commander.h"
#include <string>

Team::Team()
{
}

Team::~Team()
{
}

void Team::TeamInit(int teamID, int numberofmelee, int numberofrange, int numberofmage, int numberofscout, int numberofhealer)
{
	this->teamID = teamID;
	Teams[teamID] = this;

	if (teamID == 1)
		position.Set(300, 200);
	else
		position.Set(-300, -200);
	for (int i = 0; i < numberofmelee; ++i)
	{
		if (teamID == 1)
		{
			TeamComp["melee"].push_back(Create::MeleeCharacter("MeleeBlue", teamID, position, Vector3(50, 50, 1)));
		}
		else
		{
			TeamComp["melee"].push_back(Create::MeleeCharacter("MeleeRed", teamID, position, Vector3(50, 50, 1)));
		}
	}

	for (int i = 0; i < numberofrange; ++i)
	{
		if (teamID == 1)
		{
			TeamComp["ranged"].push_back(Create::RangedCharacter("RangedBlue", teamID, position, Vector3(50, 50, 1)));
		}
		else
		{
			TeamComp["ranged"].push_back(Create::RangedCharacter("RangedRed", teamID, position, Vector3(50, 50, 1)));
		}
	}

	for (int i = 0; i < numberofmage; ++i)
	{
		if (teamID == 1)
		{
			//TeamComp["mage"].push_back(Create::MageCharacter("MageBlue", teamID, Vector3(), Vector3(50, 50, 1)));
		}
		else
		{
			//TeamComp["mage"].push_back(Create::MageCharacter("MageRed", teamID, Vector3(), Vector3(50, 50, 1)));
		}
	}

	for (int i = 0; i < numberofscout; ++i)
	{
		if (teamID == 1)
		{
			TeamComp["scout"].push_back(Create::ScoutCharacter("ScoutBlue", teamID, position, Vector3(50, 50, 1)));
		}
		else
		{
			TeamComp["scout"].push_back(Create::ScoutCharacter("ScoutRed", teamID, position, Vector3(50, 50, 1)));
		}
	}

}