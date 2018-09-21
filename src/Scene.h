#pragma once

class Scene {
public:
	virtual void Init() = 0;
	virtual void Update(Uint32 dt) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	virtual void HandleKeyEvent(int key, bool state) = 0;
	virtual void HandleMouseEvent(int x, int y, int button) = 0;
};