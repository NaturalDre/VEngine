#ifndef MULTIANIMATION_H
#define MULTIANIMATION_H

struct ALLEGRO_BITMAP;


#include <map>
#include <string>
#include "BasicAnimation.h"
namespace VE
{
	struct FrameSequence 
	{ 
		size_t begin, end;
		FrameSequence(void): begin(1), end(1) {}
		FrameSequence(size_t _begin, size_t _end): begin(_begin), end(_end) {}
	};

	class CMultiAnimation: public IAnimation
	{
	protected:
		bool SequenceExists(const std::string& name) const;
		void Logic(double dt);

	public:
		CMultiAnimation(void);
		~CMultiAnimation(void);

		bool SetSpriteSheet(const std::string& sheet, size_t rows, size_t cols, double fps);
		bool SetSpriteSheet(const std::shared_ptr<CBitmap>& sheet, size_t rows, size_t cols, double fps);

		bool AddFrameSequence(const FrameSequence& fs, const std::string ident);

		const CBasicAnimation& GetCurrentAnim(void) const { return m_animation; }
		const std::string& GetCurrentAnimName(void) const { return m_currentAnim; }


		void SetCurrentAnim(const std::string& name);
		void SetAlpha(size_t r, size_t g, size_t b);

		inline const std::shared_ptr<CBitmap>& GetSpriteSheet(void) const { return m_animation.GetAnimationSheet(); }

	private:
		std::map<const std::string, const FrameSequence> m_sequences;
		std::string m_currentAnim;
		CBasicAnimation m_animation;
	};
}
#endif