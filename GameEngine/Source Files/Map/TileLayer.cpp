#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tileSize, int rowCount, int columnCount, TileMap tileMap, TilesetList tilesets) : m_TileSets(tilesets)
{
	m_TileSize = tileSize;
	m_RowCount = rowCount;
	m_ColumnCount = columnCount;
	m_TileMap = tileMap;

	for (unsigned int i = 0; i < m_TileSets.size(); i++) {
		TextureManager::GetInstance()->Load(m_TileSets[i].Name, "Assets/Map/" + m_TileSets[i].Source);
	}
}

void TileLayer::Update(float dt) 
{

}

void TileLayer::Render() 
{
	for (unsigned int i = 0; i < m_RowCount; i++) 
	{
		for (unsigned int j = 0; j < m_ColumnCount; j++) {
			int tileID = m_TileMap[i][j];

			if (tileID == 0)
				continue;

			int index = 0;
			if (m_TileSets.size() > 1) 
			{
				for (unsigned int k = 1; k < m_TileSets.size(); k++) {
					if (tileID > m_TileSets[k].FirstID && tileID < m_TileSets[k].LastID) {
						tileID = tileID + m_TileSets[k].TileCount - m_TileSets[k].LastID;
						index = k;
						break;
					}
				}
			}

			TileSet ts = m_TileSets[index];
			int tileRow = tileID / ts.ColumnsCount;
			int tileCol = tileID - tileRow * ts.ColumnsCount - 1;

			// if the tile is on the last column
			if (tileID % ts.ColumnsCount == 0) {
				tileRow--;
				tileCol = ts.ColumnsCount - 1;
			}

			TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, i * ts.TileSize, tileRow, tileCol);
		}
	}
}
