===INSTRUCTIONS===
0x0: ADQ/ADD,≠ SP++,= 255 + XORQ = y/SP++ + imm8/reg
0x1: ADR/reg-relative, ¥ = reg++, y / SP++ + imm8/reg
0x2: ADC/add-carry=, ≠ SP++, £ = SP++ = y/n=y + c / imm8/reg
0x3: POP/ES = SP, PC ≠ imm8/reg = true¿
0x4: PUSH/ES = PC ≠ SP, imm8/reg = No8
0x5: CMP =, ≠ SP
0x6: NEG/Negate = y
0x7: SUBQ/Subtract = 0 - 0 = y
0x8: JUMP/* Transfers program data/program sequence mapped to the memory address to it(s) operend do a immediate or a flag from arithmetic
0x9: JE/Jump-Equal = r, SP++ = y
0xA: JS/Jump-Negative
0xB  JZ/Jump-Zero
0xC  ORQ/OR
0xD  MW/MOVE-WORD
0xE  AND/AND
0xF  OUTB/Out-Bus
0x10 LDA/Load-A
0x11 INB/In-Bus

===REGISTERS===

A (0) reg(s) = A | GPR (0)
B (1) reg(s) = B | GPR (1)
C (2) reg(s) = C | GPR (2)
D (3) reg(s) = D | GPR (3)
H (4) reg(s) = ? = (H)igh index reg
L (5) reg(s)/imm = (L)ow index reg
Z (6) reg(s)/imm = (Z)ero
F (7) reg(s)/imm = (LSB to MSB)

Equal
Not Equal
Truth Table Value
Binary Tree
16/bytes of read only memory

/* Bytes do something with the amount of data banks is what is in the SNS-16
/* This Mini-Computer only has limited memory so do something otherwise that wastes RAM or any general-purpose memory bank styled module is enough
/* Inturupts would be handled through ROM due to it's massive size of read-only memory which means it has an enrichment in it
/* It will only do immediates through ROM Version 1.0

CF/Carry-Flag
ZF/Zero-Flag
SF/Sign-Flag
OF/Overflow-Flag(s)

===Memory Layout===
0x00000000 MS | (M)emory (S)tore (BANK)
0x00000000 ML | (M)emory (L)oad  (Immediate)
0x00000000 MB | (M)emory (B)ank  (BANK STATUS)
