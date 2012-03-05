#ifndef MAPLAYER_H
#define MAPLAYER_H

namespace VE
{
	class IMapLayer
	{
	protected:
		// TO DO: Implement operator overloading for <, >, == using layerNum
		IMapLayer(size_t layerNum = 1): m_layerNum(layerNum) { }
		inline void SetLayerNum(size_t layerNum) { m_layerNum = layerNum; }
	public:
		size_t getLayerNum(void) { return m_layerNum; }
		virtual void draw(void) = 0;
		virtual ~IMapLayer(void) {}

	private:
		IMapLayer(IMapLayer const&);
		void operator=(IMapLayer const&);
		size_t m_layerNum;
	};
}

#endif