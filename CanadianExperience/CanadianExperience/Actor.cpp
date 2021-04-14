/**
 * filename "Actor.cpp"
 *
 * \ author Shrey Jindal
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */

#include "pch.h"
#include "Actor.h"
#include "Picture.h"

using namespace std; using namespace Gdiplus;

CActor::CActor(const std::wstring& name) : mName(name)
{
    mName = name;
}


CActor::~CActor()
{
}

 
void CActor::SetRoot(std::shared_ptr<CDrawable> root)
{
    mRoot = root;
}

void CActor::Draw(Gdiplus::Graphics* graphics)
{
    // Don't draw if not enabled
    if (!mEnabled)
        return;

    // This takes care of determining the absolute placement
    // of all of the child drawables. We have to determine this 
    // in tree order, which may not be the order we draw.
    if (mRoot != nullptr)
        mRoot->Place(mPosition, 0);

    for (auto drawable : mDrawablesInOrder)
    {
        drawable->Draw(graphics);
    }
}


std::shared_ptr<CDrawable> CActor::HitTest(Gdiplus::Point pos)
{
    // If not enabled or not clickable, we indicate no hit.
    if (!mClickable || !mEnabled)
        return nullptr;

    // Since this list is in drawing order, we realy want to know the last thing drawn
    // under the mouse, since it will be on top. So, we reverse iterate over the list.
    for (auto d = mDrawablesInOrder.rbegin(); d != mDrawablesInOrder.rend(); d++)
    {
        auto drawable = *d;
        if (drawable->HitTest(pos))
            return drawable;
    }

    return nullptr;
}


void CActor::AddDrawable(std::shared_ptr<CDrawable> drawable)
{
    mDrawablesInOrder.push_back(drawable);
    drawable->SetActor(this);
}

void CActor::SetPicture(CPicture* picture)
{
    mPicture = picture;

    // Add the animation channel to the timeline added****
    mPicture->GetTimeline()->AddChannel(&mChannel);

    // Set the timeline for all drawables. This links the channels to
    // the timeline system.
    for (auto drawable : mDrawablesInOrder)
    {
        drawable->SetTimeline(mPicture->GetTimeline());
    }
}

void CActor::GetKeyframe()
{

    for (auto drawable : mDrawablesInOrder)
    {
        drawable->GetKeyframe();
    }

    if (mChannel.IsValid())
        mPosition = mChannel.GetPoint();
}

void CActor::SetKeyframe()
{
    mChannel.SetKeyframe(mPosition);

    for (auto drawable : mDrawablesInOrder)
    {
        drawable->SetKeyframe();
    }
}
