
void scriptInit();

extern unsigned char *scriptSourceCode;
extern unsigned int scriptSourceCodeLength;
extern unsigned int scriptReadyToRun;
extern unsigned int scriptReadyToRunRealTime;
extern unsigned int scriptType;

extern unsigned char scriptErrors[];
extern unsigned int scriptErrorCount;
extern int scriptStopScript;

void scriptHandler();

#define SCRIPT_ERRORS_COUNT				1024
#define SCRIPT_SINGLE_ERROR_LENGTH		1024
#define SCRIPT_ERRORS_LENGTH			(SCRIPT_ERRORS_COUNT*SCRIPT_SINGLE_ERROR_LENGTH)

#define SCRIPT_EXTRA_LINES_VB			8
#define SCRIPT_EXTRA_LINES_CS			9


#define SCRIPT_TYPE_VB					1
#define SCRIPT_TYPE_CS					2
#define SCRIPT_TYPE_CRT					3

unsigned int scriptErrorRow[];
extern int scriptRunning;

void scriptRealTimeHandler();


extern int scriptRealTimeCommand;
extern char* scriptGlBuffer;
extern int scriptSoundFft[1024];