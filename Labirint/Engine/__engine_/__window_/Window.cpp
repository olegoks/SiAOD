

#include "window.h"

//
#include <chrono>
//
#pragma warning(disable : 4996)

namespace wnd {
		
		void Window::PushKeystroke(KeyType key) {

			using namespace std::chrono;
			high_resolution_clock::time_point now_time_point = high_resolution_clock::now();
			unsigned int now = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
			const Keystroke keystroke = { key, now };
			This->keys_.push_back(keystroke);

		}

		LRESULT CALLBACK Window:: WndProc(HWND hWnd, UINT Message, WPARAM  wParam, LPARAM lParam) {

		switch (Message) {

			case WM_KEYDOWN: {

				const unsigned int key = wParam;

				switch (key) {

				case VK_UP: { PushKeystroke(ArrowUp);break;}
				case VK_DOWN: { PushKeystroke(ArrowDown);break;}
				case VK_LEFT: { PushKeystroke(ArrowLeft);break;};
				case VK_RIGHT: { PushKeystroke(ArrowRight);break;}
				case VK_A: { PushKeystroke(A); break; };
				case VK_D: { PushKeystroke(D); break; };
				case VK_S: { PushKeystroke(S); break; };
				case VK_W: { PushKeystroke(W); break; };

				}
				
			break;
			
			}

			case WM_MOUSEWHEEL: {

				static int wheel_delta = 0;
				wheel_delta += GET_WHEEL_DELTA_WPARAM(wParam);
				
				while (wheel_delta > WHEEL_DELTA) {
					PushKeystroke(WheelUp);
					wheel_delta -= WHEEL_DELTA;
				}
				
				while (wheel_delta < 0) {
					PushKeystroke(WheelDown);
					wheel_delta += WHEEL_DELTA;
				}

				break;
			}

			case WM_CLOSE: {DestroyWindow(This->Handle);break;}

			case WM_DESTROY: {PostQuitMessage(0);break;}
		
			default: return DefWindowProc(hWnd, Message, wParam, lParam); 
		
		}

		}

		Window::Window(HINSTANCE appIntanceHandle) {

			this->This = this;
			this->AppIntanceHandle = appIntanceHandle;
			this->win_coordinats_.x = 0;
			this->win_coordinats_.y = 0;
			this->size_.height = 100;
			this->size_.width = 100;
			this->DeviceContext = nullptr;
			this->win_caption = nullptr;
			this->Handle = nullptr;
			this->first_time_point_count_fps_ = std::chrono::high_resolution_clock::now();

		}
		
		Window::~Window() {
			

		}

		void Window::SetMode(int mode){

		}
		void Window::SetCoordinats(unsigned int x, unsigned int y)
		{

			this->win_coordinats_.x = x;
			this->win_coordinats_.y = y;

		}

		void Window::SetSize(unsigned int width, unsigned int height)
		{

			this->size_.height = height;
			this->size_.width = width;

		}

		bool Window::RegisterWindowClass() {

			TCHAR szClassName[] = L"Main window class"; // ������ � ������ ������
			WNDCLASSEX wc; //������� ��������� ������ WNDCLASSEX
			wc.cbSize = sizeof(wc);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = this->WndProc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = this->AppIntanceHandle;
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			wc.lpszMenuName = NULL;
			wc.lpszClassName = szClassName;
			wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

			if (!RegisterClassEx(&wc)) {

				MessageBox(nullptr,
					L"�� ������� ���������������� �����",
					L"������ ����������� ������!",
					MB_OK);

				return EXIT_FAILURE;

			}

			return EXIT_SUCCESS;

		}

		int  Window::Create()
		{
			
			TCHAR szClassName[] = L"Main window class";

			HWND HMainWnd;

			/*HMainWnd = CreateWindowEx(WS_EX_TOPMOST, szClassName, L"3D Application", WS_OVERLAPPEDWINDOW,
				0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), (HWND)NULL,
				(HMENU)NULL, (HINSTANCE)this->AppIntanceHandle, NULL);*/
			HMainWnd = CreateWindow(szClassName,
				this->win_caption, //L"3D Application", // ��� ���� (�� ��� ������)
				WS_POPUP,/*WS_MAXIMIZE | WS_BORDER | WS_VISIBLE*/  // ������ ����������� ������
				this->win_coordinats_.x, // ��������� ���� �� ��� � (�� ���������)
				this->win_coordinats_.y, // ������� ���� �� ��� � (��� ������ � �, �� ������ �� �����)
				this->size_.width, // ������ ������ (�� ���������)
				this->size_.height, // ������ ���� (��� ������ � ������, �� ������ �� �����)
				HWND(NULL), // ���������� ������������� ������
				NULL, // ���������� ���� 
				this->AppIntanceHandle, // l���������� ���������� ����������
				NULL); // ������ �� ������� �� WndProc
			
			if (!HMainWnd) {
				// � ������ ������������� �������� ���� (�������� ��������� � ��):
				MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
				return EXIT_FAILURE; // ������� �� ����������
			}
			
			this->Handle = HMainWnd;
			SetProcessDPIAware();//������� ��� ������� (SetProcessDPIAware), �� ��������� �������, ��� ��������� ������ ���������� ����� ��� ��������� ���������������� ��� ������� ��������� DPI (����� �� ����). ���� �� �� ��������� ���� ����, �� ��������� ������ ���������� ����� ��������� ������� ��� ������� ��������� DPI.
			DeviceContext =GetDC(HMainWnd);//CreateDC(L"DISPLAY", NULL, NULL, NULL);
			//��������� ���������� ��������� ����������
			this->DeviceContext = DeviceContext;

			return EXIT_SUCCESS;
		}

		bool Window::Show()
		{
			return ShowWindow(this->Handle, SW_MAXIMIZE);
		}

		int Window::StartMessageLoop()
		{
			
			/*
			typedef struct tagMSG {
				HWND hwnd; // ���������� ����, �������� ���������� ���������
				UINT message; // ����� (������������� ) ���������
				WPARAM wParam; // �������� ��������� wParam
				LPARAM lParam; //�������� ��������� lParam
				DWORD time; // ����� �������� ���������
				POINT pt; //������� �������(� �������� �����������) � ������
				//�������� ���������
			} MSG;
			*/
			MSG msg; // ����� ��������� ��������� MSG ��� ��������� ���������

			msg = { 0 }; // ������������� ��������� ��������� 

			while (GetMessage(&msg, NULL, NULL, NULL) != 0) {
					
					TranslateMessage(&msg);
					DispatchMessage(&msg);

				}

			// BOOL GetMessage(
			// MSG lpMsg, - ����� ��������� ���� ��������� ���������
			// HWND hWnd, - �������� ����� ��������� ����� NULL, 
			// UINT wMsgFilterMin, - ���������� ������������� �������� ������ ���������� �������� ���������, ������� ����� ���������.
			// UINT wMsgFilterMax - ���������� ������������� �������� ������ �������� �������� ���������, ������� ����� ���������.
			// *���� wMsgFilterMin � wMsgFilterMax �������� ��� ��������, ������� GetMessage ���������� ��� ��������� ��������� (�� ���� ������� ���������� � ��������� �������� �� �����������).
			
			//������� TranslateMessage ��������� ��������� ����������� ������ � ���������� ���������. 
			//���������� ��������� ���������� � ������� ��������� ����������� ������ ��� ��������� � ��������� ���, 
			//����� ����� ������� ������� GetMessage ��� PeekMessage.

			//������� DispatchMessage ������������ ��������� ������� ��������� WndProc.
			return msg.wParam;

		}

		void Window::DisplayFrame() {
			
			//using namespace std::chrono;
			//typedef high_resolution_clock::time_point time_point;
			//typedef high_resolution_clock::duration duration;

			//time_point second_time_point_count_fps = high_resolution_clock::now();

			//duration render_frame_duration = second_time_point_count_fps - first_time_point_count_fps_;
			//int current_fps = 0;
			//current_fps = 1000.0f / (float)duration_cast<milliseconds>(render_frame_duration).count();

			//if (current_fps > 100) { current_fps = 99; }
			//	else
			//		if (current_fps < 0) { current_fps = 0; };
			////fps = 30;
			//char fps_char[3] = { "00" };
			//_itoa(current_fps, fps_char, 10);
			//wchar_t* string = ConvertString(fps_char);

			SetDIBitsToDevice(
					DeviceContext,//HDC hdc
					0,//int XDest,
					0,//int YDest,+
					size_.width ,//DWORD dwWidth, 
					size_.height ,//DWORD dwHeight,+
					0,//int XSrc,
					0,//int YSrc,
					0,// UINT uStartScan
					size_.height,//UINT cScanLines
					this->display_buffer_,
					&this->display_buffer_info_,
				DIB_PAL_COLORS//DIB_RGB_COLORS/*,
					//SRCCOPY
			);
			/*TextOut(DeviceContext, 5, 5, string, 2);

			first_time_point_count_fps_ = high_resolution_clock::now();*/

				

				//int SetDIBitsToDevice(
				//	HDC hdc,                 // ���������� DC
				//	int XDest,               // x-�����. �������� ������ ���� ���������
				//	int YDest,               // y-�����. �������� ������ ���� ���������
				//	DWORD dwWidth,           // ������ �������������� ���������
				//	DWORD dwHeight,          // ������ �������������� ���������
				//	int XSrc,                // x-�����. ������� ������ ���� ���������
				//	int YSrc,                // y-�����. ������� ������ ���� ���������
				//	UINT uStartScan,         // ������ ������ ��������� � �������
				//	UINT cScanLines,         // ����� ����� ���������
				//	CONST VOID * lpvBits,     // ������ ����� DIB
				//	CONST BITMAPINFO * lpbmi, // ���������� � �������� �������
				//	UINT fuColorUse          // RGB ��� ������� �������
				//);
			

		}

		Size Window::GetSize()
		{
			return this->size_;
		}

		HDC Window::GetDeviceContext()
		{
			return this->DeviceContext;
		}

		HWND Window::GetHandle()
		{
			return this->Handle;
		}

		win_coordinats Window::GetCoord()
		{
			return this->win_coordinats_;
		}

		void Window::SetDisplayBuffer(RgbPixel* display_buffer, const unsigned int display_buffer_size){
		
			this->display_buffer_ = display_buffer;

			ZeroMemory(&this->display_buffer_info_.bmiHeader, sizeof(BITMAPINFO));

			this->display_buffer_info_.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			this->display_buffer_info_.bmiHeader.biWidth = this->size_.width;
			this->display_buffer_info_.bmiHeader.biHeight = -((int) (this->size_.height));
			this->display_buffer_info_.bmiHeader.biPlanes = 1;
			this->display_buffer_info_.bmiHeader.biBitCount = 32;//this->kBitsPerPixel;
			this->display_buffer_info_.bmiHeader.biCompression = BI_RGB;
			this->display_buffer_info_.bmiHeader.biSizeImage = ((1920 * 24 + 31) & ~31) / 8 * 1080;//display_buffer_size;
			this->display_buffer_info_.bmiHeader.biXPelsPerMeter = 0;
			this->display_buffer_info_.bmiHeader.biYPelsPerMeter = 0;
			this->display_buffer_info_.bmiHeader.biClrUsed = 0;
			this->display_buffer_info_.bmiHeader.biClrImportant = 0;
			
		}

		Window* Window::This = nullptr;



		

}