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

#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H

#include "definitions.h"                // SYS function prototypes

extern uint32_t nameStrPtr;

extern int32_t a_Multiplicand;
extern int32_t b_Multiplier;
extern int32_t rng_Error;
extern int32_t a_Sign;
extern int32_t b_Sign;
extern int32_t prod_Is_Neg;
extern int32_t a_Abs;
extern int32_t b_Abs;
extern int32_t init_Product;
extern int32_t final_Product;


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    /* function to initialize the externs defined by assembly 
     * to a known value */
    void asmExternsInit(void);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
