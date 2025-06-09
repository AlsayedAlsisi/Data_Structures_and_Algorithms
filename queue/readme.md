# Queue Implementation

A circular buffer implementation of a First-In-First-Out (FIFO) queue in C.

## Features

- Fixed-size circular buffer
- No dynamic memory allocation
- Comprehensive error handling
- 8-bit data elements (`uint8_t`)

## Functions

- `queue_enqueue()` - Add element to rear
- `queue_dequeue()` - Remove element from front
- `queue_peek()` - View front element without removal
- `queue_isEmpty()` - Check if queue is empty
- `queue_isFull()` - Check if queue is full

## Quick Example

```c
#include "queue.h"

#define BUFFER_SIZE 10
static uint8_t buffer[BUFFER_SIZE] = {0};
static queue_t my_queue = {
    .data_buffer = buffer,
    .queue_size = BUFFER_SIZE,
    .front_index = 0,
    .rear_index = 0
};

int main() {
    uint8_t data = 65; // 'A'
    
    // Add data
    queue_enqueue(&my_queue, data);
    
    // Remove data
    queue_dequeue(&my_queue, &data);
    
    return 0;
}
```

## Return Values

- `QUEUE_OPERATION_SUCCESSFUL` - Success
- `QUEUE_IS_EMPTY` / `QUEUE_NOT_EMPTY` - Empty status
- `QUEUE_IS_FULL` / `QUEUE_NOT_FULL` - Full status

## Time Complexity

All operations: **O(1)**