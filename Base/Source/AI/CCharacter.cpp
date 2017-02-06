#include "CCharacter.h"

#include "MeshBuilder.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "../MessageBoard.h"
#include "GL/glew.h"
#define EntityList EntityManager::GetInstance()->entityList

CCharacter::CCharacter(const std::string& _modelMesh)
: GenericEntity(MeshBuilder::GetInstance()->GetMesh(_modelMesh))
, Health(0)
, farRange(10)
, nearRange(5)
, Goal(Vector3(0, 0, 0))
{
	SetType("Character");
}

CCharacter::~CCharacter()
{
}


void CCharacter::Message(const std::string& herotype, const std::string& message, CCharacter* _source)
{
	MessageBoard::GetInstance()->Add(_source, herotype, message);
	std::list<EntityBase*>::iterator it, end;
	end = EntityList.end();
	for (it = EntityList.begin(); it != end; ++it)
	{
		if ((*it)->IsCharacter())
		{
			CCharacter* Hero = dynamic_cast<CCharacter*>(*it);
			if (Hero->GetType() == herotype)
			{
				Hero->MessageReceive(message, this);
			}
		}
	}
}

void CCharacter::GoTo(Vector3 pos)
{
	Goal = pos;
}


void CCharacter::MessageReceive(const std::string& message, CCharacter* _source)
{
	
}

void CCharacter::Update(double _dt)
{
	// Does nothing here, can inherit & override or create your own version of this class :D
}

CCharacter* CCharacter::GetNearestEnemy()
{
	CCharacter* result = NULL;

	std::list<EntityBase*>::iterator it, end;
	end = EntityList.end();
	for (it = EntityList.begin(); it != end; ++it)
	{
		if ((*it)->IsCharacter())
		{
			CCharacter* Hero = dynamic_cast<CCharacter*>((*it));
			if (this != (*it))
			{
				if (Hero->teamID != this->teamID && !result)
				{
					result = Hero;
				}
				else if (Hero->teamID != this->teamID)
				{
					if ((position - Hero->position).Length() < (result->position - Hero->position).Length())
					{
						result = Hero;
					}
				}
			}
		}
	}

	return result;
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
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}