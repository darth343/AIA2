#include "Melee.h"
#include "../EntityManager.h"

CMelee::CMelee(const std::string& _modelMesh)
: CCharacter(_modelMesh)
{
	
}

CMelee::~CMelee()
{
	
}

void CMelee::Update()
{
	RunFSM();
	Respond();
}

void CMelee::Render()
{
	CCharacter::Render();
}

void CMelee::RunFSM()
{
	
}

void CMelee::Respond()
{
	
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
	result->SetState(CMelee::SSTATES::DEFEND);
	EntityManager::GetInstance()->AddEntity(result, true);
	return result;
}