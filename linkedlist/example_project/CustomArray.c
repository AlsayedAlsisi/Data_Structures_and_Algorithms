/*********************************************************************************************************************
* File Information:
* Author : Alsayed Alsisi
* Date   : Wednesday, July 10, 2024
* Version: 1.0
* Contact: alsayed.alsisi@gmail.com
* File Name: CustomArray.c
* File Description: This file contains the implementation of the CustomArray component.
* License:
*********************************************************************************************************************/


/*********************************************************************************************************************
                                         << File Inclusions >>
*********************************************************************************************************************/
#include "linkedlist.h"
#include "CustomArray.h"

/*********************************************************************************************************************
                                  << Public Function Definitions >>
*********************************************************************************************************************/
/*********************************************************************************************************************
** Function Name:
*  initArray
*
** Purpose:
*  This function initializes the array.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the array to be
*    created.
*  - initial_capacity: size_t
*    Takes the size capacity of the array to be created, i.e. the maximum number of the elements that the array can
*    store.
*
** Return Value:
*  - custarr_std_ret_t
*    Returns error code of the function:
*    -- CUSTARR_OP_SUCCESS
*    -- CUSTARR_OP_FAIL
*    -- CUSTARR_OP_FULL
*    -- CUSTARR_OP_OUTOFRANGE
*********************************************************************************************************************/
custarr_std_ret_t initArray(custarr_t *my_array, size_t initial_capacity)
{
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;
    static array_init_status_t current_init_status = ARRAY_UNINITIALIZED;

    my_array->init_status = current_init_status;

    if(ARRAY_UNINITIALIZED == my_array->init_status)
    {
        /** Lock access to array **/
        my_array->lock = ARRAY_LOCKED;
        /** Initialize array structure elements **/
        my_array->head_node.data = 0;
        my_array->head_node.next_node_address_ptr = NULL;
        my_array->size = 1;
        my_array->capacity = initial_capacity;
        /** Unlock access to array **/
        my_array->init_status = ARRAY_INITIALIZED;
        current_init_status   = ARRAY_INITIALIZED;
        ret_val = CUSTARR_OP_SUCCESS;


        my_array->lock = ARRAY_UNLOCKED;
    }

    return ret_val;

}


/*********************************************************************************************************************
** Function Name:
*  lock_getstatus
*
** Purpose:
*  This function returns the lock status of the array
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.

*
** Return Value:
*  - pthread_mutex_t
*    Returns the status of the array lock
*    -- ARRAY_UNLOCKED
*    -- ARRAY_LOCKED

*********************************************************************************************************************/
pthread_mutex_t lock_getstatus(custarr_t *my_array)
{
    return my_array->lock;
}



/*********************************************************************************************************************
** Function Name:
*  insertElement_atEnd
*
** Purpose:
*  This function inserts an element in the end of the array.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*  - data: int
*    Value to be stored in the created element.
*
** Return Value:
*  - custarr_std_ret_t
*    Returns error code of the function:
*    -- CUSTARR_OP_SUCCESS
*    -- CUSTARR_OP_FAIL
*    -- CUSTARR_OP_FULL
*    -- CUSTARR_OP_OUTOFRANGE
*********************************************************************************************************************/
custarr_std_ret_t insertElement_atEnd(custarr_t *my_array, int data)
{
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;
    linkedlist_std_ret_t  linkedlist_ret_val = LINKEDLIST_OP_FAIL;
    my_array->lock = ARRAY_LOCKED;
    if((my_array->size) < (my_array->capacity))
    {
        linkedlist_ret_val = linkedlist_insert_end(&my_array->head_node, data);
        if(LINKEDLIST_OP_SUCCESS == linkedlist_ret_val)
        {
            my_array->size = my_array->size + 1; /** increment size **/
            ret_val = CUSTARR_OP_SUCCESS;    /** mark operation as successful **/
        }
    }
    else
    {
        ret_val = CUSTARR_OP_FULL; /** Array capacity exceeded, so you can't add more elements. **/
    }
    my_array->lock = ARRAY_UNLOCKED;

    return ret_val;
}


/*********************************************************************************************************************
** Function Name:
*  insertElement_atIndex
*
** Purpose:
*  This function inserts an element in the array at a provided index.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*  - index: size_t
*    Takes the index of the element to be inserted
*  - data: int
*    Value to be stored in the created element.
*
** Return Value:
*  - custarr_std_ret_t
*    Returns error code of the function:
*    -- CUSTARR_OP_SUCCESS
*    -- CUSTARR_OP_FAIL
*    -- CUSTARR_OP_FULL
*    -- CUSTARR_OP_OUTOFRANGE
*********************************************************************************************************************/
custarr_std_ret_t insertElement_atIndex(custarr_t *my_array, size_t index, int data)
{
    custarr_std_ret_t custarr_ret_val = CUSTARR_OP_FAIL;
    size_t array_new_size = my_array->size + 1;
    linkedlist_std_ret_t  linkedlist_ret_val = LINKEDLIST_OP_FAIL;
    my_array->lock = ARRAY_LOCKED;
    if((array_new_size <= my_array->capacity) && (index < array_new_size))
    {
         linkedlist_ret_val = linkedlist_insert_index(&my_array->head_node, index, data);

         if(LINKEDLIST_OP_SUCCESS == linkedlist_ret_val)
         {
             my_array->size = my_array->size + 1;
             custarr_ret_val = CUSTARR_OP_SUCCESS;
         }

    }
    else
    {
        custarr_ret_val = CUSTARR_OP_OUTOFRANGE;
    }
    my_array->lock = ARRAY_UNLOCKED;
    return custarr_ret_val;
}


/*********************************************************************************************************************
** Function Name:
*  deleteElement_atEnd
*
** Purpose:
*  This function deletes an element from the end of the array.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*
** Return Value:
*  - custarr_std_ret_t
*    Returns error code of the function:
*    -- CUSTARR_OP_SUCCESS
*    -- CUSTARR_OP_FAIL
*    -- CUSTARR_OP_FULL
*    -- CUSTARR_OP_OUTOFRANGE
*********************************************************************************************************************/
custarr_std_ret_t deleteElement_atEnd(custarr_t *my_array)
{
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;
    linkedlist_std_ret_t  linkedlist_ret_val = LINKEDLIST_OP_FAIL;
    my_array->lock = ARRAY_LOCKED;

    if((ARRAY_INITIALIZED == my_array->init_status) && (NULL != my_array->head_node.next_node_address_ptr))
    {
        linkedlist_ret_val =   linkedlist_delete_end(&my_array->head_node);
        ret_val = linkedlist_ret_val;
        my_array->size = my_array->size - 1;
    }

    my_array->lock = ARRAY_UNLOCKED;
    return ret_val;

}

/*********************************************************************************************************************
** Function Name:
*  deleteElement_atIndex
*
** Purpose:
*  This function deletes an element at a provided index.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*  - index: size_t
*    index of the element to be deleted.
*
** Return Value:
*  - custarr_std_ret_t
*    Returns error code of the function:
*    -- CUSTARR_OP_SUCCESS
*    -- CUSTARR_OP_FAIL
*    -- CUSTARR_OP_FULL
*    -- CUSTARR_OP_OUTOFRANGE
*********************************************************************************************************************/
custarr_std_ret_t deleteElement_atIndex(custarr_t *my_array, size_t index)
{
    custarr_std_ret_t custarr_ret_val = CUSTARR_OP_FAIL;
    linkedlist_std_ret_t  linkedlist_ret_val = LINKEDLIST_OP_FAIL;

    my_array->lock = ARRAY_LOCKED;
    if(index < my_array->size)
    {
         linkedlist_ret_val = linkedlist_delete_index(&my_array->head_node, index);

         if(LINKEDLIST_OP_SUCCESS == linkedlist_ret_val)
         {
             my_array->size = my_array->size - 1;
             custarr_ret_val = CUSTARR_OP_SUCCESS;
         }

    }
    else
    {
        custarr_ret_val = CUSTARR_OP_OUTOFRANGE;
    }
    my_array->lock = ARRAY_UNLOCKED;
    return custarr_ret_val;

}

/*********************************************************************************************************************
** Function Name:
*  getElement_atEnd
*
** Purpose:
*  This function returns the value of the elements in the end of the array.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*  - data: int*
*    points to the variable in which the returned data will be stored.
*
** Return Value:
*  - custarr_std_ret_t
*    Returns error code of the function:
*    -- CUSTARR_OP_SUCCESS
*    -- CUSTARR_OP_FAIL
*    -- CUSTARR_OP_FULL
*    -- CUSTARR_OP_OUTOFRANGE
*********************************************************************************************************************/
custarr_std_ret_t getElement_atEnd(custarr_t *my_array, int* data)
{
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;

    my_array->lock = ARRAY_LOCKED;
    ret_val = linkedlist_get_end(&my_array->head_node, data);
    my_array->lock = ARRAY_UNLOCKED;
    return ret_val;
}

/*********************************************************************************************************************
** Function Name:
*  getElement_atIndex
*
** Purpose:
*  This function return the value of an element at a provided index.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*  - index: size_t
*    index of the element to be read.
*  - data: int*
*    points to the variable in which the returned data will be stored.
*
** Return Value:
*  - custarr_std_ret_t
*    Returns error code of the function:
*    -- CUSTARR_OP_SUCCESS
*    -- CUSTARR_OP_FAIL
*    -- CUSTARR_OP_FULL
*    -- CUSTARR_OP_OUTOFRANGE
*********************************************************************************************************************/
custarr_std_ret_t getElement_atIndex(custarr_t *my_array, size_t index, int* data)
{
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;

    my_array->lock = ARRAY_LOCKED;
    if(index < (my_array->size))
    {
        linkedlist_get_index(&my_array->head_node, index, data);
        ret_val = CUSTARR_OP_SUCCESS;
    }
    else
    {
        ret_val = CUSTARR_OP_OUTOFRANGE;
    }
    my_array->lock = ARRAY_UNLOCKED;
    return ret_val;

}


/*********************************************************************************************************************
** Function Name:
*  freeArray
*
** Purpose:
*  This function frees all the allocated elements of the array and returns the array to the initialization status,
*  except the array is still marked "ARRAY_INITIALIZED".
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*
** Return Value:
*  - custarr_std_ret_t
*    Returns error code of the function:
*    -- CUSTARR_OP_SUCCESS
*    -- CUSTARR_OP_FAIL
*    -- CUSTARR_OP_FULL
*    -- CUSTARR_OP_OUTOFRANGE
*********************************************************************************************************************/
custarr_std_ret_t freeArray(custarr_t *my_array)
{
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;
    linkedlist_std_ret_t linkedlist_ret_val = LINKEDLIST_OP_FAIL;

    my_array->lock = ARRAY_LOCKED;
    /** Only free if the array is initialized and it has dynamically allocated data **/
    if((ARRAY_INITIALIZED == my_array->init_status) && (NULL != my_array->head_node.next_node_address_ptr))
    {
        linkedlist_ret_val = linkedlist_delete_all(&my_array->head_node);
        my_array->size = 1;
        ret_val = linkedlist_ret_val;

    }
    my_array->lock = ARRAY_UNLOCKED;

    return ret_val;
}


/*********************************************************************************************************************
** Function Name:
*  array_sizeGet
*
** Purpose:
*  This function returns the current size of the array, i.e. allocated elements of the array.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*
** Return Value:
*  - size_t
*    Current size of the array.
*********************************************************************************************************************/
/** Returns array current size (total number of active nodes)**/
size_t array_sizeGet(custarr_t *my_array)
{
    return my_array->size;
}


/*********************************************************************************************************************
** Function Name:
*  array_capacityGet
*
** Purpose:
*  Returns array current assigned capacity.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*
** Return Value:
*  - size_t
*    Value of the current capacity.
*********************************************************************************************************************/
/** Returns array current capacity (maximum number of elements(nodes) array can hold)**/
size_t array_capacityGet(custarr_t *my_array)
{
    return my_array->capacity;
}


/*********************************************************************************************************************
** Function Name:
*  array_lockstatus
*
** Purpose:
*  Returns array current lock status.
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*
** Return Value:
*  - pthread_mutex_t
*    Returns lock status of the function:
*    -- ARRAY_UNLOCKED
*    -- ARRAY_LOCKED
*********************************************************************************************************************/
pthread_mutex_t array_lockstatus(custarr_t *my_array)
{
    return my_array->lock;
}


/*********************************************************************************************************************
** Function Name:
*  array_capacityUpdate
*
** Purpose:
*  Sets a new capacity for the array. Extends or decreases the capacity as needed
*
** Input Parameters:
*  - array: CustomArray*
*    A pointer to an object created of type CustomArray, which contains all the information for the created array.
*  - new_capacity: size_t
*    New capacity to be assigned.
*
** Return Value:
*  - custarr_std_ret_t
*    Returns error code of the function:
*    -- CUSTARR_OP_SUCCESS
*    -- CUSTARR_OP_FAIL
*    -- CUSTARR_OP_FULL
*    -- CUSTARR_OP_OUTOFRANGE
*********************************************************************************************************************/
custarr_std_ret_t array_capacityUpdate(custarr_t *my_array, size_t new_capacity)
{
    custarr_std_ret_t ret_val = CUSTARR_OP_FAIL;
    if(new_capacity >= my_array->size)
    {
        my_array->capacity = new_capacity;
        ret_val = CUSTARR_OP_SUCCESS;
    }
    else
    {
        /** New capacity can't be smaller than current array size**/
    }

    return ret_val;

}
/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/
