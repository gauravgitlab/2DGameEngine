#pragma once
#include "Layer.h"
#include <string>
#include <vector>

struct TileSet {
	int FirstID, LastID;
	int RowsCount, ColumnsCount;
	int TileCount, TileSize;
	std::string Name, Source;
};

using TilesetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int>>;


class TileLayer : public Layer
{
private:
	int m_TileSize;
	int m_RowCount, m_ColumnCount;
	TileMap m_TileMap;
	TilesetList m_TileSets;

public:
	TileLayer(int tileSize, int rowCount, int columnCount, TileMap tileMap, TilesetList tilesets);
	virtual void Update(float dt);
	virtual void Render();
	inline TileMap GetTilemap() { return m_TileMap; }
};

