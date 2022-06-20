@ Assignment 2
@

.global strlen_asm0
.global strlen_asm1
.global strcpy_asm
.global strncpy_asm
.global strcmp_asm
.global strncmp_asm
.global strcat_asm

.text

strlen_asm0:    @ Gets the pointer to a string in R0 and returns len of the string passed
  MOV R3, R0        @ Store the pointer that came in into R3
  MOV R1, #0        @ To index into the string buffer
LoopStrlen0:
  LDRB R0,[R3, R1] @ Access a char of the string into R0
  CMP R0, #0        @ Check if it is NULL
BEQ LeaveStrlen0
  ADD R1, R1, #1    @ Increment the index to access the next char
  B LoopStrlen0      @ Scan the entire string until NULL is encountered
LeaveStrlen0:
  MOV R0, R1        @ The index is sams as the number of chars seen in the buffer so far
  BX LR             @ Return to the calling function
@ An optimized version of implementation of the same strlen function
@ Saving the pointer to R3 is avoided, saving one instruction compared to the earlier version
strlen_asm1:    @ Gets the pointer to a string in R0 and returns len of the string passed
  @ Use the same R0 to access the pointer address that is passed in
  MOV R1, #0        @ To index into the string buffer
LoopStrlen1:
  LDRB R2,[R0, R1]    @ Access a char of the string into R2
  CMP R2, #0          @ Check if it is NULL
BEQ LeaveStrlen1
  ADD R1, R1, #1    @ Increment the index to access the next char
  B LoopStrlen1      @ Scan the entire string until NULL is encountered
LeaveStrlen1:
  MOV R0, R1        @ The index is sams as the number of chars seen in the buffer so far
  BX LR             @ Return to the calling function


strcpy_asm:
  MOV R3, R1
  MOV R1, #0
Loopstrcpy:
  LDRB R2, [R3,R1]
  CMP R2, #0
  BEQ Leavestrcpy
  STRB R2, [R0,R1]
  ADD R1, R1, #1
  B Loopstrcpy
Leavestrcpy:
  STRB R2, [R0,R1]
  MOV R1, R3
  BX LR

  
strncpy_asm:
  PUSH {R4}
  MOV R3, R1
  MOV R1, #0
Loopstrncpy:
  LDRB R4, [R3,R1]
  CMP R4, #0
  BEQ leave1strncpy
  STRB R4, [R0,R1]
  ADD R1, R1, #1
  CMP R1, R2
  BEQ leave2strncpy
  B Loopstrncpy
leave2strncpy:
  MOV R4, #0
  STRB R4, [R0,R1]
  POP {R4}
  BX LR
leave1strncpy:
  STRB R4, [R0,R1]
  POP {R4}
  BX LR


strcmp_asm:
  PUSH {R4}
  MOV R4, #0
Loopstrcmp:
  LDRB R2, [R0, R4]
  CMP R2, #0
  BEQ leave1_strcmp
  LDRB R3, [R1, R4]
  CMP R3, #0
  BEQ leave2_strcmp
  CMP R2, R3
  BNE notEq
  ADD R4, R4, #1
  B Loopstrcmp
notEq:
  SUB R0, R2, R3
  POP {R4}
  BX LR
leave1_strcmp:
  LDRB R3, [R1, R4]
  SUB R0, R2, R3
  POP {R4}
  BX LR
leave2_strcmp:
  SUB R0, R2, R3
  POP {R4}
  BX LR


strncmp_asm:
  PUSH {R4, R5}
  MOV R4, #0
Loopstrncmp:
  LDRB R3, [R0,R4]
  CMP R3, #0
  BEQ leave1_strncmp
  LDRB R5, [R1,R4]
  CMP R5, #0
  BEQ leave2_strncmp
  CMP R3, R5
  BNE leave2_strncmp
  ADD R4, R4, #1
  CMP R2, R4
  BNE Loopstrncmp
  B leave2_strncmp
leave1_strncmp:
  LDRB R5, [R1, R4]
  SUB R0, R3, R5
  POP {R4, R5}
  BX LR
leave2_strncmp:
  SUB R0, R3, R5
  POP {R4, R5}
  BX LR



strcat_asm:
  PUSH {R4, R5}
  MOV R3, #0
  MOV R5, #0
Loop_strcat:
  LDRB R2, [r0, R3]
  CMP R2, #0
  BEQ label1_strcat
  ADD R3, R3, #1
  B Loop_strcat
label1_strcat:
  LDRB R4, [R1,R5]
  CMP R4, #0
  BEQ leave_strcat
  STRB R4, [R0,R3]
  ADD R3, R3, #1
  ADD R5, R5, #1
  B label1_strcat
leave_strcat:
  STRB R4, [R0,R3]
  POP {R4,R5}
  BX LR
  

@ Data section starts here ...
.data
.align  4 @ necessary alignment to have variables which are aligned on 4 bytes boundary

.end  

@ End of Data segment
