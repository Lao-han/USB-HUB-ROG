
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000C00

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
				DCD     WWDG_IRQHandler
				DCD     PVD_IRQHandler
				DCD     TAMPER_IRQHandler
				DCD     RTC_IRQHandler
				DCD     FLASH_IRQHandler
				DCD     RCC_IRQHandler
				DCD     EXTI0_IRQHandler
				DCD     EXTI1_IRQHandler
				DCD     EXTI2_IRQHandler
				DCD     EXTI3_IRQHandler
				DCD     EXTI4_IRQHandler
				DCD     DMAChannel1_IRQHandler
				DCD     DMAChannel2_IRQHandler
				DCD     DMAChannel3_IRQHandler
				DCD     DMAChannel4_IRQHandler
				DCD     DMAChannel5_IRQHandler
				DCD     DMAChannel6_IRQHandler
				DCD     DMAChannel7_IRQHandler
				DCD     ADC_IRQHandler
				DCD     USB_HP_CAN_TX_IRQHandler
				DCD     USB_LP_CAN_RX0_IRQHandler
				DCD     CAN_RX1_IRQHandler
				DCD     CAN_SCE_IRQHandler
				DCD     EXTI9_5_IRQHandler
				DCD     TIM1_BRK_IRQHandler
				DCD     TIM1_UP_IRQHandler
				DCD     TIM1_TRG_COM_IRQHandler
				DCD     TIM1_CC_IRQHandler
				DCD     TIM2_IRQHandler
				DCD     TIM3_IRQHandler
				DCD     TIM4_IRQHandler
				DCD     I2C1_EV_IRQHandler
				DCD     I2C1_ER_IRQHandler
				DCD     I2C2_EV_IRQHandler
				DCD     I2C2_ER_IRQHandler
				DCD     SPI1_IRQHandler
				DCD     SPI2_IRQHandler
				DCD     USART1_IRQHandler
				DCD     USART2_IRQHandler
				DCD     USART3_IRQHandler
				DCD     EXTI15_10_IRQHandler
				DCD     RTCAlarm_IRQHandler
				DCD     USBWakeUp_IRQHandler

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

				EXPORT  WWDG_IRQHandler				[WEAK]
				EXPORT  PVD_IRQHandler				[WEAK]
				EXPORT  TAMPER_IRQHandler			[WEAK]
				EXPORT  RTC_IRQHandler				[WEAK]
				EXPORT  FLASH_IRQHandler			[WEAK]
				EXPORT  RCC_IRQHandler				[WEAK]
				EXPORT  EXTI0_IRQHandler			[WEAK]
				EXPORT  EXTI1_IRQHandler			[WEAK]
				EXPORT  EXTI2_IRQHandler			[WEAK]
				EXPORT  EXTI3_IRQHandler			[WEAK]
				EXPORT  EXTI4_IRQHandler			[WEAK]
				EXPORT  DMAChannel1_IRQHandler		[WEAK]
				EXPORT  DMAChannel2_IRQHandler		[WEAK]
				EXPORT  DMAChannel3_IRQHandler		[WEAK]
				EXPORT  DMAChannel4_IRQHandler		[WEAK]
				EXPORT  DMAChannel5_IRQHandler		[WEAK]
				EXPORT  DMAChannel6_IRQHandler		[WEAK]
				EXPORT  DMAChannel7_IRQHandler		[WEAK]
				EXPORT  ADC_IRQHandler				[WEAK]
				EXPORT  USB_HP_CAN_TX_IRQHandler	[WEAK]
				EXPORT  USB_LP_CAN_RX0_IRQHandler	[WEAK]
				EXPORT  CAN_RX1_IRQHandler			[WEAK]
				EXPORT  CAN_SCE_IRQHandler			[WEAK]
				EXPORT  EXTI9_5_IRQHandler			[WEAK]
				EXPORT  TIM1_BRK_IRQHandler			[WEAK]
				EXPORT  TIM1_UP_IRQHandler			[WEAK]
				EXPORT  TIM1_TRG_COM_IRQHandler		[WEAK]
				EXPORT  TIM1_CC_IRQHandler			[WEAK]
				EXPORT  TIM2_IRQHandler				[WEAK]
				EXPORT  TIM3_IRQHandler				[WEAK]
				EXPORT  TIM4_IRQHandler				[WEAK]
				EXPORT  I2C1_EV_IRQHandler			[WEAK]
				EXPORT  I2C1_ER_IRQHandler			[WEAK]
				EXPORT  I2C2_EV_IRQHandler			[WEAK]
				EXPORT  I2C2_ER_IRQHandler			[WEAK]
				EXPORT  SPI1_IRQHandler				[WEAK]
				EXPORT  SPI2_IRQHandler				[WEAK]
				EXPORT  USART1_IRQHandler			[WEAK]
				EXPORT  USART2_IRQHandler			[WEAK]
				EXPORT  USART3_IRQHandler			[WEAK]
				EXPORT  EXTI15_10_IRQHandler		[WEAK]
				EXPORT  RTCAlarm_IRQHandler			[WEAK]
				EXPORT  USBWakeUp_IRQHandler		[WEAK]

WWDG_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMAChannel1_IRQHandler
DMAChannel2_IRQHandler
DMAChannel3_IRQHandler
DMAChannel4_IRQHandler
DMAChannel5_IRQHandler
DMAChannel6_IRQHandler
DMAChannel7_IRQHandler
ADC_IRQHandler
USB_HP_CAN_TX_IRQHandler
USB_LP_CAN_RX0_IRQHandler
CAN_RX1_IRQHandler
CAN_SCE_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_IRQHandler
TIM1_UP_IRQHandler
TIM1_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTCAlarm_IRQHandler
USBWakeUp_IRQHandler
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
