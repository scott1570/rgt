#include "pch.h"
#include "Entity.h"




Entity::Entity(UseCases* pCase)
{
	mpUseCase = pCase;
	mpCallback = NULL;

}
void Entity::onOrder(Menu menu)
{
	if (mpCallback != 0)
	{
		mpCallback(menu);
	}
}



void Entity::registerStatusCallback(LPFNOnStatusChange* pCallback)
{
	mpCallback = (LPFNOnStatusChange)pCallback;
}