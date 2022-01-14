#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <TlHelp32.h>
#include <atlstr.h>
// #include <hash_map>
#include <string>
using namespace stdext;

// �������� ��� ���μ��� ã��
HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
PROCESSENTRY32 processEntry32;

void Check() {
    // ��ȿ�� �ڵ� ���Ͻ� ����
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        exit(EXIT_FAILURE);
    }

    processEntry32.dwSize = sizeof(PROCESSENTRY32);

    // ù��° ���μ��� ���� �˻� ���н� ����
    if (!Process32First(hProcessSnap, &processEntry32))
    {
        CloseHandle(hProcessSnap);
        exit(EXIT_FAILURE);
    }
}

BOOL getStateProcess(CString name)
{
    Check();

    while (Process32Next(hProcessSnap, &processEntry32))
    {
        //std::cout << processEntry32.szExeFile << std::endl;
        // �������� ���μ��� ��
        if (name.Compare(processEntry32.szExeFile) == 0)
        {
            std::cout << processEntry32.th32ProcessID << std::endl;
            return TRUE;
        }
    }
    // �������� ���μ��� �߿� ã�� ���μ����� ���ٸ�
    return FALSE;
}
void ProcessList() {
    Check();
    // hash_map<std::string, int> list;

    while (Process32Next(hProcessSnap, &processEntry32)) {
        /*if (m.find(key) == m.end()) {

        }
        list.insert(hash_map<int, int>::value_type(processEntry32.th32ProcessID, processEntry32.th32ParentProcessID);*/
        std::cout << std::string(CT2CA(processEntry32.szExeFile)) << ": ";
        std::cout << processEntry32.th32ProcessID << " ";
        
        std::cout << processEntry32.th32ParentProcessID << std::endl;
        
    }

}

// �ߺ� ����, ��׶��� ����, ����Ʈ ���

int main() {
    ProcessList();
    char buf[100];
    std::cin >> buf;
    std::cout << getStateProcess(buf);
}