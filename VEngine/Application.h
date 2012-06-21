#ifndef APPLICATION_H
#define APPLICATION_H

namespace VE 
{
	class CEngine;
	class CApplication
	{
	protected:

	public:
		CApplication(void);
		~CApplication(void);

		int Run(void);
	private:
		CEngine* m_engine;
	};
}

#endif