//
//  main.cpp
//  Disk-Scheduling
//
//  Created by Behrouz Barati on 5/17/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Declare global variables, including dynamic array to store sequence of traversed tracks
int *trackSequence = NULL;
int sequenceSize = 0;

/*********************************************************/
void enterParameters(void) {
    // Prompt for the sequence size
    printf("Enter size of sequence: ");
    while (scanf("%d", &sequenceSize) != 1 || sequenceSize <= 0) {
        printf("Invalid input. Please try again: ");
        // Clear the input buffer in case of invalid input
        while (getchar() != '\n');
    }
    // Allocate memory for the sequence of traversed tracks
    trackSequence = (int *)malloc(sequenceSize * sizeof(int));
    return;
} // enterParameters

/*********************************************************/
void calculateDistanceFIFO(void) {
    // Declare local variables
    int startTrack;
    int totalDistance = 0;
    // Prompt for starting track, store in index 0
    printf("Enter starting track: ");
    while (scanf("%d", &startTrack) != 1 || startTrack <= 0) {
        printf("Invalid input. Please try again: ");
        // Clear the input buffer in case of invalid input
        while (getchar() != '\n');
    }
    // Prompt for sequence of tracks to seek, store in index 0 to sequence size - 1
    printf("Enter sequence of tracks to seek: ");
    for (int i = 0; i < sequenceSize; i++){
        while (scanf("%d", &trackSequence[i]) != 1 || trackSequence[i] <= 0) {
            printf("Invalid input. Please try again: ");
            // Clear the input buffer in case of invalid input
            while (getchar() != '\n');
        }
    }
    // Calculate total distance of traversed tracks
    totalDistance = abs(startTrack - trackSequence[0]);
    for (int i = 1; i < sequenceSize; i++)
        totalDistance += abs(trackSequence[i] - trackSequence[i - 1]);
    // Print sequence of traversal
    printf("Traversed sequence from track %d: ", startTrack);
    for (int i = 0; i < sequenceSize; i++)
        printf("%d ", trackSequence[i]);
    printf("\n");
    // Print total distance of tracks traversed
    printf("The distance of the traversed tracks from track %d is: %d\n\n", startTrack, totalDistance);
    return;
} // calculateDistanceFIFO

/*********************************************************/
void calculateDistanceSSTF(void) {
    // Declare local variables
    int startTrack, currentTrack, totalDistance = 0;
    int *visited = (int *)calloc(sequenceSize, sizeof(int));
    // Prompt for starting track, store in index 0
    printf("Enter starting track: ");
    while (scanf("%d", &startTrack) != 1 || startTrack <= 0) {
        printf("Invalid input. Please try again: ");
        // Clear the input buffer in case of invalid input
        while (getchar() != '\n');
    }
    // Prompt for sequence of tracks to seek, store in index 0 to sequence size - 1
    printf("Enter sequence of tracks to seek: ");
    for (int i = 0; i < sequenceSize; i++){
        while (scanf("%d", &trackSequence[i]) != 1 || trackSequence[i] <= 0) {
            printf("Invalid input. Please try again: ");
            // Clear the input buffer in case of invalid input
            while (getchar() != '\n');
        }
    }
    // Initialize current track and distance traversed to starting track
    currentTrack = startTrack;
    // Begin printing sequence of traversal
    printf("Traversed sequence from track %d: ", startTrack);
    // Until every track is traversed
    for (int i = 0; i < sequenceSize; i++) {
        int shortestDistance = INT_MAX;
        int shortestIndex = -1;
        // For each track in sequence
        for (int j = 0; j < sequenceSize; j++) {
            // If not already traversed
            if (!visited[j]) {
                int distance = abs(currentTrack - trackSequence[j]);
                // If distance to traverse is shorter than current shortest distance
                if (distance < shortestDistance) {
                    shortestDistance = distance;
                    shortestIndex = j;
                }
            }
        }
        // Set "done" value for track w/shortest distance to 1 (mark as traversed)
        visited[shortestIndex] = 1;
        // Increment number of tracks that have been traversed
        currentTrack = trackSequence[shortestIndex];
        totalDistance += shortestDistance;
        // Print position
        printf("%d ", currentTrack);
    }
    printf("\n");
    // Print total distance traversed
    printf("The distance of the traversed tracks from track %d is: %d\n\n", startTrack, totalDistance);
    free(visited);
    return;
} // calculateDistanceSSTF

/*********************************************************/
void calculateDistanceScan(void) {
    // Declare local variables
    int startTrack, currentTrack, totalDistance = 0;
    int direction;
    int *visited = (int *)calloc(sequenceSize, sizeof(int));
    // Prompt for starting track, store in index 0
    printf("Enter starting track: ");
    while (scanf("%d", &startTrack) != 1 || startTrack <= 0) {
        printf("Invalid input. Please try again: ");
        // Clear the input buffer in case of invalid input
        while (getchar() != '\n');
    }
    // Prompt for sequence of tracks to seek, store in index 0 to sequence size - 1
    printf("Enter sequence of tracks to seek: ");
    for (int i = 0; i < sequenceSize; i++){
        while (scanf("%d", &trackSequence[i]) != 1 || trackSequence[i] <= 0) {
            printf("Invalid input. Please try again: ");
            // Clear the input buffer in case of invalid input
            while (getchar() != '\n');
        }
    }
    // Prompt for initial direction (0=decreasing, 1=increasing)
    printf("Enter initial direction (0=decreasing, 1=increasing): ");
    while (scanf("%d", &direction) != 1 || direction <= 0) {
        printf("Invalid input. Please try again: ");
        // Clear the input buffer in case of invalid input
        while (getchar() != '\n');
    }
    // Initialize current track and distance traversed to starting track
    currentTrack = startTrack;
    // Begin printing sequence of traversal
    printf("Traversed sequence from track %d: ", startTrack);
    // Until every track is traversed
    int tracksTraversed = 0;
    while (tracksTraversed < sequenceSize) {
        int shortestDistance = INT_MAX;
        int shortestIndex = -1;
        int trackFound = 0;
        // For each track in sequence
        for (int i = 0; i < sequenceSize; i++) {
            // If not already traversed
            if (!visited[i]) {
                int distance = abs(currentTrack - trackSequence[i]);
                // If distance to traverse is shorter than current shortest distance in the current direction
                if ((direction == 1 && trackSequence[i] >= currentTrack) ||
                    (direction == 0 && trackSequence[i] <= currentTrack)) {
                    if (distance < shortestDistance) {
                        shortestDistance = distance;
                        shortestIndex = i;
                        trackFound = 1;
                    }
                }
            }
        }

        // If at least one track was traversed
        if (trackFound) {
            // Set "done" value for track w/shortest distance to 1 (mark as traversed)
            visited[shortestIndex] = 1;
            // Increment number of traversed tracks
            currentTrack = trackSequence[shortestIndex];
            totalDistance += shortestDistance;
            tracksTraversed++;

            // Print position
            printf("%d ", currentTrack);
        } else {
            // Else change direction
            direction = 1 - direction;
        }
    }
    printf("\n");
    // Print total distance traversed
    printf("The distance of the traversed tracks from track %d is: %d\n\n", startTrack, totalDistance);
    free(visited);
    return;
} // calculateDistanceScan

/*********************************************************/
void calculateDistanceCScan(void) {
    // Declare local variables
    int startTrack, currentTrack, totalDistance = 0;
    int *visited = (int *)calloc(sequenceSize, sizeof(int));
    // Prompt for starting track
    printf("Enter starting track: ");
    while (scanf("%d", &startTrack) != 1 || startTrack <= 0) {
        printf("Invalid input. Please try again: ");
        // Clear the input buffer in case of invalid input
        while (getchar() != '\n');
    }
    // Prompt for sequence of tracks to seek
    printf("Enter sequence of tracks to seek: ");
    for (int i = 0; i < sequenceSize; i++) {
        while (scanf("%d", &trackSequence[i]) != 1 || trackSequence[i] <= 0) {
            printf("Invalid input. Please try again: ");
            // Clear the input buffer in case of invalid input
            while (getchar() != '\n');
        }
    }
    // Sort the sequence of tracks
    for (int i = 0; i < sequenceSize - 1; i++) {
        for (int j = 0; j < sequenceSize - i - 1; j++) {
            if (trackSequence[j] > trackSequence[j + 1]) {
                int temp = trackSequence[j];
                trackSequence[j] = trackSequence[j + 1];
                trackSequence[j + 1] = temp;
            }
        }
    }
    // Initialize current track and minimum track
    currentTrack = startTrack;
    int minimumTrack = trackSequence[0];
    // Begin printing sequence of traversal
    printf("Traversed sequence from track %d: ", startTrack);
    // Until every track is traversed
    int tracksTraversed = 0;
    while (tracksTraversed < sequenceSize) {
        // Traverse upwards from current position
        for (int i = 0; i < sequenceSize; i++) {
            if (!visited[i] && trackSequence[i] >= currentTrack) {
                totalDistance += abs(currentTrack - trackSequence[i]);
                currentTrack = trackSequence[i];
                visited[i] = 1;
                tracksTraversed++;
                printf("%d ", currentTrack);
            }
        }
        // If all tracks are not yet traversed, move to the lowest track and continue
        if (tracksTraversed < sequenceSize) {
            totalDistance += abs(currentTrack - minimumTrack); // Move to minimum track
            currentTrack = minimumTrack;
            printf("%d ", currentTrack);
            for (int i = 0; i < sequenceSize; i++) {
                if (!visited[i]) {
                    totalDistance += abs(currentTrack - trackSequence[i]);
                    currentTrack = trackSequence[i];
                    visited[i] = 1;
                    tracksTraversed++;
                    printf("%d ", currentTrack);
                }
            }
        }
    }
    printf("\n");
    // Print total distance traversed
    printf("The distance of the traversed tracks from track %d is: %d\n\n", startTrack, totalDistance);
    free(visited);
    return;
} // calculateDistanceCScan

/***************************************************************/
void quitProgram(void) {
    // If sequence is not NULL, free sequence
    if (trackSequence != NULL) {
        free(trackSequence);
        trackSequence = NULL;
    }
    printf("Quitting program...\n");
    return;
} // quitProgram

/***************************************************************/
int main(void) {
    // Declare local vars
    int choice;
    // While user has not chosen to quit
    while (1) {
        // Print menu of options
        printf("Disk scheduling\n");
        printf("---------------\n");
        printf("1) Enter parameters\n");
        printf("2) Calculate distance to traverse tracks using FIFO\n");
        printf("3) Calculate distance to traverse tracks using SSTF\n");
        printf("4) Calculate distance to traverse tracks using Scan\n");
        printf("5) Calculate distance to traverse tracks using C-Scan\n");
        printf("6) Quit program and free memory\n");
        printf("Enter selection: ");
        scanf("%d", &choice);
        // Call appropriate procedure based on choice--use switch statement or series of if, else if, else statements
        switch (choice) {
            case 1:
                enterParameters();
                break;
            case 2:
                calculateDistanceFIFO();
                break;
            case 3:
                calculateDistanceSSTF();
                break;
            case 4:
                calculateDistanceScan();
                break;
            case 5:
                calculateDistanceCScan();
                break;
            case 6:
                quitProgram();
                return 0; // Indicates success
            default:
                printf("Invalid input. Please try again.\n\n");
        }
    }
    return 1; // Indicates success
} // main
