#include "vengine\Application.h"
#include <vengine\Vengine.h>
#include "vengine\GUI\VengineGUI.h"
#include "vengine\Level\VengineMap.h"
#include <vengine\Script\Script.h>
#include <vengine\VengineStatics.h>

#include <iostream>

int main() 
{
	VE::CApplication* app = VE::CreateApp();
	// Initialize
	if (int ret = app->Init())
		return ret;

	// Bind classes
	VE::GetScriptMgr().BindToLua(BindCPPToLua);
	VE::GetScriptMgr().SetProvideGlobals(ProvideGlobals);
	VE::GetLvlMgr().SetLevelFactories(ProvideLevelFactories);

	// Run the app
	if (int ret = app->Run())
		return ret;
	// Free memory
	delete app;
	app = nullptr;
	return EXIT_SUCCESS;
}