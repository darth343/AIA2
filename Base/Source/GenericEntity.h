#ifndef GENERIC_ENTITY_H
#define GENERIC_ENTITY_H

#include "EntityBase.h"
#include <string>
#include "Collider/Collider.h"


class Mesh;

class GenericEntity : public EntityBase, public CCollider
{
public:
	GenericEntity(Mesh* _modelMesh);
	virtual ~GenericEntity();

	virtual void Update(double _dt);
	virtual void Render();

	void SetAABB(Vector3 maxAABB, Vector3 minAABB);
	Vector3 GetMin();
	Vector3 GetMax();

protected:
	Mesh* modelMesh;
};

namespace Create
{
	GenericEntity* Entity(	const std::string& _meshName, 
							const Vector3& _position, 
							const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f));

	GenericEntity* Asset(	const std::string& _meshName,
							const Vector3& _position,
							const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f));
};

#endif // GENERIC_ENTITY_H