#ifndef FBNETWORK_CONSTANTS_HPP
#define FBNETWORK_CONSTANTS_HPP

#include <mysql/mysql.h>
#include <set>
#include <string>
#include <sys/socket.h>
#include <variant>
#include <vector>
#ifdef __APPLE__
#include <sys/event.h>
#else
#include <sys/epoll.h>
#endif

/**
 * @namespace FBNetwork
 * @brief Namespace for network-related constants and types.
 * @details This namespace contains constants and types related to network operations.
 * @version 1.0.0
 */
namespace FBNetwork
{
/**
 * @brief Represents a network port number.
 * @details The `port` type is a typedef for `uint16_t` and is used to represent a network port number. Network ports are used to establish communication between networked devices.
 * @version 1.0.0
 */
typedef uint16_t port;
/**
 * @brief Represents a network domain.
 * @details The `domain` type is a typedef for `int` and is used to represent a network domain. Network domains are used to specify the type of network communication (e.g., IPv4, IPv6, local).
 * @version 1.0.0
 */
typedef int domain;
/**
 * @brief Represents a file descriptor.
 * @details The `fileDescriptor` type is a typedef for `int` and is used to represent a file descriptor. File descriptors are used to identify open files or sockets in a program.
 * @version 1.0.0
 */
typedef int fileDescriptor;

const int EVENT_TYPE = 0;
const int EVENT_CLIENT_ID = 1;

#ifdef __APPLE__
/**
 * @brief Represents a event.
 * @details The `event` type is a typedef for `struct kevent`It is used to represent an event in the event queue.
 * @version 1.0.0
 */
typedef struct kevent event;
#else
/**
 * @brief Represents a event.
 * @details The `event` type is a typedef for `struct epoll_event`. It is used to represent an event in the event queue.
 * @version 1.0.0
 */
typedef struct epoll_event event;
#endif

/**
 * @brief Represents the type of event.
 * @details The `EventType` enum class is used to represent the type of event in the event queue. It can be one of the following values: ERROR, CLIENT_WANTS_TO_CONNECT, or CLIENT_WANTS_TO_SEND_DATA.
 * @version 1.0.0
 */
enum class EventType
{
    ERROR,
    CLIENT_WANTS_TO_CONNECT,
    CLIENT_WANTS_TO_SEND_DATA
};

/**
 * @brief Represents a vector of events.
 * @details The `eventList` type is a typedef for `std::vector<event>`. It is used to represent a list of events in the event queue.
 * @version 1.0.0
 */
typedef std::vector<event> eventList;

/**
 * @brief Represents a tuple of event type and client ID.
 * @details The `eventTuple` type is a typedef for `std::tuple<EventType, int>`. It is used to represent a tuple of event type and client ID.
 * @version 1.0.0
 */
typedef std::tuple<EventType, int> eventTuple;

/**
 * @namespace SQL
 * @brief Contains constants and types related to SQL operations.
 * @details This namespace contains constants and types related to SQL operations, such as parameter types and result types.
 * @version 1.0.0
 */
namespace SQL
{
const std::vector<std::string> EMPTY_RESULT = {};
typedef std::variant<std::string, int, double, MYSQL_TIME, std::vector<char>> parameter;
} // namespace SQL
/**
 * @namespace Constants
 * @brief Contains constants used in the project.
 * @details This namespace contains various constants used throughout the project, such as buffer sizes and default
 * timeouts.
 * @version 1.0.0
 */
namespace Constants
{
const size_t BUFFER_SIZE = 1024;
const struct timeval DEFAULT_TIMEOUT = {60, 0};
const int MAX_EVENTS = 2048;
const int EVENT_ERROR = -1;
} // namespace Constants
/**
 * @namespace Log
 * @brief Contains constants related to logging.
 * @details This namespace contains constants related to logging, such as log levels and log messages.
 * @version 1.0.0
 */
namespace Log
{
const std::string INFO = "INFO";
const std::string WARNING = "WARNING";
const std::string ERROR = "ERROR";

const std::string DATABASE_TYPE_NAME = "type";
const std::string DATABASE_SOURCE_NAME = "source";
const std::string DATABASE_MESSAGE_NAME = "message";
} // namespace Log
/**
 * @namespace Domain
 * @brief Contains constants related to network domains.
 * @details This namespace contains constants representing different network domains, such as local domain, IPv4 domain,
 * and IPv6 domain.
 * @version 1.0.0
 */
namespace Domain
{
const int LOCAL_DOMAIN = PF_LOCAL;
const int IPV4_DOMAIN = PF_INET;
const int IPV6_DOMAIN = PF_INET6;
} // namespace Domain
/**
 * @namespace Port
 * @brief Namespace containing constants for various network ports.
 * @details This namespace contains constants representing well-known network ports for various protocols, such as TCP
 * and UDP.
 * @version 1.0.0
 */
namespace Port
{
namespace TCP
{
const port TCPMUX_PORT = 1;
const port ECHO_PORT = 7;
const port DISCARD_PORT = 9;
const port SYSTAT_PORT = 11;
const port DAYTIME_PORT = 13;
const port QOTD_PORT = 17;
const port MSP_PORT = 18;
const port CHARGEN_PORT = 19;
const port FTP_DATA_PORT = 20;
const port FTP_CONTROL_PORT = 21;
const port SSH_PORT = 22;
const port TELNET_PORT = 23;
const port SMTP_PORT = 25;
const port TIME_PORT = 37;
const port WHOIS_PORT = 43;
const port TACACS_PORT = 49;
const port DNS_PORT = 53;
const port GOPHER_PORT = 70;
const port NETRJS_PORT = 71;
const port FINGER_PORT = 79;
const port HTTP_PORT = 80;
const port KERBEROS_PORT = 88;
const port SUPDUP_PORT = 95;
const port NIC_HOST_NAME_PORT = 101;
const port ISO_TSAP_PORT = 102;
const port DICOM_PORT = 104;
const port CCSO_NAME_SERVER_PORT = 105;
const port RTELNET_PORT = 107;
const port SNA_PORT = 108;
const port POP2_PORT = 109;
const port POP3_PORT = 110;
const port SUNRPC_PORT = 111;
const port IDENT_PORT = 113;
const port AUTH_PORT = 113;
const port SFTP_PORT = 115;
const port UUCP_PORT = 117;
const port SQL_PORT = 118;
const port NNTP_PORT = 119;
const port NXEDIT_PORT = 126;
const port DCE_ENDPOINT_PORT = 135;
const port EPMAP_PORT = 135;
const port NETBIOS_NAME_SERVICE_PORT = 137;
const port NETBIOS_SESSION_SERVICE_PORT = 139;
const port IMAP_PORT = 143;
const port BFTP_PORT = 152;
const port SGMP_PORT = 153;
const port DMSP_PORT = 158;
const port SNMPTRAP_PORT = 162;
const port POST_SCRIPT_PRINT_PORT = 170;
const port XDMCP_PORT = 177;
const port BGP_PORT = 179;
const port IRC_PORT = 194;
const port SMUX_PORT = 199;
const port QMTP_PORT = 209;
const port Z39_50_PORT = 210;
const port IPX_PORT = 213;
const port MPP_PORT = 218;
const port IMAP3_PORT = 220;
const port ESRO_PORT = 259;
const port ARCISDMS_PORT = 262;
const port BGMP_PORT = 264;
const port HTTP_MGMT_PORT = 280;
const port TSP_PORT = 318;
const port RPKI_PORT = 323;
const port MATIP_TYPE_A_PORT = 350;
const port MATIP_TYPE_B_PORT = 351;
const port CLOANTO_NET_1_PORT = 356;
const port ODMR_PORT = 366;
const port RPC2PORTMAP_PORT = 369;
const port CODAAUTH2_PORT = 370;
const port CLEARCASE_PORT = 371;
const port AMIGANETFS_PORT = 373;
const port HP_DATA_ALARM_PORT = 383;
const port A_REMOTE_NETWORK_SERVER_SYSTEM_PORT = 384;
const port UNIDATA_LDM_PORT = 388;
const port LDAP_PORT = 389;
const port UPS_PORT = 401;
const port SLP_PORT = 427;
const port MOBILE_IP_AGENT_PORT = 434;
const port HTTPS_PORT = 443;
const port SNPP_PORT = 444;
const port MICROSOFT_DS_PORT = 445;
const port URL_RENDEZVOUS_PORT = 465;
const port SMTPS_PORT = 465;
const port TCPNETHASPSRV_PORT = 475;
const port RETROSPECT_PORT = 497;
const port MODBUS_PORT = 502;
const port CITADEL_PORT = 504;
const port FCP_PORT = 510;
const port REXEC_PORT = 512;
const port RLOGIN_PORT = 513;
const port LPD_PORT = 515;
const port EFS_PORT = 520;
const port NCP_PORT = 524;
const port RPC_PORT = 530;
const port NETNEWS_PORT = 532;
const port COMMERCE_PORT = 542;
const port KLOGIN_PORT = 543;
const port KSHELL_PORT = 544;
const port DHCPV6_CLIENT_PORT = 546;
const port DHCPV6_SERVER_PORT = 547;
const port AFP_PORT = 548;
const port NEW_RWHO_PORT = 550;
const port RTSP_PORT = 554;
const port RFS_PORT = 556;
const port FILEMAKER_WEB_SHARING_PORT = 591;
const port HTTP_RPC_EPMAP_PORT = 593;
const port RELIABLE_SYSLOG_SERVICE_PORT = 601;
const port TUNNEL_PORT = 604;
const port IPP_PORT = 631;
const port RLZ_DBASE_PORT = 635;
const port MSDP_PORT = 639;
const port SSNRC_CONTROL_PORT = 641;
const port SANITY_PORT = 643;
const port LDP_PORT = 646;
const port DHCP_FAILOVER_PORT = 647;
const port RRP_PORT = 648;
const port IEEE_MMS_PORT = 651;
const port SSNRC_DATA_PORT = 653;
const port MMS_MMP_PORT = 654;
const port TINC_PORT = 655;
const port IBM_RMC_PORT = 657;
const port DOOM_PORT = 666;
const port ACAP_PORT = 674;
const port CORBA_IIOP_SSL_PORT = 684;
const port REALM_RUSD_PORT = 688;
const port VATP_PORT = 690;
const port MSEXCH_ROUTING_PORT = 691;
const port LINUX_HA_PORT = 694;
const port IEEE_MMS_SSL_PORT = 695;
const port EPP_PORT = 700;
const port LMP_PORT = 701;
const port IRIS_OVER_BEEP_PORT = 702;
const port SILC_PORT = 706;
const port TBRPF_PORT = 712;
const port KERBEROS_ADMIN_PORT = 749;
const port RRH_PORT = 753;
const port TELL_SEND_PORT = 754;
const port MDBS_DAEMON_PORT = 800;
const port CMP_PORT = 829;
const port NETCONF_OVER_SSH_PORT = 830;
const port NETCONF_OVER_BEEP_PORT = 831;
const port NETCONF_FOR_SOAP_OVER_HTTPS_PORT = 832;
const port NETCONF_FOR_SOAP_OVER_BEEP_PORT = 833;
const port GDOI_PORT = 848;
const port DNS_OVER_TLS_PORT = 853;
const port ISCRI_PORT = 860;
const port OWAMP_CONTROL_PORT = 861;
const port TWAMP_CONTROL_PORT = 862;
const port RSYNCD_PORT = 873;
const port RNDC_PORT = 953;
const port FTPS_DATA_PORT = 989;
const port FTPS_CONTROL_PORT = 990;
const port NAS_PORT = 991;
const port TELNETS_PORT = 992;
const port IMAPS_PORT = 993;
const port POP3S_PORT = 995;
} // namespace TCP
namespace UDP
{
const port ECHO_PORT = 7;
const port DISCARD_PORT = 9;
const port SYSTAT_PORT = 11;
const port DAYTIME_PORT = 13;
const port QOTD_PORT = 17;
const port MSP_PORT = 18;
const port CHARGEN_PORT = 19;
const port TIME_PORT = 37;
const port NAMESERVER_PORT = 42;
const port TACACS_PORT = 49;
const port DNS_PORT = 53;
const port BOOTP_SERVER_PORT = 67;
const port BOOTP_CLIENT_PORT = 68;
const port TFTP_PORT = 69;
const port NETRJS_PORT = 71;
const port HTTP_PORT = 80;
const port KERBEROS_PORT = 88;
const port DICOM_PORT = 104;
const port CCSO_NAME_SERVER_PORT = 105;
const port RTELNET_PORT = 107;
const port SNA_PORT = 108;
const port SUNRPC_PORT = 111;
const port UUCP_PORT = 117;
const port SQL_PORT = 118;
const port NTP_PORT = 123;
const port NXEDIT_PORT = 126;
const port DCE_ENDPOINT_PORT = 135;
const port EPMAP_PORT = 135;
const port NETBIOS_NAME_SERVICE_PORT = 137;
const port NETBIOS_DATAGRAM_SERVICE_PORT = 138;
const port BFTP_PORT = 152;
const port SGMP_PORT = 153;
const port DMSP_PORT = 158;
const port SNMP_PORT = 161;
const port SNMPTRAP_PORT = 162;
const port POST_SCRIPT_PRINT_PORT = 170;
const port XDMCP_PORT = 177;
const port BGP_PORT = 179;
const port IRC_PORT = 194;
const port SMUX_PORT = 199;
const port Z39_50_PORT = 210;
const port IPX_PORT = 213;
const port MPP_PORT = 218;
const port IMAP_PORT = 220;
const port ESRO_PORT = 259;
const port ARCISDMS_PORT = 262;
const port BGMP_PORT = 264;
const port HTTP_MGMT_PORT = 280;
const port TSP_PORT = 318;
const port PTP_EVENT_PORT = 319;
const port PTP_GENERAL_PORT = 320;
const port MATIP_TYPE_A_PORT = 350;
const port MATIP_TYPE_B_PORT = 351;
const port CLOANTO_NET_1_PORT = 356;
const port ODMR_PORT = 366;
const port RPC2PORTMAP_PORT = 369;
const port CODAAUTH2_PORT = 370;
const port SECURECAST1_PORT = 370;
const port CLEARCASE_PORT = 371;
const port AMIGANETFS_PORT = 373;
const port HP_DATA_ALARM_PORT = 383;
const port A_REMOTE_NETWORK_SERVER_SYSTEM_PORT = 384;
const port UPS_PORT = 401;
const port SLP_PORT = 427;
const port NNTP_PORT = 433;
const port MOBILE_IP_AGENT_PORT = 434;
const port HTTPS_PORT = 443;
const port SNPP_PORT = 444;
const port MICROSOFT_DS_PORT = 445;
const port TCPNETHASPSRV_PORT = 475;
const port RETROSPECT_PORT = 497;
const port ISAKMP_PORT = 500;
const port MODBUS_PORT = 502;
const port CITADEL_PORT = 504;
const port FCP_PORT = 510;
const port COMSAT_PORT = 512;
const port WHO_PORT = 513;
const port SYSLOG_PORT = 514;
const port TALK_PORT = 517;
const port NTALK_PORT = 518;
const port RIP_PORT = 520;
const port RIPNG_PORT = 521;
const port NCP_PORT = 524;
const port TIMESERVER_PORT = 525;
const port RPC_PORT = 530;
const port NETWALL_FOR_EMERGENY_BROADCASTS_PORT = 532;
const port COMMERCE_PORT = 542;
const port DHCPV6_CLIENT_PORT = 546;
const port DHCPV6_SERVER_PORT = 547;
const port NEW_RWHO_PORT = 550;
const port RTSP_PORT = 554;
const port RMONITOR_PORT = 560;
const port MONITOR_PORT = 561;
const port NNTPS_PORT = 563;
const port HTTP_RPC_EPMAP_PORT = 593;
const port ASF_RMCP_PORT = 623;
const port IPP_PORT = 631;
const port RLZ_DBASE_PORT = 635;
const port MSDP_PORT = 639;
const port SSNRC_CONTROL_PORT = 641;
const port SANITY_PORT = 643;
const port LDP_PORT = 646;
const port IEEE_MMS_PORT = 651;
const port SSNRC_DATA_PORT = 653;
const port TINC_PORT = 655;
const port IBM_RMC_PORT = 657;
const port DOOM_PORT = 666;
const port CORBA_IIOP_SSL_PORT = 684;
const port REALM_RUSD_PORT = 688;
const port VATP_PORT = 690;
const port LINUX_HA_PORT = 694;
const port OLSR_PORT = 698;
const port KERBEROS_ADMIN_PORT = 749;
const port KERBEROS_IV_PORT = 750;
const port RRH_PORT = 753;
const port TELL_SEND_PORT = 754;
const port MDBS_DAEMON_PORT = 800;
const port NETCONF_OVER_SSH_PORT = 830;
const port NETCONF_OVER_BEEP_PORT = 831;
const port NETCONF_FOR_SOAP_OVER_HTTPS_PORT = 832;
const port NETCONF_FOR_SOAP_OVER_BEEP_PORT = 833;
const port GDOI_PORT = 848;
const port DNS_OVER_QUIC_PORT = 853;
const port DNS_OVER_DTLS_PORT = 853;
const port OWAMP_CONTROL_PORT = 861;
const port TWAMP_CONTROL_PORT = 862;
const port FTPS_DATA_PORT = 989;
const port FTPS_CONTROL_PORT = 990;
const port NAS_PORT = 991;
const port TELNETS_PORT = 992;
const port POP3S_PORT = 995;
} // namespace UDP
} // namespace Port
/**
 * @namespace Http
 * @brief Contains constants related to HTTP protocol.
 * @details This namespace contains constants related to the Hypertext Transfer Protocol (HTTP), such as request
 * methods, response status codes, and header fields.
 * @version 1.0.0
 */
namespace Http
{
/**
 * @namespace Version
 * @brief Contains constants related to different versions of HTTP.
 * @details This namespace contains constants representing different versions of the Hypertext Transfer Protocol (HTTP),
 * such as HTTP/1.0, HTTP/1.1, HTTP/2.0, and HTTP/3.0.
 * @version 1.0.0
 */
namespace Version
{
const std::string HTTP_VERSION_1_0 = "HTTP/1.0";
const std::string HTTP_VERSION_1_1 = "HTTP/1.1";
const std::string HTTP_VERSION_2_0 = "HTTP/2.0";
const std::string HTTP_VERSION_3_0 = "HTTP/3.0";
} // namespace Version
/**
 * @namespace RequestMethod
 * @brief Contains constants representing different HTTP request methods.
 * @details This namespace contains constants representing different HTTP request methods, such as GET, POST, PUT,
 * DELETE, and more.
 * @version 1.0.0
 */
namespace RequestMethod
{
const std::string HTTP_GET = "GET";
const std::string HTTP_POST = "POST";
const std::string HTTP_PUT = "PUT";
const std::string HTTP_DELETE = "DELETE";
const std::string HTTP_CONNECT = "CONNECT";
const std::string HTTP_OPTIONS = "OPTIONS";
const std::string HTTP_TRACE = "TRACE";
const std::string HTTP_PATCH = "PATCH";
} // namespace RequestMethod
/**
 * @namespace RequestHeaderFields
 * @brief Contains constants for various request header fields.
 * @details This namespace provides constants for commonly used request header fields defined in various RFCs (Request
 * for Comments). Each constant represents a specific header field and its corresponding value. These constants can be
 * used to set or retrieve header field values in HTTP requests.
 * @version 1.0.0
 */
namespace RequestHeaderFields
{
namespace NonStandard
{
const std::string DNT = "DNT";
const std::string UPGRADE_INSECURE_REQUESTS = "Upgrade-Insecure-Requests";
} // namespace NonStandard
namespace RFC2965
{
const std::string COOKIE = "Cookie";
}
namespace RFC3229
{
const std::string A_IM = "A-IM";
}
namespace RFC6454
{
const std::string ORIGIN = "Origin";
}
namespace RFC7089
{
const std::string ACCEPT_DATETIME = "Accept-Datetime";
}
namespace RFC7239
{
const std::string FORWARDED = "Forwarded";
}
namespace RFC7240
{
const std::string PREFER = "Prefer";
}
namespace RFC9110
{
const std::string ACCEPT = "Accept";
const std::string ACCEPT_CHARSET = "Accept-Charset";
const std::string ACCEPT_ENCODING = "Accept-Encoding";
const std::string ACCEPT_LANGUAGE = "Accept-Language";
const std::string AUTHORIZATION = "Authorization";
const std::string CONNECTION = "Connection";
const std::string CONTENT_ENCODING = "Content-Encoding";
const std::string CONTENT_LENGTH = "Content-Length";
const std::string CONTENT_TYPE = "Content-Type";
const std::string DATE = "Date";
const std::string EXPECT = "Expect";
const std::string FROM = "From";
const std::string HOST = "Host";
const std::string IF_MATCH = "If-Match";
const std::string IF_MODIFIED_SINCE = "If-Modified-Since";
const std::string IF_NONE_MATCH = "If-None-Match";
const std::string IF_RANGE = "If-Range";
const std::string IF_UNMODIFIED_SINCE = "If-Unmodified-Since";
const std::string MAX_FORWARDS = "Max-Forwards";
const std::string PROXY_AUTHORIZATION = "Proxy-Authorization";
const std::string RANGE = "Range";
const std::string REFERER = "Referer";
const std::string TE = "TE";
const std::string TRAILER = "Trailer";
const std::string TRANSFER_ENCODING = "Transfer-Encoding";
const std::string USER_AGENT = "User-Agent";
const std::string UPGRADE = "Upgrade";
const std::string VIA = "Via";
} // namespace RFC9110
namespace RFC9111
{
const std::string CACHE_CONTROL = "Cache-Control";
const std::string PRAGMA = "Pragma";
} // namespace RFC9111
namespace FetchMetadataRequestHeaders
{
const std::string SEC_FETCH_SITE = "Sec-Fetch-Site";
const std::string SEC_FETCH_MODE = "Sec-Fetch-Mode";
const std::string SEC_FETCH_USER = "Sec-Fetch-User";
const std::string SEC_FETCH_DEST = "Sec-Fetch-Dest";
} // namespace FetchMetadataRequestHeaders
namespace UserAgentClientHints
{
const std::string SEC_CH_UA = "sec-ch-ua";
const std::string SEC_CH_UA_MOBILE = "sec-ch-ua-mobile";
const std::string SEC_CH_UA_FULL_VERSION_LIST = "sec-ch-ua-full-version-list";
const std::string SEC_CH_UA_PLATFORM = "sec-ch-ua-platform";
const std::string SEC_CH_UA_PLATFORM_VERSION = "sec-ch-ua-platform-version";
const std::string SEC_CH_UA_ARCH = "sec-ch-ua-arch";
const std::string SEC_CH_UA_MODEL = "sec-ch-ua-model";
const std::string SEC_CH_UA_BITNESS = "sec-ch-ua-bitness";
} // namespace UserAgentClientHints
} // namespace RequestHeaderFields
/**
 * @namespace ResponseHeaderFields
 * @brief Contains constants for various response header fields.
 * @details This namespace provides constants for commonly used response header fields defined in various RFCs (Request
 * for Comments). Each constant represents a specific header field and its corresponding value. These constants can be
 * used to set or retrieve header field values in HTTP responses.
 * @version 1.0.0
 */
namespace ResponseHeaderFields
{
namespace RFC3229
{
const std::string DELTA_BASE = "Delta-Base";
const std::string IM = "IM";
} // namespace RFC3229
namespace RFC4021
{
const std::string CONTENT_DISPOSITION = "Content-Disposition";
}
namespace RFC5789
{
const std::string ACCEPT_PATCH = "Accept-Patch";
}
namespace RFC5988
{
const std::string LINK = "Link";
}
namespace RFC6265
{
const std::string SET_COOKIE = "Set-Cookie";
}
namespace RFC7240
{
const std::string PREFERENCE_APPLIED = "Preference-Applied";
}
namespace RFC7469
{
const std::string PUBLIC_KEY_PINS = "Public-Key-Pins";
}
namespace RFC7480
{
const std::string ACCESS_CONTROL_ALLOW_ORIGIN = "Access-Control-Allow-Origin";
const std::string ACCESS_CONTROL_ALLOW_CREDENTIALS = "Access-Control-Allow-Credentials";
const std::string ACCESS_CONTROL_EXPOSE_HEADERS = "Access-Control-Expose-Headers";
const std::string ACCESS_CONTROL_MAX_AGE = "Access-Control-Max-Age: ";
const std::string ACCESS_CONTROL_ALLOW_METHODS = "Access-Control-Allow-Methods";
const std::string ACCESS_CONTROL_ALLOW_HEADERS = "Access-Control-Allow-Headers";
} // namespace RFC7480
namespace RFC8942
{
const std::string ACCEPT_CH = "Accept-CH";
}
namespace RFC9110
{
const std::string ACCEPT_RANGES = "Accept-Ranges";
const std::string ALLOW = "Allow";
const std::string CONNECTION = "Connection";
const std::string CONTENT_ENCODING = "Content-Encoding";
const std::string CONTENT_LANGUAGE = "Content-Language";
const std::string CONTENT_LENGTH = "Content-Length";
const std::string CONTENT_LOCATION = "Content-Location";
const std::string CONTENT_RANGE = "Content-Range";
const std::string CONTENT_TYPE = "Content-Type";
const std::string DATE = "Date";
const std::string ETAG = "ETag";
const std::string LAST_MODIFIED = "Last-Modified";
const std::string LOCATION = "Location";
const std::string PROXY_AUTHENTICATE = "Proxy-Authenticate";
const std::string RETRY_AFTER = "Retry-After";
const std::string SERVER = "Server";
const std::string TRAILER = "Trailer";
const std::string TRANSFER_ENCODING = "Transfer-Encoding";
const std::string UPGRADE = "Upgrade";
const std::string VARY = "Vary";
const std::string VIA = "Via";
const std::string WWW_AUTHENTICATE = "WWW-Authenticate";
} // namespace RFC9110
namespace RFC9111
{
const std::string AGE = "Age";
const std::string CACHE_CONTROL = "Cache-Control";
const std::string EXPIRES = "Expires";
const std::string PRAGMA = "Pragma";
} // namespace RFC9111
} // namespace ResponseHeaderFields
/**
 * @namespace ResponseStatus
 * @brief Contains constants representing HTTP response status codes.
 * @details This namespace provides a collection of constants that represent various HTTP response status codes. Each
 * constant is a string that corresponds to a specific status code. These constants can be used to set the status of an
 * HTTP response in a web application.
 * @version 1.0.0
 */
namespace ResponseStatus
{
const std::string HTTP_CONTINUE = "100 Continue";
const std::string HTTP_SWITCHING_PROTOCOLS = "101 Switching Protocols";
const std::string HTTP_PROCESSING = "102 Processing";
const std::string HTTP_EARLY_HINTS = "103 Early Hints";
const std::string HTTP_OK = "200 OK";
const std::string HTTP_CREATED = "201 Created";
const std::string HTTP_ACCEPTED = "202 Accepted";
const std::string HTTP_NON_AUTHORITATIVE_INFORMATION = "203 Non-Authoritative Information";
const std::string HTTP_NO_CONTENT = "204 No Content";
const std::string HTTP_RESET_CONTENT = "205 Reset Content";
const std::string HTTP_PARTIAL_CONTENT = "206 Partial Content";
const std::string HTTP_MULTI_STATUS = "207 Multi-Status";
const std::string HTTP_ALREADY_REPORTED = "208 Already Reported";
const std::string HTTP_IM_USED = "226 IM Used";
const std::string HTTP_MULTIPLE_CHOICES = "300 Multiple Choices";
const std::string HTTP_MOVED_PERMANENTLY = "301 Moved Permanently";
const std::string HTTP_FOUND = "302 Found";
const std::string HTTP_SEE_OTHER = "303 See Other";
const std::string HTTP_NOT_MODIFIED = "304 Not Modified";
const std::string HTTP_USE_PROXY = "305 Use Proxy";
const std::string HTTP_SWITCH_PROXY = "306 Switch Proxy";
const std::string HTTP_TEMPORARY_REDIRECT = "307 Temporary Redirect";
const std::string HTTP_PERMANENT_REDIRECT = "308 Permanent Redirect";
const std::string HTTP_BAD_REQUEST = "400 Bad Request";
const std::string HTTP_UNAUTHORIZED = "401 Unauthorized";
const std::string HTTP_PAYMENT_REQUIRED = "402 Payment Required";
const std::string HTTP_FORBIDDEN = "403 Forbidden";
const std::string HTTP_NOT_FOUND = "404 Not Found";
const std::string HTTP_METHOD_NOT_ALLOWED = "405 Method Not Allowed";
const std::string HTTP_NOT_ACCEPTABLE = "406 Not Acceptable";
const std::string HTTP_PROXY_AUTHENTICATION_REQUIRED = "407 Proxy Authentication Required";
const std::string HTTP_REQUEST_TIMEOUT = "408 Request Timeout";
const std::string HTTP_CONFLICT = "409 Conflict";
const std::string HTTP_GONE = "410 Gone";
const std::string HTTP_LENGTH_REQUIRED = "411 Length Required";
const std::string HTTP_PRECONDITION_FAILED = "412 Precondition Failed";
const std::string HTTP_PAYLOAD_TOO_LARGE = "413 Payload Too Large";
const std::string HTTP_URI_TOO_LONG = "414 URI Too Long";
const std::string HTTP_UNSUPPORTED_MEDIA_TYPE = "415 Unsupported Media Type";
const std::string HTTP_RANGE_NOT_SATISFIABLE = "416 Range Not Satisfiable";
const std::string HTTP_EXPECTATION_FAILED = "417 Expectation Failed";
const std::string HTTP_IM_A_TEAPOT = "418 I'm a teapot";
const std::string HTTP_MISDIRECTED_REQUEST = "421 Misdirected Request";
const std::string HTTP_UNPROCESSABLE_ENTITY = "422 Unprocessable Entity";
const std::string HTTP_LOCKED = "423 Locked";
const std::string HTTP_FAILED_DEPENDENCY = "424 Failed Dependency";
const std::string HTTP_TOO_EARLY = "425 Too Early";
const std::string HTTP_UPGRADE_REQUIRED = "426 Upgrade Required";
const std::string HTTP_PRECONDITION_REQUIRED = "428 Precondition Required";
const std::string HTTP_TOO_MANY_REQUESTS = "429 Too Many Requests";
const std::string HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE = "431 Request Header Fields Too Large";
const std::string HTTP_UNAVAILABLE_FOR_LEGAL_REASONS = "451 Unavailable For Legal Reasons";
const std::string HTTP_INTERNAL_SERVER_ERROR = "500 Internal Server Error";
const std::string HTTP_NOT_IMPLEMENTED = "501 Not Implemented";
const std::string HTTP_BAD_GATEWAY = "502 Bad Gateway";
const std::string HTTP_SERVICE_UNAVAILABLE = "503 Service Unavailable";
const std::string HTTP_GATEWAY_TIMEOUT = "504 Gateway Timeout";
const std::string HTTP_HTTP_VERSION_NOT_SUPPORTED = "505 HTTP Version Not Supported";
const std::string HTTP_VARIANT_ALSO_NEGOTIATES = "506 Variant Also Negotiates";
const std::string HTTP_INSUFFICIENT_STORAGE = "507 Insufficient Storage";
const std::string HTTP_LOOP_DETECTED = "508 Loop Detected";
const std::string HTTP_NOT_EXTENDED = "510 Not Extended";
const std::string HTTP_NETWORK_AUTHENTICATION_REQUIRED = "511 Network Authentication Required";
} // namespace ResponseStatus
/**
 * @brief Namespace containing constants for HTTP response status codes.
 * @details This namespace provides a collection of constants that represent various HTTP response status codes. Each
 * constant is an integer that corresponds to a specific status code. These constants can be used to set the status of
 * an HTTP response in a web application.
 * @version 1.0.0
 */
namespace ResponseStatusCodes
{
const int HTTP_CONTINUE = 100;
const int HTTP_SWITCHING_PROTOCOLS = 101;
const int HTTP_PROCESSING = 102;
const int HTTP_EARLY_HINTS = 103;
const int HTTP_OK = 200;
const int HTTP_CREATED = 201;
const int HTTP_ACCEPTED = 202;
const int HTTP_NON_AUTHORITATIVE_INFORMATION = 203;
const int HTTP_NO_CONTENT = 204;
const int HTTP_RESET_CONTENT = 205;
const int HTTP_PARTIAL_CONTENT = 206;
const int HTTP_MULTI_STATUS = 207;
const int HTTP_ALREADY_REPORTED = 208;
const int HTTP_IM_USED = 226;
const int HTTP_MULTIPLE_CHOICES = 300;
const int HTTP_MOVED_PERMANENTLY = 301;
const int HTTP_FOUND = 302;
const int HTTP_SEE_OTHER = 303;
const int HTTP_NOT_MODIFIED = 304;
const int HTTP_USE_PROXY = 305;
const int HTTP_SWITCH_PROXY = 306;
const int HTTP_TEMPORARY_REDIRECT = 307;
const int HTTP_PERMANENT_REDIRECT = 308;
const int HTTP_BAD_REQUEST = 400;
const int HTTP_UNAUTHORIZED = 401;
const int HTTP_PAYMENT_REQUIRED = 402;
const int HTTP_FORBIDDEN = 403;
const int HTTP_NOT_FOUND = 404;
const int HTTP_METHOD_NOT_ALLOWED = 405;
const int HTTP_NOT_ACCEPTABLE = 406;
const int HTTP_PROXY_AUTHENTICATION_REQUIRED = 407;
const int HTTP_REQUEST_TIMEOUT = 408;
const int HTTP_CONFLICT = 409;
const int HTTP_GONE = 410;
const int HTTP_LENGTH_REQUIRED = 411;
const int HTTP_PRECONDITION_FAILED = 412;
const int HTTP_PAYLOAD_TOO_LARGE = 413;
const int HTTP_URI_TOO_LONG = 414;
const int HTTP_UNSUPPORTED_MEDIA_TYPE = 415;
const int HTTP_RANGE_NOT_SATISFIABLE = 416;
const int HTTP_EXPECTATION_FAILED = 417;
const int HTTP_IM_A_TEAPOT = 418;
const int HTTP_MISDIRECTED_REQUEST = 421;
const int HTTP_UNPROCESSABLE_ENTITY = 422;
const int HTTP_LOCKED = 423;
const int HTTP_FAILED_DEPENDENCY = 424;
const int HTTP_TOO_EARLY = 425;
const int HTTP_UPGRADE_REQUIRED = 426;
const int HTTP_PRECONDITION_REQUIRED = 428;
const int HTTP_TOO_MANY_REQUESTS = 429;
const int HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE = 431;
const int HTTP_UNAVAILABLE_FOR_LEGAL_REASONS = 451;
const int HTTP_INTERNAL_SERVER_ERROR = 500;
const int HTTP_NOT_IMPLEMENTED = 501;
const int HTTP_BAD_GATEWAY = 502;
const int HTTP_SERVICE_UNAVAILABLE = 503;
const int HTTP_GATEWAY_TIMEOUT = 504;
const int HTTP_HTTP_VERSION_NOT_SUPPORTED = 505;
const int HTTP_VARIANT_ALSO_NEGOTIATES = 506;
const int HTTP_INSUFFICIENT_STORAGE = 507;
const int HTTP_LOOP_DETECTED = 508;
const int HTTP_NOT_EXTENDED = 510;
const int HTTP_NETWORK_AUTHENTICATION_REQUIRED = 511;

} // namespace ResponseStatusCodes
const std::string HTTP_INDEX_URI = "/";
const std::string EMPTY_DATA = "";
} // namespace Http
} // namespace FBNetwork

#endif