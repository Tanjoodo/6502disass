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
		break;

	case AND:
		ProcAND(addressingMode, operands);
		break;

	case ASL:
		ProcASL(addressingMode, operands);
		break;

	case BCC:
		ProcBCC(addressingMode, operands);
		break;

	case BCS:
		ProcBCS(addressingMode, operands);
		break;

	case BEQ:
		ProcBEQ(addressingMode, operands);
		break;

	case BIT:
		ProcBIT(addressingMode, operands);
		break;

	case BMI:
		ProcBMI(addressingMode, operands);
		break;

	case BNE:
		ProcBNE(addressingMode, operands);
		break;

	case BPL:
		ProcBPL(addressingMode, operands);
		break;

	case BRK:
		ProcBRK(addressingMode, operands);
		break;

	case BVC:
		ProcBVC(addressingMode, operands);
		break;

	case BVS:
		ProcBVS(addressingMode, operands);
		break;

	case CLC:
		ProcCLC(addressingMode, operands);
		break;

	case CLD:
		ProcCLD(addressingMode, operands);
		break;

	case CLI:
		ProcCLI(addressingMode, operands);
		break;

	case CLV:
		ProcCLV(addressingMode, operands);
		break;

	case CMP:
		ProcCMP(addressingMode, operands);
		break;

	case CPX:
		ProcCPX(addressingMode, operands);
		break;

	case CPY:
		ProcCPY(addressingMode, operands);
		break;

	case DEC:
		ProcDEC(addressingMode, operands);
		break;

	case DEX:
		ProcDEX(addressingMode, operands);
		break;

	case DEY:
		ProcDEY(addressingMode, operands);
		break;

	case EOR:
		ProcEOR(addressingMode, operands);
		break;

	case INC:
		ProcINC(addressingMode, operands);
		break;

	case INX:
		ProcINX(addressingMode, operands);
		break;

	case INY:
		ProcINY(addressingMode, operands);
		break;

	case JMP:
		ProcJMP(addressingMode, operands);
		break;

	case JSR:
		ProcJSR(addressingMode, operands);
		break;

	case LDA:
		ProcLDA(addressingMode, operands);
		break;

	case LDX:
		ProcLDX(addressingMode, operands);
		break;

	case LDY:
		ProcLDY(addressingMode, operands);
		break;

	case LSR:
		ProcLSR(addressingMode, operands);
		break;

	case NOP:
		ProcNOP(addressingMode, operands);
		break;

	case ORA:
		ProcORA(addressingMode, operands);
		break;

	case PHA:
		ProcPHA(addressingMode, operands);
		break;

	case PHP:
		ProcPHP(addressingMode, operands);
		break;

	case PLA:
		ProcPLA(addressingMode, operands);
		break;

	case PLP:
		ProcPLP(addressingMode, operands);
		break;

	case ROL:
		ProcROL(addressingMode, operands);
		break;

	case ROR:
		ProcROR(addressingMode, operands);
		break;

	case RTI:
		ProcRTI(addressingMode, operands);
		break;

	case RTS:
		ProcRTS(addressingMode, operands);
		break;

	case SBC:
		ProcSBC(addressingMode, operands);
		break;

	case SEC:
		ProcSEC(addressingMode, operands);
		break;

	case SED:
		ProcSED(addressingMode, operands);
		break;

	case SEI:
		ProcSEI(addressingMode, operands);
		break;

	case STA:
		ProcSTA(addressingMode, operands);
		break;

	case STX:
		ProcSTX(addressingMode, operands);
		break;

	case STY:
		ProcSTY(addressingMode, operands);
		break;

	case TAX:
		ProcTAX(addressingMode, operands);
		break;

	case TAY:
		ProcTAY(addressingMode, operands);
		break;

	case TSX:
		ProcTSX(addressingMode, operands);
		break;

	case TXA:
		ProcTXA(addressingMode, operands);
		break;

	case TXS:
		ProcTXS(addressingMode, operands);
		break;

	case TYA:
		ProcTYA(addressingMode, operands);
		break;
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
