#ifndef VIEW_H
#define VIEW_H

namespace VE
{
	class CRender;
	
	class IView
	{
	protected:
		IView(CRender* renderer = nullptr, int drawOrder = 0);
		virtual ~IView(void);

	public:
		virtual void Draw(void) = 0;

		inline int DrawOrder(void) const { return m_drawOrder; }
		inline void SetDrawOrder(int drawOrder) { m_drawOrder = drawOrder; }

		CRender* Renderer(void) const { return m_renderer; }
	private:
		int m_drawOrder;
		CRender* m_renderer;
	};
}
#endif