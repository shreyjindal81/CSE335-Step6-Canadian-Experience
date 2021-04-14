#pragma once
#include "AnimChannel.h"
class CAnimChannelAngle :
    public CAnimChannel
{


protected:

	void Tween(double t);

public:

	CAnimChannelAngle();///< COnstructor
	CAnimChannelAngle(CAnimChannelAngle* c) = delete; ///< disable copy constructor
	virtual ~CAnimChannelAngle(); ///< Destructor

	virtual void SetKeyframe(double angle);

	virtual void SetAngle(double n) { mAngle = n; };
	double GetAngle() { return mAngle; };

	/** Class that represents a keyframe angle */
	class KeyframeAngle : public Keyframe
	{
	public:
		virtual ~KeyframeAngle();
		KeyframeAngle() = delete;
		KeyframeAngle(KeyframeAngle* k) = delete;
		/** Constructor
 * \param channel The channel we are for
 * \param angle The angle for the keyframe */
		KeyframeAngle(CAnimChannelAngle* channel, double angle) :
			Keyframe(channel), mChannel(channel), mAngle(angle) {}
		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** Use this keyframe as the angle */
		virtual void UseOnly() override { mChannel->mAngle = mAngle; }
		virtual double GetAngle() { return mAngle; };
		virtual void SetFrame(double n) { mAngle = n; };
	private:
		double mAngle = 0;
		/// The channel this keyframe is associated with
		CAnimChannelAngle* mChannel;
	};

private:

	double mAngle = 0; ///<angle of rotation

		/// The first angle keyframe
	KeyframeAngle* mKeyframe1 = nullptr;

	/// The second angle keyframe
	KeyframeAngle* mKeyframe2 = nullptr;
};

