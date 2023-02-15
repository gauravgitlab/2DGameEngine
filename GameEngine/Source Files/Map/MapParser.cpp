#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load() 
{
	if (!Parse("level1", "Assets/Map/map.tmx"))
		return false;

	return true;
}

void MapParser::Clean() 
{

}

bool MapParser::Parse(std::string id, std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cerr << "failed to load : " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	int rowCount, colCount, tileSize = 0;

	root->Attribute("width", &colCount);
	root->Attribute("height", &rowCount);
	root->Attribute("tilewidth", &tileSize);

	// parse tile sets
	TilesetList tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}

	// parse layers
	GameMap* gameMap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("layer")) 
		{
			TileLayer* tileLayer = ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
			gameMap->m_MapLayers.push_back(tileLayer);
		}
	}

	m_MapDict[id] = gameMap;

	return true;
}

TileSet MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
	TileSet tileset;
	tileset.Name = xmlTileset->Attribute("name");
	
	xmlTileset->Attribute("firstgid", &tileset.FirstID);
	xmlTileset->Attribute("tileCount", &tileset.TileCount);
	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

	xmlTileset->Attribute("columns", &tileset.ColumnsCount);
	tileset.RowsCount = tileset.TileCount / tileset.ColumnsCount;
	xmlTileset->Attribute("firstgid", &tileset.ColumnsCount);

	xmlTileset->Attribute("tilewidth", &tileset.TileSize);

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");

	return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int columnCount)
{
	TiXmlElement* data = nullptr;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) 
	{
		if (e->Value() == std::string("data")) {
			data = e;
			break;
		}
	}

	// Parse Layer tile map
	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tilemap(rowCount, std::vector<int>(columnCount, 0));

	for (int row = 0; row = rowCount; row++) 
	{
		for (int col = 0; col = columnCount; col++) 
		{
			getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> tilemap[row][col];

			if (!iss.good())
				break;
		}
	}

	return (new TileLayer(tileSize, rowCount, columnCount, tilemap, tilesets));
}
