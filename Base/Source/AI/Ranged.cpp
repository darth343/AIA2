#include "Ranged.h"
#include "../EntityManager.h"
#include "../MessageBoard.h"
#include "Commander.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "GL\glew.h"

#define EntityList EntityManager::GetInstance()->entityList

CRanged::CRanged(const std::string& _modelMesh)
: CCharacter(_modelMesh), targetEnemy(NULL)
{
	farRange = 80;
	nearRange = 20;
	SetType("ranged");
	SetCharacter(true);

}

CRanged::~CRanged()
{

}

void CRanged::Update(double dt)
{
	RunFSM(dt);
	Respond(dt);
}

void CRanged::Render()
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y - scale.y * 0.5, position.z);
	modelStack.Scale(scale.x * 0.5, scale.y * 0.5, scale.z * 0.5);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), StateToString(), Color(1, 1, 1));
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	CCharacter::Render();
}

void CRanged::RunFSM(double dt)
{

}

std::string CRanged::StateToString()
{
	switch (state)
	{
	case NONE:
		return "NONE";
		break;
	case SHOOT:
		return "SHOOT";
		break;
	case RETREAT:
		return "RETREAT";
		break;
	case MOVE:
		return "MOVE";
		break;
	}
}

void CRanged::Respond(double dt)
{
	switch (state)
	{
	case NONE:
		break;
	case SHOOT:
	{				
				 if (targetEnemy != NULL)
				 {
					 targetEnemy->MinusHealth(20);

					 if (targetEnemy->GetHealth() <= 0)
					 {
						 targetEnemy = NULL;
					 }
				 }
				 break;
	}
	case RETREAT:
		break;
	case MOVE:
	{
				 if (targetEnemy != NULL)
				 {
					 Vector3 Distance = (this->position - targetEnemy->GetPosition()).Length();
					 if (Distance < 150)
					 {
						 this->position += (targetEnemy->GetPosition() - this->position).Normalize() * speed;
					 }
				 }

				 break;
	}
		
	}


}

void CRanged::SetState(STATES _state)
{
	state = _state;
}

void CRanged::MessageReceive(const std::string& message, CCharacter* _source)
{
	if (strcmp(message.c_str(), "Shoot Him!") == 0)
	{

		if (targetEnemy != NULL)
		{
			Vector3 Distance = (this->position - targetEnemy->GetPosition()).Length();

			if (Distance > 150)
			{
				Message("commander", "I am walking towards the enemy!", this);
				state = MOVE;
			}
			else
			{
				Message("commander", "I will shoot him!", this);
				state = SHOOT;
			}
			
		}


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

	result->SetHealth(80.f);
	result->SetState(CRanged::STATES::NONE);
	EntityManager::GetInstance()->AddEntity(result, true);
	result->speed = 1.2f;

	return result;
}