/*
 * Unified Cortex Startup - C startup file
 *
 * This file is in public domain
 *
 * Put together by Paul Sokolovsky based on article by Vanya Sergeev
 * http://dev.frozeneskimo.com/notes/cortex_cmsis/ , GNU ld documentation
 * and numerous other public resources.
 *
 */

#include <stdint.h>

/* Declare linker-defined symbols. The only thing of interest
   regarding these symbols is their *address*. uint32_t hints
   of alignment. */
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern int _start(void);

/* C main function */
extern int main(void);
/* Device-specific initialization function. Optional, any Cortex-M
   should be able to start up in its default mode on its own, though
   some may have errata for some peripherals (including PLL) which
   this function may "patch". */

void Dummy_Handler(void);

/* Cortex-M core interrupt handlers */
#define ALIAS(sym) __attribute__((weak, alias(sym)))

void Reset_Handler(void);
void NMI_Handler(void) ALIAS("Dummy_Handler");
void HardFault_Handler(void) ALIAS("Dummy_Handler");
void MemManage_Handler(void) ALIAS("Dummy_Handler");
void BusFault_Handler(void) ALIAS("Dummy_Handler");
void UsageFault_Handler(void) ALIAS("Dummy_Handler");
void SVC_Handler(void) ALIAS("Dummy_Handler");
void DebugMon_Handler(void) ALIAS("Dummy_Handler");
void PendSV_Handler(void) ALIAS("Dummy_Handler");
void SysTick_Handler(void) ALIAS("Dummy_Handler");

/* standard Cortex-M vectors - these are present in every MCU */
void *isr_vector[] __attribute__((section(".isr_vector"))) = {
    // See http://sourceware.org/binutils/docs/ld/Source-Code-Reference.html
    // why the address is used here (if not intuitive)
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
};

/* Based on http://sourceware.org/binutils/docs/ld/Output-Section-LMA.html */
void Reset_Handler(void) {
  volatile uint32_t *src, *dst;

  /* Copy data section from flash to RAM */
  src = &_sidata;
  dst = &_sdata;
  while (dst < &_edata)
    *dst++ = *src++;

  /* Clear the bss section, assumes .bss goes directly after .data */
  dst = &_sbss;
  while (dst < &_ebss)
    *dst++ = 0;
  _start();
  main();
  while (1)
    ;
}
/* Default interrupt handler */
void Dummy_Handler(void) {
  /* Receiving an unexpected interrupt is considered a bug
     in the program. Let's make it very visible by just
     hanging the processing. Ignoring it by just returning
     may result in very complicated debugging sessions. */
  while (1)
    ;
}

int _start(void) {
  // 一些初始化操作 时钟或者其他板级初始化
  return 0;
}
