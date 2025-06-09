/*********************************************************************************************************************
* File Information:
* Author : Alsayed Alsisi
* Date   : Wednesday, July 10, 2024
* Version: 1.0
* Contact: alsayed.alsisi@gmail.com
* File Name: linkedlist.h
* File Description: This file contains the public interfaces, datatypes, and other information of the linkedlist fun-
* ction library.
* License:
*********************************************************************************************************************/



/*********************************************************************************************************************
                                               << Header Guard >>
*********************************************************************************************************************/
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED


/*********************************************************************************************************************
                                               << File Inclusions >>
*********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*********************************************************************************************************************
                                               << Public Constants >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << Public Data Types >>
*********************************************************************************************************************/
/*********************************************************************************************************************
** Datatype Name:
*  node_t
*
** Description:
*  This is a structure datatype that will be used for creating a new linkedlist node.
*
** Datatype Elements:
*  [1] data: int
*      Stores node data.
*  [2] next_address: node_t*
*      Stores address of next linkedlist node.

*
** Use Example: Create a simple linkedlist:
*  Step 1: Create a linkedlist node and initialize it:
*          node_t my_head_node = {0, NULL};
*  Step 2: Change node data:
*          my_head_node.data = 7;
*  Step 3: Create a new linkedlist node:
*          my_head_node.next_node_address_ptr = (node_t*)malloc(sizeof(node_t));
*********************************************************************************************************************/
struct node_t
{
    int data;
    struct node_t* next_node_address_ptr;
};

/*********************************************************************************************************************
** Datatype Name:
*  queue_std_return_value_t
*
** Description:
*  This is an ENUM datatype that will be used for the return value of different queue operations to indicate the
*  status of the operation. Each operation return one or more of these operation codes. The return values need to be
*  checked carefully for successful queue operations.
*
** Datatype Elements:
*  [1] LINKEDLIST_OP_SUCCESS
*      Indicates that the operation performed was successful.

*********************************************************************************************************************/
typedef enum
{
    LINKEDLIST_OP_SUCCESS = 0,
    LINKEDLIST_OP_FAIL = 1
} linkedlist_std_ret_t;

/*********************************************************************************************************************
                                          << Public Variable Declarations >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                           << Public Function Declarations >>
*********************************************************************************************************************/
extern linkedlist_std_ret_t  linkedlist_insert_end(struct node_t* head_node, int new_data);
extern linkedlist_std_ret_t  linkedlist_insert_index(struct node_t* head_node, unsigned short node_index, int new_data);
extern linkedlist_std_ret_t  linkedlist_get_end(struct node_t* head_node, int* current_data);
extern linkedlist_std_ret_t  linkedlist_get_index(struct node_t* head_node, unsigned short node_index, int* current_data);
extern linkedlist_std_ret_t  linkedlist_delete_end(struct node_t* head_node);
extern linkedlist_std_ret_t  linkedlist_delete_index(struct node_t* head_node, unsigned short node_index);
extern linkedlist_std_ret_t  linkedlist_delete_all(struct node_t* head_node);
#endif /** LINKEDLIST_H_INCLUDED **/
/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/
