// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

// 음악 관련
#include <mmsystem.h>
#include <strmif.h>
#include <control.h>
#include <uuids.h>

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 380
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#define ENEMY_NUM 10 
#define BULLET_NUM 10


// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// 음악 관련
#pragma comment(lib, "strmiids.lib")

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface



						// sprite declarations
LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hero;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_bullet;    // the pointer to the sprite



									 // function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory

void init_game(void);
void do_game_logic(void);
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);


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
class Hero :public entity {

public:
	void fire();
	void super_fire();
	void move(int i);
	void init(float x, float y);


};

void Hero::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}

void Hero::move(int i)
{
	switch (i)
	{
	case MOVE_UP:
		y_pos -= 3;
		break;

	case MOVE_DOWN:
		y_pos += 3;
		break;


	case MOVE_LEFT:
		x_pos -= 3;
		break;


	case MOVE_RIGHT:
		x_pos += 3;
		break;

	}

}




// 적 클래스 
class Enemy :public entity {

public:
	void fire();
	void init(float x, float y);
	void move();

};

void Enemy::init(float x, float y)
{

	x_pos = x;
	y_pos = y;

}


void Enemy::move()
{
	y_pos += 2;

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

// 음악 관련
class Mp3
{
public:
	Mp3();
	~Mp3();

	bool Load(LPCWSTR filename);
	void Cleanup();

	bool Play();
	bool Pause();
	bool Stop();

	// msTirmeout이 0이되면 즉시반환
	// mp3가 끝나면 true 반환
	bool WaitForCompletion(long msTimeout, long *EvCode);

	// 볼륨 조절
	bool SetVolume(long vol);
	long GetVolume();

	// 1억분의 1초단위로 시간 반환
	// 10,000,000 == 1초
	// 결과를 1억으로 나눔
	// 초단위의 지속시간
	__int64 GetDuration();

	// 현재 재생 위치 반환
	__int64 GetCurrentPosition();

	//
	bool SetPositions(__int64* pCurrent, __int64* pStop, bool bAbsolutePositioning);

private:
	IGraphBuilder *  pigb;
	IMediaControl *  pimc;
	IMediaEventEx *  pimex;
	IBasicAudio * piba;
	IMediaSeeking * pims;
	bool ready;

	// mp3의 지속시간
	__int64 duration;
};

Mp3::Mp3()
{
	pigb = NULL;
	pimc = NULL;
	pimex = NULL;
	piba = NULL;
	pims = NULL;
	ready = false;
	duration = 0;
}

Mp3::~Mp3()
{
	Cleanup();
}

void Mp3::Cleanup()
{
	if (pimc) pimc->Stop();
	
	if (pigb)
	{
		pigb->Release();
		pigb = NULL;
	}

	if (pimc)
	{
		pimc->Release();
		pimc = NULL;
	}

	if (pimex)
	{
		pimex->Release();
		pimex = NULL;
	}

	if (piba)
	{
		piba->Release();
		piba = NULL;
	}

	if (pims)
	{
		pims->Release();
		pims = NULL;
	}

	ready = false;
}

bool Mp3::Load(LPCWSTR szFile)
{
	Cleanup();
	ready = false;

	if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void **)&this->pigb)))
	{
		pigb->QueryInterface(IID_IMediaControl, (void **)&pimc);
		pigb->QueryInterface(IID_IMediaEventEx, (void **)&pimex);
		pigb->QueryInterface(IID_IBasicAudio, (void**)&piba);
		pigb->QueryInterface(IID_IMediaSeeking, (void**)&pims);

		HRESULT hr = pigb->RenderFile(szFile, NULL);
		if (SUCCEEDED(hr))
		{
			ready = true;
			if (pims)
			{
				pims->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
				pims->GetDuration(&duration); // returns 10,000,000 for a second.
				duration = duration;
			}
		}
	}

	return ready;
}

bool Mp3::Pause()
{
	if (ready&&pimc)
	{
		HRESULT hr = pimc->Pause();
		return SUCCEEDED(hr);
	}

	return false;
}

bool Mp3::Stop()
{
	if (ready&&pimc)
	{
		HRESULT hr = pimc->Stop();
		return SUCCEEDED(hr);
	}

	return false;
}

bool Mp3::WaitForCompletion(long msTimeout, long* EvCode)
{
	if (ready&&pimex)
	{
		HRESULT hr = pimex->WaitForCompletion(msTimeout, EvCode);
		return *EvCode > 0;
	}

	return false;
}

bool Mp3::SetVolume(long vol)
{
	if (ready&&piba)
	{
		HRESULT hr = piba->put_Volume(vol);
		return SUCCEEDED(hr);
	}

	return false;
}

long Mp3::GetVolume()
{
	if (ready&&piba)
	{
		long vol = -1;
		HRESULT hr = piba->get_Volume(&vol);

		if (SUCCEEDED(hr))
			return vol;
	}

	return -1;
}

__int64 Mp3::GetDuration()
{
	return duration;
}

__int64 Mp3::GetCurrentPosition()
{
	if (ready&&pims)
	{
		__int64 curpos = -1;
		HRESULT hr = pims->GetCurrentPosition(&curpos);

		if (SUCCEEDED(hr))
			return curpos;
	}

	return -1;
}

bool Mp3::SetPositions(__int64* pCurrent, __int64* pStop, bool bAbsolutePositioning)
{
	if (ready&&pims)
	{
		DWORD flags = 0;
		if (bAbsolutePositioning)
			flags = AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame;
		else
			flags = AM_SEEKING_RelativePositioning | AM_SEEKING_SeekToKeyFrame;

		HRESULT hr = pims->SetPositions(pCurrent, flags, pStop, flags);

		if (SUCCEEDED(hr))
			return true;
	}

	return false;
}

class CLibMP3DLL
{
public:
	CLibMP3DLL(void);
	~CLibMP3DLL(void);

	bool LoadDLL(LPCWSTR dll);
	void UnloadDLL();

	bool Load(LPCWSTR filename);
	bool Cleanup();

	bool Play();
	bool Pause();
	bool Stop();
	bool WaitForCompletion(long msTimeout, long* EvCode);

	bool SetVolume(long vol);
	long GetVolume();

	__int64 GetDuration();
	__int64 GetCurrentPosition();

	bool SetPositions(__int64* pCurrent, __int64* pStop, bool bAbsolutePositioning);


private:
	HMODULE m_Mod;
};




//객체 생성 
Hero hero;
Enemy enemy[ENEMY_NUM];
Bullet bullet[BULLET_NUM];

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
		WS_EX_TOPMOST | WS_POPUP, 1000, 300, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;

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
	switch (message)
	{
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
		L"Panel3.png",    // the file name
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
		&sprite);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"hero.png",    // the file name
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
		&sprite_hero);    // load to sprite

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

	return;
}


void init_game(void)
{
	//객체 초기화 
	hero.init(150, 300);

	//적들 초기화 
	for (int i = 0; i<ENEMY_NUM; i++)
	{
		enemy[i].init((float)(rand() % 300), rand() % 200 - 300);
	}

	//총알 초기화 
	for (int i = 0; i<BULLET_NUM; i++)
	{
		bullet[i].init(hero.x_pos, hero.y_pos);
	}

}


void do_game_logic(void)
{

	//주인공 처리 
	if (KEY_DOWN(VK_UP))
		hero.move(MOVE_UP);

	if (KEY_DOWN(VK_DOWN))
		hero.move(MOVE_DOWN);

	if (KEY_DOWN(VK_LEFT))
		hero.move(MOVE_LEFT);

	if (KEY_DOWN(VK_RIGHT))
		hero.move(MOVE_RIGHT);


	//적들 처리 
	for (int i = 0; i<ENEMY_NUM; i++)
	{
		if (enemy[i].y_pos > 500)
			enemy[i].init((float)(rand() % 300), rand() % 200 - 300);
		else
			enemy[i].move();
	}


	//총알 처리
	for (int i = 0; i<ENEMY_NUM; i++)
	{
		if (bullet[i].show() == false)
		{
			if (KEY_DOWN(VK_SPACE))
			{
				bullet[i].active();
				bullet[i].init(hero.x_pos, hero.y_pos);
			}
		}
		if (bullet[i].show() == true)
		{
			if (bullet[i].y_pos < -70) bullet[i].hide();
			else bullet[i].move();

			//충돌 처리 
			for (int i = 0; i < BULLET_NUM; i++)
			{
				if (bullet[i].check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
				{
					for (int i = 0; i < ENEMY_NUM; i++)
					{
						enemy[i].init((float)(rand() % 300), rand() % 200 - 300);
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
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(116, 167, 243), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

											 //UI 창 렌더링 


											 /*
											 static int frame = 21;    // start the program on the final frame
											 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
											 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

											 // calculate the x-position
											 int xpos = frame * 182 + 1;

											 RECT part;
											 SetRect(&part, xpos, 0, xpos + 181, 128);
											 D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
											 D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
											 d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
											 */

											 //주인공 
	RECT part;
	SetRect(&part, 0, 0, 64, 64);
	D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
	D3DXVECTOR3 position(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
	d3dspt->Draw(sprite_hero, &part, &center, &position, D3DCOLOR_ARGB(255, 255, 255, 255));

	////총알 
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].bShow == true)
		{
			RECT part1;
			SetRect(&part1, 0, 0, 64, 64);
			D3DXVECTOR3 center1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position1(bullet[i].x_pos, bullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_bullet, &part1, &center1, &position1, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	


	////에네미 
	RECT part2;
	SetRect(&part2, 0, 0, 64, 64);
	D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner

	for (int i = 0; i<ENEMY_NUM; i++)
	{
		D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_enemy, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
	}



	d3dspt->End();    // end sprite drawing

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);

	return;
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	sprite->Release();
	d3ddev->Release();
	d3d->Release();

	//객체 해제 
	sprite_hero->Release();
	sprite_enemy->Release();
	sprite_bullet->Release();

	return;
}
