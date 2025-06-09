# Linked List Implementation

A singly linked list implementation in C with dynamic memory allocation.

## Features

- Dynamic memory allocation
- Integer data storage
- Index-based operations
- Comprehensive node management

## Functions

- `linkedlist_insert_end()` - Insert at end
- `linkedlist_insert_index()` - Insert at specific index
- `linkedlist_get_end()` - Get data from last node
- `linkedlist_get_index()` - Get data from specific index
- `linkedlist_delete_end()` - Delete last node
- `linkedlist_delete_index()` - Delete node at index
- `linkedlist_delete_all()` - Delete all nodes

## Quick Example

```c
#include "linkedlist.h"

int main() {
    // Create head node
    struct node_t head = {10, NULL};
    
    // Insert data
    linkedlist_insert_end(&head, 20);
    linkedlist_insert_end(&head, 30);
    
    // Get data
    int data;
    linkedlist_get_index(&head, 1, &data);
    printf("Data at index 1: %d\n", data);
    
    // Clean up
    linkedlist_delete_all(&head);
    
    return 0;
}
```

## Return Values

- `LINKEDLIST_OP_SUCCESS` - Operation successful
- `LINKEDLIST_OP_FAIL` - Operation failed

## Project Example

Includes a practical example implementing a dynamic array using the linked list data structure.

## Time Complexity

Most operations: **O(n)** (requires traversal)