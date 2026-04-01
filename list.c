// ***
// *** You MUST modify this file
// ***

#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL* buildPaths() {
    PathLL* retval = malloc(sizeof(PathLL));
    retval->head = NULL;
    return retval;
}

// Read the comments in list.h to understand what you need to implement
// for each function.
// Remember to check for memory leak.

void freePaths(PathLL* p) {
    PathNode *curr = p->head;
    while (curr != NULL) {
        PathNode* next = curr->next;
        freeNode(curr);
        curr = next;
    }
    free(p);
}


PathNode* buildNode(char* path) {
    // Allocate a new PathNode with path as its data, return the address.
    PathNode* node = malloc(sizeof(PathNode));
    node->path = malloc((strlen(path) + 1) * sizeof(char)); // +1 for null terminator
    strcpy(node->path, path);
    node->next = NULL;
    return node;
    // WARNING: don't forget to use strcpy to copy path into the new node.
    // Don't just set them equal, otherwise if the input path changes the node
    // will have the wrong path.

    // TODO
}

void freeNode(PathNode* p) {
    free(p->path);
    free(p);

    // Deallocate a pathNode
    // TODO
}

bool addNode(PathLL* paths, char* path) {
    PathNode* newNode = buildNode(path);
    if (paths -> head == NULL || comparePaths(path, paths->head->path) <= 0) {
        newNode->next = paths->head;
        paths->head = newNode;
        return true;
    }

    PathNode* curr = paths->head;
    while (curr->next != NULL && comparePaths(path, curr->next->path) > 0) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    return true;


    // Add a path to the list of paths
    // TODO
}

bool removeNode(PathLL* paths, char* path) {
    PathNode* curr = paths->head;
    // Remove a node from the list with the specified path
    if (curr != NULL && strcmp(curr->path, path) == 0) {
        paths->head = curr->next;
        freeNode(curr);
        return true; // Node removed successfully
        // Found the node to remove
    }
    while (curr != NULL && curr ->next != NULL) {
        if (strcmp(curr->next->path, path) == 0) {
            // Found the node to remove
            PathNode* toRemove = curr->next;
            curr->next = toRemove->next; // Bypass the node to be removed
            freeNode(toRemove);
            return true; // Node removed successfully
        }
        curr = curr->next;
    }

    return false; // Node not found
    // TODO
}

bool containsNode(PathLL* paths, char* path) {
    // Return true if path exists in the list
    PathNode* curr = paths->head;
    while (curr != NULL) {
        if (strcmp(curr->path, path) == 0) {
            return true;
            curr = curr->next;
             // Path found in the list
        }
        //curr = curr->next;
    }
    return false; // Path not found in the list
    // TODO
}

void printPaths(PathLL* paths, FILE* fptr) {
    PathNode* curr = paths->head;
    int i = 0;
    while (curr != NULL) {
        fprintf(fptr, "Path %2d: %s\n", i, curr->path);
        i++;
        curr = curr->next;
    }
}


static int countTurns(char* path) {
    int turns = 0;
    for (int i = 1; path[i] != '\0'; i++) {
        if (path[i] != path[i-1]) turns++;
    }
    return turns;
}

static int comparePaths(char* a, char* b) {
    int lenDiff = (int)strlen(a) - (int)strlen(b);
    if (lenDiff != 0) return lenDiff;

    int turnDiff = countTurns(a) - countTurns(b);
    if (turnDiff != 0) return turnDiff;

    return strcmp(a, b);
}