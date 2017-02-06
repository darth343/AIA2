#ifndef MELEE_H
#define MELEE_H

#include "CCharacter.h"

class Mesh;

class CMelee : public CCharacter
{
public:
	CCharacter* targetEnemy;


	enum SSTATES
	{
		NIL,
		ATTACK,
		DEFEND,
		SURROUND,
		RETREAT,
		NUM_OF_STATES
	};

	CMelee(const std::string& _modelMesh);
	~CMelee();

	virtual void Update(double dt);
	virtual void Render();
	virtual void RunFSM(double dt);
	virtual void Respond(double dt);
	virtual void MessageReceive(const std::string& message, CCharacter* _source);

	void SetState(SSTATES _state);
	SSTATES GetState();

	std::string StateToString();

	float defaultSpeed;
private:
	SSTATES state;
	bool ReachedGoal;

	// Attack Variables
	float attackCooldown;
};

namespace Create
{
	CMelee* MeleeCharacter(const std::string& _meshName,
		const int _teamID,
		const Vector3& _position,
		const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f));
};

#endif