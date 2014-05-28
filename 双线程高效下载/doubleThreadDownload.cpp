//---------------------API------------------------------
// 这里的代码只是示意代码，无法跑通

//downloads a block from Internet sequentially in each call
//return true, if the entire file is downloaded, otherwise false.
bool GetBlockFromNet(Block* out_block);

//writes a block to hard disk
bool WriteBlockToDisk(Block* in_block);

class Thread
{
public:
	Thread(void (*work_func)());
	~Thread();
	void Start();
	void Abort();
};

class Semaphore
{
public:
	Semaphore(int count,int max_count);
	~Semaphore();
	void Unsignal();
	void Signal();
};

class Mutex
{
public:
	WaitMutex();
	ReleaseMutex();
};
//----------------------------------------------------



//1.确定使用信号量，而非互斥量，保证并行操作
//2.当缓冲区并不满并且下载没结束时，下载线程运行
//3.当缓冲区并不空并且下载没结束时，存储线程运行


#define MAX_COUNT 1000
//缓冲区数组，模拟循环队列
Block g_Buffer[MAX_COUNT];
Thread g_Download(ProcA);
Thread g_Write(ProcB);

//一开始缓冲区空间为MAX_COUNT，整个缓冲区可供下载的数据填充
Semaphore ForDownload(MAX_COUNT,MAX_COUNT);
//一开始缓冲区无数据可供存储
Semaphore ForWrite(0,MAX_COUNT);

//下载任务是否完成
bool isDone;
//下载的数据从缓冲区的哪个地方开始填充
int in_index;
//存储的数据从缓冲区的哪个地方开始提取
int out_index;

void ProcA()
{
	while(true)
	{
		//首先取得一个空闲空间，以便下载数据填充
		ForDownload.Unsignal();
		//填充
		isDone=GetBlockFromNet(g_Buffer+in_index);
		//更新索引
		in_index=(in_index+1)%MAX_COUNT;
		//提示存储线程可以工作
		ForWrite.Signal();

		//当任务全部下载完成，进程就可以结束了
		if(isDone)
			break;
	}
}

void ProcB()
{
	while(true)
	{
		//查询时候有数据可供存储
		ForWrite.Unsignal();
		//存储
		WriteBlockToDisk(g_Buffer+out_index);
		//更新索引
		out_index=(out_index+1)%MAX_COUNT;
		//将空闲空间还给缓冲区
		ForDownload.Signal();

		//当任务全部下载完成，并且所有的数据都存储到硬盘中，进程才可以结束
		if(isDone&&in_index==out_index)
			break;
	}
}

int main()
{
	isDone=false;
	in_index=0;
	out_index=0;
	g_Download.Start();
	g_Write.Start();
}