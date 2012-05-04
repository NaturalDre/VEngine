#ifndef MULTIANIMATION_H
#define MULTIANIMATION_H

#include <vengine\Animation\BasicAnimation.h>
#include <map>
#include <string>

struct ALLEGRO_BITMAP;

namespace VE
{
	struct FrameSequence 
	{ 
		size_t begin, end;
		FrameSequence(void): begin(1), end(1) {}
		FrameSequence(size_t _begin, size_t _end): begin(_begin), end(_end) {}
	};

	class CMultiAnimation
	{
	protected:
		bool SequenceExists(const std::string& name) const;

	public:
		CMultiAnimation(void);
		~CMultiAnimation(void);

		bool SetSpriteSheet(const std::string& sheet, size_t rows, size_t cols, double fps);
		bool SetSpriteSheet(ALLEGRO_BITMAP* sheet, size_t rows, size_t cols, double fps);
		
		bool AddFrameSequence(const FrameSequence& fs, const std::string ident);
		void SetCurrentAnim(const std::string& name);
		void SetAlpha(size_t r, size_t g, size_t b);

		inline ALLEGRO_BITMAP* GetSpriteSheet(void) const { return m_animation.GetAnimationSheet(); }

		ALLEGRO_BITMAP* GetFrame(void);
	private:
		std::map<const std::string, const FrameSequence> m_sequences;
		std::string m_currentAnim;
		CBasicAnimation m_animation;
	};
}
#endif