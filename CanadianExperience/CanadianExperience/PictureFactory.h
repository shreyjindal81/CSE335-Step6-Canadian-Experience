/**
 * A factory class that builds our picture.
 * 
 * filename "Factory.h"
 * 
 * \author Shrey Jindal
 */
#pragma once
#include <memory>
#include "Picture.h"
class CPictureFactory
{
public:
	virtual std::shared_ptr<CPicture> Create();
	~CPictureFactory() {};
	CPictureFactory() {};

};

