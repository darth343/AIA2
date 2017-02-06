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
	virtual void RunFSM(double dt) = 0;
	virtual void Respond(double dt) = 0;

	void Message(const std::string& heroType, const std::string& message, CCharacter* _source);
	virtual void MessageReceive(const std::string& message, CCharacter* _source);

	void SetHealth(const float& health);
	void SetTeam(const int& teamID);

	float GetHealth();
	int GetTeamID();

	void MinusHealth(float val);
	void AddHealth(float val);
	void GoTo(Vector3 pos);

	CCharacter* GetNearestEnemy();
	float speed;

protected:
	float farRange;
	float nearRange;
	float Health;
	int teamID;
	bool Dead;
	Vector3 Goal;
};

#endif // GENERIC_ENTITY_H