#include <windows.h>
#include <tchar.h>
#include <string>

typedef std::basic_string<TCHAR> tstring;

// Step 1: Get WdfPreDeviceInstallEx, WdfPostDeviceInstall, WdfPreDeviceRemove, WdfPostDeviceRemove from DLL

void* libraryLoad(const tstring& path) {
	if(path.empty()) { return nullptr; }
	return LoadLibrary(path.c_str());
}

void libraryUnload(void* handle) {
	if(handle == nullptr) { return; }
	FreeLibrary((HMODULE)handle);
}

void* libraryGetSymbol(void* handle, const tstring& name) {
	return (void*)GetProcAddress((HMODULE)handle, name.c_str());
}

bool libraryHasSymbol(void* handle, const tstring& name) {
	return (libraryGetSymbol(handle, name) != nullptr);
}

int __cdecl _tmain(int /*argc*/, _TCHAR* /*argv[]*/) {

	return 0;
}
