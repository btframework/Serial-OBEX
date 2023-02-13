////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   Wireless Communication Library 7                                         //
//                                                                            //
//   Copyright (C) 2006-2023 Mike Petrichenko                                 //
//                           Soft Service Company                             //
//                           All Rights Reserved                              //
//                                                                            //
//   http://www.btframework.com                                               //
//                                                                            //
//   support@btframework.com                                                  //
//   shop@btframework.com                                                     //
//                                                                            //
// -------------------------------------------------------------------------- //
//                                                                            //
//   WCL Serial Framework: Serial Devices support.                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "..\Common\wclHelpers.h"
#include "..\Common\wclMessaging.h"

#include "wclSerialErrors.h"

using namespace wclCommon;

namespace wclSerial
{

/// <summary> The record contains information about serial device. </summary>
typedef struct
{
	/// <summary> The serial device friendly name. </summary>
	tstring FriendlyName;
	/// <summary> <c>True</c> if the device is a modem. </summary>
	bool IsModem;
	/// <summary> The name (as 'COM1') of the serial device used by the
	///   device. </summary>
	tstring DeviceName;
} wclSerialDevice;
/// <summary> The array contains information about found serial
///   devices. </summary>
/// <seealso cref="wclSerialDevice" />
typedef std::list<wclSerialDevice>	wclSerialDevices;

#define wclSerialDeviceEvent(_event_name_) \
	__event void _event_name_(void* Sender, const wclSerialDevice& Device)

/// <summary> The Serial Monitor allows your application to enumerate
///   available serial devices and to monitor changes in its
///   configuration. </summary>
class CwclSerialMonitor
{
	DISABLE_COPY(CwclSerialMonitor);

private:
	RTL_CRITICAL_SECTION	FCS;
	CwclMessageReceiver*	FReceiver;
	
	int InternalEnumDevices(const GUID& DevGuid, 
		wclSerialDevices& Devices) const;
	int InternalEnumDevicesCfgMgr(wclSerialDevices& Devices) const;

protected:
	/// <summary> The method called when a new notification message
	///   received. </summary>
	/// <param name="Message"> A <see cref="CwclMessage" /> object
    ///   represents a notification message. </param>
    /// <remarks> <para> This method is for internal use only. </para>
    ///   <para> If a derived class overrides this method it must always call
    ///   the inherited implementation first. </para> </remarks>
    /// <seealso cref="CwclMessage" />
    virtual void MessageReceived(const CwclMessage* const Message);
	
	/// <summary> Fires the <c>OnInserted</c> event. </summary>
    /// <param name="Device"> The <see cref="wclSerialDevice" /> structure that
    ///   describes the serial device. </param>
    /// <seealso cref="wclSerialDevice" />
    virtual void DoInserted(const wclSerialDevice& Device);
    /// <summary> Fires the <c>OnRemoved</c> event. </summary>
    /// <param name="Device"> The <see cref="wclSerialDevice" /> structure that
    ///   describes the serial device. </param>
    /// <seealso cref="wclSerialDevice" />
    virtual void DoRemoved(const wclSerialDevice& Device);

public:
    /// <summary> Creates a new Serial Monitor component. </summary>
    /// <remarks> The component must always be created in an application's
    ///   main thread. </remarks>
    CwclSerialMonitor();
    /// <summary> Frees the component. </summary>
    /// <remarks> The component must always be destroyed in an application's
    ///   main thread. </remarks>
    virtual ~CwclSerialMonitor();

    /// <summary> Starts monitoring hardware changes. </summary>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    int Start();
    /// <summary> Stops monitoring hardware changes. </summary>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    int Stop();

    /// <summary> Enumerates available serial devices. </summary>
    /// <param name="Devices"> On output contains array of found serial
    ///   devices. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <remarks> Even if the method completed with success the <c>Devices</c>
    ///   parameter can be <c>NULL</c> or empty if no one serial device was
    ///   found. </remarks>
    /// <seealso cref="wclSerialDevice" />
    int EnumDevices(wclSerialDevices& Devices) const;

    /// <summary> Gets the hardware monitoring tsate. </summary>
    /// <returns> <c>True</c> if the hardware monitoring is active. <c>False</c>
    ///   otherwise. </returns>
    bool GetMonitoring() const;

    /// <summary> The event fires when a new serial device appeared in the
    ///   system </summary>
    /// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The <see cref="wclSerialDevice" /> structure that
	///   describes the Serial Device. </param>
	/// <seealso cref="wclSerialDevice" />
    wclSerialDeviceEvent(OnInserted);
    /// <summary> The event fires when a serial device has been removed from the
    ///   system. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The <see cref="wclSerialDevice" /> structure that
	///   describes the Serial Device. </param>
	/// <seealso cref="wclSerialDevice" />
    wclSerialDeviceEvent(OnRemoved);
};

/// <summary> The structure contains information about USB device. </summary>
typedef struct
{
	/// <summary> The USB device's friendly name. </summary>
	tstring FriendlyName;
	/// <summary> The USB device's hardware ID. </summary>
	tstring HardwareId;
	/// <summary> The USB device vendor ID (VID). </summary>
	unsigned short VendorId;
	/// <summary> The USB device product ID (PID). </summary>
	unsigned short ProductId;
	/// <summary> The USB device revision (REV). </summary>
	unsigned short Revision;
	/// <summary> The USB device's instance string. </summary>
	/// <remarks> This is the Device Path value that can be used in the
	///   <c>CreateFile</c> call to access the device. </remarks>
	tstring Instance;
	/// <summary> The USB device's manufacturer name. </summary>
	tstring Manufacturer;
	/// <summary> Device's class GUID. </summary>
	GUID ClassGuid;
	/// <summary> Device status. <c>True</c> if device up and running.
	///   <c>False</c> if device is disabled. </summary>
	bool Enabled;
} wclUsbDevice;
/// <summary> The array contains list of found USB devices. </summary>
/// <seealso cref="wclUsbDevice" />
typedef std::list<wclUsbDevice>	wclUsbDevices;

/// <summary> The event handler prototype for the <c>OnInserted</c> and
///   <c>OnRemoved</c> events. </summary>
/// <param name="Sender"> The object initiates the event. </param>
/// <param name="Device"> The <see cref="wclUsbDevice" /> structure that
///   describes the USB Device. </param>
/// <seealso cref="wclUsbDevice" />
#define wclUsbDeviceEvent(_event_name_) \
	__event void _event_name_(void* Sender, const wclUsbDevice& Device)

/// <summary> The USB Monitor allows your application to enumerate
///   available USB devices and to monitor changes in its
///   configuration. </summary>
class CwclUsbMonitor
{
	DISABLE_COPY(CwclUsbMonitor);

private:
	RTL_CRITICAL_SECTION	FCS;
	CwclMessageReceiver*	FReceiver;
	
	int GetDeviceStatus(const tstring& Instance,
		bool& Enabled) const;

	tstring GetDevicePropertySetupApi(const tstring& Instance,
		const DWORD Prop) const;
	tstring GetDevicePropertyCfgMgr(const tstring& Instance, 
		const DWORD Prop) const;
	tstring GetDeviceProperty(const tstring& Instance, 
		const DWORD Prop) const;
	
	unsigned short GetVendorId(const tstring& HwId) const;
	unsigned short GetProductId(const tstring& HwId) const;
	unsigned short GetRevision(const tstring& HwId) const;

	void AddDevice(const tstring& DevId,
		wclUsbDevices& Devices) const;

	int EnumDevicesSetupApi(wclUsbDevices& Devices) const;
	int EnumDevicesCfgMgr(wclUsbDevices& Devices) const;

	int SwitchDevice(const tstring& Instance,
		const bool Enable) const;
	
protected:
	/// <summary> The method called when a new notification message
	///   received. </summary>
	/// <param name="Message"> A <see cref="CwclMessage" /> object
	///   represents a notification message. </param>
	/// <remarks> <para> This method is for internal use only. </para>
	///   <para> If a derived class overrides this method it must always call
	///   the inherited implementation first. </para> </remarks>
	/// <seealso cref="CwclMessage" />
	virtual void MessageReceived(const CwclMessage* const Message);
	
	/// <summary> Fires the <c>OnInserted</c> event. </summary>
	/// <param name="Device"> The <see cref="wclUsbDevice" /> structure that
	///   describes the serial device. </param>
	/// <seealso cref="wclUsbDevice" />
	virtual void DoInserted(const wclUsbDevice& Device);
	/// <summary> Fires the <c>OnRemoved</c> event. </summary>
	/// <param name="Device"> The <see cref="wclUsbDevice" /> structure that
	///   describes the serial device. </param>
	/// <seealso cref="wclUsbDevice" />
	virtual void DoRemoved(const wclUsbDevice& Device);
	
public:
	/// <summary> Creates a new USB Monitor component. </summary>
	/// <remarks> The component must always be created in an application's
	///   main thread. </remarks>
	CwclUsbMonitor();
	/// <summary> Frees the component. </summary>
	/// <remarks> The component must always be destroyed in an application's
	///   main thread. </remarks>
	virtual ~CwclUsbMonitor();
	
	/// <summary> Starts monitoring hardware changes. </summary>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	int Start();
	/// <summary> Stops monitoring hardware changes. </summary>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	int Stop();

	/// <summary> Disables USB device. </summary>
	/// <param name="Instance"> The USB device's instance string. </param>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	/// <remarks> The function requires administrative rights. </remarks>
	int Disable(const tstring& Instance) const;
	/// <summary> Enabled USB device. </summary>
	/// <param name="Instance"> The USB device's instance string. </param>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	/// <remarks> The function requires administrative rights. </remarks>
	int Enable(const tstring& Instance)  const;
	
	/// <summary> Enumerates available USB devices. </summary>
	/// <param name="Devices"> On output contains array of found USB
	///   devices. </param>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	/// <seealso cref="wclUsbDevices" />
	int EnumDevices(wclUsbDevices& Devices) const;
	
	/// <summary> Gets the hardware monitoring state. </summary>
	/// <returns> <c>True</c> if the hardware monitoring is active. <c>False</c>
	///   otherwise. </returns>
	bool GetMonitoring() const;
	
	/// <summary> The event fires when a new USB device appeared in the
	///   system </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The <see cref="wclUsbDevice" /> structure that
	///   describes the USB Device. </param>
	/// <seealso cref="wclUsbDevice" />
	wclUsbDeviceEvent(OnInserted);
	/// <summary> The event fires when a USB device has been removed from the
	///   system. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Device"> The <see cref="wclUsbDevice" /> structure that
	///   describes the USB Device. </param>
	/// <seealso cref="wclUsbDevice" />
	wclUsbDeviceEvent(OnRemoved);
};

/// <summary> The list represents a COM port numbers.. </summary>
typedef std::list<unsigned int> wclComPortNumbers;

/// <summary> The class provides access to the system COM ports
///   database. </summary>
class CwclComDatabase
{
	DISABLE_COPY(CwclComDatabase);
	
private:
	HANDLE	FComDb;
	
public:
	/// <summary> Creates a new component. </summary>
	/// <remarks> The component must always be created in an application's
	///   main thread. </remarks>
	CwclComDatabase();
	/// <summary> Frees the component. </summary>
	/// <remarks> The component must always be destroyed in an application's
	///   main thread. </remarks>
	virtual ~CwclComDatabase();
	
	/// <summary> Closes the COM database. </summary>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	int Close();
	/// <summary> Opens the COM database. </summary>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	int Open();

	/// <summary> Tries to get the lowest COM port number that is not already
	///   in use. </summary>
	/// <param name="Port"> If the method completed with success on output contains
	///   the free COM port number. </param>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	/// <remarks> Please note that this method does not create any serial
	///   device. This just makes you sure that no one other application and/or
	///   driver creates serial (COM) device with the same number. </remarks>
	int ClaimPort(unsigned long& Port);
	/// <summary> Enumerates the used COM ports. </summary>
	/// <param name="Ports"> The array that will be filled with used COM port
    ///   numbers. </param>
	/// <returns> If the function succeed the return value is
	///   <see cref="wclErrors.WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	/// <seealso cref="wclComPortNumbers" />
	int EnumUsedPorts(wclComPortNumbers& Ports);
	/// <summary> Releases a COM port number in the COM port database. </summary>
	/// <param name="Port"> Specifies the COM port number to release. This must
	///   be a port number returned by the <c>ClaimPort</c> method. </param>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	/// <remarks> Please note that this method does not destroy any serial
	///   device. This just release the serial (COM) device number so any other
	///   application and/or driver can now use this number. </remarks>
	int ReleasePort(const unsigned long Port);
	
	/// <summary> Gets the COM ports database status. </summary>
	/// <returns> The <c>Boolean</c> value indicates the COM database status.
	///   <c>true</c> if the COM database is opened. <c>false</c>
	///   otherwise. </returns>
	bool GetOpened() const;
};

/// <summary> Helper function that reads serial device information by its Device
///   Instance ID. </summary>
/// <param name="Instance"> The device instance ID string. </param>
/// <param name="Device"> The <see cref="wclSerialDevice" /> object with
///   device information. </param>
/// <returns> If the function succeed the return value is
///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
///   the WCL error codes. </returns>
/// <seealso cref="wclSerialDevice" />
int wclReadDeviceInformation(const tstring& Instance, wclSerialDevice& Device);

}