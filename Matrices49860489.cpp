// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

#include <mmsystem.h>
#include <Digitalv.h>

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 1200
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#define NOTE 100
#define ENEMY_NOTE 100

bool mScreen;
bool sScreen;
bool igScreen;
bool cScreen;
bool goScreen;

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface

						// sprite declarations
LPDIRECT3DTEXTURE9 mainScreen;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 music_note;
int mnA;

LPDIRECT3DTEXTURE9 selectScreen;
LPDIRECT3DTEXTURE9 text_song;
LPDIRECT3DTEXTURE9 name_mamamoo;

LPDIRECT3DTEXTURE9 inGame;

LPDIRECT3DTEXTURE9 ingame_ui;

LPDIRECT3DTEXTURE9 leftbutton;
LPDIRECT3DTEXTURE9 rightbutton;
LPDIRECT3DTEXTURE9 upbutton;

LPDIRECT3DTEXTURE9 leftbutton_effect;
LPDIRECT3DTEXTURE9 upbutton_effect;
LPDIRECT3DTEXTURE9 rightbutton_effect;

LPDIRECT3DTEXTURE9 ln_sprite;
LPDIRECT3DTEXTURE9 un_sprite;
LPDIRECT3DTEXTURE9 rn_sprite;

LPDIRECT3DTEXTURE9 le_sprite;
LPDIRECT3DTEXTURE9 ue_sprite;
LPDIRECT3DTEXTURE9 re_sprite;

LPDIRECT3DTEXTURE9 Star_effect1;
LPDIRECT3DTEXTURE9 Star_effect2;
LPDIRECT3DTEXTURE9 Star_effect3;
LPDIRECT3DTEXTURE9 Star_effect4;

LPDIRECT3DTEXTURE9 text_0;
LPDIRECT3DTEXTURE9 text_1;
LPDIRECT3DTEXTURE9 text_2;
LPDIRECT3DTEXTURE9 text_3;
LPDIRECT3DTEXTURE9 text_4;
LPDIRECT3DTEXTURE9 text_5;
LPDIRECT3DTEXTURE9 text_6;
LPDIRECT3DTEXTURE9 text_7;
LPDIRECT3DTEXTURE9 text_8;
LPDIRECT3DTEXTURE9 text_9;

LPDIRECT3DTEXTURE9 text_combo;
LPDIRECT3DTEXTURE9 text_hit;

LPDIRECT3DTEXTURE9 number_text1;
LPDIRECT3DTEXTURE9 number_text10;

LPDIRECT3DTEXTURE9 hit_text1;
LPDIRECT3DTEXTURE9 hit_text10;

LPDIRECT3DTEXTURE9 heart_text1;
LPDIRECT3DTEXTURE9 heart_text10;

LPDIRECT3DTEXTURE9 text_goal;

LPDIRECT3DTEXTURE9 mamamoo_image;

LPDIRECT3DTEXTURE9 go_screen;
LPDIRECT3DTEXTURE9 text_back;;

LPDIRECT3DTEXTURE9 c_screen;



									 // function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory

void init_game(void);
void do_game_logic(void);
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);

MCI_OPEN_PARMS mbgmopen;
MCI_PLAY_PARMS mbgmplay;
int mbgmID;

MCI_OPEN_PARMS igbgmopen;
MCI_PLAY_PARMS igbgmplay;
int igbgmID;

DWORD hTime;
DWORD hNow;
DWORD eTime;
DWORD eNow;

bool lkone;
bool ukone;
bool rkone;

int leCount[ENEMY_NOTE];
int ueCount[ENEMY_NOTE];
int reCount[ENEMY_NOTE];

int igCombo;
int igHit;
int igHeart;

float main_x;
float ingame_x;

float goal_position;

void Main_position()
{
	main_x--;

	if (main_x < -6087.0f) main_x = 1600.0f;
}

void Ingame_position()
{
	ingame_x--;

	if (ingame_x < -1000.0f) ingame_x = -350.0f;
}


// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

using namespace std;


enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };


//기본 클래스 
class entity {

public:
	float x_pos;
	float y_pos;
	int status;
	int HP;

};


bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1)
{

	if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) < (size0 + size1) * (size0 + size1))
		return true;
	else
		return false;

}

class LeftKey :public entity {
public:
	bool bleft;
	bool bEffcet;

	void fire();
	void super_fire();
	void init(float x, float y);
	void effect(float x, float y);
	bool effect_show();
	void effect_active();
	void effect_hide();

};

void LeftKey::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void LeftKey::effect(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool LeftKey::effect_show()
{
	return bleft;
}

void LeftKey::effect_active()
{
	bleft = true;
}

void LeftKey::effect_hide()
{
	bleft = false;
}

class UpKey :public entity {
public:
	bool bup;
	bool bEffect;

	void fire();
	void super_fire();
	void init(float x, float y);
	void effect(float x, float y);
	bool effect_show();
	void effect_active();
	void effect_hide();

};

void UpKey::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void UpKey::effect(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool UpKey::effect_show()
{
	return bup;
}

void UpKey::effect_active()
{
	bup = true;
}

void UpKey::effect_hide()
{
	bup = false;
}

class RightKey :public entity {
public:
	bool bright;
	bool bEffect;

	void fire();
	void super_fire();
	void init(float x, float y);
	void effect(float x, float y);
	bool effect_show();
	void effect_active();
	void effect_hide();

};

void RightKey::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void RightKey::effect(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool RightKey::effect_show()
{
	return bright;
}

void RightKey::effect_active()
{
	bright = true;
}

void RightKey::effect_hide()
{
	bright = false;
}

// 적 클래스 
class Enemy :public entity {

public:
	void fire();
	void init(float x, float y);
	void move();

	float ex_pos;
	float ey_pos;
	
	bool hit;
	void effect(float x, float y);
	bool effect_show();
	void effect_active();
	void effect_hide();
};

void Enemy::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void Enemy::move()
{
	x_pos -= 5;
}

void Enemy::effect(float x, float y)
{
	ex_pos = x;
	ey_pos = y;
}

bool Enemy::effect_show()
{
	return hit;
}

void Enemy::effect_active()
{
	hit = true;

}

void Enemy::effect_hide()
{
	hit = false;
}

class Left_enemy :public entity {

public:
	bool bShow;
	bool bMove;

	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();

	float ex_pos;
	float ey_pos;

	bool hit;
	void effect(float x, float y);
	bool effect_show();
	void effect_active();
	void effect_hide();
};

void Left_enemy::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void Left_enemy::move()
{
	if (bMove) x_pos -= 10;
}

bool Left_enemy::show()
{
	return bShow;
}

void Left_enemy::active()
{
	bShow = true;
}

void Left_enemy::hide()
{
	bShow = false;
}

void Left_enemy::effect(float x, float y)
{
	ex_pos = x;
	ey_pos = y;
}

bool Left_enemy::effect_show()
{
	return hit;
}

void Left_enemy::effect_active()
{
	hit = true;

}

void Left_enemy::effect_hide()
{
	hit = false;
}

class Up_enemy :public entity {

public:
	bool bShow;
	bool bMove;

	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();

	float ex_pos;
	float ey_pos;

	bool hit;
	void effect(float x, float y);
	bool effect_show();
	void effect_active();
	void effect_hide();
};

void Up_enemy::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void Up_enemy::move()
{
	if (bMove) x_pos -= 10;
}

bool Up_enemy::show()
{
	return bShow;
}

void Up_enemy::active()
{
	bShow = true;
}

void Up_enemy::hide()
{
	bShow = false;
}

void Up_enemy::effect(float x, float y)
{
	ex_pos = x;
	ey_pos = y;
}

bool Up_enemy::effect_show()
{
	return hit;
}

void Up_enemy::effect_active()
{
	hit = true;

}

void Up_enemy::effect_hide()
{
	hit = false;
}

class Right_enemy :public entity {

public:
	bool bShow;
	bool bMove;

	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();

	float ex_pos;
	float ey_pos;

	bool hit;
	void effect(float x, float y);
	bool effect_show();
	void effect_active();
	void effect_hide();
};

void Right_enemy::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

void Right_enemy::move()
{
	if(bMove) x_pos -= 10;
}

bool Right_enemy::show()
{
	return bShow;
}

void Right_enemy::active()
{
	bShow = true;
}

void Right_enemy::hide()
{
	bShow = false;
}

void Right_enemy::effect(float x, float y)
{
	ex_pos = x;
	ey_pos = y;
}

bool Right_enemy::effect_show()
{
	return hit;
}

void Right_enemy::effect_active()
{
	hit = true;

}

void Right_enemy::effect_hide()
{
	hit = false;
}

// 총알 클래스 

class Left_note :public entity {

public:
	bool bShow;
	bool bMove;

	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);
};

bool Left_note::check_collision(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		return true;
	}
	else {
		return false;
	}
}

void Left_note::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool Left_note::show()
{
	return bShow;
}

void Left_note::active()
{
	bShow = true;
}

void Left_note::move()
{
	if(bMove) y_pos -= 20;
}

void Left_note::hide()
{
	bShow = false;
}

class Up_note :public entity {

public:
	bool bShow;
	bool bMove;

	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);
};

bool Up_note::check_collision(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		return true;
	}
	else {
		return false;
	}
}

void Up_note::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool Up_note::show()
{
	return bShow;
}

void Up_note::active()
{
	bShow = true;
}

void Up_note::move()
{
	if(bMove) y_pos -= 20;
}

void Up_note::hide()
{
	bShow = false;
}

class Right_note :public entity {

public:
	bool bShow;
	bool bMove;

	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);
};

bool Right_note::check_collision(float x, float y)
{
	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 32, x, y, 32) == true)
	{
		bShow = false;
		return true;
	}
	else {
		return false;
	}
}

void Right_note::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool Right_note::show()
{
	return bShow;
}

void Right_note::active()
{
	bShow = true;
}

void Right_note::move()
{
	if(bMove) y_pos -= 20;
}

void Right_note::hide()
{
	bShow = false;
}

LeftKey lk;
UpKey uk;
RightKey rk;

Left_note ln[NOTE];
Up_note un[NOTE];
Right_note rn[NOTE];

Left_enemy le[ENEMY_NOTE];
Up_enemy ue[ENEMY_NOTE];
Right_enemy re[ENEMY_NOTE];

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, L"WindowClass", L"Our Direct3D Program",
		WS_EX_TOPMOST | WS_POPUP, 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;

	mbgmopen.lpstrElementName = L"Happy_things.mp3";
	mbgmopen.lpstrDeviceType = L"MPEGVideo";

	mciSendCommand(mbgmID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mbgmopen);

	mbgmID = mbgmopen.wDeviceID;

	igbgmopen.lpstrElementName = L"MAMAMOO.mp3";
	igbgmopen.lpstrDeviceType = L"MPEGVideo";

	mciSendCommand(igbgmID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&igbgmopen);

	igbgmID = igbgmopen.wDeviceID;

	mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mbgmplay);

	while (TRUE)
	{
		DWORD starting_point = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if (mScreen) Main_position();
		if (igScreen) Ingame_position();
		
		do_game_logic();

		render_frame();

		// check the 'escape' key
		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);

		while ((GetTickCount() - starting_point) < 25);
	}

	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static int x;
	static int y;
	switch (message)
	{
	case WM_LBUTTONUP:
	{
		if (mScreen)
		{
			sScreen = true;
			mScreen = false;
			mnA = 0;
			break;
		}
		if (sScreen)
		{
			mciSendCommand(1, MCI_STOP, 0, (DWORD)(LPVOID)&mbgmplay);
			mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mbgmplay);
			mciSendCommand(2, MCI_PLAY, 0, (DWORD)(LPVOID)&igbgmplay);

			mnA = 0;

			igScreen = true;
			sScreen = false;
			break;
		}
		if (cScreen)
		{
			mciSendCommand(1, MCI_PLAY, 0, (DWORD)(LPVOID)&mbgmplay);
			
			mnA = 0;
			
			mScreen = true;
			cScreen = false;
			break;
		}
		if (goScreen)
		{
			mciSendCommand(1, MCI_PLAY, 0, (DWORD)(LPVOID)&mbgmplay);
			
			mnA = 0;
			
			mScreen = true;
			goScreen = false;
			break;
		}
		return 0;
	}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	D3DXCreateSprite(d3ddev, &d3dspt);    // create the Direct3D Sprite object

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Main_screen.png",    // the file name
		4487,    // default width
		1200,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&mainScreen);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Music_Note.png",    // the file name
		1200,    // default width
		600,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&music_note);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Select_screen.png",    // the file name
		1600,    // default width
		1200,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&selectScreen);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"songs_text.png",    // the file name
		300,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_song);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"song_name.png",    // the file name
		800,    // default width
		200,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&name_mamamoo);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Ingame_screen.png",    // the file name
		2600,    // default width
		1200,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&inGame);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Ingame_UI.png",    // the file name
		1600,    // default width
		1200,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&ingame_ui);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"left_enemy.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&le_sprite);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Up_enemy.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&ue_sprite);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"right_enemy.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&re_sprite);    // load to sprite
	
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"left_note.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&ln_sprite);    // load to sprite
	
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"up_note.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&un_sprite);    // load to sprite
	
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"right_note.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&rn_sprite);    // load to sprite

	//////////////////////////////////////////////////////////////////////
	
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"left_button.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&leftbutton);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"up_button.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&upbutton);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"right_button.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&rightbutton);    // load to sprite

	////////////////////////////////////////////////////////////////////

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"lb_effect.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&leftbutton_effect);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"ub_effect.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&upbutton_effect);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"rb_effect.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&rightbutton_effect);    // load to sprite
	
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"star_effect1.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&Star_effect1);    // load to sprite
	
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"star_effect2.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&Star_effect2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"star_effect3.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&Star_effect3);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"star_effect4.png",    // the file name
		118,    // default width
		118,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&Star_effect4);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"0_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_0);    // load to sprite


	///// 숫자 /////
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"0_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_0);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"1_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_1);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"2_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"3_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_3);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"4_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_4);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"5_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_5);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"6_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_6);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"7_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_7);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"8_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_8);    // load to sprite
	
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"9_text.png",    // the file name
		80,    // default width
		100,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_9);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"goal_text.png",    // the file name
		600,    // default width
		250,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_goal);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Mamamoo.png",    // the file name
		300,    // default width
		300,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&mamamoo_image);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Game_over.png",    // the file name
		1600,    // default width
		1200,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&go_screen);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"back_text.png",    // the file name
		450,    // default width
		150,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&text_back);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Clear_screen.png",    // the file name
		1600,    // default width
		1200,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&c_screen);    // load to sprite
	return;
}

void Ig_reset()
{
	igCombo = 0;
	igHit = 0;
	igHeart = 20;

	goal_position = 13000.0f;

	//객체 초기화
	lk.init(278, 970);
	lk.bEffcet = true;

	uk.init(410, 970);
	uk.bEffect = true;

	rk.init(540, 970);
	rk.bEffect = true;

	main_x = 0.0f;

	lkone = true;
	ukone = true;
	rkone = true;

	float le_pos = 120.0f;
	float ue_pos = 220.0f;
	float re_pos = 320.0f;

	//적들 초기화 
	//for (int i = 0; i<ENEMY_NUM; i++)
	//{
	//	enemy[i].init(2000, (float)(rand() % 300));
	//	enemy[i].effect(enemy[i].x_pos, enemy[i].y_pos);
	//}

	float ep = 8882000;

	for (int i = 0; i < ENEMY_NOTE; i++)
	{
		le[i].init(ep, 120);
		le[i].bShow = true;
		le[i].bMove = true;

		ue[i].init(ep, 220);
		ue[i].bShow = true;
		ue[i].bMove = true;

		re[i].init(ep, 320);
		re[i].bShow = true;
		re[i].bMove = true;

		ep += 300;
	}

	le[0].init(2580, le_pos);
	ue[0].init(2830, ue_pos);
	le[1].init(3000, le_pos);
	re[0].init(3230, re_pos);

	le[2].init(3200, le_pos);
	ue[1].init(3480, ue_pos);
	le[3].init(3650, le_pos);
	re[1].init(3880, re_pos);

	le[4].init(3830, le_pos);
	ue[2].init(4080, ue_pos);
	le[5].init(4250, le_pos);
	re[2].init(4480, re_pos);

	le[6].init(4500, le_pos);
	le[7].init(4600, le_pos);
	ue[3].init(4780, ue_pos);
	le[8].init(4700, le_pos);
	le[9].init(4900, le_pos);
	re[3].init(5080, re_pos);

	le[10].init(5070, le_pos);
	ue[4].init(5350, ue_pos);
	le[11].init(5520, le_pos);
	re[4].init(5750, re_pos);

	le[12].init(5750, le_pos);
	ue[5].init(6000, ue_pos);
	le[13].init(6170, le_pos);
	re[5].init(6400, re_pos);

	le[14].init(6350, le_pos);
	ue[6].init(6600, ue_pos);
	le[15].init(6770, le_pos);
	re[6].init(7000, re_pos);

	le[16].init(7020, le_pos);
	le[17].init(7120, le_pos);
	ue[7].init(7270, ue_pos);
	ue[8].init(7370, ue_pos);
	re[7].init(7520, re_pos);
	re[8].init(7620, re_pos);
	le[18].init(7460, le_pos);
	ue[9].init(7580, ue_pos);
	re[9].init(7700, re_pos);

	le[19].init(7650, le_pos);
	ue[10].init(7800, ue_pos);
	re[10].init(7950, re_pos);
	le[20].init(8010, le_pos);
	re[11].init(8300, re_pos);

	le[21].init(8300, le_pos);
	ue[11].init(8450, ue_pos);
	re[12].init(8600, re_pos);
	le[22].init(8660, le_pos);
	re[13].init(8950, re_pos);

	ue[12].init(9000, ue_pos);

	le[23].init(9200, le_pos);
	ue[13].init(9350, ue_pos);
	re[14].init(9500, re_pos);
	le[24].init(9400, le_pos);
	ue[14].init(9550, ue_pos);
	re[15].init(9700, re_pos);

	re[16].init(10300, re_pos);
	ue[15].init(10300, ue_pos);
	le[25].init(10300, le_pos);
	re[17].init(10650, re_pos);
	le[26].init(10550, le_pos);

	re[18].init(10300 + 650, re_pos);
	ue[16].init(10300 + 650, ue_pos);
	le[27].init(10300 + 650, le_pos);
	re[19].init(10650 + 650, re_pos);
	le[28].init(10550 + 650, le_pos);

	ue[17].init(10300 + 650 + 500, ue_pos);

	le[29].init(10300 + 650 + 500 + 400, le_pos);
	ue[18].init(10300 + 650 + 500 + 400, ue_pos);
	re[20].init(10300 + 650 + 500 + 400, re_pos);
	le[30].init(10300 + 650 + 500 + 600, le_pos);
	ue[19].init(10300 + 650 + 500 + 600, ue_pos);
	re[21].init(10300 + 650 + 500 + 600, re_pos);

	for (int i = 0; i < NOTE; i++)
	{
		ln[i].bMove = true;
		un[i].bMove = true;
		rn[i].bMove = true;
	}

	//총알 초기화 
	for (int i = 0; i<NOTE; i++)
	{
		ln[i].init(lk.x_pos, lk.y_pos);
	}

	for (int i = 0; i<NOTE; i++)
	{
		un[i].init(uk.x_pos, uk.y_pos);
	}

	for (int i = 0; i<NOTE; i++)
	{
		rn[i].init(rk.x_pos, rk.y_pos);
	}
}

void init_game(void)
{
	mScreen = true;
	sScreen = false;
	igScreen = false;
	cScreen = false;
	goScreen = false;

	mnA = 0;

	Ig_reset();
}


void do_game_logic(void)
{
	if (mScreen)
	{
		if(mnA < 255) mnA++;
	}
	if (goScreen)
	{
		if (mnA < 255)
		{
			mnA++;
			mnA++;
			mnA++;
		}
	}
	if (cScreen)
	{
		if (mnA < 255)
		{
			mnA++;
			mnA++;
			mnA++;
		}
	}

	if (igScreen)
	{
		goal_position -= 10;

		if (goal_position == 600)
		{
			Ig_reset();
			mciSendCommand(2, MCI_STOP, 0, (DWORD)(LPVOID)&igbgmplay);
			mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
			igScreen = false;
			cScreen = true;
		}

		//// 1 자리 ////
		if ((igCombo % 10) == 0)
		{
			number_text1 = text_0;
		}
		if ((igCombo % 10) == 1)
		{
			number_text1 = text_1;
		}
		if ((igCombo % 10) == 2)
		{
			number_text1 = text_2;
		}
		if ((igCombo % 10) == 3)
		{
			number_text1 = text_3;
		}
		if ((igCombo % 10) == 4)
		{
			number_text1 = text_4;
		}
		if ((igCombo % 10) == 5)
		{
			number_text1 = text_5;
		}
		if ((igCombo % 10) == 6)
		{
			number_text1 = text_6;
		}
		if ((igCombo % 10) == 7)
		{
			number_text1 = text_7;
		}
		if ((igCombo % 10) == 8)
		{
			number_text1 = text_8;
		}
		if ((igCombo % 10) == 9)
		{
			number_text1 = text_9;
		}

		//// 10 자리 ////
		if ((igCombo % 100) >= 0)
		{
			if ((igCombo % 100) < 10) number_text10 = text_0;
		}
		if ((igCombo % 100) >= 10)
		{
			if ((igCombo % 100) < 20) number_text10 = text_1;
		}
		if ((igCombo % 100) >= 20)
		{
			if ((igCombo % 100) < 30) number_text10 = text_2;
		}
		if ((igCombo % 100) >= 30)
		{
			if ((igCombo % 100) < 40) number_text10 = text_3;
		}
		if ((igCombo % 100) >= 40)
		{
			if ((igCombo % 100) < 50) number_text10 = text_4;
		}
		if ((igCombo % 100) >= 50)
		{
			if ((igCombo % 100) < 60) number_text10 = text_5;
		}
		if ((igCombo % 100) >= 60)
		{
			if ((igCombo % 100) < 70) number_text10 = text_6;
		}
		if ((igCombo % 100) >= 70)
		{
			if ((igCombo % 100) < 80) number_text10 = text_7;
		}
		if ((igCombo % 100) >= 80)
		{
			if ((igCombo % 100) < 90) number_text10 = text_8;
		}
		if ((igCombo % 100) >= 90)
		{
			if ((igCombo % 100) < 100) number_text10 = text_9;
		}

		//// HIT ////

		if ((igHit % 10) == 0)
		{
			hit_text1 = text_0;
		}
		if ((igHit % 10) == 1)
		{
			hit_text1 = text_1;
		}
		if ((igHit % 10) == 2)
		{
			hit_text1 = text_2;
		}
		if ((igHit % 10) == 3)
		{
			hit_text1 = text_3;
		}
		if ((igHit % 10) == 4)
		{
			hit_text1 = text_4;
		}
		if ((igHit % 10) == 5)
		{
			hit_text1 = text_5;
		}
		if ((igHit % 10) == 6)
		{
			hit_text1 = text_6;
		}
		if ((igHit % 10) == 7)
		{
			hit_text1 = text_7;
		}
		if ((igHit % 10) == 8)
		{
			hit_text1 = text_8;
		}
		if ((igHit % 10) == 9)
		{
			hit_text1 = text_9;
		}

		//// HIT 10 ////

		if ((igHit % 100) >= 0)
		{
			if ((igHit % 100) < 10) hit_text10 = text_0;
		}
		if ((igHit % 100) >= 10)
		{
			if ((igHit % 100) < 20) hit_text10 = text_1;
		}
		if ((igHit % 100) >= 20)
		{
			if ((igHit % 100) < 30) hit_text10 = text_2;
		}
		if ((igHit % 100) >= 30)
		{
			if ((igHit % 100) < 40) hit_text10 = text_3;
		}
		if ((igHit % 100) >= 40)
		{
			if ((igHit % 100) < 50) hit_text10 = text_4;
		}
		if ((igHit % 100) >= 50)
		{
			if ((igHit % 100) < 60) hit_text10 = text_5;
		}
		if ((igHit % 100) >= 60)
		{
			if ((igHit % 100) < 70) hit_text10 = text_6;
		}
		if ((igHit % 100) >= 70)
		{
			if ((igHit % 100) < 80) hit_text10 = text_7;
		}
		if ((igHit % 100) >= 80)
		{
			if ((igHit % 100) < 90) hit_text10 = text_8;
		}
		if ((igHit % 100) >= 90)
		{
			if ((igHit % 100) < 100) hit_text10 = text_9;
		}

		//// HEART ////

		if ((igHeart % 10) == 0)
		{
			heart_text1 = text_0;
		}
		if ((igHeart % 10) == 1)
		{
			heart_text1 = text_1;
		}
		if ((igHeart % 10) == 2)
		{
			heart_text1 = text_2;
		}
		if ((igHeart % 10) == 3)
		{
			heart_text1 = text_3;
		}
		if ((igHeart % 10) == 4)
		{
			heart_text1 = text_4;
		}
		if ((igHeart % 10) == 5)
		{
			heart_text1 = text_5;
		}
		if ((igHeart % 10) == 6)
		{
			heart_text1 = text_6;
		}
		if ((igHeart % 10) == 7)
		{
			heart_text1 = text_7;
		}
		if ((igHeart % 10) == 8)
		{
			heart_text1 = text_8;
		}
		if ((igHeart % 10) == 9)
		{
			heart_text1 = text_9;
		}

		//// HEART 10 ////

		if ((igHeart % 100) >= 0)
		{
			if ((igHeart % 100) < 10) heart_text10 = text_0;
		}
		if ((igHeart % 100) >= 10)
		{
			if ((igHeart % 100) < 20) heart_text10 = text_1;
		}
		if (igHeart == 20)
		{
			heart_text10 = text_2;
		}
		

		/////////////////////////////////////////////////

		for (int i = 0; i < ENEMY_NOTE; i++)
		{
			if (le[i].x_pos < 0)
			{
				le[i].hide();
				igCombo = 0;
				igHeart--;
				le[i].bMove = false;
				le[i].init(1600.0f, 0.0f);
			}
			else
				le[i].move();

			if (ue[i].x_pos < 0)
			{
				ue[i].hide();
				igCombo = 0;
				igHeart--;
				ue[i].bMove = false;
				ue[i].init(1600.0f, 0.0f);
			}
			else
				ue[i].move();

			if (re[i].x_pos < 0)
			{
				re[i].hide();
				igCombo = 0;
				igHeart--;
				re[i].bMove = false;
				re[i].init(1600.0f, 0.0f);
			}
			else re[i].move();

			if (igHeart == 0)
			{
				Ig_reset();
				mciSendCommand(2, MCI_STOP, 0, (DWORD)(LPVOID)&igbgmplay);
				mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
				igScreen = false;
				goScreen = true;

			}
		}

		if (KEY_DOWN(VK_LEFT))
		{
			lk.bEffcet = false;

			if (lkone)
			{
				for (int i = 0; i < NOTE; i++)
				{
					if (ln[i].show() == false)
					{
						ln[i].active();
						ln[i].init(lk.x_pos, lk.y_pos);
						lkone = false;
						break;
					}
				}
			}
		}
		if (KEY_UP(VK_LEFT))
		{
			lkone = true;
			lk.bEffcet = true;
		}

		if (KEY_DOWN(VK_UP))
		{
			uk.bEffect = false;

			if (ukone)
			{
				for (int i = 0; i < NOTE; i++)
				{
					if (un[i].show() == false)
					{
						un[i].active();
						un[i].init(uk.x_pos, uk.y_pos);
						ukone = false;
						break;
					}
				}
			}
		}
		if (KEY_UP(VK_UP))
		{
			ukone = true;
			uk.bEffect = true;
		}

		if (KEY_DOWN(VK_RIGHT))
		{
			rk.bEffect = false;

			if (rkone)
			{
				for (int i = 0; i < NOTE; i++)
				{
					if (rn[i].show() == false)
					{
						rn[i].active();
						rn[i].init(rk.x_pos, rk.y_pos);
						rkone = false;
						break;
					}
				}
			}
		}
		if (KEY_UP(VK_RIGHT))
		{
			rkone = true;
			rk.bEffect = true;
		}

		for (int i = 0; i < NOTE; i++)
		{
			if (ln[i].show() == true)
			{
				if (ln[i].y_pos < -70)
				{
					ln[i].hide();
					//igCombo = 0;
				}
				else ln[i].move();

				//충돌 처리 
				for (int y = 0; y < ENEMY_NOTE; y++)
				{
					if (ln[i].check_collision(le[y].x_pos, le[y].y_pos) == true)
					{
						le[y].effect(le[y].x_pos, le[y].y_pos);
						le[y].effect_active();
						//eTime = timeGetTime() / 1000;
						
						le[y].init(1600.0f, 0.0f);
						le[y].hide();
						le[y].bMove = false;

						igCombo++;
						igHit++;
						break;
					}
				}
			}
		}
		
		for (int i = 0; i < NOTE; i++)
		{
			if (un[i].show() == true)
			{
				if (un[i].y_pos < -70)
				{
					un[i].hide();
					//igCombo = 0;
				}
				else un[i].move();

				//충돌 처리 
				for (int y = 0; y < ENEMY_NOTE; y++)
				{
					if (un[i].check_collision(ue[y].x_pos, ue[y].y_pos) == true)
					{
						ue[y].effect(ue[y].x_pos, ue[y].y_pos);
						ue[y].effect_active();
						//eTime = timeGetTime() / 1000;

						ue[y].init(1600.0f, 0.0f);
						ue[y].hide();
						ue[y].bMove = false;

						igCombo++;
						igHit++;
						break;
					}
				}
			}
		}
		
		for (int i = 0; i < NOTE; i++)
		{
			if (rn[i].show() == true)
			{
				if (rn[i].y_pos < -70)
				{
					rn[i].hide();
					//igCombo = 0;
				}
				else rn[i].move();

				//충돌 처리 
				for (int y = 0; y < ENEMY_NOTE; y++)
				{
					if (rn[i].check_collision(re[y].x_pos, re[y].y_pos) == true)
					{
						re[y].effect(re[y].x_pos, re[y].y_pos);
						re[y].effect_active();
						//eTime = timeGetTime() / 1000;
						
						re[y].init(1600.0f, 0.0f);
						re[y].hide();
						re[y].bMove = false;

						igCombo++;
						igHit++;
						break;
					}
				}
			}
		}
	}
}

// this is the function used to render a single frame
void render_frame(void)
{
		// clear the window to a deep blue
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

		d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

												 //UI 창 렌더링 


												 /*
												 static int frame = 21;    // start the program on the final frame
												 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
												 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

												 // calculate the x-position
												 int xpos = frame * 182 + 1;
												 */
		if (mScreen)
		{
			RECT part0;
			SetRect(&part0, 0, 0, 4487, 1200);
			D3DXVECTOR3 center0(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position0(main_x, 0.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(mainScreen, &part0, &center0, &position0, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT mn_rect;
			SetRect(&mn_rect, 0, 0, 1200, 600);
			D3DXVECTOR3 mncenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 mnposition(200, 300, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(music_note, &mn_rect, &mncenter, &mnposition, D3DCOLOR_ARGB(mnA, 255, 255, 255));
		}

		if (sScreen)
		{
			RECT s_rect;
			SetRect(&s_rect, 0, 0, 1600, 1200);
			D3DXVECTOR3 scenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 sposition(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(selectScreen, &s_rect, &scenter, &sposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT st_rect;
			SetRect(&st_rect, 0, 0, 300, 100);
			D3DXVECTOR3 stcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 stposition(30.0f, 200.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(text_song, &st_rect, &stcenter, &stposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT mamamoo_rect;
			SetRect(&mamamoo_rect, 0, 0, 800, 200);
			D3DXVECTOR3 mamamoocenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 mamamooposition(100.0f, 400.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(name_mamamoo, &mamamoo_rect, &mamamoocenter, &mamamooposition, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (igScreen)
		{
			RECT ig_rect;
			SetRect(&ig_rect, 0, 0, 2600, 1200);
			D3DXVECTOR3 igcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 igposition(ingame_x, 0.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(inGame, &ig_rect, &igcenter, &igposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT ui_rect;
			SetRect(&ui_rect, 0, 0, 1600, 1200);
			D3DXVECTOR3 uicenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 uiposition(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(ingame_ui, &ui_rect, &uicenter, &uiposition, D3DCOLOR_ARGB(255, 255, 255, 255));
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			RECT left_rect;
			SetRect(&left_rect, 0, 0, 118, 118);
			D3DXVECTOR3 lkcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 lkposition(lk.x_pos, lk.y_pos, 0.0f);    // position at 50, 50 with no depth
			if(lk.bEffcet)
				d3dspt->Draw(leftbutton, &left_rect, &lkcenter, &lkposition, D3DCOLOR_ARGB(255, 255, 255, 255));
			if(lk.bEffcet == false)
				d3dspt->Draw(leftbutton_effect, &left_rect, &lkcenter, &lkposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT up_rect;
			SetRect(&up_rect, 0, 0, 118, 118);
			D3DXVECTOR3 ukcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 ukposition(uk.x_pos, uk.y_pos, 0.0f);    // position at 50, 50 with no depth
			if(uk.bEffect)
				d3dspt->Draw(upbutton, &up_rect, &ukcenter, &ukposition, D3DCOLOR_ARGB(255, 255, 255, 255));
			if(uk.bEffect == false)
				d3dspt->Draw(upbutton_effect, &up_rect, &ukcenter, &ukposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT right_rect;
			SetRect(&left_rect, 0, 0, 118, 118);
			D3DXVECTOR3 rkcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 rkposition(rk.x_pos, rk.y_pos, 0.0f);    // position at 50, 50 with no depth
			if(rk.bEffect)
				d3dspt->Draw(rightbutton, &left_rect, &rkcenter, &rkposition, D3DCOLOR_ARGB(255, 255, 255, 255));
			if(rk.bEffect == false)
				d3dspt->Draw(rightbutton_effect, &left_rect, &rkcenter, &rkposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			////////////////////////////////////////////////////////////////////////////////////////////////////////


			////총알 
			for (int i = 0; i < NOTE; i++)
			{
				if (ln[i].bShow == true)
				{
					RECT ln_rect;
					SetRect(&ln_rect, 0, 0, 118, 118);
					D3DXVECTOR3 lncenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
					D3DXVECTOR3 lnposition(ln[i].x_pos, ln[i].y_pos, 0.0f);    // position at 50, 50 with no depth
					d3dspt->Draw(ln_sprite, &ln_rect, &lncenter, &lnposition, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}

			for (int i = 0; i < NOTE; i++)
			{
				if (un[i].bShow == true)
				{
					RECT un_rect;
					SetRect(&un_rect, 0, 0, 118, 118);
					D3DXVECTOR3 uncenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
					D3DXVECTOR3 unposition(un[i].x_pos, un[i].y_pos, 0.0f);    // position at 50, 50 with no depth
					d3dspt->Draw(un_sprite, &un_rect, &uncenter, &unposition, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}

			for (int i = 0; i < NOTE; i++)
			{
				if (rn[i].bShow == true)
				{
					RECT rn_rect;
					SetRect(&rn_rect, 0, 0, 118, 118);
					D3DXVECTOR3 rncenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
					D3DXVECTOR3 rnposition(rn[i].x_pos, rn[i].y_pos, 0.0f);    // position at 50, 50 with no depth
					d3dspt->Draw(rn_sprite, &rn_rect, &rncenter, &rnposition, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////
			
			RECT le_rect;
			SetRect(&le_rect, 0, 0, 118, 118);
			D3DXVECTOR3 lecenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

			for (int i = 0; i < ENEMY_NOTE; i++)
			{
				if (le[i].bShow == true)
				{
					D3DXVECTOR3 leposition(le[i].x_pos, le[i].y_pos, 0.0f);    // position at 50, 50 with no depth
					d3dspt->Draw(le_sprite, &le_rect, &lecenter, &leposition, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}

			RECT le_star;
			SetRect(&le_star, 0, 0, 118, 118);
			D3DXVECTOR3 leStarcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

			for (int i = 0; i < ENEMY_NOTE; i++)
			{
				D3DXVECTOR3 leStarposition(lk.x_pos, 120, 0.0f);    // position at 50, 50 with no depth

				if (le[i].hit)
				{
					int count = 0;
					for (int j = 0; j <= 1000; j++)
					{
						count += 1;
						if (count == 0)
						{
							d3dspt->Draw(Star_effect1, &le_star, &leStarcenter, &leStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
						if (count == 250)
						{
							d3dspt->Draw(Star_effect2, &le_star, &leStarcenter, &leStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
						if (count == 500)
						{
							d3dspt->Draw(Star_effect3, &le_star, &leStarcenter, &leStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
						if (count == 750)
						{
							d3dspt->Draw(Star_effect4, &le_star, &leStarcenter, &leStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
					}
					if (count >= 1000)
					{
						le[i].effect_hide();
					}
				}
			}
			
			RECT ue_rect;
			SetRect(&ue_rect, 0, 0, 118, 118);
			D3DXVECTOR3 uecenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

			for (int i = 0; i < ENEMY_NOTE; i++)
			{
				if (ue[i].bShow == true)
				{
					D3DXVECTOR3 ueposition(ue[i].x_pos, ue[i].y_pos, 0.0f);    // position at 50, 50 with no depth
					d3dspt->Draw(ue_sprite, &ue_rect, &uecenter, &ueposition, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}

			RECT ue_star;
			SetRect(&ue_star, 0, 0, 118, 118);
			D3DXVECTOR3 ueStarcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

			for (int i = 0; i < ENEMY_NOTE; i++)
			{
				D3DXVECTOR3 ueStarposition(uk.x_pos, 220, 0.0f);    // position at 50, 50 with no depth
				
				if (ue[i].hit)
				{
					int count = 0;
					for (int j = 0; j <= 1000; j++)
					{
						count += 1;
						if (count == 0)
						{
							d3dspt->Draw(Star_effect1, &ue_star, &ueStarcenter, &ueStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
						if(count == 250)
						{
							d3dspt->Draw(Star_effect2, &ue_star, &ueStarcenter, &ueStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
						if (count == 500)
						{
							d3dspt->Draw(Star_effect3, &ue_star, &ueStarcenter, &ueStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
						if (count == 750)
						{
							d3dspt->Draw(Star_effect4, &ue_star, &ueStarcenter, &ueStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
					}
					if (count >= 1000)
					{
						ue[i].effect_hide();
					}
				}
			}

			RECT re_rect;
			SetRect(&re_rect, 0, 0, 118, 118);
			D3DXVECTOR3 recenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

			for (int i = 0; i < ENEMY_NOTE; i++)
			{
				if (re[i].bShow == true)
				{
					D3DXVECTOR3 reposition(re[i].x_pos, re[i].y_pos, 0.0f);    // position at 50, 50 with no depth
					d3dspt->Draw(re_sprite, &re_rect, &recenter, &reposition, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}

			RECT re_star;
			SetRect(&re_star, 0, 0, 118, 118);
			D3DXVECTOR3 reStarcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

			for (int i = 0; i < ENEMY_NOTE; i++)
			{
				D3DXVECTOR3 reStarposition(rk.x_pos, 320, 0.0f);    // position at 50, 50 with no depth

				if (re[i].hit)
				{
					int count = 0;
					for (int j = 0; j <= 1000; j++)
					{
						count += 1;
						if (count == 0)
						{
							d3dspt->Draw(Star_effect1, &re_star, &reStarcenter, &reStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
						if (count == 250)
						{
							d3dspt->Draw(Star_effect2, &re_star, &reStarcenter, &reStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
						if (count == 500)
						{
							d3dspt->Draw(Star_effect3, &re_star, &reStarcenter, &reStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
						if (count == 750)
						{
							d3dspt->Draw(Star_effect4, &re_star, &reStarcenter, &reStarposition, D3DCOLOR_ARGB(255, 255, 255, 255));
						}
					}
					if (count >= 1000)
					{
						re[i].effect_hide();
					}
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////
			///// TEXTS /////

			RECT combo_rect1;
			SetRect(&combo_rect1, 0, 0, 80, 100);
			D3DXVECTOR3 c1center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 c1position(1250, 550, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(number_text1, &combo_rect1, &c1center, &c1position, D3DCOLOR_ARGB(255, 255, 255, 255));

			if (igCombo >= 10)
			{
				RECT combo_rect10;
				SetRect(&combo_rect10, 0, 0, 80, 100);
				D3DXVECTOR3 c10center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 c10position(1200, 550, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(number_text10, &combo_rect10, &c10center, &c10position, D3DCOLOR_ARGB(255, 255, 255, 255));
			}

			RECT hit_rect1;
			SetRect(&hit_rect1, 0, 0, 80, 100);
			D3DXVECTOR3 h1center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 h1position(950, 425, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(hit_text1, &hit_rect1, &h1center, &h1position, D3DCOLOR_ARGB(255, 255, 255, 255));

			if (igHit >= 10)
			{
				RECT hit_rect10;
				SetRect(&hit_rect10, 0, 0, 80, 100);
				D3DXVECTOR3 h10center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 h10position(900, 425, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(hit_text10, &hit_rect10, &h10center, &h10position, D3DCOLOR_ARGB(255, 255, 255, 255));
			}

			RECT heart_rect1;
			SetRect(&heart_rect1, 0, 0, 80, 100);
			D3DXVECTOR3 hp1center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 hp1position(150, 450, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(heart_text1, &heart_rect1, &hp1center, &hp1position, D3DCOLOR_ARGB(255, 255, 255, 255));
			
			if (igHeart >= 10)
			{
				RECT heart_rect10;
				SetRect(&heart_rect10, 0, 0, 80, 100);
				D3DXVECTOR3 hp10center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 hp10position(100, 450, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(heart_text10, &heart_rect10, &hp10center, &hp10position, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			RECT goal_rect;
			SetRect(&goal_rect, 0, 0, 600, 250);
			D3DXVECTOR3 goalcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 goalposition(goal_position, 150, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(text_goal, &goal_rect, &goalcenter, &goalposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT image_rect;
			SetRect(&image_rect, 0, 0, 300, 300);
			D3DXVECTOR3 imagecenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 imageposition(1000, 700, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(mamamoo_image, &image_rect, &imagecenter, &imageposition, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		if (goScreen)
		{
			RECT go_rect;
			SetRect(&go_rect, 0, 0, 1600, 1200);
			D3DXVECTOR3 gocenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 goposition(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(go_screen, &go_rect, &gocenter, &goposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT back_rect;
			SetRect(&back_rect, 0, 0, 450, 150);
			D3DXVECTOR3 backcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 backposition(1000.0f, 1030.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(text_back, &back_rect, &backcenter, &backposition, D3DCOLOR_ARGB(mnA, 255, 255, 255));
		}

		if (cScreen)
		{
			RECT c_rect;
			SetRect(&c_rect, 0, 0, 1600, 1200);
			D3DXVECTOR3 ccenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 cposition(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(c_screen, &c_rect, &ccenter, &cposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT back_rect;
			SetRect(&back_rect, 0, 0, 450, 150);
			D3DXVECTOR3 backcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 backposition(1000.0f, 1030.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(text_back, &back_rect, &backcenter, &backposition, D3DCOLOR_ARGB(mnA, 255, 255, 255));
		}

		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);
		return;
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	d3ddev->Release();
	d3d->Release();
	
	return;
}
