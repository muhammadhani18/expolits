#include <stdlib.h>

void C_Application_Firewall(char* in_buff) {
    for(char c = *in_buff++; c!= '\x00'; c = *in_buff++) {
        if(c == 'A') {
            printf("You have been blocked\n");
            exit(-1);
        }
    }
}

void CAFTest() {
    char buf[256] = {0};
    printf("\nPlease Enter a payload: ");
    gets(buf); //gets is a dangerous function which has format string vulnerability

    C_Application_Firewall(buf);
    printf(buf);
}

int main() {
    while(1) {
        CAFTest();
    }
}