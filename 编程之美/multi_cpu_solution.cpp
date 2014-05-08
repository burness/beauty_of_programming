#include <Windows.h>
#include <stdlib.h>
#include <tchar.h>
int main(int argc, char* argv[]){
	int busyTime=10;
	int idleTime=busyTime*50;
	__int64 startTime=0;
	::SetThreadAffinityMask(::GetCurrentProcess(),0x00000001);//表示当前进程在第一个cpu上运行
	while(true){
		startTime=GetTickCount();
		while((GetTickCount()-startTime)<=busyTime);
		Sleep(idleTime);
	}
	return 0;
}