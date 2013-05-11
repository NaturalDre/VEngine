#include"Application.h"
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;
using namespace VE;

int main(int argc, const char* argv[])
{
	//TiXmlDocument doc("example4.xml");
	//doc.LoadFile();
	//TiXmlNode* windows = doc.FirstChild("MyApp")->FirstChild("Windows");
	//auto ele = windows->FirstChild()->ToElement();
	//auto f = ele->Attribute("name");
	CApplication app;
	return app.Run();
}