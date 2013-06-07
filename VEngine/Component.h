#pragma once

struct lua_State;
namespace VE
{
	class IComponent
	{
	public:
		IComponent(void): m_enabled(true) { }
		virtual ~IComponent(void) { }
		virtual void Update(double dt) = 0;

		bool IsEnabled(void) const { return m_enabled; }
		void SetEnabled(bool enabled) { m_enabled = enabled; }

		static void Export(lua_State* L);

	private:
		bool m_enabled;
	};
}