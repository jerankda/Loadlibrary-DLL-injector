#include "injector.h"

#include <iostream>
#include <string>

int main()
{
    std::string dllPath;
    DWORD processId;

    // Ask the user for the path to the DLL to inject
    std::cout << "Enter the path to the DLL to inject: ";
    std::cin >> dllPath;

    // Ask the user for the process ID of the target process
    std::cout << "Enter the process ID of the target process: ";
    std::cin >> processId;

    // Inject the DLL
    injectDll(dllPath, processId);

    return 0;
}
