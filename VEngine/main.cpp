#include "vengine\Application.h"
#include <vengine\Vengine.h>
#include "vengine\GUI\VengineGUI.h"
#include "vengine\Level\VengineLevelLoader.h"
#include "vengine\Level\VengineMap.h"
#include <vengine\Script\Script.h>
#include <vengine\BindToLua.h>

#include <iostream>

int main() 
{
	VE::CApplication* app = VE::CreateApp();
	// Initialize
	if (int ret = app->Init())
		return ret;

	// Set the GUI for the app
	VE::GetGUIMgr().SetGUI(new VE::CVengineGUI);
	// Set the level loader for the app
	VE::GetLvlMgr().SetLevelLoader(new VE::CVengineLevelLoader);
	// Bind classes
	VE::GetScriptMgr().BindToLua(BindCPPToLua);
	VE::GetScriptMgr().SetProvideGlobals(ProvideGlobals);

	// Run the app
	if (int ret = app->Run())
		return ret;
	// Free memory
	delete app;
	app = nullptr;

	return EXIT_SUCCESS;
}