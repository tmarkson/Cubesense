

#define MP_WRITE 0
#define MP_READ 1
#define MAX_NUM_MPUSB_DEV 127

#define USB_ENDPOINT_GEN 1
#define USB_ENDPOINT_STRM 2

void usbInit();
bool usbConnect();
void usbDisconnect();
void usbSendPacket(unsigned char* buffer, int size, unsigned char endpoint);
/*
char usbService(unsigned char* buf, unsigned char* buf2);
char usbStatusService();
*/

extern char usbUseUsbStream;
extern unsigned char usbVideoBuffer[LATTICE_MAX_SIZE*3];

void usbInit();
void usbCopyToUsbBuffer();
void usbHandler();
extern int usbUsbControl;
int usbServiceStatus(int s);
char usbService();
extern int usbStreamVideo;
extern int usbConnected;