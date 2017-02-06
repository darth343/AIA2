#include "Team.h"
#include "Melee.h"
#include "Ranged.h"
#include "Mage.h"
#include "Scout.h"
#include "Healer.h"
#include "Commander.h"
#include <string>

std::map<int, Team*> Team::Teams = {};

Team::Team()
{
}

Team::~Team()
{
}

float Team::GetTeamHealth()
{
	float health = 0;

	for (int i = 0; i < TeamComp["melee"].size(); ++i)
	{
		health += TeamComp["melee"][i]->GetHealth();
	}

	for (int i = 0; i < TeamComp["ranged"].size(); ++i)
	{
		health += TeamComp["ranged"][i]->GetHealth();
	}

	for (int i = 0; i < TeamComp["mage"].size(); ++i)
	{
		health += TeamComp["mage"][i]->GetHealth();
	}

	for (int i = 0; i < TeamComp["scout"].size(); ++i)
	{
		health += TeamComp["scout"][i]->GetHealth();
	}

	for (int i = 0; i < TeamComp["healer"].size(); ++i)
	{
		health += TeamComp["healer"][i]->GetHealth();
	}


	for (int i = 0; i < TeamComp["commander"].size(); ++i)
	{
		health += TeamComp["commander"][i]->GetHealth();
	}

	return health;
}

Vector3 Team::GetTeamPosition()
{

	for (int i = 0; i < TeamComp["melee"].size(); ++i)
	{
		position += TeamComp["melee"][i]->GetPosition();
	}

	for (int i = 0; i < TeamComp["ranged"].size(); ++i)
	{
		position += TeamComp["ranged"][i]->GetPosition();
	}

	for (int i = 0; i < TeamComp["mage"].size(); ++i)
	{
		position += TeamComp["mage"][i]->GetPosition();
	}

	for (int i = 0; i < TeamComp["scout"].size(); ++i)
	{
		position += TeamComp["scout"][i]->GetPosition();
	}

	for (int i = 0; i < TeamComp["healer"].size(); ++i)
	{
		position += TeamComp["healer"][i]->GetPosition();
	}


	for (int i = 0; i < TeamComp["commander"].size(); ++i)
	{
		position += TeamComp["commander"][i]->GetPosition();
	}

	return position;
}

void Team::TeamInit(int teamID, int numberofmelee, int numberofrange, int numberofmage, int numberofscout, int numberofhealer)
{
	this->teamID = teamID;
	Teams[teamID] = this;

	if (teamID == 1)
		position.Set(300, 200);
	else
		position.Set(-300, -200);

	defaultbase = position;

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

	for (int i = 0; i < numberofhealer; ++i)
	{
		if (teamID == 1)
		{
			TeamComp["healer"].push_back(Create::HealerCharacter("HealerBlue", teamID, position, Vector3(50, 50, 1)));
		}
		else
		{
			TeamComp["healer"].push_back(Create::HealerCharacter("HealerRed", teamID, position, Vector3(50, 50, 1)));
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

	if (teamID == 1)
		TeamComp["commander"].push_back(Create::CommanderCharacter("CommanderBlue", teamID, position, Vector3(50, 50, 1)));
	else
		TeamComp["commander"].push_back(Create::CommanderCharacter("CommanderRed", teamID, position, Vector3(50, 50, 1)));
}