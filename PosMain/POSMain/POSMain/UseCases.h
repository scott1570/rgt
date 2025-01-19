#pragma once


#include "ServiceMaster.h"
#include "defines.h"
class Entity;

class UseCases
{


public:

	UseCases();

	Entity* mpEntity;

	void order(Menu menu);
	


};

