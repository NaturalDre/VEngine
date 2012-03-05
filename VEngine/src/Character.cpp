#include <vengine\Character\Character.h>

namespace VE
{
	ICharacter::ICharacter(void)
		: m_health(100.0f)
		, m_exp(0)
	{

	}

	ICharacter::~ICharacter(void)
	{

	}
}