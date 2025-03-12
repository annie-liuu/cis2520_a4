/*
Assignment 4
Student Name:   Annie Liu
Student ID:     1266956
Due Date:       November 29th, 2024
Course:         CIS*2520

I have exclusive control over this submission via my password.
By including this header comment, I certify that:
    1) I have read and understood the policy on academic integrity.
    2) I have completed Moodle's module on academic integrity.
    3) I have achieved at least 80% on the academic integrity quiz.
I assert that this work is my own. I have appropriately acknowledged
any and all material that I have used, be it directly quoted or
paraphrased. Furthermore, I certify that this assignment was written
by my in its entirety. 
*/
#include "graph.h"

/*
 * A basic menu based structure has been provided
 */

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    Graph *graph = readGraph(argv[1]);
    if (graph == NULL){
        return 1;
    }
    createAdjacencyList(graph);

    int choice;
    int startVertex = 1;
    do
    {

        // Display the options
        prompt();

        // Get user input
        printf("Enter your choice: ");
        if (scanf("%d", &choice)!=1){
            char garbage[MAX_VERTICES];
            scanf("%s", garbage);
            continue;
        }  // skips while loop if input is not an integer

        /*
         * You will need to add all the cases here.
         * Call the relevant functions in each case.
         * Make sure to handle invalid inputs or edge cases.
         */

        switch (choice) {
            case 1:{ // display adjacency list
                displayAdjacencyList(graph);
                break;
            }
            case 2:{ // perform breadth-first search
                bfs(graph,startVertex);
                break;
            }
            case 3:{ // perform depth first-search
                dfs(graph,startVertex);
                break;
            }
            case 4:{ // find shortest path (Dijkstra's Algorithm)
                dijkstra(graph,startVertex);
                break;
            }
            case 5:{
                freeGraph(graph);
                return 0;
            }
            default:
                printf("Please enter a valid choice.\n");
                break;
        }

    } while (true);

    return 0;
}
