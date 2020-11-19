#include <stdio.h> //printf
#include <fcntl.h> //open
#include <sys/mman.h> //mmap
#include <bcm_host.h> //gpio address
#include <string.h> //strcpy
#include <ctype.h> //tolower
#include "gpioreg.h"

#define _DEFAULTERROR "Enter a GPIO register offset between 0 and 60 (or 0x00 to 0xf0).\nUse 'readpin -help' for more info.\n"


int main (int argc, char *argv[]) 
{

    InitPins();
    
    unsigned p_num = 'z'; 
    if (argc == 2) {
        unsigned size = strlen(argv[1]);
        if(size > 2) { 
            if ( (size == 4) && (argv[1][0]-48 == 0) )
            { 
                // convert to int from hex
                int tot = StrHexToInt(argv[1]);
                p_num = tot/4;
            }
            // iterate through all known reg names
            // compare argv[1] 
           else {
               char yn = 0;
                for(int v = 0; v < 61; v++)
                {
                    if ( strcmp(argv[1], pins[v].name) == 0)
                    {
                        //printf("found %s\n", pins[v].name);
                        p_num = v;
                        yn = 1;
                    }
                }
                if (yn == 0) {
                    printf(_DEFAULTERROR); 
                    return -1;
                }
            } 
        }
        else if(size == 2) { 
            p_num = (10 * (argv[1][0]-48)) + (argv[1][1]-48); 
            if (p_num > 60) { 
                printf(_DEFAULTERROR); 
                return -1; 
            }
        }
        else { 
            p_num = argv[1][0] - 48; 
        }
    }
    
    // Ensure GPIO memory is accessible
    int fdgpio = open("/dev/gpiomem", O_RDWR);
    if (fdgpio < 0) 
    { printf("Error!\n"); return -1; }
    
    // Map locally
    unsigned int *gpio = (unsigned int*)mmap(
     0, 256,
     PROT_READ|PROT_WRITE, MAP_SHARED,
     fdgpio, 0
    );
    
    // Just to check what is reported by the system
    unsigned pa = bcm_host_get_peripheral_address();
    printf("Peripheral addr: %#010x\n", pa);

    // Print the table    
    printf("GPIO Ofs |   Value    |   Name\n");
    if (p_num == 'z') {
        for (char i = 0; i < 61; i++)
        {
            // Skip unused addresses
            if (i != 6 && i != 9 && i != 12 && i != 15 && i != 18
             && i != 21 && i != 24 && i != 27 && i != 30 && i != 33)
            {
                if (i < 36 || i > 56){
                    for(unsigned p = 0; p < 32; p++)
                    {
                        binaryout[p] = 0;
                    }
                    // Print each register info
                    if (gpio[i] == '\0') {
                        printf("  %#04x : 0x00000000 : %s%s%s\n", i*4, _FG _BRWHITE, 
                         pins[i].name, _RESET);
                        
                    }
                    else { 
                        printf("  %#04x : %#010p : %s%s%s\n", i*4, gpio[i], 
                         _FG _BRWHITE, pins[i].name, _RESET);
                        GetBinary(gpio[i]); 
                    }
                    // and individual bits 
                    PrintBinOut(pins[i]);
                }
            }
            else {
                if (i >= 36 && i <= 56)
                    printf("Invalid GPIO register offset.");
            }
        }
    }
    else {
        for(unsigned p = 0; p < 32; p++)
            { binaryout[p] = 0; }
        if (gpio[p_num] == '\0') {
            printf("  %#04x : 0x00000000 : %s%s%s\n", p_num*4, _FG _BRWHITE, 
                pins[p_num].name, _RESET);
        }
        else { 
            printf("  %#04x : %#010p : %s%s%s\n", p_num*4, gpio[p_num], 
                _FG _BRWHITE, pins[p_num].name, _RESET);
            GetBinary(gpio[p_num]); 
        }
        PrintBinOut(pins[p_num]);
        printf("%s", pins[p_num].desc);
    }
    // Unmap memory!
    munmap(gpio, 256);
    
    return 0;
}


