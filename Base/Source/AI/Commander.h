#ifndef COMMANDER_H
#define COMMANDER_H

#include "CCharacter.h"

class Mesh;

class CCommander : public CCharacter
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

	CCommander(const std::string& _modelMesh);
	~CCommander();

	virtual void Update(double dt);
	virtual void Render();
	virtual void RunFSM();
	virtual void Respond();
	virtual void MessageReceive(const std::string& message, CCharacter* _source);

	void SetState(SSTATES _state);
	SSTATES GetState();

private:
	SSTATES state;
};

namespace Create
{
	CCommander* CommanderCharacter(const std::string& _meshName,
		const int _teamID,
		const Vector3& _position,
		const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f));
};

#endif