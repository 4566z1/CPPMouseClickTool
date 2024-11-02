#pragma once
#include <iostream>
#include <Windows.h>
#include <process.h>

using namespace std;
BOOL FLAG = NULL;	// 程序退出标志

// 线程池 （方便管理线程）
typedef class _ThreadPool {

private:
	// 线程数据结构(保存线程信息)
	typedef struct _ThreadData {
		HANDLE ThreadHandle = NULL;	//线程句柄
	}ThreadData;

	DWORD THREAD_NUM_MAXIMUM; // 线程池最大线程数
	ThreadData *THREAD_DATA;	// 线程池 线程数据

public:

	// 启动 线程池 线程
	DWORD StartThreadPool();

	// 挂起 线程池 线程
	DWORD SuspendThreadPool();

	// 初始化线程池数据
	DWORD InitThreadPool(
		DWORD iThreadMaxCount,
		_beginthreadex_proc_type ThreadFunction);

	// 析构函数
	~_ThreadPool() {
		//设置程序退出标志
		FLAG = TRUE;
		std::cout << "[*] 你选择了退出， 请等待线程销毁" << endl;
		Sleep(2000);
	}

}ThreadPool;


DWORD _ThreadPool::SuspendThreadPool() {
	for (int i = 0; i < THREAD_NUM_MAXIMUM; i++){
		SuspendThread(THREAD_DATA[i].ThreadHandle);	
	}
	return 0;
}

DWORD _ThreadPool::StartThreadPool() {
	for (int i = 0; i < THREAD_NUM_MAXIMUM; i++)
	{
		ResumeThread(THREAD_DATA[i].ThreadHandle);
	}
	return 0;
}

DWORD _ThreadPool::InitThreadPool(
	DWORD iThreadMaxCount,
	_beginthreadex_proc_type ThreadFunction){

	THREAD_NUM_MAXIMUM = iThreadMaxCount;

	// 给 线程数据结构 分配内存
	THREAD_DATA = new ThreadData [THREAD_NUM_MAXIMUM];

	for (int i = 0; i < THREAD_NUM_MAXIMUM; i++){
		THREAD_DATA[i].ThreadHandle = (HANDLE)_beginthreadex(NULL, NULL, ThreadFunction, NULL, CREATE_SUSPENDED, NULL);
	}
	return 0;
}