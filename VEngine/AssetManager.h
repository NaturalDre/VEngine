#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "Asset.h"
#include <map>
#include <vector>

class IAsset;

class CAssetManager
{
	static CAssetManager* instance;
public:
	CAssetManager(void);
	~CAssetManager(void);

	std::shared_ptr<IAsset> GetAsset(const std::string& name);
	void SetCurScene(size_t scene) { m_curScene = scene; }

	void LoadAssetsFromXML(const std::string& filename);
	void LoadAssetsFromLua(const std::string& filename);

	static CAssetManager* Instance(void) { if (!instance) instance = new CAssetManager; return instance; }
private:
	size_t m_curScene;
	std::map<size_t, std::vector<std::shared_ptr<IAsset>>> m_assets;
};
#endif