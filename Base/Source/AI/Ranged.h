#ifndef RANGED_H
#define RANGED_H

#include "CCharacter.h"

class Mesh;

class CRanged : public CCharacter
{
public:
	enum STATES
	{
		NONE,
		SHOOT,
		RETREAT,
		MOVE,
		NUM_OF_STATES,
	};

	CRanged(const std::string& _modelMesh);
	~CRanged();

	virtual void Update();
	virtual void Render();
	virtual void RunFSM();
	virtual void Respond();
	virtual void MessageReceive(const std::string& message, CCharacter* _source);

	void SetState(STATES _state);
	STATES GetState();

private:
	STATES state;
};

namespace Create
{
	CRanged* RangedCharacter(const std::string& _meshName,
		const int _teamID,
		const Vector3& _position,
		const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f));
}

#endif