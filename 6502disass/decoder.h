#pragma once
enum Instruction
{
	ADC, AND, ASL,
	BCC, BCS, BEQ,
	BIT, BMI, BNE,
	BPL, BRK, BVC,
	BVS, CLC, CLD,
	CLI, CLV, CMP,
	CPX, CPY, DEC,
	DEX, DEY, EOR,
	INC, INX, INY,
	JMP, JSR, LDA,
	LDX, LDY, LSR,
	NOP, ORA, PHA,
	PHP, PLA, PLP,
	ROL, ROR, RTI,
	RTS, SBC, SEC,
	SED, SEI, STA,
	STX, STY, TAX,
	TAY, TSX, TXA,
	TXS, TYA
};;

enum AddressingMode
{
	Accumulator,
	Implied,
	Immediate,
	Absolute,
	ZeroPage,
	Relative,
	AbsoluteX,
	AbsoluteY,
	ZeroPageX,
	ZeroPageY,
	ZeroPageIndirectX, // Zero Page Indexed Indirect (zp,x)
	ZeroPageIndirectY  // Zero Page Indirect Indexed with Y (zp), y
};