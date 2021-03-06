#include<windows.h>
#include<stdio.h>
//#define WINVER 0x0500
void SetMousePosition(POINT & mp);
void LeftClick();
POINT GetMousePosition();
int main(int argc, char** argv)
{
    FARPROC pGetPixel;
	int x[4]={45,164 ,290 ,385},i=0,f;
	POINT pt;
	pt.y=500;
    HINSTANCE _hGDI = LoadLibrary("gdi32.dll");
    if(_hGDI)
    {
        pGetPixel = GetProcAddress(_hGDI, "GetPixel");
        HDC _hdc = GetDC(NULL);
    if(_hdc)
    {
        
        while(1){
		COLORREF _color = (*pGetPixel) (_hdc, x[i],500);
	
     
		if(_color<1000)
		{
		   
			switch(i)
			{
				case 0:	
					pt.x=x[i];
					SetMousePosition();
					break;
				case 1:	
					pt.x=x[i];
					SetMousePosition();
					break;
				case 2:	
					pt.x=x[i];
					SetMousePosition();
					break;
				case 3:	
					pt.x=x[i];
					SetMousePosition();
					break;
				
			}
			LeftClick();
					
  		}
		if(i<3)
		i++;
		else
		i=0;
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
void SetMousePosition(POINT& mp)
{
	long fScreenWidth	    = GetSystemMetrics( SM_CXSCREEN ) - 1; 
	long fScreenHeight	    = GetSystemMetrics( SM_CYSCREEN ) - 1; 

	// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx		        = mp.x * ( 65535.0f / fScreenWidth  );
	float fy		        = mp.y * ( 65535.0f / fScreenHeight );		  
				
	INPUT Input             = { 0 };			
	Input.type		        = INPUT_MOUSE;

	Input.mi.dwFlags	    = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
				
	Input.mi.dx		        = (long)fx;
	Input.mi.dy		        = (long)fy;

	SendInput(1,&Input,sizeof(INPUT));
}
