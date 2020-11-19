//readpin.h

#define _FG "\e[3"
#define _BG "\e[4"

#define _BLACK "0m"
#define _RED "1m"
#define _GREEN "2m"
#define _YELLOW "3m"
#define _BLUE "4m"
#define _MAGENTA "5m"
#define _CYAN "6m"
#define _WHITE "7m"

#define _BRBLACK "0;1m"
#define _BRRED "1;1m"
#define _BRGREEN "2;1m"
#define _BRYELLOW "3;1m"
#define _BRBLUE "4;1m"
#define _BRMAGENTA "5;1m"
#define _BRCYAN "6;1m"
#define _BRWHITE "7;1m"

#define _RESET "\e[0;0m"

unsigned binaryout[32];

#define READONLY 0
#define WRITEONLY 1
#define READWRITE 2
#define WRITE1CLR 3
#define _BR "\n"

#define _FUNCSELSTR "000 : Input mode\n001 : Output mode"_BR"100 : Alt function 0\n101 : Alt function 1\n110 : Alt function 2"_BR"111 : Alt function 3\n011 : Alt function 4\n010 : Alt function 5"_BR

struct Pin {
    unsigned addr;
    char name[24];
    char desc[512];
    unsigned usable; // (usable-n) unreserved pins
    char rw; // 0 RO, 1 = WO, 2 = RW, 3 = W1C
}; 

struct Pin pins[61];    


int StrHexToInt(char ar[])
{
    unsigned hi = toupper(ar[2])-48;
    unsigned lo = toupper(ar[3])-48;
    if (hi > 9) hi = hi - 7;
    if (lo > 9) lo = lo - 7;
    return (hi * 16) + lo;
}

void InitPins(void)
{
    strcpy(pins[0].name, "GPFSEL0");
    pins[0].usable = 30;
    strcpy(pins[0].desc, _FG _BRBLUE"    ===---===---===---===---===---\n"_RESET
     _FG _WHITE"(32) 9  8  7  6  5  4  3  2  1  0 (0)\n"_RESET
     "Function select for GPIO pins 0-9.\n"_FUNCSELSTR);
    strcpy(pins[1].desc, _FG _BRBLUE"    ===---===---===---===---===---\n"_RESET
     _FG _WHITE"(32) 19 18 17 16 15 14 13 12 11 10 (0)\n"_RESET
     "Function select for GPIO pins 10-19.\n"_FUNCSELSTR);
    strcpy(pins[2].desc, _FG _BRBLUE"    ===---===---===---===---===---\n"_RESET
     _FG _WHITE"(32) 29 28 27 26 25 24 23 22 21 20 (0)\n"_RESET
     "Function select for GPIO pins 20-29.\n"_FUNCSELSTR);
    strcpy(pins[3].desc, _FG _BRBLUE"    ===---===---===---===---===---\n"_RESET
     _FG _WHITE"(32) 39 38 37 36 35 34 33 32 31 30 (0)\n"_RESET
     "Function select for GPIO pins 30-39.\n"_FUNCSELSTR);
    strcpy(pins[4].desc, _FG _BRBLUE"    ===---===---===---===---===---\n"_RESET
     _FG _WHITE"(32) 49 48 47 46 45 44 43 42 41 40 (0)\n"_RESET
     "Function select for GPIO pins 40-49.\n"_FUNCSELSTR);
    strcpy(pins[5].desc, _FG _BRBLUE"          ===---===---===---===---\n"_RESET
     _FG _WHITE"(32)       57 56 55 54 53 52 51 50 (0)\n"_RESET
     "Function select for GPIO pins 50-57.\n"_FUNCSELSTR);
    
    for(int pi = 0; pi < 61; pi++) pins[pi].rw = 2;
    for(int pi = 7; pi < 12; pi++) pins[pi].rw = WRITEONLY;
    for(int pi = 12; pi < 16; pi++) pins[pi].rw = READONLY;   
    pins[16].rw = WRITE1CLR;
    pins[17].rw = WRITE1CLR; 
    strcpy(pins[1].name, "GPFSEL1");
    pins[1].usable = 30;
    strcpy(pins[2].name, "GPFSEL2");
    pins[2].usable = 30;
    strcpy(pins[3].name, "GPFSEL3");
    pins[3].usable = 30;
    strcpy(pins[4].name, "GPFSEL4");
    pins[4].usable = 30;
    strcpy(pins[5].name, "GPFSEL5");
    pins[5].usable = 24;
    
    strcpy(pins[7].name, "GPSET0");
    pins[7].usable = 32;
    strcpy(pins[8].name, "GPSET1");
    pins[8].usable = 26;
    
    strcpy(pins[10].name, "GPCLR0");
    pins[10].usable = 32;
    strcpy(pins[11].name, "GPCLR1");
    pins[11].usable = 26;
    
    strcpy(pins[13].name, "GPLEV0");
    pins[13].usable = 32;
    strcpy(pins[14].name, "GPLEV1");
    pins[14].usable = 26;
    
    strcpy(pins[16].name, "GPEDS0");
    pins[16].usable = 32;
    strcpy(pins[17].name, "GPEDS1");
    pins[17].usable = 26;
    
    strcpy(pins[19].name, "GPREN0");
    pins[19].usable = 32;
    strcpy(pins[20].name, "GPREN1");
    pins[20].usable = 26;
    
    strcpy(pins[22].name, "GPFEN0");
    pins[22].usable = 32;
    strcpy(pins[23].name, "GPFEN1");
    pins[23].usable = 26;
    
    strcpy(pins[25].name, "GPHEN0");
    pins[25].usable = 32;
    strcpy(pins[26].name, "GPHEN1");
    pins[26].usable = 26;
    
    strcpy(pins[28].name, "GPLEN0");
    pins[28].usable = 32;
    strcpy(pins[29].name, "GPLEN1");
    pins[29].usable = 26;
    
    strcpy(pins[31].name, "GPAREN0");
    pins[31].usable = 32;
    strcpy(pins[32].name, "GPAREN1");
    pins[32].usable = 26;
    
    strcpy(pins[34].name, "GPAFEN0");
    pins[34].usable = 32;
    strcpy(pins[35].name, "GPAFEN1");
    pins[35].usable = 26;
    
    strcpy(pins[57].name, "GPIO_PUP_PDN_CNTRL_REG0");
    pins[57].usable = 32;
    strcpy(pins[58].name, "GPIO_PUP_PDN_CNTRL_REG1");
    pins[58].usable = 32;
    strcpy(pins[59].name, "GPIO_PUP_PDN_CNTRL_REG2");
    pins[59].usable = 32;
    strcpy(pins[60].name, "GPIO_PUP_PDN_CNTRL_REG3");
    pins[60].usable = 30;
}
    
void GetBinary(unsigned gval)
{
// Converts gval to binaryout[]
    for(int b = 31; gval > 0; b--)
    {
        binaryout[b] = gval % 2;
        gval = gval / 2;
    }
    return;
}

void PrintBinOut(struct Pin p)
// Prints individual pins from binaryout[] as binary string 
{
    printf(" (");
    for (int c = 0; c < 32; c++)
    {
        if (32 - p.usable <= c)
        {
            if (binaryout[c] == 1) printf(_FG _BRGREEN);
            if (binaryout[c] == 0) printf(_FG _BRRED);
            printf("%u", binaryout[c]);
            printf(_RESET);
        }
        else
            printf(_FG _WHITE "." _RESET);
        
    }
    printf(") [");
    if (p.rw == 2) printf("R/W]");
    if (p.rw == 0) printf("RO]");
    if (p.rw == 1) printf("WO]");
    if (p.rw == 3) printf("W1C]");
    printf("\n");
}

