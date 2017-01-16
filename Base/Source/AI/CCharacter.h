#ifndef CHARACTER_H
#define CHARACTER_H

#include "../GenericEntity.h"

class Mesh;

class CCharacter : public GenericEntity
{
public:
	CCharacter(const std::string& _modelMesh);
	virtual ~CCharacter();

	virtual void Update(double _dt);
	virtual void Render();
	virtual void RunFSM() = 0;
	virtual void Respond() = 0;

	void SetHealth(const float& health);
	void SetTeam(const int& teamID);

	float GetHealth();
	int GetTeamID();

	void MinusHealth(float val);
	void AddHealth(float val);

private:
	float Health;
	int teamID;
	bool Dead;
};

#endif // GENERIC_ENTITY_H