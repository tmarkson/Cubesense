#include "windows.h"

extern HANDLE threadMutexScriptStatus;

void threadsInit();
void threadsRun();
void threadsClean();
void threadCopyContentDefaultCoreIn();
void threadCopyContentDefaultCoreOut();
void threadCopyContentDefaultOpenglIn();
void threadCopyContentDefaultOpenglOut();
void threadCopyContentCoreOpenglIn();
void threadCopyContentCoreOpenglOut();
void threadCopyContentDefaultOpenglInit();
void threadCopyContentDefaultUsbIn();
void threadCopyContentDefaultUsbOut();
void threadCopyContentCoreUsbIn();
void threadCopyContentCoreUsbOut();
void threadCopyContentCoreOpenglInit();


extern HANDLE threadMutexCopyContentCoreOpengl;
extern unsigned char threadVideoBuffer[];

void threadCopyContentAudioCoreIn();
void threadCopyContentAudioCoreOut();


extern unsigned char threadUsbVideoBuffer[];