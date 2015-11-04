#pragma once
#include <cstdint>
#include <iostream>
#include <iomanip>

#include "instruction_procedures.h"
#include "decoder.h"

using namespace std;

void Format(AddressingMode addressingMode)
{
	switch (addressingMode)
	{
	case Immediate:
		cout << "#$";
		break;
	case ZeroPage:
	case ZeroPageX:
	case ZeroPageY:
	case Relative:
		cout << "$" << setw(2) << setfill('0') << uppercase << hex;
		break;
	case Absolute:
	case AbsoluteX:
	case AbsoluteY:
		cout << "$" << setw(4) << setfill('0') << uppercase << hex;
		break;
	case Accumulator:
		cout << setw(1) << setfill('0') << uppercase << hex;
		break;
	case ZeroPageIndirectX:
	case ZeroPageIndirectY:
		cout << '(' << '$' << setw(4) << setfill('0') << uppercase << hex;
		break;
	}

	//Anything else does not need special formatting
}
void ProcADC(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcAND(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcASL(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBCC(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBCS(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBEQ(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBIT(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBMI(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBNE(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBPL(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBRK(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBVC(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcBVS(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcCLC(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcCLD(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcCLI(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcCLV(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcCMP(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcCPX(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcCPY(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcDEC(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcDEX(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcDEY(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcEOR(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcINC(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcINX(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcINY(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcJMP(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcJSR(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcLDA(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcLDX(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcLDY(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcLSR(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcNOP(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcORA(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcPHA(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcPHP(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcPLA(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcPLP(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcROL(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcROR(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcRTI(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcRTS(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcSBC(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcSEC(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcSED(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcSEI(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcSTA(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcSTX(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcSTY(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcTAX(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcTAY(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcTSX(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcTXA(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcTXS(AddressingMode addressingMode, uint8_t operands[])
{
}

void ProcTYA(AddressingMode addressingMode, uint8_t operands[])
{
}