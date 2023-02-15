#pragma once

class Layer 
{
private:

public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};
