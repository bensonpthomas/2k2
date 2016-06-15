/** ###################################################################
**     Filename  : calc_gain.H
**     Project   : sine_800_0
**     Processor : 56F8014VFAE
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 7/29/2011, 8:48 AM
**     Contents  :
**         User source code
**
** ###################################################################*/

void CNTRL_GAIN_CODE(void);
void CALC_GAIN_CODE(void);
void prop_gain(void);
void intgrl_gain(void);
void feed_frd(void);
unsigned int uns_mask(unsigned int h_limit,unsigned l_limit,int val);
