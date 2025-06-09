/*********************************************************************************************************************
* File Information:
* Author : Alsayed Alsisi
* Date   : Wednesday, July 10, 2024
* Version: 1.0
* Contact: alsayed.alsisi@gmail.com
* File Name: CustomArray.h
* File Description: This file contains the public interfaces, datatypes, and other information of the CustomArray co-
* mponent.
* License:
*********************************************************************************************************************/



/*********************************************************************************************************************
                                               << Header Guard >>
*********************************************************************************************************************/
#ifndef CUSTOMARRAY_H_INCLUDED
#define CUSTOMARRAY_H_INCLUDED


/*********************************************************************************************************************
                                               << File Inclusions >>
*********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
/*********************************************************************************************************************
                                               << Public Constants >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << Public Data Types >>
*********************************************************************************************************************/
/*********************************************************************************************************************
** Datatype Name:
*  custarr_std_ret_t
*
** Description:
*  This is an ENUM datatype that will be used for the return value of different CustomArray operations to indicate the
*  status of the operation. Each operation return one or more of these operation codes. The return values need to be
*  checked carefully for successful CustomArray operations.
*
** Datatype Elements:
*  [1] LINKEDLIST_OP_SUCCESS
*      Indicates that the operation performed was successful.
*  [2] CUSTARR_OP_FAIL
*      Indicates that the operation performed failed.
*  [3] CUSTARR_OP_FULL
*      Indicates that array is full.
*  [4] CUSTARR_OP_OUTOFRANGE
*      Indicates that the inserted value is out of range.
*********************************************************************************************************************/
typedef enum
{
    CUSTARR_OP_SUCCESS    = 0,
    CUSTARR_OP_FAIL       = 1,
    CUSTARR_OP_FULL       = 2,
    CUSTARR_OP_OUTOFRANGE = 3,
}   custarr_std_ret_t;


/*********************************************************************************************************************
** Datatype Name:
*  pthread_mutex_t
*
** Description:
*  Returns lock status of the function.
*
** Datatype Elements:
*  [1] ARRAY_UNLOCKED
*      Indicates that the array is unlocked, so it can be accessed and different operations on the array can be perfo-
*       rmed.
*  [2] ARRAY_LOCKED
*      Indicates that the array is locked, so it not can be accessed and different operations on the array can not be
*      performed.
*********************************************************************************************************************/
typedef enum
{
    ARRAY_UNLOCKED = 0,
    ARRAY_LOCKED
} pthread_mutex_t;

/*********************************************************************************************************************
** Datatype Name:
*  array_init_status_t
*
** Description:
*  This is an ENUM datatype that will be used for to mark an initialized array as initialized, so if the initarray()
*  API is called again for the same array, nothing would happen.
*
** Datatype Elements:
*  [1] ARRAY_INITIALIZED
*      Indicates that the array is already initialized.
*  [2] ARRAY_UNINITIALIZED
*      Indicates that the array is not initialized.

*********************************************************************************************************************/
typedef enum
{
    ARRAY_INITIALIZED = 0,
    ARRAY_UNINITIALIZED = 1
} array_init_status_t;


/*********************************************************************************************************************
** Datatype Name:
*  custarr_t
*
** Description:
*  datatype for storing all the information for the array to be created.
*
** Datatype Elements:
*  [1] head_node: struct node_t
*      structure that contains the information of the array head node.
*  [2] size: size_t
*      Stores the current allocated size of the array
*  [3] capacity: size_t
*      maximum size that can be allocated for the array.
*  [4] lock: pthread_mutex_t
*      mutex to lock access to array while in use.
*  [5] init_status: array_init_status_t
*      stores the initializations status of the array.
*********************************************************************************************************************/
typedef struct {
 struct node_t head_node;
 size_t size;
 size_t capacity;
 pthread_mutex_t lock;
 array_init_status_t init_status;
} custarr_t;

/*********************************************************************************************************************
                                          << Public Variable Declarations >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                           << Public Function Declarations >>
*********************************************************************************************************************/
extern custarr_std_ret_t initArray(custarr_t *my_array, size_t initial_capacity);
extern custarr_std_ret_t insertElement_atEnd(custarr_t *my_array, int element);
extern custarr_std_ret_t insertElement_atIndex(custarr_t *my_array, size_t index, int element);
extern custarr_std_ret_t deleteElement_atEnd(custarr_t *my_array);
extern custarr_std_ret_t deleteElement_atIndex(custarr_t *my_array, size_t index);
extern custarr_std_ret_t getElement_atEnd(custarr_t *my_array, int* data);
extern custarr_std_ret_t getElement_atIndex(custarr_t *my_array, size_t index, int* data);
extern custarr_std_ret_t freeArray(custarr_t *my_array);
extern size_t array_sizeGet(custarr_t *my_array);
extern size_t array_capacityGet(custarr_t *my_array);
extern pthread_mutex_t array_lockstatus(custarr_t *my_array);
extern custarr_std_ret_t array_capacityUpdate(custarr_t *my_array, size_t new_capacity);

#endif /** CUSTOMARRAY_H_INCLUDED **/
/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/
