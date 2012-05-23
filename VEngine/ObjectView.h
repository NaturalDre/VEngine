#ifndef OBJECTVIEW_H
#define OBJECTVIEW_H

namespace VE {
	class CRender;
	class IObjectView
	{
		friend CRender;
	protected:
		IObjectView(int drawNum = 0);
		~IObjectView(void);

		// It's time to draw to the screen.
		virtual void Draw(void) = 0 { };

	public:
		inline void SetDrawNum(int drawNum) { m_drawNumber = drawNum; }
		inline int GetDrawNum(void) const { return m_drawNumber; }

		inline bool SetShouldDraw(bool shouldDraw) { m_shouldDraw = shouldDraw; }
		inline bool ShouldDraw(void) const { return m_shouldDraw; }
	private:
		// Holds when an object is drawn. Lower is sooner.
		int m_drawNumber;
		// Should the render manager call Draw()?
		bool m_shouldDraw;
	};
}
#endif