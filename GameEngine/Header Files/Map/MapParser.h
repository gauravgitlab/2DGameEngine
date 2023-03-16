#pragma once

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"

class MapParser
{
private:
	MapParser() { }
	static MapParser* s_Instance;
	std::map<std::string, GameMap*> m_MapDict;

	bool Parse(std::string id, std::string source);
	TileSet ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int columnCount);

public:
	inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }
	bool Load();
	void Clean();

	inline GameMap* GetMap(std::string id) { return m_MapDict[id]; }
};

