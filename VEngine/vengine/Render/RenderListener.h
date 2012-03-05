#ifndef RENDERLISTENER_H
#define RENDERLISTENER_H

namespace VE
{
	class CRenderManager;
}
namespace VE
{
	class IRenderListener
	{
		friend CRenderManager;
	protected:
		IRenderListener(size_t orderID = 1);


		virtual void Draw(void) = 0;

	public:
		size_t GetOrderID(void) const { return m_orderID; }
		void SetOrderID(size_t orderID) { m_orderID = orderID; }
		virtual ~IRenderListener(void);

	private:
		size_t m_orderID;

		IRenderListener(IRenderListener const&);
		void operator=(IRenderListener const&);
	};
}
#endif