/** This is a sample program demonstrating the usage of double-dim array of const char* sent by reference in a function */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * add a 'box' an array of const char* texts to a container
 */
int addToContainer(char****, char***, unsigned int*);

/**
 * removes all items in the container (the size must be known) 
 */
int emptyContainer(char****, unsigned int*);

/** 
 * fills the second argument with the lists of addresses of the devices
 * which are in the container sent as the first argument
 */
int getAddressList(char****, char****, unsigned int);

/**
 * entry/ exit point
 */
int main(void)
{
    const char* szAddresses[][4] = {
        {"192.168.12.31", "192.168.12.71", "192.168.12.21", "1.0.0.1"},
        {"192.168.12.32", "192.168.12.72", "192.168.12.31", "1.0.0.1"},
        {"192.168.12.33", "192.168.12.73", "192.168.12.41", "1.0.0.1"},
                                    };
    const char* szName[] = {"XB214", "XB215", "XB216"};
    const char** szBox[][2] = {
        {(const char**)&szName[0], szAddresses[0]},
        {(const char**)&szName[1], szAddresses[1]},
        {(const char**)&szName[2], szAddresses[2]},
                               };
    unsigned int nBoxes = 0; /* the size of the container */
    
    char**** pppszCont = (char****)malloc(0xff*sizeof(char***));
    memset(pppszCont, '\0', 0xff*sizeof(char***));
    int i = 0;
    for(i = 0; i<3; i++)
    {
        addToContainer(pppszCont, szBox[i], &nBoxes);
    }
    printf("1st address: %s and 1st box: %s\n", pppszCont[0][1][0],  pppszCont[0][0][0]);
    printf("%d boxes;\n", nBoxes);
    char**** pppszAddrCont; // = (char****)malloc(0xff*sizeof(char***));
    // memset(pppszAddrCont, '\0', 0xff*sizeof(char***)); // really needed?
    
    int nAddresses = 0;
    nAddresses = getAddressList(pppszCont, pppszAddrCont, nBoxes);
    
    printf("%d addresses.\n", nAddresses);
    
    // free(pppszAddrCont);
    free(pppszCont);    
    printf("Hello, world!\n");
    return 0;
}


int addToContainer(char**** pppszCont, char*** szBox, unsigned int* pnBoxes)
{
    if(szBox)
    {
        pppszCont[*pnBoxes] = szBox;
        (*pnBoxes)++;
    }
    return *pnBoxes;
}


int emptyContainer(char**** pppszCont, unsigned int* pnBoxes)
{
    *pnBoxes = 0;
    return 0;
}

/* NOTE: causes segfault!!!!??? More?  */
int getAddressList(char**** pppszCont, char**** szAddressList, unsigned int nBoxes)
{
    int i = 0; /* counts boxes in the container */
    int j = 0; /* counts addresses in the box (there is only a name in a box) */
    unsigned int iAddrCnt = 0;
    unsigned char cF = '\0'; /* 1 if the current address is found, 0 otherwise... */
    unsigned int* pnBoxCnt = (unsigned int*)malloc(sizeof(int)*30); // count boxes
    memset(pnBoxCnt, '\0', sizeof(int)*30);
    
    return 24;
    szAddressList[0][0][0] = pppszCont[0][1][0]; /* first address in the list of addresses */
    
    szAddressList[0][0][1] = pppszCont[0][0][0]; /* add the 1st box in the 1st list of addresses */
    
    for(i = 0; i<nBoxes; i++)
    {
        for(j = 0; j<4; j++) /* addresses in box */
        {
            if(!pppszCont[i][1][j]) break; /* if there is no address or is null */
            int k = 0;
            for(k = 0; k<iAddrCnt; k++)
            {
                if(0==strcmp(pppszCont[i][1][j], szAddressList[iAddrCnt][k][0])) /* if  */
                { /* add a new box in the box list of this address */
                    szAddressList[k][0][pnBoxCnt[k]] = pppszCont[i][0][0]; /* the box name in the list */
                    cF = '\1'; /* found */
                    break;
                }
            }
            if(!cF) /* add a new address and its box as well */
            {
                iAddrCnt++; // only then increase the number of addresses...
                szAddressList[iAddrCnt][0][pnBoxCnt[iAddrCnt]] = pppszCont[i][1][0]; /* the address */
                szAddressList[iAddrCnt][0][pnBoxCnt[iAddrCnt]] = pppszCont[i][0][0]; /* the box name in the list */
                /* no additional check if the box exists, it is exists for sure! */
            }
            pnBoxCnt[iAddrCnt]++; /* and increase the box count */
        }
    }
    free(pnBoxCnt);
    return iAddrCnt; /* how many addresses */
}

