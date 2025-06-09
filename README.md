# Data Structures and Algorithms

A comprehensive collection of fundamental data structures and algorithms implemented in C for educational purposes and practical applications.

## Table of Contents

- [Overview](#overview)
- [Data Structures](#data-structures)
  - [Queue](#queue)
  - [Linked List](#linked-list)
- [Getting Started](#getting-started)
- [Usage Examples](#usage-examples)
- [API Reference](#api-reference)
- [Examples](#examples)
- [Contributing](#contributing)
- [Roadmap](#roadmap)
- [License](#license)

## Overview

This repository contains C implementations of essential data structures with a focus on efficiency and low-level programming. Each implementation includes:

- Clean, well-documented C code with comprehensive header files
- Detailed function interfaces with return value checking
- Memory-efficient implementations suitable for embedded systems
- Complete usage examples demonstrating practical applications
- Robust error handling and status reporting

## Data Structures

### Queue

A circular buffer implementation of a First-In-First-Out (FIFO) data structure. Uses a fixed-size buffer with efficient memory usage and no dynamic allocation.

**Key Features:**
- Fixed-size circular buffer implementation
- No dynamic memory allocation
- Comprehensive status checking with enum return values
- Support for 8-bit data elements (`uint8_t`)
- Thread-safe design considerations

**Available Operations:**
- `queue_enqueue()` - Add an item to the rear of the queue
- `queue_dequeue()` - Remove and return the front item
- `queue_peek()` - Return the front item without removing it
- `queue_isEmpty()` - Check if the queue is empty
- `queue_isFull()` - Check if the queue is full

**Return Status Codes:**
- `QUEUE_OPERATION_SUCCESSFUL` - Operation completed successfully
- `QUEUE_IS_EMPTY` - Queue contains no elements
- `QUEUE_NOT_EMPTY` - Queue contains at least one element
- `QUEUE_IS_FULL` - Queue has reached maximum capacity
- `QUEUE_NOT_FULL` - Queue has available space

### Linked List

A singly linked list implementation with dynamic memory allocation, supporting integer data storage and comprehensive node manipulation operations.

**Key Features:**
- Dynamic memory allocation using `malloc()`
- Integer data storage (`int` type)
- Index-based and position-based operations
- Comprehensive node management (insert, delete, retrieve)
- Memory cleanup utilities

**Available Operations:**
- `linkedlist_insert_end()` - Insert a new node at the end of the list
- `linkedlist_insert_index()` - Insert a new node at a specific index
- `linkedlist_get_end()` - Retrieve data from the last node
- `linkedlist_get_index()` - Retrieve data from a node at specific index
- `linkedlist_delete_end()` - Delete the last node
- `linkedlist_delete_index()` - Delete a node at specific index
- `linkedlist_delete_all()` - Delete all nodes and free memory

**Return Status Codes:**
- `LINKEDLIST_OP_SUCCESS` - Operation completed successfully
- `LINKEDLIST_OP_FAIL` - Operation failed (e.g., invalid index, memory allocation failure)

## Getting Started

### Prerequisites

- C compiler (GCC recommended)
- Standard C library support

### Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/data-structures-algorithms.git
cd data-structures-algorithms
```

2. Include the header files in your C project:
```c
#include "queue.h"
#include "linkedlist.h"
```

3. Compile with your project:
```bash
gcc -o your_program your_program.c queue.c linkedlist.c
```

## Usage Examples

### Queue Example

```c
#include "queue.h"

// Define buffer size for LCD display queue
#define LCD_QUEUE_BUFFER_SIZE 21

// Create static buffer array
static uint8_t lcd_queue_buffer_array[LCD_QUEUE_BUFFER_SIZE] = {0};

// Initialize queue structure
static queue_t lcd_queue = {
    .data_buffer = lcd_queue_buffer_array,
    .rear_index = 0, 
    .front_index = 0,
    .queue_size = LCD_QUEUE_BUFFER_SIZE
};

int main() {
    queue_std_return_value_t status;
    uint8_t data_to_send = 65; // ASCII 'A'
    uint8_t received_data;
    
    // Check if queue is empty
    status = queue_isEmpty(&lcd_queue);
    if (status == QUEUE_IS_EMPTY) {
        printf("Queue is initially empty\n");
    }
    
    // Add data to queue
    status = queue_enqueue(&lcd_queue, data_to_send);
    if (status == QUEUE_OPERATION_SUCCESSFUL) {
        printf("Successfully enqueued: %c\n", data_to_send);
    }
    
    // Peek at front element without removing
    status = queue_peek(&lcd_queue, &received_data);
    if (status == QUEUE_OPERATION_SUCCESSFUL) {
        printf("Front element: %c\n", received_data);
    }
    
    // Remove data from queue
    status = queue_dequeue(&lcd_queue, &received_data);
    if (status == QUEUE_OPERATION_SUCCESSFUL) {
        printf("Successfully dequeued: %c\n", received_data);
    }
    
    return 0;
}
```

### Linked List Example

```c
#include "linkedlist.h"

int main() {
    linkedlist_std_ret_t status;
    int retrieved_data;
    
    // Create head node
    struct node_t head_node = {0, NULL};
    head_node.data = 10; // Set initial data
    
    // Insert elements at the end
    status = linkedlist_insert_end(&head_node, 20);
    if (status == LINKEDLIST_OP_SUCCESS) {
        printf("Successfully inserted 20 at end\n");
    }
    
    status = linkedlist_insert_end(&head_node, 30);
    if (status == LINKEDLIST_OP_SUCCESS) {
        printf("Successfully inserted 30 at end\n");
    }
    
    // Insert element at specific index
    status = linkedlist_insert_index(&head_node, 1, 15);
    if (status == LINKEDLIST_OP_SUCCESS) {
        printf("Successfully inserted 15 at index 1\n");
    }
    
    // Retrieve data from specific index
    status = linkedlist_get_index(&head_node, 2, &retrieved_data);
    if (status == LINKEDLIST_OP_SUCCESS) {
        printf("Data at index 2: %d\n", retrieved_data);
    }
    
    // Get data from end
    status = linkedlist_get_end(&head_node, &retrieved_data);
    if (status == LINKEDLIST_OP_SUCCESS) {
        printf("Last element: %d\n", retrieved_data);
    }
    
    // Delete element at index
    status = linkedlist_delete_index(&head_node, 1);
    if (status == LINKEDLIST_OP_SUCCESS) {
        printf("Successfully deleted element at index 1\n");
    }
    
    // Clean up - delete all nodes
    status = linkedlist_delete_all(&head_node);
    if (status == LINKEDLIST_OP_SUCCESS) {
        printf("Successfully deleted all nodes\n");
    }
    
    return 0;
}
```

## API Reference

### Queue Functions

| Function | Parameters | Return Type | Description |
|----------|------------|-------------|-------------|
| `queue_enqueue` | `queue_t* my_queue, uint8_t queue_new_rear_value` | `queue_std_return_value_t` | Adds element to rear of queue |
| `queue_dequeue` | `queue_t* my_queue, uint8_t* queue_front_value` | `queue_std_return_value_t` | Removes element from front of queue |
| `queue_peek` | `queue_t* my_queue, uint8_t* queue_front_value` | `queue_std_return_value_t` | Views front element without removal |
| `queue_isEmpty` | `queue_t* my_queue` | `queue_std_return_value_t` | Checks if queue is empty |
| `queue_isFull` | `queue_t* my_queue` | `queue_std_return_value_t` | Checks if queue is full |

### Linked List Functions

| Function | Parameters | Return Type | Description |
|----------|------------|-------------|-------------|
| `linkedlist_insert_end` | `struct node_t* head_node, int new_data` | `linkedlist_std_ret_t` | Inserts node at end of list |
| `linkedlist_insert_index` | `struct node_t* head_node, unsigned short node_index, int new_data` | `linkedlist_std_ret_t` | Inserts node at specific index |
| `linkedlist_get_end` | `struct node_t* head_node, int* current_data` | `linkedlist_std_ret_t` | Retrieves data from last node |
| `linkedlist_get_index` | `struct node_t* head_node, unsigned short node_index, int* current_data` | `linkedlist_std_ret_t` | Retrieves data from node at index |
| `linkedlist_delete_end` | `struct node_t* head_node` | `linkedlist_std_ret_t` | Deletes last node |
| `linkedlist_delete_index` | `struct node_t* head_node, unsigned short node_index` | `linkedlist_std_ret_t` | Deletes node at specific index |
| `linkedlist_delete_all` | `struct node_t* head_node` | `linkedlist_std_ret_t` | Deletes all nodes in list |

## Examples

The repository includes comprehensive examples demonstrating:
- Queue management for various applications
- Dynamic linked list operations with error handling
- Memory management best practices
- Status code checking and error handling patterns

## Performance Analysis

### Queue
- **Time Complexity:** O(1) for all operations (enqueue, dequeue, peek, isEmpty, isFull)
- **Space Complexity:** O(n) where n is the queue size (fixed at compile time)
- **Memory Usage:** Static allocation, no runtime overhead

### Linked List
- **Time Complexity:** 
  - Insert at end: O(n) - requires traversal to find last node
  - Insert at index: O(n) - requires traversal to target index
  - Delete operations: O(n) - requires traversal
  - Get operations: O(n) - requires traversal
- **Space Complexity:** O(n) where n is the number of nodes
- **Memory Usage:** Dynamic allocation with `malloc()`

## Contributing

Contributions are welcome! Please follow these guidelines:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-data-structure`)
3. Follow the existing code style and documentation format
4. Include comprehensive header documentation
5. Add usage examples for new implementations
6. Test thoroughly, especially error conditions
7. Commit your changes (`git commit -am 'Add new data structure'`)
8. Push to the branch (`git push origin feature/new-data-structure`)
9. Create a Pull Request

### Code Style Guidelines

- Follow existing header file documentation format
- Use descriptive variable names and comprehensive comments
- Include detailed function parameter and return value descriptions
- Provide practical usage examples
- Implement robust error handling with appropriate return codes

## Roadmap

### Planned Data Structures
- [ ] Stack (LIFO implementation)
- [ ] Hash Table with collision handling
- [ ] Doubly Linked List

### Planned Algorithms
- [ ] Sorting Algorithms
- [ ] Search Algorithms

### Planned Features
- [ ] Unit test framework integration
- [ ] Thread-safety implementations

## Testing(Under Construction)

Each data structure implementation should be thoroughly tested:

```bash
# Compile test programs
gcc -o test_queue test_queue.c queue.c
gcc -o test_linkedlist test_linkedlist.c linkedlist.c

# Run tests
./test_queue
./test_linkedlist
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Designed for educational and practical applications
- Optimized for memory-constrained environments
- Built following industry-standard C programming practices
- Comprehensive error handling and status reporting

---

**Note:** This repository focuses on practical, production-ready implementations suitable for both educational purposes and real-world applications. All implementations prioritize reliability, efficiency, and comprehensive error handling.