#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include <vector>

struct lua_State;

namespace VE
{
	class CScript
	{
		friend bool LoadScript(CScript* script);
	protected:
		//static bool LoadScript(CScript*);

	public:
		CScript(const std::string& filename, lua_State* state, const std::string& scriptID = "");
		~CScript(void);

		const std::string& ScriptID(void) const { return m_scriptID; }
		// Attempts to push this script's table to the top of the stack.
		// If it returns true, it found and put the table at the top of the stack
		// and you must pop it off. If false then it couldn't find itself(Which
		// should NEVER happen) and you don't have to pop anything.
		bool Push(void);

		void Load(void);
		void Unload(void);

		bool IsLoaded(void) const { return m_loaded; }

		void Update(double dt);
		void Render(void);
	private:
		std::string m_scriptID;
		std::string m_filename;
		std::vector<char> m_buffer;
		lua_State* m_state;
		bool m_loaded;
	};
}
#endif