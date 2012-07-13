
#define LOG_TO_FILE					0

#define LOG_THREAD_DEFAULT			1
#define LOG_THREAD_CORE				2
#define LOG_THREAD_OPENGL			3
#define LOG_THREAD_USB				4

void logInit();
void logEvent(int threadId, System::String^ e);