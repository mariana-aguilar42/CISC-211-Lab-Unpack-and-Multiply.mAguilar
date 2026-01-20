/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _TEST_FUNCS_H    /* Guard against multiple inclusion */
#define _TEST_FUNCS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */
// #define EXAMPLE_CONSTANT 0


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

// define structs to make testing easier

typedef struct _expectedValues
{
    uint32_t packedVal;
    int32_t inputA;
    int32_t inputB;
    int32_t absA;
    int32_t absB;
    int32_t signA;
    int32_t signB;
    int32_t initProduct;
    int32_t finalProduct;
} expectedValues;


    // *****************************************************************************

    /** Descriptive Data Type Name

      @Summary
        Brief one-line summary of the data type.
    
      @Description
        Full description, explaining the purpose and usage of the data type.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Remarks
        Any additional remarks
        <p>
        Describe enumeration elements and structure and union members above each 
        element or member.
     */
    

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

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

int32_t calcExpectedValues(
        int32_t testNum, // test number
        char *desc,      // optional test descriptor, or ""
        uint32_t packedValue, // test case input
        expectedValues *e);   // ptr to struct where values will be stored

void resetGlobalVars();

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
        );

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
        );


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
        );


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
        );



void testAsmMain(
        int32_t testNum, // test number
        char *desc, // optional description, or ""
        uint32_t packedVal, // inputs
        int32_t r0_mainFinalProd, // outputs
        int32_t aMultiplicand,
        int32_t bMultiplier,
        int32_t aAbs, 
        int32_t aSign, 
        int32_t bAbs, 
        int32_t bSign,
        int32_t init_Product,
        int32_t final_Product,
        expectedValues * exp, // expected values
        uint32_t sp_before,
        uint32_t sp_after,
        int32_t * passCount,
        int32_t * failCount,
        bool onlyPrintFails,
        volatile bool * txComplete
        );




    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _TEST_FUNCS_H */

/* *****************************************************************************
 End of File
 */
