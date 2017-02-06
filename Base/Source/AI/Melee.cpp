#include "Melee.h"
#include "../EntityManager.h"
#include "../MessageBoard.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "GL\glew.h"

CMelee::CMelee(const std::string& _modelMesh)
: CCharacter(_modelMesh)
, targetEnemy(NULL)
, ReachedGoal(false)
, attackCooldown(0.f)
{
	farRange = 70;
	nearRange = 45;
	SetType("melee");
	SetCharacter(true);
	Goal.Set(Math::RandFloatMinMax(-400, 400), Math::RandFloatMinMax(-300, 300));
}

CMelee::~CMelee()
{
	
}

void CMelee::Update(double dt)
{
	RunFSM(dt);
	Respond(dt);
}

void CMelee::Render()
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

void CMelee::MessageReceive(const std::string& message, CCharacter* _source)
{

}

void CMelee::RunFSM(double dt)
{
	CCharacter* nearestEnemy = GetNearestEnemy();

	if (nearestEnemy && state != ATTACK)
	{
		if ((position - nearestEnemy->GetPosition()).Length() - scale.x < nearRange)
		{
			state = ATTACK;
		}
	}

	// low hp
	if (GetHealth() <= 50)
	{
		Message("healer", "I am low on health, heal me!", this);
	}

	if (ReachedGoal && state == SURROUND)
	{
		state = ATTACK;
		attackCooldown = 10;
	}

}

std::string CMelee::StateToString()
{
	switch (state)
	{
	case NIL:
		return "NIL";
		break;
	case ATTACK:
		return "ATTACK";
		break;
	case DEFEND:
		return "DEFEND";
		break;
	case SURROUND:
		return "SURROUND";
		break;
	case RETREAT:
		return "RETREAT";
		break;
	}
}

void CMelee::Respond(double dt)
{
	switch (state)
	{
	case NIL:
		break;
	case ATTACK:
		if (targetEnemy)
		{
			if (attackCooldown < 0)
			{
				attackCooldown = 1;
				int RNGNUMBER = Math::RandIntMinMax(0, 100);
				std::cout << RNGNUMBER << std::endl;
				if (RNGNUMBER > 20)
				{
					speed = defaultSpeed * 5;

					Vector3 dist = position - targetEnemy->GetPosition();
					Goal.Set(targetEnemy->GetPosition() - (dist.Normalized() * 50));
					targetEnemy->MinusHealth(30);
					ReachedGoal = false;

					if (targetEnemy->GetHealth() <= 0)
					{
						targetEnemy->SetTeam(-1);
						targetEnemy = NULL;
					}
				}
			}
			else
			{
				attackCooldown -= dt;
			}
		}
		else
		{
			state = DEFEND;
			Goal.Set(Math::RandFloatMinMax(-400, 400), Math::RandFloatMinMax(-300, 300));
		}

		if (ReachedGoal)
		{
			speed = defaultSpeed;
		}

		break;
	case DEFEND:
		break;
	case SURROUND:
		break;
	case RETREAT:
		break;
	}

	Vector3 dis = Goal - position;

	if (dis.Length() > 10)
	{
		position += dis.Normalize() * speed;
		ReachedGoal = false;
	}
	else
	{
		// Reach goal
		ReachedGoal = true;
	}
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
	result->speed = 1.5f;
	result->defaultSpeed = result->speed;
	EntityManager::GetInstance()->AddEntity(result, true);
	return result;
}