#pragma once
#include <iostream>
#include <Windows.h>
#include <process.h>

using namespace std;
BOOL FLAG = NULL;	// �����˳���־

// �̳߳� ����������̣߳�
typedef class _ThreadPool {

private:
	// �߳����ݽṹ(�����߳���Ϣ)
	typedef struct _ThreadData {
		HANDLE ThreadHandle = NULL;	//�߳̾��
	}ThreadData;

	DWORD THREAD_NUM_MAXIMUM; // �̳߳�����߳���
	ThreadData *THREAD_DATA;	// �̳߳� �߳�����

public:

	// ���� �̳߳� �߳�
	DWORD StartThreadPool();

	// ���� �̳߳� �߳�
	DWORD SuspendThreadPool();

	// ��ʼ���̳߳�����
	DWORD InitThreadPool(
		DWORD iThreadMaxCount,
		_beginthreadex_proc_type ThreadFunction);

	// ��������
	~_ThreadPool() {
		//���ó����˳���־
		FLAG = TRUE;
		std::cout << "[*] ��ѡ�����˳��� ��ȴ��߳�����" << endl;
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

	// �� �߳����ݽṹ �����ڴ�
	THREAD_DATA = new ThreadData [THREAD_NUM_MAXIMUM];

	for (int i = 0; i < THREAD_NUM_MAXIMUM; i++){
		THREAD_DATA[i].ThreadHandle = (HANDLE)_beginthreadex(NULL, NULL, ThreadFunction, NULL, CREATE_SUSPENDED, NULL);
	}
	return 0;
}