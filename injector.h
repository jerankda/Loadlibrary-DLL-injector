#ifndef INJECTOR_H
#define INJECTOR_H

#include <string>
#include <Windows.h>

// Injects the DLL at the specified path into the process with the given process ID
void injectDll(const std::string& dllPath, DWORD processId);

#endif
