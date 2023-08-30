/*
 * FreeRTOSIPConfig.h
 *
 *  Author: pherrmann
 */ 


#ifndef FREERTOS_IP_CONFIG_H
#define FREERTOS_IP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ipconfigUSE_IPv6
    #define ipconfigUSE_IPv6 (0)
#endif

#ifndef USE_LOG_EVENT
    #define USE_LOG_EVENT (0)
#endif

#ifndef ipconfigMULTI_INTERFACE
    #define ipconfigMULTI_INTERFACE (0)
#endif

#ifndef GMAC_USES_WAKEUP_CALLBACK
    #define GMAC_USES_WAKEUP_CALLBACK (0)
#endif

#ifndef ipconfigDHCP_SEND_DISCOVER_AFTER_AUTO_IP
    #define ipconfigDHCP_SEND_DISCOVER_AFTER_AUTO_IP (0)
#endif

#ifndef ipconfigUSE_LINKED_RX_MESSAGES
    #define ipconfigUSE_LINKED_RX_MESSAGES (0)
#endif

/* The priority used by the Ethernet MAC driver interrupt. */
#define configMAC_INTERRUPT_PRIORITY		( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY )

/* The priority used by the HSMCI peripheral. */
#define configHSMCI_INTERRUPT_PRIORITY		( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY )

/* Define the byte order of the target MCU (the MCU FreeRTOS+TCP is executing
on).  Valid options are pdFREERTOS_BIG_ENDIAN and pdFREERTOS_LITTLE_ENDIAN. */
#define ipconfigBYTE_ORDER pdFREERTOS_LITTLE_ENDIAN

/* Define whether the checksums are handled by the driver, or if they need to
be handled by the TCP/IP stack. */
#define ipconfigDRIVER_INCLUDED_TX_IP_CHECKSUM		( 1 )
#define ipconfigDRIVER_INCLUDED_RX_IP_CHECKSUM		( 1 )

	/*
	 * Note: tha SAM4E does have RX checksum offloading
	 * but TX checksum offloading has NOT been implemented.
	 */

#define ipconfigHAS_TX_CRC_OFFLOADING				( 0 )
#define ipconfigHAS_RX_CRC_OFFLOADING				( 1 )

/* Several API's will block until the result is known, or the action has been
performed, for example FreeRTOS_send() and FreeRTOS_recv().  The timeouts can be
set per socket, using setsockopt().  If not set, the times below will be
used as defaults. */
#define ipconfigSOCK_DEFAULT_RECEIVE_BLOCK_TIME	( 5000 )
#define	ipconfigSOCK_DEFAULT_SEND_BLOCK_TIME	( 5000 )

#define ipconfigZERO_COPY_RX_DRIVER			( 0 )
#define ipconfigZERO_COPY_TX_DRIVER			( 1 )

/* Include support for LLMNR: Link-local Multicast Name Resolution
(non-Microsoft).  This allows "ping [hostname]", "ftp [hostname]", etc. when the
IP address is not know. */
#define ipconfigUSE_LLMNR					( 1 )

/* Include support for NBNS: NetBIOS Name Service (Microsoft) */
#define ipconfigUSE_NBNS					( 1 )

/* Include support for DNS caching.  For TCP, having a small DNS cache is very
useful.  When a cache is present, ipconfigDNS_REQUEST_ATTEMPTS can be kept low
and also DNS may use small timeouts.  If a DNS reply comes in after the DNS
socket has been destroyed, the result will be stored into the cache.  The next
call to FreeRTOS_gethostbyname() will return immediately, without even creating
a socket. */
#define ipconfigUSE_DNS_CACHE				( 1 )
#define ipconfigDNS_CACHE_NAME_LENGTH		( 16 )
#define ipconfigDNS_CACHE_ENTRIES			( 4 )
#define ipconfigDNS_REQUEST_ATTEMPTS		( 4 )

/* The IP stack executes it its own task (although any application task can make
use of its services through the published sockets API). ipconfigIP_TASK_PRIORITY
sets the priority of the task that executes the IP stack.  The priority is a
standard FreeRTOS task priority so can take any value from 0 (the lowest
priority) to (configMAX_PRIORITIES - 1) (the highest priority).
configMAX_PRIORITIES is a standard FreeRTOS configuration parameter defined in
FreeRTOSConfig.h, not FreeRTOSIPConfig.h. Consideration needs to be given as to
the priority assigned to the task executing the IP stack relative to the
priority assigned to tasks that use the IP stack. */
#define ipconfigIP_TASK_PRIORITY			( configMAX_PRIORITIES - 2 )

/* The size, in words (not bytes), of the stack allocated to the FreeRTOS+TCP
task.  This setting is less important when the FreeRTOS Win32 simulator is used
as the Win32 simulator only stores a fixed amount of information on the task
stack.  FreeRTOS includes optional stack overflow detection, see:
http://www.freertos.org/Stacks-and-stack-overflow-checking.html */
#define ipconfigIP_TASK_STACK_SIZE_WORDS	( configMINIMAL_STACK_SIZE * 5 )

/* ipconfigRAND32() is called by the IP stack to generate random numbers for
things such as a DHCP transaction number or initial sequence number.  Random
number generation is performed via this macro to allow applications to use their
own random number generation method.  For example, it might be possible to
generate a random number by sampling noise on an analogue input. */
extern UBaseType_t uxRand( void );
#define ipconfigRAND32()	uxRand()

/* If ipconfigUSE_NETWORK_EVENT_HOOK is set to 1 then FreeRTOS+TCP will call the
network event hook at the appropriate times.  If ipconfigUSE_NETWORK_EVENT_HOOK
is not set to 1 then the network event hook will never be called.  See
http://www.FreeRTOS.org/FreeRTOS-Plus/FreeRTOS_Plus_UDP/API/vApplicationIPNetworkEventHook.shtml
*/
#define ipconfigUSE_NETWORK_EVENT_HOOK 1

/* Sockets have a send block time attribute.  If FreeRTOS_sendto() is called but
a network buffer cannot be obtained then the calling task is held in the Blocked
state (so other tasks can continue to executed) until either a network buffer
becomes available or the send block time expires.  If the send block time expires
then the send operation is aborted.  The maximum allowable send block time is
capped to the value set by ipconfigMAX_SEND_BLOCK_TIME_TICKS.  Capping the
maximum allowable send block time prevents prevents a deadlock occurring when
all the network buffers are in use and the tasks that process (and subsequently
free) the network buffers are themselves blocked waiting for a network buffer.
ipconfigMAX_SEND_BLOCK_TIME_TICKS is specified in RTOS ticks.  A time in
milliseconds can be converted to a time in ticks by dividing the time in
milliseconds by portTICK_PERIOD_MS. */
#define ipconfigUDP_MAX_SEND_BLOCK_TIME_TICKS ( pdMS_TO_TICKS( 5000 ) )

/* If ipconfigUSE_DHCP is 1 then FreeRTOS+TCP will attempt to retrieve an IP
address, netmask, DNS server address and gateway address from a DHCP server.  If
ipconfigUSE_DHCP is 0 then FreeRTOS+TCP will use a static IP address.  The
stack will revert to using the static IP address even when ipconfigUSE_DHCP is
set to 1 if a valid configuration cannot be obtained from a DHCP server for any
reason.  The static configuration used is that passed into the stack by the
FreeRTOS_IPInit() function call. */
#define ipconfigUSE_DHCP				1
#define ipconfigDHCP_REGISTER_HOSTNAME	1
#define ipconfigDHCP_USES_UNICAST       1

/* When ipconfigUSE_DHCP is set to 1, DHCP requests will be sent out at
increasing time intervals until either a reply is received from a DHCP server
and accepted, or the interval between transmissions reaches
ipconfigMAXIMUM_DISCOVER_TX_PERIOD.  The IP stack will revert to using the
static IP address passed as a parameter to FreeRTOS_IPInit() if the
re-transmission time interval reaches ipconfigMAXIMUM_DISCOVER_TX_PERIOD without
a DHCP reply being received. */
#define ipconfigMAXIMUM_DISCOVER_TX_PERIOD		( pdMS_TO_TICKS( 30000 ) )

/* MAC address configuration.  In a deployed production system this would
probably be read from an EEPROM.  In the demo it is just hard coded.  Make sure
each node on the network has a unique MAC address. */
#define configMAC_ADDR0		0x00
#define configMAC_ADDR1		0x11
#define configMAC_ADDR2		0x22
#define configMAC_ADDR3		0x33
#define configMAC_ADDR4		0x44
#define configMAC_ADDR5		0x47

/* Default IP address configuration.  Used in case ipconfigUSE_DHCP is set to 0, or
ipconfigUSE_DHCP is set to 1 but a DHCP server cannot be contacted. */
#define configIP_ADDR0		192
#define configIP_ADDR1		168
#define configIP_ADDR2		24
#define configIP_ADDR3		101

/* Default gateway IP address configuration.  Used in case ipconfigUSE_DHCP is
set to 0, or ipconfigUSE_DHCP is set to 1 but a DHCP server cannot be contacted. */
#define configGATEWAY_ADDR0	10
#define configGATEWAY_ADDR1	1
#define configGATEWAY_ADDR2	22
#define configGATEWAY_ADDR3	1

/* Default DNS server configuration.  OpenDNS addresses are 208.67.222.222 and
208.67.220.220.  Used if ipconfigUSE_DHCP is set to 0, or ipconfigUSE_DHCP is set
to 1 but a DHCP server cannot be contacted.*/
#define configDNS_SERVER_ADDR0 	88
#define configDNS_SERVER_ADDR1 	88
#define configDNS_SERVER_ADDR2 	88
#define configDNS_SERVER_ADDR3 	88

/* Default netmask configuration.  Used in case ipconfigUSE_DHCP is set to 0,
or ipconfigUSE_DHCP is set to 1 but a DHCP server cannot be contacted. */
#define configNET_MASK0		255
#define configNET_MASK1		255
#define configNET_MASK2		255
#define configNET_MASK3		0

/* The address of an echo server that will be used by the two demo echo client
tasks.
http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Clients.html
http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/UDP_Echo_Clients.html */
#define configECHO_SERVER_ADDR0	10
#define configECHO_SERVER_ADDR1 1
#define configECHO_SERVER_ADDR2 22
#define configECHO_SERVER_ADDR3 205

/* The ARP cache is a table that maps IP addresses to MAC addresses.  The IP
stack can only send a UDP message to a remove IP address if it knowns the MAC
address associated with the IP address, or the MAC address of the router used to
contact the remote IP address.  When a UDP message is received from a remote IP
address the MAC address and IP address are added to the ARP cache.  When a UDP
message is sent to a remote IP address that does not already appear in the ARP
cache then the UDP message is replaced by a ARP message that solicits the
required MAC address information.  ipconfigARP_CACHE_ENTRIES defines the maximum
number of entries that can exist in the ARP table at any one time. */
#define ipconfigARP_CACHE_ENTRIES		6

/* ARP requests that do not result in an ARP response will be re-transmitted a
maximum of ipconfigMAX_ARP_RETRANSMISSIONS times before the ARP request is
aborted. */
#define ipconfigMAX_ARP_RETRANSMISSIONS ( 5 )

/* ipconfigMAX_ARP_AGE defines the maximum time between an entry in the ARP
table being created or refreshed and the entry being removed because it is stale.
New ARP requests are sent for ARP cache entries that are nearing their maximum
age.  ipconfigMAX_ARP_AGE is specified in tens of seconds, so a value of 150 is
equal to 1500 seconds (or 25 minutes). */
#define ipconfigMAX_ARP_AGE			150

/* Implementing FreeRTOS_inet_addr() necessitates the use of string handling
routines, which are relatively large.  To save code space the full
FreeRTOS_inet_addr() implementation is made optional, and a smaller and faster
alternative called FreeRTOS_inet_addr_quick() is provided.  FreeRTOS_inet_addr()
takes an IP in decimal dot format (for example, "192.168.0.1") as its parameter.
FreeRTOS_inet_addr_quick() takes an IP address as four separate numerical octets
(for example, 192, 168, 0, 1) as its parameters.  If
ipconfigINCLUDE_FULL_INET_ADDR is set to 1 then both FreeRTOS_inet_addr() and
FreeRTOS_indet_addr_quick() are available.  If ipconfigINCLUDE_FULL_INET_ADDR is
not set to 1 then only FreeRTOS_indet_addr_quick() is available. */
#define ipconfigINCLUDE_FULL_INET_ADDR	1

/* ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS defines the total number of network buffer that
are available to the IP stack.  The total number of network buffers is limited
to ensure the total amount of RAM that can be consumed by the IP stack is capped
to a pre-determinable value. */
#if( ipconfigZERO_COPY_RX_DRIVER != 0 )
	/* _HT_ Actually we should know the value of 'configNUM_RX_DESCRIPTORS' here. */
	#define ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS		51 //( 25 + 6 + 10)
#else
	#define ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS		12
#endif

/* A FreeRTOS queue is used to send events from application tasks to the IP
stack.  ipconfigEVENT_QUEUE_LENGTH sets the maximum number of events that can
be queued for processing at any one time.  The event queue must be a minimum of
5 greater than the total number of network buffers. */
#define ipconfigEVENT_QUEUE_LENGTH		( ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS + 5 )

/* The address of a socket is the combination of its IP address and its port
number.  FreeRTOS_bind() is used to manually allocate a port number to a socket
(to 'bind' the socket to a port), but manual binding is not normally necessary
for client sockets (those sockets that initiate outgoing connections rather than
wait for incoming connections on a known port number).  If
ipconfigALLOW_SOCKET_SEND_WITHOUT_BIND is set to 1 then calling
FreeRTOS_sendto() on a socket that has not yet been bound will result in the IP
stack automatically binding the socket to a port number from the range
socketAUTO_PORT_ALLOCATION_START_NUMBER to 0xffff.  If
ipconfigALLOW_SOCKET_SEND_WITHOUT_BIND is set to 0 then calling FreeRTOS_sendto()
on a socket that has not yet been bound will result in the send operation being
aborted. */
#define ipconfigALLOW_SOCKET_SEND_WITHOUT_BIND 1

/* Defines the Time To Live (TTL) values used in outgoing UDP packets. */
#define ipconfigUDP_TIME_TO_LIVE		128
#define ipconfigTCP_TIME_TO_LIVE		128 /* also defined in FreeRTOSIPConfigDefaults.h */

/* USE_TCP: Use TCP and all its features */
#define ipconfigUSE_TCP				( 1 )

/* USE_WIN: Let TCP use windowing mechanism. */
#define ipconfigUSE_TCP_WIN			( 1 )

/* The MTU is the maximum number of bytes the payload of a network frame can
contain.  For normal Ethernet V2 frames the maximum MTU is 1500.  Setting a
lower value can save RAM, depending on the buffer management scheme used.  If
ipconfigCAN_FRAGMENT_OUTGOING_PACKETS is 1 then (ipconfigNETWORK_MTU - 28) must
be divisible by 8. */
#define ipconfigNETWORK_MTU					1500

/* Set ipconfigUSE_DNS to 1 to include a basic DNS client/resolver.  DNS is used
through the FreeRTOS_gethostbyname() API function. */
#define ipconfigUSE_DNS		1

/* If ipconfigREPLY_TO_INCOMING_PINGS is set to 1 then the IP stack will
generate replies to incoming ICMP echo (ping) requests. */
#define ipconfigREPLY_TO_INCOMING_PINGS				1

/* If ipconfigSUPPORT_OUTGOING_PINGS is set to 1 then the
FreeRTOS_SendPingRequest() API function is available. */
#define ipconfigSUPPORT_OUTGOING_PINGS				0

/* If ipconfigSUPPORT_SELECT_FUNCTION is set to 1 then the FreeRTOS_select()
(and associated) API function is available. */
#define ipconfigSUPPORT_SELECT_FUNCTION				1

/* If ipconfigFILTER_OUT_NON_ETHERNET_II_FRAMES is set to 1 then Ethernet frames
that are not in Ethernet II format will be dropped.  This option is included for
potential future IP stack developments. */
#define ipconfigFILTER_OUT_NON_ETHERNET_II_FRAMES 1

/* If ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES is set to 1 then it is the
responsibility of the Ethernet interface to filter out packets that are of no
interest.  If the Ethernet interface does not implement this functionality, then
set ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES to 0 to have the IP stack
perform the filtering instead (it is much less efficient for the stack to do it
because the packet will already have been passed into the stack).  If the
Ethernet driver does all the necessary filtering in hardware then software
filtering can be removed by using a value other than 1 or 0. */
#define ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES	1

/* The windows simulator cannot really simulate MAC interrupts, and needs to
block occasionally to allow other tasks to run. */
#define configWINDOWS_MAC_INTERRUPT_SIMULATOR_DELAY ( 2 / portTICK_PERIOD_MS )

/* Advanced only: in order to access 32-bit fields in the IP packets with
32-bit memory instructions, all packets will be stored 32-bit-aligned, plus
16-bits.  This has to do with the contents of the IP-packets: all 32-bit fields
are 32-bit-aligned, plus 16-bit(!). */
#define ipconfigPACKET_FILLER_SIZE 2

/* Define the size of the pool of TCP window descriptors.  On the average, each
TCP socket will use up to 2 x 6 descriptors, meaning that it can have 2 x 6
outstanding packets (for Rx and Tx).  When using up to 10 TP sockets
simultaneously, one could define TCP_WIN_SEG_COUNT as 120. */
#define ipconfigTCP_WIN_SEG_COUNT 64

/* Each TCP socket has a circular buffers for Rx and Tx, which have a fixed
maximum size.  Define the size of Rx buffer for TCP sockets. */
#define ipconfigTCP_RX_BUFFER_LENGTH	( 3 * ipconfigTCP_MSS ) //		( 3 * 1460 )

/* Define the size of Tx buffer for TCP sockets. */
#define ipconfigTCP_TX_BUFFER_LENGTH	( 2 * ipconfigTCP_MSS ) //		( 2 * 1460 )

/* When using call-back handlers, the driver may check if the handler points to
real program memory (RAM or flash) or just has a random non-zero value. */
#define ipconfigIS_VALID_PROG_ADDRESS(x) ( (x) != NULL )

/* Include support for TCP hang protection.  All sockets in a connecting or
disconnecting stage will timeout after a period of non-activity. */
#define ipconfigTCP_HANG_PROTECTION				( 1 )
#define ipconfigTCP_HANG_PROTECTION_TIME		( 30 )

/* Include support for TCP keep-alive messages. */
#define ipconfigTCP_KEEP_ALIVE				( 1 )
#define ipconfigTCP_KEEP_ALIVE_INTERVAL		( 20 ) /* in seconds */

/* The application must provide an xApplicationDHCPHook() implementation
when ipconfigUSE_DHCP_HOOK is set to 1. */
#define ipconfigUSE_DHCP_HOOK			( 0 )

/* Used to select the protocols supported by the standard TCP server task.  Set
to 1 to support the protocol or 0 to omit the protocol.  There are also setting
in main.c that either include or exclude the TCP server task from the example
altogether. */
#define ipconfigUSE_FTP						0
#define ipconfigUSE_HTTP					0

/* Buffer and window sizes for the FTP and HTTP servers. */
#define ipconfigFTP_TX_BUFSIZE				( 4 * ipconfigTCP_MSS )
#define ipconfigFTP_TX_WINSIZE				( 2 )
#define ipconfigFTP_RX_BUFSIZE				( 8 * ipconfigTCP_MSS )
#define ipconfigFTP_RX_WINSIZE				( 4 )
#define ipconfigHTTP_TX_BUFSIZE				( 4 * ipconfigTCP_MSS )
#define ipconfigHTTP_TX_WINSIZE				( 2 )
#define ipconfigHTTP_RX_BUFSIZE				( 4 * ipconfigTCP_MSS )
#define ipconfigHTTP_RX_WINSIZE				( 4 )
#ifdef ipconfigTCP_MSS
	#undef ipconfigTCP_MSS
#endif

#define ipconfigTCP_COMMAND_BUFFER_SIZE		( ipconfigTCP_MSS )
#define ipconfigTCP_FILE_BUFFER_SIZE		( ipconfigTCP_MSS )

/* UDP Logging related constants follow.  The standard UDP logging facility
writes formatted strings to a buffer, and creates a task that removes messages
from the buffer and sends them to the UDP address and port defined by the
constants that follow. */

/****** UDP logging settings. *************************************************/

/* If set to 1 then each message sent via the UDP logging facility will end
with \r\n.  If set to 0 then each message sent via the UDP logging facility will
end with \n. */
#define configUDP_LOGGING_NEEDS_CR_LF  ( 0 )

/* Sets the maximum length for a string sent via the UDP logging facility. */
#define configUDP_LOGGING_STRING_LENGTH	( 200 )

/* The UDP logging facility buffers messages until the UDP logging task is able
to transmit them.  configUDP_LOGGING_MAX_MESSAGES_IN_BUFFER sets the maximum
number of messages that can be buffered at any one time. */
#define	configUDP_LOGGING_MAX_MESSAGES_IN_BUFFER	( 30 )

/* The UDP logging facility creates a task to send buffered messages to the UDP
port.  configUDP_LOGGING_TASK_STACK_SIZE sets the task's stack size. */
#define	configUDP_LOGGING_TASK_STACK_SIZE  	( 512 )

/* The UDP logging facility creates a task to send buffered messages to the UDP
port.  configUDP_LOGGING_TASK_PRIORITY sets the task's priority.  It is
suggested to give the task a low priority to ensure it does not adversely effect
the performance of other TCP/IP stack activity. */
#define configUDP_LOGGING_TASK_PRIORITY   	( tskIDLE_PRIORITY  + 2 )

/* The UDP port to which the UDP logging facility sends messages. */
#define configUDP_LOGGING_PORT_REMOTE		2403

/* The local UDP port to which commands can be sent. */
#define configUDP_LOGGING_PORT_LOCAL		2402

/* Here it is possible to define the target IP address to send all UDP
logging as e.g.:

If not defined, the local broadcast address will be used, e.g. 192.168.0.255
*/

/* Prototype for the function used to print out.  In this case the standard
UDP logging facility is used. */
extern int lUDPLoggingPrintf( const char *pcFormatString, ... );

/* Set to 1 to print out debug messages.  If ipconfigHAS_DEBUG_PRINTF is set to
1 then FreeRTOS_debug_printf should be defined to the function used to print
out the debugging messages. */
#define ipconfigHAS_DEBUG_PRINTF	0
#if( ipconfigHAS_DEBUG_PRINTF == 1 )
	#define FreeRTOS_debug_printf(X)	lUDPLoggingPrintf X
#endif

/* Set to 1 to print out non debugging messages, for example the output of the
FreeRTOS_netstat() command, and ping replies.  If ipconfigHAS_PRINTF is set to 1
then FreeRTOS_printf should be set to the function used to print out the
messages. */
#define ipconfigHAS_PRINTF			0
#if( ipconfigHAS_PRINTF == 1 )
	#define FreeRTOS_printf(X)			lUDPLoggingPrintf X
#endif

/* === Specific for GMAC === */

/* Number of DMA buffers used by the driver for RX. */
#define GMAC_RX_BUFFERS  48 /* 96 * 128 = 12288 bytes = 8 full segments <-- This is the old definition, the new gmac.c define GMAC_RX_UNITSIZE as 1536 so 8 = 8 segments*/

/* Number of DMA buffer used by the driver for TX. */
#define GMAC_TX_BUFFERS  4  /* 2 * 1518 = 3036 bytes */

/* MAC PHY operation max retry count, used by gmac.c */
#define MAC_PHY_RETRY_MAX 1000000

/* BOARD_GMAC_PHY_ADDR will be defined in e.g. 'sam4e_xplained_pro.h' */
/*
#define BOARD_GMAC_PHY_ADDR     1
*/
#define ETHERNET_CONF_PHY_ADDR  BOARD_GMAC_PHY_ADDR

/* Ethernet MII/RMII mode.  Used by ksz8051mnl\ethernet_phy.c */
#define ETH_PHY_MODE  GMAC_PHY_RMII

#define ETHERNET_CONF_DATA_OFFSET  2

#define GMAC_USES_TX_CALLBACK 1

/* === End of GMAC specifics === */

/* The example IP trace macros are included here so the definitions are
available in all the FreeRTOS+TCP source files. */
//#include "DemoIPTrace.h"
#define ipconfigUSE_CALLBACKS			1

#define ipconfigCHECK_IP_QUEUE_SPACE	1

#define ipconfigIPERF_VERSION			3
#define USE_IPERF						1

#define ipconfigIPERF_TX_BUFSIZE				( 4 * ipconfigTCP_MSS )	/* Units of bytes. */
#define ipconfigIPERF_TX_WINSIZE				( 2 )			/* Size in units of MSS */
#define ipconfigIPERF_RX_BUFSIZE				( 6 * ipconfigTCP_MSS )	/* Units of bytes. */
#define ipconfigIPERF_RX_WINSIZE				( 4 );			/* Size in units of MSS */

#define ipconfigETHERNET_MINIMUM_PACKET_BYTES	( 60 )



#define ipconfigETHERNET_AN_ENABLE					1
#define ipconfigETHERNET_AUTO_CROSS_ENABLE			1

#define ipconfigSOCKET_HAS_USER_SEMAPHORE			1

#define ipconfigUSE_LOOPBACK						1

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FREERTOS_IP_CONFIG_H */