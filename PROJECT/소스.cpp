#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <TlHelp32.h>
#include <atlstr.h>
// #include <hash_map>
#include <string>
using namespace stdext;

// 실행중인 모든 프로세스 찾기
HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
PROCESSENTRY32 processEntry32;

void Check() {
    // 무효한 핸들 값일시 종료
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        exit(EXIT_FAILURE);
    }

    processEntry32.dwSize = sizeof(PROCESSENTRY32);

    // 첫번째 프로세스 정보 검색 실패시 종료
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
        // 실행중인 프로세스 비교
        if (name.Compare(processEntry32.szExeFile) == 0)
        {
            std::cout << processEntry32.th32ProcessID << std::endl;
            return TRUE;
        }
    }
    // 실행중인 프로세스 중에 찾는 프로세스가 없다면
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

// 중복 제거, 백그라운드 제외, 리스트 출력

int main() {
    ProcessList();
    char buf[100];
    std::cin >> buf;
    std::cout << getStateProcess(buf);
}