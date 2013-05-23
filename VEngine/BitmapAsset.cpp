#include "BitmapAsset.h"
#include "Bitmap.h"

namespace VE
{
	CBitmapAsset::CBitmapAsset(const std::string& file)
		: IAsset(file, IAsset::GRAPHICAL, -1)
	{

	}

	void CBitmapAsset::OnLoad(void)
	{
		m_bitmap = std::move(CreateBitmap(GetFilename()));
		SetLoaded(m_bitmap);
	}

	void CBitmapAsset::OnUnload(void) 
	{
		m_bitmap.reset();
	}
}