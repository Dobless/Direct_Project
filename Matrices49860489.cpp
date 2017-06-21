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

#define ENEMY_NUM 10 
#define BULLET_NUM 100

#define LEFT_NOTE 100
#define UP_NOTE 100
#define RIGHT_NOTE 100


bool mScreen = true;
bool igScreen = false;

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface

						// sprite declarations
LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 inGame;

//LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_bullet;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_effect;
LPDIRECT3DTEXTURE9 leftbutton;
LPDIRECT3DTEXTURE9 rightbutton;
LPDIRECT3DTEXTURE9 upbutton;
LPDIRECT3DTEXTURE9 ln_sprite;
LPDIRECT3DTEXTURE9 un_sprite;
LPDIRECT3DTEXTURE9 rn_sprite;

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

bool one;
bool lkone;
bool ukone;
bool rkone;

float main_x;
float ingame_x;

void Main_position()
{
	main_x--;

	if (main_x < -6087.0f) main_x = 1600.0f;
}

void Ingame_position()
{
	ingame_x--;

	if (ingame_x < -1000.0f) ingame_x = 0.0f;
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



//주인공 클래스 
//class Hero :public entity {
//public:
//	bool space;
//
//	void fire();
//	void super_fire();
//	void move(int i);
//	void init(float x, float y);
//	void effect(float x, float y);
//	bool effect_show();
//	void effect_active();
//	void effect_hide();
//
//};
//
//void Hero::init(float x, float y)
//{
//	x_pos = x;
//	y_pos = y;
//}
//
//void Hero::effect(float x, float y)
//{
//	x_pos = x;
//	y_pos = y;
//}
//
//bool Hero::effect_show()
//{
//	return space;
//}
//
//void Hero::effect_active()
//{
//	space = true;
//}
//
//void Hero::effect_hide()
//{
//	space = false;
//}
//
//void Hero::move(int i)
//{
//	switch (i)
//	{
//	case MOVE_UP:
//		y_pos -= 3;
//		break;
//
//	case MOVE_DOWN:
//		y_pos += 3;
//		break;
//
//	case MOVE_LEFT:
//		x_pos -= 3;
//		break;
//
//	case MOVE_RIGHT:
//		x_pos += 3;
//		break;
//	}
//}

class LeftKey :public entity {
public:
	bool bleft;

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


// 총알 클래스 
class Bullet :public entity {

public:
	bool bShow;

	void init(float x, float y);
	void move();
	bool show();
	void hide();
	void active();
	bool check_collision(float x, float y);
};

bool Bullet::check_collision(float x, float y)
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

void Bullet::init(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

bool Bullet::show()
{
	return bShow;
}

void Bullet::active()
{
	bShow = true;
}

void Bullet::move()
{
	y_pos -= 8;
}

void Bullet::hide()
{
	bShow = false;
}

class Left_note :public entity {

public:
	bool bShow;

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
	y_pos -= 8;
}

void Left_note::hide()
{
	bShow = false;
}

class Up_note :public entity {

public:
	bool bShow;

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
	y_pos -= 8;
}

void Up_note::hide()
{
	bShow = false;
}

class Right_note :public entity {

public:
	bool bShow;

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
	y_pos -= 8;
}

void Right_note::hide()
{
	bShow = false;
}

Enemy enemy[ENEMY_NUM];
Bullet bullet[BULLET_NUM];

LeftKey lk;
UpKey uk;
RightKey rk;

Left_note ln[LEFT_NOTE];
Up_note un[UP_NOTE];
Right_note rn[RIGHT_NOTE];

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
		WS_EX_TOPMOST | WS_POPUP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
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
			mciSendCommand(1, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mbgmplay);

			igbgmopen.lpstrElementName = L"MAMAMOO.mp3";
			igbgmopen.lpstrDeviceType = L"MPEGVideo";

			mciSendCommand(igbgmID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&igbgmopen);

			igbgmID = igbgmopen.wDeviceID;

			mciSendCommand(2, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&igbgmplay);

			mScreen = false;
			igScreen = true;
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
		&sprite);    // load to sprite

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

	//D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
	//	L"hero.png",    // the file name
	//	64,    // default width
	//	64,    // default height
	//	D3DX_DEFAULT,    // no mip mapping
	//	NULL,    // regular usage
	//	D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
	//	D3DPOOL_MANAGED,    // typical memory handling
	//	D3DX_DEFAULT,    // no filtering
	//	D3DX_DEFAULT,    // no mip filtering
	//	D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
	//	NULL,    // no image info struct
	//	NULL,    // not using 256 colors
	//	&sprite_hero);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"effect.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_effect);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"enemy.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"bullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_bullet);    // load to sprite
	
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
	return;
}


void init_game(void)
{
	mScreen = true;
	igScreen = false;

	//객체 초기화
	lk.init(300, 1000);
	uk.init(450, 1000);
	rk.init(600, 1000);

	main_x = 0.0f;

	one = true;
	lkone = true;
	ukone = true;
	rkone = true;


	//적들 초기화 
	for (int i = 0; i<ENEMY_NUM; i++)
	{
		enemy[i].init(2000, (float)(rand() % 300));
		enemy[i].effect(enemy[i].x_pos, enemy[i].y_pos);
	}

	//총알 초기화 
	//for (int i = 0; i<BULLET_NUM; i++)
	//{
	//	bullet[i].init(hero.x_pos, hero.y_pos);
	//}

	for (int i = 0; i<LEFT_NOTE; i++)
	{
		bullet[i].init(lk.x_pos, lk.y_pos);
	}

	for (int i = 0; i<UP_NOTE; i++)
	{
		bullet[i].init(uk.x_pos, uk.y_pos);
	}

	for (int i = 0; i<RIGHT_NOTE; i++)
	{
		bullet[i].init(rk.x_pos, rk.y_pos);
	}
}


void do_game_logic(void)
{
	//주인공 처리 
	//if (KEY_DOWN(VK_UP))
	//	hero.move(MOVE_UP);
	//
	//if (KEY_DOWN(VK_DOWN))
	//	hero.move(MOVE_DOWN);
	//
	//if (KEY_DOWN(VK_LEFT))
	//	hero.move(MOVE_LEFT);
	//
	//if (KEY_DOWN(VK_RIGHT))
	//	hero.move(MOVE_RIGHT);
	//
	//if (KEY_DOWN(VK_SPACE))
	//{
	//	hero.effect_active();
	//	hero.effect(hero.x_pos, hero.y_pos);
	//}
	
	if (igScreen)
	{
		//적들 처리 
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemy[i].x_pos < 0)
				enemy[i].init(2000, (float)(rand() % 300));
			else
				enemy[i].move();
		}

		if (KEY_DOWN(VK_LEFT))
		{
			if (lkone)
			{
				for (int i = 0; i < LEFT_NOTE; i++)
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
		}

		if (KEY_DOWN(VK_UP))
		{
			if (ukone)
			{
				for (int i = 0; i < UP_NOTE; i++)
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
		}

		if (KEY_DOWN(VK_RIGHT))
		{
			if (rkone)
			{
				for (int i = 0; i < RIGHT_NOTE; i++)
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
		}

		for (int i = 0; i < LEFT_NOTE; i++)
		{
			if (ln[i].show() == true)
			{
				if (ln[i].y_pos < -70) ln[i].hide();
				else ln[i].move();

				//충돌 처리 
				for (int y = 0; y < ENEMY_NUM; y++)
				{
					if (ln[i].check_collision(enemy[y].x_pos, enemy[y].y_pos) == true)
					{
						enemy[y].effect(enemy[y].x_pos, enemy[y].y_pos);
						enemy[y].effect_active();
						eTime = timeGetTime() / 1000;

						enemy[y].init(2000, (float)(rand() % 300));
						break;
					}
				}
			}
		}
		
		for (int i = 0; i < UP_NOTE; i++)
		{
			if (un[i].show() == true)
			{
				if (un[i].y_pos < -70) bullet[i].hide();
				else un[i].move();

				//충돌 처리 
				for (int y = 0; y < ENEMY_NUM; y++)
				{
					if (un[i].check_collision(enemy[y].x_pos, enemy[y].y_pos) == true)
					{
						enemy[y].effect(enemy[y].x_pos, enemy[y].y_pos);
						enemy[y].effect_active();
						eTime = timeGetTime() / 1000;

						enemy[y].init(2000, (float)(rand() % 300));
						break;
					}
				}
			}
		}
		
		for (int i = 0; i < RIGHT_NOTE; i++)
		{
			if (rn[i].show() == true)
			{
				if (rn[i].y_pos < -70) rn[i].hide();
				else rn[i].move();

				//충돌 처리 
				for (int y = 0; y < ENEMY_NUM; y++)
				{
					if (rn[i].check_collision(enemy[y].x_pos, enemy[y].y_pos) == true)
					{
						enemy[y].effect(enemy[y].x_pos, enemy[y].y_pos);
						enemy[y].effect_active();
						eTime = timeGetTime() / 1000;

						enemy[y].init(2000, (float)(rand() % 300));
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
			d3dspt->Draw(sprite, &part0, &center0, &position0, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		//주인공 
		//RECT part;
		//SetRect(&part, 0, 0, 64, 64);
		//D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		//D3DXVECTOR3 position(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
		//d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));

		if (igScreen)
		{
			RECT ig_rect;
			SetRect(&ig_rect, 0, 0, 2600, 1200);
			D3DXVECTOR3 igcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 igposition(ingame_x, 0.0f, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(inGame, &ig_rect, &igcenter, &igposition, D3DCOLOR_ARGB(255, 255, 255, 255));
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			RECT left_rect;
			SetRect(&left_rect, 0, 0, 118, 118);
			D3DXVECTOR3 lkcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 lkposition(lk.x_pos, lk.y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(leftbutton, &left_rect, &lkcenter, &lkposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT up_rect;
			SetRect(&up_rect, 0, 0, 118, 118);
			D3DXVECTOR3 ukcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 ukposition(uk.x_pos, uk.y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(upbutton, &up_rect, &ukcenter, &ukposition, D3DCOLOR_ARGB(255, 255, 255, 255));

			RECT right_rect;
			SetRect(&left_rect, 0, 0, 118, 118);
			D3DXVECTOR3 rkcenter(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 rkposition(rk.x_pos, rk.y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(rightbutton, &left_rect, &rkcenter, &rkposition, D3DCOLOR_ARGB(255, 255, 255, 255));
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////


			////총알 
			for (int i = 0; i < LEFT_NOTE; i++)
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

			for (int i = 0; i < UP_NOTE; i++)
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

			for (int i = 0; i < RIGHT_NOTE; i++)
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



			////에네미 
			RECT part2;
			SetRect(&part2, 0, 0, 64, 64);
			D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

			for (int i = 0; i < ENEMY_NUM; i++)
			{
				D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
			}

			RECT part4;
			SetRect(&part4, 0, 0, 64, 64);
			D3DXVECTOR3 center4(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

			eNow = timeGetTime() / 1000;
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				if (enemy[i].hit == true)
				{
					D3DXVECTOR3 position4(enemy[i].ex_pos, enemy[i].ey_pos, 0.0f);    // position at 50, 50 with no depth
					d3dspt->Draw(sprite_effect, &part4, &center4, &position4, D3DCOLOR_ARGB(255, 255, 255, 255));


					if (eNow - eTime >= 1.0f)         //흐른시간이 1초이상이면 내가 하고싶은것 처리
					{
						enemy[i].effect_hide();
					}
				}
			}
		}

		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);
		return;
	//}
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	d3ddev->Release();
	d3d->Release();
	
	//if (mScreen)
	//{
	//	sprite->Release();
	//}
	//
	////객체 해제 
	////sprite_hero->Release();
	//
	//if (igScreen)
	//{
	//	sprite_enemy->Release();
	//	sprite_bullet->Release();
	//	sprite_effect->Release();
	//}
	return;
}
