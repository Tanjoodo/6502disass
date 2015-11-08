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
		cout << "#$" << setw(2) << setfill('0') << uppercase << hex;
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
	case ZeroPageIndirectX:
	case ZeroPageIndirectY:
		cout << '(' << '$' << setw(4) << setfill('0') << uppercase << hex;
		break;
	}

	//Anything else does not need special formatting
}

void PrintOperands(AddressingMode addressingMode, uint8_t operands[])
{
	Format(addressingMode);

	uint16_t operand;
	switch (addressingMode)
	{
	case Immediate:
		cout << (int)operands[0];
		break;
	case ZeroPage:
		cout << (int)operands[0];
		break;
	case ZeroPageX:
		cout << (int)operands[0] << ",X";
		break;
	case ZeroPageY:
		cout << (int)operands[0] << ",Y";
	case Relative:
		cout << (int)operands[0];
		break;
	case Absolute:
		operand = (uint16_t)operands[1] << 8 | operands[0];
		cout << operand;
		break;
	case AbsoluteX:
		operand = (uint16_t)operands[1] << 8 | operands[0];
		cout << operand << ",X";
		break;
	case AbsoluteY:
		operand = (uint16_t)operands[1] << 8 | operands[0];
		cout << operand << ",Y";
		break;
	case ZeroPageIndirectX:
		cout << (int)operands[0] << ",X)";
		break;
	case ZeroPageIndirectY:
		cout << (int)operands[0] << "),Y";
		break;
	}

	cout << endl;

}
void ProcADC(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "ADC ";
	PrintOperands(addressingMode, operands);
}

void ProcAND(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "AND ";
	PrintOperands(addressingMode, operands);
}

void ProcASL(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "ASL ";
	PrintOperands(addressingMode, operands);
}

void ProcBCC(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BCC ";
	PrintOperands(addressingMode, operands);
}

void ProcBCS(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BCS ";
	PrintOperands(addressingMode, operands);
}

void ProcBEQ(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BEQ ";
	PrintOperands(addressingMode, operands);
}

void ProcBIT(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BIT ";
	PrintOperands(addressingMode, operands);
}

void ProcBMI(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BMI ";
	PrintOperands(addressingMode, operands);
}

void ProcBNE(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BNE ";
	PrintOperands(addressingMode, operands);
}

void ProcBPL(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BPL ";
	PrintOperands(addressingMode, operands);
}

void ProcBRK(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BRK ";
	PrintOperands(addressingMode, operands);
}

void ProcBVC(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BVC ";
	PrintOperands(addressingMode, operands);
}

void ProcBVS(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "BVS ";
	PrintOperands(addressingMode, operands);
}

void ProcCLC(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "CLC ";
	PrintOperands(addressingMode, operands);
}

void ProcCLD(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "CLD ";
	PrintOperands(addressingMode, operands);
}

void ProcCLI(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "CLI ";
	PrintOperands(addressingMode, operands);
}

void ProcCLV(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "CLV ";
	PrintOperands(addressingMode, operands);
}

void ProcCMP(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "CMP ";
	PrintOperands(addressingMode, operands);
}

void ProcCPX(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "CPX ";
	PrintOperands(addressingMode, operands);
}

void ProcCPY(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "CPY ";
	PrintOperands(addressingMode, operands);
}

void ProcDEC(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "DEC ";
	PrintOperands(addressingMode, operands);
}

void ProcDEX(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "DEX ";
	PrintOperands(addressingMode, operands);
}

void ProcDEY(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "DEY ";
	PrintOperands(addressingMode, operands);
}

void ProcEOR(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "EOR ";
	PrintOperands(addressingMode, operands);
}

void ProcINC(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "INC ";
	PrintOperands(addressingMode, operands);
}

void ProcINX(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "INX ";
	PrintOperands(addressingMode, operands);
}

void ProcINY(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "INY ";
	PrintOperands(addressingMode, operands);
}

void ProcJMP(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "JMP ";
	PrintOperands(addressingMode, operands);
}

void ProcJSR(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "JSR ";
	PrintOperands(addressingMode, operands);
}

void ProcLDA(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "LDA ";
	PrintOperands(addressingMode, operands);
}

void ProcLDX(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "LDX ";
	PrintOperands(addressingMode, operands);
}

void ProcLDY(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "LDY ";
	PrintOperands(addressingMode, operands);
}

void ProcLSR(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "LSR ";
	PrintOperands(addressingMode, operands);
}

void ProcNOP(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "NOP ";
	PrintOperands(addressingMode, operands);
}

void ProcORA(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "ORA ";
	PrintOperands(addressingMode, operands);
}

void ProcPHA(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "PHA ";
	PrintOperands(addressingMode, operands);
}

void ProcPHP(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "PHP ";
	PrintOperands(addressingMode, operands);
}

void ProcPLA(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "PLA ";
	PrintOperands(addressingMode, operands);
}

void ProcPLP(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "PLP ";
	PrintOperands(addressingMode, operands);
}

void ProcROL(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "ROL ";
	PrintOperands(addressingMode, operands);
}

void ProcROR(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "ROR ";
	PrintOperands(addressingMode, operands);
}

void ProcRTI(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "RTI ";
	PrintOperands(addressingMode, operands);
}

void ProcRTS(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "RTS ";
	PrintOperands(addressingMode, operands);
}

void ProcSBC(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "SBC ";
	PrintOperands(addressingMode, operands);
}

void ProcSEC(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "SEC ";
	PrintOperands(addressingMode, operands);
}

void ProcSED(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "SED ";
	PrintOperands(addressingMode, operands);
}

void ProcSEI(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "SEI ";
	PrintOperands(addressingMode, operands);
}

void ProcSTA(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "STA ";
	PrintOperands(addressingMode, operands);
}

void ProcSTX(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "STX ";
	PrintOperands(addressingMode, operands);
}

void ProcSTY(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "STY ";
	PrintOperands(addressingMode, operands);
}

void ProcTAX(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "TAX ";
	PrintOperands(addressingMode, operands);
}

void ProcTAY(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "TAY ";
	PrintOperands(addressingMode, operands);
}

void ProcTSX(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "TSX ";
	PrintOperands(addressingMode, operands);
}

void ProcTXA(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "TXA ";
	PrintOperands(addressingMode, operands);
}

void ProcTXS(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "TXS ";
	PrintOperands(addressingMode, operands);
}

void ProcTYA(AddressingMode addressingMode, uint8_t operands[])
{
	cout << "TYA ";
	PrintOperands(addressingMode, operands);
}
