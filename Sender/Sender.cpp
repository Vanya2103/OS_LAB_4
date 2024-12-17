#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    if (argc < 3) {
        cout << "������������ ����������. ���������: ��� ����� � ������ ��������." << endl;
        return 1;
    }

    string filename = argv[1];
    int senderIndex = stoi(argv[2]);

    ofstream out(filename, ios::binary | ios::app);
    out.close();

    HANDLE hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"SyncMutex");
    HANDLE hFullSemaphore = OpenSemaphoreW(SEMAPHORE_ALL_ACCESS, FALSE, L"FullSemaphore");
    HANDLE hEmptySemaphore = OpenSemaphoreW(SEMAPHORE_ALL_ACCESS, FALSE, L"EmptySemaphore");

    if (!hMutex) {
        cout << "������ �������� ���������������� ��������" << endl;
        return GetLastError();
    }

    wstring eventName = L"SenderReady_" + to_wstring(senderIndex);
    HANDLE readyEvent = OpenEventW(EVENT_ALL_ACCESS, FALSE, eventName.c_str());

    if (!readyEvent) {
        cout << "������ �������� ������� ����������: " << GetLastError() << endl;
        return GetLastError();
    }

    SetEvent(readyEvent);
    CloseHandle(readyEvent);
    cout << "Sender �����." << endl;

    ReleaseMutex(hMutex);

    string comand, mess;
    while (true) {
        cout << "�������� �������� exit ��� sent: " << endl;
        cin >> comand;

        if (comand == "sent") {
            WaitForSingleObject(hEmptySemaphore, INFINITE);
            WaitForSingleObject(hMutex, INFINITE);

            cout << "������� ���������: " << endl;
            cin >> mess;

            out.open(filename, ios::binary | ios::app);
            string paddedMessage = mess + string(20 - mess.size(), '\0');
            out.write(paddedMessage.c_str(), 20);
            out.close();

            ReleaseMutex(hMutex);
            ReleaseSemaphore(hFullSemaphore, 1, NULL);
        }
        else if (comand == "exit") {
            break;
        }
        else {
            cout << "������������ ��� ��������" << endl;
        }
    }

    CloseHandle(hMutex);
    CloseHandle(hFullSemaphore);
    CloseHandle(hEmptySemaphore);

    return 0;
}
