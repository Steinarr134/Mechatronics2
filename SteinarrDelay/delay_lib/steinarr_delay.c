/*
 * steinarr_delay.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Notandi
 */

#include "../delay_lib/steinarr_delay.h"

void delay_half_us()
{
//	asm volatile("");
}
void delay_1us()
{
	asm volatile("nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"
				 "nop\n\t"::);
}


void delay_us(unsigned int us)
{
	// overhead from calling function,
	// (2*ldi + call) costs 6 cycles

	// special case for us=1, (covers us=0 as well)
		// comparison costs 2 cycles (cpc and cpi)
	if (us < 2) // branches with brcs
	{
		// branch: 2 cycles to go here

		// at this point we are aiming for 1 microseconds
		// that is 16 cycles. We spent 6 on (2*ldi+call),
		// 2 on comparison, 2 on the branching and 4 for the return
		// leaving 16-6-4-2-2 = 2 cycles left to spend
		asm volatile("nop\n\t"
					 "nop\n\t"::);
		return; // 4 cycles for ret
	}
	// branch: one cycle to go here

	// burn 2 cycles to make the overhead from
	// calling to be exactly 1 microsecond
	// see calculation for why 2 cycles at the bottom
	// of the function
	asm volatile("nop\n\t"
				 "nop\n\t"::);
	// subtract the one microseconds that burns up
	// in the overhead
	us--; // takes 2 cycles (sbwi)

	// each loop should then be exactly 1 microsecond
	while(1)
	{
		// this loop should take 16 cycles,
		// so here we burn 16 -2 -2 = 12 cycles
		asm volatile("nop\n\t"
				 	 "nop\n\t"
					 "nop\n\t"
					 "nop\n\t"
					 "nop\n\t"
					 "nop\n\t"
					 "nop\n\t"
					 "nop\n\t"
					 "nop\n\t"
					 "nop\n\t"
					 "nop\n\t"
					 "nop\n\t"::);
		us--; // sbwi: 2 cycles, saves overflow to Zero Flag
		if (!us) // branches with brne
		{
			// 1 cycle to go here
			return; // 4 cycles
		}
		// 2 cycles to go here (aka to loop)
	}
	// Why 2 cycles:
	// Overhead from calling is:
	// 2*ldi+call	6 cycles
	// cpi + cpc	2 cycles
	// if (brcs)	1 cycle (didn't branch)
	// sbwi			2 cycles
	// return		4
	// and finally the last loop will take be one cycle
	// short of 1 microsecond because the brne instruction
	// takes 2 cycles if it branches as expected in the loop
	// but the last loop doesn't branch so brne only takes 1 cycle
	// leaving the last loop as only 15 cycles.

	// so the overhead should aim for 17 cycles to make
	// up that one cycle that gets forgotten in the last loop

	// so we have  17 = 6 + 4 + 2 + 2 + 1 + X
	// 			==> X = 2
}


void delay_ms(unsigned int ms)
{   // 6 cycles for call overhead

	// accounting for overhead:
	// goal here is total of 16.000 cycles or exactly 1 ms
	// so far we spent 6, comparison(<2) will take 2 cycles
	// the single nop will take 1 and jump to return will take 2
	// or the skip will take 1 and the decrement will take 2
	// the return will cost 4
	// for a total of 6 + 2 + 2 + 4 = 15
	// so now we should spend 16.000 - 15 = 15.985

	DELAY_9P4(3994); // takes 4*3.994 + 9 = 15.985
	// thus we sleep for 1 cycle

	// 2 cycles for comparison
	if (ms < 2)
	{// 2 cycles to get here

		// one nop here to equal the overhead branches
		asm volatile("nop");
		return;
	}
	// 1 cycle to get here
	ms--; // 2 cycles (sbiw)

	// this loop shall take 1 ms (16.000 cycles) per loop
	while(1)
	{
		// accounting for this loop
		// sbiw and brne each cost 2 cycles
		// we need to burn an additional 15.996 cycles
		DELAY_9P4(3996); // burns 3.996*4 +9 = 15.993
		// additional 3 cycles needed:

		asm volatile("nop\n\t"
				"nop\n\t"
				"nop\n\t"::);

		ms--; // sbiw: 2 cycles
		if (!ms) // comparison is free with sbiw
		{
			// 1 cycle to get here
			// loop accounting expects the branching
			// to cost 2 cycles so add 1 nop here
			asm volatile("nop\n\t"::);
			return;
		}
		// 2 cycles to get here and loop
	}
}




void delay_s(unsigned int s)
{   // 6 cycles for call overhead

	// accounting for overhead:
	// goal here is total of 16.000.000 cycles or exactly 1s
	// so far we spent 6, comparison(if s<2) will take 2 cycles
	// the single nop will take 1 and jump to return will take 2
	// or the skip will take 1 and the decrement will take 2
	// the return will cost 4
	// for a total of 6 + 2 + 2 + 1 + 4 = 15
	// so now we should spend 16,000,000 - 15 = 15,999,985
	DELAY_9P262153(61); // takes 262.153*61 + 9 = 15,991,342
	// we still need 15,999,985 - 15,991,342 = 8,643
	DELAY_9P4(2158); // takes 9 + 4*2,158 = 8,641
	// we still need 8,643 - 8,641 = 2 cycles
	asm volatile("nop\n\t"
			"nop\n\t"::);
//
	// 2 cycles for comparison
	if (s < 2)
	{// 2 cycles to get here

		// one nop here to equal the overhead branches
		asm volatile("nop\n\t");
		return;
	}
	// 1 cycle to get here
	s--; // 2 cycles (sbiw)

	// this loop shall take 1 s (16.000.000 cycles) per loop
	while(1)
	{
		// accounting for this loop
		// sbiw and brne each cost 2 cycles for total of 4
		// so now we should spend 16,000,000 - 4 = 15,999,996
		DELAY_9P262153(61); // takes 262.153*61 + 9 = 15,991,342
		// we still need 15,999,996 - 15,991,342 = 8,654
		DELAY_9P4(2161); // takes 9 + 4*2,161 = 8,653
		// we still need 8,654 - 8,653 = 1 cycles
		asm volatile("nop\n\t");

		s--; // sbiw: 2 cycles
		if (!s) // comparison is free with sbiw
		{
			// 1 cycle to get here
			// loop accounting expects the branching
			// to cost 2 cycles so add 1 nop here
			asm volatile("nop\n\t"::);
			return;
		}
		// 2 cycles to get here and loop
	}
}

void main_fake()
{
	d(100);
}

void d(unsigned int us)
{
	asm volatile("nop\n\t"::);
	us--;

	while(us)
	{
		asm volatile("nop\n\t"::);
		us--;
	}
}
