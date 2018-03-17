#ifndef __ctINPUT_H__
#define __ctINPUT_H__

#include "ctModule.h"

#include "SDL\include\SDL_gamecontroller.h"
#include "SDL\include\SDL_scancode.h"

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
#define NUM_PAD_BUTTONS 16
#define PAD_DEAD_ZONE 10000
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;

enum ctEventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum ctKeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum AxisState
{
	RIGHT_AXIS = 0,
	LEFT_AXIS,
	UP_AXIS,
	DOWN_AXIS,
	UP_RIGHT_AXIS,
	UP_LEFT_AXIS,
	DOWN_RIGHT_AXIS,
	DOWN_LEFT_AXIS,

	RIGHT_AXIS_REPEAT,
	LEFT_AXIS_REPEAT,
	UP_AXIS_REPEAT,
	DOWN_AXIS_REPEAT,
	UP_RIGHT_AXIS_REPEAT,
	UP_LEFT_AXIS_REPEAT,
	DOWN_RIGHT_AXIS_REPEAT,
	DOWN_LEFT_AXIS_REPEAT,

	NO_STATE
};

enum GAMEPAD_STATE
{
	PAD_BUTTON_IDLE = 0,
	PAD_BUTTON_DOWN,
	PAD_BUTTON_REPEAT,
	PAD_BUTTON_KEY_UP
};

struct Gamepad {
	GAMEPAD_STATE A = PAD_BUTTON_IDLE;
	GAMEPAD_STATE B;
	GAMEPAD_STATE Y;
	GAMEPAD_STATE X;
};

class ctInput : public ctModule
{

public:

	ctInput();

	// Destructor
	virtual ~ctInput();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Gather relevant win events
	bool GetWindowEvent(ctEventWindow ev);

	// Check key states (includes mouse and joy buttons)
	ctKeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	ctKeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	ctKeyState GetPadButtonDown(int id) const
	{
		return pad_buttons[id - 1];
	}

	float GetPadXAxis() const
	{
		return x_axis;
	}

	float GetPadYAxis() const
	{
		return y_axis;
	}

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetWorldMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

	AxisState x_axis_state = NO_STATE;
	AxisState y_axis_state = NO_STATE;
	AxisState diagonal_axis_state = NO_STATE;

	Gamepad gamepad;

private:
	bool		windowEvents[WE_COUNT];
	ctKeyState*	keyboard = nullptr;
	ctKeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	ctKeyState	pad_buttons[NUM_PAD_BUTTONS];
	int			mouse_motion_x = 0;
	int			mouse_motion_y = 0;
	int			mouse_x = 0;
	int			mouse_y = 0;
	float		x_axis = 0;
	float		y_axis = 0;

	

	SDL_Joystick* pad_controller = nullptr;
	SDL_GameController *controller;

	bool is_keyboard_available = false;

};

#endif // __ctINPUT_H__