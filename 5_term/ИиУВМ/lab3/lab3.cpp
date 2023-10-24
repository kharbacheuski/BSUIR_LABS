#include "stdafx.h"
#include "hexioctrl.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>

#define IDENTIFY_DEVICE 		0xEC
#define IDENTIFY_PACKET_DEVICE	0xA1

const int dataRegister[2] = {0x1F0, 0x170};
const int DH_register[2] = {0x1F6, 0x176};
const int StateCommandRegister[2] = {0x1F7, 0x177};
const int altStateRegister[2] = {0x3F6, 0x376};

unsigned short data[256];

void waitDeviceBusy(int channelNum);
bool getDeviceInfo(int devNum, int channelNum);
void showTable();
bool waitReady(int channelNum);


int main()
{
    ALLOW_IO_OPERATIONS;

	std::cout << " Model                                  | Serial Number      |Type | Size   | PIO         | Multiword DMA | Ultra DMA         |" << std::endl;
	std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    for(int channel = 0; channel <= 1; channel++) {
        for(int device = 0; device <= 1; device++)
        {              
            if(getDeviceInfo(device, channel)) 
            {
                showTable();
            }
        }
    }

    system("pause");
    return 0;
}


bool waitReady(int channelNum)
{
    for (int i = 0; i < 1000; i++)
    {
        unsigned char state = _inp(altStateRegister[channelNum]);
        if(state & (1 << 6)) return true;
    }
    return false;
}


void  waitDeviceBusy(int channelNum)
{
    unsigned char state;
    do state = _inp(altStateRegister[channelNum]);
    while (state & (1 << 7));
}

bool getDeviceInfo(int devNum, int channelNum)
{  
    const int commands[2] = {IDENTIFY_PACKET_DEVICE, IDENTIFY_DEVICE};
    for (int i = 0; i < 2; i++)
    {
        waitDeviceBusy(channelNum);

        unsigned char regData = (devNum << 4) + (7 << 5); //111X0000
        _outp(DH_register[channelNum], regData); //device in DH

        if(!waitReady(channelNum))  return false;      

        _outp(StateCommandRegister[channelNum], commands[i]);

        waitDeviceBusy(channelNum);
    }

    for( int i = 0; i < 256; i++ )
        data[i] = _inpw(dataRegister[channelNum]);
   
    return true;
}

void showTable()
{
	//model
    for(int i = 27; i <= 46; i++)
        printf("%c%c", data[i] >> 8, data[i] & 0x00FF );

	std::cout<<"|";

	//serial number
    for( int i = 10; i <= 19; i++ )
        printf("%c%c", data[i] >> 8, data[i] & 0x00FF );

	std::cout<<"|";

	int isAtapi = data[0] & (1 << 15);
    if(isAtapi) 
		printf("ATAPI");
    else 
		printf("ATA  ");

	std::cout<<"|";

    if(!isAtapi)
    {
        printf("%lu", ((unsigned long *)data)[30] >> 1);	
    }
	else
		printf("        ");	

	std::cout <<"|";

	
    printf("[%s%s", (data[64] & 1) ? "+" : "-" ,"] PIO 3    |" );
	std::cout << std::endl;
    
	printf("\t\t\t\t\t\t\t\t\t    |[%s%s", (data[64] & 2) ? "+" : "-" ,"] PIO 4    |" );
	std::cout << std::endl;
    
	printf("\t\t\t\t\t\t\t\t\t\t\t  |[%s%s", (data[63] & 1) ? "+" : "-" ,"] MWDMA 0    |" );
	std::cout << std::endl;
	
	printf("\t\t\t\t\t\t\t\t\t\t\t  |[%s%s", (data[63] & 2) ? "+" : "-" ,"] MWDMA 1    |" );
	std::cout << std::endl;

	printf("\t\t\t\t\t\t\t\t\t\t\t  |[%s%s", (data[63] & 4) ? "+" : "-" ,"] MWDMA 2    |" );
	std::cout << std::endl;
	
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t  |[%s%s", (data[88] & 1) ? "+" : "-" ,"] UDMA Mode 0    |" );
	std::cout << std::endl;

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t  |[%s%s", (data[88] & (1 << 1)) ? "+" : "-" ,"] UDMA Mode 1    |" );
    std::cout << std::endl;

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t  |[%s%s", (data[88] & (1 << 2)) ? "+" : "-" ,"] UDMA Mode 2    |" );
    std::cout << std::endl;

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t  |[%s%s", (data[88] & (1 << 3)) ? "+" : "-" ,"] UDMA Mode 3    |" );
    std::cout << std::endl;

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t  |[%s%s", (data[88] & (1 << 4)) ? "+" : "-" ,"] UDMA Mode 4    |" );
    std::cout << std::endl;

	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t  |[%s%s", (data[88] & (1 << 5)) ? "+" : "-" ,"] UDMA Mode 5    |" );
	
	std::cout << std::endl;
}