#include "injector.h"

#include <iostream>

// Prints an error message and the last error message from GetLastError
void printError(const std::string& message)
{
    std::cerr << message << ": " << GetLastError() << std::endl;
}

// Injects the DLL at the specified path into the process with the given process ID
void injectDll(const std::string& dllPath, DWORD processId)
{
    // Get a handle to the target process
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (processHandle == NULL)
    {
        printError("Failed to get handle to target process");
        return;
    }

    // Allocate memory for the DLL path in the target process
    LPVOID memoryAddress = VirtualAllocEx(processHandle, NULL, dllPath.size() + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (memoryAddress == NULL)
    {
        printError("Failed to allocate memory in target process");
        return;
    }

    // Write the DLL path to the allocated memory in the target process
    if (!WriteProcessMemory(processHandle, memoryAddress, dllPath.c_str(), dllPath.size() + 1, NULL))
    {
        printError("Failed to write to memory in target process");
        return;
    }

    // Get the address of the LoadLibraryA function from the target process's import table
    LPTHREAD_START_ROUTINE loadLibraryAddress = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if (loadLibraryAddress == NULL)
    {
        printError("Failed to get address of LoadLibraryA function");
        return;
    }

    // Create a new thread in the target process that starts at the LoadLibraryA function
    HANDLE threadHandle = CreateRemoteThread(processHandle, NULL, 0, loadLibraryAddress, memoryAddress, 0, NULL);
    if (threadHandle == NULL)
    {
        printError("Failed to create remote thread in target process");
        return;
    }

    // Wait for the remote thread to finish
    WaitForSingleObject(threadHandle, INFINITE);

    // Get the exit code of the thread
    DWORD threadExitCode;
    if (!GetExitCodeThread(threadHandle, &threadExitCode))
    {
        printError("Failed to get exit code of remote thread");
        return;
    }

    // Check if the DLL was successfully loaded
    if (threadExitCode == 0)
    {
        std::cerr << "Failed to load DLL in target process" << std::endl;
        return;
    }

    // Free the memory allocated in the target process
    VirtualFreeEx(processHandle, memoryAddress, dllPath.size() + 1, MEM_RELEASE);

    // Close the handles
    CloseHandle(threadHandle);
    CloseHandle(processHandle);
}
