#define _CRT_SECURE_NO_WARNINGS
#include "Main.h"

DWORD THREAD_MAX = NULL;
DWORD TIME_SLEEP = NULL;

// ��������¼�
UINT CALLBACK MouseEvent(LPVOID) {
	// ģ�����
	while (1) {
		if (FLAG == TRUE)
			break;
		mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
		mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
		if(TIME_SLEEP != 0)
			Sleep(TIME_SLEEP);
	}
	return 0;
}

int main() {
/*-------------------------------------------------------------------------------*/

	R:
	// �༭������
	system("color 04");
	std::cout << "\t\t|------------------------------------------|" << endl;
	std::cout << "\t\t|                ���������                |" << endl;
	std::cout << "\t\t|                BY 4566Z1                 |" << endl;
	std::cout << "\t\t|                Version 3.0               |" << endl;
	std::cout << "\t\t|------------------------------------------|" << endl;
	std::cout << "[!] ע������ �������ʶ�����Ч��� ���Ҳ���ǰٴ�����ÿ��" << endl;
	std::cout << "[!] �����ϸó�����Դﵽ�����ÿ��, ���Ǽ�����޷�ʶ��" << endl;
	std::cout << "[*] ����ӳ�Ϊ0 ��������ģʽ(����)" << endl;
	std::cout << "[*] �����������ӳ�: ";
	scanf("%d", &TIME_SLEEP);	// �ȴ��û�����
	std::cout << "[*] �����߳���: ";
	scanf("%d", &THREAD_MAX);	// �ȴ��û�����
	rewind(stdin);	// ˢ�����뻺������ �������fflush���ڲ�������
	if (TIME_SLEEP < 0|| THREAD_MAX <= 0) {
		system("cls");
		std::cout << "[!] ���벻�Ϸ�." << endl;
		Sleep(2000);
		goto R;
	}

/*-------------------------------------------------------------------------------*/
	system("cls");
	// �����ڴ�
	ThreadPool *ThreadPool1 = new ThreadPool;

	// ��ʼ���̳߳�
	ThreadPool1->InitThreadPool(THREAD_MAX, MouseEvent);
	cout << "[*] ��ȴ��߳�ȫ���������.." << endl;
	Sleep(2000);

T:
	system("cls");
	cout << "[*]  TAB ��ʼ����   " << endl
		<< "[*] ����Ҽ�ȡ������ " << endl
		<< "[*]   ESC �˳�����   " << endl
		<< "[-] ��ǰ�߳�����: " << THREAD_MAX << endl;
	while (1) {
		if (GetKeyState(VK_ESCAPE) < 0) {
			delete ThreadPool1;	// ɾ�� ����� ������������
			goto EXIT;
		}
		if (GetKeyState(VK_TAB) < 0)
			break;
		Sleep(1);	// ��ֹռ�� CPU ʱ��Ƭ
	}

	ThreadPool1->StartThreadPool();	// �����߳�

	std::cout << "[*] �̹߳�����.." << endl;
	while (1) {
		if (GetKeyState(VK_ESCAPE) < 0) {
			delete ThreadPool1;	// ɾ�� ����� ������������
			goto EXIT;
		}
		if (GetKeyState(VK_RBUTTON) < 0)
			break;
		Sleep(1);   // ��ֹռ�� CPU ʱ��Ƭ
	}

	ThreadPool1->SuspendThreadPool();
	cout << "[*] ���ڹ����߳�.." << endl;
	Sleep(1000);
	goto T;
	EXIT:
	return 0;
}