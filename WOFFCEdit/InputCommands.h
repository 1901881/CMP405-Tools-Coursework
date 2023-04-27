#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;

	bool up;
	bool down;

	bool rotRight;
	bool rotLeft;
	bool rotUp;
	bool rotDown;

	int mouse_X;
	int mouse_Y;
	bool mouse_LB_Down;
	bool mouse_RB_Down;

	bool multiSelect;

	bool ctrl_Down;
	bool c_Down;
	bool v_Down;
	
	bool i_Down;
	bool j_Down;
	bool k_Down;
	bool l_Down;

	bool o_Down;
	bool u_Down;

	bool mouseWheel_Down_Down;
	bool mouseWheel_UP_Down;

	long mouseDX;
	long mouseDY;

	void ResetState()
	{
		ZeroMemory(this, sizeof(this));
	}
};
