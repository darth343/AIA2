#ifndef HEALER_H
#define HEALER_h

#include "CCharacter.h"

class Mesh;

class CHealer : public CCharacter
{
public:
	enum STATES
	{
		NONE,
		HEAL,
		DESTROY,
		MOVE,
		NUM_OF_STATES,
	};

	CHealer(const std::string& _modelMesh);
	~CHealer();

	virtual void Update(double dt);
	virtual void Render();
	virtual void RunFSM(double dt);
	virtual void Respond(double dt);
	virtual void MessageReceive(const std::string& message, CCharacter* _source);

	void SetState(STATES _state);
	STATES GetState();

	std::string StateToString();
private:
	STATES state;
};

namespace Create
{
	CHealer* HealerCharacter(const std::string& _meshName,
		const int _teamID,
		const Vector3& _position,
		const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f));
}

#endif