/*
*file "PictureObserver.h"
* \author Shrey Jindal
* 
* this class implements the base class functionality
* for an observer in the obersver pattern
*/

#pragma once
#include <memory>
class CPicture;
/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class CPictureObserver
{
public:

	/// Copy Constructor (Disabled)
	CPictureObserver(const CPictureObserver&) = delete;
	/// Assignment Operator (Disabled)
	void operator=(const CPictureObserver&) = delete;
	/// This function is called to update any observers
	virtual void UpdateObserver() = 0;
	virtual void SetPicture(std::shared_ptr<CPicture> picture);
	virtual std::shared_ptr<CPicture> GetPicture() { return mPicture; }
	virtual ~CPictureObserver();

protected:
	CPictureObserver() {}
private:
	/// Picture we are observing
	std::shared_ptr<CPicture> mPicture;


};

