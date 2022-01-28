#pragma once

#include "Cerberus/Core/Environment/CWorld.h"
#include "CerberusTools/CT_EditorResources.h"

#include <vector>
#include <string>
#include <map>

struct OperationData
{
	std::vector<int> PreOperation;
	std::vector<int> PostOperation;

};




class EditorWorld : public CWorld
{

	

	//std::vector<CT_EntityData> entityList;


	// performs a change operation on the world, Bounds are the 3 coordinates used to determine the size of the operation, Additive determines if the operation adds walkable space or removes it.
	void BoxOperation(Vector3 Bound1, Vector3 Bound2, bool Additive);
	void CircleOperation(Vector3 Origin, int Scale, bool Additive);

	void AddEntity(std::string EntityID);
	

protected: 

	
	

};

