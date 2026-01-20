/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */



// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <string.h>
#include <malloc.h>
#include <inttypes.h>   // required to print out pointers using PRIXPTR macro
#include "definitions.h"                // SYS function prototypes
#include "asmExterns.h"
#include "testFuncs.h" // lab test structs
#include "printFuncs.h"  // lab print funcs

#define MAX_PRINT_LEN 1000

#define USING_HW 1

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void printAndWait(char *txBuffer, volatile bool *txCompletePtr)
{
    *txCompletePtr = false;

#if USING_HW 
    DMAC_ChannelTransfer(DMAC_CHANNEL_0, txBuffer, \
        (const void *)&(SERCOM5_REGS->USART_INT.SERCOM_DATA), \
        strlen((const char*)txBuffer));
    // spin here, waiting for timer and UART to complete
    while (*txCompletePtr == false); // wait for print to finish
    /* reset it for the next print */
    *txCompletePtr = false;
#endif

}

// print the mem addresses of the global vars at startup
// this is to help the students debug their code
void printGlobalAddresses(char *txBuffer, volatile bool *txComplete)
{
    // build the string to be sent out over the serial lines
    snprintf((char*)txBuffer, MAX_PRINT_LEN,
            "========= GLOBAL VARIABLES MEMORY ADDRESS LIST\r\n"
            "global variable \"a_Multiplicand\" stored at address: 0x%" PRIXPTR "\r\n"
            "global variable \"b_Multiplier\" stored at address:   0x%" PRIXPTR "\r\n"
            "global variable \"rng_Error\" stored at address:      0x%" PRIXPTR "\r\n"
            "global variable \"a_Sign\" stored at address:         0x%" PRIXPTR "\r\n"
            "global variable \"b_Sign\" stored at address:         0x%" PRIXPTR "\r\n"
            "global variable \"prod_Is_Neg\" stored at address:    0x%" PRIXPTR "\r\n"
            "global variable \"a_Abs\" stored at address:          0x%" PRIXPTR "\r\n"
            "global variable \"b_Abs\" stored at address:          0x%" PRIXPTR "\r\n"
            "global variable \"init_Product\" stored at address:   0x%" PRIXPTR "\r\n"
            "global variable \"final_Product\" stored at address:  0x%" PRIXPTR "\r\n"
            "========= END -- GLOBAL VARIABLES MEMORY ADDRESS LIST\r\n"
            "\r\n",
            (uintptr_t)(&a_Multiplicand), 
            (uintptr_t)(&b_Multiplier), 
            (uintptr_t)(&rng_Error), 
            (uintptr_t)(&a_Sign), 
            (uintptr_t)(&b_Sign), 
            (uintptr_t)(&prod_Is_Neg), 
            (uintptr_t)(&a_Abs), 
            (uintptr_t)(&b_Abs),
            (uintptr_t)(&init_Product), 
            (uintptr_t)(&final_Product)
            ); 
    printAndWait((char *)txBuffer, txComplete);
}

/* *****************************************************************************
 End of File
 */
