#ifndef MELEE_H
#define MELEE_H

#include "CCharacter.h"

class Mesh;

class CMelee : public CCharacter
{
public:
	enum SSTATES
	{
		NIL,
		ATTACK,
		DEFEND,
		RETREAT,
		NUM_OF_STATES
	};

	CMelee(const std::string& _modelMesh);
	~CMelee();

	virtual void Update();
	virtual void Render();
	virtual void RunFSM();
	virtual void Respond();

	void SetState(SSTATES _state);
	SSTATES GetState();

private:
	SSTATES state;
};

namespace Create
{
	CMelee* MeleeCharacter(const std::string& _meshName,
		const int _teamID,
		const Vector3& _position,
		const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f));
};

#endif