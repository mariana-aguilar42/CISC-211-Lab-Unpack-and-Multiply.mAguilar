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

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

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


#define MAX_PRINT_LEN 2000

static uint8_t txBuffer[MAX_PRINT_LEN] = {0};


static char * pass = "PASS";
static char * fail = "FAIL";
static char * oops = "OOPS!!!";



/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */
static void check(int32_t in1, 
        int32_t in2, 
        int32_t *goodCount, 
        int32_t *badCount,
        char **pfString )
{
    if (in1 == in2)
    {
        *goodCount += 1;
        *pfString = pass;
    }
    else
    {
        *badCount += 1;
        *pfString = fail;        
    }
    return;
}

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
int32_t calcExpectedValues(
            int32_t testNum, 
            char *desc, 
            uint32_t packedValue,
            expectedValues *e)
{
    e->packedVal = packedValue;
    // calculate sign-extended A and B
    
    // Multiplicand A
    e->inputA = 0;
    e->inputB = 0;
    // unpack A
    e->inputA =  packedValue>>16;
    e->signA = e->inputA & 0x8000;
    if (e->signA != 0)
    {
        e->signA = 1;
        e->inputA = e->inputA | 0xFFFF8000;
    }
    e->absA = abs(e->inputA);
    
    // Multiplicand B
    // unpack B
    e->signB = packedValue & 0x8000;
    if (e->signB != 0)
    {
        e->signB = 1;
        e->inputB = packedValue | 0xFFFF8000;
    }
    else
    {
        e->inputB = packedValue & 0x0000FFFF;
    }
    e->absB = abs(e->inputB);
    
    e->initProduct = e->absA * e->absB;
    e->finalProduct = e->inputA * e->inputB;

    return 0;
}





void resetGlobalVars()
{
    a_Multiplicand = 0x42424242;
    b_Multiplier = 0x42424242;
    rng_Error = 0x42424242;
    a_Sign = 0x42424242;
    b_Sign = 0x42424242;
    prod_Is_Neg = 0x42424242;
    a_Abs = 0x42424242;
    b_Abs = 0x42424242;
    init_Product = 0x42424242;
    final_Product = 0x42424242; 
}

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void testAsmUnpack(
        int32_t testNum, // test number
        char *desc, // optional description, or ""
        uint32_t packedVal, // inputs
        int32_t * unpackedA,     // outputs
        int32_t * unpackedB,
        int32_t inputA,    // expected values
        int32_t inputB,
        uint32_t sp_before,
        uint32_t sp_after,
        int32_t * passCount,
        int32_t * failCount,
        bool onlyPrintFails,
        volatile bool * txComplete
        )
{
    *failCount = 0;
    *passCount = 0;
    char *aCheck = oops;
    char *bCheck = oops;
    char *spCheck = oops;  // check that the SP was correct after the return
    
    check(inputA, *unpackedA, passCount, failCount, &aCheck);
    check(inputB, *unpackedB, passCount, failCount, &bCheck);
    check(sp_before, sp_after, passCount, failCount, &spCheck);

    if( onlyPrintFails == false || ((onlyPrintFails == true) && (*failCount != 0)))
    {
    // build the string to be sent out over the serial lines
    snprintf((char*)txBuffer, MAX_PRINT_LEN,
            "========= testAsmUnpack %s test number: %ld\r\n"
            "packed (input) value:    0x%08lx\r\n"
            "unpacked A (multiplicand) value: %11ld; 0x%08lx\r\n"
            "expected A (multiplicand) value: %11ld; 0x%08lx\r\n"
            "unpacked B (multiplier) value:   %11ld; 0x%08lx\r\n"
            "expected B (multiplier) value:   %11ld; 0x%08lx\r\n"
            "SP value after return from call: 0x%08lx\r\n"
            "Expected Stack Ptr Value:        0x%08lx\r\n"
            "unpacked A pass/fail:            %s\r\n"
            "unpacked B pass/fail:            %s\r\n"
            "Stack Ptr Check pass/fail:       %s\r\n"
            "========= END -- testAsmUnpack() debug output\r\n"
            "\r\n",
            desc,
            testNum,
            packedVal, 
            *unpackedA,*unpackedA,
            inputA,inputA,
            *unpackedB,*unpackedB,
            inputB,inputB,
            sp_before,
            sp_after,
            aCheck,bCheck,spCheck
            ); 

    printAndWait((char *)txBuffer, txComplete);
    }
    return ;
};

void testAsmAbs(
        int32_t testNum, // test number
        char *desc, // optional description, or ""
        int32_t signedInput,  //inputs
        int32_t * absVal,        // I/O
        int32_t * signBit,
        int32_t r0_absVal,   // outputs
        int32_t expAbs,  // expected values
        int32_t expSignBit,  // expected values
        uint32_t sp_before,
        uint32_t sp_after,
        int32_t * passCount,
        int32_t * failCount,
        bool onlyPrintFails,
        volatile bool * txComplete
        )
{
    *failCount = 0;
    *passCount = 0;
    char *absMemCheck = oops;
    char *sbMemCheck = oops;
    char *r0Check = oops;
    char *spCheck = oops;
    
    check(expAbs, *absVal, passCount, failCount, &absMemCheck);
    check(expAbs, r0_absVal, passCount, failCount, &r0Check);
    check(expSignBit, *signBit, passCount, failCount, &sbMemCheck);

    if( onlyPrintFails == false || ((onlyPrintFails == true) && (*failCount != 0)))
    {
    // build the string to be sent out over the serial lines
    snprintf((char*)txBuffer, MAX_PRINT_LEN,
            "========= testAsmAbs %s test number: %ld\r\n"
            "signed input value:    0x%08lx\r\n"
            "abs value stored in mem:  %11ld; 0x%08lx; %s\r\n"
            "abs value returned in r0: %11ld; 0x%08lx; %s\r\n"
            "sign bit stored in mem:   %11ld; 0x%08lx; %s\r\n"
            "expected abs value:   %11ld; 0x%08lx\r\n"
            "expected sign bit:    %11ld\r\n"
            "Expected and Actual SP: 0x%08lx; 0x%08lx; %s\r\n"
            "========= END -- testAsmAbs() debug output\r\n"
            "\r\n",
            desc,
            testNum,
            signedInput, 
            *absVal,*absVal,absMemCheck,
            r0_absVal,r0_absVal,r0Check,
            *signBit,*signBit,sbMemCheck,
            expAbs,expAbs,
            expSignBit,
            sp_before, sp_after, spCheck
            ); 

    printAndWait((char *)txBuffer, txComplete);
    }
    return ;
}


void testAsmMult(
        int32_t testNum, // test number
        char *desc, // optional description, or ""
        int32_t absA, // inputs
        int32_t absB,
        int32_t r0_initProd, // outputs
        int32_t expectedInitProduct, // expected values
        uint32_t sp_before,
        uint32_t sp_after,
        int32_t * passCount,
        int32_t * failCount,
        bool onlyPrintFails,
        volatile bool * txComplete
        )
{
    *failCount = 0;
    *passCount = 0;
    char *prodCheck = oops;
    char *spCheck = oops;
    
    check(expectedInitProduct, r0_initProd, passCount, failCount, &prodCheck);
    check(sp_before, sp_after, passCount, failCount, &spCheck);

    if( onlyPrintFails == false || ((onlyPrintFails == true) && (*failCount != 0)))
    {
    // build the string to be sent out over the serial lines
    snprintf((char*)txBuffer, MAX_PRINT_LEN,
            "========= testAsmMult %s test number: %ld\r\n"
            "Inputs:\r\n"
            "abs value A:             %11ld; 0x%08lx\r\n"
            "abs value B:             %11ld; 0x%08lx\r\n"
            "Output:\r\n"
            "product abs(A) * abs(B): %11ld; 0x%08lx; %s\r\n"
            "Expected product:        %11ld; 0x%08lx\r\n"
            "Expected and Actual SP: 0x%08lx; 0x%08lx; %s\r\n"
            "========= END -- testAsmMult() debug output\r\n"
            "\r\n",
            desc,
            testNum,
            absA,absA,
            absB,absB,
            r0_initProd,r0_initProd,prodCheck,
            expectedInitProduct,expectedInitProduct,
            sp_before, sp_after, spCheck
            ); 

    printAndWait((char *)txBuffer, txComplete);
    }
    return;
}

void testAsmFixSign(
        int32_t testNum, // test number
        char *desc, // optional description, or ""
        uint32_t initProduct, // inputs
        int32_t signA, 
        int32_t signB,
        int32_t r0_finalProduct, // outputs
        int32_t expectedFinalProduct, // expected values
        uint32_t sp_before,
        uint32_t sp_after,
        int32_t * passCount,
        int32_t * failCount,
        bool onlyPrintFails,
        volatile bool * txComplete
        )
{
    *failCount = 0;
    *passCount = 0;
    char *prodCheck = oops;
    char *spCheck = oops;
    
    check(expectedFinalProduct, r0_finalProduct, passCount, failCount, &prodCheck);
    check(sp_before, sp_after, passCount, failCount, &spCheck);

    if( onlyPrintFails == false || ((onlyPrintFails == true) && (*failCount != 0)))
    {
    // build the string to be sent out over the serial lines
    snprintf((char*)txBuffer, MAX_PRINT_LEN,
            "========= testAsmFixSign %s test number: %ld\r\n"
            "Inputs:\r\n"
            "Initial (unsigned) product: %11ld; 0x%08lx\r\n"
            "sign bit A:                 %ld\r\n"
            "sign bit B:                 %ld\r\n"
            "Output:\r\n"
            "Final (signed) product:     %11ld; 0x%08lx; %s\r\n"
            "Expected product:           %11ld; 0x%08lx\r\n"
            "Expected and Actual SP: 0x%08lx; 0x%08lx; %s\r\n"
            "========= END -- testAsmFixSign() debug output\r\n"
            "\r\n",
            desc,
            testNum,
            initProduct,initProduct,
            signA,
            signB,
            r0_finalProduct,r0_finalProduct,prodCheck,
            expectedFinalProduct,expectedFinalProduct,
            sp_before, sp_after, spCheck
            ); 

    printAndWait((char *)txBuffer, txComplete);
    }
    return;
}



void testAsmMain(
        int32_t testNum, // test number
        char *desc, // optional description, or ""
        uint32_t packedVal, // inputs
        int32_t r0_mainFinalProd, // outputs
        int32_t a,
        int32_t b,
        int32_t aAbs, 
        int32_t aSign, 
        int32_t bAbs, 
        int32_t bSign,
        int32_t initProduct,
        int32_t finalProduct,
        expectedValues * exp, // expected values
        uint32_t sp_before,
        uint32_t sp_after,
        int32_t * passCount,
        int32_t * failCount,
        bool onlyPrintFails,
        volatile bool * txComplete
        )
{
    *failCount = 0;
    *passCount = 0;
    char *aCheck = oops;
    char *bCheck = oops;
    char *aSignCheck = oops;
    char *bSignCheck = oops;
    char *aAbsCheck = oops;
    char *bAbsCheck = oops;
    char *initProdCheck = oops;
    char *finalProdCheck = oops;
    char *r0Check = oops;
    char *spCheck = oops;

    check(exp->inputA, a, passCount, failCount, &aCheck);
    check(exp->inputB, b, passCount, failCount, &bCheck);
    check(exp->signA, aSign, passCount, failCount, &aSignCheck);
    check(exp->signB, bSign, passCount, failCount, &bSignCheck);
    check(exp->absA, aAbs, passCount, failCount, &aAbsCheck);
    check(exp->absB, bAbs, passCount, failCount, &bAbsCheck);
    check(exp->initProduct, initProduct, passCount, failCount, &initProdCheck);
    check(exp->finalProduct, finalProduct, passCount, failCount, &finalProdCheck);
    check(exp->finalProduct, r0_mainFinalProd, passCount, failCount, &r0Check);
    check(sp_before, sp_after, passCount, failCount, &spCheck);
 
    if( onlyPrintFails == false || ((onlyPrintFails == true) && (*failCount != 0)))
    {
    snprintf((char*)txBuffer, MAX_PRINT_LEN,
            "========= testAsmMain %s test number: %ld\r\n"
            "test case INPUT: packed value:    0x%08lx\r\n"
            "test case INPUT: multiplier (a):   %11ld; 0x%08lx\r\n"
            "test case INPUT: multiplicand (b): %11ld; 0x%08lx\r\n"
            "a check p/f:           %s\r\n"
            "b check p/f:           %s\r\n"
            "sign bit a check p/f:  %s\r\n"
            "sign bit b check p/f:  %s\r\n"
            "abs a check p/f:       %s\r\n"
            "abs b check p/f:       %s\r\n"
            "initial product p/f:   %s\r\n"
            "final product p/f:     %s\r\n"
            "returned result p/f:   %s\r\n"
            "debug values        expected        actual\r\n"
            "a_Multiplicand:..%11ld   %11ld\r\n"
            "b_Multiplier:....%11ld   %11ld\r\n"
            "a_Sign:..........%11ld   %11ld\r\n"
            "b_Sign:..........%11ld   %11ld\r\n"
            "a_Abs:...........%11ld   %11ld\r\n"
            "b_Abs:...........%11ld   %11ld\r\n"
            "init_Product:....%11ld   %11ld\r\n"
            "final_Product:...%11ld   %11ld\r\n"
            "returned value:..%11ld   %11ld\r\n"
            "Expected and Actual SP: 0x%08lx; 0x%08lx; %s\r\n",
            desc,
            testNum,
            exp->packedVal,
            exp->inputA, exp->inputA,
            exp->inputB, exp->inputB,
            aCheck,
            bCheck,
            aSignCheck,
            bSignCheck,
            aAbsCheck,
            bAbsCheck,
            initProdCheck,
            finalProdCheck,
            r0Check,
            exp->inputA, a,
            exp->inputB, b,
            exp->signA, aSign,
            exp->signB, bSign,
            exp->absA, aAbs,
            exp->absB, bAbs,
            exp->initProduct, initProduct,
            exp->finalProduct, finalProduct,
            exp->finalProduct, r0_mainFinalProd,
            sp_before, sp_after, spCheck
            );
    
    printAndWait((char *)txBuffer, txComplete);
    }
    return;
}

/* *****************************************************************************
 End of File
 */
