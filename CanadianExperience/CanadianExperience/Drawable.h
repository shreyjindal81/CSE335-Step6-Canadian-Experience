/**
 * file "Drawable.h"
 * 
 * \author Shrey Jindal
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "AnimChannel.h"
#include "AnimChannelAngle.h"

class CTimeline;
class CActor;

using namespace std; using namespace Gdiplus;
using namespace Gdiplus;
class CTimeline;
class CActor;
/**
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */
class CDrawable
{
public:
    virtual ~CDrawable();

    ///disable default
    CDrawable() = delete;
    ///disable copy
    CDrawable(const CDrawable&) = delete;

    ///draws the drawable
    ///\param graphics
    virtual void Draw(Gdiplus::Graphics* graphics) = 0;

 
    void Place(Gdiplus::Point offset, double rotate);

 
    void AddChild(std::shared_ptr<CDrawable> child);

 
    virtual bool HitTest(Gdiplus::Point pos) = 0;

    virtual void SetActor(CActor* actor);


 
    virtual bool IsMovable() { return false; }
    void Move(Gdiplus::Point delta);
 
    void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

 
    Gdiplus::Point GetPosition() const { return mPosition; }
 
    void SetRotation(double r) { mRotation = r; }
     
    double GetRotation() const { return mRotation; }
     
    std::wstring GetName() const { return mName; }
     
    CDrawable* GetParent() const { return mParent; }
     
    void SetParent(CDrawable* drawable) { mParent = drawable; }
     
    CAnimChannelAngle* GetAngleChannel() { return &mChannel; }
     
    virtual void SetTimeline(CTimeline* timeline);

    virtual void SetKeyframe();

    virtual void GetKeyframe();

protected:
    CDrawable(const std::wstring& name);

    Gdiplus::Point RotatePoint(Gdiplus::Point point, double angle);
 
    Gdiplus::Point mPlacedPosition = Gdiplus::Point(0, 0);
     
    double mPlacedR = 0;

private:
    /// The drawable name
    std::wstring mName;

    /// The position of this drawable relative to its parent
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

    /// animation channel for drawable
    CAnimChannelAngle mChannel;

    /// The rotation of this drawable relative to its parent
    double mRotation = 0;

    /// The actor using this drawable
    CActor* mActor = nullptr;

    /// Children drawables
    std::vector<std::shared_ptr<CDrawable>> mChildren;

    /// Parent drawable
    CDrawable* mParent = nullptr;


};

