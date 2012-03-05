#include "vengine\Level\VengineLevel.h"
#include <vengine\Utility.h>

namespace VE
{
	CVengineLevel::CVengineLevel(const std::string& filename)
		: m_filename(filename)
	{

	}

	void CVengineLevel::LoadData(void)
	{
		m_map = CVengineMap::Create(m_filename);
		m_map->Assemble();
	}

	void CVengineLevel::Assemble(void)
	{

	}

	void CVengineLevel::EndLevel(void)
	{

	}

	void CVengineLevel::Logic(void)
	{

	}

}