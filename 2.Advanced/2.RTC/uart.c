/*****************************************************************************
 *   uart.c:  UART API file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "lpc17xx.h"
#include "type.h"
#include "uart.h"

volatile uint32_t UART3Status, UART1Status,UART0Status;
volatile uint8_t UART3TxEmpty = 1, UART1TxEmpty = 1,UART0TxEmpty = 1;
volatile uint8_t UART3Buffer[BUFSIZE], UART1Buffer[BUFSIZE],UART0Buffer[BUFSIZE];
volatile uint32_t UART3Count = 0, UART1Count = 0,UART0Count = 0;

/*****************************************************************************
** Function name:		UART3_IRQHandler
**
** Descriptions:		UART3 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void UART3_IRQHandler (void) 
{
  uint8_t IIRValue, LSRValue;
  uint8_t Dummy = Dummy;
	
  IIRValue = LPC_UART3->IIR;
    
  IIRValue >>= 1;			/* skip pending bit in IIR */
  IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
  if ( IIRValue == IIR_RLS )		/* Receive Line Status */
  {
	LSRValue = LPC_UART3->LSR;
	/* Receive Line Status */
	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{
	  /* There are errors or break interrupt */
	  /* Read LSR will clear the interrupt */
	  UART3Status = LSRValue;
	  Dummy = LPC_UART3->RBR;		/* Dummy read on RX to clear 
							interrupt, then bail out */
	  return;
	}
	if ( LSRValue & LSR_RDR )	/* Receive Data Ready */			
	{
	  /* If no error on RLS, normal ready, save into the data buffer. */
	  /* Note: read RBR will clear the interrupt */
	  UART3Buffer[UART3Count] = LPC_UART3->RBR;
	  UART3Count++;
	  if ( UART3Count == BUFSIZE )
	  {
		UART3Count = 0;		/* buffer overflow */
	  }	
	}
  }
  else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
  {
	/* Receive Data Available */
	UART3Buffer[UART3Count] = LPC_UART3->RBR;
	UART3Count++;
	if ( UART3Count == BUFSIZE )
	{
	  UART3Count = 0;		/* buffer overflow */
	}
  }
  else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
  {
	/* Character Time-out indicator */
	UART3Status |= 0x100;		/* Bit 9 as the CTI error */
  }
  else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
  {
	/* THRE interrupt */
	LSRValue = LPC_UART3->LSR;		/* Check status in the LSR to see if
									valid data in U0THR or not */
	if ( LSRValue & LSR_THRE )
	{
	  UART3TxEmpty = 1;
	}
	else
	{
	  UART3TxEmpty = 0;
	}
  }    
}

/*****************************************************************************
** Function name:		UART1_IRQHandler
**
** Descriptions:		UART1 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void UART1_IRQHandler (void) 
{
  uint8_t IIRValue, LSRValue;
  uint8_t Dummy = Dummy;
	
  IIRValue = LPC_UART1->IIR;
    
  IIRValue >>= 1;			/* skip pending bit in IIR */
  IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
  if ( IIRValue == IIR_RLS )		/* Receive Line Status */
  {
	LSRValue = LPC_UART1->LSR;
	/* Receive Line Status */
	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{
	  /* There are errors or break interrupt */
	  /* Read LSR will clear the interrupt */
	  UART1Status = LSRValue;
	  Dummy = LPC_UART1->RBR;		/* Dummy read on RX to clear 
								interrupt, then bail out */
	  return;
	}
	if ( LSRValue & LSR_RDR )	/* Receive Data Ready */			
	{
	  /* If no error on RLS, normal ready, save into the data buffer. */
	  /* Note: read RBR will clear the interrupt */
	  UART1Buffer[UART1Count] = LPC_UART1->RBR;
	  UART1Count++;
	  if ( UART1Count == BUFSIZE )
	  {
		UART1Count = 0;		/* buffer overflow */
	  }	
	}
  }
  else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
  {
	/* Receive Data Available */
	UART1Buffer[UART1Count] = LPC_UART1->RBR;
	UART1Count++;
	if ( UART1Count == BUFSIZE )
	{
	  UART1Count = 0;		/* buffer overflow */
	}
  }
  else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
  {
	/* Character Time-out indicator */
	UART1Status |= 0x100;		/* Bit 9 as the CTI error */
  }
  else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
  {
	/* THRE interrupt */
	LSRValue = LPC_UART1->LSR;		/* Check status in the LSR to see if
								valid data in U0THR or not */
	if ( LSRValue & LSR_THRE )
	{
	  UART1TxEmpty = 1;
	}
	else
	{
	  UART1TxEmpty = 0;
	}
  }
}
/*****************************************************************************
** Function name:		UART0_IRQHandler
**
** Descriptions:		UART0 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void UART0_IRQHandler (void) 
{
  uint8_t IIRValue, LSRValue;
  uint8_t Dummy = Dummy;
	
  IIRValue = LPC_UART0->IIR;
    
  IIRValue >>= 1;			/* skip pending bit in IIR */
  IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
  if ( IIRValue == IIR_RLS )		/* Receive Line Status */
  {
	LSRValue = LPC_UART0->LSR;
	/* Receive Line Status */
	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{
	  /* There are errors or break interrupt */
	  /* Read LSR will clear the interrupt */
	  UART0Status = LSRValue;
	  Dummy = LPC_UART0->RBR;		/* Dummy read on RX to clear 
								interrupt, then bail out */
	  return;
	}
	if ( LSRValue & LSR_RDR )	/* Receive Data Ready */			
	{
	  /* If no error on RLS, normal ready, save into the data buffer. */
	  /* Note: read RBR will clear the interrupt */
	  UART0Buffer[UART0Count] = LPC_UART0->RBR;
	  UART0Count++;
	  if ( UART0Count == BUFSIZE )
	  {
		UART0Count = 0;		/* buffer overflow */
	  }	
	}
  }
  else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
  {
	/* Receive Data Available */
	UART0Buffer[UART0Count] = LPC_UART0->RBR;
	UART0Count++;
	if ( UART0Count == BUFSIZE )
	{
	  UART0Count = 0;		/* buffer overflow */
	}
  }
  else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
  {
	/* Character Time-out indicator */
	UART0Status |= 0x100;		/* Bit 9 as the CTI error */
  }
  else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
  {
	/* THRE interrupt */
	LSRValue = LPC_UART0->LSR;		/* Check status in the LSR to see if
								valid data in U0THR or not */
	if ( LSRValue & LSR_THRE )
	{
	  UART0TxEmpty = 1;
	}
	else
	{
	  UART0TxEmpty = 0;
	}
  }
}

/*****************************************************************************
** Function name:		UARTInit
**
** Descriptions:		Initialize UART port, setup pin select,
**						clock, parity, stop bits, FIFO, etc.
**
** parameters:			portNum(0 or 1) and UART baudrate
** Returned value:		true or false, return false only if the 
**						interrupt handler can't be installed to the 
**						VIC table
** 
*****************************************************************************/
uint32_t  UARTInit( uint32_t PortNum, uint32_t baudrate )
{
  uint32_t Fdiv;
  uint32_t pclkdiv, pclk;

  switch(PortNum)
  {
  	case 0:
	{
		LPC_PINCON->PINSEL0 &= ~0x000000F0;
		LPC_PINCON->PINSEL0 |= 0x00000050;	/* Enable TxD0 P0.2 and p0.3 */
		/* By default, the PCLKSELx value is zero, thus, the PCLK for
		all the peripherals is 1/4 of the SystemFrequency. */
		/* Bit 6,7 are for UART0 */
		pclkdiv = (LPC_SC->PCLKSEL0 >> 6) & 0x03;
		switch ( pclkdiv )
		{
		  case 0x00:
		  default:
			pclk = SystemCoreClock/4;
			break;
		  case 0x01:
			pclk = SystemCoreClock;
			break; 
		  case 0x02:
			pclk = SystemCoreClock/2;
			break; 
		  case 0x03:
			pclk = SystemCoreClock/8;
			break;
		}
	
	    LPC_UART0->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
		Fdiv = ( pclk / 16 ) / baudrate ;	/*baud rate */
	    LPC_UART0->DLM = Fdiv / 256;							
	    LPC_UART0->DLL = Fdiv % 256;
		LPC_UART0->LCR = 0x03;		/* DLAB = 0 */
	    LPC_UART0->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */
	
	   	NVIC_EnableIRQ(UART0_IRQn);
	
	    LPC_UART0->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART1 interrupt */
	    return (TRUE);
	}

	case 1:
	{
	#if 0
		LPC_PINCON->PINSEL0 &= ~0xC0000000;
		LPC_PINCON->PINSEL0 |= 0x40000000;	/* Enable TxD1 P0.15 */
		LPC_PINCON->PINSEL1 &= ~0x00000003;
		LPC_PINCON->PINSEL1 |= 0x00000001;	/* Enable RxD1 P0.16 */
	#else
		LPC_PINCON->PINSEL4 &= ~(3 << 0) ;
		LPC_PINCON->PINSEL4 |= (1 << 1);	/* Enable TxD1 P2.0 function 10*/
		LPC_PINCON->PINSEL4 &= ~(3 << 2);
		LPC_PINCON->PINSEL4 |= (1 << 3);	/* Enable RxD1 P2.1 function 10*/
	#endif	
		/* By default, the PCLKSELx value is zero, thus, the PCLK for
		all the peripherals is 1/4 of the SystemFrequency. */
		/* Bit 8,9 are for UART1 */
		pclkdiv = (LPC_SC->PCLKSEL0 >> 8) & 0x03;
		switch ( pclkdiv )
		{
		  case 0x00:
		  default:
			pclk = SystemCoreClock/4;
			break;
		  case 0x01:
			pclk = SystemCoreClock;
			break; 
		  case 0x02:
			pclk = SystemCoreClock/2;
			break; 
		  case 0x03:
			pclk = SystemCoreClock/8;
			break;
		}
	
	    LPC_UART1->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
		Fdiv = ( pclk / 16 ) / baudrate ;	/*baud rate */
	    LPC_UART1->DLM = Fdiv / 256;							
	    LPC_UART1->DLL = Fdiv % 256;
		LPC_UART1->LCR = 0x03;		/* DLAB = 0 */
	    LPC_UART1->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */
	
	   	NVIC_EnableIRQ(UART1_IRQn);
	
	    LPC_UART1->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART1 interrupt */
	    return (TRUE);
	}
	
	case 2:
    	break;

    case 3:
		LPC_SC->PCONP |= (1 << 25);
		#if 0
		LPC_PINCON->PINSEL0 &= ~0x0000000F;
		LPC_PINCON->PINSEL0 |= 0x0000000A;  /* RxD3 is P0.1 and TxD3 is P0.0 */
	#else
		LPC_PINCON->PINSEL9 |= 0x0F000000;  /* RxD3 is P4.29 and TxD3 is P4.28 */
	#endif
		/* By default, the PCLKSELx value is zero, thus, the PCLK for
		all the peripherals is 1/4 of the SystemFrequency. */
		/* Bit 18~19 is for UART3 */
		pclkdiv = (LPC_SC->PCLKSEL1 >> 18) & 0x03;
		switch ( pclkdiv )
		{
		  case 0x00:
		  default:
			pclk = SystemCoreClock/4;
			break;
		  case 0x01:
			pclk = SystemCoreClock;
			break; 
		  case 0x02:
			pclk = SystemCoreClock/2;
			break; 
		  case 0x03:
			pclk = SystemCoreClock/8;
			break;
		}
	
	    LPC_UART3->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
		Fdiv = ( pclk / 16 ) / baudrate ;	/*baud rate */
	    LPC_UART3->DLM = Fdiv / 256;							
	    LPC_UART3->DLL = Fdiv % 256;
		LPC_UART3->LCR = 0x03;		/* DLAB = 0 */
	    LPC_UART3->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */
	
	   	NVIC_EnableIRQ(UART3_IRQn);
	
	    LPC_UART3->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART3 interrupt */
	    return (TRUE);
	}
	
	return( FALSE ); 
}

/*****************************************************************************
** Function name:		UARTSend
**
** Descriptions:		Send a block of data to the UART 0 port based
**						on the data length
**
** parameters:			portNum, buffer pointer, and data length
** Returned value:		None
** 
*****************************************************************************/
void UARTSend( uint32_t portNum, uint8_t *BufferPtr, uint32_t Length )
{
  switch(portNum)
  {
  	case 0:
	
    	while ( Length != 0 )
    	{
	  		/* THRE status, contain valid data */
	  		while ( !(UART0TxEmpty & 0x01) );	
	  		LPC_UART0->THR = *BufferPtr;
	  		UART0TxEmpty = 0;	/* not empty in the THR until it shifts out */
	  		BufferPtr++;
	  		Length--;
		}
		break;
  
    case 1:
  
		while ( Length != 0 )
    	{
	 		 /* THRE status, contain valid data */
	  		while ( !(UART1TxEmpty & 0x01) );	
	  		LPC_UART1->THR = *BufferPtr;
	  		UART1TxEmpty = 0;	/* not empty in the THR until it shifts out */
	  		BufferPtr++;
	  		Length--;
    	}
			break;
  
   case 2:
  	default:
		break;

   case 3:
   
	while ( Length != 0 )
    {
	  	/* THRE status, contain valid data */
	  	while ( !(UART3TxEmpty & 0x01) );	
	  	LPC_UART3->THR = *BufferPtr;
	  	UART3TxEmpty = 0;	/* not empty in the THR until it shifts out */
	  	BufferPtr++;
	  	Length--;
    }
		break;
  
//	return;
  }
}

/*****************************************************************************
** Function name:		UARTsendchar
**
** Descriptions:		Send a character the UART x port 
**
** parameters:			portNum, and ch
** Returned value:		None
** 
*****************************************************************************/

void UARTsendchar(uint32_t portNum , uint8_t ch)
{
  switch(portNum)
  {
  	case 0:
	
	  		/* THRE status, contain valid data */
	  		while ( !(UART0TxEmpty & 0x01) );	
	  		LPC_UART0->THR = ch;
	  		UART0TxEmpty = 0;	/* not empty in the THR until it shifts out */
		break;
  
    case 1:
  
	 		 /* THRE status, contain valid data */
	  		while ( !(UART1TxEmpty & 0x01) );	
	  		LPC_UART1->THR = ch;
	  		UART1TxEmpty = 0;	/* not empty in the THR until it shifts out */
			break;
  
   case 2:
  	default:
		break;

   case 3:
   
	  	/* THRE status, contain valid data */
	  	while ( !(UART3TxEmpty & 0x01) );	
	  	LPC_UART3->THR = ch;
	  	UART3TxEmpty = 0;	/* not empty in the THR until it shifts out */
		break;
	}		
}
/******************************************************************************
**                            End Of File
******************************************************************************/
