#include "Ranged.h"
#include "../EntityManager.h"
#include "../MessageBoard.h"
#include "Commander.h"
#define EntityList EntityManager::GetInstance()->entityList

CRanged::CRanged(const std::string& _modelMesh)
: CCharacter(_modelMesh)
{
	farRange = 80;
	nearRange = 20;
	SetType("ranged");
	SetCharacter(true);
}

CRanged::~CRanged()
{

}

void CRanged::Update()
{
	RunFSM();
	Respond();
}

void CRanged::Render()
{
	CCharacter::Render();
}

void CRanged::RunFSM()
{

}

void CRanged::Respond()
{

}

void CRanged::SetState(STATES _state)
{
	state = _state;
}

void CRanged::MessageReceive(const std::string& message, CCharacter* _source)
{
	if (strcmp(message.c_str(), "Shoot Him!") == 0)
	{
		Message("commander", "Let's shoot him!", this);
	}
}

CRanged* Create::RangedCharacter(const std::string& _meshName,
	const int _teamID,
	const Vector3& _position,
	const Vector3& _scale)
{
	CRanged* result = new CRanged(_meshName);
	result->SetTeam(_teamID);
	result->SetPosition(_position);
	result->SetScale(_scale);

	result->SetHealth(100.f);
	result->SetState(CRanged::STATES::SHOOT);
	EntityManager::GetInstance()->AddEntity(result, true);
	return result;
}