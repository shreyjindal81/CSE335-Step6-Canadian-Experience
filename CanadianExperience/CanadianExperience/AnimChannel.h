/**
 * Base class for animation channels
 *
 * filename 'AnimChannel.h'
 * 
 * author Shrey Jindal
 */
#pragma once
#include <string>
#include <memory>
#include <vector>
class CTimeline;
 /**
  * Base class for animation channels
  *
  * This class provides basic functionality and a polymorphic
  * representation for animation channels.
  */
class CAnimChannel
{
public:
	CAnimChannel();
	void RemoveKeyframe();
	///< COnstructor
	CAnimChannel(CAnimChannel* c) = delete; ///< disable copy constructor
	virtual ~CAnimChannel(); ///< Destructor
	virtual bool IsValid();
	virtual void SetFrame(int currFrame);
	
	virtual void SetName(std::wstring n) { mName = n; };
	std::wstring GetName() { return mName; };
	virtual void SetTimeline(CTimeline* t) { mTimeline = t; };
	virtual CTimeline* GetTimeline() { return mTimeline; };
	/** Class that represents a keyframe */
	class Keyframe
	{
	public:
		Keyframe() = delete;
		Keyframe(Keyframe* k) = delete;
		virtual ~Keyframe();
		virtual void UseAs1()=0;
		virtual void UseAs2()=0;
		virtual void UseOnly()=0;
		virtual int GetFrame() { return mFrame; };
		virtual void SetFrame(int n) { mFrame = n; };
	protected:
		int mFrame{};
		/** Constructor
 * \param channel Channel we are associated with */
		Keyframe(CAnimChannel* channel) : mChannel(channel) {}
	private:
		/// The channel this keyframe is associated with
		CAnimChannel* mChannel;
	};

protected:
	virtual	void Tween(double t);
	virtual void InsertKeyframe(std::shared_ptr<Keyframe> k);

private:
	int mKeyframe1 = -1;
	int mKeyframe2 = -1;
	std::wstring mName{};
	/// The timeline object
	CTimeline* mTimeline = nullptr;
	/// The collection of keyframes for this channel
	std::vector<std::shared_ptr<Keyframe>> mKeyframes;
};

