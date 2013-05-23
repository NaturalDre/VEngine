#pragma once
#include "Asset.h"
#include <memory>

namespace VE
{
	class CBitmap;
	class CBitmapAsset: public IAsset
	{
	protected:
		void OnLoad(void);
		void OnUnload(void);

	public:
		CBitmapAsset(const std::string& file);
		const std::shared_ptr<CBitmap> GetBitmap(void) const { return m_bitmap; }
	private:
		std::shared_ptr<CBitmap> m_bitmap;
	};
}