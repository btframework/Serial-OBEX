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
//   WCL Serial Framework: Serial Clients.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <set>

#include "..\Common\wclHelpers.h"

#include "..\Communication\wclConnections.h"

#include "wclSerialDevices.h"
#include "wclSerialErrors.h"

using namespace wclCommon;
using namespace wclCommunication;

namespace wclSerial
{

/// <summary> Specifies the DTR (data-terminal-ready) input flow
///   control. </summary>
typedef enum
{
	/// <summary> Lowers the DTR line when the device is opened. The application
	///   can adjust the state of the line with
	///   <c>EscapeCommFunction</c>. </summary>
	dtrControlDisable,
	/// <summary> Raises the DTR line when the device is opened. The application
	///   can adjust the state of the line with
	///   <c>EscapeCommFunction</c>. </summary>
	dtrControlEnable,
	/// <summary> Enables DTR flow-control handshaking. If this value is used,
	///   it is an error for the application to adjust the line with
	///   <c>EscapeCommFunction</c>. </summary>
	dtrControlHandshake
} wclSerialDtrControl;

/// <summary> Specifies the RTS (request-to-send) input flow
///   control. </summary>
typedef enum
{
    /// <summary> Lowers the RTS line when the device is opened. The application
    ///   can use <c>EscapeCommFunction</c> to change the state of the
    ///   line. </summary>
    rtsControlDisable,
    /// <summary> Raises the RTS line when the device is opened. The application
    ///   can use <c>EscapeCommFunction</c> to change the state of the
    ///   line. </summary>
    rtsControlEnable,
    /// <summary> Enables RTS flow-control handshaking. The driver raises the
    ///   RTS line, enabling the DCE to send, when the input buffer has enough
    ///   room to receive data. The driver lowers the RTS line, preventing the
    ///   DCE to send, when the input buffer does not have enough room to
    ///   receive data. If this value is used, it is an error for the
    ///   application to adjust the line with
    ///   <c>EscapeCommFunction</c>. </summary>
    rtsControlHandshake,
    /// <summary> Specifies that the RTS line will be high if bytes are
    ///   available for transmission. After all buffered bytes have been sent,
    ///   the RTS line will be low. If this value is set, it would be an error
    ///   for an application to adjust the line with
    ///   <c>EscapeCommFunction</c>. </summary>
    rtsControlToggle
} wclSerialRtsControl;

/// <summary> Specifies the parity scheme to be used. </summary>
typedef enum
{
	/// <summary> No parity. </summary>
	spNo,
    /// <summary> Odd parity. </summary>
    spOdd,
    /// <summary> Even parity. </summary>
    spEven,
    /// <summary> Mark parity. </summary>
    spMark,
    /// <summary> Space parity. </summary>
    spSpace 
} wclSerialParity;
/// <summary> The set of supported parities. </summary>
/// <seealso cref="wclSerialParity" />
typedef std::set<wclSerialParity> wclSerialParities;

/// <summary> Specifies the number of stop bits to be used. </summary>
typedef enum
{
    /// <summary> 1 stop bit. </summary>
    sbOne,
    /// <summary> 1.5 stop bits. </summary>
    sbOne5,
    /// <summary> 2 stop bits. </summary>
    sbTwo
} wclSerialStopBits;
/// <summary> Set of the number of stop bits to be used. </summary>
/// <seealso cref="wclSerialStopBits" />
typedef std::set<wclSerialStopBits> wclSerialStopBitsSet;

/// <summary> The structure describes a serial device (COM port) configuration
///   settings that is used to open the COM port. </summary>
typedef struct
{
    /// <summary> Specifies the baud at which the communications device
    ///   operates. This member can be an actual baud value, or a baud
    ///   index. </summary>
	unsigned long BaudRate;
    /// <summary> Specifies whether parity checking is enabled. If this member
    ///   is <c>True</c>, parity checking is performed and parity errors are
    ///   reported. This should not be confused with the <c>Parity</c> member,
    ///   which controls the type of parity used in communications. </summary>
    bool ParityCheck;
    /// <summary> Specifies whether the CTS (clear-to-send) signal is monitored
    ///   for output flow control. If this member is <c>True</c> and CTS is
    ///   low, output is suspended until CTS is high again. The CTS signal is
    ///   under control of the DCE (usually a modem), the DTE (usually the PC)
    ///   simply monitors the status of this signal, the DTE does not
    ///   change it. </summary>
    bool OutxCtsFlow;
    /// <summary> Specifies whether the DSR (data-set-ready) signal is monitored
    ///   for output flow control. If this member is <c>True</c> and DSR is low,
    ///   output is suspended until DSR is high again. Once again, this signal
    ///   is under the control of the DCE; the DTE only monitors this
    ///   signal. </summary>
    bool OutxDsrFlow;
    /// <summary> Specifies the DTR (data-terminal-ready) input flow
    ///   control. </summary>
    /// <seealso cref="wclSerialDtrControl" />
    wclSerialDtrControl DtrControl;
    /// <summary> Specifies whether the communications driver is sensitive to
    ///   the state of the DSR signal. If this member is <c>True</c> the driver
    ///   ignores any bytes received, unless the DSR modem input line is
    ///   high. </summary>
    bool DsrSensitivity;
    /// <summary> Specifies whether transmission stops when the input buffer is
    ///   full and the driver has transmitted the XOFF character. If this
    ///   member is <c>True</c>, transmission continues after the XOFF character
    ///   has been sent. If this member is <c>False</c>, transmission does not
    ///   continue until the input buffer is within XonLim bytes of being empty
    ///   and the driver has transmitted the XON character. </summary>
    bool TXContinueOnXoff;
    /// <summary> Specifies whether XON/XOFF flow control is used during
    ///   transmission. If this member is <c>True</c>, transmission stops when
    ///   the XOFF character is received and starts again when the XON
    ///   character is received. </summary>
    bool OutX;
    /// <summary> Specifies whether XON/XOFF flow control is used during
    ///   reception. If this member is <c>True</c>, the XOFF character is sent
    ///   when the input buffer comes within XoffLim bytes of being full, and
    ///   the XON character is sent when the input buffer comes within XonLim
    ///   bytes of being empty. </summary>
    bool InX;
    /// <summary> Specifies whether bytes received with parity errors are
    ///   replaced with the character specified by the <c>ErrorChar</c> member.
    ///   If this member is <c>True</c> and the <c>Parity</c> member is
    ///   <c>True</c>, replacement occurs. </summary>
    bool ErrorCharReplace;
    /// <summary> Specifies whether null bytes are discarded. If this member
    ///   is <c>True</c>, null bytes are discarded when received. </summary>
    bool NullStrip;
    /// <summary> Specifies the RTS (request-to-send) input flow
    ///   control. </summary>
    /// <seealso cref="wclSerialRtsControl" />
    wclSerialRtsControl RtsControl;
    /// <summary> Specifies whether read and write operations are terminated if
    ///   an error occurs. If this member is <c>True</c>, the driver terminates
    ///   all read and write operations with an error status if an error occurs.
    ///   The driver will not accept any further communications operations until
    ///   the application has acknowledged. </summary>
    bool AbortOnError;
    /// <summary> Specifies the minimum number of bytes allowed in the input
    ///   buffer before the XON character is sent. </summary>
    unsigned short XonLim;
    /// <summary> Specifies the maximum number of bytes allowed in the input
    ///   buffer before the XOFF character is sent. The maximum number of bytes
    ///   allowed is calculated by subtracting this value from the size, in
    ///   bytes, of the input buffer. </summary>
    unsigned short XoffLim;
    /// <summary> The number of bits in the bytes transmitted and
    ///   received. </summary>
    unsigned char ByteSize;
    /// <summary> Specifies the parity scheme to be used. </summary>
    wclSerialParity Parity;
    /// <summary> Specifies the number of stop bits to be used. </summary>
    wclSerialStopBits StopBits;
    /// <summary> Specifies the value of the XON character for both transmission
    ///   and reception. </summary>
    char XonChar;
    /// <summary> Specifies the value of the XOFF character for both
    ///   transmission and reception. </summary>
    char XoffChar;
    /// <summary> Specifies the value of the character used to replace bytes
    ///   received with a parity error. </summary>
    char ErrorChar;
    /// <summary> Specifies the value of the character used to signal the end
    ///   of data. </summary>
    char EofChar;
    /// <summary> Specifies the value of the character used to cause the
    ///   <c>evRxFlag</c> event. </summary>
    char EvtChar;
} wclSerialConfig;

/// <summary> Contains the time-out parameters for a communications
///   device. </summary>
/// <remarks> <para> If an application sets <c>ReadInterval</c> and
///   <c>ReadMultiplier</c> to <c>MAXDWORD</c> and sets <c>ReadConstant</c> to
///   a value greater than zero and less than <c>MAXDWORD</c>, one of the
///   following occurs when the ReadFile function is called: </para>
///   <para> If there are any bytes in the input buffer, ReadFile returns
///   immediately with the bytes in the buffer. </para>
///   <para> If there are no bytes in the input buffer, ReadFile waits until
///   a byte arrives and then returns immediately. </para>
///   <para> If no bytes arrive within the time specified by
///   <c>ReadConstant</c>, ReadFile times out. </para> </remarks>
typedef struct
{
    /// <summary> <para> The maximum time allowed to elapse before the arrival
    ///   of the next byte on the communications line, in milliseconds. If the
    ///   interval between the arrival of any two bytes exceeds this amount,
    ///   the ReadFile operation is completed and any buffered data is returned.
    ///   A value of zero indicates that interval time-outs are not
    ///   used. </para>
    ///   <para> A value of <c>MAXDWORD</c>, combined with zero values for both
    ///   the <c>ReadConstant</c> and <c>ReadMultiplier</c> members, specifies
    ///   that the read operation is to return immediately with the bytes that
    ///   have already been received, even if no bytes have been
    ///   received. </para> </summary>
    unsigned long ReadInterval;
    /// <summary> The multiplier used to calculate the total time-out period for
    ///   read operations, in milliseconds. For each read operation, this value
    ///   is multiplied by the requested number of bytes to be read. </summary>
    unsigned long ReadMultiplier;
    /// <summary> <para> A constant used to calculate the total time-out period
    ///   for read operations, in milliseconds. For each read operation, this
    ///   value is added to the product of the <c>ReadMultiplier</c> member and
    ///   the requested number of bytes. </para>
    ///   <para> A value of zero for both the <c>ReadMultiplier</c> and
    ///   <c>ReadConstant</c> members indicates that total time-outs are not
    ///   used for read operations. </para> </summary>
    unsigned long ReadConstant;
    /// <summary> The multiplier used to calculate the total time-out period for
    ///   write operations, in milliseconds. For each write operation, this
    ///   value is multiplied by the number of bytes to be written. </summary>
    unsigned long WriteMultiplier;
    /// <summary> <para> A constant used to calculate the total time-out period
    ///   for write operations, in milliseconds. For each write operation, this
    ///   value is added to the product of the <c>WriteMultiplier</c> member and
    ///   the number of bytes to be written. </para>
    ///   <para> A value of zero for both the <c>WriteMultiplier</c> and
    ///   <c>WriteConstant</c> members indicates that total time-outs are not
    ///   used for write operations. </para> </summary>
    unsigned long WriteConstant;
} wclSerialTimeouts;

/// <summary> The flags used in <c>PurgeConmm</c> method. </summary>
typedef enum
{
    /// <summary> Terminates all outstanding overlapped read operations and
    ///   returns immediately, even if the read operations have not
    ///   been completed. </summary>
    purgeRxAbort,
    /// <summary> Clears the input buffer (if the device driver has
    ///   one). </summary>
    purgeRxClear,
    /// <summary> Terminates all outstanding overlapped write operations and
    ///   returns immediately, even if the write operations have not been
    ///   completed. </summary>
    purgeTxAbort,
    /// <summary> Clears the output buffer (if the device driver has
    ///   one). </summary>
    purgeTxClear
} wclSerialPurgeFlag;

/// <summary> The set of flags used in <c>PurgeComm</c> method. </summary>
/// <seealso cref="wclSerialPurgeFlag" />
typedef std::set<wclSerialPurgeFlag> wclSerialPurgeFlags;

/// <summary> The extended function to be performed by the
///   <c>EscapeCommFunction</c> method. </summary>
typedef enum
{
    /// <summary> Restores character transmission and places the transmission
    ///   line in a nonbreak state. The <c>escClrBreak</c> extended function
    ///   code is identical to the ClearCommBreak function. </summary>
    escClrBreak,
    /// <summary> Clears the DTR (data-terminal-ready) signal. </summary>
    escClrDtr,
    /// <summary> Clears the RTS (request-to-send) signal. </summary>
    escClrRts,
    /// <summary> Suspends character transmission and places the transmission
    ///   line in a break state until the ClearCommBreak function is called
    ///   (or <c>EscapeCommFunction</c> is called with the <c>sescClrBreak</c>
    ///   extended function code). The <c>escSetBreak</c> extended function
    ///   code is identical to the <c>SetCommBreak</c> function. Note that
    ///   this extended function does not flush data that has not been
    ///   transmitted. </summary>
    escSetBreak,
    /// <summary> Sends the DTR (data-terminal-ready) signal. </summary>
    escSetDtr,
    /// <summary> Sends the RTS (request-to-send) signal. </summary>
    escSetRts,
    /// <summary> Causes transmission to act as if an XOFF character has been
    ///   received. </summary>
    escSetXoff,
    /// <summary> Causes transmission to act as if an XON character has been
    ///   received. </summary>
    escSetXon
} wclSerialEscapeFunction;

/// <summary> The type of a serial device event. </summary>
typedef enum
{
    /// <summary> A break was detected on input. </summary>
    evBreak,
    /// <summary> The CTS (clear-to-send) signal changed state. </summary>
    evCts,
    /// <summary> The DSR (data-set-ready) signal changed state. </summary>
    evDsr,
    /// <summary> A ring indicator was detected. </summary>
    evRing,
    /// <summary> The RLSD (receive-line-signal-detect) signal changed
    ///   state. </summary>
    evRlsd,
    /// <summary> The event character was received. </summary>
    evChar
} wclSerialEvent;

/// <summary> The set of the communication events. </summary>
/// <seealso cref="wclSerialEvent" />
typedef std::set<wclSerialEvent> wclSerialEvents;

/// <summary> The serial errors. </summary>
typedef enum
{
    /// <summary> The hardware detected a break condition. </summary>
    erBreak,
    /// <summary> The hardware detected a framing error. </summary>
    erFrame,
    /// <summary> A character-buffer overrun has occurred. The next character
    ///   is lost. </summary>
    erOverrun,
    /// <summary> An input buffer overflow has occurred. There is either no
    ///   room in the input buffer, or a character was received after the
    ///   end-of-file (EOF) character. </summary>
    erRxOver,
    /// <summary> The hardware detected a parity error. </summary>
    erRxParity
} wclSerialError;

/// <summary> Set of serial device errors. </summary>
/// <seealso cref="wclSerialError" />
typedef std::set<wclSerialError> wclSerialErrors;

/// <summary> The enumeration describes state of the serial communication
///   device. </summary>
typedef enum
{
    /// <summary> Transmission is waiting for the CTS (clear-to-send) signal to
    ///   be sent. </summary>
    csCtsHold,
    /// <summary> Transmission is waiting for the DSR (data-set-ready) signal to
    ///   be sent. </summary>
    csDsrHold,
    /// <summary> Transmission is waiting for the RLSD
    ///   (receive-line-signal-detect) signal to be sent. </summary>
    csRlsdHold,
    /// <summary> Transmission is waiting because the XOFF character was
    ///   received. </summary>
    csXoffHold,
    /// <summary> Transmission is waiting because the XOFF character was
    ///   transmitted. (Transmission halts when the XOFF character is
    ///   transmitted to a system that takes the next character as XON,
    ///   regardless of the actual character.) </summary>
    csXoffSent,
    /// <summary> The end-of-file (EOF) character has been received. </summary>
    csEof,
    /// <summary> There is a character queued for transmission that has come to
    ///   the communications device by way of the <c>TransmitCommChar</c>
    ///   function. The communications device transmits such a character ahead
    ///   of other characters in the device's output buffer. </summary>
    csTxim
} wclSerialCommunicationState;

/// <summary> The set contains the current communication device
///   state. </summary>
/// <seealso cref="wclSerialCommunicationState" />
typedef std::set<wclSerialCommunicationState> wclSerialCommunicationStates;

/// <summary> The state of the modem control-register value. </summary>
typedef enum
{
    /// <summary> The CTS (clear-to-send) signal is on. </summary>
    msCtsOn,
    /// <summary> The DSR (data-set-ready) signal is on. </summary>
    msDsrOn,
    /// <summary> The ring indicator signal is on. </summary>
    msRingOn,
    /// <summary> The RLSD (receive-line-signal-detect) signal is on. </summary>
    msRlsdOn
} wclModemStatus;

/// <summary> The states of the modem control-register values. </summary>
/// <seealso cref="wclModemStatus" />
typedef std::set<wclModemStatus> wclModemStatuses;

/// <summary> The maximum allowable baud rate, in bits per second
///   (bps). </summary>
typedef enum
{
	/// <summary> 75 bps. </summary>
	br075,
	/// <summary> 110 bps. </summary>
	br110,
	/// <summary> 134.5 bps. </summary>
	br134_5,
	/// <summary> 150 bps. </summary>
	br150,
	/// <summary> 300 bps. </summary>
	br300,
	/// <summary> 600 bps. </summary>
	br600,
	/// <summary> 1200 bps. </summary>
	br1200,
	/// <summary> 1800 bps. </summary>
	br1800,
	/// <summary> 2400 bps. </summary>
	br2400,
	/// <summary> 4800 bps. </summary>
	br4800,
	/// <summary> 7200 bps. </summary>
	br7200,
	/// <summary> 9600 bps. </summary>
	br9600,
	/// <summary> 14400 bps. </summary>
	br14400,
	/// <summary> 19200 bps. </summary>
	br19200,
	/// <summary> 38400 bps. </summary>
	br38400,
	/// <summary> 56K bps. </summary>
	br56K,
	/// <summary> 57600 bps. </summary>
	br57600,
	/// <summary> 115200 bps. </summary>
	br115200,
	/// <summary> 128K bps. </summary>
	br128K,
	/// <summary> Programmable baud rate. </summary>
	brUser
} wclSerialBaudRate;
/// <summary> The serial port baud rates. </summary>
/// <seealso cref="wclSerialBaudRate" />
typedef std::set<wclSerialBaudRate> wclSerialBaudRates;

/// <summary> The communications-provider type. </summary>
typedef enum
{
	/// <summary> FAX device. </summary>
	stFax,
	/// <summary> LAT protocol. </summary>
	stLat,
	/// <summary> Modem device. </summary>
	stModem,
	/// <summary> Unspecified network bridge. </summary>
	stNetworkBridge,
	/// <summary> Parallel port. </summary>
	stParallelPort,
	/// <summary> RS-232 serial port. </summary>
	stRS232,
	/// <summary> RS-422 port. </summary>
	stRS422,
	/// <summary> RS-423 port. </summary>
	stRS423,
	/// <summary> RS-449 port. </summary>
	stRS449,
	/// <summary> Scanner device. </summary>
	stScanner,
	/// <summary> TCP/IP Telnet protocol. </summary>
	stTcpIpTelNet,
	/// <summary> X.25 standards. </summary>
	stX25,
	/// <summary> Unspecified. </summary>
	stUnspecified
} wclSerialType;

/// <summary> The possible serial port capabilities. </summary>
typedef enum
{
	/// <summary> Special 16-bit mode supported. </summary>
	sc16BitMode,
	/// <summary> DTR (data-terminal-ready)/DSR (data-set-ready)
	///   supported. </summary>
	scDtrDsr,
	/// <summary> Interval time-outs supported. </summary>
	scIntervalTimeouts,
	/// <summary> Parity checking supported. </summary>
	scParityCheck,
	/// <summary> RLSD (receive-line-signal-detect) supported. </summary>
	scRlsd,
	/// <summary> RTS (request-to-send)/CTS (clear-to-send)
	///   supported. </summary>
	scRtsCts,
	/// <summary> Settable XON/XOFF supported. </summary>
	scSetXChar,
	/// <summary> Special character support provided. </summary>
	scSpecialChars,
	/// <summary> The total (elapsed) time-outs supported. </summary>
	scTotalTimeouts,
	/// <summary> XON/XOFF flow control supported. </summary>
	scXOnXoff
} wclSerialCapability;
/// <summary> The capabilities offered by the serial port. </summary>
/// <seealso cref="wclSerialCapability" />
typedef std::set<wclSerialCapability> wclSerialCapabilities;

/// <summary> The communications parameters that can be changed. </summary>
typedef enum
{
	/// <summary> Baud rate. </summary>
	spBaud,
	/// <summary> Data bits. </summary>
	spDataBits,
	/// <summary> Handshaking (flow control). </summary>
	spHandshaking,
	/// <summary> Parity. </summary>
	spParity,
	/// <summary> Parity checking. </summary>
	spParityCheck,
	/// <summary> RLSD (receive-line-signal-detect). </summary>
	sRlsd,
	/// <summary> Stop bits. </summary>
	spStopBits
} wclSerialParam;
/// <summary> The set of the communications parameters that can be
///   changed. </summary>
/// <seealso cref="wclSerialParam" />
typedef std::set<wclSerialParam> wclSerialParams;

/// <summary> The number of data bits that can be set. </summary>
typedef enum
{
	/// <summary> 5 data bits. </summary>
	sdFive,
	/// <summary> 6 data bits. </summary>
	sdSix,
	/// <summary> 7 data bits. </summary>
	sdSeven,
	/// <summary> 8 data bits. </summary>
	sdEight,
	/// <summary> 16 data bits. </summary>
	sdSixteen,
	/// <summary> Wide path through serial hardware lines. </summary>
	sdWide
} wclSerialDataSize;
/// <summary> The set of number of data bits that can be set. </summary>
/// <seealso cref="wclSerialDataSize" />
typedef std::set<wclSerialDataSize> wclSerialDataSizes;

/// <summary> Contains communications driver features information. </summary>
typedef struct
{
	/// <summary> The maximum size of the driver's internal output buffer, in
	///   bytes. A value of zero indicates that no maximum value is imposed by
	///   the serial provider. </summary>
	unsigned long MaxTxBuffer;
	/// <summary> The maximum size of the driver's internal input buffer, in
	///   bytes. A value of zero indicates that no maximum value is imposed by
	///   the serial provider. </summary>
	unsigned long MaxRxBuffer;
	/// <summary> The maximum allowable baud rate, in bits per second
	///   (bps). </summary>
	/// <seealso cref="wclSerialBaudRate" />
	wclSerialBaudRate MaxBaudRate;
	/// <summary> The communications-provider type. </summary>
	/// <seealso cref="wclSerialType" />
	wclSerialType SerialType;
	/// <summary> The capabilities offered by the provider. </summary>
	/// <seealso cref="wclSerialCapabilities" />
	wclSerialCapabilities Capabilities;
	/// <summary> The communications parameters that can be changed. </summary>
	/// <seealso cref="wclSerialParams" />
	wclSerialParams SettableParams;
	/// <summary> The baud rates that can be used. </summary>
	/// <seealso cref="wclSerialBaudRates" />
	wclSerialBaudRates SettableBaud;
	/// <summary> The number of data bits that can be set. </summary>
	/// <seealso cref="wclSerialDataSizes" />
	wclSerialDataSizes SettableData;
	/// <summary> The stop bit that can be selected. </summary>
	/// <seealso cref="wclSerialStopBitsSet" />
	wclSerialStopBitsSet SettableStopBits;
	/// <summary> The parity settings that can be selected. </summary>
	/// <seealso cref="wclSerialParities" />
	wclSerialParities SettableParity;
} wclSerialFeatures;

/// <summary> The <c>OnError</c> event handler prototype. </summary>
/// <param name="Sender"> The object initiates the event. </param>
/// <param name="Errors"> The set of the detected errors. </param>
/// <param name="States"> The set of flags describes the current serial device
///   communication state. </param>
/// <seealso cref="wclSerialErrors" />
/// <seealso cref="wclSerialCommunicationStates" />
#define wclSerialDeviceErrorEvent(_event_name_) \
	__event void _event_name_(void* Sender, const wclSerialErrors& Errors, \
	const wclSerialCommunicationStates& States)
/// <summary> The <c>OnEvents</c> event handler prototype. </summary>
/// <param name="Sender"> The object initiates the event. </param>
/// <param name="Events"> The set of received events. </param>
/// <seealso cref="wclSerialEvents" />
#define wclSerialDeviceEventsEvent(_event_name_) \
	__event void _event_name_(void* Sender, const wclSerialEvents& Events)
/// <summary> The <c>OnReadError</c> event handler prototype. </summary>
/// <param name="Sender"> The object initiates the event. </param>
/// <param name="Error"> The reading operation result. </param>
#define wclSerialDeviceReadErrorEvent(_event_name_) \
	__event void _event_name_(void* Sender, const int Error)

/// <summary> The component represents a Serial Client connection. </summary>
class CwclSerialClient
{
	DISABLE_COPY(CwclSerialClient);
	
private:
	tstring						FDeviceName;
    CwclClientDataConnection*	FConnection;
	RTL_CRITICAL_SECTION		FCS;

	void Enter() const;
	void Leave() const;

    void ClientConnect(void* Sender, const int Error);
	void ClientData(void* Sender, const void* const Data, 
		const unsigned long Size);
	void ClientDisconnect(void* Sender, const int Reason);
	void ClientError(void* Sender, const wclSerialErrors& Errors,
		const wclSerialCommunicationStates& States);
	void ClientEvents(void* Sender, const wclSerialEvents& Events);
	void ClientReadError(void* Sender, const int Error);
	
protected:
    /// <summary> Fires the <c>OnConnect</c> event. </summary>
    /// <param name="Error"> The connection operation result code. If the
    ///   parameter is <see cref="WCL_E_SUCCESS" /> the connection to a remote
    ///   device was established and the remote device is connected. Otherwise
    ///   the connection was not established and the remote device is
    ///   not connected. </param>
    virtual void DoConnect(const int Error);
	/// <summary> Fires the <c>OnCreateProcessor</c> event. </summary>
    /// <param name="Connection"> The <see cref="CwclClientDataConnection" />
    ///   object that requires a data processor. </param>
    /// <seealso cref="CwclClientDataConnection" />
    virtual void DoCreateProcessor(CwclClientDataConnection* const Connection);
	/// <summary> Fires the <c>OnData</c> event. </summary>
    /// <param name="Data"> The pointer to the received data buffer.
    ///   It is guaranteed that the parameter points to a valid data buffer.
    ///   The data buffer is valid only inside the event handler. If an
    ///   application needs to use the data outside the event handle it must
    ///   allocate own buffer and copy data into it. </param>
    /// <param name="Size"> The data buffer size. It is guaranteed that the size
    ///   is greater than 0. </param>
    virtual void DoData(const void* const Data, const unsigned long Size);
	/// <summary> Fires the <c>OnDestroyProcessor</c> event. </summary>
    /// <param name="Connection"> The <see cref="CwclClientDataConnection" />
    ///   object that requires a data processor. </param>
    /// <seealso cref="CwclClientDataConnection" />
    virtual void DoDestroyProcessor(CwclClientDataConnection* const Connection);
    /// <summary> Fires the <c>OnDisconnect</c> event. </summary>
    /// <param name="Reason"> The disconnection code. If the
    ///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
    ///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
    ///   reason. </param>
    virtual void DoDisconnect(const int Reason);
    /// <summary> Fires the <c>OnError</c> event. </summary>
    /// <param name="Errors"> The set of the detected errors. </param>
    /// <param name="States"> The set of flags describes the current serial
    ///   device communication state. </param>
    /// <seealso cref="wclSerialErrors" />
    /// <seealso cref="wclSerialCommunicationStates" />
    virtual void DoError(const wclSerialErrors& Errors, 
		const wclSerialCommunicationStates& States);
    /// <summary> Fires the <c>OnEvent</c> event. </summary>
    /// <param name="Events"> The set of the serial device events. </param>
    /// <seealso cref="wclSerialEvents" />
    virtual void DoEvents(const wclSerialEvents& Events);
    /// <summary> Fires the <c>OnReadError</c> event. </summary>
    /// <param name="Error"> The read operation error code. </param>
    virtual void DoReadError(const int Error);
	
public:
    /// <summary> Create a new component. </summary>
    CwclSerialClient();
    /// <summary> Frees the component. </summary>
    virtual ~CwclSerialClient();

    /// <summary> Connects to a Serial Device (COM port). </summary>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    int Connect();
    /// <summary> Disconnects from the connected remote device. </summary>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <remarks> The method disconnects from the connected remote device or
    ///   terminates the pending connection. </remarks>
    int Disconnect();

    /// <summary> Reads the read buffer size. </summary>
    /// <param name="Size"> On output he read buffer size in bytes. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    int GetReadBufferSize(unsigned long& Size) const;
    /// <summary> Reads the write buffer size. </summary>
    /// <param name="Size"> On output the write buffer size in bytes. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    int GetWriteBufferSize(unsigned long& Size) const;

    /// <summary> Sets the read buffer size. </summary>
    /// <param name="Size"> The new read buffer size in bytes. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    int SetReadBufferSize(const unsigned long Size) const;
    /// <summary> Sets the write buffer size. </summary>
    /// <param name="Size"> The new write buffer size in bytes. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    int SetWriteBufferSize(const unsigned long Size) const;

    /// <summary> Sends data to the connected device. </summary>
    /// <param name="Data"> The pointer to the data buffer that should be sent
    ///   to the connected device. </param>
    /// <param name="Size"> The data buffer size. </param>
    /// <param name="Written"> The amount of bytes actually written to the
    ///   device. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <remarks> The write is synchronous operation. </remarks>
    int Write(const void* const Data, const unsigned long Size, 
		unsigned long& Written) const;
	
	/// <summary> Gets the Serial port features. </summary>
	/// <param name="Features"> If the method completed with success on output
	///   contains information about supported features. </param>
	/// <returns> If the function succeed the return value is
	///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
	///   the WCL error codes. </returns>
	/// <seealso cref="wclSerialFeatures" />
	int GetFeatures(wclSerialFeatures& Features) const;

    /// <summary> Gets the current serial port settings. </summary>
    /// <param name="Config"> If the method succeed the parameter contains the
    ///   current serial port configuration. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <seealso cref="wclSerialConfig" />
    int GetConfig(wclSerialConfig& Config) const;
    /// <summary> Sets the new serial port configuration. </summary>
    /// <param name="Config"> The new serial port configuration. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <remarks> It is recomended to read current configuration first by
    ///   calling the <c>GetConfig</c> method. </remarks>
    /// <seealso cref="wclSerialConfig" />
    int SetConfig(const wclSerialConfig& Config) const;

    /// <summary> Gets the current serial port timeouts. </summary>
    /// <param name="Timeouts"> If the function completed with success the
    ///   parameter contains the current serial port timeouts. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <seealso cref="wclSerialTimeouts" />
    int GetTimeouts(wclSerialTimeouts& Timeouts) const;
    /// <summary> Sets the serial port timeouts. </summary>
    /// <param name="Timeouts"> The new serial port timeouts. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <remarks> It is recomended to read default/current timeouts
    ///   firest by calling the <c>GetTimeouts</c> method. </remarks>
    /// <seealso cref="wclSerialTimeouts" />
    int SetTimeouts(const wclSerialTimeouts& Timeouts) const;

    /// <summary> Restores character transmission for a specified communications
    ///   device and places the transmission line in a nonbreak
    ///   state. </summary>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <remarks> A communications device is placed in a break state by the
    ///   <c>SetCommBreak</c> or <c>EscapeCommFunction</c> function. Character
    ///   transmission is then suspended until the break state is cleared by
    ///   calling <c>ClearCommBreak</c>. </remarks>
    int ClearCommBreak() const;
    /// <summary> Directs the specified communications device to perform an
    ///   extended function. </summary>
    /// <param name="Func"> The extended function to be performed. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <seealso cref="wclSerialEscapeFunction" />
    int EscapeCommFunction(const wclSerialEscapeFunction Func) const;
    /// <summary> Flushes the buffers and causes all buffered data to be sent
    ///   to the COM port. </summary>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    int FlushBuffers() const;
    /// <summary> Retrieves the modem control-register values. </summary>
    /// <param name="Status"> If the function completed with success
    ///   the parameter contaisn the current state of the modem control-register
    ///   values. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <remarks> <para> The <c>GetModemStatus</c> function is useful when you
    ///   received the CTS, RLSD, DSR, or ring indicator signals(through
    ///   <c>OnEvent</c> event.) </para>
    ///   <para> The function fails if the hardware does not support the
    ///   control-register values. </para> </remarks>
    /// <seealso cref="wclModemStatuses" />
    int GetModemStatus(wclModemStatuses& Status) const;
    /// <summary> Discards all characters from the output or input buffer of a
    ///   specified communications resource. It can also terminate pending
    ///   read or write operations on the resource. </summary>
    /// <param name="Flags"> The set of the <see cref="wclSerialPurgeFlags" />
    ///   flags. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <seealso cref="wclSerialPurgeFlags" />
    int PurgeComm(const wclSerialPurgeFlags& Flags) const;
    /// <summary> Suspends character transmission for a specified communications
    ///   device and places the transmission line in a break state until the
    ///   <c>ClearCommBreak</c> function is called. </summary>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    int SetCommBreak() const;
    /// <summary> Transmits a specified character ahead of any pending data in
    ///   the output buffer of the specified communications device. </summary>
    /// <param name="Ch"> The character to be transmitted. </param>
    /// <returns> If the function succeed the return value is
    ///   <see cref="WCL_E_SUCCESS" />. Otherwise the method returns one of
    ///   the WCL error codes. </returns>
    /// <remarks> <para> The <c>TransmitCommChar</c> function is useful for
    ///   sending an interrupt character (such as a CTRL+C) to a host
    ///   system. </para>
    ///   <para> If the device is not transmitting, <c>TransmitCommChar</c>
    ///   cannot be called repeatedly. Once <c>TransmitCommChar</c> places a
    ///   character in the output buffer, the character must be transmitted
    ///   before the function can be called again. If the previous character
    ///   has not yet been sent, <c>TransmitCommChar</c> returns an
    ///   error. </para> </remarks>
    int TransmitCommChar(const char Ch) const;

	/// <summary> Gets the Data Processor created for the connection. </summary>
    /// <returns> The <see cref="CwclCustomClientDataProcessor" />
    ///   object. </returns>
    /// <seealso cref="CwclCustomClientDataProcessor" />
    CwclCustomClientDataProcessor* GetProcessor() const;
    /// <summary> Gets the connection state. </summary>
    /// <returns> The <see cref="wclClientState" /> indicates the current
    ///   connection state. </returns>
    /// <seealso cref="wclClientState" />
    wclClientState GetState() const;

    /// <summary> Gets the serial device name. </summary>
    /// <returns> The name of the serial device tha shoul;d be used in
    ///   communication. </returns>
    tstring GetDeviceName() const;
	/// <summary> Sets the serial device name. </summary>
    /// <param name="value"> The name of the serial device tha shoul;d be used in
    ///   communication. </param>
    void SetDeviceName(const tstring& value);
    /// <summary> Gets the write operation timeout. </summary>
    /// <returns> The write operation timeout in milliseconds. </returns>
    unsigned long GetWriteTimeout() const;
	/// <summary> Sets the write operation timeout. </summary>
    /// <param name="value"> The write operation timeout in milliseconds. </param>
	void SetWriteTimeout(const unsigned long value) const;

    /// <summary> The event fires when a connection to a remote device
    ///   has been completed (with or without success). </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Error"> The disconnection code. If the
	///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
	///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
	///   reason. </param>
    /// <remarks> If the <c>Error</c> parameter of the event is not
    ///   <see cref="WCL_E_SUCCESS" /> an application may call <c>Connect</c>
    ///   method again from inside the event handler. </remarks>
    wclClientConnectionConnectEvent(OnConnect);
	/// <summary> The event fires when connection to a remote device has
    ///   been established with success to allow application provide a
    ///   data processor for the connection. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Connection"> The <see cref="CwclClientDataConnection" />
	///   object that requires a Data Processor. </param>
    /// <remarks> If an application needs an additional data processit it
    ///   can use Data Processors. An application must create a Data Processor
    ///   inside this event handler. If a Data Processor created for the
    ///   connection the <c>OnData</c> event will NOT fire. </remarks>
	/// <seealso cref="CwclClientDataConnection" />
	/// <seealso cref="CwclCustomClientDataProcessor" />
    wclClientConnectionProcessorEvent(OnCreateProcessor);
    /// <summary> The event fires when new data is received from the
    ///   connected remote device. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Data"> The pointer to the received data buffer.
	///   It is guaranteed that the parameter points to a valid data buffer.
	///   The data buffer is valid only inside the event handler. If an
	///   application needs to use the data outside the event handle it must
	///   allocate own buffer and copy data into it. </param>
	/// <param name="Size"> The data buffer size. It is guaranteed that the size
	///   is greater than 0. </param>
    wclConnectionDataEvent(OnData);
	/// <summary> The event fires when connection to a remote device has
    ///   been terminated. An application must destroy the Data Processor
    ///   created for the connection. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Connection"> The <see cref="CwclClientDataConnection" />
	///   object that requires a Data Processor. </param>
	/// <seealso cref="CwclClientDataConnection" />
	/// <seealso cref="CwclCustomClientDataProcessor" />
    wclClientConnectionProcessorEvent(OnDestroyProcessor);
    /// <summary> The event fires when the remote connected device has been
    ///   disconnected. </summary>
	/// <param name="Sender"> The object that initiated the event. </param>
	/// <param name="Reason"> The disconnection code. If the
	///   parameter is <see cref="WCL_E_SUCCESS" /> the connection was closed
	///   by the <c>Disconnect</c> call. Otherwise indicates the disconnection
	///   reason. </param>
    wclClientConnectionDisconnectEvent(OnDisconnect);
    /// <summary> The event fires when a error occured during
    ///   communication. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Errors"> The set of the detected errors. </param>
	/// <param name="States"> The set of flags describes the current serial device
	///   communication state. </param>
	/// <seealso cref="wclSerialErrors" />
	/// <seealso cref="wclSerialCommunicationStates" />
	wclSerialDeviceErrorEvent(OnError);
    /// <summary> The event fires when a serial device event
    ///   accoures. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Events"> The set of received events. </param>
	/// <seealso cref="wclSerialEvents" />
	wclSerialDeviceEventsEvent(OnEvents);
    /// <summary> The event fires when the error occured during read
    ///   operation. </summary>
	/// <param name="Sender"> The object initiates the event. </param>
	/// <param name="Error"> The reading operation result. </param>
    wclSerialDeviceReadErrorEvent(OnReadError);
};

}