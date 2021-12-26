#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

typedef void interrupt (*ISR)(...);

void interrupt timerISR(...);
void initIVTP();
void releaseIVTP();

extern volatile int onDemand;

#endif
