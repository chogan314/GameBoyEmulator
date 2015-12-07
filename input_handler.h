#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

class Input;

class InputHandler
{
public:
	virtual bool OnKeyDown(int key, int mods) = 0;
	virtual bool OnKeyUp(int key, int mods) = 0;
	virtual bool OnMouseDown(int button, int mods) = 0;
	virtual bool OnMouseUp(int button, int mods) = 0;
	virtual bool OnMouseScroll(float xOffset, float yOffset) = 0;
	virtual bool OnMouseMoved(float x, float y) = 0;
};

#endif