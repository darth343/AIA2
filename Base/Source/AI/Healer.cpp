#include "Healer.h"
#include "../EntityManager.h"
#include "../MessageBoard.h"
#include "Melee.h"
#define EntityList EntityManager::GetInstance()->entityList

CHealer::CHealer(const std::string& _modelMesh)
: CCharacter(_modelMesh)
{
	farRange = 50;
	nearRange = 20;
	SetType("healer");
	SetCharacter(true);
}

CHealer::~CHealer()
{

}

void CHealer::Update()
{
	RunFSM();
	Respond();
}

void CHealer::Render()
{
	CCharacter::Render();
}

void CHealer::RunFSM()
{

}

void CHealer::Respond()
{

}

void CHealer::SetState(STATES _state)
{
	state = _state;
}

void CHealer::MessageReceive(const std::string& message, CCharacter* _source)
{
	if (strcmp(message.c_str(), "I am low on health, heal me!") == 0)
	{
		Message("melee", "I will heal you!", this);
		_source->AddHealth(30);
	}
}

CHealer* Create::HealerCharacter(const std::string& _meshName,
	const int _teamID,
	const Vector3& _position,
	const Vector3& _scale)
{
	CHealer* result = new CHealer(_meshName);
	result->SetTeam(_teamID);
	result->SetPosition(_position);
	result->SetScale(_scale);

	result->SetHealth(100.f);
	result->SetState(CHealer::STATES::HEAL);
	EntityManager::GetInstance()->AddEntity(result, true);
	return result;
}