#include "Melee.h"
#include "../EntityManager.h"
#include "../MessageBoard.h"

CMelee::CMelee(const std::string& _modelMesh)
: CCharacter(_modelMesh)
{
	farRange = 70;
	nearRange = 45;
	SetType("melee");
	SetCharacter(true);
}

CMelee::~CMelee()
{
	
}

void CMelee::Update(double dt)
{
	RunFSM();
	Respond();
}

void CMelee::Render()
{
	CCharacter::Render();
}

void CMelee::MessageReceive(const std::string& message, CCharacter* _source)
{

}

void CMelee::RunFSM()
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

void CMelee::Respond()
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

	Vector3 dis = (Goal - position);

	if (!dis.IsZero())
	position += dis.Normalize();
}

void CMelee::SetState(SSTATES _state)
{
	state = _state;
}

CMelee* Create::MeleeCharacter(const std::string& _meshName,
	const int _teamID,
	const Vector3& _position,
	const Vector3& _scale)
{
	CMelee* result = new CMelee(_meshName);
	result->SetTeam(_teamID);
	result->SetPosition(_position);
	result->SetScale(_scale);

	result->SetHealth(100.f);
	result->SetState(CMelee::SSTATES::NIL);
	EntityManager::GetInstance()->AddEntity(result, true);
	return result;
}