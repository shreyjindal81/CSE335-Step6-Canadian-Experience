/**
 * Factory class that builds the other character
 *
 * filename "OtherCharFactory.h"
 *
 * \author Shrey Jindal
 */
#pragma once
#include "ActorFactory.h"
#include <memory>
#include "Actor.h"
 /**
  * Factory class that builds the Harold character
  */
class COtherCharFactory :
    public CActorFactory
{
public:
    virtual std::shared_ptr<CActor> Create();
};

