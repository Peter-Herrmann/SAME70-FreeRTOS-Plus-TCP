/*
 * FreeRTOSConfig.h
 *
 *  Author: pherrmann
 */ 


#ifndef FREERTOSCONFIG_H_
#define FREERTOSCONFIG_H_

#if defined(__GNUC__) || defined(__ICCARM__)
/* Includes to be ignored by assembler */
    #include <stdint.h>
    void assert_triggered(const char *file, uint32_t line);
#endif

extern uint32_t SystemCoreClock;

#ifndef configCPU_CLOCK_HZ
    #define configCPU_CLOCK_HZ                      (300000000)
#endif

#ifndef configMAX_PRIORITIES
    #define configMAX_PRIORITIES                    (8)
#endif

#ifndef configMINIMAL_STACK_SIZE
    #define configMINIMAL_STACK_SIZE                ((uint16_t)130)
#endif

#ifndef configTOTAL_HEAP_SIZE
    #define configTOTAL_HEAP_SIZE                   ((size_t)100u * 1024)
#endif

#ifndef configUSE_MUTEXES
    #define configUSE_MUTEXES                       (1)
#endif

#ifndef configUSE_COUNTING_SEMAPHORES
    #define configUSE_COUNTING_SEMAPHORES           (1)
#endif

#ifndef FREERTOS_ADVANCED_CONFIG
    #define FREERTOS_ADVANCED_CONFIG                (1)
#endif

#ifndef configUSE_PREEMPTION
    #define configUSE_PREEMPTION                    (1)
#endif

#ifndef configUSE_RECURSIVE_MUTEXES
    #define configUSE_RECURSIVE_MUTEXES             (1)
#endif

#ifndef configGENERATE_RUN_TIME_STATS
    #define configGENERATE_RUN_TIME_STATS           (0)
#endif

#if configGENERATE_RUN_TIME_STATS
    extern void     vConfigureTimerForRunTimeStats(void);
    extern uint32_t vGetRunTimeCounterValue(void);
    #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
    #define portGET_RUN_TIME_COUNTER_VALUE()         vGetRunTimeCounterValue()
#endif

#ifndef configUSE_16_BIT_TICKS
    #define configUSE_16_BIT_TICKS                  (0)
#endif

#ifndef configCHECK_FOR_STACK_OVERFLOW
    #define configCHECK_FOR_STACK_OVERFLOW          (0)
#endif

#ifndef configUSE_MALLOC_FAILED_HOOK
    #define configUSE_MALLOC_FAILED_HOOK            (1)
#endif

#ifndef configUSE_IDLE_HOOK
    #define configUSE_IDLE_HOOK                     (0)
#endif

#ifndef configUSE_TICK_HOOK
    #define configUSE_TICK_HOOK                     (0)
#endif

#ifndef configUSE_TICKLESS_IDLE
    #define configUSE_TICKLESS_IDLE                 (0)
#endif

#ifndef configUSE_TRACE_FACILITY
    #define configUSE_TRACE_FACILITY                (1)
#endif

#ifndef configUSE_STATS_FORMATTING_FUNCTIONS
    #define configUSE_STATS_FORMATTING_FUNCTIONS    (1)
#endif

#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION (1)
#endif

#ifndef configUSE_APPLICATION_TASK_TAG
    #define configUSE_APPLICATION_TASK_TAG          (0)
#endif

#ifndef configUSE_CO_ROUTINES
    #define configUSE_CO_ROUTINES                   (0)
#endif

#ifndef configMAX_CO_ROUTINE_PRIORITIES
    #define configMAX_CO_ROUTINE_PRIORITIES         (2)
#endif

#ifndef configTICK_RATE_HZ
    #define configTICK_RATE_HZ                      ((TickType_t)1000)
#endif

#ifndef configUSE_TIMERS
    #define configUSE_TIMERS                        (0)
#endif

#ifndef configTIMER_TASK_PRIORITY
    #define configTIMER_TASK_PRIORITY               (configMAX_PRIORITIES - 1)
#endif

#define configTIMER_QUEUE_LENGTH                    (5)

#ifndef TIMER_TASK_STACK_DEPTH
    #define configTIMER_TASK_STACK_DEPTH            (configMINIMAL_STACK_SIZE * 2)
#endif

#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS		                    __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS		                    (3)
#endif


#define configMAX_TASK_NAME_LEN                     (8)
#define configIDLE_SHOULD_YIELD                     (1)
#define configQUEUE_REGISTRY_SIZE                   (8)
#define configUSE_QUEUE_SETS                        (1)
#define configENABLE_BACKWARD_COMPATIBILITY         (1)

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */ 

#define INCLUDE_xTaskGetSchedulerState              (1)
#define INCLUDE_uxTaskGetStackHighWaterMark         (0)
#define INCLUDE_xTimerGetTimerDaemonTaskHandle      (0)

#ifndef INCLUDE_vTaskPrioritySet    
    #define INCLUDE_vTaskPrioritySet                (1)
#endif  

#ifndef INCLUDE_uxTaskPriorityGet   
    #define INCLUDE_uxTaskPriorityGet               (1)
#endif  

#ifndef INCLUDE_vTaskDelete 
    #define INCLUDE_vTaskDelete                     (1)
#endif  

#ifndef INCLUDE_vTaskSuspend    
    #define INCLUDE_vTaskSuspend                    (1)
#endif  

#ifndef INCLUDE_xResumeFromISR  
    #define INCLUDE_xResumeFromISR                  (0)
#endif  

#ifndef INCLUDE_vTaskDelayUntil 
    #define INCLUDE_vTaskDelayUntil                 (0)
#endif  

#ifndef INCLUDE_vTaskDelay  
    #define INCLUDE_vTaskDelay                      (1)
#endif  

#ifndef INCLUDE_xTaskGetCurrentTaskHandle   
    #define INCLUDE_xTaskGetCurrentTaskHandle       (1)
#endif  

#ifndef INCLUDE_xTaskGetIdleTaskHandle  
    #define INCLUDE_xTaskGetIdleTaskHandle          (0)
#endif  

#ifndef INCLUDE_pcTaskGetTaskName   
    #define INCLUDE_pcTaskGetTaskName               (1)
#endif  

#ifndef INCLUDE_eTaskGetState   
    #define INCLUDE_eTaskGetState                   (0)
#endif  

#ifndef INCLUDE_vTaskCleanUpResources   
    #define INCLUDE_vTaskCleanUpResources           (0)
#endif  

#ifndef INCLUDE_xTimerPendFunctionCall  
    #define INCLUDE_xTimerPendFunctionCall          (0)
#endif  

/* FreeRTOS+CLI buffer */   
#define configCOMMAND_INT_MAX_OUTPUT_SIZE           (400)

#define configASSERT(x) \
	if ((x) == 0)       \
    {                   \
		for (;;)        \
			;           \
	}

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names - or at least those used in the unmodified vector table. */

#define vPortSVCHandler                             SVC_Handler
#define xPortPendSVHandler                          PendSV_Handler
#define xPortSysTickHandler                         SysTick_Handler


/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY     (0x07)

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY (5)

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY             (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY        (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))


#endif /* FREERTOSCONFIG_H_ */
