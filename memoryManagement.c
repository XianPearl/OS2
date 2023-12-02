#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for representing memory partitions
struct MemoryPartition {
    int id;
    int size;
    int allocated;
    struct MemoryPartition* next;
};

// Function to display memory allocation status
void displayMemory(struct MemoryPartition* memory) {
    struct MemoryPartition* curr = memory;
    while (curr != NULL) {
        printf("Partition %d: Size = %d, Allocated = %s\n", curr->id, curr->size, curr->allocated ? "Yes" : "No");
        curr = curr->next;
    }
}

// Function to allocate memory using Best Fit algorithm
void bestFit(struct MemoryPartition* memory, int processId, int processSize) {
    // Implement the Best Fit algorithm here
    // You need to find the best-fit partition to allocate the process
	 struct MemoryPartition* curr = memory;
    struct MemoryPartition* bestFitPartition = NULL;
    int minFragmentation = INT_MAX;

    while (curr != NULL) {
        if (!curr->allocated && curr->size >= processSize) {
            int fragmentation = curr->size - processSize;
            if (fragmentation < minFragmentation) {
                bestFitPartition = curr;
                minFragmentation = fragmentation;
            }
        }
        curr = curr->next;
    }

    if (bestFitPartition != NULL) {
        if (bestFitPartition->size > processSize) {
            // Create a new partition for the remaining memory
            struct MemoryPartition* newPartition = (struct MemoryPartition*)malloc(sizeof(struct MemoryPartition));
            newPartition->id = bestFitPartition->id;
            newPartition->size = bestFitPartition->size - processSize;
            newPartition->allocated = 0;
            newPartition->next = bestFitPartition->next;

            bestFitPartition->size = processSize;
            bestFitPartition->allocated = 1;
            bestFitPartition->next = newPartition;
        } else {
            bestFitPartition->allocated = 1;
        }

        printf("Process %d allocated to Partition %d\n", processId, bestFitPartition->id);
    } else {
        printf("Process %d could not be allocated.\n", processId);
    }
}

// Function to allocate memory using Worst Fit algorithm
void worstFit(struct MemoryPartition* memory, int processId, int processSize) {
    // Implement the Worst Fit algorithm here
    // You need to find the worst-fit partition to allocate the process
	struct MemoryPartition* curr = memory;
    struct MemoryPartition* worstFitPartition = NULL;
    int maxFragmentation = INT_MIN;

    while (curr != NULL) {
        if (!curr->allocated && curr->size >= processSize) {
            int fragmentation = curr->size - processSize;
            if (fragmentation > maxFragmentation) {
                worstFitPartition = curr;
                maxFragmentation = fragmentation;
            }
        }
        curr = curr->next;
    }

    if (worstFitPartition != NULL) {
        if (worstFitPartition->size > processSize) {
            // Create a new partition for the remaining memory
            struct MemoryPartition* newPartition = (struct MemoryPartition*)malloc(sizeof(struct MemoryPartition));
            newPartition->id = worstFitPartition->id;
            newPartition->size = worstFitPartition->size - processSize;
            newPartition->allocated = 0;
            newPartition->next = worstFitPartition->next;

            worstFitPartition->size = processSize;
            worstFitPartition->allocated = 1;
            worstFitPartition->next = newPartition;
        } else {
            worstFitPartition->allocated = 1;
        }

        printf("Process %d allocated to Partition %d\n", processId, worstFitPartition->id);
    } else {
        printf("Process %d could not be allocated.\n", processId);
    }
}

// Function to allocate memory using First Fit algorithm
void firstFit(struct MemoryPartition* memory, int processId, int processSize) {
    // Implement the First Fit algorithm here
    // You need to find the first available partition to allocate the process
	struct MemoryPartition* curr = memory;
    struct MemoryPartition* firstFitPartition = NULL;

    while (curr != NULL) {
        if (!curr->allocated && curr->size >= processSize) {
            firstFitPartition = curr;
            break; // Found the first partition that fits
        }
        curr = curr->next;
    }

    if (firstFitPartition != NULL) {
        if (firstFitPartition->size > processSize) {
            // Create a new partition for the remaining memory
            struct MemoryPartition* newPartition = (struct MemoryPartition*)malloc(sizeof(struct MemoryPartition));
            newPartition->id = firstFitPartition->id;
            newPartition->size = firstFitPartition->size - processSize;
            newPartition->allocated = 0;
            newPartition->next = firstFitPartition->next;

            firstFitPartition->size = processSize;
            firstFitPartition->allocated = 1;
            firstFitPartition->next = newPartition;
        } else {
            firstFitPartition->allocated = 1;
        }

        printf("Process %d allocated to Partition %d\n", processId, firstFitPartition->id);
    } else {
        printf("Process %d could not be allocated.\n", processId);
    }
}

int main() {
    struct MemoryPartition* memory = NULL;

    // Initialize memory partitions (you can add more)
    struct MemoryPartition partition1 = {1, 100, 0, NULL};
    struct MemoryPartition partition2 = {2, 200, 0, NULL};
    struct MemoryPartition partition3 = {3, 50, 0, NULL};

    // Connect partitions to form a linked list
    partition1.next = &partition2;
    partition2.next = &partition3;
    memory = &partition1;

    int choice, processId, processSize;

    do {
        printf("1. Best Fit Allocation\n");
        printf("2. Worst Fit Allocation\n");
        printf("3. First Fit Allocation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process ID and size: ");
                scanf("%d %d", &processId, &processSize);
                bestFit(memory, processId, processSize);
                displayMemory(memory);
                break;
            case 2:
                printf("Enter process ID and size: ");
                scanf("%d %d", &processId, &processSize);
                worstFit(memory, processId, processSize);
                displayMemory(memory);
                break;
            case 3:
                printf("Enter process ID and size: ");
                scanf("%d %d", &processId, &processSize);
                firstFit(memory, processId, processSize);
                displayMemory(memory);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    } while (1);

    return 0;
}
