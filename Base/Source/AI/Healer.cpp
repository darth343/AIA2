#include "Healer.h"
#include "../EntityManager.h"
#include "../MessageBoard.h"
#include "Melee.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "GL\glew.h"
#include "Team.h"

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

void CHealer::Update(double dt)
{
	RunFSM(dt);
	Respond(dt);
}

void CHealer::Render()
{
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y + scale.y * 0.5, position.z);
	modelStack.Scale(scale.x * 0.5, scale.y * 0.5, scale.z * 0.5);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), StateToString(), Color(1, 1, 1));
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	CCharacter::Render();
}

void CHealer::RunFSM(double dt)
{
	if (state == NONE)
	{
		std::cout << "NONE" << std::endl;
	}
	else if (state == HEAL)
	{
		std::cout << "HEAL" << std::endl;
	}
	else if (state == MOVE)
	{
		std::cout << "MOVE" << std::endl;
	}

	//for (int i = 0; i < Team::Teams[teamID]->TeamComp["melee"].size(); i++)
	//{
	//	float teamMateHP = static_cast<CMelee*>(Team::Teams[teamID]->TeamComp["melee"][i])->GetHealth();
	//	std::cout << teamMateHP << std::endl;
	//}
}

std::string CHealer::StateToString()
{
	switch (state)
	{
	case NONE:
		return "NONE";
		break;
	case HEAL:
		return "HEAL";
		break;
	case DESTROY:
		return "DESTROY";
		break;
	case MOVE:
		return "MOVE";
		break;
	}
}

void CHealer::Respond(double dt)
{
	switch (state)
	{
	case NONE:
	{
				 break;
	}
	case HEAL:
	{
				 //for (int i = 0; i < Team::Teams[teamID]->TeamComp["melee"].size(); i++)
				 //{
					// float teamMateHP = static_cast<CMelee*>(Team::Teams[teamID]->TeamComp["melee"][i])->GetHealth();

					// if (teamMateHP <= 50)
					// {
					//	 static_cast<CMelee*>(Team::Teams[teamID]->TeamComp["melee"][i])->AddHealth(30);
					// }
				 //}
				 break;
	}
	case DESTROY:
	{
					//std::cout << "test" << std::endl;
				 break;
	}
	case MOVE:
	{			
				 for (int i = 0; i < Team::Teams[teamID]->TeamComp["melee"].size(); i++)
				 {
					 Vector3 dist = static_cast<CMelee*>(Team::Teams[teamID]->TeamComp["melee"][i])->GetPosition();

					 position += (dist - position).Normalize() * speed;

				 }
				 break;
	}

	}
}

void CHealer::SetState(STATES _state)
{
	state = _state;
}

void CHealer::MessageReceive(const std::string& message, CCharacter* _source)
{
	if (strcmp(message.c_str(), "Me MELEE is low on health, heal me!") == 0)
	{
		
		for (int i = 0; i < Team::Teams[teamID]->TeamComp["melee"].size(); i++)
		{
			Vector3 dist = ((static_cast<CMelee*>(Team::Teams[teamID]->TeamComp["melee"][i])->GetPosition()) - (this->position)).Length();
	
			float teamMateHP = static_cast<CMelee*>(Team::Teams[teamID]->TeamComp["melee"][i])->GetHealth();

			if (dist < 150)
			{
				state = MOVE;
			}
			else
			{
				if (teamMateHP <= 50)
				{
					state = HEAL;
					Message("melee", "I am healing you MELEE!", this);
					static_cast<CMelee*>(Team::Teams[teamID]->TeamComp["melee"][i])->AddHealth(30);
				}
				else
				{
					state = NONE;
				}
				
				
			}
			
			
		}

	}
	if (strcmp(message.c_str(), "Me RANGED is low on health, heal me!") == 0)
	{
		state = HEAL;
	}
	if (strcmp(message.c_str(), "Me SCOUT is low on health, heal me!") == 0)
	{
		state = HEAL;
	}
	if (strcmp(message.c_str(), "Me COMMANDER is low on health, heal me!") == 0)
	{
		state = HEAL;
	}
	if (strcmp(message.c_str(), "Me MAGE is low on health, heal me!") == 0)
	{
		state = HEAL;
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
	result->SetState(CHealer::STATES::NONE);
	result->speed = 1.2f;
	EntityManager::GetInstance()->AddEntity(result, true);

	return result;
}