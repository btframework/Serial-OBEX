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
//   WCL Serial Framework: Error Codes.                                       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "..\Common\wclErrors.h"

using namespace wclCommon;

namespace wclSerial
{

/* Common Serial Framework error codes. */

/// <summary> The base error code for Serial Framework errors. </summary>
const int WCL_E_SERIAL_BASE = 0x00060000;
/// <summary> The device's registry key was not found or not enough
///  privilegies. </summary>
const int WCL_E_SERIAL_UNABLE_OPEN_DEVICE_KEY = WCL_E_SERIAL_BASE + 0x0000;
/// <summary> Unable to read a device's friendly name. </summary>
const int WCL_E_SERIAL_UNABLE_READ_FRIENDLY_NAME = WCL_E_SERIAL_BASE + 0x0001;
/// <summary> The device's parameters registry key was not found or not enough
///  privilegies. </summary>
const int WCL_E_SERIAL_UNABLE_OPEN_DEVICE_PARAMETERS_KEY = WCL_E_SERIAL_BASE + 0x0002;
/// <summary> Unable to read a device's port name. </summary>
const int WCL_E_SERIAL_UNABLE_READ_PORT_NAME = WCL_E_SERIAL_BASE + 0x0003;
/// <summary> The given Device Class Guid was not found. </summary> 
const int WCL_E_SERIAL_DEVICE_CLASS_NOT_FOUND = WCL_E_SERIAL_BASE + 0x0004;
/// <summary> Monitoring is running. </summary>
const int WCL_E_SERIAL_MONITORING_RUNNING = WCL_E_SERIAL_BASE + 0x0005;
/// <summary> Monitoring is not running. </summary>
const int WCL_E_SERIAL_MONITORING_NOT_RUNNING = WCL_E_SERIAL_BASE + 0x0006;
/// <summary> Unable to get read buffer size. </summary>
const int WCL_E_SERIAL_UNABLE_GET_READ_BUFFER = WCL_E_SERIAL_BASE + 0x0007;
/// <summary> Unable to get write buffer size. </summary>
const int WCL_E_SERIAL_UNABLE_GET_WRITE_BUFFER = WCL_E_SERIAL_BASE + 0x0008;
/// <summary> Unable to set read buffer size. </summary>
const int WCL_E_SERIAL_UNABLE_SET_READ_BUFFER = WCL_E_SERIAL_BASE + 0x0009;
/// <summary> Unable to set write buffer size. </summary>
const int WCL_E_SERIAL_UNABLE_SET_WRITE_BUFFER = WCL_E_SERIAL_BASE + 0x000A;
/// <summary> Unable to initialize the overlapped IO operation. </summary>
const int WCL_E_SERIAL_UNABLE_INIT_OVERLAPPED_OPERATION = WCL_E_SERIAL_BASE + 0x000B;
/// <summary> Write data to the serial port was failed. </summary>
const int WCL_E_SERIAL_WRITE_FAILED = WCL_E_SERIAL_BASE + 0x000C;
/// <summary> Timeout appeared during write operation. That doe snot mean
///   real error. That just means that some bytes were sent but time out
///   appeared before all bytes are sent. You can retry to send remaining
///   bytes or terminate connection. </summary>
const int WCL_E_SERIAL_WRITE_TIMEOUT = WCL_E_SERIAL_BASE + 0x000D;
/// <summary> A serial device has been removed. </summary>
const int WCL_E_SERIAL_DEVICE_REMOVED = WCL_E_SERIAL_BASE + 0x000E;
/// <summary> Unable to read COM port configuration. </summary>
const int WCL_E_SERIAL_UNABLE_GET_COMM_CONFIGURATION = WCL_E_SERIAL_BASE + 0x000F;
/// <summary> Unable to write COM port configuration. </summary>
const int WCL_E_SERIAL_UNABLE_SET_COMM_CONFIGURATION = WCL_E_SERIAL_BASE + 0x0010;
/// <summary> Unable to read COM port timeouts. </summary>
const int WCL_E_SERIAL_UNABLE_GET_COMM_TIMEOUTS = WCL_E_SERIAL_BASE + 0x0011;
/// <summary> Unable to write COM port timeouts. </summary>
const int WCL_E_SERIAL_UNABLE_SET_COMM_TIMEOUTS = WCL_E_SERIAL_BASE + 0x0012;
/// <summary> Unable create overlapped operation event. </summary>
const int WCL_E_SERIAL_UNABLE_CREATE_OVERLAPPED_EVENT = WCL_E_SERIAL_BASE + 0x0013;
/// <summary> Unable to open the specified COM port. </summary>
const int WCL_E_SERIAL_UNABLE_OPEN_PORT = WCL_E_SERIAL_BASE + 0x0014;
/// <summary> Unable clear input and output buffers. </summary>
const int WCL_E_SERIAL_UNABLE_CLEAR_BUFFERS = WCL_E_SERIAL_BASE + 0x0015;
/// <summary> Unable to set COM potr events mask. </summary>
const int WCL_E_SERIAL_UNABLE_SET_EVENTS_MASK = WCL_E_SERIAL_BASE + 0x0016;
/// <summary> The PurgeComm operation was failed. </summary>
const int WCL_E_SERIAL_PURGE_COMM_FAILED = WCL_E_SERIAL_BASE + 0x0017;
/// <summary> The <c>EscapeCommFunction</c> has been failed. </summary>
const int WCL_E_SERIAL_ESCAPE_COMM_FUNCTION_FAILED = WCL_E_SERIAL_BASE + 0x0018;
/// <summary> The <c>SetCommBreak</c> method failed. </summary>
const int WCL_E_SERIAL_SET_COMM_BREAK_FAILED = WCL_E_SERIAL_BASE + 0x0019;
/// <summary> The <c>ClearCommBreak</c> method failed. </summary>
const int WCL_E_SERIAL_CLEAR_COMM_BREAK_FAILED = WCL_E_SERIAL_BASE + 0x001A;
/// <summary> The <c>TransmitCommChar</c> method failed. </summary>
const int WCL_E_SERIAL_TRANSMIT_COMM_CHAR_FAILED = WCL_E_SERIAL_BASE + 0x001B;
/// <summary> The <c>FlushBuffers</c> method failed. </summary>
const int WCL_E_SERIAL_FLUSH_BUFFERS_FAILED = WCL_E_SERIAL_BASE + 0x001C;
/// <summary> The <c>GetCommStatus</c> method failed. </summary>
const int WCL_E_SERIAL_GET_MODEM_STATUS_FAILED = WCL_E_SERIAL_BASE + 0x001D;
/// <summary> Read operation failed. </summary>
const int WCL_E_SERIAL_READ_ERROR = WCL_E_SERIAL_BASE + 0x001E;
/// <summary> Unable create communication restart event. </summary>
const int WCL_E_SERIAL_UNABLE_CREATE_RESTART_EVENT = WCL_E_SERIAL_BASE + 0x001F;
/// <summary> Write operation was timed out on wait. Probably device is
///   disconnected or not available. </summary>
const int WCL_E_SERIAL_DEVICE_WRITE_TIMEOUT = WCL_E_SERIAL_BASE + 0x0020;
/// <summary> Configuration Manager DLL was not found. </summary>
const int WCL_E_SERIAL_CFGMGR_DLL_NOT_FOUND = WCL_E_SERIAL_BASE + 0x0021;
/// <summary> Required Configuration Manager functions (API) are not available. </summary>
const int WCL_E_SERIAL_CFGMGR_NOT_AVAILABLE = WCL_E_SERIAL_BASE + 0x0022;
/// <summary> Unable to locate specified device's node. </summary>
const int WCL_E_SERIAL_UNABLE_GET_DEVICE_NODE = WCL_E_SERIAL_BASE + 0x0023;
/// <summary> No one device's interface was found for specified device's
///   instance ID. </summary>
const int WCL_E_SERIAL_DEVICE_INTERFACES_NOT_FOUND = WCL_E_SERIAL_BASE + 0x0024;
/// <summary> Unable to switch (disable or enable) specified USB (serial)
///   devices. </summary>
const int WCL_E_SERIAL_DEVICE_SWITCH_FAILED = WCL_E_SERIAL_BASE + 0x0025;
/// <summary> COM features read failed. </summary>
const int WCL_E_SERIAL_UNABLE_GET_COMM_FEATURES = WCL_E_SERIAL_BASE + 0x0026;

/* USB monitor error codes. */

/// <summary> The base error code for USB monitor errors. </summary>
const int WCL_E_USB_MONITOR_BASE = WCL_E_SERIAL_BASE + 0x1000;
/// <summary> No USB devices found on this system. </summary>
const int WCL_E_USB_MONITOR_DEVICE_CLASS_NOT_FOUND = WCL_E_USB_MONITOR_BASE + 0x0000;
/// <summary> Monitoring is running. </summary>
const int WCL_E_USB_MONITORING_RUNNING = WCL_E_USB_MONITOR_BASE + 0x0001;
/// <summary> Monitoring is not running. </summary>
const int WCL_E_USB_MONITORING_NOT_RUNNING = WCL_E_USB_MONITOR_BASE + 0x0002;

/* COM database error codes. */

/// <summary> The base error code for COM database errors. </summary>
const int WCL_E_COM_DATABASE_BASE = WCL_E_SERIAL_BASE + 0x2000;
/// <summary> The COM Database API access Mutex creation failed. </summary>
const int WCL_E_COM_DATABASE_CREATE_MUTEX_FAILED = WCL_E_COM_DATABASE_BASE + 0x0000;
/// <summary> The COM Database API is not available. </summary>
const int WCL_E_COM_DATABASE_NOT_AVAILABLE = WCL_E_COM_DATABASE_BASE + 0x0001;
/// <summary> The COM Database API was not loaded. </summary>
const int WCL_E_COM_DATABASE_NOT_LOADED = WCL_E_COM_DATABASE_BASE + 0x0002;
/// <summary> The COM database is opened. </summary>
const int WCL_E_COM_DATABASE_OPENED = WCL_E_COM_DATABASE_BASE + 0x0003;
/// <summary> The COM database is closed. </summary>
const int WCL_E_COM_DATABASE_CLOSED = WCL_E_COM_DATABASE_BASE + 0x0004;
/// <summary> The routine could not open the database. </summary>
const int WCL_E_COM_DATABASE_ACCESS_DENIED = WCL_E_COM_DATABASE_BASE + 0x0005;
/// <summary> Unknown or undefined error. </summary>
const int WCL_E_COM_DATABASE_UNKNOWN = WCL_E_COM_DATABASE_BASE + 0x0006;
/// <summary> The method could not access the COM database. </summary>
const int WCL_E_COM_DATABASE_NOT_CONNECTED = WCL_E_COM_DATABASE_BASE + 0x0007;
/// <summary> Write to the COM port database failed. </summary>
const int WCL_E_COM_DATABASE_WRITE_FAILED = WCL_E_COM_DATABASE_BASE + 0x0008;
/// <summary> The COM port database handle is not valid. </summary>
const int WCL_E_COM_DATABASE_HANDLE_INVALID = WCL_E_COM_DATABASE_BASE + 0x0009;
/// <summary> The COM port database is full and cannot arbitrate any more port
///   numbers. </summary>
const int WCL_E_COM_DATABASE_FULL = WCL_E_COM_DATABASE_BASE + 0x000A;
/// <summary> The specified port number is not in the COM port
///   database. </summary>
const int WCL_E_COM_DATABASE_INVALID_PORT = WCL_E_COM_DATABASE_BASE + 0x000B;

}