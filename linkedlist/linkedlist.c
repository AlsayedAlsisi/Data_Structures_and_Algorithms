/*********************************************************************************************************************
* File Information:
* Author : Alsayed Alsisi
* Date   : Wednesday, July 10, 2024
* Version: 1.0
* Contact: alsayed.alsisi@gmail.com
* File Name: linkedlist.c
* File Description: This file contains the implementation of the linkedlist datastructure.
* License:
*********************************************************************************************************************/


/*********************************************************************************************************************
                                         << File Inclusions >>
*********************************************************************************************************************/
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

/*********************************************************************************************************************
                                  << Private Function Declarations >>
*********************************************************************************************************************/
static void memFree_safe(void** pointer_to_free);

/*********************************************************************************************************************
                                  << Public Function Definitions >>
*********************************************************************************************************************/
linkedlist_std_ret_t  linkedlist_insert_end(struct node_t* head_node, int new_data)
{
    linkedlist_std_ret_t ret_val = LINKEDLIST_OP_FAIL;
    struct node_t* node_current = head_node;
    struct node_t* node_new = (struct node_t*)malloc(sizeof(struct node_t));

    if(NULL!=node_new)
    {
        node_new->next_node_address_ptr = NULL;
        node_new->data = new_data;

        /** Iterating through the linkedlist to reach the last node **/
        while(node_current->next_node_address_ptr!= NULL)
        {
            node_current = node_current->next_node_address_ptr;
        }/** node_current at this point points to the last node **/

        /** link the last node to the new node: **/
        node_current->next_node_address_ptr = node_new;
        ret_val = LINKEDLIST_OP_SUCCESS;
    }

    return ret_val;

}

linkedlist_std_ret_t  linkedlist_insert_index(struct node_t* head_node, unsigned short node_index, int new_data)
{
    linkedlist_std_ret_t ret_val = LINKEDLIST_OP_FAIL;
    struct node_t* node_current = head_node;
    struct node_t* node_new = (struct node_t*)malloc(sizeof(struct node_t));
    node_new->data = new_data;

    unsigned short loop_cntr = 0;

    /** Iterating through the linkedlist to reach the required index **/
    while(node_current->next_node_address_ptr!= NULL)
    {
        if(loop_cntr == (node_index-1))
        {
            node_new->next_node_address_ptr = node_current->next_node_address_ptr;
            node_current->next_node_address_ptr = node_new;
            ret_val = LINKEDLIST_OP_SUCCESS;
            break;
        }

        node_current = node_current->next_node_address_ptr;
        loop_cntr= loop_cntr+1;
    }

    return ret_val;

}

linkedlist_std_ret_t  linkedlist_get_end(struct node_t* head_node, int* current_data)
{
    linkedlist_std_ret_t ret_val = LINKEDLIST_OP_FAIL;
    struct node_t* node_current = head_node;


    /** Iterating through the linkedlist to reach the node in the end **/
    while(node_current->next_node_address_ptr!= NULL)
    {
        node_current = node_current->next_node_address_ptr;
    } /** At this point node current points to the last node.
          If the array has only the head node, it will point to the head node.**/

    *current_data = node_current->data;
    ret_val = LINKEDLIST_OP_SUCCESS;

    return ret_val;

}

linkedlist_std_ret_t  linkedlist_get_index(struct node_t* head_node, unsigned short node_index, int* data)
{
    linkedlist_std_ret_t ret_val = LINKEDLIST_OP_FAIL;
    struct node_t* node_current = head_node;
    unsigned short loop_cntr = 0;


    /** Iterating through the linkedlist to reach the node at required node index **/
    while(node_current->next_node_address_ptr!= NULL)
    {
        if(loop_cntr == node_index)
        {
            *data =  node_current->data;
            ret_val = LINKEDLIST_OP_SUCCESS;
            break;
        }

        node_current = node_current->next_node_address_ptr;
        loop_cntr= loop_cntr+1;

        if(loop_cntr == node_index)
        {
            *data =  node_current->data;
            ret_val = LINKEDLIST_OP_SUCCESS;
            break;
        }


    }


    return ret_val;

}

linkedlist_std_ret_t  linkedlist_delete_end(struct node_t* head_node)
{
    linkedlist_std_ret_t ret_val = LINKEDLIST_OP_FAIL;
    struct node_t* node_current = head_node;
    struct node_t* node_to_delete = NULL;



    if(NULL!= head_node->next_node_address_ptr)
    {

        /** Iterating through the linkedlist to reach the last node **/
        while(node_current->next_node_address_ptr!= NULL)
        {
            node_to_delete = node_current;
            node_current = node_current->next_node_address_ptr;
        }/** node_current at this point points to the last node **/

        /** Delete the last node by freeing its memory **/
        free(node_current->next_node_address_ptr);
        node_to_delete->next_node_address_ptr = NULL;


        ret_val = LINKEDLIST_OP_SUCCESS;
    }
    else
    {
        /** Do nothing **/
        /** Array only has the head node.. No dynamically allocated nodes.
            So, there is nothing to free. **/
    }

    return ret_val;

}

linkedlist_std_ret_t  linkedlist_delete_index(struct node_t* head_node, unsigned short node_index)
{
    linkedlist_std_ret_t ret_val = LINKEDLIST_OP_FAIL;
    struct node_t* node_current = head_node;
    struct node_t* node_to_delete = NULL;

    unsigned short loop_cntr = 0;

    /** Iterating through the linkedlist to reach the required index **/
    while(node_current->next_node_address_ptr!= NULL)
    {
        if(loop_cntr == (node_index-1))
        {
            node_to_delete = node_current->next_node_address_ptr;
            node_current->next_node_address_ptr = node_current->next_node_address_ptr->next_node_address_ptr;
            ret_val = LINKEDLIST_OP_SUCCESS;
            break;
        }

        node_current = node_current->next_node_address_ptr;
        loop_cntr= loop_cntr+1;
    }
    free(node_to_delete);
    node_to_delete = NULL;

    return ret_val;
}



linkedlist_std_ret_t  linkedlist_delete_all(struct node_t* head_node)
{
    linkedlist_std_ret_t ret_val = LINKEDLIST_OP_FAIL;
    struct node_t* node_current = head_node;
    struct node_t  next_node = {0,NULL};
    struct node_t* node_tofree  = NULL;



    if(head_node->next_node_address_ptr !=NULL)
    {
        node_current = head_node->next_node_address_ptr;
        head_node->next_node_address_ptr = NULL;
        while(node_current!= NULL)
        {
            node_tofree = node_current;
            next_node = (*node_current);
            memFree_safe((void **)&node_tofree); /** Safely free that memory **/
            node_current = next_node.next_node_address_ptr;
        }

        ret_val = LINKEDLIST_OP_SUCCESS;
    }
    else
    {
        /** Array only contains the head node, so there are no dynamically allocated nodes to free **/
    }





    return ret_val;

}

/*********************************************************************************************************************
                                  << Private Function Definitions >>
*********************************************************************************************************************/
static void memFree_safe(void** pointer_to_free)
{
    if(*pointer_to_free!= NULL) /**Checking is made so it doesn't re-free a NULL pointer**/
    {
        free(*pointer_to_free);
        *pointer_to_free = NULL; /** Set freed pointer as NULL, so it doesn't become dangling. **/
    }
}

/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/
