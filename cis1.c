
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cis1.h"

#define NAMESIZE 128

typedef struct mp3 {
  char *name;
  char *song;
  int year;
  int t;

  struct mp3 *next;
  struct mp3 *prev;
} mp3_t;

//this link always point to first mp3
mp3_t *head = NULL;


//this link always point to last mp3 
mp3_t *last = NULL;

mp3_t *current = NULL;

int insertMP3();
int deleteMP3(char *str);
int printForward();
int printBackward();
bool isEmpty();
void deallocateAll();


int main (int argc, char *argv[]){

    char artist[NAMESIZE];
    int num = 0;
    int d = 1;
    char c;
  
    do{
      
      printf ("\nPlease select a menu item:");
      printf ("\n1. Add an MP3");
      printf ("\n2. Delete an MP3");
      printf ("\n3. Print all MP3s from beginning to end");
      printf ("\n4. Print all MP3s from end to beginning");
      printf ("\n5. Exit");
      printf ("\nPlease enter which option you would like to select: (1-5)");
      scanf("%d%c", &num,&c);

      switch(num){
        case 1:
	        insertMP3();
    	        break;

        case 2:
     	        printf("Please enter the artist you would like to delete:") ;
	        if(fgets(artist,NAMESIZE,stdin)!=NULL){
	            artist[strlen(artist) - 1] = '\0';
	       	    deleteMP3(artist);
	        }
	        break;

        case 3:
   	        printForward();
	        break;

        case 4:
	        printBackward();
                break;

        case 5:
	        deallocateAll();
	        d = 2;
	        break;

        default:
                printf("\nInvalid Entry: 1-5 Only");
	        getchar();
	        break;
                }
   }while(d != 2);
   
   return 0;
}

/* The function isEmpty() checks to see if the head of the list is empty.
	No arguments are taken
	Does not affect anything else
	returns a boolean: False if not NULL; true if NULL    */
bool isEmpty() {
   return head == NULL;
}


/* The function insertMP3() prompts a user for infomation about a song
       (Artist Name, Song title, Year created and Runtime) and adds
        that MP3 data to the end-node of a list of MP3s.
	No arguments are taken
	Allocates memory for MP3 that was inputed by the user
	returns an integer    */
int insertMP3(){
    char n[NAMESIZE],s[NAMESIZE];
    int Newyear, Newtime;
    int len;
    mp3_t *mp3;
    char c;

    //create mp3
    mp3 = (mp3_t *) malloc(sizeof(mp3_t));
  
    printf("\nPlease enter the artist you would like to add:");
    fgets(n,NAMESIZE,stdin);
    printf("\nPlease enter the song you would like to add:");
    fgets(s,NAMESIZE,stdin);

    //artist name
    len = (int) strlen(n);
    n[len - 1] = '\0';   
    mp3->name = (char *) malloc(len);
    strcpy(mp3->name, n);

    //song name
    len = (int) strlen(s);
    s[len - 1] = '\0';   
    mp3->song = (char *) malloc(len);
    strcpy(mp3->song, s);	

    //year
    printf("\nPlease enter the year the song was created:");
    scanf("%d%c", &Newyear,&c);
    mp3->year = Newyear;

    //runtime of song
    printf("\nPlease enter the song duration in seconds:");
    scanf("%d%c", &Newtime,&c);
    mp3->t = Newtime;

    //adds MP3 to tail-end of list
    if(head==NULL){
	mp3->next=mp3->prev=NULL;
	head=last=mp3;
    }else{
         mp3->next=NULL; 
         last->next=mp3; 
         mp3->prev=last; 
         last=mp3; 
    }
    return 0;
}


/* The function deleteMP3(char *str) deletes all MP3s with the same 
        name given by the user and deallocates their memory.
	One argument: a pointer to a character array that holds
		the artist name
	Deallocates memory for MP3s with the given artist name
	returns an integer    */
int deleteMP3(char *str){
     //start from the first mp3
     mp3_t *current = head;
     mp3_t *previous = NULL;

     //if list is empty
     if(head == NULL) {
        return 0;
     }
     do{
         //Search for artist
         if(strcmp(current->name,str) != 0) {
      
                //if it is last mp3	
                if(current->next == NULL) {
                    return 0;
                }else{
                    previous = current;
                    current = current->next;             
                } 
         }else{

                //found a match, update the mp3
   	        if(current == head) {
      	            //change head to point to next mp3
      	            head = head->next;
   	        }else{
                     //bypass the current mp3
                     current->prev->next = current->next;
   	        }  
                if(current == last) {
                     //change last to point to prev mp3
                     last = current->prev;
                }else{
                     current->next->prev = current->prev;
                }
         }
     }while(current->next != NULL);

     free(current->name);
     free(current->song);
     free(current);
     return 0;
}


/* The function printForward() prints the list of MP3s from beginning to end.
	No arguments are taken
	Does not affect anything else
	returns an integer   */
int printForward(){

  //start from the beginning
   mp3_t *ptr = head;
	
   //navigates all items of the list
   printf("\n[ ");
	
   while(ptr != NULL) {        
      printf("Artist: %s \nSong: %s \nYear: %d \nRuntime: %d",ptr->name,ptr->song, ptr->year, ptr->t);
      ptr = ptr->next;
   }
   printf(" ]");

   return 0;
}

/* The function printBackward() prints the list of MP3s from end to beginning.
	No arguments are taken
	Does not affect anything else
	returns an integer   */
int printBackward(){
   //start from the end
   mp3_t *ptr = last;
   
   //navigates all items of the list
   printf("\n[ ");
	
   while(ptr != NULL) {        
      printf("Artist: %s \nSong: %s \nYear: %d \nRuntime: %d",ptr->name,ptr->song, ptr->year, ptr->t);
      ptr = ptr->prev;
      }
   printf(" ]");
   
   return 0;
}


/* The function deallocateAll() deallocates the memory of all MP3s in the list.
	No arguments are taken
	Deallocates memory for all MP3s in the list
	returns nothing    */
void deallocateAll(){

	while(head){
                mp3_t *temp=head;
                head=head->next;
                free(temp->name);
                free(temp->song);
                free(temp);
	}

}