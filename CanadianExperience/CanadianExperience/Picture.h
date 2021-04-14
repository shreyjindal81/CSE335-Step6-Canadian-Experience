/*
* file "Picture.h"
* \author Shrey Jindal
* 
* there will be one picture object that contains all of 
* our actors, which then contains the drawables
*/

#pragma once
#include <vector>
#include "Actor.h"
#include "Timeline.h"
class CPictureObserver;


/**
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */
class CPicture
{
public:

    /** Iterator that iterates over the city tiles */
    class Iter
    {
    public:
        /** Constructor
         * \param pic The picutre we are iterating over */
        Iter(CPicture* pic, int pos) : mPicture(pic), mPos(pos) {}

        /** Test for end of the iterator
         * \returns True if we this position equals not equal to the other position */
        bool operator!=(const Iter& other) const
        {
            return mPos != other.mPos;
        }

        /** Get value at current position
         * \returns Value at mPos in the collection */
        std::shared_ptr<CActor> operator *() const { return mPicture->mActors[mPos]; }

        /** Increment the iterator
         * \returns Reference to this iterator */
        const Iter& operator++()
        {
            mPos++;
            return *this;
        }

        

    private:
        CPicture* mPicture;   ///< City we are iterating over
        int mPos;       ///< Position in the collection
    };

    /** Get a pointer to the Timeline object
* \returns Pointer to the Timeline object
 */
    CTimeline* GetTimeline() { return &mTimeline; }

    /** Get an iterator for the beginning of the collection
 * \returns Iter object at position 0 */
    Iter begin() { return Iter(this, 0); }

    /** Get an iterator for the end of the collection
     * \returns Iter object at position past the end */
    Iter end() { return Iter(this, mActors.size()); }

	CPicture() {};
    /// Copy Constructor (Disabled)
    CPicture(const CPicture&) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const CPicture&) = delete;
    /** The picture size
* \returns Size */
    Gdiplus::Size GetSize() { return mSize; }

    /** The picture size
    * \param size The new picture size */
    void SetSize(Gdiplus::Size size) { mSize = size; }

    void AddObserver(CPictureObserver* observer);
    void RemoveObserver(CPictureObserver* observer);
    void UpdateObservers();
    void Draw(Gdiplus::Graphics* graphics);

    void SetAnimationTime(double time);
    
    virtual void AddActor(std::shared_ptr<CActor> actor) { mActors.push_back(actor); actor->SetPicture(this); };

    double GetCurrTime() { return mTimeline.GetTime(); }
private:
    /// The picture size
    Gdiplus::Size mSize = Gdiplus::Size(800, 600);
    /// The observers of this picture
    std::vector<CPictureObserver*> mObservers;
    ///all the actors
    std::vector <std::shared_ptr<CActor>> mActors;
    /// The animation timeline
    CTimeline mTimeline;
};

