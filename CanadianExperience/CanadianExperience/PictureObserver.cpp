#include "pch.h"
#include "PictureObserver.h"
#include "Picture.h"
/**
 * Set the picture for this observer
 * \param picture The picture to set
 */
void CPictureObserver::SetPicture(std::shared_ptr<CPicture> picture)
{
    mPicture = picture;
    mPicture->AddObserver(this);
}

/** Destructor */
CPictureObserver::~CPictureObserver()
{
    if (mPicture != nullptr)
    {
        mPicture->RemoveObserver(this);
    }
}