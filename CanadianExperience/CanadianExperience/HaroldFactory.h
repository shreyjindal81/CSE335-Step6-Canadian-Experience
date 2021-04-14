/**
 * Factory class that builds the Harold character
 * 
 * filename "HaroldFactory.h"
 * 
 * \author Shrey Jindal
 */
#pragma once
#include "ActorFactory.h"

 /**
  * Factory class that builds the Harold character
  */
class CHaroldFactory :
    public CActorFactory
{
public:
    virtual std::shared_ptr<CActor> Create();
};

