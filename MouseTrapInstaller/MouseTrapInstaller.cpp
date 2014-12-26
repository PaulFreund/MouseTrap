#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>

typedef std::basic_string<TCHAR> tstring;

/*
	http://www.osronline.com/article.cfm?name=wdffltr_v10.zip&id=446
	http://www.techtalkz.com/microsoft-device-drivers/262160-wdf-class-filter-driver-installation.html
	http://msdn.microsoft.com/en-us/library/windows/hardware/ff537751(v=vs.85).aspx

	I do not need to create a device as this is a filter for all devices. I might have to modify the inf to reflect the changes, but "calling" the MouseTrap_Installer key should work.

	Summarized:
	- Call CoInstaller routines
	- Call inf installer
	- Add UpperFilter
*/

const tstring PathSeparator = _T("\\");
const TCHAR PathSeparatorChar = _T('\\');
const tstring LibrarySuffix = _T(".dll");

inline bool endsWith(const tstring& heystack, const tstring& needle) {
	if(heystack.length() < needle.length()) { return false; }
	return (heystack.substr(heystack.length() - needle.length(), needle.length()) == needle);
}

std::vector<tstring> fileDirectoryContents(const tstring& path) {

	if(path.empty()) { return {}; }
	tstring findPath = path;
	if(!endsWith(findPath, PathSeparator)) { findPath += PathSeparator; }
	findPath.append("*");

	WIN32_FIND_DATA findData;
	auto handle = FindFirstFile(findPath.c_str(), &findData);
	if(handle == INVALID_HANDLE_VALUE) { return {}; }

	std::vector<tstring> result;
	tstring current;
	do {
		current = tstring(findData.cFileName);
		if(!current.empty() && current != _T(".") && current != _T("..")) { result.push_back(path + PathSeparator + current); }
	}
	while(FindNextFile(handle, &findData) != 0);

	return std::move(result);
}

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
