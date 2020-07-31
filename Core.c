#include "Core.h"
#include "Registers.h"

Core *initCore(Instruction_Memory *i_mem)
{
    Core *core = (Core *)malloc(sizeof(Core));
    core->clk = 0;
    core->PC = 0;
    core->instr_mem = i_mem;
    core->tick = tickFunc;

    // FIXME, initialize register file here.
    // core->data_mem[0] = ...
	core -> data_mem[0] = 16;
	core -> data_mem[1] = 128;
	core -> data_mem[2] = 8;
	core -> data_mem[3] = 4;

    // FIXME, initialize data memory here.
    core->reg_file[25] = 4;
	core->reg_file[10] = 4;
	core->reg_file[22] = 1;

    return core;
}

// FIXME, implement this function
bool tickFunc(Core *core)
{
    // Steps may include
    // (Step 1) Reading instruction from instruction memory
    unsigned instruction = core->instr_mem->instructions[core->PC / 4].instruction;
    
    // (Step 2) ...
    
    // (Step N) Increment PC. FIXME, is it correct to always increment PC by 4?!
	// call control unit 
	signal control_unit_input = (instruction / 64);
	ControlUnit(control_unit_input, ControlSignals *signals);
	//Alu control 
	Signal aluControlResult = ALUControlUnit(signals->ALUOp, instruction>>24,instruction >> 11);
	//get reg values
	
	// get inputs for reg file from instructions
	int reg_index_1,reg_index_2,write_dat;
	reg_index_1 = (instruction / 524288)>>15;
	reg_index_2 = (instruction / 16777216)>>20;
	write_dat = (instruction / 2048)>>7;
	signal reg_read_1, reg_read_2
	if (write_dat == 0 )
	{
		reg_read_1 = reg_file[reg_index_1];
		reg_read_2 = reg_file[reg_index_2];
	else if (write_dat == 1)		
		reg_file[reg_index_1] = // result of memory manipulation Mux all the way to the right 
	}
	// Reading / writing regs 	
	ALU(reg_file[0],reg_file[0],aluControlResult,Signal *ALU_result,Signal *zero);
	//call 
	
	
	 if (1) // figure out conditional. Mux control on the left? 
	 {
		core->PC += 4;
	 else
		 core->PC = ;
	 }
    

    ++core->clk;
    // Are we reaching the final instruction?
    if (core->PC > core->instr_mem->last->addr)
    {
        return false;
    }
    return true;
}

// FIXME (1). Control Unit. Refer to Figure 4.18.
void ControlUnit(Signal input,
                 ControlSignals *signals)
{
    // For R-type
    if (input == 51)
    {
        signals->ALUSrc = 0;
        signals->MemtoReg = 0;
        signals->RegWrite = 1;
        signals->MemRead = 0;
        signals->MemWrite = 0;
        signals->Branch = 0;
        signals->ALUOp = 2;
    }
	// For I-type -- ld
    if (input == 3)
    {
        signals->ALUSrc = 0;
        signals->MemtoReg = 1;
        signals->RegWrite = 1;
        signals->MemRead = 1;
        signals->MemWrite = 0;
        signals->Branch = 0;
        signals->ALUOp = 3;
    }
}

// FIXME (2). ALU Control Unit. Refer to Figure 4.12.
Signal ALUControlUnit(Signal ALUOp,
                      Signal Funct7,
                      Signal Funct3)
{
    // For add
    if (ALUOp == 2 && Funct7 == 0 && Funct3 == 0)
    {
        return 2;
    }
	// For ldd
    if (ALUOp == 2 && Funct3 == 7)
    {
        return 3;
    }
	
}

// FIXME (3). Imme. Generator
Signal ImmeGen(Signal input)
{
	ImmeGen = input;
}

// FIXME (4). ALU
void ALU(Signal input_0,
         Signal input_1,
         Signal ALU_ctrl_signal,
         Signal *ALU_result,
         Signal *zero)
{
    // For addition
    if (ALU_ctrl_signal == 2)
    {
        *ALU_result = (input_0 + input_1);
        if (*ALU_result == 0) { *zero = 1; } else { *zero = 0; }
    }
	// For ld
    if (ALU_ctrl_signal == 3)
    {
        *ALU_result = input_1;
        if (*ALU_result == 0) { *zero = 1; } else { *zero = 0; }
    }
	
}

// (4). MUX
Signal MUX(Signal sel,
           Signal input_0,
           Signal input_1)
{
    if (sel == 0) { return input_0; } else { return input_1; }
}

// (5). Add
Signal Add(Signal input_0,
           Signal input_1)
{
    return (input_0 + input_1);
}

// (6). ShiftLeft1
Signal ShiftLeft1(Signal input)
{
    return input << 1;
}
