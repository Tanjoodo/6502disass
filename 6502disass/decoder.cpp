#include <cstdint>

#include "decoder.h"
#include "instruction_procedures.h"

int Decode(int index, uint8_t bytes[])
{
	Instruction instruction = DecodeInstruction(bytes[index]);
	AddressingMode addressingMode = DecodeAddressingMode(bytes[index]);
	
	/*
	* Exceptions:
	*    STX:
	*        ZeroPageX -> ZeroPageY
	*    LDX:
	*        ZeroPageX -> ZeroPageY
	*        AbsoluteX -> AbsoluteY
	*    
	*    Branching instructions are always Relative.
	*    
	*/
	if ((instruction == STX || instruction == LDX) && addressingMode == ZeroPageX)
		addressingMode = ZeroPageY;
	if (instruction == LDX && addressingMode == AbsoluteX)
		addressingMode = AbsoluteY;

	Dispatch(instruction, addressingMode, index, bytes);
	return FindInstructionLength(addressingMode);
}

AddressingMode DecodeAddressingMode(uint8_t instructionByte)
{
	uint8_t aaa, bbb, cc;
	aaa = 0b11100000 & instructionByte;
	aaa >>= 5;
	bbb = 0b00011100 & instructionByte;
	bbb >>= 2;
	cc  = 0b00000011 & instructionByte;

	switch (cc)
	{
	   /*
		* Exceptions:
		*     STA does not have an immediate mode.
		*/
	case 0b01:
		switch (bbb)
		{
		case 0:
			return ZeroPageIndirectX;
		case 1:
			return ZeroPage;
		case 0b10:
			return Immediate;
		case 0b11:
			return Absolute;
		case 0b100:
			return ZeroPageIndirectY;
		case 0b101:
			return ZeroPageX;
		case 0b110:
			return AbsoluteX;
		case 0b111:
			return AbsoluteY;
		}
	   /*
	    * Exceptions:
		*    STX:
		*        ZeroPageX -> ZeroPageY
		*    LDX:
		*        ZeroPageX -> ZeroPageY
		*        AbsoluteX -> AbsoluteY
		*/
	case 0b10:
		switch (bbb)
		{
		case 0:
			return Immediate;
		case 1:
			return ZeroPage;
		case 0b10:
			return Accumulator;
		case 0b11:
			return Absolute;
		case 0b101:
			return ZeroPageX;
		case 0b111:
			return AbsoluteX;
		}
	case 0:
		switch (bbb)
		{
		case 0:
			return Immediate;
		case 1:
			return ZeroPage;
		case 0b11:
			return Absolute;
		case 0b101:
			return ZeroPageX;
		case 0b111:
			return AbsoluteX;
		}
	}
	
	Instruction instruction = DecodeInstruction(instructionByte);
	// Following instructions are always the same addressing mode.
	switch (instruction)
	{
	case CLC:
	case CLD:
	case CLI:
	case CLV:
	case DEX:
	case DEY:
	case INX:
	case INY:
	case NOP:
	case PHA:
	case PHP:
	case PLA:
	case PLP:
	case RTI:
	case RTS:
	case SEC:
	case SEI:
	case TAX:
	case TAY:
	case TSX:
	case TXA:
	case TXS:
	case TYA:
		return Implied;

	case BCC:
	case BCS:
	case BEQ:
	case BMI:
	case BNE:
	case BPL:
	case BVC:
		return Relative;
	}

	return UnknownAM;
}

Instruction DecodeInstruction(uint8_t instructionByte)
{
	// Start with special cases:
	switch (instructionByte)
	{
	case 0x00:
		return BRK;
	case 0x20:
		return JSR; //Absolute mode
	case 0x40:
		return RTI;
	case 0x60:
		return RTS;
	case 0x08:
		return PHP;
	case 0x28:
		return PHA;
	case 0x68:
		return PLA;
	case 0x88:
		return DEY;
	case 0xA8:
		return TAY;
	case 0xC8:
		return INY;
	case 0xE8:
		return INX;
	case 0x18:
		return CLC;
	case 0x38:
		return SEC;
	case 0x58:
		return CLI;
	case 0x78:
		return SEI;
	case 0x98:
		return TYA;
	case 0xB8:
		return CLV;
	case 0xD8:
		return CLD;
	case 0xF8:
		return SED;
	case 0x8A:
		return TXA;
	case 0x9A:
		return TXS;
	case 0xAA:
		return TAX;
	case 0xBA:
		return TSX;
	case 0xCA:
		return DEX;
	case 0xEA:
		return NOP;
	}

	// Decode branch instructions:
	switch (instructionByte)
	{
	case 0x10:
		return BPL;
	case 0x30:
		return BMI;
	case 0x50:
		return BVC;
	case 0x70:
		return BVS;
	case 0x90:
		return BCC;
	case 0xB0:
		return BCS;
	case 0xD0:
		return BNE;
	case 0xF0:
		return BEQ;
	}

	// The general case for instructions is the aaabbbcc pattern
	uint8_t aaa, cc;
	aaa = 0b11100000 & instructionByte;
	aaa >>= 5;
	cc  = 0b00000011 & instructionByte;
	
	switch (cc)
	{
	case 1:
		switch (aaa)
		{
		case 0:
			return ORA;
		case 1:
			return AND;
		case 0b10:
			return EOR;
		case 0b11:
			return ADC;
		case 0b100:
			return STA;
		case 0b101:
			return LDA;
		case 0b110:
			return CMP;
		case 0b111:
			return SBC;
		}

	case 0b10:
		switch (aaa)
		{
		case 0:
			return ASL;
		case 1:
			return ROL;
		case 0b10:
			return LSR;
		case 0b11:
			return ROR;
		case 0b100:
			return STX;
		case 0b101:
			return LDX;
		case 0b110:
			return DEC;
		case 0b111:
			return INC;
		}
	
	case 0:
		switch (aaa)
		{
		case 1:
			return BIT;
		case 0b10:
			return JMP;
		case 0b11:
			return JMP; // Absolute mode
		case 0b100:
			return STY;
		case 0b101:
			return LDY;
		case 0b110:
			return CPY;
		case 0b111:
			return CPX;
		}
	}

	return UnknownIns; // The above is probably not exhaustive.
}

void Dispatch(Instruction instruction, AddressingMode addressingMode, int index, uint8_t bytes[])
{
	uint8_t operands[] = { bytes[index + 1], bytes[index + 2] };
	switch (instruction)
	{
	case ADC:
		ProcADC(addressingMode, operands);

	case AND:
		ProcAND(addressingMode, operands);

	case ASL:
		ProcASL(addressingMode, operands);

	case BCC:
		ProcBCC(addressingMode, operands);

	case BCS:
		ProcBCS(addressingMode, operands);

	case BEQ:
		ProcBEQ(addressingMode, operands);

	case BIT:
		ProcBIT(addressingMode, operands);

	case BMI:
		ProcBMI(addressingMode, operands);

	case BNE:
		ProcBNE(addressingMode, operands);

	case BPL:
		ProcBPL(addressingMode, operands);

	case BRK:
		ProcBRK(addressingMode, operands);

	case BVC:
		ProcBVC(addressingMode, operands);

	case BVS:
		ProcBVS(addressingMode, operands);

	case CLC:
		ProcCLC(addressingMode, operands);

	case CLD:
		ProcCLD(addressingMode, operands);

	case CLI:
		ProcCLI(addressingMode, operands);

	case CLV:
		ProcCLV(addressingMode, operands);

	case CMP:
		ProcCMP(addressingMode, operands);

	case CPX:
		ProcCPX(addressingMode, operands);

	case CPY:
		ProcCPY(addressingMode, operands);

	case DEC:
		ProcDEC(addressingMode, operands);

	case DEX:
		ProcDEX(addressingMode, operands);

	case DEY:
		ProcDEY(addressingMode, operands);

	case EOR:
		ProcEOR(addressingMode, operands);

	case INC:
		ProcINC(addressingMode, operands);

	case INX:
		ProcINX(addressingMode, operands);

	case INY:
		ProcINY(addressingMode, operands);

	case JMP:
		ProcJMP(addressingMode, operands);

	case JSR:
		ProcJSR(addressingMode, operands);

	case LDA:
		ProcLDA(addressingMode, operands);

	case LDX:
		ProcLDX(addressingMode, operands);

	case LDY:
		ProcLDY(addressingMode, operands);

	case LSR:
		ProcLSR(addressingMode, operands);

	case NOP:
		ProcNOP(addressingMode, operands);

	case ORA:
		ProcORA(addressingMode, operands);

	case PHA:
		ProcPHA(addressingMode, operands);

	case PHP:
		ProcPHP(addressingMode, operands);

	case PLA:
		ProcPLA(addressingMode, operands);

	case PLP:
		ProcPLP(addressingMode, operands);

	case ROL:
		ProcROL(addressingMode, operands);

	case ROR:
		ProcROR(addressingMode, operands);

	case RTI:
		ProcRTI(addressingMode, operands);

	case RTS:
		ProcRTS(addressingMode, operands);

	case SBC:
		ProcSBC(addressingMode, operands);

	case SEC:
		ProcSEC(addressingMode, operands);

	case SED:
		ProcSED(addressingMode, operands);

	case SEI:
		ProcSEI(addressingMode, operands);

	case STA:
		ProcSTA(addressingMode, operands);

	case STX:
		ProcSTX(addressingMode, operands);

	case STY:
		ProcSTY(addressingMode, operands);

	case TAX:
		ProcTAX(addressingMode, operands);

	case TAY:
		ProcTAY(addressingMode, operands);

	case TSX:
		ProcTSX(addressingMode, operands);

	case TXA:
		ProcTXA(addressingMode, operands);

	case TXS:
		ProcTXS(addressingMode, operands);

	case TYA:
		ProcTYA(addressingMode, operands);
	}
}

int FindInstructionLength(AddressingMode addressingMode)
{
	switch (addressingMode)
	{
	case Accumulator:
	case Implied:
		return 1;
	case Absolute:
	case AbsoluteX:
	case AbsoluteY:
		return 3;

	default:
		return 2;
	}
}
