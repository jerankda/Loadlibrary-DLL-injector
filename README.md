# Loadlibrary DLL Injector

**Description:**
Thi is a simple command-line tool designed for injecting dynamic link libraries (DLLs) into running processes on Windows systems. This can be useful for various purposes, including debugging, code injection, and modifying the behavior of applications.

**Disclaimer:**
Use this tool responsibly and ethically. Unauthorized use of DLL injection techniques may violate the terms of service of certain software or potentially lead to legal consequences. The author is not responsible for any misuse of this tool.

## Features:

- **DLL Injection:** Inject dynamic link libraries into running processes.
- **Process Selection:** Choose the target process by providing its process ID (PID).
- **User Interface:** Command-line interface for easy integration into scripts or manual usage.

## Usage:

```bash
Loadlibrary-DLL-injector.exe <PID> <DLL Path>
<PID>: The process ID of the target process.
<DLL Path>: The full path to the DLL that you want to inject.
```

## Example:

Loadlibrary-DLL-injector.exe 1234 C:\Path\To\Your\InjectedDLL.dll

## Note

This project was developed as part of an internship project and will not be updated further.
