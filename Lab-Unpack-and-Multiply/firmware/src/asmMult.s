/*** asmMult.s   ***/
/* Tell the assembler to allow both 16b and 32b extended Thumb instructions */
.syntax unified

/* Tell the assembler that what follows is in data memory    */
.data
.align
 
/* define and initialize global variables that C can access */
/* create a string */
.global nameStr
.type nameStr,%gnu_unique_object
    
/*** STUDENTS: Change the next line to your name!  **/
nameStr: .asciz "Mariana Aguilar"  

.align   /* realign so that next mem allocations are on word boundaries */
 
/* initialize a global variable that C can access to print the nameStr */
.global nameStrPtr
.type nameStrPtr,%gnu_unique_object
nameStrPtr: .word nameStr   /* Assign the mem loc of nameStr to nameStrPtr */

.global packed_Value,a_Multiplicand,b_Multiplier,a_Sign,b_Sign,prod_Is_Neg,a_Abs,b_Abs,abs_Product,final_Product
.type packed_Value,%gnu_unique_object
.type a_Multiplicand,%gnu_unique_object
.type b_Multiplier,%gnu_unique_object
.type a_Sign,%gnu_unique_object
.type b_Sign,%gnu_unique_object
.type prod_Is_Neg,%gnu_unique_object
.type a_Abs,%gnu_unique_object
.type b_Abs,%gnu_unique_object
.type abs_Product,%gnu_unique_object
.type final_Product,%gnu_unique_object

/* NOTE! These are only initialized ONCE, right before the program runs.
 * If you want these to be 0 every time asmMult gets called, you must set
 * them to 0 at the start of your code!
 */
packed_Value:    .word     0  
a_Multiplicand:  .word     0  
b_Multiplier:    .word     0  
a_Sign:          .word     0  
b_Sign:          .word     0 
prod_Is_Neg:     .word     0  
a_Abs:           .word     0  
b_Abs:           .word     0 
abs_Product:     .word     0
final_Product:   .word     0

 /* Tell the assembler that what follows is in instruction memory    */
.text
.align

    
/********************************************************************
function name: asmMult
function description:
     output = asmMult ()
     
where:
     output: 
     
     function description: See Lab Instructions
     
     notes:
        None
          
********************************************************************/    
.global asmMult
.type asmMult,%function
asmMult:   

    /* save the caller's registers, as required by the ARM calling convention */
    push {r4-r11,LR}
 
.if 0
    /* profs test code. */
    mov r0,r0
.endif
    
    /*** STUDENTS: Place your code BELOW this line!!! **************/
    
    //UNPACKING//
    
    //storing packed value from r0 into memeory
    LDR R2, =packed_Value
    STR R0, [R2]
    
    //storing Ra(R3) and shifting to get A in LSB 
    MOV R3, R0
    ASR R3, R3, 16 //sign extending
    
    //storing Rb(R4) and shifting to get B in MSB 
    LSL R4, R0, 16
    ASR R4, R4, 16 //sign extending 
    
    //Ra goes to a_nultiplicand
    LDR R2, =a_Multiplicand
    STR R3, [R2]
    
    //stroing Ra sign//
    
    //checking if Ra is 0
    CMP R3, 0
    BLT Ra_neg
    
    //if Ra is positive
Ra_pos:
    MOV R5, 0 //setting sign 
    MOV R6, R3 //abs value of Ra goes, because its positive
    B storing_Ra
    
    
Ra_neg:
    MOV R5, 1 //1 because negative
    RSB R6, R3, 0  //0 - Ra = positive abs value

storing_Ra:
    LDR R2, =a_Sign
    STR R5, [R2]
    LDR R2, =a_Abs
    STR R6, [R2]
    
    //storing Rb sign(same as Ra)//
    LDR R2, =b_Multiplier
    STR R4, [R2]
    
    //checking if Rb is 0
    CMP R4, 0
    BLT Rb_neg
    
    
Rb_pos:
    MOV R7, 0 //setting sign 
    MOV R8, R4
    B storing_Rb
    
    
Rb_neg:
    MOV R7, 1
    RSB R8, R4, 0
    
    
storing_Rb:
    LDR R2, =b_Sign
    STR R7, [R2]
    LDR R2, =b_Abs
    STR R8, [R2]
    
    //getting final product sign//
    CMP R5, R7
    BEQ sign_pos //positive if (+ x +) and if (- x -)
    

sign_pos:
    MOV R9, 0 //R9 will hold sign 
    
sign_neg:
    MOV R9, 1
    
    LDR R2, =prod_Is_Neg
    STR R9, [R2]
    
    
    //MULTIPLY USING SHIFT AND ADD//
    
    //getting multiplicand and multiplier from memory
    LDR R2, =a_Abs
    LDR R0, [R2]
    
    LDR R2, =b_Abs
    LDR R1, [R2] 
    
    //setting up product
    MOV R2, 0
    
Shift_Add_loop:
    CMP R1, 0
    BEQ returing_Prod
    
    //is multiplier LSB 1
    TST R1, 1
    BEQ shift
    
    ADD R2, R2, R0
    
shift:
    LSL R0, R0, 1
    LSR R1, R1, 1 
    B Shift_Add_loop
    
returing_Prod:
    LDR R3, =abs_Product
    STR R2, [R3]
    
    
    //checking product is negative
    LDR R3, =prod_Is_Neg
    LDR R4, [R3]
    CMP R4, 1
    BNE final_Prod
    RSB R2, R2, 0 //product was negative
    
final_Prod:
    LDR R3, =final_Product
    STR R2, [R3]
    MOV R0, R2
    
    B done 
    
    
    /*** STUDENTS: Place your code ABOVE this line!!! **************/

done:    
    mov r0,r0 /* these are do-nothing lines to deal with IDE mem display bug */
    mov r0,r0 

    /* restore the caller's registers, as required by the 
     * ARM calling convention 
     */
    pop {r4-r11,LR}

    mov pc, lr	 /* asmMult return to caller */
   

/**********************************************************************/   
.end  /* The assembler will not process anything after this directive!!! */
           




