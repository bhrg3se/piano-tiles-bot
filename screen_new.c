#include<windows.h>
#include<stdio.h>
#include<time.h>
const int max_r=5;
const int max_g=100;
const int max_b=100;
const int max_t=60;
//#define WINVER 0x0500
void SetMousePosition(POINT * mp);
void LeftClick();
POINT GetMousePosition();
int main(int argc, char** argv)
{
    FARPROC pGetPixel;
	POINT pt1,pt2,pt3,pt4;
	COLORREF _color1,_color2,_color3,_color4; 
	int _red1 ,_green1 ,_blue1,_red2,_green2,_blue2,_red3,_green3,_blue3,_red4 ,_green4 ,_blue4;
     clock_t t1,t2,t3,t4;
	pt1.y=300;
	pt1.x=15;
	pt2.y=300;
	pt2.x=130;
	pt3.y=300;
	pt3.x=230;
	pt4.y=300;
	pt4.x=345;
	t1=101;
	t2-101;t3=101;t4=101;
	
	
	HINSTANCE _hGDI = LoadLibrary("gdi32.dll");
    if(_hGDI)
    {
        pGetPixel = GetProcAddress(_hGDI, "GetPixel");
        HDC _hdc = GetDC(NULL);
    if(_hdc)
    {
        
        while(1){
        if(clock()-t1>max_t)
		{
	
		_color1 = (*pGetPixel) (_hdc,45,300);
		_red1 = GetRValue(_color1);
        _green1 = GetGValue(_color1);
        _blue1 = GetBValue(_color1);
        
       if(_red1<max_r&&_green1<max_g&&_blue1<max_b)
				
		{
		
					SetMousePosition(&pt1);
					LeftClick();
				
					t1=clock();
						
		}
    }
    if(clock()-t2>max_t)
    {
	
        _color2 = (*pGetPixel) (_hdc, 164,300);
		_red2 = GetRValue(_color2);
        _green2 = GetGValue(_color2);
        _blue2 = GetBValue(_color2);
        
        
        if(_red2<max_r&&_green2<max_g&&_blue2<max_b)
				
		{
					SetMousePosition(&pt2);
					LeftClick();
				
					t2=clock();
						
		}
}if(clock()-t3>max_t)
{

		_color3 = (*pGetPixel) (_hdc, 290,300);
		_red3 = GetRValue(_color3);
        _green3 = GetGValue(_color3);
        _blue3 = GetBValue(_color3);
        
        
        if(_red3<max_r&&_green3<max_g&&_blue3<max_b)
				
		{
					SetMousePosition(&pt3);
					LeftClick();
				
					t3=clock();
						
		}
}if(clock()-t4>max_t)
{

		_color4 = (*pGetPixel) (_hdc, 385,300);
		_red4 = GetRValue(_color4);
        _green4 = GetGValue(_color4);
        _blue4 = GetBValue(_color4);
        
		
		
		
        if(_red4<max_r&&_green4<max_g&&_blue4<max_b)
				
		{
					SetMousePosition(&pt4);
					LeftClick();
				
					t4=clock();
						
		}
}
		}
		
    }
 	FreeLibrary(_hGDI);

    return 0;
}}




//
// Desc    : Clicks the left mouse button down and releases it.
// Returns : Nothing.
//
void LeftClick()
{  
	INPUT    Input={0};													// Create our input.

	Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
	SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.
//	sleep(1);
	ZeroMemory(&Input,sizeof(INPUT));									// Fills a block of memory with zeros.
	Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
	SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.
}

//
// Desc    : Gets the cursors current position on the screen.
// Returns : The mouses current on screen position.
// Info    : Used a static POINT, as sometimes it would return trash values
//
POINT GetMousePosition()
{
	static POINT m;
	POINT mouse;
	GetCursorPos(&mouse);
	m.x = mouse.x;
	m.y = mouse.y;
	return m;
}

//
// Desc    : Sets the cursors position to the point you enter (POINT& mp).
// Returns : Nothing.
//
void SetMousePosition(POINT * mp)
{
	long fScreenWidth	    = GetSystemMetrics( SM_CXSCREEN ) - 1; 
	long fScreenHeight	    = GetSystemMetrics( SM_CYSCREEN ) - 1; 

	// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx		        = mp->x * ( 65535.0f / fScreenWidth  );
	float fy		        = mp->y * ( 65535.0f / fScreenHeight );		  
				
	INPUT Input             = { 0 };			
	Input.type		        = INPUT_MOUSE;

	Input.mi.dwFlags	    = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
				
	Input.mi.dx		        = (long)fx;
	Input.mi.dy		        = (long)fy;

	SendInput(1,&Input,sizeof(INPUT));
}
