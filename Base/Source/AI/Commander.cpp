#include "Commander.h"
#include "../EntityManager.h"
#include "../MessageBoard.h"
#include "Melee.h"
#include "Ranged.h"
#include "Mtx44.h"
#include "Team.h"
#define EntityList EntityManager::GetInstance()->entityList

CCommander::CCommander(const std::string& _modelMesh)
: CCharacter(_modelMesh)
{
	farRange = 70;
	nearRange = 45;
	SetType("commander");
	SetCharacter(true);
}

CCommander::~CCommander()
{

}

void CCommander::Update(double dt)
{
	RunFSM(dt);
	Respond(dt);
}

void CCommander::Render()
{
	CCharacter::Render();
}


void CCommander::MessageReceive(const std::string& message, CCharacter* _source)
{
	if (message == "Found enemy here, help me!")
	{
		Message("melee", "Surround Him!", this);
		CCharacter* enemy = _source->GetNearestEnemy();
		Vector3 enemypos = enemy->GetPosition();
		for (int i = 0; i < Team::Teams[teamID]->TeamComp["melee"].size(); i++)
		{
			Vector3 pos = Vector3(80, 0, 0);
			Mtx44 Rotate;
			Rotate.SetToRotation(360.f / (float)(Team::Teams[teamID]->TeamComp["melee"].size()) * ((float)i + 1), 0, 0, 1);
			pos = Rotate * pos;

			Team::Teams[teamID]->TeamComp["melee"][i]->GoTo(pos + enemypos);
			static_cast<CMelee*>(Team::Teams[teamID]->TeamComp["melee"][i])->targetEnemy = enemy;
			static_cast<CMelee*>(Team::Teams[teamID]->TeamComp["melee"][i])->SetState(CMelee::SSTATES::SURROUND);
		}

		
		for (int i = 0; i < Team::Teams[teamID]->TeamComp["ranged"].size(); i++)
		{

			static_cast<CRanged*>(Team::Teams[teamID]->TeamComp["ranged"][i])->targetEnemy = enemy;

		}
		Message("ranged", "Shoot Him!", this);

	}
}

void CCommander::RunFSM(double dt)
{
	CCharacter* nearestEnemy = GetNearestEnemy();

	if (nearestEnemy && state != ATTACK)
	{
		if ((position - nearestEnemy->GetPosition()).Length() - scale.x < nearRange)
		{
			state = ATTACK;
		}
	}

}

void CCommander::Respond(double dt)
{
	switch (state)
	{
	case NIL:
		break;
	case ATTACK:
		break;
	case DEFEND:
		break;
	case RETREAT:
		break;
	}

	//position += (Goal - position).Normalize();
}

void CCommander::SetState(SSTATES _state)
{
	state = _state;
}

CCommander* Create::CommanderCharacter(const std::string& _meshName,
	const int _teamID,
	const Vector3& _position,
	const Vector3& _scale)
{
	CCommander* result = new CCommander(_meshName);
	result->SetTeam(_teamID);
	result->SetPosition(_position);
	result->SetScale(_scale);

	result->SetHealth(100.f);
	result->SetState(CCommander::SSTATES::NIL);
	EntityManager::GetInstance()->AddEntity(result, true);
	result->speed = 1;
	return result;
}