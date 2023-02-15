#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, int rowCount, int columnCount, TileMap tileMap, TilesetList tilesets) : m_TileSets(tilesets)
{
	m_TileSize = tileSize;
	m_RowCount = rowCount;
	m_ColumnCount = columnCount;
	m_TileMap = tileMap;
}

void TileLayer::Update(float dt) {

}

void TileLayer::Render() {

}
