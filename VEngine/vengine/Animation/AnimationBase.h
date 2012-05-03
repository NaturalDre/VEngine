#ifndef ANIMATION_H
#define ANIMATION_H

#include <assert.h>

namespace VE
{

	class IAnimationBase
	{
	protected:
		virtual void NextFrame(void);

	public:
		virtual ~IAnimationBase(void);
		/*
		 * GetCurrentFrame()
		 *
		 * Returns: size_t
		 *		The current frame this animation is on.
		 *		E.G.: If an animation has 3 rows, 4 cols, and the
		 *		current frame is row 2, col 3, you're on the 7th frame.
		 */
		inline size_t GetCurrentFrame(void) const { return m_currentFrame; }
		// Do timing.
		void Logic(void);
		/* 
		 * SetCurrentFrame()
		 *
		 * Params: 
		 *		size_t frame: Jump the animation to a specific frame.
		 *
		 * Returns: bool
		 *		Returns true if the frame given was valid. False otherwise.
		 *
		 * Notes:
		 *		Does not reset how much time has passed since
		 *		last frame changed. (aka Time last animated).
		 */
		inline bool SetCurrentFrame(size_t frame) { m_currentFrame = frame; }
		// How many rows does this animation have?
		inline size_t GetRows(void) const { return m_rows; }
		// How many columns does this animation have?
		inline size_t GetCols(void) const { return m_cols; }
		// How fast the animation is playing
		inline double GetFPS(void) const { return m_fps; }
		// Change the framerate of the animation. TODO: Throw exception on <=0.
		inline void SetFPS(double fps) { assert(fps > 0); m_fps = fps;}
		// Is the animation held? AKA the animation is frozen.
		inline bool IsAnimHeld(void) const { return m_holdAnimation; }
		// Should the animation be held?
		inline void SetHoldAnimation(bool hold) { m_holdAnimation = hold; }
		/* 
		 * Reset()
		 * 
		 * Reset the animation to the first frame. Time 'til next frame is reset.
		 * Sets hold animation to false.
		 */
		void Reset(void);
		// How much game time until this animation goes to the next frame?
		inline double TimeToNextFrame(void) const { return m_timeout; }

	protected:
		/*
		 * Constructor()
		 *
		 * Initializes to default parameters.
		 * 
		 * Default Params:
		 *		rows = 1;
		 *		cols = 1;
		 *		currentFrame = 1;
		 *		fps = 1.0;
		 *		timeout = 1.0
		 *		holdAnimation = false;
		 */
		IAnimationBase(void);
		/*
		 * Constructor()
		 *
		 * Params:
		 *		rows = How many rows the animation sheet has. Must be > 0
		 *		cols = How many columns the animation sheet has. Must be > 0
		 * Throws:
		 *		std::exception if row or col is zero.
		 */
		IAnimationBase(size_t rows, size_t cols, double fps);

		bool m_holdAnimation;
		double m_timeout;
		double m_fps;
		size_t m_currentFrame;
		size_t m_rows;
		size_t m_cols;
	};
}
#endif