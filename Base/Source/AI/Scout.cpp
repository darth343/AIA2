#include "Scout.h"
#include "../EntityManager.h"
#include "../MessageBoard.h"
#include "Team.h"


CScout::CScout(const std::string& _modelMesh)
: CCharacter(_modelMesh)
{
	farRange = 70;
	nearRange = 45;
	SetType("scout");
	SetCharacter(true);
	Goal.Set(Math::RandFloatMinMax(-400, 400), Math::RandFloatMinMax(-300, 300));
}

CScout::~CScout()
{

}

void CScout::Update(double dt)
{
	RunFSM();
	Respond();
}

void CScout::Render()
{
	CCharacter::Render();
}

void CScout::RunFSM()
{
	CCharacter* nearestEnemy = GetNearestEnemy();

	if (nearestEnemy && state != RETREAT)
	{
		if ((position - nearestEnemy->GetPosition()).Length() - scale.x < nearRange)
		{
			if (nearestEnemy->GetType() == "scout")
			{
				//Message();
			}
			state = RETREAT;
			GoTo(base);
			Message("commander", "Found enemy here, help me!", this);
		}
	}

}

void CScout::SetBase(Vector3 pos)
{
	base = pos;
}

void CScout::Respond()
{
	switch (state)
	{
	case NIL:
		break;
	case ATTACK:
		break;
	case SCOUT:
		if ((position - Goal).Length() < 50)
		{
			std::cout << "Reached Dest" << std::endl;
			Goal.Set(Math::RandFloatMinMax(-400, 400), Math::RandFloatMinMax(-300, 300));
		}
		break;
	case RETREAT:
		break;
	}

	if ((Goal - position).Length() > 2)
	{
		position += (Goal - position).Normalize() * 2;
	}
}

void CScout::SetState(SSTATES _state)
{
	state = _state;
}

CScout* Create::ScoutCharacter(const std::string& _meshName,
	const int _teamID,
	const Vector3& _position,
	const Vector3& _scale)
{
	CScout* result = new CScout(_meshName);
	result->SetTeam(_teamID);
	result->SetPosition(_position);
	result->SetScale(_scale);

	result->SetHealth(100.f);
	result->SetState(CScout::SSTATES::SCOUT);
	EntityManager::GetInstance()->AddEntity(result, true);
	result->SetBase(Team::Teams[_teamID]->defaultbase);

	return result;
}