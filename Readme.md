# MouseTrap

Windows Kernel mode class filter driver (KMDF) built with the WDF framework.

* Inverts scroll wheel for every mouse
* Comes with a Driver Installer application
* MouseTrapInstaller.exe has to be in the same path as the packaged files
* Install as admin with "MouseTrapInstaller.exe" install and a reboot
* Remove as admin with "MouseTrapInstaller.exe remove" and a reboot
* Implementation of installer/installation not polished
* Tested with windows 7 

# Installation 

On Windows 7 x64 test signatures have to be allowd in the bootloader:

	bcdedit /set TESTSIGNING ON

Then open a ADMIN shell and go to the path where "MouseTrapInstaller.exe", "MouseTrap.sys", "MouseTrap.inf" and "WdfCoInstaller01011.dll" are located and

## Install

	MouseTrapInstaller.exe
	
## Remove

	MouseTrapInstaller.exe remove
