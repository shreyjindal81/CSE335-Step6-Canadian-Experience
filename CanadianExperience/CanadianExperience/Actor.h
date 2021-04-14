/**
 * filename "Actor.h"
 * 
 * \ author Shrey Jindal
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */


#pragma once
#include <string>
#include "Drawable.h"
#include <memory>
#include <vector>
#include "AnimChannelPoint.h"
using namespace Gdiplus;
class CPicture;

/**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class CActor
{
public:
    CActor(const std::wstring& name);

    /** Default constructor disabled */
    CActor() = delete;
    /** Copy constructor disabled */
    CActor(const CActor&) = delete;
    /** Assignment operator disabled */
    void operator=(const CActor&) = delete;

    virtual ~CActor();

    void SetRoot(std::shared_ptr<CDrawable> root);

    void Draw(Gdiplus::Graphics* graphics);
    
    std::shared_ptr<CDrawable> HitTest(Gdiplus::Point pos);
    
    void AddDrawable(std::shared_ptr<CDrawable> drawable);
     
    std::wstring GetName() const { return mName; }
     
    Gdiplus::Point GetPosition() const { return mPosition; }
     
    void SetPosition(Gdiplus::Point pos) { mPosition = pos; }
     
    bool IsEnabled() const { return mEnabled; }
     
    void SetEnabled(bool enabled) { mEnabled = enabled; }
     
    bool IsClickable() const { return mClickable; }
     
    CAnimChannelPoint* GetPositionChannel() { return &mChannel; }
     
    void SetClickable(bool clickable) { mClickable = clickable; }

    void SetPicture(CPicture* picture);

    void SetKeyframe();

    void GetKeyframe();
 
    CPicture* GetPicture() { return mPicture; }

private:

    /// Name of Actor
    std::wstring mName;

    /// if it is enabled 
    bool mEnabled = true;

    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

    bool mClickable = true;

    std::shared_ptr<CDrawable> mRoot;

    /// The drawables in drawing order
    std::vector<std::shared_ptr<CDrawable>> mDrawablesInOrder;

    /// Picture actor belongs to
    CPicture* mPicture = nullptr;

    /// The actor position channel
    CAnimChannelPoint mChannel;
};

