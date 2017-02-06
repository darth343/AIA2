#ifndef SCOUT_H
#define SCOUT_H

#include "CCharacter.h"

class Mesh;

class CScout : public CCharacter
{
public:
	enum SSTATES
	{
		NIL,
		ATTACK,
		SCOUT,
		RETREAT,
		NUM_OF_STATES
	};

	CScout(const std::string& _modelMesh);
	~CScout();

	virtual void Update(double dt);
	virtual void Render();
	virtual void RunFSM(double dt);
	virtual void Respond(double dt);


	void SetBase(Vector3 pos);
	void SetState(SSTATES _state);
	SSTATES GetState();

private:
	SSTATES state;
	Vector3 base;
};

namespace Create
{
	CScout* ScoutCharacter(const std::string& _meshName,
		const int _teamID,
		const Vector3& _position,
		const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f));
};

#endif