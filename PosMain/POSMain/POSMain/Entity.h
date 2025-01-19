#pragma once

#include "defines.h"
#include "UseCases.h"

class Entity
{
public:
	Entity(UseCases* pCase);
	UseCases *mpUseCase;
	LPFNOnStatusChange mpCallback;
	void registerStatusCallback(LPFNOnStatusChange* pCallback);
	void onOrder(Menu menu);
	
};

