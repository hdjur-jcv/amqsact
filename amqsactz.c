/* @(#) MQMBID sn=p750-003-140123 su=_v82gEIRJEeOSfofehNkeyQ pn=samples/c/amqsact0.c */
/********************************************************************/
/*                                                                  */
/* Program name: amqsact                                            */
/*                                                                  */
/* Description: Sample C program that gets an activity trace        */
/*              from the standard queue and writes the formatted    */
/*              data to standard output.                            */
/*                                                                  */
/*   <copyright                                                     */
/*   notice="lm-source-program"                                     */
/*   pids="5724-H72,"                                               */
/*   years="1994,2012"                                              */
/*   crc="1563970721" >                                             */
/*  Licensed Materials - Property of IBM                            */
/*                                                                  */
/*  5724-H72,                                                       */
/*                                                                  */
/*  (C) Copyright IBM Corp. 1994, 2012 All Rights Reserved.         */
/*                                                                  */
/*  US Government Users Restricted Rights - Use, duplication or     */
/*  disclosure restricted by GSA ADP Schedule Contract with         */
/*  IBM Corp.                                                       */
/*   </copyright>                                                   */
/********************************************************************/
/*                                                                  */
/* Function:                                                        */
/*                                                                  */
/*                                                                  */
/*   amqsact is a sample C program to retrieve application          */
/*   activity trace messages and write the formatted contents of    */
/*   the message to the screen. The source of the data can be       */
/*   changed from the default of SYSTEM.ADMIN.TRACE.ACTIVITY.QUEUE  */
/*   for example if the queue has been redefined as a QALIAS that   */
/*   targets another queue or topic. The -q and -t parameters give  */
/*   flexibility in where the messages are consumed from.           */
/*                                                                  */
/*      -- sample reads from SYSTEM.ADMIN.TRACE.ACTIVITY.QUEUE      */
/*      OR                                                          */
/*         reads from named queue (-q)                              */
/*      OR                                                          */
/*         creates managed non-durable subscription to a named      */
/*         topic (-t)                                               */
/*                                                                  */
/*      -- displays the contents of the message to the screen       */
/*                                                                  */
/*      -- Details of any failures are written to the screen        */
/*                                                                  */
/*      -- Program ends, returning a return code of                 */
/*           zero if a message was processed                        */
/*             1   if no messages were available to process         */
/*            -1   if any other error occurred                      */
/*                                                                  */
/********************************************************************/
/*                                                                  */
/*   amqsact has the following parameters                           */
/*                                                                  */
/*   amqsact   [-m QMgrName]                                        */
/*             [-q QName]        # Override default queue name      */
/*             [-t TopicString]  # Subscribe to event topic         */
/*             [-b]              # Only browse records              */
/*             [-c CCSID]        # CCSID to use on GET              */
/*             [-v]              # Verbose output                   */
/*             [-d <depth>]      # Number of records to display     */
/*             [-w <timeout>]    # Time to wait (in seconds)        */
/*             [-s <startTime>]  # Start time of record to process  */
/*             [-e <endTime>]    # End time of record to process    */
/*             [-f <APIFields1>] # Fields to display for API line   */ 
/*             [-g <APIFields2>] # More APID fields for API line    */
/*             [-r]              # Create summary reports for non-  */
/*                                 verbose run                      */ 
/*                                                                  */
/*   -f is a numeric value to represent what fields to show in      */
/*   the API summary line. Add the values below to get the fields   */
/*   to list (i.e. -f 7 would list Pid, Tid, CnId).                 */
/*                                                                  */
/*   To display all fields below a certain field (largest field     */
/*   inclusive), multiply the largest field by 2 and subtract 1.    */
/*   ex. (2048 x 2) - 1 = 4095 to see all fields from Pid - Appl    */
/*                                                                  */ 
/*   The default value is 1023 (the first 10 fields in the list).   */
/*                                                                  */ 
/*   Value        Short Name   Long Name                            */
/*   ==========   ==========   =========                            */
/*            1   Pid          Pid                                  */
/*            2   Tid          Tid                                  */
/*            4   CnId         Connection Id                        */
/*            8   Chl          Channel Name                         */
/*           16   Date         Date                                 */
/*           32   Time         Time                                 */
/*           64   Opr          API Operation                        */
/*          128   RC           Reason Code                          */
/*          256   HObj         Object Handle                        */
/*          512   Obj          Object Name                          */
/*         1024   Qmgr         Queue Manager Name                   */
/*         2048   Appl         Application Name                     */ 
/*         4096   User         User Id                              */
/*         8192   MgId         Message Id                           */
/*        16384   CrId         Correlation Id                       */ 
/*        32768   OQNm         Object Queue Manager Name            */
/*        65536   RQNm         Resolved Queue Name                  */
/*       131072   RQMN         Resolved Queue Manager Name          */
/*       262144   RLQN         Resolved Local Queue Name            */
/*       524288   RLQM         Resolved Local Queue Manager Name    */
/*      1048576   RToQ         Reply To Queue                       */
/*      2097152   RTQM         Reply To Queue Manager               */
/*      4194304   Prty         Priority                             */
/*      8388608   Prst         Persistence                          */
/*     16777216   Rprt         Report Options                       */
/*     33554432   Expr         Expiry                               */
/*     67108864   MsgL         Message Length                       */ 
/*    134217728   CCSI         Coded Character Set Id               */
/*    268435456   Encd         Encoding                             */ 
/*    536870912   MDAB         Message Data As Bytes                */ 
/*                                                                  */
/*   -g is a numeric value to represent what fields to show in      */
/*   the API summary line. Add the values below to get the fields   */
/*   to list (i.e. -g 7 would list CnOp, OpOp, GtOp).               */
/*                                                                  */
/*   To display all fields below a certain field (largest field     */
/*   inclusive), multiply the largest field by 2 and subtract 1.    */
/*   ex. (128 x 2) - 1 = 255 to see all fields from CnOp - SROp     */
/*                                                                  */
/*   The default value is 0 (no fields).                            */
/*                                                                  */
/*   Value        Short Name   Long Name                            */
/*   ==========   ==========   =========                            */
/*            1   CnOp         Connection Options                   */
/*            2   OpOp         Open Options                         */
/*            4   GtOp         Get Options                          */
/*            8   PtOp         Put Options                          */
/*           16   ClOp         Close Options                        */
/*           32   CbOp         Callback Options                     */
/*           64   SbOp         Subscription Options                 */
/*          128   SROp         Subscription Request options         */
/*                                                                  */
/*   -r summary reports includes the following helpful reports:     */
/*   Application Summary Report                                     */
/*   Application Objects Referenced Report                          */
/*   Application Objects Detail Report                              */
/*   Application Channels Referenced Report                         */
/*   Application Operations Executed Report                         */
/*   Application Operations Options Report                          */
/*   Application Operations Reason Code Report                      */ 
/*                                                                  */
/*   Modifications by Tim Zielke (CICS/MQ SYSPROG - Aon):           */
/*   - Include RecordNum in MQI Operation title line                */
/*   - Enhance TerseTraceLine to include 1LS= eye catcher,          */
/*     RecordNum, pid, conname, channel name.                       */
/*   - Include ObjName in TerseTraceLine when PUT1                  */  
/*   - Correct printf of char in printMonByteString where unsigned  */
/*     char with high bit of 1 had a FFFFFFxx format.               */ 
/*   - -r option for summary reports                                */
/*   - -f,-g options for customizing fields on API one line summary */
/*                                                                  */
/*   amqsactz server build examples:                                */ 
/*   Linux x86 build example when MQ install path is /opt/mqm:      */
/*   gcc -m64  -o amqsactz amqsactz.c -I/opt/mqm/inc -L/opt/mqm/lib64  */ 
/*   -Wl,-rpath=/opt/mqm/lib64 -Wl,-rpath=/usr/lib64 -lmqm_r -lpthread */ 
/*                                                                     */
/*   Solaris SPARC build example with MQ install path of /opt/mqm:     */
/*   gcc -m64 -o amqsactz amqsactz.c -I/opt/mqm/inc -L/opt/mqm/lib64   */ 
/*   -R/opt/mqm/lib64 -R/usr/lib/64 -lmqm -lsocket -lnsl -ldl          */ 
/*                                                                  */
/*   Windows Visual Studio build example when MQ install path is    */
/*   "c:\Program Files\IBM\WebSphere MQ":                           */ 
/*   cl -MD amqsactz.c -Famqsactz_win.exe                           */ 
/*    "c:\Program Files\IBM\WebSphere MQ\tools\Lib\mqm.Lib"         */
/*                                                                  */
/*   Example of how to use amqsactz on Linux:                       */
/*   1. amqsactz -r -b > amqsactz.out                               */
/*   2. grep 1LS= amqsactz.out > amqsactz_1LS.out                   */
/*   3. amqsactz -v -b > amqsactz_v.out                             */
/*                                                                  */
/*   Step 1 will create summary output of each activity trace       */
/*   record, followed by several helpful summary reports (via -r).  */
/*                                                                  */
/*   Step 2 will produce a one line summary report of all of the    */
/*   API calls. For information on what each column represents,     */
/*   look back in the amqsactz.out at a 1LS= reference.             */
/*                                                                  */
/*   Step 3 will produce a verbose report for each activity trace   */
/*   record.  The RecordNum that appears in the first two reports   */
/*   can be used for quickly indexing into the verbose report.      */ 
/********************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* includes for MQI  */
#include <cmqc.h>
#include <cmqcfc.h>
#include <cmqxc.h>

/********************************************************************/
/* Define constants used by this program                            */
/********************************************************************/
#if !defined(FALSE)
  #define FALSE 0
#endif

#if !defined(TRUE)
  #define TRUE (!FALSE)
#endif

MQLONG printHeader = FALSE;


/********************************************************************/
/* Global fields for collecting AAT data for summary reports        */
/********************************************************************/
MQLONG Report = FALSE;
MQLONG APIFields1 = 1023;
MQLONG APIFields2 = 0;
MQLONG CodedCharSetId = MQCCSI_Q_MGR; 

typedef struct PidTracker {
   void *prevItem;
   void *nextItem;
   MQLONG pid;
   MQLONG MQICt;
   MQCHAR QmgrName[MQ_Q_MGR_NAME_LENGTH+1];
   MQCHAR ApplicationName[MQ_APPL_NAME_LENGTH+1];
   MQCHAR UserId[MQ_USER_ID_LENGTH+1];
   void *ObjTrackerHead;
   void *ObjTrackerCurr;
   void *ChlTrackerHead;
   void *ChlTrackerCurr;
   void *OprTrackerHead;
   void *OprTrackerCurr;
   void *TidTrackerHead;
   void *TidTrackerCurr;

} PidTrackerItem;

PidTrackerItem *PidTrackerHead=NULL;
PidTrackerItem *PidTrackerCurr=NULL;

typedef struct ObjTracker {
   void *prevItem;
   void *nextItem;
   MQCHAR ObjName[MQ_OBJECT_NAME_LENGTH+1];
   MQLONG ObjCt;
   void *OptTrackerHead;
   void *OptTrackerCurr;
   void *OprTrackerHead;
   void *OprTrackerCurr;
} ObjTrackerItem;

ObjTrackerItem *ObjTrackerHead=NULL;
ObjTrackerItem *ObjTrackerCurr=NULL;


typedef struct OptTracker {
   void *prevItem;
   void *nextItem;
   MQLONG OptType;
   MQLONG Opt;
   MQLONG OptCt;
} OptTrackerItem;

OptTrackerItem *OptTrackerHead=NULL;
OptTrackerItem *OptTrackerCurr=NULL;

typedef struct ReasonTracker {
   void *prevItem;
   void *nextItem;
   MQLONG Reason;
   MQLONG ReasonCt;
} ReasonTrackerItem;

ReasonTrackerItem *ReasonTrackerHead=NULL;
ReasonTrackerItem *ReasonTrackerCurr=NULL;

typedef struct ChlTracker {
   void *prevItem;
   void *nextItem;
   MQCHAR ChannelName[MQ_CHANNEL_NAME_LENGTH+1];
   MQLONG ChlCt;
} ChlTrackerItem;

ChlTrackerItem *ChlTrackerHead=NULL;
ChlTrackerItem *ChlTrackerCurr=NULL;

typedef struct OprTracker {
   void *prevItem;
   void *nextItem;
   MQCHAR Operation[16];
   MQLONG OprCt;
   MQLONG NonPrstCt;
   MQLONG NonPrstMsgLgth;
   MQLONG PrstCt;
   MQLONG PrstMsgLgth;
   MQLONG DfltPrstCt;
   MQLONG DfltPrstMsgLgth;
   MQLONG NAPrstCt;
   MQLONG NAPrstMsgLgth;
   void *OptTrackerHead;
   void *OptTrackerCurr;
   void *ReasonTrackerHead;
   void *ReasonTrackerCurr;
} OprTrackerItem;

OprTrackerItem *OprTrackerHead=NULL;
OprTrackerItem *OprTrackerCurr=NULL;
OprTrackerItem *OprTrackerHoldHead=NULL;
OprTrackerItem *OprTrackerHoldCurr=NULL;

typedef struct TidTracker {
   void *prevItem;
   void *nextItem;
   MQLONG tid;
} TidTrackerItem;

TidTrackerItem *TidTrackerHead=NULL;
TidTrackerItem *TidTrackerCurr=NULL;


/********************************************************************/
/* Private Function prototypes                                      */
/********************************************************************/
static int ParseOptions(int     argc,
                        char    *argv[],
                        char    qmgrName[MQ_Q_MGR_NAME_LENGTH],
                        char    **ppqname,
                        char    **pptopicstr,
                        MQLONG  *pbrowse,
                        MQLONG  *pCodedCharSetId,
                        MQLONG  *pVerbose,
                        MQLONG  *pmaximumRecords,
                        MQLONG  *pwaitTime,
                        time_t  *pstartTime,
                        time_t  *pendTime,
                        MQLONG  *pAPIFields1,
                        MQLONG  *pAPIFields2,
                        MQLONG  *pReport);

int getPCFDateTimeFromMsg(MQBYTE *buffer,
                          MQLONG parmCount,
                          MQLONG dateParameter,
                          MQLONG timeParameter,
                          MQCHAR dateString[MQ_DATE_LENGTH+1],
                          MQCHAR timeString[MQ_DATE_LENGTH+1]);

int printMonitoring(MQMD   *pmd,
                    MQBYTE *buffer,
                    MQLONG buflen,
                    MQLONG Verbose,
                    MQLONG RecordNum);

int printMonitoringRecord(MQLONG parameterCount,
                          MQLONG indentCount,
                          MQBYTE **ppbuffer,
                          MQLONG *pbuflen,
                          MQLONG Verbose,
                          MQLONG RecordNum,
                          MQCHAR *conn);

int skipMonitoringRecord(MQLONG parameterCount,
                         MQBYTE **ppbuffer,
                         MQLONG *pbuflen);

char * getMonInteger(MQLONG _parm, 
                     MQLONG _value, 
                     MQCHAR *buffer, 
                     MQLONG buflen);

int printTerseTraceLine(MQLONG parameterCount,
                        MQLONG indentCount,
                        MQBYTE **ppbuffer,
                        MQLONG *pbuflen,
                        MQLONG pid,
                        MQLONG RecordNum,
                        MQCHAR *QmgrName,
                        MQCHAR *ChannelName,
                        MQCHAR *ApplicationName,
                        MQCHAR *UserId,
                        MQCHAR *conn);

int addPidTracker(MQLONG pid,
                  char *QmgrName,
                  char *ApplicationName,
                  char *UserId,
                  MQLONG MQICt);


int crtPidTracker(MQLONG pid,
                  char *QmgrName,
                  char *ApplicationName,
                  char *UserId,
                  MQLONG MQICt);

int addObjTracker(char *ObjName,
                  MQLONG ObjCt); 

int crtObjTracker(char *ObjName,
                  MQLONG ObjCt);

int addOptTracker(MQLONG OptType,
                  MQLONG Opt,
                  MQLONG OptCt);

int crtOptTracker(MQLONG OptType,
                  MQLONG Opt,
                  MQLONG OptCt);

int addReasonTracker(MQLONG Reason,
                     MQLONG ReasonCt);

int crtReasonTracker(MQLONG Reason,
                     MQLONG ReasonCt);

int addChlTracker(char *ChannelName,
                  MQLONG ChlCt);

int crtChlTracker(char *ChannelName,
                  MQLONG ChlCt);

int addOprTracker(char *Operation,
                  MQLONG OprCt,
                  MQLONG NonPrstCt,
                  MQLONG NonPrstMsgLgth,
                  MQLONG PrstCt,
                  MQLONG PrstMsgLgth,
                  MQLONG DfltPrstCt,
                  MQLONG DfltPrstMsgLgth,
                  MQLONG NAPrstCt,
                  MQLONG NAPrstMsgLgth);

int crtOprTracker(char *Operation,
                  MQLONG OprCt,
                  MQLONG NonPrstCt,
                  MQLONG NonPrstMsgLgth,
                  MQLONG PrstCt,
                  MQLONG PrstMsgLgth,
                  MQLONG DfltPrstCt,
                  MQLONG DfltPrstMsgLgth,
                  MQLONG NAPrstCt,
                  MQLONG NAPrstMsgLgth);

int addTidTracker(MQLONG tid);

int crtTidTracker(MQLONG tid);

int printOption(MQLONG OptType,
                MQLONG Opt);

/********************************************************************/
/* MAIN                                                             */
/********************************************************************/
int main(int argc, char **argv)
{

  /*   Declare MQI structures needed                                */
  MQCNO   cno = {MQCNO_DEFAULT};   /* Connection Options            */
  MQOD     od = {MQOD_DEFAULT};    /* Object Descriptor             */
  MQSD     sd = {MQSD_DEFAULT};    /* Subscription Descriptor       */
  MQMD     md = {MQMD_DEFAULT};    /* Message Descriptor            */
  MQGMO   gmo = {MQGMO_DEFAULT};   /* get message options           */
  /** note, sample uses defaults where it can **/

  MQHCONN  Hcon = MQHC_UNUSABLE_HCONN; /* connection handle         */
  MQHOBJ   Hobj = MQHO_NONE;       /* object handle                 */
  MQHOBJ   Hsub = MQHO_NONE;       /* subscription handle           */
  MQLONG   O_options;              /* MQOPEN options                */
  MQLONG   C_options;              /* MQCLOSE options               */
  MQLONG   CompCode;               /* completion code               */
  MQLONG   Reason;                 /* reason code                   */
  MQBYTE   *buffer;                /* message buffer                */
  MQLONG   buflen;                 /* buffer length                 */
  MQLONG   messlen;                /* message length received       */
  int      prc;                    /* return code from program      */
  int      frc;                    /* function return code          */
  MQLONG   exitLoop=FALSE;
  MQCFH    *pcfh;                  /* Pointer to header             */
  MQLONG   StartBrowse=TRUE;

  char     qmgrName[MQ_Q_MGR_NAME_LENGTH]="";
  char     * pQName = "SYSTEM.ADMIN.TRACE.ACTIVITY.QUEUE";
  char     * pTopicStr = NULL;
  MQLONG   waitInterval=0;
  time_t   intervalStartTime;
  time_t   intervalEndTime;
  MQLONG   browse = FALSE;
  MQLONG   maximumRecords = -1;
  MQLONG   RecordNum=0;
  MQLONG   Verbose=FALSE;
  MQLONG   TidCt;

  char underline[130];                    /* Underline string        */
  PidTrackerItem *PidTrackerTemp=NULL;

  /******************************************************************/
  /* Parse the options from the command line                        */
  /******************************************************************/
  prc = ParseOptions(argc,
                     argv,
                     qmgrName,
                     &pQName,
                     &pTopicStr,
                     &browse,
                     &CodedCharSetId,
                     &Verbose,
                     &maximumRecords,
                     &waitInterval,
                     &intervalStartTime,
                     &intervalEndTime,
                     &APIFields1,
                     &APIFields2,
                     &Report);

  if (prc != 0)
  {
    int pad=(int)strlen(argv[0]);
    fprintf(stderr,
            "Usage: %s [-m QMgrName]\n"
            "       %*.s [-q QName]        # Override default queue name\n"
            "       %*.s [-t TopicString]  # Subscribe to event topic\n"
            "       %*.s [-b]              # Only browse records\n"
            "       %*.s [-c CCSID]        # CCSID to use for GET\n"
            "       %*.s [-v]              # Verbose output\n"
            "       %*.s [-d <depth>]      # Number of records to display\n"
            "       %*.s [-w <timeout>]    # Time to wait (in seconds)\n"
            "       %*.s [-s <startTime>]  # Start time of record to process\n"
            "       %*.s [-e <endTime>]    # End time of record to process\n"
            "       %*.s [-f <APIFields1>] # API fields to list for API one line summary\n"
            "       %*.s [-g <APIFields2>] # More API fields to list for API one line summary\n"
            "       %*.s [-r]              # Report for non-verbose run\n",
            argv[0],   /* -m */
            pad, " ",  /* -q */
            pad, " ",  /* -t */
            pad, " ",  /* -b */
            pad, " ",  /* -c */
            pad, " ",  /* -v */
            pad, " ",  /* -d */
            pad, " ",  /* -w */
            pad, " ",  /* -s */
            pad, " ", /* -e */
            pad, " ", /* -f */
            pad, " ", /* -g */
            pad, " "); /* -r */
    exit(-1);
  }

  /******************************************************************/
  /*                                                                */
  /*   The sample will not generate any activity trace              */
  /*                                                                */
  /******************************************************************/
  cno.Options |= MQCNO_ACTIVITY_TRACE_DISABLED;

  /******************************************************************/
  /*                                                                */
  /*   Connect to queue manager                                     */
  /*                                                                */
  /******************************************************************/
  MQCONNX(qmgrName,               /* queue manager                  */
          &cno,                    /* connection options             */
          &Hcon,                   /* connection handle              */
          &CompCode,               /* completion code                */
          &Reason);                /* reason code                    */

  /* report reason and stop if it failed     */
  if (CompCode == MQCC_FAILED)
  {
    fprintf(stderr, "MQCONN ended with reason code %d\n", (int)Reason);
    goto mod_exit;
  }

  if(pTopicStr != NULL)
  {
    sd.ObjectString.VSPtr = pTopicStr;
    sd.ObjectString.VSLength = (MQLONG)strlen(pTopicStr);

    sd.Options = MQSO_CREATE
                 | MQSO_NON_DURABLE
                 | MQSO_FAIL_IF_QUIESCING
                 | MQSO_MANAGED;

    MQSUB(Hcon,                       /* connection handle            */
          &sd,                        /* object descriptor for queue  */
          &Hobj,                      /* object handle                */
          &Hsub,                      /* subscription handle          */
          &CompCode,                  /* completion code              */
          &Reason);                   /* reason code                  */

    /* report reason, if any; stop if failed      */
    if ((CompCode == MQCC_FAILED) &&
        (Reason != MQRC_NONE))
    {
      fprintf(stderr, "MQSUB ended with reason code %d\n", (int)Reason);
      goto mod_exit;
    }
  }
  else 
  {  
    /******************************************************************/
    /*                                                                */
    /*   Open the named message queue for input; exclusive or shared  */
    /*   use of the queue is controlled by the queue definition here  */
    /*                                                                */
    /******************************************************************/
    strncpy(od.ObjectName, pQName, MQ_Q_NAME_LENGTH);

    O_options = MQOO_INPUT_AS_Q_DEF    /* open queue for input      */
                | MQOO_BROWSE            /* but not if MQM stopping   */
                | MQOO_FAIL_IF_QUIESCING /* but not if MQM stopping   */
                ;

    MQOPEN(Hcon,                      /* connection handle            */
           &od,                       /* object descriptor for queue  */
           O_options,                 /* open options                 */
           &Hobj,                     /* object handle                */
           &CompCode,                 /* completion code              */
           &Reason);                  /* reason code                  */

    /* report reason, if any; stop if failed      */
    if ((CompCode == MQCC_FAILED) &&
        (Reason != MQRC_NONE))
    {
      fprintf(stderr, "MQOPEN ended with reason code %d\n", (int)Reason);
      goto mod_exit;
    }
  }

  /******************************************************************/
  /* Initialise the buffer used for getting the message             */
  /******************************************************************/
  buflen = 1024 * 100; /* 100K */
  buffer=(MQBYTE *)malloc(buflen);
  if (buffer == NULL)
  {
    fprintf(stderr, "Failed to allocate memory(%d) for message\n", 
            (int)buflen);
    goto mod_exit;
  }

  /******************************************************************/
  /* Main processing loop                                           */
  /******************************************************************/
  do
  {
    gmo.Options = MQGMO_CONVERT;      /* convert if necessary       */

    if (StartBrowse)
    {
      gmo.Options |= MQGMO_BROWSE_FIRST;
      StartBrowse=FALSE;
    }
    else
    {
      gmo.Options |= MQGMO_BROWSE_NEXT;
    }

    if (waitInterval == 0)
    {
      gmo.Options |= MQGMO_NO_WAIT;
    }
    else
    {
      gmo.Options |= MQGMO_WAIT;
      gmo.WaitInterval = waitInterval * 1000;
    }

    do
    {
      memcpy(md.MsgId, MQMI_NONE, sizeof(md.MsgId));
      memcpy(md.CorrelId, MQCI_NONE, sizeof(md.CorrelId));

      /****************************************************************/
      /*                                                              */
      /*   MQGET sets Encoding and CodedCharSetId to the values in    */
      /*   the message returned, so these fields should be reset to   */
      /*   the default values before every call, as MQGMO_CONVERT is  */
      /*   specified.                                                 */
      /*                                                              */
      /****************************************************************/
      md.Encoding       = MQENC_NATIVE;
      md.CodedCharSetId = CodedCharSetId;

      MQGET(Hcon,                /* connection handle                 */
            Hobj,                /* object handle                     */
            &md,                 /* message descriptor                */
            &gmo,                /* get message options               */
            buflen,              /* buffer length                     */
            buffer,              /* message buffer                    */
            &messlen,            /* message length                    */
            &CompCode,           /* completion code                   */
            &Reason);            /* reason code                       */

      /* report reason, if any     */
      if ((CompCode == MQCC_WARNING) && 
          (Reason == MQRC_TRUNCATED_MSG_FAILED))
      {
        buflen=messlen;
        buffer=(MQBYTE *)realloc(buffer, buflen);
        if (buffer == NULL)
        {
          fprintf(stderr,
                  "Failed to allocate memory(%d) for message\n", (int)buflen);
          goto mod_exit;
        }
      }
    } while ((CompCode==MQCC_WARNING) && 
             (Reason == MQRC_TRUNCATED_MSG_FAILED));

    if (CompCode != MQCC_OK)
    {
      if (Reason == MQRC_NO_MSG_AVAILABLE)
      {
        exitLoop=TRUE;
      }
      else if (Reason == MQRC_Q_MGR_STOPPING)
      {
        fprintf(stderr, "Queue Manager Stopping.\n");
        exitLoop=TRUE;
      }
      else
      {
        fprintf(stderr, 
                "Failed to retrieve message from queue [reason: %d]\n",
                (int)Reason);
        exitLoop=TRUE;
      }
    }
    else
    {
      /**************************************************************/
      /* Check to see if the message matches what we are looking    */
      /* for.                                                       */
      /**************************************************************/
      pcfh=(MQCFH *)buffer;

      if (pcfh->Type != MQCFT_APP_ACTIVITY)
      {
        continue;
      }

      if (intervalStartTime != -1)
      {
        struct tm startTm = {0};
        time_t startTime;
        MQCHAR MsgStartDate[MQ_DATE_LENGTH+1];
        MQCHAR MsgStartTime[MQ_TIME_LENGTH+1];

        frc=getPCFDateTimeFromMsg(buffer + sizeof(MQCFH),
                                  pcfh->ParameterCount,
                                  MQCAMO_START_DATE,
                                  MQCAMO_START_TIME,
                                  MsgStartDate,
                                  MsgStartTime);
        if (frc == 0)
        {
          startTm.tm_year=1970;
          startTm.tm_mon=1;
          startTm.tm_mday=1;
          startTm.tm_hour=0;
          startTm.tm_min=0;
          startTm.tm_sec=0;

          sscanf(MsgStartDate, "%4u-%2u-%2u",
                 &(startTm.tm_year),
                 &(startTm.tm_mon),
                 &(startTm.tm_mday));
          sscanf(MsgStartTime, "%2u.%2u.%2u",
                 &(startTm.tm_hour),
                 &(startTm.tm_min),
                 &(startTm.tm_sec));

          if ((startTm.tm_year < 1900) ||
              (startTm.tm_mon < 1) ||
              (startTm.tm_mon > 12) ||
              (startTm.tm_mday < 1) ||
              (startTm.tm_mday > 31) ||
              (startTm.tm_hour > 24) ||
              (startTm.tm_min > 59) ||
              (startTm.tm_sec > 59))
          {
            continue;
          }

          startTm.tm_year-=1900;

          startTime=mktime(&startTm);

          if ((startTime == -1) ||
              (startTime < intervalStartTime))
          {
            continue;
          }
        }
      }

      if (intervalEndTime != -1)
      {
        struct tm endTm = {0};
        time_t endTime;
        MQCHAR MsgEndDate[MQ_DATE_LENGTH+1];
        MQCHAR MsgEndTime[MQ_TIME_LENGTH+1];

        frc=getPCFDateTimeFromMsg(buffer + sizeof(MQCFH),
                                  pcfh->ParameterCount,
                                  MQCAMO_END_DATE,
                                  MQCAMO_END_TIME,
                                  MsgEndDate,
                                  MsgEndTime);
        if (frc == 0)
        {
          endTm.tm_year=2999;
          endTm.tm_mon=12;
          endTm.tm_mday=31;
          endTm.tm_hour=23;
          endTm.tm_min=59;
          endTm.tm_sec=59;

          sscanf(MsgEndDate, "%4u-%2u-%2u",
                 &(endTm.tm_year),
                 &(endTm.tm_mon),
                 &(endTm.tm_mday));
          sscanf(MsgEndTime, "%2u.%2u.%2u",
                 &(endTm.tm_hour),
                 &(endTm.tm_min),
                 &(endTm.tm_sec));

          if ((endTm.tm_year < 1900) ||
              (endTm.tm_mon < 1) ||
              (endTm.tm_mon > 12) ||
              (endTm.tm_mday < 1) ||
              (endTm.tm_mday > 31) ||
              (endTm.tm_hour > 24) ||
              (endTm.tm_min > 59) ||
              (endTm.tm_sec > 59))
          {
            continue;
          }

          endTm.tm_year-=1900;

          endTime=mktime(&endTm);

          if ((endTime == -1) ||
              (endTime > intervalEndTime))
          {
            continue;
          }
        }
      }

      /**************************************************************/
      /* If we are not browsing the queue then reissue the get.     */
      /**************************************************************/
      if (!browse)
      {
        gmo.Options = MQGMO_CONVERT |     /* convert if necessary   */
                      MQGMO_MSG_UNDER_CURSOR |
                      MQGMO_NO_WAIT;

        MQGET(Hcon,              /* connection handle               */
              Hobj,              /* object handle                   */
              &md,               /* message descriptor              */
              &gmo,              /* get message options             */
              buflen,            /* buffer length                   */
              buffer,            /* message buffer                  */
              &messlen,          /* message length                  */
              &CompCode,         /* completion code                 */
              &Reason);          /* reason code                     */

        if (CompCode != MQCC_OK)
        {
          /**********************************************************/
          /* If we fail to get the message then perhaps someone     */
          /* else has got there first so just continue on the next  */
          /* msg.                                                   */
          /**********************************************************/
          continue;
        }
      }

      /**************************************************************/
      /* We have found a matching message so process it.            */
      /**************************************************************/
      printHeader = TRUE;
      prc=printMonitoring(&md,
                          buffer,
                          messlen,
                          Verbose,
                          RecordNum);

      if (prc == 0)
      {
        RecordNum++;
      }

      if ((maximumRecords != -1) && (RecordNum == maximumRecords))
      {
        exitLoop=TRUE;
      }
    }
  } while (!exitLoop);

  printf("%d Records Processed.\n", (int)RecordNum);

  if (!Verbose && Report)
  {
    /******************************************************************/
    /* Print out Application Summary Report                           */
    /******************************************************************/
    printf("\n");
    memset(underline, '=', sizeof(underline)-1);
    underline[sizeof(underline)-1]='\0';
    printf("%s\n", underline);
    printf("Application Summary Report\n");
    printf("%s\n", underline);
    printf("%-48s %-10s %-28s %-12s %-10s %-10s\n", "Queue Manager", "Pid", "ApplicationName", "UserId", "Tid Count", "MQI Count");
    PidTrackerCurr=PidTrackerHead;
    while (PidTrackerCurr != NULL)
    {
      TidCt=0;
      TidTrackerCurr=PidTrackerCurr->TidTrackerHead;
      while (TidTrackerCurr != NULL)
      {
        TidCt++;
        TidTrackerHead=TidTrackerCurr->nextItem;
        TidTrackerCurr=TidTrackerHead;
      }
      printf("%-48s %-10d %-28s %-12s %-10d %-10d\n", PidTrackerCurr->QmgrName, PidTrackerCurr->pid, PidTrackerCurr->ApplicationName, PidTrackerCurr->UserId, TidCt, PidTrackerCurr->MQICt);
      PidTrackerTemp=PidTrackerCurr->nextItem;
      PidTrackerCurr=PidTrackerTemp;
    }
  
    /******************************************************************/
    /* Print out Application Objects Referenced Report                */
    /******************************************************************/
    printf("\n");
    memset(underline, '=', sizeof(underline)-1);
    underline[sizeof(underline)-1]='\0';
    printf("%s\n", underline);
    printf("Application Objects Referenced Report\n");
    printf("%s\n", underline);
    PidTrackerCurr=PidTrackerHead;
    while (PidTrackerCurr != NULL)
    {
      printf("Qmgr(%s)  Pid(%d)  ApplName(%s)  UserId(%s)  referenced the following objects:\n", PidTrackerCurr->QmgrName, PidTrackerCurr->pid, PidTrackerCurr->ApplicationName, PidTrackerCurr->UserId);
      ObjTrackerCurr=PidTrackerCurr->ObjTrackerHead;
      while (ObjTrackerCurr != NULL)
      {
        printf("  ObjName: %-48s Count: %-10d\n", ObjTrackerCurr->ObjName, ObjTrackerCurr->ObjCt); 
        ObjTrackerHead=ObjTrackerCurr->nextItem;
        ObjTrackerCurr=ObjTrackerHead;
      }
      PidTrackerTemp=PidTrackerCurr->nextItem;
      PidTrackerCurr=PidTrackerTemp;
    }


    /******************************************************************/
    /* Print out Application Objects Detail Report                    */
    /******************************************************************/
    printf("\n");
    memset(underline, '=', sizeof(underline)-1);
    underline[sizeof(underline)-1]='\0';
    printf("%s\n", underline);
    printf("Application Objects Detail Report\n");
    printf("Details included by object are:\n");
    printf("1. Operations found, including persistence (NonPrst, Prst, DfltPrst) and total message length data, where applicable\n"); 
    printf("2. Options found, which include conn, open, get, put, close, callback, sub, subrq\n");
    printf("%s\n", underline);
    PidTrackerCurr=PidTrackerHead;
    while (PidTrackerCurr != NULL)
    {
      printf("Qmgr(%s)  Pid(%d)  ApplName(%s)  UserId(%s)  referenced the following operations and options by object:\n", PidTrackerCurr->QmgrName, PidTrackerCurr->pid, PidTrackerCurr->ApplicationName, PidTrackerCurr->UserId);

      ObjTrackerCurr=PidTrackerCurr->ObjTrackerHead;
      while (ObjTrackerCurr != NULL)
      {
        if (ObjTrackerCurr->OptTrackerHead != NULL)
        {
          printf("  Object Name: %-48s\n", ObjTrackerCurr->ObjName);

          OprTrackerCurr=ObjTrackerCurr->OprTrackerHead;
          while (OprTrackerCurr != NULL)
          {
            printf("    Operation: %-15s Count: %-10d\n", OprTrackerCurr->Operation, OprTrackerCurr->OprCt);
            if (OprTrackerCurr->NonPrstCt > 0)
              printf("      NonPrstCount: %-10d  TotalMessageLength: %-10d\n", OprTrackerCurr->NonPrstCt, OprTrackerCurr->NonPrstMsgLgth);
            if (OprTrackerCurr->PrstCt > 0)
              printf("      PrstCount: %-10d  TotalMessageLength: %-10d\n", OprTrackerCurr->PrstCt, OprTrackerCurr->PrstMsgLgth);
            if (OprTrackerCurr->DfltPrstCt > 0)
              printf("      DfltPrstCount: %-10d  TotalMessageLength: %-10d\n", OprTrackerCurr->DfltPrstCt, OprTrackerCurr->DfltPrstMsgLgth);
            if (OprTrackerCurr->NAPrstCt > 0)
              printf("      Count: %-10d  TotalMessageLength: %-10d\n", OprTrackerCurr->NAPrstCt, OprTrackerCurr->NAPrstMsgLgth);
            OprTrackerHead=OprTrackerCurr->nextItem;
            OprTrackerCurr=OprTrackerHead;
          }

          OptTrackerCurr=ObjTrackerCurr->OptTrackerHead;
          while (OptTrackerCurr != NULL)
          {
            switch (OptTrackerCurr->OptType) {
            case 1:
              printf("    Connect Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 2:
              printf("    Open Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 3:
              printf("    Get Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 4:
              printf("    Put Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 5:
              printf("    Close Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 6:
              printf("    Callback Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 7:
              printf("    Subscription Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 8:
              printf("    Subscription Request Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            }
            OptTrackerHead=OptTrackerCurr->nextItem;
            OptTrackerCurr=OptTrackerHead;
          }
        }
        ObjTrackerHead=ObjTrackerCurr->nextItem;
        ObjTrackerCurr=ObjTrackerHead;
      }

      PidTrackerTemp=PidTrackerCurr->nextItem;
      PidTrackerCurr=PidTrackerTemp;
    }


    /******************************************************************/
    /* Print out Application Channels Referenced Report               */
    /******************************************************************/
    printf("\n");
    memset(underline, '=', sizeof(underline)-1);
    underline[sizeof(underline)-1]='\0';
    printf("%s\n", underline);
    printf("Application Channels Referenced Report\n");
    printf("%s\n", underline);
    PidTrackerCurr=PidTrackerHead;
    while (PidTrackerCurr != NULL)
    {
      printf("Qmgr(%s)  Pid(%d)  ApplName(%s)  UserId(%s)  referenced the following channels:\n", PidTrackerCurr->QmgrName, PidTrackerCurr->pid, PidTrackerCurr->ApplicationName, PidTrackerCurr->UserId);
      ChlTrackerCurr=PidTrackerCurr->ChlTrackerHead;
      while (ChlTrackerCurr != NULL)
      {
        printf("  ChannelName: %-20s Count: %-10d\n", ChlTrackerCurr->ChannelName, ChlTrackerCurr->ChlCt);
        ChlTrackerHead=ChlTrackerCurr->nextItem;
        ChlTrackerCurr=ChlTrackerHead;
      }
      PidTrackerTemp=PidTrackerCurr->nextItem;
      PidTrackerCurr=PidTrackerTemp;
    }

    /******************************************************************/
    /* Print out Application Operations Executed Report               */
    /******************************************************************/
    printf("\n");
    memset(underline, '=', sizeof(underline)-1);
    underline[sizeof(underline)-1]='\0';
    printf("%s\n", underline);
    printf("Application Operations Executed Report\n");
    printf("This report also includes persistence (NonPrst, Prst, DfltPrst) and total message length data, where applicable\n");
    printf("%s\n", underline);
    PidTrackerCurr=PidTrackerHead;
    while (PidTrackerCurr != NULL)
    {
      printf("Qmgr(%s)  Pid(%d)  ApplName(%s)  UserId(%s)  executed the following operations:\n", PidTrackerCurr->QmgrName, PidTrackerCurr->pid, PidTrackerCurr->ApplicationName, PidTrackerCurr->UserId);
      OprTrackerCurr=PidTrackerCurr->OprTrackerHead;
      while (OprTrackerCurr != NULL)
      {
        printf("  Operation: %-15s Count: %-10d\n", OprTrackerCurr->Operation, OprTrackerCurr->OprCt);
        if (OprTrackerCurr->NonPrstCt > 0)
          printf("    NonPrstCount: %-10d  TotalMessageLength: %-10d\n", OprTrackerCurr->NonPrstCt, OprTrackerCurr->NonPrstMsgLgth);
        if (OprTrackerCurr->PrstCt > 0)
          printf("    PrstCount: %-10d  TotalMessageLength: %-10d\n", OprTrackerCurr->PrstCt, OprTrackerCurr->PrstMsgLgth);
        if (OprTrackerCurr->DfltPrstCt > 0)
          printf("    DfltPrstCount: %-10d  TotalMessageLength: %-10d\n", OprTrackerCurr->DfltPrstCt, OprTrackerCurr->DfltPrstMsgLgth);
        if (OprTrackerCurr->NAPrstCt > 0)
          printf("    Count: %-10d  TotalMessageLength: %-10d\n", OprTrackerCurr->NAPrstCt, OprTrackerCurr->NAPrstMsgLgth);
        OprTrackerHead=OprTrackerCurr->nextItem;
        OprTrackerCurr=OprTrackerHead;
      }
      PidTrackerTemp=PidTrackerCurr->nextItem;
      PidTrackerCurr=PidTrackerTemp;
    }

    /******************************************************************/
    /* Print out Application Operations Options Report                */
    /* Options tracked are conn, open, get, put, close, callback      */
    /******************************************************************/
    printf("\n");
    memset(underline, '=', sizeof(underline)-1);
    underline[sizeof(underline)-1]='\0';
    printf("%s\n", underline);
    printf("Application Operations Options Report\n");
    printf("Options tracked include conn, open, get, put, close, callback, sub, subrq\n");
    printf("%s\n", underline);
    PidTrackerCurr=PidTrackerHead;
    while (PidTrackerCurr != NULL)
    {
      printf("Qmgr(%s)  Pid(%d)  ApplName(%s)  UserId(%s)  referenced the following options by operations:\n", PidTrackerCurr->QmgrName, PidTrackerCurr->pid, PidTrackerCurr->ApplicationName, PidTrackerCurr->UserId);

      OprTrackerCurr=PidTrackerCurr->OprTrackerHead;
      while (OprTrackerCurr != NULL)
      {
        if (OprTrackerCurr->OptTrackerHead != NULL)
        {
          printf("  Operation: %-15s\n", OprTrackerCurr->Operation);
          OptTrackerCurr=OprTrackerCurr->OptTrackerHead;
          while (OptTrackerCurr != NULL)
          {
            switch (OptTrackerCurr->OptType) {
            case 1:
              printf("    Connect Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 2:
              printf("    Open Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 3:
              printf("    Get Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 4:
              printf("    Put Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 5:
              printf("    Close Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 6:
              printf("    Callback Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 7:
              printf("    Subscription Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;
            case 8:
              printf("    Subscription Request Options: %-10d Count: %-10d\n", OptTrackerCurr->Opt, OptTrackerCurr->OptCt);
              printOption(OptTrackerCurr->OptType,OptTrackerCurr->Opt);
              break;            }
            OptTrackerHead=OptTrackerCurr->nextItem;
            OptTrackerCurr=OptTrackerHead;
          }
        }
        OprTrackerHead=OprTrackerCurr->nextItem;
        OprTrackerCurr=OprTrackerHead;
      }

      PidTrackerTemp=PidTrackerCurr->nextItem;
      PidTrackerCurr=PidTrackerTemp;
    }


    /******************************************************************/
    /* Print out Application Operations Reason Code Report            */
    /******************************************************************/
    printf("\n");
    memset(underline, '=', sizeof(underline)-1);
    underline[sizeof(underline)-1]='\0';
    printf("%s\n", underline);
    printf("Application Operations Reason Code Report\n");
    printf("%s\n", underline);
    PidTrackerCurr=PidTrackerHead;
    while (PidTrackerCurr != NULL)
    {
      printf("Qmgr(%s)  Pid(%d)  ApplName(%s)  UserId(%s)  referenced the following reason codes by operations:\n", PidTrackerCurr->QmgrName, PidTrackerCurr->pid, PidTrackerCurr->ApplicationName, PidTrackerCurr->UserId);

      OprTrackerCurr=PidTrackerCurr->OprTrackerHead;
      while (OprTrackerCurr != NULL)
      {
        if (OprTrackerCurr->ReasonTrackerHead != NULL)
        {
          printf("  Operation: %-15s\n", OprTrackerCurr->Operation);
          ReasonTrackerCurr=OprTrackerCurr->ReasonTrackerHead;
          while (ReasonTrackerCurr != NULL)
          {
            printf("    Reason Code: %-10d Count: %-10d\n", ReasonTrackerCurr->Reason, ReasonTrackerCurr->ReasonCt);
            ReasonTrackerHead=ReasonTrackerCurr->nextItem;
            ReasonTrackerCurr=ReasonTrackerHead;
          }
        }
        OprTrackerHead=OprTrackerCurr->nextItem;
        OprTrackerCurr=OprTrackerHead;
      }

      PidTrackerTemp=PidTrackerCurr->nextItem;
      PidTrackerCurr=PidTrackerTemp;
    }

  }  /* if (!Verbose && Report) */


mod_exit:

  /******************************************************************/
  /*                                                                */
  /*   Close the subscription (if it was made)                      */
  /*                                                                */
  /******************************************************************/
  if(Hsub != MQHO_NONE)
  {
    C_options = MQCO_NONE;             /* no close options          */
  
    MQCLOSE(Hcon,                      /* connection handle         */
            &Hsub,                     /* subscription handle       */
            C_options,
            &CompCode,                 /* completion code           */
            &Reason);                  /* reason code               */
  
    if (Reason != MQRC_NONE)
    {
      if ((CompCode != MQRC_CONNECTION_BROKEN) &&
          (CompCode != MQRC_Q_MGR_STOPPING))
      {
        fprintf(stderr, "MQCLOSE of subscription ended with reason code %d\n", 
                (int)Reason);
      }
    }
  }

  /******************************************************************/
  /*                                                                */
  /*   Close the source queue (if it was opened)                    */
  /*                                                                */
  /******************************************************************/
  if(Hobj != MQHO_NONE)
  {
    C_options = MQCO_NONE;             /* no close options          */
  
    MQCLOSE(Hcon,                      /* connection handle         */
            &Hobj,                     /* object handle             */
            C_options,
            &CompCode,                 /* completion code           */
            &Reason);                  /* reason code               */
  
    if (Reason != MQRC_NONE)
    {
      if ((CompCode != MQRC_CONNECTION_BROKEN) &&
          (CompCode != MQRC_Q_MGR_STOPPING))
      {
        fprintf(stderr, "MQCLOSE of queue ended with reason code %d\n", 
                (int)Reason);
      }
    }
  }

  /******************************************************************/
  /*                                                                */
  /*   Disconnect from MQM                                          */
  /*                                                                */
  /******************************************************************/
  if(Hcon != MQHC_UNUSABLE_HCONN)
  {
    MQDISC(&Hcon,                       /* connection handle        */
           &CompCode,                   /* completion code          */
           &Reason);                    /* reason code              */
  
    if (Reason != MQRC_NONE)
    {
      if ((CompCode != MQRC_CONNECTION_BROKEN) &&
          (CompCode != MQRC_Q_MGR_STOPPING))
      {
        fprintf(stderr, "MQDISC ended with reason code %d\n", (int)Reason);
      }
    }
  }

  /******************************************************************/
  /*                                                                */
  /* END OF AMQSMON0                                                */
  /*                                                                */
  /******************************************************************/
  return((RecordNum >0)?0:1);
}

/********************************************************************/
/*                                                                  */
/* Function: parseOptions                                           */
/*                                                                  */
/*                                                                  */
/*   This function parses the options supplied by the user on the   */
/*   command line and returns the options selected as a set of      */
/*   flags back to the caller.                                      */
/*                                                                  */
/********************************************************************/
static int ParseOptions(int     argc,
                        char    *argv[],
                        char    qmgrName[MQ_Q_MGR_NAME_LENGTH],
                        char    **ppqname,
                        char    **pptopicstr,
                        MQLONG  *pbrowse,
                        MQLONG  *pCodedCharSetId,
                        MQLONG  *pVerbose,
                        MQLONG  *pmaximumRecords,
                        MQLONG  *pwaitTime,
                        time_t  *pstartTime,
                        time_t  *pendTime,
                        MQLONG  *pAPIFields1,
                        MQLONG  *pAPIFields2,
                        MQLONG  *pReport)
{
  int counter;              /* Argument counter                    */
  int InvalidArgument=0;    /* Number of invalid argument          */
  int error=FALSE;          /* Number of invalid argument          */
  int i;                    /* Simple counter                      */
  char *p;                  /* Simple character pointer            */
  char *parg;               /* pointer to current argument         */
  char *pval;               /* pointer to current value            */

  struct tm startTime={0};
  struct tm endTime={0};
 
  int qnameSpecified     = FALSE;
  int topicstrSpecified  = FALSE;
  int browseSpecified    = FALSE;
  int CCSIDSpecified     = FALSE;
  int verboseSpecified   = FALSE;
  int depthSpecified     = FALSE;
  int qmgrSpecified      = FALSE;
  int waitSpecified      = FALSE;
  int startTimeSpecified = FALSE;
  int endTimeSpecified   = FALSE;
  int reportSpecified    = FALSE;
  int APIFields1Specified  = FALSE;
  int APIFields2Specified  = FALSE;

  memset(qmgrName, 0, MQ_Q_MGR_NAME_LENGTH);
  *pbrowse=FALSE;
  *pVerbose =FALSE;
  *pmaximumRecords=-1;
  *pwaitTime=0;
  *pstartTime=-1;
  *pendTime=-1;
  *pReport=FALSE;
  *pAPIFields1=1023;
  *pAPIFields2=0;

  for (counter=1; (counter < argc) && !InvalidArgument; counter++)
  {
    parg=argv[counter];

    if (parg[0] != '-')
    {
      InvalidArgument=counter;
      continue;
    }

    switch (parg[1])
    {
    case 'm': /* Queue manager Name */
      if (qmgrSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        qmgrSpecified=TRUE;
        memset(qmgrName, 0, MQ_Q_MGR_NAME_LENGTH);
        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */

        if ((*p == '\0') && ((counter+1) < argc))
        {
          pval=argv[++counter];
        }
        else
        {
          pval=p;
        }

        for (i=0; (*pval != '\0') && (i <MQ_Q_MGR_NAME_LENGTH); i++)
        {
          qmgrName[i]=*pval++;
        }
      }
      break;
    case 'q': /* Queue Name */
      if (qnameSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        qnameSpecified=TRUE;

        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */

        if ((*p == '\0') && ((counter+1) < argc))
        {
          pval=argv[++counter];
        }
        else
        {
          pval=p;
        }
        *ppqname = pval;
      }
      break;
    case 't': /* Topic String */
      if (topicstrSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        topicstrSpecified=TRUE;

        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */

        if ((*p == '\0') && ((counter+1) < argc))
        {
          pval=argv[++counter];
        }
        else
        {
          pval=p;
        }
        *pptopicstr = pval;
      }
      break;
    case 'b': /* Browse messages only */
      if (browseSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        browseSpecified=TRUE;
        *pbrowse=TRUE;
      }
      break;
    case 'c': /* CCSID to use for GET */
      if (CCSIDSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        CCSIDSpecified=TRUE;
        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */
        if (*p == '\0')
        {
          if ((counter+1 < argc) && argv[counter+1][0] != '-')
          {
            counter++;
            pval=argv[counter];
          }
          else
          {
            pval=NULL;
          }
        }
        else
        {
          pval=p;
        }

        if ((pval == NULL) || (*pval == '\0'))
        {
          *pCodedCharSetId=MQCCSI_Q_MGR;
        }
        else
        {
          *pCodedCharSetId=atoi(pval);
          if (*pCodedCharSetId <= 0)
          {
            InvalidArgument=counter;
          }
        }
      }
      break;
    case 'v': /* Verbose output */
      if (verboseSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        verboseSpecified=TRUE;
        *pVerbose=TRUE;
      }
      break;
    case 'r': /* Report */
      if (reportSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        reportSpecified=TRUE;
        *pReport=TRUE;
      }
      break;
    case 'd': /* Maximum number of messages to display */
      if (depthSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        depthSpecified=TRUE;
        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */
        if (*p == '\0')
        {
          if ((counter+1 < argc) && argv[counter+1][0] != '-')
          {
            counter++;
            pval=argv[counter];
          }
          else
          {
            pval=NULL;
          }
        }
        else
        {
          pval=p;
        }

        if ((pval == NULL) || (*pval == '\0'))
        {
          *pmaximumRecords=1;
        }
        else
        {
          *pmaximumRecords=atoi(pval);
          if (*pmaximumRecords <= 0)
          {
            InvalidArgument=counter;
          }
        }
      }
      break;
    case 'f': /* APIFields1 to display in one line API summary */
      if (APIFields1Specified)
      {
        InvalidArgument=counter;
      }
      else
      {
        APIFields1Specified=TRUE;
        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */
        if (*p == '\0')
        {
          if ((counter+1 < argc) && argv[counter+1][0] != '-')
          {
            counter++;
            pval=argv[counter];
          }
          else
          {
            pval=NULL;
          }
        }
        else
        {
          pval=p;
        }

        if ((pval == NULL) || (*pval == '\0'))
        {
          *pAPIFields1=1023;
        }
        else
        {
          *pAPIFields1=atoi(pval);
          if (*pAPIFields1 <= 0)
          {
            InvalidArgument=counter;
          }
        }
      }
      break;
    case 'g': /* APIFields2 to display in one line API summary */
      if (APIFields2Specified)
      {
        InvalidArgument=counter;
      }
      else
      {
        APIFields2Specified=TRUE;
        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */
        if (*p == '\0')
        {
          if ((counter+1 < argc) && argv[counter+1][0] != '-')
          {
            counter++;
            pval=argv[counter];
          }
          else
          {
            pval=NULL;
          }
        }
        else
        {
          pval=p;
        }

        if ((pval == NULL) || (*pval == '\0'))
        {
          *pAPIFields2=0;
        }
        else
        {
          *pAPIFields2=atoi(pval);
          if (*pAPIFields2 <= 0)
          {
            InvalidArgument=counter;
          }
        }
      }
      break;
    case 'w': /* The maximum time to wait for a message  */
      if (waitSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        waitSpecified=TRUE;
        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */
        if (*p == '\0')
        {
          if ((counter+1 < argc) && argv[counter+1][0] != '-')
          {
            counter++;
            pval=argv[counter];
          }
          else
          {
            pval=NULL;
          }
        }
        else
        {
          pval=p;
        }

        if ((pval == NULL) || (*pval == '\0'))
        {
          *pwaitTime=0;
        }
        else
        {
          *pwaitTime=atoi(pval);
          if (*pwaitTime < 0)
          {
            *pwaitTime=0;
          }
        }
      }
      break;
    case 's': /* The start time of records to process */
      memset(&startTime, 0, sizeof(startTime));
      startTime.tm_year=1970;
      startTime.tm_mon=1;
      startTime.tm_mday=1;
      startTime.tm_hour=0;
      startTime.tm_min=0;
      startTime.tm_sec=0;

      if (startTimeSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        startTimeSpecified=TRUE;
        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */
        if (*p == '\0')
        {
          if ((counter+1 < argc) && (argv[counter+1][0] != '-'))
          {
            counter++;
            pval=argv[counter];
          }
          else
          {
            pval=NULL;
          }
        }
        else
        {
          pval=p;
        }
        if ((pval == NULL) || (*pval == '\0'))
        {
          InvalidArgument=counter;
        }
        else
        {
          sscanf(pval, "%4u-%2u-%2u %2u.%2u.%2u",
                 &(startTime.tm_year),
                 &(startTime.tm_mon),
                 &(startTime.tm_mday),
                 &(startTime.tm_hour),
                 &(startTime.tm_min),
                 &(startTime.tm_sec));

          if ((startTime.tm_year < 1900) ||
              (startTime.tm_mon < 1) ||
              (startTime.tm_mon > 12) ||
              (startTime.tm_mday < 1) ||
              (startTime.tm_mday > 31) ||
              (startTime.tm_hour > 24) ||
              (startTime.tm_min > 59) ||
              (startTime.tm_sec > 59))
          {
            InvalidArgument=counter;
          }
          else
          {
            startTime.tm_year-=1900;

            *pstartTime=mktime(&startTime);

            if (*pstartTime == -1)
            {
              InvalidArgument=counter;
            }
          }
        }
      }
      break;
    case 'e': /* The end time of records to process */
      memset(&endTime, 0, sizeof(endTime));
      endTime.tm_year=2999;
      endTime.tm_mon=12;
      endTime.tm_mday=31;
      endTime.tm_hour=23;
      endTime.tm_min=59;
      endTime.tm_sec=59;

      if (endTimeSpecified)
      {
        InvalidArgument=counter;
      }
      else
      {
        endTimeSpecified=TRUE;
        for (p=&(parg[2]); *p==' '; p++) ; /* Strip off spaces        */
        if (*p == '\0')
        {
          if ((counter+1 < argc) && (argv[counter+1][0] != '-'))
          {
            counter++;
            pval=argv[counter];
          }
          else
          {
            pval=NULL;
          }
        }
        else
        {
          pval=p;
        }
        if ((pval == NULL) || (*pval == '\0'))
        {
          InvalidArgument=counter;
        }
        else
        {
          sscanf(pval, "%4u-%2u-%2u %2u.%2u.%2u",
                 &(endTime.tm_year),
                 &(endTime.tm_mon),
                 &(endTime.tm_mday),
                 &(endTime.tm_hour),
                 &(endTime.tm_min),
                 &(endTime.tm_sec));

          if ((endTime.tm_year < 1900) ||
              (endTime.tm_mon < 1) ||
              (endTime.tm_mon > 12) ||
              (endTime.tm_mday < 1) ||
              (endTime.tm_mday > 31) ||
              (endTime.tm_hour > 24) ||
              (endTime.tm_min > 59) ||
              (endTime.tm_sec > 59))
          {
            InvalidArgument=counter;
          }
          else
          {
            endTime.tm_year-=1900;

            *pendTime=mktime(&endTime);

            if (*pendTime == -1)
            {
              InvalidArgument=counter;
            }
          }
        }
      }
      break;
    default:
      InvalidArgument=counter;
      break;
    }
  }

  if (InvalidArgument != 0)
  {
    fprintf(stderr, "Argument %d has an error\n",
            InvalidArgument);
    error=TRUE;
  }


  return error;
}
/********************************************************************/
/*                                                                  */
/* Keywords and Constants                                           */
/*                                                                  */
/*                                                                  */
/*   The following Keywords and Constants are used for formatting   */
/*   the PCF application trace data                        */
/*                                                                  */
/********************************************************************/
/********************************************************************/

/********************************************************************/
/* Structure: ConstDefinitions                                      */
/*                                                                  */
/*   This structure is used to define test definitions of MQ        */
/*   constants into text identifiers.                               */
/*                                                                  */
/********************************************************************/
struct ConstDefinitions
{
  MQLONG Value;
  char *Identifier;
};


/* For MQIACF_API_ENVIRONMENT */
static struct ConstDefinitions  ExitEnvironment[] =
{
  {MQXE_OTHER,          "MQXE_OTHER"},
  {MQXE_MCA,            "MQXE_MCA"},
  {MQXE_MCA_SVRCONN,    "MQXE_MCA_SVRCONN"},
  {MQXE_COMMAND_SERVER, "MQXE_COMMAND_SERVER"},
  {MQXE_MQSC,           "MQXE_MQSC"},
  {-1, ""}
};

/* For MQIA_PLATFORM */
static struct ConstDefinitions  Platform[] =
{
  {MQPL_ZOS,        "MQPL_ZOS"},
  {MQPL_OS2,        "MQPL_OS2"},
  {MQPL_UNIX,       "MQPL_UNIX"},
  {MQPL_OS400,      "MQPL_OS400"},
  {MQPL_WINDOWS,    "MQPL_WINDOWS"},
  {MQPL_WINDOWS_NT, "MQPL_WINDOWS_NT"},
  {MQPL_VMS,        "MQPL_VMS"},
  {MQPL_NSS,        "MQPL_NSS"},
  {MQPL_OPEN_TP1,   "MQPL_OPEN_TP1"},
  {MQPL_VM,         "MQPL_VM"},
  {MQPL_TPF,        "MQPL_TPF"},
  {MQPL_VSE,        "MQPL_VSE"},
  {-1, ""}
};

/* For MQIA_APPL_TYPE */
static struct ConstDefinitions  AppType[] =
{
  {MQAT_NO_CONTEXT,       "MQAT_NO_CONTEXT"},
  {MQAT_CICS,             "MQAT_CICS"},
  {MQAT_MVS,              "MQAT_MVS"},
  {MQAT_OS390,            "MQAT_OS390"},
  {MQAT_ZOS,              "MQAT_ZOS"},
  {MQAT_IMS,              "MQAT_IMS"},
  {MQAT_OS2,              "MQAT_OS2"},
  {MQAT_DOS,              "MQAT_DOS"},
  {MQAT_UNIX,             "MQAT_UNIX"},
  {MQAT_QMGR,             "MQAT_QMGR"},
  {MQAT_OS400,            "MQAT_OS400"},
  {MQAT_WINDOWS,          "MQAT_WINDOWS"},
  {MQAT_CICS_VSE,         "MQAT_CICS_VSE"},
  {MQAT_WINDOWS_NT,       "MQAT_WINDOWS_NT"},
  {MQAT_VMS,              "MQAT_VMS"},
  {MQAT_NSK,              "MQAT_NSK"},
  {MQAT_VOS,              "MQAT_VOS"},
  {MQAT_OPEN_TP1,         "MQAT_OPEN_TP1"},
  {MQAT_VM,               "MQAT_VM"},
  {MQAT_IMS_BRIDGE,       "MQAT_IMS_BRIDGE"},
  {MQAT_XCF,              "MQAT_XCF"},
  {MQAT_CICS_BRIDGE,      "MQAT_CICS_BRIDGE"},
  {MQAT_NOTES_AGENT,      "MQAT_NOTES_AGENT"},
  {MQAT_TPF,              "MQAT_TPF"},
  {MQAT_USER,             "MQAT_USER"},
  {MQAT_BROKER,           "MQAT_BROKER"},
  {MQAT_JAVA,             "MQAT_JAVA"},
  {MQAT_DQM,              "MQAT_DQM"},
  {MQAT_CHANNEL_INITIATOR,"MQAT_CHANNEL_INITIATOR"},
  {MQAT_WLM,              "MQAT_WLM"},
  {MQAT_BATCH,            "MQAT_BATCH"},
  {MQAT_RRS_BATCH,        "MQAT_RRS_BATCH"},
  {MQAT_SIB,              "MQAT_SIB"},
  {MQAT_SYSTEM_EXTENSION, "MQAT_SYSTEM_EXTENSION"},
  {MQAT_USER_FIRST,       "MQAT_USER_FIRST"},
  {MQAT_USER_LAST,        "MQAT_USER_LAST"},
  {-1, ""}
};


/* For MQIACF_API_CALLER_TYPE */
static struct ConstDefinitions  ExitAPICaller[] =
{
  {MQXACT_EXTERNAL,   "MQXACT_EXTERNAL"},
  {MQXACT_INTERNAL,   "MQXACT_INTERNAL"},
  {-1, ""}
};

/* For MQIACF_COMP_CODE */
static struct ConstDefinitions  CompCode[] =
{
  {MQCC_OK,           "MQCC_OK"},
  {MQCC_WARNING,      "MQCC_WARNING"},
  {MQCC_FAILED,       "MQCC_FAILED"},
  {MQCC_UNKNOWN,      "MQCC_UNKNOWN"},
  {-1, ""}
};
/* For MQIACF_CTL_OPERATION */
static struct ConstDefinitions  CtlOp[] =
{
  {MQOP_DEREGISTER,    "MQOP_DEREGISTER"},
  {MQOP_REGISTER,      "MQOP_REGISTER"},
  {MQOP_SUSPEND,       "MQOP_SUSPEND"},
  {MQOP_RESUME,        "MQOP_RESUME"},
  {MQOP_START,         "MQOP_START"},
  {MQOP_START_WAIT,    "MQOP_START_WAIT"},
  {MQOP_STOP,          "MQOP_STOP"},
  {-1, ""}
};
/* For MQIACF_MQCB_OPERATION */
static struct ConstDefinitions  CallbackOp[] =
{
  {MQOP_DEREGISTER,    "MQOP_DEREGISTER"},
  {MQOP_REGISTER,      "MQOP_REGISTER"},
  {MQOP_SUSPEND,       "MQOP_SUSPEND"},
  {MQOP_RESUME,        "MQOP_RESUME"},
  {-1, ""}
};
/* For MQIACF_MQCB_TYPE */
static struct ConstDefinitions  CallbackType[] =
{
  {MQCBT_MESSAGE_CONSUMER, "MQCBT_MESSAGE_CONSUMER"},
  {MQCBT_EVENT_HANDLER,    "MQCBT_EVENT_HANDLER"},
  {-1, ""}
};
/* For MQIACF_CALL_TYPE */
static struct ConstDefinitions  CallType[] =
{
  {MQCBCT_START_CALL,      "MQCBCT_START_CALL"},
  {MQCBCT_STOP_CALL,       "MQCBCT_STOP_CALL"},
  {MQCBCT_REGISTER_CALL,   "MQCBCT_REGISTER_CALL"},
  {MQCBCT_DEREGISTER_CALL, "MQCBCT_DEREGISTER_CALL"},
  {MQCBCT_EVENT_CALL,      "MQCBCT_EVENT_CALL"},
  {MQCBCT_MSG_REMOVED,     "MQCBCT_MSG_REMOVED"},
  {MQCBCT_MSG_NOT_REMOVED, "MQCBCT_MSG_NOT_REMOVED"},
  {-1, ""}
};

/* For MQIACF_OPERATION_ID */
static struct ConstDefinitions  OperationId[] =
{
  {MQXF_CONN,            "MQXF_CONN"},
  {MQXF_CONNX,           "MQXF_CONNX"},
  {MQXF_DISC,            "MQXF_DISC"},
  {MQXF_OPEN,            "MQXF_OPEN"},
  {MQXF_CLOSE,           "MQXF_CLOSE"},
  {MQXF_PUT1,            "MQXF_PUT1"},
  {MQXF_PUT,             "MQXF_PUT"},
  {MQXF_GET,             "MQXF_GET"},
  {MQXF_INQ,             "MQXF_INQ"},
  {MQXF_SET,             "MQXF_SET"},
  {MQXF_BEGIN,           "MQXF_BEGIN"},
  {MQXF_CMIT,            "MQXF_CMIT"},
  {MQXF_BACK,            "MQXF_BACK"},
  {MQXF_STAT,            "MQXF_STAT"},
  {MQXF_CB,              "MQXF_CB"},
  {MQXF_CTL,             "MQXF_CTL"},
  {MQXF_CALLBACK,        "MQXF_CALLBACK"},
  {MQXF_SUB,             "MQXF_SUB"},
  {MQXF_SUBRQ,           "MQXF_SUBRQ"},
  {MQXF_XACLOSE,         "MQXF_XACLOSE"},
  {MQXF_XACOMMIT,        "MQXF_XACOMMIT"},
  {MQXF_XACOMPLETE,      "MQXF_XACOMPLETE"},
  {MQXF_XAEND,           "MQXF_XAEND"},
  {MQXF_XAFORGET,        "MQXF_XAFORGET"},
  {MQXF_XAOPEN,          "MQXF_XAOPEN"},
  {MQXF_XAPREPARE,       "MQXF_XAPREPARE"},
  {MQXF_XARECOVER,       "MQXF_XARECOVER"},
  {MQXF_XAROLLBACK,      "MQXF_XAROLLBACK"},
  {MQXF_XASTART,         "MQXF_XASTART"},
  {-1, ""}
};

/* Object types */
static struct ConstDefinitions ObjTypes[] =
{
  {MQOT_Q_MGR                 ,"MQOT_Q_MGR"},
  {MQOT_Q                     ,"MQOT_Q"},
  {MQOT_NAMELIST              ,"MQOT_NAMELIST"},
  {MQOT_PROCESS               ,"MQOT_PROCESS"},
  {MQOT_STORAGE_CLASS         ,"MQOT_STORAGE_CLASS"},
  {MQOT_CHANNEL               ,"MQOT_CHANNEL"},
  {MQOT_AUTH_INFO             ,"MQOT_AUTH_INFO"},
  {MQOT_CF_STRUC              ,"MQOT_CF_STRUC"},
  {MQOT_LISTENER              ,"MQOT_LISTENER"},
  {MQOT_SERVICE               ,"MQOT_SERVICE"},
  {MQOT_RESERVED_1            ,"MQOT_RESERVED_1"},
  {MQOT_ALL                   ,"MQOT_ALL"},
  {MQOT_ALIAS_Q               ,"MQOT_ALIAS_Q"},
  {MQOT_MODEL_Q               ,"MQOT_MODEL_Q"},
  {MQOT_LOCAL_Q               ,"MQOT_LOCAL_Q"},
  {MQOT_REMOTE_Q              ,"MQOT_REMOTE_Q"},
  {MQOT_SENDER_CHANNEL        ,"MQOT_SENDER_CHANNEL"},
  {MQOT_SERVER_CHANNEL        ,"MQOT_SERVER_CHANNEL"},
  {MQOT_REQUESTER_CHANNEL     ,"MQOT_REQUESTER_CHANNEL"},
  {MQOT_RECEIVER_CHANNEL      ,"MQOT_RECEIVER_CHANNEL"},
  {MQOT_CURRENT_CHANNEL       ,"MQOT_CURRENT_CHANNEL"},
  {MQOT_SAVED_CHANNEL         ,"MQOT_SAVED_CHANNEL"},
  {MQOT_SVRCONN_CHANNEL       ,"MQOT_SVRCONN_CHANNEL"},
  {MQOT_CLNTCONN_CHANNEL      ,"MQOT_CLNTCONN_CHANNEL"},
  {MQOT_REMOTE_Q_MGR_NAME     ,"MQOT_REMOTE_Q_MGR_NAME"},
  {-1, ""}
};

/* Channel types */
static struct ConstDefinitions ChlTypes[] =
{
  {MQCHT_SENDER                 ,"MQCHT_SENDER"},
  {MQCHT_SERVER                 ,"MQCHT_SERVER"},
  {MQCHT_RECEIVER               ,"MQCHT_RECEIVER"},
  {MQCHT_REQUESTER              ,"MQCHT_REQUESTER"},
  {MQCHT_ALL                    ,"MQCHT_ALL"},
  {MQCHT_CLNTCONN               ,"MQCHT_CLNTCONN"},
  {MQCHT_SVRCONN                ,"MQCHT_SVRCONN"},
  {MQCHT_CLUSRCVR               ,"MQCHT_CLUSRCVR"},
  {MQCHT_CLUSSDR                ,"MQCHT_CLUSSDR"},
  {-1, ""}
};


/* For MQIA_PLATFORM */
static struct ConstDefinitions  FunTypes[] =
{
  {MQFUN_TYPE_UNKNOWN        ,"MQFUN_TYPE_UNKNOWN"},
  {MQFUN_TYPE_JVM            ,"MQFUN_TYPE_JVM"},
  {MQFUN_TYPE_PROGRAM        ,"MQFUN_TYPE_PROGRAM"},
  {MQFUN_TYPE_PROCEDURE      ,"MQFUN_TYPE_PROCEDURE"},
  {MQFUN_TYPE_USERDEF        ,"MQFUN_TYPE_USERDEF"},
  {MQFUN_TYPE_COMMAND        ,"MQFUN_TYPE_COMMAND"},
  {-1, ""}
};

/* For MQIACH_XMIT_PROTOCOL_TYPE */
static struct ConstDefinitions XpTypes[] =
{
  {MQXPT_ALL                 ,"MQXPT_ALL"},
  {MQXPT_DECNET              ,"MQXPT_DECNET"},
  {MQXPT_LOCAL               ,"MQXPT_LOCAL"},
  {MQXPT_LU62                ,"MQXPT_LU62"},
  {MQXPT_NETBIOS             ,"MQXPT_NETBIOS"},
  {MQXPT_SPX                 ,"MQXPT_SPX"},
  {MQXPT_TCP                 ,"MQXPT_TCP"},
  {MQXPT_UDP                 ,"MQXPT_UDP"},
  {-1, ""}  
};

/* For MQIACF_MSG_TYPE */
static struct ConstDefinitions MsgTypes[] =
{
  {MQMT_REQUEST              ,"MQMT_REQUEST"},
  {MQMT_REPLY                ,"MQMT_REPLY"},
  {MQMT_DATAGRAM             ,"MQMT_DATAGRAM"},
  {MQMT_REPORT               ,"MQMT_REPORT"},
  {MQMT_MQE_FIELDS_FROM_MQE  ,"MQMT_MQE_FIELDS_FROM_MQE"},
  {MQMT_MQE_FIELDS           ,"MQMT_MQE_FIELDS"},
  {-1,""}
};

/********************************************************************/
/* Structure: MonDefinitions                                        */
/*                                                                  */
/*   This structure is used to build tables used to convert PCF     */
/*   constants into text identifiers.                               */
/*                                                                  */
/********************************************************************/
struct MonDefinitions
{
  MQLONG Parameter;
  char *Identifier;
  struct ConstDefinitions *NamedValues;
};

struct MonDefinitions MonitoringByteStringFields[] =
{
  {MQBACF_CONNECTION_ID,     "ConnectionId", NULL},
  {MQBACF_MESSAGE_DATA,      "Message Data", NULL},
  {MQBACF_MSG_ID,            "Msg_id", NULL},
  {MQBACF_CORREL_ID,         "Correl_id", NULL},
  {MQBACF_MQMD_STRUCT,       "MQMD Structure", NULL},
  {MQBACF_MQGMO_STRUCT,      "MQGMO Structure", NULL},
  {MQBACF_MQPMO_STRUCT,      "MQPMO Structure", NULL},
  {MQBACF_MQCB_FUNCTION,     "Callback Function", NULL},
  {MQBACF_SUB_CORREL_ID,     "SUB_CORREL_ID"},
  {MQBACF_MQSTS_STRUCT ,     "MQSTS Structure"},
  {MQBACF_MQSD_STRUCT  ,     "MQSD Structure"},
  {MQBACF_XA_XID       ,     "XA_XID"},
  {MQBACF_ALTERNATE_SECURITYID,   "Alternate_security id", NULL},
  {MQBACF_MQCBC_STRUCT,      "MQCBC Structure", NULL},
  {MQBACF_MQCBD_STRUCT,      "MQCBD Structure", NULL},
  {MQBACF_MQCD_STRUCT,       "MQCD Structure", NULL},
  {MQBACF_MQCNO_STRUCT,      "MQCNO Structure", NULL},
  {MQBACF_GROUP_ID,          "GroupId", NULL},
  {MQBACF_ACCOUNTING_TOKEN,  "AccountingToken", NULL},
  {MQBACF_MQBO_STRUCT,       "MQBO Structure", NULL},
  {MQBACF_XQH_MSG_ID,        "Transmit Header Msg_id", NULL},
  {MQBACF_XQH_CORREL_ID,     "Transmit Header Correl_id", NULL}
};

struct MonDefinitions MonitoringIntegerFields[] =
{
  {MQIA_COMMAND_LEVEL,        "CommandLevel", NULL},
  {MQIACF_PROCESS_ID,         "ApplicationPid", NULL},
  {MQIACF_SEQUENCE_NUMBER,    "SeqNumber", NULL},
  {MQIACF_THREAD_ID,          "ApplicationTid", NULL},
  {MQIACF_HOBJ,               "Hobj", NULL},
  {MQIACF_CLOSE_OPTIONS,      "Close Options", NULL},
  {MQIACF_CONNECT_OPTIONS,    "Connect Options", NULL},
  {MQIACH_XMIT_PROTOCOL_TYPE, "Transport Type", XpTypes},
  {MQIACF_CTL_OPERATION,      "Control Operation", CtlOp},
  {MQIACF_OPERATION_ID,       "Operation Id", OperationId},
  {MQIACF_API_CALLER_TYPE,    "API Caller Type", ExitAPICaller},
  {MQIACF_API_ENVIRONMENT,    "API Environment", ExitEnvironment},
  {MQIA_APPL_TYPE,            "Application Type", AppType},
  {MQIA_PLATFORM,             "Platform", Platform},
  {MQIACF_COMP_CODE,          "Completion Code", CompCode},
  {MQIACF_MQCB_OPERATION,     "Callback Operation", CallbackOp},
  {MQIACF_MQCB_TYPE,          "Callback type", CallbackType},
  {MQIACF_CALL_TYPE,          "Call type", CallType},
  {MQIACF_MQCB_OPTIONS,       "Callback options",NULL},
  {MQIACF_SELECTOR_COUNT,     "Selector Count",NULL},
  {MQIACF_SELECTORS,          "Selectors",NULL},
  {MQIACF_INTATTR_COUNT,      "Int Attr Count",NULL},
  {MQIACF_INT_ATTRS,          "Int Attrs",NULL},
  {MQIACF_SUBRQ_ACTION,       "Sub Request Action",NULL},
  {MQIACF_NUM_PUBS,           "MQIACF_NUM_PUBS"},
  {MQIACF_HSUB,               "MQIACF_HSUB"},
  {MQIACF_SUBRQ_OPTIONS,      "MQIACF_SUBRQ_OPTIONS"},
  {MQIACF_SUB_OPTIONS,        "MQIACF_SUB_OPTIONS"},
  {MQIACF_NUM_PUBS,           "Num Pubs",NULL},
  {MQIACF_REASON_CODE,        "Reason Code", NULL},
  {MQIACF_TRACE_DETAIL,       "Trace Detail Level", NULL},
  {MQIACF_BUFFER_LENGTH,      "Buffer Length", NULL},
  {MQIACF_GET_OPTIONS,        "Get Options", NULL},
  {MQIACF_MSG_LENGTH,         "Msg length", NULL},
  {MQIACF_REPORT,             "Report Options", NULL},
  {MQIACF_MSG_TYPE,           "Msg_type", MsgTypes},
  {MQIACF_EXPIRY,             "Expiry", NULL},
  {MQIACF_PRIORITY,           "Priority", NULL},
  {MQIACF_PERSISTENCE,        "Persistence", NULL},
  {MQIA_CODED_CHAR_SET_ID,    "Coded_char_set_id", NULL},
  {MQIACF_ENCODING,           "Encoding", NULL},
  {MQIACF_OBJECT_TYPE,        "Object_type", ObjTypes},
  {MQIACF_OPEN_OPTIONS,       "Open_options", NULL},
  {MQIACF_RECS_PRESENT,       "Recs_present", NULL},
  {MQIACF_KNOWN_DEST_COUNT,   "Known_dest_count", NULL},
  {MQIACF_UNKNOWN_DEST_COUNT, "Unknown_dest_count", NULL},
  {MQIACF_INVALID_DEST_COUNT, "Invalid_dest_count", NULL},
  {MQIACF_RESOLVED_TYPE,      "Resolved_type", ObjTypes},
  {MQIACF_PUT_OPTIONS,        "Put Options", NULL},
  {MQIACH_MAX_MSG_LENGTH,     "Max message length", NULL},
  {MQIACF_XA_RMID,            "MQIACF_XA_RMID", NULL},
  {MQIACF_XA_FLAGS,           "MQIACF_XA_FLAGS", NULL},
  {MQIACF_XA_RETCODE,         "MQIACF_XA_RETCODE", NULL},
  {MQIACF_XA_HANDLE,          "MQIACF_XA_HANDLE"},
  {MQIACF_XA_RETVAL,          "MQIACF_XA_RETVAL"},
  {MQIACF_STATUS_TYPE,        "MQIACF_STATUS_TYPE"},
  {MQIACF_XA_COUNT,           "MQIACF_XA_COUNT"},
  {MQIACH_XMIT_PROTOCOL_TYPE, "Xmit Protocol", XpTypes},
  {MQIACF_TRACE_DATA_LENGTH,  "Trace Data Length", NULL},
  {MQIACF_FEEDBACK,           "Feedback", NULL},
  {MQIACF_POINTER_SIZE,       "Pointer size", NULL},
  {MQIACF_APPL_FUNCTION_TYPE, "Appl Function Type", FunTypes},
  {MQIACH_CHANNEL_TYPE,       "Channel Type", ChlTypes}
};

struct MonDefinitions MonitoringInteger64Fields[] =
{
  {MQIAMO64_HIGHRES_TIME,     "High Res Time", NULL}
};

struct MonDefinitions MonitoringStringFields[] =
{
  {MQCA_REMOTE_Q_MGR_NAME,        "RemoteQMgr", NULL},
  {MQCACF_APPL_NAME,              "ApplicationName", NULL},
  {MQCACF_USER_IDENTIFIER,        "UserId", NULL},
  {MQCACH_CONNECTION_NAME,        "ConnName", NULL},
  {MQCACH_CHANNEL_NAME,           "Channel Name", NULL},
  {MQCAMO_END_DATE,               "IntervalEndDate", NULL},
  {MQCAMO_END_TIME,               "IntervalEndTime", NULL},
  {MQCACF_OPERATION_DATE,         "OperationDate", NULL},
  {MQCACF_OPERATION_TIME,         "OperationTime", NULL},  
  {MQCAMO_START_DATE,             "IntervalStartDate", NULL},
  {MQCAMO_START_TIME,             "IntervalStartTime", NULL},
  {MQCA_Q_MGR_NAME,               "QueueManager", NULL},
  {MQCACF_RESOLVED_Q_NAME,        "Resolved_Q_Name", NULL},
  {MQCACH_FORMAT_NAME,            "Format_name", NULL},
  {MQCACF_REPLY_TO_Q,             "Reply_to_Q ", NULL},
  {MQCACF_REPLY_TO_Q_MGR,         "Reply_to_Q_Mgr", NULL},
  {MQCACF_PUT_DATE,               "Put_date", NULL},
  {MQCACF_PUT_TIME,               "Put_time", NULL},
  {MQCACF_OBJECT_NAME,            "Object_name", NULL},
  {MQCACF_OBJECT_Q_MGR_NAME,      "Object_Q_mgr_name", NULL},
  {MQCACF_DYNAMIC_Q_NAME,         "Dynamic_Q_name", NULL},
  {MQCACF_RESOLVED_LOCAL_Q_NAME,  "Resolved_local_Q_name", NULL},
  {MQCACF_RESOLVED_LOCAL_Q_MGR,   "Resolved_local_Q_mgr", NULL},
  {MQCACF_RESOLVED_Q_MGR,         "Resolved_Q_mgr", NULL},
  {MQCACF_OBJECT_STRING,          "Object_string", NULL},
  {MQCACF_SELECTION_STRING,       "Selection_string", NULL},
  {MQCACF_ALTERNATE_USERID,       "Alternate_userid", NULL},
  {MQCACF_RESOLVED_OBJECT_STRING, "Resolved_object_string", NULL},
  {MQCACF_MQCB_NAME,              "Callback name", NULL},
  {MQCACF_CHAR_ATTRS,             "Character Attributes", NULL},  
  {MQCACF_XA_INFO,                "XA Info", NULL},
  {MQCACF_SUB_NAME,               "Subscription Name", NULL},
  {MQCACF_SUB_USER_DATA,          "Subscription User Data", NULL},
  {MQCA_Q_NAME,                   "QueueName", NULL},
  {MQCA_POLICY_NAME,              "Protection Policy", NULL},
  {MQCACF_HOST_NAME,              "Host Name", NULL},
  {MQCACF_APPL_FUNCTION,          "Application Function", NULL},
  {MQCACF_XQH_REMOTE_Q_NAME,      "Transmit Header RemoteQName", NULL},
  {MQCACF_XQH_REMOTE_Q_MGR,       "Transmit Header RemoteQMgr", NULL},
  {MQCACF_XQH_PUT_DATE,           "Transmit Header Put_date", NULL},
  {MQCACF_XQH_PUT_TIME,           "Transmit Header Put_time", NULL}
};

struct MonDefinitions MonitoringGroupFields[] =
{
  {MQGACF_ACTIVITY_TRACE,  "MQI Operation"},
  {MQGACF_APP_DIST_LIST,   "Distribution List"}
};

#define printMonInteger(_indent, _parm, _value)                     \
{                                                                   \
  MQLONG i;                                                         \
  MQLONG tagId=-1;                                                  \
  struct ConstDefinitions *pDef;                                    \
  for (i=0; (i < (sizeof(MonitoringIntegerFields) /                 \
       sizeof(struct MonDefinitions))) && (tagId == -1); i++)       \
  {                                                                 \
    if (MonitoringIntegerFields[i].Parameter==(_parm))              \
    {                                                               \
      tagId=i;                                                      \
    }                                                               \
  }                                                                 \
  if (tagId != -1)                                                  \
  {                                                                 \
    if (MonitoringIntegerFields[tagId].NamedValues == NULL)         \
    {                                                               \
      printf("%s%s: %d\n",                                          \
             _indent,                                               \
             MonitoringIntegerFields[tagId].Identifier,             \
             (int)_value);                                          \
    }                                                               \
    else                                                            \
    {                                                               \
      pDef=MonitoringIntegerFields[tagId].NamedValues;              \
      for (;(pDef->Value != _value) && (pDef->Value != -1); pDef++) \
        ;                                                           \
      if (pDef->Value == _value)                                    \
      {                                                             \
        printf("%s%s: %s\n",                                        \
               _indent,                                             \
               MonitoringIntegerFields[tagId].Identifier,           \
               pDef->Identifier);                                   \
      }                                                             \
      else                                                          \
      {                                                             \
        printf("%s%s: %d\n",                                        \
               _indent,                                             \
               MonitoringIntegerFields[tagId].Identifier,           \
               (int)_value);                                        \
      }                                                             \
    }                                                               \
  }                                                                 \
  else                                                              \
  {                                                                 \
    printf("%s%d: %d\n",                                            \
           _indent,                                                 \
           (int)_parm,                                              \
           (int)_value);                                            \
  }                                                                 \
}

#define printMonIntegerList(_indent, _parm, _count, _values)        \
{                                                                   \
  MQLONG i, j;                                                      \
  MQLONG tagId=-1;                                                  \
  for (i=0; (i < (sizeof(MonitoringIntegerFields) /                 \
       sizeof(struct MonDefinitions))) && (tagId == -1); i++)       \
  {                                                                 \
    if (MonitoringIntegerFields[i].Parameter==(_parm))              \
    {                                                               \
      tagId=i;                                                      \
    }                                                               \
  }                                                                 \
  if (tagId != -1)                                                  \
  {                                                                 \
    printf("%s%s: [",                                               \
           _indent,                                                 \
           MonitoringIntegerFields[tagId].Identifier);              \
  }                                                                 \
  else                                                              \
  {                                                                 \
    printf("%s%d: [",                                               \
           _indent,                                                 \
           (int)_parm);                                             \
  }                                                                 \
  for (j=0; j < (_count); j++)                                      \
  {                                                                 \
    if (j == ((_count) -1))                                         \
    {                                                               \
      printf("%d]\n", (int)_values[j]);                             \
    }                                                               \
    else                                                            \
    {                                                               \
      printf("%d, ", (int)_values[j]);                              \
    }                                                               \
  }                                                                 \
}

#define printMonInteger64(_indent, _parm, _value)                   \
{                                                                   \
  MQLONG i;                                                         \
  MQLONG tagId=-1;                                                  \
  for (i=0; (i < (sizeof(MonitoringInteger64Fields) /               \
       sizeof(struct MonDefinitions))) && (tagId == -1); i++)       \
  {                                                                 \
    if (MonitoringInteger64Fields[i].Parameter==(_parm))            \
    {                                                               \
      tagId=i;                                                      \
    }                                                               \
  }                                                                 \
  if (tagId != -1)                                                  \
  {                                                                 \
    printf("%s%s: %lld\n",                                          \
           _indent,                                                 \
           MonitoringInteger64Fields[tagId].Identifier,             \
           _value);                                                 \
  }                                                                 \
  else                                                              \
  {                                                                 \
    printf("%s%d: %lld\n",                                          \
           _indent,                                                 \
           _parm,                                                   \
           _value);                                                 \
  }                                                                 \
}

#define printMonInteger64List(_indent, _parm, _count, _values)      \
{                                                                   \
  MQLONG i, j;                                                      \
  MQLONG tagId=-1;                                                  \
  for (i=0; (i < (sizeof(MonitoringInteger64Fields) /               \
       sizeof(struct MonDefinitions))) && (tagId == -1); i++)       \
  {                                                                 \
    if (MonitoringInteger64Fields[i].Parameter==(_parm))            \
    {                                                               \
      tagId=i;                                                      \
    }                                                               \
  }                                                                 \
  if (tagId != -1)                                                  \
  {                                                                 \
    printf("%s%s: [",                                               \
           _indent,                                                 \
           MonitoringInteger64Fields[tagId].Identifier);            \
  }                                                                 \
  else                                                              \
  {                                                                 \
    printf("%s%d: [",                                               \
           _indent,                                                 \
           _parm);                                                  \
  }                                                                 \
  for (j=0; j < (_count); j++)                                      \
  {                                                                 \
    if (j == ((_count) -1))                                         \
    {                                                               \
      printf("%lld]\n", _values[j]);                                \
    }                                                               \
    else                                                            \
    {                                                               \
      printf("%lld, ", _values[j]);                                 \
    }                                                               \
  }                                                                 \
}


#define printMonString(_indent, _parm, _len, _string)               \
{                                                                   \
  MQLONG i;                                                         \
  MQLONG tagId=-1;                                                  \
  MQLONG length=_len;                                               \
  for (i=0; (i < (sizeof(MonitoringStringFields) /                  \
       sizeof(struct MonDefinitions))) && (tagId == -1); i++)       \
  {                                                                 \
    if (MonitoringStringFields[i].Parameter==(_parm))               \
    {                                                               \
      tagId=i;                                                      \
    }                                                               \
  }                                                                 \
  for (length=_len-1;                                               \
       _string[length] == '\0' || _string[length] == ' ';           \
       length--);                                                   \
  if (tagId != -1)                                                  \
  {                                                                 \
    printf("%s%s: '%.*s'\n",                                        \
           _indent,                                                 \
           MonitoringStringFields[tagId].Identifier,                \
           (int)length+1,                                           \
           _string);                                                \
  }                                                                 \
  else                                                              \
  {                                                                 \
    printf("%s%d: '%.*s'\n",                                        \
           _indent,                                                 \
           (int)_parm,                                              \
           (int)length+1,                                           \
           _string);                                                \
  }                                                                 \
}

#define printMonStringList(_indent, _parm, _count, _len, _strings)  \
{                                                                   \
  MQLONG i, j;                                                      \
  MQLONG tagId=-1;                                                  \
  for (i=0; (i < (sizeof(MonitoringStringFields) /                  \
       sizeof(struct MonDefinitions))) && (tagId == -1); i++)       \
  {                                                                 \
    if (MonitoringStringFields[i].Parameter==(_parm))               \
    {                                                               \
      tagId=i;                                                      \
    }                                                               \
  }                                                                 \
  if (tagId != -1)                                                  \
  {                                                                 \
    printf("%s%s: [",                                               \
           _indent,                                                 \
           MonitoringStringFields[tagId].Identifier);               \
  }                                                                 \
  else                                                              \
  {                                                                 \
    printf("%s%d: [",                                               \
           _indent,                                                 \
           (int)_parm);                                             \
  }                                                                 \
  for (j=0; j < (_count); j++)                                      \
  {                                                                 \
    if (j == ((_count) -1))                                         \
    {                                                               \
      printf("'%.*s']\n", (int)_len, &(_strings[j * (_len)]));      \
    }                                                               \
    else                                                            \
    {                                                               \
      printf("'%.*s', ", (int)_len, &(_strings[j * (_len)]));       \
    }                                                               \
  }                                                                 \
  printf("]\n");                                                    \
}

#define printMonByteString(_indent, _parm, _len, _array)            \
{                                                                   \
  MQLONG i, j;                                                      \
  MQLONG tagId=-1;                                                  \
  MQCHAR hexline[80];                                               \
  for (i=0; (i < (sizeof(MonitoringByteStringFields) /              \
       sizeof(struct MonDefinitions))) && (tagId == -1); i++)       \
  {                                                                 \
    if (MonitoringByteStringFields[i].Parameter==(_parm))           \
    {                                                               \
      tagId=i;                                                      \
    }                                                               \
  }                                                                 \
  if (tagId != -1)                                                  \
  {                                                                 \
    printf("%s%s:",                                                 \
           _indent,                                                 \
           MonitoringByteStringFields[tagId].Identifier);           \
  }                                                                 \
  else                                                              \
  {                                                                 \
    printf("%s%d:",                                                 \
           _indent,                                                 \
           (int)_parm);                                             \
  }                                                                 \
  i=0;                                                              \
  do                                                                \
  {                                                                 \
    j=0;                                                            \
    printf("\n%s%08X: ",_indent, i);                                \
    while ( (j < 16) && (i < (_len)) )                              \
    {                                                               \
      if (j % 2 == 0)                                               \
        printf(" ");                                                \
      printf("%02X",_array[i] & 0xff);                              \
      hexline[j] = isprint(_array[i]) ? _array[i] : '.';            \
      j++;                                                          \
      i++;                                                          \
    }                                                               \
    if (j < 16)                                                     \
    {                                                               \
      for ( ;j < 16; j++)                                           \
      {                                                             \
        if (j % 2 == 0) printf(" ");                                \
          printf("  ");                                             \
        hexline[j] = ' ';                                           \
      }                                                             \
    }                                                               \
    hexline[j] = '\0';                                              \
    printf("  '%s'",hexline);                                       \
  } while(i<(_len));                                                \
  printf("\n");                                                     \
}

#define printMonGroup(_indent, _parm, _count)                       \
{                                                                   \
  MQLONG i;                                                         \
  MQLONG tagId=-1;                                                  \
  for (i=0; (i < (sizeof(MonitoringIntegerFields) /                 \
       sizeof(struct MonDefinitions))) && (tagId == -1); i++)       \
  {                                                                 \
    if (MonitoringGroupFields[i].Parameter==(_parm))                \
    {                                                               \
      tagId=i;                                                      \
    }                                                               \
  }                                                                 \
  if (tagId != -1)                                                  \
  {                                                                 \
    printf("%s%s: %d\n",                                            \
           _indent,                                                 \
           MonitoringGroupFields[tagId].Identifier,                 \
           (int)_count);                                            \
  }                                                                 \
  else                                                              \
  {                                                                 \
    printf("%sGROUP(%d): %d\n",                                     \
           _indent,                                                 \
           (int)_parm,                                              \
           (int)_count);                                            \
  }                                                                 \
}

/********************************************************************/
/*                                                                  */
/* Function: printMonitoring                                        */
/*                                                                  */
/*                                                                  */
/*   This function translates a message buffer containing an        */
/*   activity trace message as written by Websphere MQ              */
/*   and writes the formatted data to standard output.              */
/*                                                                  */
/********************************************************************/
int printMonitoring(MQMD *pmd,
                    MQBYTE *buffer,
                    MQLONG buflen,
                    MQLONG Verbose,
                    MQLONG RecordNum)
{
  int frc=0;
  int i=0;
  PMQCFH pcfh;
  char underline[130];                    /* Underline string        */
  char conn[9];

  /******************************************************************/
  /* First check the format of the message to ensure it is of a     */
  /* valid type for us to start processing.                         */
  /******************************************************************/
  if (memcmp(pmd->Format, MQFMT_ADMIN, sizeof(pmd->Format)) != 0)
  {
    fprintf(stderr, "Invalid monitoring record 'md.Format' = %8.8s.\n",
            pmd->Format);
    return -1;
  }

  /******************************************************************/
  /* Gain access to the PCF header and check the definitions to     */
  /* ensure this is indeed an monitoring PCF record.                */
  /******************************************************************/
  pcfh=(PMQCFH)buffer;

  if ((pcfh->Type != MQCFT_APP_ACTIVITY))
  {
    fprintf(stderr, "Invalid monitoring record 'cfh.Type' = %d.\n",
            (int)pcfh->Type);
    return -1;
  }

  buffer+=sizeof(MQCFH);
  switch (pcfh->Command)
  {
  case MQCMD_ACTIVITY_TRACE:
    printf("MonitoringType: MQI Activity Trace RecordNum: %d\n", RecordNum);
    /* Print message correlID*/
    for (i=0;i<8;i++)
       conn[i]=pmd->CorrelId[i+16]; 

    printMonByteString("", 
                       MQBACF_CORREL_ID,
                       MQ_CORREL_ID_LENGTH,
                       pmd->CorrelId);
    frc=printMonitoringRecord(pcfh->ParameterCount,
                              0,
                              &buffer,
                              &buflen,
                              Verbose,
                              RecordNum,
                              conn);
    break;
  default:
    fprintf(stderr, "Invalid monitoring record 'cfh.Command' = %d.\n",
            (int)pcfh->Command);
    break;
  }

  memset(underline, '=', sizeof(underline)-1);
  underline[sizeof(underline)-1]='\0';
  printf("%s\n", underline);  
  printf("\n");

  return frc;
}

/********************************************************************/


/********************************************************************/
/*                                                                  */
/* Function: getMonInteger                                          */
/*                                                                  */
/*   This function works out the string value of an integer parm.   */
/*                                                                  */
/********************************************************************/
char * getMonInteger(MQLONG _parm, 
                     MQLONG _value, 
                     MQCHAR *buffer, 
                     MQLONG buflen)                     
{
  MQLONG i;                                                         
  MQLONG tagId=-1;                                           
  struct ConstDefinitions *pDef;                             

  memset(buffer,0,buflen);
  for (i=0; (i < (sizeof(MonitoringIntegerFields) /                 
                  sizeof(struct MonDefinitions))) && (tagId == -1); i++)
  {
    if (MonitoringIntegerFields[i].Parameter==(_parm))
    {
      tagId=i;                                                      
    }
  }                                                                 
  if (tagId != -1)
  {
    if (MonitoringIntegerFields[tagId].NamedValues == NULL)
    {
      sprintf(buffer,"%s:%02d",
              MonitoringIntegerFields[tagId].Identifier, (int)_value); 
    }
    else
    {
      pDef=MonitoringIntegerFields[tagId].NamedValues;              
      for (;(pDef->Value != _value) && (pDef->Value != -1); pDef++)
        ;                                                           
      if (pDef->Value == _value)
      {
        sprintf(buffer,"%s",
                pDef->Identifier);
      }
      else
      {
        sprintf(buffer,"%s:%0d",
                MonitoringIntegerFields[tagId].Identifier, (int)_value); 
      }                                                             
    }                                                               
  }
  else
  {
    sprintf(buffer,"%d:%02d", 
            (int)_parm,                                                   
            (int)_value);                                                 
  }    
  return buffer;
}

/********************************************************************/
/*                                                                  */
/* Function: printMonitoringRecord                                  */
/*                                                                  */
/*                                                                  */
/*   This function prints out the contents of a message buffer      */
/*   containing MQI activity trace records.                         */
/*                                                                  */
/********************************************************************/
int printMonitoringRecord(MQLONG parameterCount,
                          MQLONG indentCount,
                          MQBYTE **ppbuffer,
                          MQLONG *pbuflen,
                          MQLONG Verbose,
                          MQLONG RecordNum,
                          MQCHAR *conn)
{
  int i;
  int frc = 0;                        /* Function return code       */
  int rc = 0;                         /* Internal return code       */
  int groupCount=0;                   /* Group counter              */
  char indent[21];                    /* indentString               */
  MQBYTE *ptr = NULL;                 /* Current buffer pointer     */
  MQLONG bytesLeft = 0;               /* Number of remaining bytes  */
  MQLONG item_count = 0;              /* Parameter counter          */
  MQLONG Type = 0;                    /* Type of next structure     */
  MQLONG Length = 0;                  /* Length of next structure   */
  MQLONG Parameter = 0 ;              /* Type of next parameter     */
  MQLONG StringLength = 0 ;           /* Type of next parameter     */
  MQLONG Count = 0 ;                  /* Type of next parameter     */
  MQINT64 Value64 = 0;                /* 64 bit value               */
  MQLONG  Value32 = 0;                /* 32 bit value               */
  MQCHAR * StringData = NULL;         /* String value               */
  MQCHAR QmgrName[MQ_Q_MGR_NAME_LENGTH+1];
  MQCHAR ChannelName[MQ_CHANNEL_NAME_LENGTH+1];   /* String value               */
  MQCHAR ApplicationName[MQ_APPL_NAME_LENGTH+1];  /* String value               */
  MQCHAR UserId[MQ_USER_ID_LENGTH+1];   /* String value               */
  MQLONG ChannelNameLength = 0;
  MQLONG * Values32 = NULL;           /* 32 bit integer values      */
  MQLONG ParameterCount = 0 ;         /* Parameter count in group   */
  MQLONG pid = 0;
  MQLONG MQICt = 0;
  ObjTrackerItem *ObjTrackerTemp; 
  ObjTrackerItem *ObjTrackerTemp2; 
  ChlTrackerItem *ChlTrackerTemp;     
  ChlTrackerItem *ChlTrackerTemp2;
  OprTrackerItem *OprTrackerTemp;
  OprTrackerItem *OprTrackerTemp2;
  TidTrackerItem *TidTrackerTemp;
  TidTrackerItem *TidTrackerTemp2;
  OptTrackerItem *OptTrackerTemp;
  OptTrackerItem *OptTrackerTemp2;
  ReasonTrackerItem *ReasonTrackerTemp;
  ReasonTrackerItem *ReasonTrackerTemp2;
  
  memset( QmgrName, '\0', sizeof(QmgrName));
  memset( ChannelName, '\0', sizeof(ChannelName));
  memset( ApplicationName, '\0', sizeof(ApplicationName));
  memset( UserId, '\0', sizeof(UserId));

  /*****************************************************************/
  /* Set global list pointers to NULL so temp lists can be built   */
  /* and used.                                                     */
  /*****************************************************************/
  ObjTrackerHead=NULL;
  ObjTrackerCurr=NULL;
  ChlTrackerHead=NULL;
  ChlTrackerCurr=NULL;
  OprTrackerHead=NULL;
  OprTrackerCurr=NULL;
  TidTrackerHead=NULL;
  TidTrackerCurr=NULL;
  ReasonTrackerHead=NULL;
  ReasonTrackerCurr=NULL;

  if (indentCount <= (sizeof(indent)-1))
  {
    memset(indent, ' ', indentCount);
    indent[indentCount]='\0';
  }
  else
  {
    memset(indent, ' ', (sizeof(indent)-1));
    indent[sizeof(indent)-1]='\0';
  }

  bytesLeft=*pbuflen;
  ptr=*ppbuffer;
  for (item_count=0; (frc == 0) && (item_count < parameterCount); item_count++)
  {
    /****************************************************************/
    /* The first 12 bytes of every PCF structure contain its type,  */
    /* length and parameter ID.                                     */
    /****************************************************************/
    if (bytesLeft < (sizeof(MQLONG) * 3))
    {
      fprintf(stderr, 
              "Premature end of buffer before processing complete.\n");
      frc=-1;
      break;
    }

    memcpy(&Type, (ptr + offsetof(MQCFIN, Type)), sizeof(MQLONG));
    memcpy(&Length, (ptr + offsetof(MQCFIN, StrucLength)), sizeof(MQLONG));
    memcpy(&Parameter, (ptr + offsetof(MQCFIN, Parameter)), sizeof(MQLONG));

    if (bytesLeft < Length)
    {
      fprintf(stderr, 
              "Premature end of buffer before processing complete.\n");
      frc=-1;
      break;
    }

    if (Parameter == MQIACF_PROCESS_ID)
       memcpy(&pid, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));

    if (Parameter == MQCA_Q_MGR_NAME)
       {
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_Q_MGR_NAME_LENGTH)
           {
            for (i=0; (i < MQ_Q_MGR_NAME_LENGTH) && (StringData[i] != ' '); i++)
              QmgrName[i]=StringData[i];
           }
       }

    if (Parameter == MQCACH_CHANNEL_NAME)
       {
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_CHANNEL_NAME_LENGTH)
           {
            for (i=0; (i < MQ_CHANNEL_NAME_LENGTH) && (StringData[i] != ' '); i++)           
              ChannelName[i]=StringData[i];
           }   
       }

    if (Parameter == MQCACF_APPL_NAME)
       {
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_APPL_NAME_LENGTH)
           {
            strncpy(ApplicationName,StringData,StringLength);
            ApplicationName[StringLength]='\0';
            for (i = StringLength-1; (i >= 0) && (ApplicationName[i] == ' '); i--)
              ApplicationName[i]='\0';
           }
       }

    if (Parameter == MQCACF_USER_IDENTIFIER)
       {
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_USER_ID_LENGTH)
           {
            strncpy(UserId,StringData,StringLength);
            UserId[StringLength]='\0';
            for (i = StringLength-1; (i >= 0) && (UserId[i] == ' '); i--)
              UserId[i]='\0';
           }
       }

    switch (Type)
    {
    case MQCFT_INTEGER:
      memcpy(&Value32, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
 
      printMonInteger(indent,
                      Parameter,
                      Value32);

      bytesLeft-=Length;
      ptr+=Length;
      break;

    case MQCFT_INTEGER64:
      memcpy(&Value64, (ptr + offsetof(MQCFIN64, Value)), sizeof(MQINT64));

      printMonInteger64(indent,
                        Parameter,
                        Value64);

      bytesLeft-=Length;
      ptr+=Length;
      break;

    case MQCFT_STRING:
      memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
      StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));

      printMonString(indent,
                     Parameter,
                     StringLength,
                     StringData);

      bytesLeft-=Length;
      ptr+=Length;
      break;

    case MQCFT_INTEGER_LIST:
      memcpy(&Count, (ptr + offsetof(MQCFIL, Count)), sizeof(MQLONG));
      Values32 = (MQLONG *)malloc(sizeof(MQLONG) * Count);
      if(Values32)
      {
        memcpy(Values32, (ptr + offsetof(MQCFIL, Values)), sizeof(MQLONG) * Count);
  
        printMonIntegerList(indent,
                            Parameter,
                            Count,
                            Values32);
        free(Values32);
        Values32 = NULL;
      }
      else
      {
        fprintf(stderr, "Unable to allocate storage for integer list (%d/%d).\n",
                Count, Parameter);
        frc=-1;
      }
      bytesLeft-=Length;
      ptr+=Length;
      break;

    case MQCFT_STRING_LIST:
      memcpy(&Count, (ptr + offsetof(MQCFSL, Count)), sizeof(MQLONG));
      memcpy(&StringLength, (ptr + offsetof(MQCFSL, StringLength)), sizeof(MQLONG));
      StringData = (MQCHAR *)(ptr + offsetof(MQCFSL, Strings));
      printMonStringList(indent,
                         Parameter,
                         Count,
                         StringLength,
                         StringData);

      bytesLeft-=Length;
      ptr+=Length;
      break;

    case MQCFT_BYTE_STRING:
      memcpy(&StringLength, (ptr + offsetof(MQCFBS, StringLength)), sizeof(MQLONG));
      StringData = (MQCHAR *)(ptr + offsetof(MQCFBS, String));

      printMonByteString(indent,
                         Parameter,
                         StringLength,
                         StringData);

      bytesLeft-=Length;
      ptr+=Length;
      break;

    case MQCFT_GROUP:
      rc = 0;
      memcpy(&ParameterCount, (ptr + offsetof(MQCFGR, ParameterCount)), sizeof(MQLONG));
      if (Verbose)
      {
        printMonGroup(indent, Parameter, groupCount);
      }
      groupCount++;
      bytesLeft-=Length;
      ptr+=Length;
      if (Verbose)
      {
        printMonitoringRecord(ParameterCount,
                              indentCount+2,
                              &ptr,
                              &bytesLeft,
                              Verbose,
                              RecordNum,
                              conn);
      }
      else
      {
        MQICt++;
        printTerseTraceLine(ParameterCount,
                            indentCount+2,
                            &ptr,
                            &bytesLeft,
                            pid,
                            RecordNum,
                            QmgrName,
                            ChannelName,
                            ApplicationName,
                            UserId, 
                            conn);

      }
      break;

    default:
      fprintf(stderr, "Error processing unknown PCF structure (%d)\n", 
              (int)Type);
      break;
    }
  }

  *ppbuffer=ptr;
  *pbuflen=bytesLeft;

  if (Report)
  {
    addPidTracker(pid,QmgrName,ApplicationName,UserId,MQICt);

    ObjTrackerTemp=ObjTrackerHead;
    ObjTrackerHead=PidTrackerCurr->ObjTrackerHead;
    ObjTrackerCurr=PidTrackerCurr->ObjTrackerCurr; 
    while (ObjTrackerTemp != NULL)
    {
      addObjTracker(ObjTrackerTemp->ObjName,ObjTrackerTemp->ObjCt);

      if (ObjTrackerTemp->OptTrackerHead != NULL)
      {
        OptTrackerTemp=ObjTrackerTemp->OptTrackerHead;
        OptTrackerHead=ObjTrackerCurr->OptTrackerHead;
        OptTrackerCurr=ObjTrackerCurr->OptTrackerCurr;
        while (OptTrackerTemp != NULL)
        {      
          addOptTracker(OptTrackerTemp->OptType,OptTrackerTemp->Opt,OptTrackerTemp->OptCt);
          OptTrackerTemp2=OptTrackerTemp->nextItem;
          free(OptTrackerTemp);
          OptTrackerTemp=OptTrackerTemp2; 
        }
        ObjTrackerCurr->OptTrackerHead=OptTrackerHead;
        ObjTrackerCurr->OptTrackerCurr=OptTrackerCurr; 
      }

      if (ObjTrackerTemp->OprTrackerHead != NULL)
      {
        OprTrackerHoldHead=OprTrackerHead;
        OprTrackerHoldCurr=OprTrackerCurr;
        OprTrackerTemp=ObjTrackerTemp->OprTrackerHead;
        OprTrackerHead=ObjTrackerCurr->OprTrackerHead;
        OprTrackerCurr=ObjTrackerCurr->OprTrackerCurr;
        while (OprTrackerTemp != NULL)
        {
          addOprTracker(OprTrackerTemp->Operation,OprTrackerTemp->OprCt,OprTrackerTemp->NonPrstCt,OprTrackerTemp->NonPrstMsgLgth,OprTrackerTemp->PrstCt,OprTrackerTemp->PrstMsgLgth,OprTrackerTemp->DfltPrstCt,OprTrackerTemp->DfltPrstMsgLgth,OprTrackerTemp->NAPrstCt,OprTrackerTemp->NAPrstMsgLgth);
          OprTrackerTemp2=OprTrackerTemp->nextItem;
          free(OprTrackerTemp);
          OprTrackerTemp=OprTrackerTemp2;
        }
        ObjTrackerCurr->OprTrackerHead=OprTrackerHead;
        ObjTrackerCurr->OprTrackerCurr=OprTrackerCurr;
        OprTrackerHead=OprTrackerHoldHead;
        OprTrackerCurr=OprTrackerHoldCurr;
      }

      ObjTrackerTemp2=ObjTrackerTemp->nextItem;
      free(ObjTrackerTemp);
      ObjTrackerTemp=ObjTrackerTemp2;
    }      
    PidTrackerCurr->ObjTrackerHead=ObjTrackerHead;
    PidTrackerCurr->ObjTrackerCurr=ObjTrackerCurr;

    ChlTrackerTemp=ChlTrackerHead;
    ChlTrackerHead=PidTrackerCurr->ChlTrackerHead;
    ChlTrackerCurr=PidTrackerCurr->ChlTrackerCurr;
    while (ChlTrackerTemp != NULL)
    {
      addChlTracker(ChlTrackerTemp->ChannelName,ChlTrackerTemp->ChlCt);
      ChlTrackerTemp2=ChlTrackerTemp->nextItem;
      free(ChlTrackerTemp); 
      ChlTrackerTemp=ChlTrackerTemp2;
    }
    PidTrackerCurr->ChlTrackerHead=ChlTrackerHead;
    PidTrackerCurr->ChlTrackerCurr=ChlTrackerCurr;

    OprTrackerTemp=OprTrackerHead;
    OprTrackerHead=PidTrackerCurr->OprTrackerHead;
    OprTrackerCurr=PidTrackerCurr->OprTrackerCurr;
    while (OprTrackerTemp != NULL)
    {
      addOprTracker(OprTrackerTemp->Operation,OprTrackerTemp->OprCt,OprTrackerTemp->NonPrstCt,OprTrackerTemp->NonPrstMsgLgth,OprTrackerTemp->PrstCt,OprTrackerTemp->PrstMsgLgth,OprTrackerTemp->DfltPrstCt,OprTrackerTemp->DfltPrstMsgLgth,OprTrackerTemp->NAPrstCt,OprTrackerTemp->NAPrstMsgLgth);

      if (OprTrackerTemp->OptTrackerHead != NULL)
      {
        OptTrackerTemp=OprTrackerTemp->OptTrackerHead;
        OptTrackerHead=OprTrackerCurr->OptTrackerHead;
        OptTrackerCurr=OprTrackerCurr->OptTrackerCurr;
        while (OptTrackerTemp != NULL)
        {     
          addOptTracker(OptTrackerTemp->OptType,OptTrackerTemp->Opt,OptTrackerTemp->OptCt);
          OptTrackerTemp2=OptTrackerTemp->nextItem;
          free(OptTrackerTemp);
          OptTrackerTemp=OptTrackerTemp2;
        }
        OprTrackerCurr->OptTrackerHead=OptTrackerHead; 
        OprTrackerCurr->OptTrackerCurr=OptTrackerCurr; 
      }

      if (OprTrackerTemp->ReasonTrackerHead != NULL)
      {
        ReasonTrackerTemp=OprTrackerTemp->ReasonTrackerHead;
        ReasonTrackerHead=OprTrackerCurr->ReasonTrackerHead;
        ReasonTrackerCurr=OprTrackerCurr->ReasonTrackerCurr;
        while (ReasonTrackerTemp != NULL)
        {
          addReasonTracker(ReasonTrackerTemp->Reason,ReasonTrackerTemp->ReasonCt);
          ReasonTrackerTemp2=ReasonTrackerTemp->nextItem;
          free(ReasonTrackerTemp);
          ReasonTrackerTemp=ReasonTrackerTemp2;
        }
        OprTrackerCurr->ReasonTrackerHead=ReasonTrackerHead;
        OprTrackerCurr->ReasonTrackerCurr=ReasonTrackerCurr;
      }

      OprTrackerTemp2=OprTrackerTemp->nextItem;
      free(OprTrackerTemp);
      OprTrackerTemp=OprTrackerTemp2;
    }
    PidTrackerCurr->OprTrackerHead=OprTrackerHead;
    PidTrackerCurr->OprTrackerCurr=OprTrackerCurr;

    TidTrackerTemp=TidTrackerHead;
    TidTrackerHead=PidTrackerCurr->TidTrackerHead;
    TidTrackerCurr=PidTrackerCurr->TidTrackerCurr;
    while (TidTrackerTemp != NULL)
    {
      addTidTracker(TidTrackerTemp->tid);
      TidTrackerTemp2=TidTrackerTemp->nextItem;
      free(TidTrackerTemp);
      TidTrackerTemp=TidTrackerTemp2;
    }
    PidTrackerCurr->TidTrackerHead=TidTrackerHead;
    PidTrackerCurr->TidTrackerCurr=TidTrackerCurr;

  }

 
  return 0;
}

/********************************************************************/
/*                                                                  */
/* Function: addPidTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function adds a PidTracker item to the link list if the   */
/*   item does not currently exist.                                 */
/*                                                                  */
/********************************************************************/
int addPidTracker(MQLONG pid,
                  char *QmgrName,
                  char *ApplicationName,
                  char *UserId,
                  MQLONG MQICt)
{
  PidTrackerItem *PidTrackerTemp=NULL;
  PidTrackerItem *PidTrackerTemp2=NULL;
  int i;

  /*******************************************************************/
  /* Check if our PidTrackerCurr is a match, and get out, if so      */ 
  /*******************************************************************/
  if (PidTrackerCurr != NULL) 
    if (PidTrackerCurr->pid == pid && 
        !strcmp(PidTrackerCurr->QmgrName,QmgrName) &&
        !strcmp(PidTrackerCurr->ApplicationName,ApplicationName) &&
        !strcmp(PidTrackerCurr->UserId,UserId))
    {
      PidTrackerCurr->MQICt=PidTrackerCurr->MQICt+MQICt; 
      return 0;
    }

  /*******************************************************************/
  /* Check if our pid is included in the PidTracker list, and get    */
  /* out, if so. If not, build new item and add sorted by pid in list*/ 
  /*******************************************************************/
  if (PidTrackerHead != NULL)
  {
    PidTrackerTemp=PidTrackerHead;
    while (PidTrackerTemp != NULL)
    {
      if (PidTrackerTemp->pid == pid &&
          !strcmp(PidTrackerTemp->QmgrName,QmgrName) &&
          !strcmp(PidTrackerTemp->ApplicationName,ApplicationName) &&
          !strcmp(PidTrackerTemp->UserId,UserId))
      {
        PidTrackerCurr=PidTrackerTemp;
        PidTrackerCurr->MQICt=PidTrackerCurr->MQICt+MQICt;
        return 0;
      }

      /*******************************************************************/
      /* If our current PidTracker is > inputs, we need to create        */
      /* a new list item into our list.                                  */
      /*******************************************************************/
      if ((strcmp(PidTrackerTemp->QmgrName,QmgrName) > 0) ||

          (!strcmp(PidTrackerTemp->QmgrName,QmgrName) &&
           PidTrackerTemp->pid > pid) ||

          (!strcmp(PidTrackerTemp->QmgrName,QmgrName) &&
           PidTrackerTemp->pid == pid &&
           strcmp(PidTrackerTemp->ApplicationName,ApplicationName) > 0) ||

          (!strcmp(PidTrackerTemp->QmgrName,QmgrName) &&
           PidTrackerTemp->pid == pid &&
           !strcmp(PidTrackerTemp->ApplicationName,ApplicationName) &&
           strcmp(PidTrackerTemp->UserId,UserId) > 0))
      {
        crtPidTracker(pid,QmgrName,ApplicationName,UserId,MQICt);

        /*******************************************************************/
        /* prevItem NULL means our current list item is the head and we    */
        /* should insert out new item at the beginning of the list.        */
        /*******************************************************************/
        if (PidTrackerTemp->prevItem == NULL)
        {
          PidTrackerHead=PidTrackerCurr;
          PidTrackerTemp->prevItem=PidTrackerHead;
          PidTrackerHead->prevItem=NULL;
          PidTrackerHead->nextItem=PidTrackerTemp;                              
          PidTrackerTemp=NULL;
        }
        /*******************************************************************/
        /* else insert item in middle of list                              */
        /*******************************************************************/
        else
        {
          PidTrackerTemp2=PidTrackerTemp->prevItem;
          PidTrackerTemp2->nextItem=PidTrackerCurr;
          PidTrackerTemp->prevItem=PidTrackerCurr;
          PidTrackerCurr->prevItem=PidTrackerTemp2;
          PidTrackerCurr->nextItem=PidTrackerTemp;
          PidTrackerTemp=NULL;
        }  /* if (PidTrackerTemp->prevItem == NULL) */ 
      }
      else
      {
        /*******************************************************************/
        /* nextItem NULL means we are at the end of the list and we should */
        /* insert a new item at the end of the list.                       */
        /*******************************************************************/
        if (PidTrackerTemp->nextItem == NULL)
        {
          crtPidTracker(pid,QmgrName,ApplicationName,UserId,MQICt);
          PidTrackerCurr->prevItem=PidTrackerTemp;
          PidTrackerCurr->nextItem=NULL;
          PidTrackerTemp->nextItem=PidTrackerCurr;
          PidTrackerTemp=NULL;  
        }
        /*******************************************************************/
        /* else we have more items to search in our list                   */
        /*******************************************************************/
        else
        {
          PidTrackerTemp2=PidTrackerTemp->nextItem;
          PidTrackerTemp=PidTrackerTemp2;
        }  /* if (PidTrackerTemp->nextItem == NULL) */
      }  /* if (PidTrackerTemp->pid > pid) */ 
    }  /* while (PidTrackerTemp != NULL) */
  }
  else
  /*******************************************************************/
  /* First time - allocate list, update item, and get out.           */
  /*******************************************************************/
  {
    crtPidTracker(pid,QmgrName,ApplicationName,UserId,MQICt);
    PidTrackerHead=PidTrackerCurr;
    return 0;
  }  /* if (PidTrackerHead != NULL) */ 

  return 0;

}


/********************************************************************/
/*                                                                  */
/* Function: crtPidTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function creates a PidTracker item.                       */
/*   The global variable PidTrackerCurr will be used for the return */
/*   item.                                                          */
/*                                                                  */
/********************************************************************/
int crtPidTracker(MQLONG pid,
                  char *QmgrName,
                  char *ApplicationName,
                  char *UserId,
                  MQLONG MQICt)
{
  int i;

  PidTrackerCurr=(PidTrackerItem *)malloc(sizeof(PidTrackerItem));
  if (PidTrackerCurr == NULL)
  {
    fprintf(stderr, "Failed to allocate memory(%d) for PidTracker List\n",
            (int)sizeof(PidTrackerItem));
    exit(-1);
  }
  PidTrackerCurr->prevItem=NULL;
  PidTrackerCurr->nextItem=NULL;
  PidTrackerCurr->pid=pid;
  PidTrackerCurr->MQICt=MQICt;

  for (i=0;i < MQ_Q_MGR_NAME_LENGTH;i++)
     PidTrackerCurr->QmgrName[i]=QmgrName[i];
  PidTrackerCurr->QmgrName[MQ_Q_MGR_NAME_LENGTH]='\0';

  for (i=0;i < MQ_APPL_NAME_LENGTH;i++)
     PidTrackerCurr->ApplicationName[i]=ApplicationName[i];
  PidTrackerCurr->ApplicationName[MQ_APPL_NAME_LENGTH]='\0';

  for (i=0;i < MQ_USER_ID_LENGTH;i++)
     PidTrackerCurr->UserId[i]=UserId[i];
  PidTrackerCurr->UserId[MQ_USER_ID_LENGTH]='\0';

  PidTrackerCurr->ObjTrackerHead=NULL;
  PidTrackerCurr->ObjTrackerCurr=NULL;
  PidTrackerCurr->ChlTrackerHead=NULL;
  PidTrackerCurr->ChlTrackerCurr=NULL;
  PidTrackerCurr->OprTrackerHead=NULL;
  PidTrackerCurr->OprTrackerCurr=NULL;
  PidTrackerCurr->TidTrackerHead=NULL;
  PidTrackerCurr->TidTrackerCurr=NULL;

  return 0;
}


/********************************************************************/
/*                                                                  */
/* Function: printTerseTraceLine                                    */
/*                                                                  */
/*                                                                  */
/*   This function prints out a single line of trace for an MQI     */
/*   operation                                                      */
/*                                                                  */
/********************************************************************/
int printTerseTraceLine(MQLONG parameterCount,
                        MQLONG indentCount,
                        MQBYTE **ppbuffer,
                        MQLONG *pbuflen,
                        MQLONG pid,
                        MQLONG RecordNum,
                        MQCHAR *QmgrName,
                        MQCHAR *ChannelName,
                        MQCHAR *ApplicationName,
                        MQCHAR *UserId,
                        MQCHAR *conn)
{
  MQLONG i;
  int frc = 0;                        /* Function return code       */
  char indent[21];                    /* indentString               */
  MQBYTE *ptr = NULL;                 /* Current buffer pointer     */
  MQLONG bytesLeft = 0;               /* Number of remaining bytes  */
  MQLONG count = 0;                   /* Parameter counter          */
  MQLONG Type = 0;                    /* Type of next structure     */
  MQLONG Length = 0;                  /* Length of next structure   */
  MQLONG Parameter = 0;               /* Type of next parameter     */
  MQLONG ParameterCount = 0 ;         /* Parameter count in group   */
  MQLONG StringLength = 0 ;           /* Type of next parameter     */
  MQLONG  Value32 = 0;                /* 32 bit value               */
  MQCHAR operation[128];
  MQLONG tid = 0;
  MQCHAR operationDate[MQ_DATE_LENGTH+1];
  MQCHAR operationTime[MQ_TIME_LENGTH+1];
  MQCHAR CompCode[128];                /* Completion Code            */
  MQCHAR * StringData = NULL;         /* String value               */
  MQLONG ReasonCode = 0;               /* Reason Code                */
  MQLONG HObj = MQHO_UNUSABLE_HOBJ;    /* Object Handle              */
  MQCHAR ObjName[MQ_OBJECT_NAME_LENGTH+1]; /* Object Name            */
  MQCHAR ObjQmgrName[MQ_Q_MGR_NAME_LENGTH+1]; 
  MQCHAR ResolvedQueueName[MQ_OBJECT_NAME_LENGTH+1]; 
  MQCHAR ResolvedQmgrName[MQ_Q_MGR_NAME_LENGTH+1];
  MQCHAR ResLclQueueName[MQ_OBJECT_NAME_LENGTH+1];
  MQCHAR ResLclQmgrName[MQ_Q_MGR_NAME_LENGTH+1];
  MQCHAR ReplyToQueueName[MQ_OBJECT_NAME_LENGTH+1];
  MQCHAR ReplyToQmgrName[MQ_Q_MGR_NAME_LENGTH+1];
  MQCHAR MsgId[MQ_MSG_ID_LENGTH+1];
  MQCHAR CorrelId[MQ_CORREL_ID_LENGTH+1]; 
  MQCHAR buffer[1024];
  MQCHAR * pMessageData;
  MQLONG MessageDataLgth;
  char *EYEC = "1LS="; 
  char underline[130];                    /* Underline string         */
  MQINT64 HighResTime = 0;
  MQLONG TempCt = 1;
  MQLONG OptType = 0;
  MQLONG Priority=0;
  MQLONG HoldPrst=0;
  MQLONG ReportOptions=0;
  MQLONG Expiry=0;
  MQLONG HoldMsgLgth=0;
  MQLONG CCSID=0;
  MQLONG Encoding=0;
  MQLONG NonPrstCt = 0;
  MQLONG NonPrstMsgLgth = 0;
  MQLONG PrstCt = 0;
  MQLONG PrstMsgLgth = 0;
  MQLONG DfltPrstCt = 0;
  MQLONG DfltPrstMsgLgth = 0;
  MQLONG NAPrstCt = 0;
  MQLONG NAPrstMsgLgth = 0;
  char HighResTimeFindCd='N';
  char PriorityFindCd='N';
  char PrstFindCd='N'; 
  char ReportOptionsFindCd='N';
  char ExpiryFindCd='N';
  char MsgLgthFindCd='N';
  char CCSIDFindCd='N';
  char EncodingFindCd='N';
  char ConnOptFindCd='N';
  char OpenOptFindCd='N';
  char GetOptFindCd='N';
  char PutOptFindCd='N';
  char CloseOptFindCd='N';
  char CBOptFindCd='N';
  char SubOptFindCd='N';
  char SubRqOptFindCd='N';
  char MsgIdFindCd='N';
  char CorrelIdFindCd='N';
  char MessageDataFindCd='N';
  char ObjQmgrNameFindCd='N';
  char ResolvedQueueNameFindCd='N';
  char ResolvedQmgrNameFindCd='N';
  char ResLclQueueNameFindCd='N';
  char ResLclQmgrNameFindCd='N';
  char ReplyToQueueNameFindCd='N';
  char ReplyToQmgrNameFindCd='N';
  MQLONG ConnOpt;
  MQLONG OpenOpt;
  MQLONG GetOpt;
  MQLONG PutOpt;
  MQLONG CloseOpt;
  MQLONG CBOpt;
  MQLONG SubOpt;
  MQLONG SubRqOpt;

  memset( ObjName, '\0', sizeof(ObjName));
  memset( ObjQmgrName, '\0', sizeof(ObjQmgrName));
  memset( ResolvedQueueName, '\0', sizeof(ResolvedQueueName));
  memset( ResolvedQmgrName, '\0', sizeof(ResolvedQmgrName));
  memset( ResLclQueueName, '\0', sizeof(ResLclQueueName));
  memset( ResLclQmgrName, '\0', sizeof(ResLclQmgrName));
  memset( ReplyToQueueName, '\0', sizeof(ReplyToQueueName));
  memset( ReplyToQmgrName, '\0', sizeof(ReplyToQmgrName));
  memset( MsgId, '\0', sizeof(MsgId));
  memset( CorrelId, '\0', sizeof(CorrelId));

  memset(underline, '=', sizeof(underline)-1);
  underline[sizeof(underline)-1]='\0';

  if (indentCount <= (sizeof(indent)-1))
  {
    memset(indent, ' ', indentCount);
    indent[indentCount]='\0';
  }
  else
  {
    memset(indent, ' ', (sizeof(indent)-1));
    indent[sizeof(indent)-1]='\0';
  }

  bytesLeft=*pbuflen;
  ptr=*ppbuffer;
  memset(operationDate,0,MQ_DATE_LENGTH+1);
  memset(operationTime,0,MQ_TIME_LENGTH+1);
  memset(operation,0,128);
  memset(CompCode,0,128);
  for (count=0; (frc == 0) && (count < parameterCount); count++)
  {
    /****************************************************************/
    /* The first 12 bytes of every PCF structure contain its type,  */
    /* length and parameter id... check that this looks valid       */
    /****************************************************************/
    if (bytesLeft < (sizeof(MQLONG) * 3))
    {
      fprintf(stderr, 
              "Premature end of buffer before processing complete.\n");
      frc=-1;
      break;
    }

    memcpy(&Type, (ptr + offsetof(MQCFIN, Type)), sizeof(MQLONG));
    memcpy(&Length, (ptr + offsetof(MQCFIN, StrucLength)), sizeof(MQLONG));
    memcpy(&Parameter, (ptr + offsetof(MQCFIN, Parameter)), sizeof(MQLONG));

    if (bytesLeft < Length)
    {
      fprintf(stderr, 
              "Premature end of buffer before processing complete.\n");
      frc=-1;
      break;
    }
    if (Type == MQCFT_GROUP)
    {
      memcpy(&ParameterCount, (ptr + offsetof(MQCFGR, ParameterCount)), sizeof(MQLONG));
      ptr+=Length;
      bytesLeft-=Length;
      frc=skipMonitoringRecord(ParameterCount,
                               &ptr,
                               &bytesLeft);
    }
    else
    {
      memset(buffer, 0, sizeof(buffer));
      switch (Parameter)
      {
      case MQIAMO64_HIGHRES_TIME:
        memcpy(&HighResTime, (ptr + offsetof(MQCFIN64, Value)), sizeof(MQINT64));
        HighResTimeFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_OPERATION_ID:
        memcpy(&Value32, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        strcpy(operation, getMonInteger(Parameter,
                                        Value32, buffer, sizeof(buffer)));
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_PROCESS_ID:
        memcpy(&pid, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_THREAD_ID:
        memcpy(&tid, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_CONNECT_OPTIONS:
        memcpy(&ConnOpt, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        ConnOptFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_OPEN_OPTIONS:
        memcpy(&OpenOpt, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        OpenOptFindCd='Y'; 
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_GET_OPTIONS:
        memcpy(&GetOpt, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        GetOptFindCd='Y'; 
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_PUT_OPTIONS:
        memcpy(&PutOpt, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        PutOptFindCd='Y'; 
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_CLOSE_OPTIONS:
        memcpy(&CloseOpt, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        CloseOptFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_MQCB_OPTIONS:
        memcpy(&CBOpt, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        CBOptFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_SUB_OPTIONS:
        memcpy(&SubOpt, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        SubOptFindCd='Y'; 
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_SUBRQ_OPTIONS:
        memcpy(&SubRqOpt, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        SubRqOptFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_PERSISTENCE:
        memcpy(&HoldPrst, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        PrstFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_PRIORITY:
        memcpy(&Priority, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        PriorityFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_REPORT:
        memcpy(&ReportOptions, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        ReportOptionsFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_EXPIRY:
        memcpy(&Expiry, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        ExpiryFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_MSG_LENGTH:
        memcpy(&HoldMsgLgth, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        MsgLgthFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break; 

      case MQIA_CODED_CHAR_SET_ID:
        memcpy(&CCSID, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        CCSIDFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_ENCODING:
        memcpy(&Encoding, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        EncodingFindCd='Y';
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_OPERATION_DATE:
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        memcpy(operationDate, (ptr + offsetof(MQCFST, String)), StringLength );
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_OPERATION_TIME:
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        memcpy(operationTime, (ptr + offsetof(MQCFST, String)), StringLength );
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_COMP_CODE:
        memcpy(&Value32, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        strcpy(CompCode, getMonInteger(Parameter,
                                       Value32, buffer, sizeof(buffer)));
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_REASON_CODE:
        memcpy(&Value32, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        ReasonCode = Value32;
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQIACF_HOBJ:
        memcpy(&Value32, (ptr + offsetof(MQCFIN, Value)), sizeof(MQLONG));
        HObj = Value32;
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_OBJECT_NAME:
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_OBJECT_NAME_LENGTH)
        {
          for (i=0; (i < MQ_OBJECT_NAME_LENGTH) && (StringData[i] != ' '); i++)
            ObjName[i]=StringData[i];
        }
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_OBJECT_Q_MGR_NAME:
        ObjQmgrNameFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_Q_MGR_NAME_LENGTH)
        {
          for (i=0; (i < MQ_Q_MGR_NAME_LENGTH) && (StringData[i] != ' '); i++)
            ObjQmgrName[i]=StringData[i];
        }
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_RESOLVED_Q_NAME:
        ResolvedQueueNameFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_OBJECT_NAME_LENGTH)
        {
          for (i=0; (i < MQ_OBJECT_NAME_LENGTH) && (StringData[i] != ' '); i++)
            ResolvedQueueName[i]=StringData[i];
        }
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_RESOLVED_Q_MGR:
        ResolvedQmgrNameFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_Q_MGR_NAME_LENGTH)
        {
          for (i=0; (i < MQ_Q_MGR_NAME_LENGTH) && (StringData[i] != ' '); i++)
            ResolvedQmgrName[i]=StringData[i];
        }
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_RESOLVED_LOCAL_Q_NAME:
        ResLclQueueNameFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_OBJECT_NAME_LENGTH)
        {
          for (i=0; (i < MQ_OBJECT_NAME_LENGTH) && (StringData[i] != ' '); i++)
            ResLclQueueName[i]=StringData[i];
        }
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_RESOLVED_LOCAL_Q_MGR:
        ResLclQmgrNameFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_Q_MGR_NAME_LENGTH)
        {
          for (i=0; (i < MQ_Q_MGR_NAME_LENGTH) && (StringData[i] != ' '); i++)
            ResLclQmgrName[i]=StringData[i];
        }
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_REPLY_TO_Q:
        ReplyToQueueNameFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_OBJECT_NAME_LENGTH)
        {
          for (i=0; (i < MQ_OBJECT_NAME_LENGTH) && (StringData[i] != ' '); i++)
            ReplyToQueueName[i]=StringData[i];
        }
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQCACF_REPLY_TO_Q_MGR:
        ReplyToQmgrNameFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        StringData = (MQCHAR *)(ptr + offsetof(MQCFST, String));
        if (StringLength > 0 && StringLength <= MQ_Q_MGR_NAME_LENGTH)
        {
          for (i=0; (i < MQ_Q_MGR_NAME_LENGTH) && (StringData[i] != ' '); i++)
            ReplyToQmgrName[i]=StringData[i];
        }
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQBACF_MSG_ID:
        MsgIdFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFBS, StringLength)), sizeof(MQLONG));
        memcpy(MsgId, (ptr + offsetof(MQCFBS, String)), StringLength );
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQBACF_CORREL_ID:
        CorrelIdFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFBS, StringLength)), sizeof(MQLONG));
        memcpy(CorrelId, (ptr + offsetof(MQCFBS, String)), StringLength );
        bytesLeft-=Length;
        ptr+=Length;
        break;

      case MQBACF_MESSAGE_DATA:
        MessageDataFindCd='Y';
        memcpy(&StringLength, (ptr + offsetof(MQCFBS, StringLength)), sizeof(MQLONG));
        pMessageData = (ptr + offsetof(MQCFBS, String));
        MessageDataLgth=StringLength;
        bytesLeft-=Length;
        ptr+=Length;
        break;

      default:  /* Just ignore additional single parameters */
        bytesLeft-=Length;
        ptr+=Length;
        break;
      }
    }

  }
  /****************************************************************/
  /* Print the header if required                                 */
  /****************************************************************/
  if (printHeader == TRUE)
  {
    printf("%s\n", underline);
    printHeader = FALSE;
  }

  /****************************************************************/
  /* Print the line of trace                                      */
  /****************************************************************/
  printf("%s",indent);

  printf("1LS= ");

  printf("Rec(%d) ",RecordNum);

  if ((APIFields1 & 0x1) == 0x1)
    printf("Pid(%d) ", pid);

  if ((APIFields1 & 0x2) == 0x2)
    printf("Tid(%d) ", tid);

  if ((APIFields1 & 0x10) == 0x10)
    printf("Date(%s) ", operationDate);

  if ((APIFields1 & 0x20) == 0x20)
  { 
    if (HighResTimeFindCd == 'Y')
      printf("Time(%s.%06d) ", operationTime, HighResTime%1000000);
    else
      printf("Time(%s) ", operationTime);
  }

  if ((APIFields1 & 0x40) == 0x40)
    printf("Opr(%s) ", operation);

  if ((APIFields1 & 0x80) == 0x80)
    printf("RC(%d) ", ReasonCode);

  if ((APIFields1 & 0x400) == 0x400)
    printf("Qmgr(%s) ", QmgrName);

  if ((APIFields1 & 0x8) == 0x8)
    printf("Chl(%s) ", ChannelName);

  if ((APIFields1 & 0x800) == 0x800)
    printf("Appl(%s) ", ApplicationName);

  if ((APIFields1 & 0x1000) == 0x1000)
    printf("User(%s) ", UserId);

  if ((APIFields1 & 0x4) == 0x4)
  {
    printf("CnId(%02X", conn[0] & 0xff);
    for (i=1;i < 8;i++)
      printf("%02X", conn[i] & 0xff);
    printf(") ");
  }

  if ((APIFields1 & 0x100) == 0x100)
  {
    if ( HObj != MQHO_UNUSABLE_HOBJ)
      printf(  "HObj(%d) ", HObj);
  }

  if ((APIFields1 & 0x200) == 0x200)
  {
    if ( HObj != MQHO_UNUSABLE_HOBJ)
      printf(  "Obj(%s) ", ObjName);
    else
    {
      if (!strncmp(operation,"MQXF_PUT1",9))
        printf(  "Obj(%s) ", ObjName);
    }
  }

  if ((APIFields1 & 0x8000) == 0x8000)
  {
    if (ObjQmgrNameFindCd == 'Y')
      printf(  "OQNm(%s) ", ObjQmgrName);
  }


  if ((APIFields1 & 0x10000) == 0x10000)
  {
    if (ResolvedQueueNameFindCd == 'Y')
      printf(  "RQNm(%s) ", ResolvedQueueName);
  }

  if ((APIFields1 & 0x20000) == 0x20000)
  {
    if (ResolvedQmgrNameFindCd == 'Y')
      printf(  "RQMN(%s) ", ResolvedQmgrName);
  }

  if ((APIFields1 & 0x40000) == 0x40000)
  {
    if (ResLclQueueNameFindCd == 'Y')
      printf(  "RLQN(%s) ", ResLclQueueName);
  }

  if ((APIFields1 & 0x80000) == 0x80000)
  {
    if (ResLclQmgrNameFindCd == 'Y')
      printf(  "RLQM(%s) ", ResLclQmgrName);
  }

  if ((APIFields1 & 0x100000) == 0x100000)
  {
    if (ReplyToQueueNameFindCd == 'Y')
      printf(  "RToQ(%s) ", ReplyToQueueName);
  }

  if ((APIFields1 & 0x200000) == 0x200000)
  {
    if (ReplyToQmgrNameFindCd == 'Y')
      printf(  "RTQM(%s) ", ReplyToQmgrName);
  }

  if ((APIFields1 & 0x400000) == 0x400000)
  {
    if (PriorityFindCd == 'Y')
      printf(  "Prty(%d) ", Priority);
  }

  if ((APIFields1 & 0x800000) == 0x800000)
  {
    if (PrstFindCd == 'Y')
      printf(  "Prst(%d) ", HoldPrst);
  }

  if ((APIFields1 & 0x1000000) == 0x1000000)
  {
    if (ReportOptionsFindCd == 'Y')
      printf(  "Rprt(%d) ", ReportOptions);
  }

  if ((APIFields1 & 0x2000000) == 0x2000000)
  {
    if (ExpiryFindCd == 'Y')
      printf(  "Expr(%d) ", Expiry);
  }

  if ((APIFields1 & 0x4000000) == 0x4000000)
  {
    if (MsgLgthFindCd == 'Y')
      printf(  "MsgL(%d) ", HoldMsgLgth);
  }

  if ((APIFields1 & 0x8000000) == 0x8000000)
  {
    if (CCSIDFindCd == 'Y')
      printf(  "CCSI(%d) ", CCSID);
  }

  if ((APIFields1 & 0x10000000) == 0x10000000)
  {
    if (EncodingFindCd == 'Y')
      printf(  "Encd(%d) ", Encoding);
  }

  if ((APIFields2 & 0x1) == 0x1)
  {
    if (ConnOptFindCd == 'Y')
      printf(  "CnOp(%d) ", ConnOpt);
  }

  if ((APIFields2 & 0x2) == 0x2)
  {
    if (OpenOptFindCd == 'Y')
      printf(  "OpOp(%d) ", OpenOpt);
  }

  if ((APIFields2 & 0x4) == 0x4)
  {
    if (GetOptFindCd == 'Y')
      printf(  "GtOp(%d) ", GetOpt);
  }

  if ((APIFields2 & 0x8) == 0x8)
  {
    if (PutOptFindCd == 'Y')
      printf(  "PtOp(%d) ", PutOpt);
  }

  if ((APIFields2 & 0x10) == 0x10)
  {
    if (CloseOptFindCd == 'Y')
      printf(  "ClOp(%d) ", CloseOpt);
  }

  if ((APIFields2 & 0x20) == 0x20)
  {
    if (CBOptFindCd == 'Y')
      printf(  "CbOp(%d) ", CBOpt);
  }

  if ((APIFields2 & 0x40) == 0x40)
  {
    if (SubOptFindCd == 'Y')
      printf(  "SbOp(%d) ", SubOpt);
  }

  if ((APIFields2 & 0x80) == 0x80)
  {
    if (SubRqOptFindCd == 'Y')
      printf(  "SROp(%d) ", SubRqOpt);
  }

  if ((APIFields1 & 0x2000) == 0x2000)
  {
    if (MsgIdFindCd == 'Y')
    {
      printf("MgId(%02X", MsgId[0] & 0xff);
      for (i=1;i < MQ_MSG_ID_LENGTH;i++)
        printf("%02X", MsgId[i] & 0xff);
      printf(") ");
    }
  }

  if ((APIFields1 & 0x4000) == 0x4000)
  {
    if (CorrelIdFindCd == 'Y')
    {
      printf("CrId(%02X", CorrelId[0] & 0xff);
      for (i=1;i < MQ_CORREL_ID_LENGTH;i++)
        printf("%02X", CorrelId[i] & 0xff);
      printf(") ");
    }
  }

  if ((APIFields1 & 0x20000000) == 0x20000000)
  {
    if (MessageDataFindCd == 'Y')
    {
      printf("MDAB(");
      for (i=0;i < MessageDataLgth;i++)
        printf("%02X", pMessageData[i] & 0xff);
      printf(") ");
    }
  }

  printf("\n");

  /*********************************************************/
  /* Set Persistence and Message Length fields accordingly */ 
  /*********************************************************/
  if (PrstFindCd == 'Y')
  {
    switch (HoldPrst)
    {
    case MQPER_NOT_PERSISTENT:
      NonPrstCt=1;
      if (MsgLgthFindCd == 'Y') 
        NonPrstMsgLgth=HoldMsgLgth;
      break;
    case MQPER_PERSISTENT:
      PrstCt=1;
      if (MsgLgthFindCd == 'Y') 
        PrstMsgLgth=HoldMsgLgth;
      break;
    case MQPER_PERSISTENCE_AS_Q_DEF:
      DfltPrstCt=1;
      if (MsgLgthFindCd == 'Y') 
        DfltPrstMsgLgth=HoldMsgLgth;
      break;
    default:
      NAPrstCt=1;
      if (MsgLgthFindCd == 'Y')
        NAPrstMsgLgth=HoldMsgLgth;
      break;
    }
  }
  else
  {
    if (MsgLgthFindCd == 'Y')
    {
      NAPrstCt=1;
      NAPrstMsgLgth=HoldMsgLgth;
    }
  } 


  /*********************************************************/
  /* If Reporting, add data to lists                       */
  /*********************************************************/
  if (Report)
  {
    if (ChannelName[0] != '\0')
      addChlTracker(ChannelName, TempCt);

    addOprTracker(operation, TempCt, NonPrstCt, NonPrstMsgLgth, PrstCt, PrstMsgLgth, DfltPrstCt, DfltPrstMsgLgth, NAPrstCt, NAPrstMsgLgth);

    if (ConnOptFindCd  == 'Y' ||
        OpenOptFindCd  == 'Y' ||
        GetOptFindCd   == 'Y' ||
        PutOptFindCd   == 'Y' ||
        CloseOptFindCd == 'Y' ||
        CBOptFindCd    == 'Y' ||
        SubOptFindCd   == 'Y' ||
        SubRqOptFindCd == 'Y')
    {
      OptTrackerHead=OprTrackerCurr->OptTrackerHead;
      OptTrackerCurr=OprTrackerCurr->OptTrackerCurr;
      if (ConnOptFindCd == 'Y')
      {
        OptType=1;
        addOptTracker(OptType,ConnOpt,TempCt);
      }
      if (OpenOptFindCd == 'Y')
      {
        OptType=2;
        addOptTracker(OptType,OpenOpt,TempCt);
      }
      if (GetOptFindCd == 'Y')
      {
        OptType=3;
        addOptTracker(OptType,GetOpt,TempCt);
      }
      if (PutOptFindCd == 'Y')
      {
        OptType=4;
        addOptTracker(OptType,PutOpt,TempCt);
      }
      if (CloseOptFindCd == 'Y')
      {
        OptType=5;
        addOptTracker(OptType,CloseOpt,TempCt);
      }
      if (CBOptFindCd == 'Y')
      {
        OptType=6;
        addOptTracker(OptType,CBOpt,TempCt);
      }
      if (SubOptFindCd == 'Y')
      {
        OptType=7;
        addOptTracker(OptType,SubOpt,TempCt);
      }
      if (SubRqOptFindCd == 'Y')
      {
        OptType=8;
        addOptTracker(OptType,SubRqOpt,TempCt);
      }
      OprTrackerCurr->OptTrackerHead=OptTrackerHead;
      OprTrackerCurr->OptTrackerCurr=OptTrackerCurr;
    }

    ReasonTrackerHead=OprTrackerCurr->ReasonTrackerHead;
    ReasonTrackerCurr=OprTrackerCurr->ReasonTrackerCurr;
    addReasonTracker(ReasonCode,TempCt);
    OprTrackerCurr->ReasonTrackerHead=ReasonTrackerHead;
    OprTrackerCurr->ReasonTrackerCurr=ReasonTrackerCurr;

    addTidTracker(tid);
  }

  if ( HObj != MQHO_UNUSABLE_HOBJ)
  {
    if ( ObjName[0] != '\0')
    {
      if (Report)
      {
        addObjTracker(ObjName, TempCt);

        OprTrackerHoldHead=OprTrackerHead;
        OprTrackerHoldCurr=OprTrackerCurr;
        OprTrackerHead=ObjTrackerCurr->OprTrackerHead;
        OprTrackerCurr=ObjTrackerCurr->OprTrackerCurr;
        addOprTracker(operation, TempCt, NonPrstCt, NonPrstMsgLgth, PrstCt, PrstMsgLgth, DfltPrstCt, DfltPrstMsgLgth, NAPrstCt, NAPrstMsgLgth);
        ObjTrackerCurr->OprTrackerHead=OprTrackerHead;
        ObjTrackerCurr->OprTrackerCurr=OprTrackerCurr;
        OprTrackerHead=OprTrackerHoldHead;
        OprTrackerCurr=OprTrackerHoldCurr;

        if (ConnOptFindCd  == 'Y' ||
            OpenOptFindCd  == 'Y' ||
            GetOptFindCd   == 'Y' ||
            PutOptFindCd   == 'Y' ||
            CloseOptFindCd == 'Y' ||
            CBOptFindCd    == 'Y' ||
            SubOptFindCd   == 'Y' ||
            SubRqOptFindCd == 'Y')
        {
          OptTrackerHead=ObjTrackerCurr->OptTrackerHead;
          OptTrackerCurr=ObjTrackerCurr->OptTrackerCurr;
          if (ConnOptFindCd == 'Y')
          {
            OptType=1;
            addOptTracker(OptType,ConnOpt,TempCt);
          }
          if (OpenOptFindCd == 'Y')
          {
            OptType=2;
            addOptTracker(OptType,OpenOpt,TempCt);
          }
          if (GetOptFindCd == 'Y')
          {
            OptType=3;
            addOptTracker(OptType,GetOpt,TempCt);
          }
          if (PutOptFindCd == 'Y')
          {
            OptType=4;
            addOptTracker(OptType,PutOpt,TempCt);
          }
          if (CloseOptFindCd == 'Y')
          {
            OptType=5;
            addOptTracker(OptType,CloseOpt,TempCt);
          }
          if (CBOptFindCd == 'Y')
          {
            OptType=6;
            addOptTracker(OptType,CBOpt,TempCt);
          }
          if (SubOptFindCd == 'Y')
          {
            OptType=7;
            addOptTracker(OptType,SubOpt,TempCt);
          }
          if (SubRqOptFindCd == 'Y')
          {
            OptType=8;
            addOptTracker(OptType,SubRqOpt,TempCt);
          }
          ObjTrackerCurr->OptTrackerHead=OptTrackerHead;
          ObjTrackerCurr->OptTrackerCurr=OptTrackerCurr;
        } 
      }
    }
  }
  else
  {
    if (!strncmp(operation,"MQXF_PUT1",9))
    {
      if (Report)
      {
        addObjTracker(ObjName, TempCt);

        OprTrackerHoldHead=OprTrackerHead;
        OprTrackerHoldCurr=OprTrackerCurr;
        OprTrackerHead=ObjTrackerCurr->OprTrackerHead;
        OprTrackerCurr=ObjTrackerCurr->OprTrackerCurr;
        addOprTracker(operation, TempCt, NonPrstCt, NonPrstMsgLgth, PrstCt, PrstMsgLgth, DfltPrstCt, DfltPrstMsgLgth, NAPrstCt, NAPrstMsgLgth);
        ObjTrackerCurr->OprTrackerHead=OprTrackerHead;
        ObjTrackerCurr->OprTrackerCurr=OprTrackerCurr;
        OprTrackerHead=OprTrackerHoldHead;
        OprTrackerCurr=OprTrackerHoldCurr;

        if (ConnOptFindCd  == 'Y' ||
            OpenOptFindCd  == 'Y' ||
            GetOptFindCd   == 'Y' ||
            PutOptFindCd   == 'Y' ||
            CloseOptFindCd == 'Y' ||
            CBOptFindCd    == 'Y' ||
            SubOptFindCd   == 'Y' ||
            SubRqOptFindCd == 'Y')
        {
          OptTrackerHead=ObjTrackerCurr->OptTrackerHead;
          OptTrackerCurr=ObjTrackerCurr->OptTrackerCurr;
          if (ConnOptFindCd == 'Y')
          {
            OptType=1;
            addOptTracker(OptType,ConnOpt,TempCt);
          }
          if (OpenOptFindCd == 'Y')
          {
            OptType=2;
            addOptTracker(OptType,OpenOpt,TempCt);
          }
          if (GetOptFindCd == 'Y')
          {
            OptType=3;
            addOptTracker(OptType,GetOpt,TempCt);
          }
          if (PutOptFindCd == 'Y')
          {
            OptType=4;
            addOptTracker(OptType,PutOpt,TempCt);
          }
          if (CloseOptFindCd == 'Y')
          {
            OptType=5;
            addOptTracker(OptType,CloseOpt,TempCt);
          }
          if (CBOptFindCd == 'Y')
          {
            OptType=6;
            addOptTracker(OptType,CBOpt,TempCt);
          }
          if (SubOptFindCd == 'Y')
          {
            OptType=7;
            addOptTracker(OptType,SubOpt,TempCt);
          }
          if (SubRqOptFindCd == 'Y')
          {
            OptType=8;
            addOptTracker(OptType,SubRqOpt,TempCt);
          }
          ObjTrackerCurr->OptTrackerHead=OptTrackerHead;
          ObjTrackerCurr->OptTrackerCurr=OptTrackerCurr;
        }

      }

    }

  }  /* if ( HObj != MQHO_UNUSABLE_HOBJ) */ 

  *ppbuffer=ptr;
  *pbuflen=bytesLeft;

  return 0;
}


/********************************************************************/
/*                                                                  */
/* Function: addObjTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function adds a ObjTracker item to the link list if the   */
/*   item does not currently exist.                                 */
/*                                                                  */
/********************************************************************/
int addObjTracker(char *ObjName, 
                  MQLONG ObjCt)
{
  ObjTrackerItem *ObjTrackerTemp=NULL;
  ObjTrackerItem *ObjTrackerTemp2=NULL;
  int i;

  /*******************************************************************/
  /* Check if our ObjTrackerCurr is a match, and get out, if so      */ 
  /*******************************************************************/
  if (ObjTrackerCurr != NULL) 
    if (!strcmp(ObjTrackerCurr->ObjName,ObjName)) 
    {
      ObjTrackerCurr->ObjCt=ObjTrackerCurr->ObjCt+ObjCt;
      return 0;
    }

  /*******************************************************************************/
  /* Check if our ObjName is included in the ObjTracker list, and update and get */
  /* out, if so. If not, build new item and add sorted by ObjName in list        */ 
  /*******************************************************************************/
  if (ObjTrackerHead != NULL)
  {
    ObjTrackerTemp=ObjTrackerHead;
    while (ObjTrackerTemp != NULL)
    {
      if (!strcmp(ObjTrackerTemp->ObjName,ObjName))
      {
        ObjTrackerCurr=ObjTrackerTemp;
        ObjTrackerCurr->ObjCt=ObjTrackerCurr->ObjCt+ObjCt;
        return 0;
      }

      /********************************************************************/
      /* If our current ObjTracker ObjName is > input ObjName, we need to */
      /* create a new list item into our list.                            */
      /********************************************************************/
      if (strcmp(ObjTrackerTemp->ObjName,ObjName) > 0)  
      {
        crtObjTracker(ObjName, ObjCt);

        /*******************************************************************/
        /* prevItem NULL means our current list item is the head and we    */
        /* should insert out new item at the beginning of the list.        */
        /*******************************************************************/
        if (ObjTrackerTemp->prevItem == NULL)
        {
          ObjTrackerHead=ObjTrackerCurr;
          ObjTrackerTemp->prevItem=ObjTrackerHead;
          ObjTrackerHead->prevItem=NULL;
          ObjTrackerHead->nextItem=ObjTrackerTemp;                              
          ObjTrackerTemp=NULL;
        }
        /*******************************************************************/
        /* else insert item in middle of list                              */
        /*******************************************************************/
        else
        {
          ObjTrackerTemp2=ObjTrackerTemp->prevItem;
          ObjTrackerTemp2->nextItem=ObjTrackerCurr;
          ObjTrackerTemp->prevItem=ObjTrackerCurr;
          ObjTrackerCurr->prevItem=ObjTrackerTemp2;
          ObjTrackerCurr->nextItem=ObjTrackerTemp;
          ObjTrackerTemp=NULL;
        }  /* if (ObjTrackerTemp->prevItem == NULL) */ 
      }
      else
      {
        /*******************************************************************/
        /* nextItem NULL means we are at the end of the list and we should */
        /* insert a new item at the end of the list.                       */
        /*******************************************************************/
        if (ObjTrackerTemp->nextItem == NULL)
        {
          crtObjTracker(ObjName, ObjCt);
          ObjTrackerCurr->prevItem=ObjTrackerTemp;
          ObjTrackerCurr->nextItem=NULL;
          ObjTrackerTemp->nextItem=ObjTrackerCurr;
          ObjTrackerTemp=NULL;  
        }
        /*******************************************************************/
        /* else we have more items to search in our list                   */
        /*******************************************************************/
        else
        {
          ObjTrackerTemp2=ObjTrackerTemp->nextItem;
          ObjTrackerTemp=ObjTrackerTemp2;
        }  /* if (ObjTrackerTemp->nextItem == NULL) */
      }  /* if (ObjTrackerTemp->pid > pid) */ 
    }  /* while (ObjTrackerTemp != NULL) */
  }
  else
  /*******************************************************************/
  /* First time - allocate list, update item, and get out.           */
  /*******************************************************************/
  {
    crtObjTracker(ObjName, ObjCt);
    ObjTrackerHead=ObjTrackerCurr;

    return 0;
  }  /* if (ObjTrackerHead != NULL) */ 

  return 0;

}


/********************************************************************/
/*                                                                  */
/* Function: crtObjTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function creates a ObjTracker item.                       */
/*   The global variable ObjTrackerCurr will be used for the return */
/*   item.                                                          */
/*                                                                  */
/********************************************************************/
int crtObjTracker(char *ObjName, MQLONG ObjCt)
{
  int i;

  ObjTrackerCurr=(ObjTrackerItem *)malloc(sizeof(ObjTrackerItem));
  if (ObjTrackerCurr == NULL)
  {
    fprintf(stderr, "Failed to allocate memory(%d) for ObjTracker List\n",
            (int)sizeof(ObjTrackerItem));
    exit(-1);
  }
  ObjTrackerCurr->prevItem=NULL;
  ObjTrackerCurr->nextItem=NULL;

  for (i=0;i < MQ_OBJECT_NAME_LENGTH;i++)
     ObjTrackerCurr->ObjName[i]=ObjName[i];
  ObjTrackerCurr->ObjName[MQ_OBJECT_NAME_LENGTH]='\0';

  ObjTrackerCurr->ObjCt=ObjCt;

  ObjTrackerCurr->OptTrackerHead=NULL;
  ObjTrackerCurr->OptTrackerCurr=NULL;
  ObjTrackerCurr->OprTrackerHead=NULL;
  ObjTrackerCurr->OprTrackerCurr=NULL;

  return 0;
}


/********************************************************************/
/*                                                                  */
/* Function: addOptTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function adds a OptTracker item to the link list if the   */
/*   item does not currently exist.                                 */
/*                                                                  */
/********************************************************************/
int addOptTracker(MQLONG OptType, 
                  MQLONG Opt,
                  MQLONG OptCt)
{
  OptTrackerItem *OptTrackerTemp=NULL;
  OptTrackerItem *OptTrackerTemp2=NULL;

  /*******************************************************************/
  /* Check if our OptTrackerCurr is a match, and get out, if so      */ 
  /*******************************************************************/
  if (OptTrackerCurr != NULL) 
    if (OptTrackerCurr->OptType == OptType &&
        OptTrackerCurr->Opt == Opt) 
    {
      OptTrackerCurr->OptCt=OptTrackerCurr->OptCt+OptCt;
      return 0;
    }

  /***********************************************************************************/
  /* Check if our OptType/Opt is included in the OptTracker list, and update and get */
  /* out, if so. If not, build new item and add sorted by OptType/Opt in list        */ 
  /***********************************************************************************/
  if (OptTrackerHead != NULL)
  {
    OptTrackerTemp=OptTrackerHead;
    while (OptTrackerTemp != NULL)
    {
      if (OptTrackerTemp->OptType == OptType &&
          OptTrackerTemp->Opt == Opt) 
      {
        OptTrackerCurr=OptTrackerTemp;
        OptTrackerCurr->OptCt=OptTrackerCurr->OptCt+OptCt;
        return 0;
      }

      /****************************************************************************/
      /* If our current OptTracker OptType/Opt is > input OptType/Opt, we need to */
      /* create a new list item into our list.                                    */
      /****************************************************************************/
      if (OptTrackerTemp->OptType > OptType ||
          (OptTrackerTemp->OptType == OptType &&
           OptTrackerTemp->Opt > Opt))  
      {
        crtOptTracker(OptType, Opt, OptCt);

        /*******************************************************************/
        /* prevItem NULL means our current list item is the head and we    */
        /* should insert out new item at the beginning of the list.        */
        /*******************************************************************/
        if (OptTrackerTemp->prevItem == NULL)
        {
          OptTrackerHead=OptTrackerCurr;
          OptTrackerTemp->prevItem=OptTrackerHead;
          OptTrackerHead->prevItem=NULL;
          OptTrackerHead->nextItem=OptTrackerTemp;                              
          OptTrackerTemp=NULL;
        }
        /*******************************************************************/
        /* else insert item in middle of list                              */
        /*******************************************************************/
        else
        {
          OptTrackerTemp2=OptTrackerTemp->prevItem;
          OptTrackerTemp2->nextItem=OptTrackerCurr;
          OptTrackerTemp->prevItem=OptTrackerCurr;
          OptTrackerCurr->prevItem=OptTrackerTemp2;
          OptTrackerCurr->nextItem=OptTrackerTemp;
          OptTrackerTemp=NULL;
        }  /* if (OptTrackerTemp->prevItem == NULL) */ 
      }
      else
      {
        /*******************************************************************/
        /* nextItem NULL means we are at the end of the list and we should */
        /* insert a new item at the end of the list.                       */
        /*******************************************************************/
        if (OptTrackerTemp->nextItem == NULL)
        {
          crtOptTracker(OptType, Opt, OptCt);
          OptTrackerCurr->prevItem=OptTrackerTemp;
          OptTrackerCurr->nextItem=NULL;
          OptTrackerTemp->nextItem=OptTrackerCurr;
          OptTrackerTemp=NULL;  
        }
        /*******************************************************************/
        /* else we have more items to search in our list                   */
        /*******************************************************************/
        else
        {
          OptTrackerTemp2=OptTrackerTemp->nextItem;
          OptTrackerTemp=OptTrackerTemp2;
        }  /* if (OptTrackerTemp->nextItem == NULL) */
      }  /* if (OptTrackerTemp->pid > pid) */ 
    }  /* while (OptTrackerTemp != NULL) */
  }
  else
  /*******************************************************************/
  /* First time - allocate list, update item, and get out.           */
  /*******************************************************************/
  {
    crtOptTracker(OptType, Opt, OptCt);
    OptTrackerHead=OptTrackerCurr;

    return 0;
  }  /* if (OptTrackerHead != NULL) */ 

  return 0;

}


/********************************************************************/
/*                                                                  */
/* Function: crtOptTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function creates a OptTracker item.                       */
/*   The global variable OptTrackerCurr will be used for the return */
/*   item.                                                          */
/*                                                                  */
/********************************************************************/
int crtOptTracker(MQLONG OptType,
                  MQLONG Opt,
                  MQLONG OptCt)
{

  OptTrackerCurr=(OptTrackerItem *)malloc(sizeof(OptTrackerItem));
  if (OptTrackerCurr == NULL)
  {
    fprintf(stderr, "Failed to allocate memory(%d) for OptTracker List\n",
            (int)sizeof(OptTrackerItem));
    exit(-1);
  }
  OptTrackerCurr->prevItem=NULL;
  OptTrackerCurr->nextItem=NULL;

  OptTrackerCurr->OptType=OptType;
  OptTrackerCurr->Opt=Opt;

  OptTrackerCurr->OptCt=OptCt;

  return 0;
}


/**********************************************************************/
/*                                                                    */
/* Function: addReasonTracker                                         */
/*                                                                    */
/*                                                                    */
/*   This function adds a ReasonTracker item to the link list if the  */
/*   item does not currently exist.                                   */
/*                                                                    */
/**********************************************************************/
int addReasonTracker(MQLONG Reason, 
                     MQLONG ReasonCt)
{
  ReasonTrackerItem *ReasonTrackerTemp=NULL;
  ReasonTrackerItem *ReasonTrackerTemp2=NULL;

  /*******************************************************************/
  /* Check if our ReasonTrackerCurr is a match, and get out, if so   */ 
  /*******************************************************************/
  if (ReasonTrackerCurr != NULL) 
    if (ReasonTrackerCurr->Reason == Reason) 
    {
      ReasonTrackerCurr->ReasonCt=ReasonTrackerCurr->ReasonCt+ReasonCt;
      return 0;
    }

  /**********************************************************************************/
  /* Check if our Reason is included in the ReasonTracker list, and update and get  */
  /* out, if so. If not, build new item and add sorted by Reason in list            */ 
  /**********************************************************************************/
  if (ReasonTrackerHead != NULL)
  {
    ReasonTrackerTemp=ReasonTrackerHead;
    while (ReasonTrackerTemp != NULL)
    {
      if (ReasonTrackerTemp->Reason == Reason) 
      {
        ReasonTrackerCurr=ReasonTrackerTemp;
        ReasonTrackerCurr->ReasonCt=ReasonTrackerCurr->ReasonCt+ReasonCt;
        return 0;
      }

      /*********************************************************************/
      /* If our current ReasonTracker Reason is > input Reason, we need to */
      /* create a new list item into our list.                             */
      /*********************************************************************/
      if (ReasonTrackerTemp->Reason > Reason)
      {
        crtReasonTracker(Reason, ReasonCt);

        /*******************************************************************/
        /* prevItem NULL means our current list item is the head and we    */
        /* should insert out new item at the beginning of the list.        */
        /*******************************************************************/
        if (ReasonTrackerTemp->prevItem == NULL)
        {
          ReasonTrackerHead=ReasonTrackerCurr;
          ReasonTrackerTemp->prevItem=ReasonTrackerHead;
          ReasonTrackerHead->prevItem=NULL;
          ReasonTrackerHead->nextItem=ReasonTrackerTemp;                              
          ReasonTrackerTemp=NULL;
        }
        /*******************************************************************/
        /* else insert item in middle of list                              */
        /*******************************************************************/
        else
        {
          ReasonTrackerTemp2=ReasonTrackerTemp->prevItem;
          ReasonTrackerTemp2->nextItem=ReasonTrackerCurr;
          ReasonTrackerTemp->prevItem=ReasonTrackerCurr;
          ReasonTrackerCurr->prevItem=ReasonTrackerTemp2;
          ReasonTrackerCurr->nextItem=ReasonTrackerTemp;
          ReasonTrackerTemp=NULL;
        }  /* if (ReasonTrackerTemp->prevItem == NULL) */ 
      }
      else
      {
        /*******************************************************************/
        /* nextItem NULL means we are at the end of the list and we should */
        /* insert a new item at the end of the list.                       */
        /*******************************************************************/
        if (ReasonTrackerTemp->nextItem == NULL)
        {
          crtReasonTracker(Reason, ReasonCt);
          ReasonTrackerCurr->prevItem=ReasonTrackerTemp;
          ReasonTrackerCurr->nextItem=NULL;
          ReasonTrackerTemp->nextItem=ReasonTrackerCurr;
          ReasonTrackerTemp=NULL;  
        }
        /*******************************************************************/
        /* else we have more items to search in our list                   */
        /*******************************************************************/
        else
        {
          ReasonTrackerTemp2=ReasonTrackerTemp->nextItem;
          ReasonTrackerTemp=ReasonTrackerTemp2;
        }  /* if (ReasonTrackerTemp->nextItem == NULL) */
      }  /* if (ReasonTrackerTemp->pid > pid) */ 
    }  /* while (ReasonTrackerTemp != NULL) */
  }
  else
  /*******************************************************************/
  /* First time - allocate list, update item, and get out.           */
  /*******************************************************************/
  {
    crtReasonTracker(Reason, ReasonCt);
    ReasonTrackerHead=ReasonTrackerCurr;

    return 0;
  }  /* if (ReasonTrackerHead != NULL) */ 

  return 0;

}


/***********************************************************************/
/*                                                                     */
/* Function: crtReasonTracker                                          */
/*                                                                     */
/*                                                                     */
/*   This function creates a ReasonTracker item.                       */
/*   The global variable ReasonTrackerCurr will be used for the return */
/*   item.                                                             */
/*                                                                     */
/***********************************************************************/
int crtReasonTracker(MQLONG Reason,
                     MQLONG ReasonCt)
{

  ReasonTrackerCurr=(ReasonTrackerItem *)malloc(sizeof(ReasonTrackerItem));
  if (ReasonTrackerCurr == NULL)
  {
    fprintf(stderr, "Failed to allocate memory(%d) for ReasonTracker List\n",
            (int)sizeof(ReasonTrackerItem));
    exit(-1);
  }
  ReasonTrackerCurr->prevItem=NULL;
  ReasonTrackerCurr->nextItem=NULL;

  ReasonTrackerCurr->Reason=Reason;
  ReasonTrackerCurr->ReasonCt=ReasonCt;

  return 0;
}


/********************************************************************/
/*                                                                  */
/* Function: printOption                                            */
/*                                                                  */
/*                                                                  */
/*   This function prints the constants for an option.              */
/********************************************************************/
int printOption(MQLONG OptType,
                MQLONG Opt)
{
  switch (OptType) {
  case 1: 
    if (Opt == 0)
       printf("   MQCNO_NONE\n");
    else
       {
        if ((Opt & 0x1) == 0x1)
           printf("      MQCNO_FASTPATH_BINDING\n");
        if ((Opt & 0x2) == 0x2)
           printf("      MQCNO_SERIALIZE_CONN_TAG_Q_MGR\n");
        if ((Opt & 0x4) == 0x4)
           printf("      MQCNO_SERIALIZE_CONN_TAG_QSG\n");
        if ((Opt & 0x8) == 0x8)
           printf("      MQCNO_RESTRICT_CONN_TAG_Q_MGR\n");
        if ((Opt & 0x10) == 0x10)
           printf("      MQCNO_RESTRICT_CONN_TAG_QSG\n");
        if ((Opt & 0x20) == 0x20)
           printf("      MQCNO_HANDLE_SHARE_NONE\n");
        if ((Opt & 0x40) == 0x40)
           printf("      MQCNO_HANDLE_SHARE_BLOCK\n");
        if ((Opt & 0x80) == 0x80)
           printf("      MQCNO_HANDLE_SHARE_NO_BLOCK\n");
        if ((Opt & 0x100) == 0x100)
           printf("      MQCNO_SHARED_BINDING\n");
        if ((Opt & 0x200) == 0x200)
           printf("      MQCNO_ISOLATED_BINDING\n");
        if ((Opt & 0x400) == 0x400)
           printf("      MQCNO_LOCAL_BINDING\n");
        if ((Opt & 0x800) == 0x800)
           printf("      MQCNO_CLIENT_BINDING\n");
        if ((Opt & 0x1000) == 0x1000)
           printf("      MQCNO_ACCOUNTING_MQI_ENABLED\n");
        if ((Opt & 0x2000) == 0x2000)
           printf("      MQCNO_ACCOUNTING_MQI_DISABLED\n");
        if ((Opt & 0x4000) == 0x4000)
           printf("      MQCNO_ACCOUNTING_Q_ENABLED\n");
        if ((Opt & 0x8000) == 0x8000)
           printf("      MQCNO_ACCOUNTING_Q_DISABLED\n");
        if ((Opt & 0x10000) == 0x10000)
           printf("      MQCNO_NO_CONV_SHARING\n");
        if ((Opt & 0x40000) == 0x40000)
           printf("      MQCNO_ALL_CONVS_SHARE\n");
        if ((Opt & 0x80000) == 0x80000)
           printf("      MQCNO_CD_FOR_OUTPUT_ONLY\n");
        if ((Opt & 0x100000) == 0x100000)
           printf("      MQCNO_USE_CD_SELECTION\n");
        if ((Opt & 0x1000000) == 0x1000000)
           printf("      MQCNO_RECONNECT\n");
        if ((Opt & 0x2000000) == 0x2000000)
           printf("      MQCNO_RECONNECT_DISABLED\n");
        if ((Opt & 0x4000000) == 0x4000000)
           printf("      MQCNO_RECONNECT_Q_MGR\n");
        if ((Opt & 0x8000000) == 0x8000000)
           printf("      MQCNO_ACTIVITY_TRACE_ENABLED\n");
        if ((Opt & 0x10000000) == 0x10000000)
           printf("      MQCNO_ACTIVITY_TRACE_DISABLED\n");
       }
    break;
  case 2: 
    if ((Opt & 0x1) == 0x1)
       printf("      MQOO_INPUT_AS_Q_DEF\n");
    if ((Opt & 0x2) == 0x2)
       printf("      MQOO_INPUT_SHARED\n");
    if ((Opt & 0x4) == 0x4)
       printf("      MQOO_INPUT_EXCLUSIVE\n");
    if ((Opt & 0x8) == 0x8)
       printf("      MQOO_BROWSE\n");
    if ((Opt & 0x10) == 0x10)
       printf("      MQOO_OUTPUT\n");
    if ((Opt & 0x20) == 0x20)
       printf("      MQOO_INQUIRE\n");
    if ((Opt & 0x40) == 0x40)
       printf("      MQOO_SET\n");
    if ((Opt & 0x80) == 0x80)
       printf("      MQOO_SAVE_ALL_CONTEXT\n");
    if ((Opt & 0x100) == 0x100)
       printf("      MQOO_PASS_IDENTITY_CONTEXT\n");
    if ((Opt & 0x200) == 0x200)
       printf("      MQOO_PASS_ALL_CONTEXT\n");
    if ((Opt & 0x400) == 0x400)
       printf("      MQOO_SET_IDENTITY_CONTEXT\n");
    if ((Opt & 0x800) == 0x800)
       printf("      MQOO_SET_ALL_CONTEXT\n");
    if ((Opt & 0x1000) == 0x1000)
       printf("      MQOO_ALTERNATE_USER_AUTHORITY\n");
    if ((Opt & 0x2000) == 0x2000)
       printf("      MQOO_FAIL_IF_QUIESCING\n");
    if ((Opt & 0x4000) == 0x4000)
       printf("      MQOO_BIND_ON_OPEN\n");
    if ((Opt & 0x8000) == 0x8000)
       printf("      MQOO_BIND_NOT_FIXED\n");
    if ((Opt & 0x10000) == 0x10000)
       printf("      MQOO_RESOLVE_NAMES\n");
    if ((Opt & 0x20000) == 0x20000)
       printf("      MQOO_CO_OP\n");
    if ((Opt & 0x40000) == 0x40000)
       {
        printf("      MQOO_RESOLVE_LOCAL_TOPIC\n");
        printf("      MQOO_RESOLVE_LOCAL_Q (C++ only)\n");
       }
    if ((Opt & 0x80000) == 0x80000)
       printf("      MQOO_NO_READ_AHEAD\n");
    if ((Opt & 0x100000) == 0x100000)
       printf("      MQOO_READ_AHEAD\n");
    if ((Opt & 0x200000) == 0x200000)
       printf("      MQOO_NO_MULTICAST\n");
    if ((Opt & 0x400000) == 0x400000)
       printf("      MQOO_BIND_ON_GROUP\n");
    break;
  case 3:
    if (Opt == 0)
       printf("      MQGMO_NONE\n");
    if ((Opt & 0x1) == 0x1)
       printf("      MQGMO_WAIT\n");
    if ((Opt & 0x2) == 0x2)
       printf("      MQGMO_SYNCPOINT\n");
    if ((Opt & 0x4) == 0x4)
       printf("      MQGMO_NO_SYNCPOINT\n");
    if ((Opt & 0x8) == 0x8)
       printf("      MQGMO_SET_SIGNAL\n");
    if ((Opt & 0x10) == 0x10)
       printf("      MQGMO_BROWSE_FIRST\n");
    if ((Opt & 0x20) == 0x20)
       printf("      MQGMO_BROWSE_NEXT\n");
    if ((Opt & 0x40) == 0x40)
       printf("      MQGMO_ACCEPT_TRUNCATED_MSG\n");
    if ((Opt & 0x80) == 0x80)
       printf("      MQGMO_MARK_SKIP_BACKOUT\n");
    if ((Opt & 0x100) == 0x100)
       printf("      MQGMO_MSG_UNDER_CURSOR\n");
    if ((Opt & 0x200) == 0x200)
       printf("      MQGMO_LOCK\n");
    if ((Opt & 0x400) == 0x400)
       printf("      MQGMO_UNLOCK\n");
    if ((Opt & 0x800) == 0x800)
       printf("      MQGMO_BROWSE_MSG_UNDER_CURSOR\n");
    if ((Opt & 0x1000) == 0x1000)
       printf("      MQGMO_SYNCPOINT_IF_PERSISTENT\n");
    if ((Opt & 0x2000) == 0x2000)
       printf("      MQGMO_FAIL_IF_QUIESCING\n");
    if ((Opt & 0x4000) == 0x4000)
       printf("      MQGMO_CONVERT\n");
    if ((Opt & 0x8000) == 0x8000)
       printf("      MQGMO_LOGICAL_ORDER\n");
    if ((Opt & 0x10000) == 0x10000)
       printf("      MQGMO_COMPLETE_MSG\n");
    if ((Opt & 0x20000) == 0x20000)
       printf("      MQGMO_ALL_MSGS_AVAILABLE\n");
    if ((Opt & 0x40000) == 0x40000)
       printf("      MQGMO_ALL_SEGMENTS_AVAILABLE\n");
    if ((Opt & 0x100000) == 0x100000)
       printf("      MQGMO_MARK_BROWSE_HANDLE\n");
    if ((Opt & 0x200000) == 0x200000)
       printf("      MQGMO_MARK_BROWSE_CO_OP\n");
    if ((Opt & 0x400000) == 0x400000)
       printf("      MQGMO_UNMARK_BROWSE_CO_OP\n");
    if ((Opt & 0x800000) == 0x800000)
       printf("      MQGMO_UNMARK_BROWSE_HANDLE\n");
    if ((Opt & 0x1000000) == 0x1000000)
       printf("      MQGMO_UNMARKED_BROWSE_MSG\n");
    if ((Opt & 0x2000000) == 0x2000000)
       printf("      MQGMO_PROPERTIES_FORCE_MQRFH2\n");
    if ((Opt & 0x4000000) == 0x4000000)
       printf("      MQGMO_NO_PROPERTIES\n");
    if ((Opt & 0x8000000) == 0x8000000)
       printf("      MQGMO_PROPERTIES_IN_HANDLE\n");
    if ((Opt & 0x10000000) == 0x10000000)
       printf("      MQGMO_PROPERTIES_COMPATIBILITY\n");
    if ((Opt & 0x01100010) == 0x01100010)
       printf("      MQGMO_BROWSE_HANDLE\n");
    if ((Opt & 0x01200010) == 0x01200010)
       printf("      MQGMO_BROWSE_CO_OP\n");
    break;
  case 4:
    if (Opt == 0)
       printf("      MQPMO_NONE\n");
    if ((Opt & 0x2) == 0x2)
       printf("      MQPMO_SYNCPOINT\n");
    if ((Opt & 0x4) == 0x4)
       printf("      MQPMO_NO_SYNCPOINT\n");
    if ((Opt & 0x20) == 0x20)
       printf("      MQPMO_DEFAULT_CONTEXT\n");
    if ((Opt & 0x40) == 0x40)
       printf("      MQPMO_NEW_MSG_ID\n");
    if ((Opt & 0x80) == 0x80)
       printf("      MQPMO_NEW_CORREL_ID\n");
    if ((Opt & 0x100) == 0x100)
       printf("      MQPMO_PASS_IDENTITY_CONTEXT\n");
    if ((Opt & 0x200) == 0x200)
       printf("      MQPMO_PASS_ALL_CONTEXT\n");
    if ((Opt & 0x400) == 0x400)
       printf("      MQPMO_SET_IDENTITY_CONTEXT\n");
    if ((Opt & 0x800) == 0x800)
       printf("      MQPMO_SET_ALL_CONTEXT\n");
    if ((Opt & 0x1000) == 0x1000)
       printf("      MQPMO_ALTERNATE_USER_AUTHORITY\n");
    if ((Opt & 0x2000) == 0x2000)
       printf("      MQPMO_FAIL_IF_QUIESCING\n");
    if ((Opt & 0x4000) == 0x4000)
       printf("      MQPMO_NO_CONTEXT\n");
    if ((Opt & 0x8000) == 0x8000)
       printf("      MQPMO_LOGICAL_ORDER\n");
    if ((Opt & 0x10000) == 0x10000)
       printf("      MQPMO_ASYNC_RESPONSE\n");
    if ((Opt & 0x20000) == 0x20000)
       printf("      MQPMO_SYNC_RESPONSE\n");
    if ((Opt & 0x40000) == 0x40000)
       printf("      MQPMO_RESOLVE_LOCAL_Q\n");
    if ((Opt & 0x80000) == 0x80000)
       printf("      MQPMO_WARN_IF_NO_SUBS_MATCHED\n");
    if ((Opt & 0x200000) == 0x200000)
       printf("      MQPMO_RETAIN\n");
    if ((Opt & 0x800000) == 0x800000)
       printf("      MQPMO_MD_FOR_OUTPUT_ONLY\n");
    if ((Opt & 0x4000000) == 0x4000000)
       printf("      MQPMO_SCOPE_QMGR\n");
    if ((Opt & 0x8000000) == 0x8000000)
       printf("      MQPMO_SUPPRESS_REPLYTO\n");
    if ((Opt & 0x10000000) == 0x10000000)
       printf("      MQPMO_NOT_OWN_SUBS\n");
    break;
  case 5:
    switch (Opt) {
    case 0:
       printf("      MQCO_NONE\n");
       printf("      MQCO_IMMEDIATE\n");
       break;
    case 1:
       printf("      MQCO_DELETE\n");
       break;
    case 2:
       printf("      MQCO_DELETE_PURGE\n");
       break;
    case 4:
       printf("      MQCO_KEEP_SUB\n");
       break;
    case 8:
       printf("      MQCO_REMOVE_SUB\n");
       break;
    case 32:
       printf("      MQCO_QUIESCE\n");
       break;
    }
    break;
  case 6:
    if (Opt == 0)
       printf("      MQCBDO_NONE\n");
    if ((Opt & 0x1) == 0x1)
       printf("      MQCBDO_START_CALL\n");
    if ((Opt & 0x4) == 0x4)
       printf("      MQCBDO_STOP_CALL\n");
    if ((Opt & 0x100) == 0x100)
       printf("      MQCBDO_REGISTER_CALL\n");
    if ((Opt & 0x200) == 0x200)
       printf("      MQCBDO_DEREGISTER_CALL\n");
    if ((Opt & 0x2000) == 0x2000)
       printf("      MQCBDO_FAIL_IF_QUIESCING\n");
    if ((Opt & 0x4000) == 0x4000)
       printf("      MQCBDO_EVENT_CALL\n");
    if ((Opt & 0x8000) == 0x8000)
       printf("      MQCBDO_MC_EVENT_CALL\n");
    break;
  case 7:
    if (Opt == 0)
    {
       printf("      MQSO_NONE\n");
       printf("      MQSO_NON_DURABLE\n");
       printf("      MQSO_READ_AHEAD_AS_Q_DEF\n");
    }
    if ((Opt & 0x1) == 0x1)
       printf("      MQSO_ALTER\n");
    if ((Opt & 0x2) == 0x2)
       printf("      MQSO_CREATE\n");
    if ((Opt & 0x4) == 0x4)
       printf("      MQSO_RESUME\n");
    if ((Opt & 0x8) == 0x8)
       printf("      MQSO_DURABLE\n");
    if ((Opt & 0x10) == 0x10)
       printf("      MQSO_GROUP_SUB\n");
    if ((Opt & 0x20) == 0x20)
       printf("      MQSO_MANAGED\n");
    if ((Opt & 0x40) == 0x40)
       printf("      MQSO_SET_IDENTITY_CONTEXT\n");
    if ((Opt & 0x80) == 0x80)
       printf("      MQSO_NO_MULTICAST\n");
    if ((Opt & 0x100) == 0x100)
       printf("      MQSO_FIXED_USERID\n");
    if ((Opt & 0x200) == 0x200)
       printf("      MQSO_ANY_USERID\n");
    if ((Opt & 0x800) == 0x800)
       printf("      MQSO_PUBLICATIONS_ON_REQUEST\n");
    if ((Opt & 0x1000) == 0x1000)
       printf("      MQSO_NEW_PUBLICATIONS_ONLY\n");
    if ((Opt & 0x2000) == 0x2000)
       printf("      MQSO_FAIL_IF_QUIESCING\n");
    if ((Opt & 0x40000) == 0x40000)
       printf("      MQSO_ALTERNATE_USER_AUTHORITY\n");
    if ((Opt & 0x100000) == 0x100000)
       printf("      MQSO_WILDCARD_CHAR\n");
    if ((Opt & 0x200000) == 0x200000)
       printf("      MQSO_WILDCARD_TOPIC\n");
    if ((Opt & 0x400000) == 0x400000)
       printf("      MQSO_SET_CORREL_ID\n");
    if ((Opt & 0x4000000) == 0x4000000)
       printf("      MQSO_SCOPE_QMGR\n");
    if ((Opt & 0x8000000) == 0x8000000)
       printf("      MQSO_NO_READ_AHEAD\n");
    if ((Opt & 0x10000000) == 0x10000000)
       printf("      MQSO_READ_AHEAD\n");
    break;
  case 8:
    if (Opt == 0)
       printf("      MQSRO_NONE\n");
    if ((Opt & 0x2000) == 0x2000)
       printf("      MQSRO_FAIL_IF_QUIESCING\n");
    break;
  }
}

/********************************************************************/
/*                                                                  */
/* Function: addChlTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function adds a ChlTracker item to the link list if the   */
/*   item does not currently exist.                                 */
/*                                                                  */
/********************************************************************/
int addChlTracker(char *ChannelName, 
                  MQLONG ChlCt)
{
  ChlTrackerItem *ChlTrackerTemp=NULL;
  ChlTrackerItem *ChlTrackerTemp2=NULL;
  int i;

  /*******************************************************************/
  /* Check if our ChlTrackerCurr is a match, and get out, if so      */ 
  /*******************************************************************/
  if (ChlTrackerCurr != NULL) 
    if (!strcmp(ChlTrackerCurr->ChannelName,ChannelName)) 
    {
      ChlTrackerCurr->ChlCt=ChlTrackerCurr->ChlCt+ChlCt;
      return 0;
    }

  /***********************************************************************************/
  /* Check if our ChannelName is included in the ChlTracker list, and update and get */
  /* out, if so. If not, build new item and add sorted by ChannelName in list        */ 
  /***********************************************************************************/
  if (ChlTrackerHead != NULL)
  {
    ChlTrackerTemp=ChlTrackerHead;
    while (ChlTrackerTemp != NULL)
    {
      if (!strcmp(ChlTrackerTemp->ChannelName,ChannelName))
      {
        ChlTrackerCurr=ChlTrackerTemp;
        ChlTrackerCurr->ChlCt=ChlTrackerCurr->ChlCt+ChlCt;
        return 0;
      }

      /****************************************************************************/
      /* If our current ChlTracker ChannelName is > input ChannelName, we need to */
      /* create a new list item into our list.                                    */
      /****************************************************************************/
      if (strcmp(ChlTrackerTemp->ChannelName,ChannelName) > 0)  
      {
        crtChlTracker(ChannelName, ChlCt);

        /*******************************************************************/
        /* prevItem NULL means our current list item is the head and we    */
        /* should insert out new item at the beginning of the list.        */
        /*******************************************************************/
        if (ChlTrackerTemp->prevItem == NULL)
        {
          ChlTrackerHead=ChlTrackerCurr;
          ChlTrackerTemp->prevItem=ChlTrackerHead;
          ChlTrackerHead->prevItem=NULL;
          ChlTrackerHead->nextItem=ChlTrackerTemp;                              
          ChlTrackerTemp=NULL;
        }
        /*******************************************************************/
        /* else insert item in middle of list                              */
        /*******************************************************************/
        else
        {
          ChlTrackerTemp2=ChlTrackerTemp->prevItem;
          ChlTrackerTemp2->nextItem=ChlTrackerCurr;
          ChlTrackerTemp->prevItem=ChlTrackerCurr;
          ChlTrackerCurr->prevItem=ChlTrackerTemp2;
          ChlTrackerCurr->nextItem=ChlTrackerTemp;
          ChlTrackerTemp=NULL;
        }  /* if (ChlTrackerTemp->prevItem == NULL) */ 
      }
      else
      {
        /*******************************************************************/
        /* nextItem NULL means we are at the end of the list and we should */
        /* insert a new item at the end of the list.                       */
        /*******************************************************************/
        if (ChlTrackerTemp->nextItem == NULL)
        {
          crtChlTracker(ChannelName, ChlCt);
          ChlTrackerCurr->prevItem=ChlTrackerTemp;
          ChlTrackerCurr->nextItem=NULL;
          ChlTrackerTemp->nextItem=ChlTrackerCurr;
          ChlTrackerTemp=NULL;  
        }
        /*******************************************************************/
        /* else we have more items to search in our list                   */
        /*******************************************************************/
        else
        {
          ChlTrackerTemp2=ChlTrackerTemp->nextItem;
          ChlTrackerTemp=ChlTrackerTemp2;
        }  /* if (ChlTrackerTemp->nextItem == NULL) */
      }  /* if (ChlTrackerTemp->pid > pid) */ 
    }  /* while (ChlTrackerTemp != NULL) */
  }
  else
  /*******************************************************************/
  /* First time - allocate list, update item, and get out.           */
  /*******************************************************************/
  {
    crtChlTracker(ChannelName,ChlCt);
    ChlTrackerHead=ChlTrackerCurr;

    return 0;
  }  /* if (ChlTrackerHead != NULL) */ 

  return 0;

}


/********************************************************************/
/*                                                                  */
/* Function: crtChlTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function creates a ChlTracker item.                       */
/*   The global variable ChlTrackerCurr will be used for the return */
/*   item.                                                          */
/*                                                                  */
/********************************************************************/
int crtChlTracker(char *ChannelName,  
                  MQLONG ChlCt)
{
  int i;

  ChlTrackerCurr=(ChlTrackerItem *)malloc(sizeof(ChlTrackerItem));
  if (ChlTrackerCurr == NULL)
  {
    fprintf(stderr, "Failed to allocate memory(%d) for ChlTracker List\n",
            (int)sizeof(ChlTrackerItem));
    exit(-1);
  }
  ChlTrackerCurr->prevItem=NULL;
  ChlTrackerCurr->nextItem=NULL;

  for (i=0;i < MQ_CHANNEL_NAME_LENGTH;i++)
     ChlTrackerCurr->ChannelName[i]=ChannelName[i];
  ChlTrackerCurr->ChannelName[MQ_CHANNEL_NAME_LENGTH]='\0';

  ChlTrackerCurr->ChlCt=ChlCt;

  return 0;
}


/********************************************************************/
/*                                                                  */
/* Function: addOprTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function adds a OprTracker item to the link list if the   */
/*   item does not currently exist.                                 */
/*                                                                  */
/********************************************************************/
int addOprTracker(char *Operation,
                  MQLONG OprCt,
                  MQLONG NonPrstCt,
                  MQLONG NonPrstMsgLgth,
                  MQLONG PrstCt,
                  MQLONG PrstMsgLgth,
                  MQLONG DfltPrstCt,
                  MQLONG DfltPrstMsgLgth,
                  MQLONG NAPrstCt,
                  MQLONG NAPrstMsgLgth)
{
  OprTrackerItem *OprTrackerTemp=NULL;
  OprTrackerItem *OprTrackerTemp2=NULL;
  int i;

  /*******************************************************************/
  /* Check if our OprTrackerCurr is a match, and get out, if so      */ 
  /*******************************************************************/
  if (OprTrackerCurr != NULL) 
    if (!strcmp(OprTrackerCurr->Operation,Operation)) 
    {
      OprTrackerCurr->OprCt=OprTrackerCurr->OprCt+OprCt;
      OprTrackerCurr->NonPrstCt=OprTrackerCurr->NonPrstCt+NonPrstCt;
      OprTrackerCurr->NonPrstMsgLgth=OprTrackerCurr->NonPrstMsgLgth+NonPrstMsgLgth;
      OprTrackerCurr->PrstCt=OprTrackerCurr->PrstCt+PrstCt;
      OprTrackerCurr->PrstMsgLgth=OprTrackerCurr->PrstMsgLgth+PrstMsgLgth;
      OprTrackerCurr->DfltPrstCt=OprTrackerCurr->DfltPrstCt+DfltPrstCt;
      OprTrackerCurr->DfltPrstMsgLgth=OprTrackerCurr->DfltPrstMsgLgth+DfltPrstMsgLgth;
      OprTrackerCurr->NAPrstCt=OprTrackerCurr->NAPrstCt+NAPrstCt;
      OprTrackerCurr->NAPrstMsgLgth=OprTrackerCurr->NAPrstMsgLgth+NAPrstMsgLgth;
      return 0;
    }

  /*********************************************************************************/
  /* Check if our Operation is included in the OprTracker list, and update and get */
  /* out, if so. If not, build new item and add sorted by Operation in list        */ 
  /*********************************************************************************/
  if (OprTrackerHead != NULL)
  {
    OprTrackerTemp=OprTrackerHead;
    while (OprTrackerTemp != NULL)
    {
      if (!strcmp(OprTrackerTemp->Operation,Operation))
      {
        OprTrackerCurr=OprTrackerTemp;
        OprTrackerCurr->OprCt=OprTrackerCurr->OprCt+OprCt;
        OprTrackerCurr->NonPrstCt=OprTrackerCurr->NonPrstCt+NonPrstCt;
        OprTrackerCurr->NonPrstMsgLgth=OprTrackerCurr->NonPrstMsgLgth+NonPrstMsgLgth;
        OprTrackerCurr->PrstCt=OprTrackerCurr->PrstCt+PrstCt;
        OprTrackerCurr->PrstMsgLgth=OprTrackerCurr->PrstMsgLgth+PrstMsgLgth;
        OprTrackerCurr->DfltPrstCt=OprTrackerCurr->DfltPrstCt+DfltPrstCt;
        OprTrackerCurr->DfltPrstMsgLgth=OprTrackerCurr->DfltPrstMsgLgth+DfltPrstMsgLgth;
        OprTrackerCurr->NAPrstCt=OprTrackerCurr->NAPrstCt+NAPrstCt;
        OprTrackerCurr->NAPrstMsgLgth=OprTrackerCurr->NAPrstMsgLgth+NAPrstMsgLgth;
        return 0;
      }

      /********************************************************************/
      /* If our current OprTracker Operation is > input Operation, we need to */
      /* create a new list item into our list.                            */
      /********************************************************************/
      if (strcmp(OprTrackerTemp->Operation,Operation) > 0)  
      {
        crtOprTracker(Operation, OprCt, NonPrstCt, NonPrstMsgLgth, PrstCt, PrstMsgLgth, DfltPrstCt, DfltPrstMsgLgth, NAPrstCt, NAPrstMsgLgth);

        /*******************************************************************/
        /* prevItem NULL means our current list item is the head and we    */
        /* should insert out new item at the beginning of the list.        */
        /*******************************************************************/
        if (OprTrackerTemp->prevItem == NULL)
        {
          OprTrackerHead=OprTrackerCurr;
          OprTrackerTemp->prevItem=OprTrackerHead;
          OprTrackerHead->prevItem=NULL;
          OprTrackerHead->nextItem=OprTrackerTemp;                              
          OprTrackerTemp=NULL;
        }
        /*******************************************************************/
        /* else insert item in middle of list                              */
        /*******************************************************************/
        else
        {
          OprTrackerTemp2=OprTrackerTemp->prevItem;
          OprTrackerTemp2->nextItem=OprTrackerCurr;
          OprTrackerTemp->prevItem=OprTrackerCurr;
          OprTrackerCurr->prevItem=OprTrackerTemp2;
          OprTrackerCurr->nextItem=OprTrackerTemp;
          OprTrackerTemp=NULL;
        }  /* if (OprTrackerTemp->prevItem == NULL) */ 
      }
      else
      {
        /*******************************************************************/
        /* nextItem NULL means we are at the end of the list and we should */
        /* insert a new item at the end of the list.                       */
        /*******************************************************************/
        if (OprTrackerTemp->nextItem == NULL)
        {
          crtOprTracker(Operation, OprCt, NonPrstCt, NonPrstMsgLgth, PrstCt, PrstMsgLgth, DfltPrstCt, DfltPrstMsgLgth, NAPrstCt, NAPrstMsgLgth);
          OprTrackerCurr->prevItem=OprTrackerTemp;
          OprTrackerCurr->nextItem=NULL;
          OprTrackerTemp->nextItem=OprTrackerCurr;
          OprTrackerTemp=NULL;  
        }
        /*******************************************************************/
        /* else we have more items to search in our list                   */
        /*******************************************************************/
        else
        {
          OprTrackerTemp2=OprTrackerTemp->nextItem;
          OprTrackerTemp=OprTrackerTemp2;
        }  /* if (OprTrackerTemp->nextItem == NULL) */
      }  /* if (OprTrackerTemp->pid > pid) */ 
    }  /* while (OprTrackerTemp != NULL) */
  }
  else
  /*******************************************************************/
  /* First time - allocate list, update item, and get out.           */
  /*******************************************************************/
  {
    crtOprTracker(Operation, OprCt, NonPrstCt, NonPrstMsgLgth, PrstCt, PrstMsgLgth, DfltPrstCt, DfltPrstMsgLgth, NAPrstCt, NAPrstMsgLgth);
    OprTrackerHead=OprTrackerCurr;

    return 0;
  }  /* if (OprTrackerHead != NULL) */ 

  return 0;

}


/********************************************************************/
/*                                                                  */
/* Function: crtOprTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function creates a OprTracker item.                       */
/*   The global variable OprTrackerCurr will be used for the return */
/*   item.                                                          */
/*                                                                  */
/********************************************************************/
int crtOprTracker(char *Operation,
                  MQLONG OprCt,
                  MQLONG NonPrstCt,
                  MQLONG NonPrstMsgLgth,
                  MQLONG PrstCt,
                  MQLONG PrstMsgLgth,
                  MQLONG DfltPrstCt,
                  MQLONG DfltPrstMsgLgth,
                  MQLONG NAPrstCt,
                  MQLONG NAPrstMsgLgth)
{
  int i;

  OprTrackerCurr=(OprTrackerItem *)malloc(sizeof(OprTrackerItem));
  if (OprTrackerCurr == NULL)
  {
    fprintf(stderr, "Failed to allocate memory(%d) for OprTracker List\n",
            (int)sizeof(OprTrackerItem));
    exit(-1);
  }
  OprTrackerCurr->prevItem=NULL;
  OprTrackerCurr->nextItem=NULL;

  OprTrackerCurr->OprCt=OprCt;
  OprTrackerCurr->NonPrstCt=NonPrstCt;
  OprTrackerCurr->NonPrstMsgLgth=NonPrstMsgLgth;
  OprTrackerCurr->PrstCt=PrstCt;
  OprTrackerCurr->PrstMsgLgth=PrstMsgLgth;
  OprTrackerCurr->DfltPrstCt=DfltPrstCt;
  OprTrackerCurr->DfltPrstMsgLgth=DfltPrstMsgLgth;
  OprTrackerCurr->NAPrstCt=NAPrstCt;
  OprTrackerCurr->NAPrstMsgLgth=NAPrstMsgLgth;

  for (i=0;i < 15;i++)
     OprTrackerCurr->Operation[i]=Operation[i];
  OprTrackerCurr->Operation[15]='\0';

  OprTrackerCurr->OptTrackerHead=NULL;
  OprTrackerCurr->OptTrackerCurr=NULL;
  OprTrackerCurr->ReasonTrackerHead=NULL;
  OprTrackerCurr->ReasonTrackerCurr=NULL;

  return 0;
}


/********************************************************************/
/*                                                                  */
/* Function: addTidTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function adds a TidTracker item to the link list if the   */
/*   item does not currently exist.                                 */
/*                                                                  */
/********************************************************************/
int addTidTracker(MQLONG tid)
{
  TidTrackerItem *TidTrackerTemp=NULL;
  TidTrackerItem *TidTrackerTemp2=NULL;
  int i;

  /*******************************************************************/
  /* Check if our TidTrackerCurr is a match, and get out, if so      */ 
  /*******************************************************************/
  if (TidTrackerCurr != NULL) 
    if (TidTrackerCurr->tid == tid) 
      return 0;

  /***************************************************************************/
  /* Check if our tid is included in the TidTracker list, and update and get */
  /* out, if so. If not, build new item and add sorted by tid in list        */ 
  /***************************************************************************/
  if (TidTrackerHead != NULL)
  {
    TidTrackerTemp=TidTrackerHead;
    while (TidTrackerTemp != NULL)
    {
      if (TidTrackerTemp->tid == tid)
      {
        TidTrackerCurr=TidTrackerTemp;
        return 0;
      }

      /************************************************************/
      /* If our current TidTracker tid is > input tid, we need to */
      /* create a new list item into our list.                    */
      /************************************************************/
      if (TidTrackerTemp->tid > tid)  
      {
        crtTidTracker(tid);

        /*******************************************************************/
        /* prevItem NULL means our current list item is the head and we    */
        /* should insert out new item at the beginning of the list.        */
        /*******************************************************************/
        if (TidTrackerTemp->prevItem == NULL)
        {
          TidTrackerHead=TidTrackerCurr;
          TidTrackerTemp->prevItem=TidTrackerHead;
          TidTrackerHead->prevItem=NULL;
          TidTrackerHead->nextItem=TidTrackerTemp;                              
          TidTrackerTemp=NULL;
        }
        /*******************************************************************/
        /* else insert item in middle of list                              */
        /*******************************************************************/
        else
        {
          TidTrackerTemp2=TidTrackerTemp->prevItem;
          TidTrackerTemp2->nextItem=TidTrackerCurr;
          TidTrackerTemp->prevItem=TidTrackerCurr;
          TidTrackerCurr->prevItem=TidTrackerTemp2;
          TidTrackerCurr->nextItem=TidTrackerTemp;
          TidTrackerTemp=NULL;
        }  /* if (TidTrackerTemp->prevItem == NULL) */ 
      }
      else
      {
        /*******************************************************************/
        /* nextItem NULL means we are at the end of the list and we should */
        /* insert a new item at the end of the list.                       */
        /*******************************************************************/
        if (TidTrackerTemp->nextItem == NULL)
        {
          crtTidTracker(tid);
          TidTrackerCurr->prevItem=TidTrackerTemp;
          TidTrackerCurr->nextItem=NULL;
          TidTrackerTemp->nextItem=TidTrackerCurr;
          TidTrackerTemp=NULL;  
        }
        /*******************************************************************/
        /* else we have more items to search in our list                   */
        /*******************************************************************/
        else
        {
          TidTrackerTemp2=TidTrackerTemp->nextItem;
          TidTrackerTemp=TidTrackerTemp2;
        }  /* if (TidTrackerTemp->nextItem == NULL) */
      }  /* if (TidTrackerTemp->pid > pid) */ 
    }  /* while (TidTrackerTemp != NULL) */
  }
  else
  /*******************************************************************/
  /* First time - allocate list, update item, and get out.           */
  /*******************************************************************/
  {
    crtTidTracker(tid);
    TidTrackerHead=TidTrackerCurr;

    return 0;
  }  /* if (TidTrackerHead != NULL) */ 

  return 0;

}


/********************************************************************/
/*                                                                  */
/* Function: crtTidTracker                                          */
/*                                                                  */
/*                                                                  */
/*   This function creates a TidTracker item.                       */
/*   The global variable TidTrackerCurr will be used for the return */
/*   item.                                                          */
/*                                                                  */
/********************************************************************/
int crtTidTracker(MQLONG tid)
{
  TidTrackerCurr=(TidTrackerItem *)malloc(sizeof(TidTrackerItem));
  if (TidTrackerCurr == NULL)
  {
    fprintf(stderr, "Failed to allocate memory(%d) for TidTracker List\n",
            (int)sizeof(TidTrackerItem));
    exit(-1);
  }
  TidTrackerCurr->prevItem=NULL;
  TidTrackerCurr->nextItem=NULL;
  TidTrackerCurr->tid=tid;

  return 0;
}


/********************************************************************/
/*                                                                  */
/* Function: skipMonitoringRecord                                   */
/*                                                                  */
/*   This function accepts parses through a PCF message skipping    */
/*   the number of structures identified in the paramterCount       */
/*   parameter.                                                     */
/*                                                                  */
/********************************************************************/
int skipMonitoringRecord(MQLONG parameterCount,
                         MQBYTE **ppbuffer,
                         MQLONG *pbuflen)
{
  int      frc = 0;                /* Function return code          */
  MQBYTE   *ptr;                   /* Current buffer pointer        */
  MQLONG   bytesLeft;              /* Number of remaining bytes     */
  MQLONG   item_count;             /* Parameter counter             */
  MQLONG   Type = 0;               /* Type of next structure        */
  MQLONG   Length = 0;             /* Length of next structure      */
  MQLONG   Parameter = 0;          /* PCF param of next structure   */
  MQLONG   StringLength = 0 ;      /* Length of next parameter      */
  MQLONG   ParameterCount = 0 ;    /* Parameter count in group      */

  bytesLeft=*pbuflen;
  ptr=*ppbuffer;
  for (item_count=0; (frc == 0) && (item_count < parameterCount); item_count++)
  {
    /****************************************************************/
    /* The first 12 bytes of every PCF structure contain its type,  */
    /* length and parameter id so check that this looks valid...    */
    /****************************************************************/
    if (bytesLeft < (sizeof(MQLONG) * 3))
    {
      fprintf(stderr, 
              "Premature end of buffer before processing complete.\n");
      frc=-1;
      break;
    }
    memcpy(&Type, (ptr + offsetof(MQCFIN, Type)), sizeof(MQLONG));
    memcpy(&Length, (ptr + offsetof(MQCFIN, StrucLength)), sizeof(MQLONG));
    memcpy(&Parameter, (ptr + offsetof(MQCFIN, Parameter)), sizeof(MQLONG));

    if (bytesLeft < Length)
    {
      fprintf(stderr, 
              "Premature end of buffer before processing complete.\n");
      frc=-1;
      break;
    }

    switch (Type)
    {
    case MQCFT_INTEGER:
    case MQCFT_INTEGER64:
    case MQCFT_STRING:
    case MQCFT_INTEGER_LIST:
    case MQCFT_INTEGER64_LIST:
    case MQCFT_STRING_LIST:
    case MQCFT_BYTE_STRING:
      bytesLeft-=Length;
      ptr+=Length;
      break;

    case MQCFT_GROUP:
      memcpy(&ParameterCount, (ptr + offsetof(MQCFGR, ParameterCount)), sizeof(MQLONG));
      ptr+=Length;
      bytesLeft-=Length;
      frc=skipMonitoringRecord(ParameterCount,
                               &ptr,
                               &bytesLeft);

      break;

    default:
      fprintf(stderr, "Error processing unknown PCF structure (%d)\n", 
              (int)Type);
      break;
    }
  }

  *ppbuffer=ptr;
  *pbuflen=bytesLeft;

  return  frc;
}

/********************************************************************/
/*                                                                  */
/* Function: getPCFDateTimeFromMsg                                  */
/*                                                                  */
/*                                                                  */
/*   This function accepts a PCF message and searches through       */
/*   the PCF structures for the identified Date Time strings.       */
/*                                                                  */
/********************************************************************/
int getPCFDateTimeFromMsg(MQBYTE *buffer,
                          MQLONG parmCount,
                          MQLONG dateParameter,
                          MQLONG timeParameter,
                          MQCHAR dateString[MQ_DATE_LENGTH+1],
                          MQCHAR timeString[MQ_DATE_LENGTH+1])
{
  MQBYTE   *bufptr;                /* Temporary buffer pointer      */
  int      item_count;             /* Loop counter                  */
  int      dateFound=FALSE;        /* Date parameter found          */
  int      timeFound=FALSE;        /* Time parameter found          */
  MQLONG   Type = 0;               /* Type of next structure        */
  MQLONG   Length = 0;             /* Length of next structure      */
  MQLONG   Parameter = 0;          /* PCF param of next structure   */
  MQLONG   StringLength = 0 ;      /* Length of next parameter      */
  MQLONG   ParameterCount = 0 ;    /* Parameter count in group      */

  bufptr=buffer;

  dateString[0]='\0';
  timeString[0]='\0';

  for (item_count=0; !(dateFound && timeFound) && (item_count < parmCount); item_count++)
  {
    memcpy(&Type, (bufptr + offsetof(MQCFIN, Type)), sizeof(MQLONG));
    memcpy(&Length, (bufptr + offsetof(MQCFIN, StrucLength)), sizeof(MQLONG));
    memcpy(&Parameter, (bufptr + offsetof(MQCFIN, Parameter)), sizeof(MQLONG));

    if (Type == MQCFT_STRING)
    {
      if (!dateFound && (Parameter == dateParameter))
      {
        memcpy(&StringLength, (bufptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        strncpy(dateString, (MQCHAR *)(bufptr + offsetof(MQCFST, String)), StringLength);
        dateString[MQ_DATE_LENGTH]='\0';
        dateFound=TRUE;
      }
      else if (!timeFound && (Parameter == timeParameter))
      {
        memcpy(&StringLength, (bufptr + offsetof(MQCFST, StringLength)), sizeof(MQLONG));
        strncpy(timeString, (MQCHAR *)(bufptr + offsetof(MQCFST, String)), StringLength);
        timeString[MQ_TIME_LENGTH]='\0';
        timeFound=TRUE;
      }
    }
    else if (Type == MQCFT_GROUP)
    {
      memcpy(&ParameterCount, (bufptr + offsetof(MQCFGR, ParameterCount)), sizeof(MQLONG));
      parmCount+=ParameterCount;
    }

    bufptr+=Length;
  }

  return(dateFound && timeFound)?0:1;
}

/* MQMBID Start */
#ifndef __MQMBID_H
  #define __MQMBID_H
  #if defined(_AIX)
    #pragma comment(user, "@(#) MQMBID sn=p750-003-140123 su=_v82gEIRJEeOSfofehNkeyQ pn=samples/c/amqsact0.c")
  #elif defined(hpux)
    #pragma VERSIONID "@(#) MQMBID sn=p750-003-140123 su=_v82gEIRJEeOSfofehNkeyQ pn=samples/c/amqsact0.c"  
  #elif defined(_LINUX_2)
    static char * __attribute__((used)) MQMBID(void) { return "@(#) MQMBID sn=p750-003-140123 su=_v82gEIRJEeOSfofehNkeyQ pn=samples/c/amqsact0.c"; }
  #elif defined(WIN32) || defined(_WIN32)
    #pragma optimize("", off)
    const static char MQMBID[]="@(#) MQMBID sn=p750-003-140123 su=_v82gEIRJEeOSfofehNkeyQ pn=samples/c/amqsact0.c";
    #pragma optimize("", on)
  #else
    static char * MQMBID(void) { return "@(#) MQMBID sn=p750-003-140123 su=_v82gEIRJEeOSfofehNkeyQ pn=samples/c/amqsact0.c"; }
  #endif
#endif
/* MQMBID End */
