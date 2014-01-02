#include "soar_predefine.h"
#include "soar_error_code.h"

BEGINDEFSTRTABLE(SOAR_RET)
DEFIDTOSTRING(FAIL_INTERNAL_ERORR                   , "Internal system error.")
DEFIDTOSTRING(SOAR_RET_SUCC                          , "Success .")

// framework
DEFIDTOSTRING(ERROR_COMMLIB_BEGIN                   , "")
DEFIDTOSTRING(ERROR_PROCESS_C4ACACHE                , "Commlib: ERROR_PROCESS_C4ACACHE.")
DEFIDTOSTRING(ERROR_PROCESS_MYSQLDB                 , "Commlib: ERROR_PROCESS_MYSQLDB.")
DEFIDTOSTRING(ERROR_PROCESS_SQLITE                  , "Commlib: ERROR_PROCESS_SQLITE.");
DEFIDTOSTRING(ERROR_INIT_RECEIVE_PIPE               , "Commlib: Create Receive Pipe Error.")
DEFIDTOSTRING(ERROR_INIT_SEND_PIPE                  , "Commlib: Create Send Pipe Error.")
DEFIDTOSTRING(ERROR_INIT_ERROR_PIPE                 , "Commlib: Create Error Pipe Error.")
DEFIDTOSTRING(ERROR_PIPE_IS_FULL                    , "Commlib: Pipe is full.")
DEFIDTOSTRING(ERROR_PIPE_IS_EMPTY                   , "Commlib: Pipe is empty.")
DEFIDTOSTRING(ERROR_GET_CFGFILE_CONFIG_FAIL         , "Commlib: Get Config file configure error.")
DEFIDTOSTRING(ERROR_GET_AUTO_CONN_CONFIG_FAIL       , "Commlib: Get Auto Connect config error.")
DEFIDTOSTRING(ERROR_NO_FOUND_DATA_FROM_DB           , "Commlib: Not found any data from db.")
DEFIDTOSTRING(ERROR_MMAP_MALLOC_FAIL                , "Commlib: MMAP malloc fail.")
DEFIDTOSTRING(ERROR_FIND_REPEAT_CMD_ID              , "Commlib: Transaction Manager Find repeat command id.")
DEFIDTOSTRING(ERROR_FIND_REPEAT_TRANSACTION_ID      , "Commlib: Find Repeat Transaction ID.")
DEFIDTOSTRING(ERROR_CANNOT_FIND_TRANSACTION_ID      , "Commlib: Can't Find Transaction ID.")
DEFIDTOSTRING(ERROR_APPFRAME_BUFFER_SHORT           , "Commlib: APPFRAME buffer too short.")
DEFIDTOSTRING(ERROR_CDR_ENCODE_FAIL                 , "Commlib: CDR encode fail.")
DEFIDTOSTRING(ERROR_CDR_DECODE_FAIL                 , "Commlib: CDR decode fail.")
DEFIDTOSTRING(ERROR_INVALID_DATA_ID                 , "Commlib: Invalid data id.")
DEFIDTOSTRING(ERROR_SERVICES_INFO_CONFIG            , "Commlib: Can't find Services info.")
DEFIDTOSTRING(ERROR_MML_ERROR                       , "Commlib: MML error.")
DEFIDTOSTRING(ERROR_MML_STRING_PARSE_FAIL           , "Commlib: Parse MML String fail.")
DEFIDTOSTRING(ERROR_CONSOLE_IS_CLOSED               , "Commlib: Console is closed.")
DEFIDTOSTRING(ERROR_CONSOLE_START_FAIL              , "Commlib: Console start fail.")
DEFIDTOSTRING(ERROR_EVENT_NOTIFY_FAIL               , "Commlib: Event notify fail.")
DEFIDTOSTRING(ERROR_EVENT_PROCESS_FAIL              , "Commlib: Event Process fail.")
DEFIDTOSTRING(ERROR_FRAME_DATA_IS_ERROR             , "Commlib: Frame Data is error.")
DEFIDTOSTRING(ERROR_QQUIN_INCERTITUDE               , "Commlib: QQUin incertitude.")
DEFIDTOSTRING(ERROR_FRAME_NOT_TAIL_IPINFO           , "Commlib: Appframe don't have ip info.")
DEFIDTOSTRING(ERROR_APPFRAME_ERROR                  , "Commlib: Appframe error.")
DEFIDTOSTRING(ERROR_APPFRAME_ENCRYPT_DECRYPT        , "Commlib: Appframe encrypt or decrypt error.")
DEFIDTOSTRING(ERROR_OCCUR_EXCEPTION                 , "Commlib: ERROR_OCCUR_EXCEPTION.")
DEFIDTOSTRING(ERROR_FORK_FAIL                       , "Commlib: ERROR_FORK_FAIL")
DEFIDTOSTRING(ERROR_STARTUP_TIP                     , "Commlib: ERROR_STARTUP_TIP")
DEFIDTOSTRING(ERROR_GET_STARTUP_CONFIG_FAIL         , "Commlib: ERROR_GET_STARTUP_CONFIG_FAIL")
DEFIDTOSTRING(ERROR_WRITE_ERROR_PIDFILE             , "Commlib: ERROR_WRITE_ERROR_PIDFILE")
DEFIDTOSTRING(ERROR_INIT_TIMER_QUEUE                , "Commlib: ERROR_INIT_TIMER_QUEUE")
DEFIDTOSTRING(ERROR_NOT_FIND_SERVICES_INFO          , "Commlib: ERROR_NOT_FIND_SERVICES_INFO")
DEFIDTOSTRING(ERROR_INIT_DB_CONFIG                  , "Commlib: ERROR_INIT_DB_CONFIG")
DEFIDTOSTRING(ERROR_GET_CONFIG_FROM_DB              , "Commlib: ERROR_CET_CONFIG_FROM_DB")
DEFIDTOSTRING(ERROR_WRITE_PID_FILE_FAIL             , "Commlib: ERROR_WRITE_PID_FILE_FAIL")
DEFIDTOSTRING(ERROR_DIR_REPORT_INIT_ERROR           , "Commlib: ERROR_DIR_REPORT_INIT_ERROR")
DEFIDTOSTRING(ERROR_NOT_FIND_FUNC                   , "Commlib: ERROR_NOT_FIND_FUNC")
DEFIDTOSTRING(ERROR_RECORD_LOG_FAIL_BUFFER_LACK     , "Commlib: ERROR_RECORD_LOG_FAIL_BUFFER_LACK")
DEFIDTOSTRING(ERROR_NAVIGATION_TREE_XML_ERROR       , "Commlib: ERROR_NAVIGATION_TREE_XML_ERROR")
DEFIDTOSTRING(ERROR_NAVIGATION_TREE_PARSE_FAIL      , "Commlib: ERROR_NAVIGATION_TREE_PARSE_FAIL")
DEFIDTOSTRING(ERROR_NOT_FIND_NAVTREE_NODE           , "Commlib: ERROR_NOT_FIND_NAVTREE_NODE")
DEFIDTOSTRING(ERROR_APPFRAME_SESSION                , "Commlib: Appframe is session frame")
DEFIDTOSTRING(ERROR_DIRTY_KEYWORD                   , "Commlib: ERROR_DIRTY_KEYWORD")
DEFIDTOSTRING(ERROR_MMAP_CACHE_ERROR                , "Commlib: ERROR_MMAP_CACHE_ERROR")
DEFIDTOSTRING(ERROR_REPEAT_PROCESS_START            , "Commlib: ERROR_REPEAT_PROCESS_START")
DEFIDTOSTRING(ERROR_PROCESS_MUTEX_ERROR             , "Commlib: ERROR_PROCESS_MUTEX_ERROR")
DEFIDTOSTRING(ERROR_NAVTREE_XML_FILE_FAIL           , "Commlib:ERROR_NAVTREE_XML_FILE_FAIL")
DEFIDTOSTRING(ERROR_INVALID_QQ_NUMBER               , "Commlib:ERROR_INVALID_QQ_NUMBER")
DEFIDTOSTRING(ERROR_INVALID_SOARING_LIB_TYPE         , "Commlib:ERROR_INVALID_SOARING_LIB_TYPE")
DEFIDTOSTRING(ERROR_INVALID_INTERNAL_IPADDRESS      , "Commlib:ERROR_INVALID_INTERNAL_IPADDRESS")
DEFIDTOSTRING(ERROR_MML_CONSOLE_FAIL                , "ERROR_MML_CONSOLE_FAIL")
DEFIDTOSTRING(ERROR_LOAD_DLL_OR_SO_FAIL             , "ERROR_LOAD_DLL_OR_SO_FAIL")
DEFIDTOSTRING(ERROR_APPFRAME_SESSION_EXPIRE         , "ERROR_APPFRAME_SESSION_EXPIRE")
DEFIDTOSTRING(ERROR_OGRE_FRAME_ERROR                , "ERROR_OGRE_FRAME_ERROR")
DEFIDTOSTRING(ERROR_TRANS_NO_CLONE_COMMAND          , "ERROR_TRANS_NO_CLONE_COMMAND")
DEFIDTOSTRING(ERROR_TRANS_HAS_FINISHED              , "ERROR_TRANS_HAS_FINISHED")
DEFIDTOSTRING(ERROR_NOTIFY_SEND_QUEUE_DEQUEUE_FAIL  , "ERROR_NOTIFY_SEND_QUEUE_DEQUEUE_FAIL")
DEFIDTOSTRING(ERROR_NOTIFY_RECV_QUEUE_DEQUEUE_FAIL  , "ERROR_NOTIFY_RECV_QUEUE_DEQUEUE_FAIL")
DEFIDTOSTRING(ERROR_NOTIFY_SEND_QUEUE_ENQUEUE_FAIL  , "ERROR_NOTIFY_SEND_QUEUE_ENQUEUE_FAIL")
DEFIDTOSTRING(ERROR_NOTIFY_RECV_QUEUE_ENQUEUE_FAIL  , "ERROR_NOTIFY_RECV_QUEUE_ENQUEUE_FAIL")
DEFIDTOSTRING(ERROR_ZULU_INPUT_IPADDRESS_ERROR      , "ERROR_ZULU_INPUT_IPADDRESS_ERROR")
DEFIDTOSTRING(ERROR_ZULU_CONNECT_SERVER_FAIL        , "ERROR_ZULU_CONNECT_SERVER_FAIL")
DEFIDTOSTRING(ERROR_ZULU_SEND_PACKAGE_FAIL          , "ERROR_ZULU_SEND_PACKAGE_FAIL")
DEFIDTOSTRING(ERROR_ZULU_RECEIVE_PACKAGE_FAIL       , "ERROR_ZULU_RECEIVE_PACKAGE_FAIL")
DEFIDTOSTRING(ERROR_ZULU_RECEIVE_OTHERS_COMMAND     , "ERROR_ZULU_RECEIVE_OTHERS_COMMAND")
DEFIDTOSTRING(ERROR_MML_COMMAND_INVALID             , "ERROR_MML_COMMAND_INVALID")
DEFIDTOSTRING(ERROR_LOTTERY_RATIO_TOTAL             , "ERROR_LOTTERY_RATIO_TOTAL")
DEFIDTOSTRING(ERROR_TRANSACTION_NEED_CMD_ERROR      , "ERROR_TRANSACTION_NEED_CMD_ERROR")
DEFIDTOSTRING(ERROR_SQLITE3_SQL_SYNTAX_ERROR        , "ERROR_SQLITE3_SQL_SYNTAX_ERROR")
DEFIDTOSTRING(ERROR_SQLITE3_OPEN_DATABASE           , "ERROR_SQLITE3_OPEN_DATABASE")
DEFIDTOSTRING(ERROR_BOOL_EXPRESSION_ERROR           , "ERROR_BOOL_EXPRESSION_ERROR")
DEFIDTOSTRING(ERROR_BOOL_EXPRESSION_HAVE_ERR_CHAR   , "ERROR_BOOL_EXPRESSION_HAVE_ERR_CHAR")
DEFIDTOSTRING(ERROR_TASKID_PHASEID_NOT_MATCHING     , "ERROR_TASKID_PHASEID_NOT_MATCHING")
DEFIDTOSTRING(ERROR_SINGLE_SELECT_USER_INPUT_ERROR  , "ERROR_SINGLE_SELECT_USER_INPUT_ERROR")
DEFIDTOSTRING(ERROR_TASK_ID_EQUAL_ZERO              , "ERROR_TASK_ID_EQUAL_ZERO")
DEFIDTOSTRING(ERROR_CHECK_CONDITION_ERROR           , "ERROR_CHECK_CONDITION_ERROR")
DEFIDTOSTRING(ERROR_GETTASK_CONDITION_RRROR         , "ERROR_GETTASK_CONDITION_RRROR")
DEFIDTOSTRING(ERROR_ILLUSION_STRING_TO_ID_FAIL      , "ERROR_ILLUSION_STRING_TO_ID_FAIL")
DEFIDTOSTRING(ERROR_ILLUSION_CFG_COULD_HAVE_MODIFY  , "ERROR_ILLUSION_CFG_COULD_HAVE_MODIFY")
DEFIDTOSTRING(ERROR_ILLUSION_EXCEL_FILE_ERROR       , "ERROR_ILLUSION_EXCEL_FILE_ERROR")
DEFIDTOSTRING(ERROR_ZULU_LINK_DISCONNECT            , "ERROR_ZULU_LINK_DISCONNECT")
DEFIDTOSTRING(ERROR_LOLO_SEND_RECV_CONN_NOT_SAME    , "ERROR_LOLO_SEND_RECV_CONN_NOT_SAME")
DEFIDTOSTRING(ERROR_COMMLIB_END                     , "")

// proxy
DEFIDTOSTRING(ERR_PROXY_BEGIN                       , "")
DEFIDTOSTRING(ERR_PROXY_APPFRAME_CMD_ERROR          , "ERR_PROXY_APPFRAME_CMD_ERROR")
DEFIDTOSTRING(ERR_PROXY_SEND_PIPE_IS_FULL           , "ERR_PROXY_SEND_PIPE_IS_FULL")
DEFIDTOSTRING(ERR_PROXY_RECEIVE_ERROR_FRAME         , "ERR_PROXY_RECEIVE_ERROR_FRAME")
DEFIDTOSTRING(ERR_PROXY_END                         , "")

// zergsvr
DEFIDTOSTRING(ERR_ZERG_FAIL_SOCKET_OP_ERROR         , "Socket return a error.")
DEFIDTOSTRING(ERR_ZERG_GREATER_MAX_LEN_FRAME        , "Appframe length is greater than max length.")
DEFIDTOSTRING(ERR_ZERG_GREATER_DEFINE_LEN_FRAME     , "Appframe length is greater than define length.")
DEFIDTOSTRING(ERR_ZERG_SOCKET_CLOSE                 , "Socket is closed")
DEFIDTOSTRING(ERR_ZERG_SERVER_ALREADY_LONGIN        , "Services already login in this server.")
DEFIDTOSTRING(ERR_ZERG_CONNECT_NO_FIND_SVCINFO      , "Connect not Find this services info.")
DEFIDTOSTRING(ERR_ZERG_INIT_RECEIVE_PIPE            , "Create Receive Pipe Error.")
DEFIDTOSTRING(ERR_ZERG_INIT_SEND_PIPE               , "Create Send Pipe Error.")
DEFIDTOSTRING(ERR_ZERG_INIT_ERR_ZERG_PIPE           , "Create Error Pipe Error.")
DEFIDTOSTRING(ERR_ZERG_NO_FIND_EVENT_HANDLE         , "Not Find Handle with services info.")
DEFIDTOSTRING(ERR_ZERG_RECEIVE_PIPE_IS_FULL         , "Recveive Pipe full.")
DEFIDTOSTRING(ERR_ZERG_SEND_PIPE_IS_FULL            , "Send Pipe full.")
DEFIDTOSTRING(ERR_ZERG_ERROR_PIPE_IS_FULL           , "Error Pipe full.")
DEFIDTOSTRING(ERR_ZERG_GREAT_THAN_ERROR_TRY         , "Up to Max error try send.")
DEFIDTOSTRING(ERR_ZERG_MMAP_MALLOC_FAIL             , "Alloc MMAP memory Fail.")
DEFIDTOSTRING(ERR_ZERG_INIT_ACCEPT_SOCKET_FAIL      , "Init Accept Socket Fail.")
DEFIDTOSTRING(ERR_ZERG_GET_STARTUP_CONFIG_FAIL      , "Get Startup Config Fail.")
DEFIDTOSTRING(ERR_ZERG_GET_CFGFILE_CONFIG_FAIL      , "Get Config file configure error.")
DEFIDTOSTRING(ERR_ZERG_GET_AUTO_CONN_CONFIG_FAIL    , "Get Auto Connect config error.")
DEFIDTOSTRING(ERR_ZERG_OCCUR_EXCEPTION              , "Occur exception.")
DEFIDTOSTRING(ERR_ZERG_APPFRAME_ERROR               , "Appframe error.")
DEFIDTOSTRING(ERR_ZERG_INIT_LISTEN_PORT_FAIL        , "Init Accept Socket Peer fail.")
DEFIDTOSTRING(ERR_ZERG_UNSAFE_PORT_WARN             , "Unsafe port,if you need to open this port,please close insurance.")
DEFIDTOSTRING(ERR_ZERG_INIT_UPD_PORT_FAIL           , "Init UDP Port fail.")
DEFIDTOSTRING(ERR_ZERG_IP_RESTRICT_CHECK_FAIL       , "IP Restrict check fail")
DEFIDTOSTRING(ERR_ZERG_UDPSESSION_NOFOUND           , "ERR_ZERG_UDPSESSION_NOFOUND")
DEFIDTOSTRING(ERR_ZERG_UDPSESSION_FULL              , "ERR_ZERG_UDPSESSION_FULL")
DEFIDTOSTRING(ERR_ZERG_LOAD_OPERATION_KEY_FAIL      , "ERR_ZERG_LOAD_OPERATION_KEY_FAIL")

// end
ENDDEFSTRTABLE

