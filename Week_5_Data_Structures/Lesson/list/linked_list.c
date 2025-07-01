//LINKED LISTS:
//for each element of the list, we have the actual value (e.g. int), as well as a pointer. 

//the pointer points to the next element in the list. This way the elements dont have to be
//right next to each other in memeory

//for the last character, the pointer is 0x0 (nul) so it doesnt point to anythign. 

//now to add a new element we just change the last pointer to point to wherever there is free memory

//note that there is a pointer pointing to the head of the list

//the downside is that we spend additional memory on the pointers themslevs

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h> //for ez get_int

const int LEN = 6;


//lets declare this so we can make linked lists
typedef struct node{
    int number;
    struct node* next;  //we can't jsut say node since compiler reads top to bottom
} node;

int main(void){

    node* list = NULL;

    for (int i = 0; i< LEN; i++){
        //lets add to our linked list

        node* n = malloc(sizeof(node));

        if (n == NULL){
            //TODO: technically i shuould free any memory already used before terminating
            //by traversing the list and freeing as we go (same thing as how we free before the return 1 at the end of this code)
            //but im lazy so hell no im not doing that
            return 1;
        }

        // (*n).number = get_int("Number"); //go to whats in n, then access its number field and set it to 1
        // (*n).next = NULL;

        //the above syntax is a bit unpleasant, so we can use the arrow syntax which is exactly the same

        n->number = get_int("Number: ");

        //INSERTING AT HEAD
        //we have made a new node, lets insert it to the list
        // n->next = list; //set the next of this node to point to whatever is at the start of our list so far. 
        //                 //this means we are adding to the front of the list
        // list = n; //the front of our list should now point to the node we just created;
        //note that because of this, we made it "backwards" (since we add to the front of the list)


        //INSERTING AT TAIL
        //if we don't want it reversed, we'll need to tack on this node to the end of the list
        //this will take O(n), since we have to traverse the list to get to its tail
        //we could make this O(1) by having a pointer that points directly to the tail for us
        // n->next = NULL;

        // if (list == NULL){
        //     list = n;
        // }
        // else{
        //     for (node* ptr = list; ptr != NULL; ptr = ptr->next){
        //         if (ptr->next == NULL){
        //             ptr->next = n;
        //             break;
        //         }
        //     }
        // }


        //SORTING WHILE INSERTING
        //when we have this new node n, lets add into the list such that the list remains sorted
        n->next = NULL;

        //empty list
        if (list == NULL){
            list = n;
        }

        //n goes at start of list
        else if (n->number < list->number){
            n->next = list;
            list = n;
        }
        //in the middle somewhere
        else{
            for (node* ptr = list; ptr != NULL; ptr = ptr->next){
                if (ptr->next == NULL){
                    //ptr is the last element of the list
                    //if we havent found n's spot by now, it should go at the end

                    ptr->next = n;
                    break;
                }
    
                else if (n->number < ptr->next->number){
                    //n should go right after ptr rn
                    n->next = ptr->next;
                    ptr->next = n;
                    break;
                }
            }
        }


    }
    


    //lets print the list by traversing through it

    // node* ptr = list; //ptr will point at the same thing list points at

    // while (ptr != NULL){
    //     printf("%i\n", ptr->number);
    //     ptr = ptr->next;
    // }
    // printf("\n");

    //we can also do this with a for loop
    for (node* ptr = list; ptr != NULL; ptr=ptr->next){
        printf("%i\n", ptr->number);
    }


    //good. But we now have to free our list. we can traverse it again and free it as we go
    node* ptr = list;
    while (ptr != NULL){
        node* next = ptr->next;
        free(ptr);
        ptr = next;
    }

    return 0; //we can return once we free it
}