#include <vengine\Animation\MultiAnimation.h>
#include <allegro5\allegro5.h>
#include <algorithm>
#include <iostream>
namespace VE
{
	CMultiAnimation::CMultiAnimation(void)
	{

	}

	CMultiAnimation::~CMultiAnimation(void)
	{

	}

	bool CMultiAnimation::SequenceExists(const std::string& name) const
	{
		for (auto iter = m_sequences.begin(); iter != m_sequences.end(); ++iter)
		{
			if ((*iter).first == name)
				return true;
		}
		return false;
	}


	void CMultiAnimation::SetAlpha(size_t r, size_t g, size_t b)
	{

	}

	bool CMultiAnimation::SetSpriteSheet(const std::string& sheet, size_t rows, size_t cols, double fps)
	{
		return SetSpriteSheet(al_load_bitmap(sheet.c_str()), rows, cols, fps);	
	}

	bool CMultiAnimation::SetSpriteSheet(ALLEGRO_BITMAP* sheet, size_t rows, size_t cols, double fps)
	{
		m_animation = CBasicAnimation(sheet, rows, cols, fps);
		if (m_animation.GetAnimationSheet())
			return true;
		false;
	}

	bool CMultiAnimation::AddFrameSequence(const FrameSequence& fs, const std::string ident)
	{
		if (ident.empty() || fs.begin < 1 || fs.end < 1)
			return false;

		m_sequences.insert(std::pair<const std::string, const FrameSequence>(ident, fs));
	}

	void CMultiAnimation::SetCurrentAnim(const std::string& name)
	{
		// If the name is an empty string or is not the key of any known sequence, do nothing.
		if (name.empty() || !SequenceExists(name))
			return;
		// The name of the current animation sequence
		m_currentAnim = name;
		// Set the begin and end frames based on the data in the FrameSequence struct.
		m_animation.SetBeginFrame(m_sequences[m_currentAnim].begin);
		m_animation.SetEndFrame(m_sequences[m_currentAnim].end);
	}

	ALLEGRO_BITMAP* CMultiAnimation::GetFrame(void)
	{
		if (!m_currentAnim.empty())
			return m_animation.GetFrame();
		return nullptr;
	}
}