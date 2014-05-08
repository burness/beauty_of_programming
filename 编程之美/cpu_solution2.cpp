#include <Windows.h>

int main(){
const DWORD busyTime=10;
const DWORD idleTime=busyTime;

INT64 startTime=0;
while (true)
{
	DWORD startTime=GetTickCount();
	while((GetTickCount()-startTime)<=busyTime)
		;
	Sleep(idleTime);
}
return 0;
}