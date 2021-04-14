/**
 * file "Drawable.h"
 *
 * \author Shrey Jindal
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */

#include "pch.h"
#include "Drawable.h"
#include "Actor.h"
#include "Timeline.h"
#include <string>
#include <memory>

using namespace std; using namespace Gdiplus;

 
CDrawable::CDrawable(const std::wstring& name) : mName(name)
{

}

 CDrawable::~CDrawable()
{
}



void CDrawable::SetActor(CActor* actor)
{
    mActor = actor;

    mChannel.SetName(actor->GetName() + L":" + mName);
}



void CDrawable::Place(Gdiplus::Point offset, double rotate)
{
    // Combine the transformation we are given with the transformation
    // for this object.
    mPlacedPosition = offset + RotatePoint(mPosition, rotate);
    mPlacedR = mRotation + rotate;

    // Update our children
    for (auto drawable : mChildren)
    {
        drawable->Place(mPlacedPosition, mPlacedR);
    }
}



void CDrawable::AddChild(std::shared_ptr<CDrawable> child)
{
    mChildren.push_back(child);
    child->SetParent(this);
}





void CDrawable::Move(Gdiplus::Point delta)
{
    if (mParent != nullptr)
    {
        mPosition = mPosition + RotatePoint(delta, -mParent->mPlacedR);
    }
    else
    {
        mPosition = mPosition + delta;
    }
}



Gdiplus::Point CDrawable::RotatePoint(Gdiplus::Point point, double angle)
{
    double cosA = cos(angle);
    double sinA = sin(angle);

    return Gdiplus::Point(int(cosA * point.X + sinA * point.Y),
        int(-sinA * point.X + cosA * point.Y));
}


void CDrawable::SetTimeline(CTimeline* timeline)
{
    timeline->AddChannel(&mChannel);
}

void CDrawable::SetKeyframe()
{
    mChannel.SetKeyframe(mRotation);
}

void CDrawable::GetKeyframe()
{
    if (mChannel.IsValid())
        mRotation = mChannel.GetAngle();
}