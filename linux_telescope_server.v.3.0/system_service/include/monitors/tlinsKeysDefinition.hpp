#ifndef __tlinsKeysDefinition_hpp__
#define __tlinsKeysDefinition_hpp__

class tlinsKeysDefinition {
  private:
	tlinsKeysDefinition() = default;

public:
 //
      // Klawaitura
      //
    static const int KEY_LEFT;
    static const int KEY_RIGHT;
	static const int KEY_UP;
	static const int KEY_DOWN;
	static const int KEY_OK;

	static const int KEY_F01;
	static const int KEY_F02;

	static const int KEY_F11;
	static const int KEY_F12;
	static const int KEY_F13;
	static const int KEY_F14;

	static const int KEY_F21;
	static const int KEY_F22;
	static const int KEY_F23;
	static const int KEY_F24;

	static const int KEY_F31;
	static const int KEY_F32;
	static const int KEY_F33;
	static const int KEY_F34;

	//
	// Joystick
	//
	static const int JOY_LPAD;
	static const int JOY_RPAD;

	static const int JOY_PAD_LEFT;
	static const int JOY_PAD_RIGHT;
	static const int JOY_PAD_UP;
	static const int JOY_PAD_DOWN;

	static const int JOY_KEY_1;
	static const int JOY_KEY_2;
	static const int JOY_KEY_3;
	static const int JOY_KEY_4;
	static const int JOY_KEY_START;
	static const int JOY_KEY_SELECT;

	static const int JOY_KEY_L1;
	static const int JOY_KEY_L2;

	static const int JOY_KEY_R1;
	static const int JOY_KEY_R2;

	//
	// Osie obrotu
	//
	static const int AXIS_X;
	static const int AXIS_Y;

	~tlinsKeysDefinition() = default;
};

#endif
