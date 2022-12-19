#include <sys/io.h>

#include <fstream>
#include <iostream>

#include <iostream>

void WaitDevice()
{
    unsigned char state;
    do state = _inp(0x3F6);
    while (state & (1 << 7));
}
bool Initialization(const int command){
    unsigned char regData = (0 << 4) + (7 << 5);
    bool flag = false;

    WaitDevice();
    _outp(0x1F6, regData);

    for (int j = 0; j < 1000; j++)
    {
        unsigned char state = _inp(0x3F6);
        if(state & (1 << 6))
        {
            flag = true;
            break;
        }
    }
    if (!flag) return false;

    _outp(0x1F7, command);
    WaitDevice();

    unsigned char curState = _inp(0x1F7);
    if(!(curState & (1 << 3)))
    {
        if(command == 0xEC) return false;
        return true;
    }
    else return true;
}
void PrintDeviceInfo(unsigned short *device_info)
{
    printf("?: ");
    for(int i = 27; i <= 46; i++) printf("%c%c", device_info[i] >> 8, device_info[i] & 0x00FF );

    printf("\n---------------------------------------------\n");
    printf("??: ");
    for( int i = 10; i <= 19; i++ ) printf("%c%c", device_info[i] >> 8, device_info[i] & 0x00FF );

    printf("\n---------------------------------------------\n");
    printf("???: ");
    for( int i = 23; i <= 26; i++ ) printf("%c%c", device_info[i] >> 8, device_info[i] & 0x00FF );

    printf("\n---------------------------------------------\n");
    printf("????: ");
    if(device_info[0] & (1 << 15))	printf("ATAPI\n");
    else printf("ATA\n");

    printf("---------------------------------------------\n");
    if(!(device_info[0] & (1 << 15))) printf("Ðàçìåð: %.0lf áàéò\n", (long double)(((unsigned long *)device_info)[30]) * 512);

    printf("---------------------------------------------\n");
    printf("Programmable Input Output:\n");
    if (device_info[64] & 1) printf("Mode 3\n");
    if (device_info[64] & 2) printf("Mode 4\n");

    printf("---------------------------------------------\n");
    printf("Multiword Direct Memory Access:\n");
    if (device_info[63] & 1) printf("Mode 0\n");
    if (device_info[63] & 2) printf("Mode 1\n");
    if (device_info[63] & 4) printf("Mode 2\n");

    printf("---------------------------------------------\n");
    printf("Ultra Direct Memory Access:\n");
    if (device_info[88] & 1) printf("Mode 1\n");
    if (device_info[88] & 2) printf("Mode 2\n");
    if (device_info[88] & 3) printf("Mode 3\n");
    if (device_info[88] & 4) printf("Mode 4\n");
    if (device_info[88] & 5) printf("Mode 5\n");
    printf("\n");
}
int main()
{
//    setlocale(LC_ALL, "Russian");

    if (iopl(3)) {
        perror("Root privileges required");
        exit(EXIT_FAILURE);
    }

    unsigned short device_info[256] = {};

    if (!Initialization(0xA1)) return 0;
    if (!Initialization(0xEC)) return 0;

    for( int i = 0; i < 256; i++ )
    {
        device_info[i] = _inpw(0x1F0);
    }

    PrintDeviceInfo(device_info);
    return 0;
}