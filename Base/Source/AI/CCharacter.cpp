#include "CCharacter.h"

#include "MeshBuilder.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

CCharacter::CCharacter(const std::string& _modelMesh)
: GenericEntity(MeshBuilder::GetInstance()->GetMesh(_modelMesh))
, Health(0)
{
	SetType("Character");
}

CCharacter::~CCharacter()
{
}

void CCharacter::Update(double _dt)
{
	// Does nothing here, can inherit & override or create your own version of this class :D
}

void CCharacter::SetHealth(const float& _health)
{
	Health = _health;
}

void CCharacter::SetTeam(const int& _teamID)
{
	teamID = _teamID;
}

int CCharacter::GetTeamID()
{
	return teamID;
}

float CCharacter::GetHealth()
{
	return Health;
}

void CCharacter::MinusHealth(float val)
{
	Health -= val;
	if (Health <= 0)
	{
		Dead = true;
	}
}

void CCharacter::AddHealth(float val)
{
	Health += val;
}

void CCharacter::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();
}