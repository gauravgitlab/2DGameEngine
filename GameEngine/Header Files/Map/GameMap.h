#pragma once
#include "Layer.h"
#include <vector>

class GameMap
{
private:
	friend class MapParser;
	std::vector<Layer*> m_MapLayers;

public:
	void Render() {
		for (int i = 0; i < m_MapLayers.size(); i++) {
			m_MapLayers[i]->Render();
		}
	}

	void Update(float dt) {
		for (int i = 0; i < m_MapLayers.size(); i++) {
			m_MapLayers[i]->Update(dt);
		}
	}

	std::vector<Layer*> GetMapLayers() { return m_MapLayers; }
};
