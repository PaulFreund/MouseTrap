//######################################################################################################################
/*
	Copyright (c) since 2014 - Paul Freund

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
//######################################################################################################################

#include <ntddk.h>
#include <wdf.h>

#include <kbdmou.h>
#include <ntddmou.h>

//======================================================================================================================

#if DBG
	#define TRAP() DbgBreakPoint()
	#define DebugPrint(_x_) DbgPrint _x_
#else   // DBG
	#define TRAP()
	#define DebugPrint(_x_)
#endif

//======================================================================================================================

DEFINE_GUID(GUID_DEVINTERFACE_MouseTrap, 0x5a455edd, 0x84e0, 0x4bcc, 0x9f, 0x92, 0x2a, 0xfc, 0x12, 0xb9, 0xbe, 0x06);

//======================================================================================================================

typedef struct _DEVICE_CONTEXT {
	CONNECT_DATA UpperConnectData;
} DEVICE_CONTEXT, *PDEVICE_CONTEXT;


WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)

//======================================================================================================================

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD MouseTrapEvtDeviceAdd;

EVT_WDF_IO_QUEUE_IO_INTERNAL_DEVICE_CONTROL MouseTrapEvtIoInternalDeviceControl;

void MouseTrapServiceCallback(DEVICE_OBJECT* deviceObject, MOUSE_INPUT_DATA* inputDataStart, MOUSE_INPUT_DATA* inputDataEnd, ULONG* inputDataConsumed);

//======================================================================================================================
