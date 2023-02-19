/**/
#include<windows.h>

#ifndef CAP_win_h
#define CAP_win_h
void CAP_pause_spin(DWORD);

#endif

#ifdef CAP_win
//function
void CAP_pause_spin(DWORD millisecond)
{
	DWORD start=GetTickCount();
	while(GetTickCount()-start< millisecond){}
}

#endif
