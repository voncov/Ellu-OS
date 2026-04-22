#ifndef ISR_H
#define ISR_H

#include <stddef.h>
#include <driver.h>
#include <video/lfb.h>
#include <tty/tty.h>

VOID isr_Init(E_LFBDRV *lfb, E_TTYDRV *tty);

#endif