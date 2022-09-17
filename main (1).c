#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFERSIZE 128


typedef struct node
{
  char *lastname;
  char *firstname;
  char *status;
  long studentid;
  int grad_yr;

  struct node *next;
  struct node *prev;

} student_obj;
struct node *head = NULL;
struct node *tail = NULL;

// the purpose of this function is to push the created node to the end of the DBLL. it first
// checks whether the current node is empty and if so continues and makes room for the newly
// created room by pushing tail and head one over.
// otherwise the function will place the node to the end (tail). 
// this function takes in student_obj *student for reference
void
push (student_obj * student)
{
  struct node *temp = head;
  if (head == NULL && tail == NULL)
    {
      head = student;
      tail = student;
      student->next = NULL;
      student->prev = NULL;
    }
  else
    {
      temp = tail;
      temp->next = student;
      student->prev = temp;
      tail = student;
    }
  return;
}

// makeNewStudent function is a function which creates new students by allocating memory (presized to 128) for the specified
// char. Takes in all fields, lastname, firstname, status, id, and grad year. And stores it into the DBLL
// using the already created push functions help to designate the location for the newly created student
// node. 
// this function takes in nothing.
student_obj *
makeNewStudent ()
{
  student_obj *student;
  char ln[BUFFERSIZE];
  char fn[BUFFERSIZE];
  char stat[BUFFERSIZE];
  int len;
  printf ("Please enter students last name: ");
  if (fgets (ln, BUFFERSIZE, stdin) != NULL)
    {
      len = (int) strlen (ln);
      ln[len - 1] = '\0';
      student = (student_obj *) malloc (sizeof (student_obj));
      student->lastname = (char *) malloc (len);
      strcpy (student->lastname, ln);
    }
  printf ("Please enter students first name: ");
  if (fgets (fn, BUFFERSIZE, stdin) != NULL)
    {
      len = (int) strlen (fn);
      fn[len - 1] = '\0';
      student->firstname = (char *) malloc (len);
      strcpy (student->firstname, fn);
    }
  printf ("Please enter students status: ");
  if (fgets (stat, BUFFERSIZE, stdin) != NULL)
    {
      len = (int) strlen (stat);
      stat[len - 1] = '\0';
      student->status = (char *) malloc (len);
      strcpy (student->status, stat);
    }
  printf ("Please enter students id: ");
  scanf ("%ld", &(student->studentid));
  printf ("Please enter students graduation year: ");
  scanf ("%d", &(student->grad_yr));
  printf ("Successfully created student!");
  student->next = student->prev = NULL;
  push (student);
  return student;
}

// prints the DBLL from head->tail
// function takes in nothing.
void
printIO ()
{
  struct node *temp = head;
  while (temp != NULL)
    {
      printf ("firstname: %s \n", temp->firstname);
      printf ("lastname: %s \n", temp->lastname);
      printf ("status: %s \n", temp->status);
      printf ("student id: %ld \n", temp->studentid);
      printf ("grad year: %d \n", temp->grad_yr);
      printf ("------------------------------------------\n");
      temp = temp->next;
    }
}

// prints the DBLL from tail->head
// function takes in nothing.
void
printBackwards ()
{
  struct node *temp = tail;
  while (temp != NULL)
    {
      printf ("firstname: %s \n", temp->firstname);
      printf ("lastname: %s \n", temp->lastname);
      printf ("status: %s \n", temp->status);
      printf ("student id: %ld \n", temp->studentid);
      printf ("grad year: %d \n", temp->grad_yr);
      printf ("------------------------------------------\n");
      temp = temp->prev;
    }
}

// freestudentinfo is a helper function to make the code look cleaner, will be used in delete student_obj
// takes in student_obj to identify the node to delete which will be taken in deletestudent
// function takes in nothing. 
void
freestudentinfo (student_obj * student)
{
  free (student->lastname);
  free (student->firstname);
  free (student->status);
}

// deletestudent is a function which deletes a specificed node by strcmpy the input of the user with 
// the created DBLL. It checks whether the node is at the beginning, end or middle of the list (also null)
// and depending on the location redesignates the head or tail to comply with the deletion of the entered 
// node
// function takes in nothing.
void
deletestudent ()
{
  struct node *trav = head;
  char answer[BUFFERSIZE];
  printf ("Please enter the student's last name you wish to delete: ");
  scanf ("%s", answer);
  while (trav)
    {
      if (strcmp (trav->lastname, answer))
	{
	  trav = trav->next;
	}
      break;
    }
  struct node *p = trav;
  if (trav->prev == NULL)
    {
      head = trav->next;
    }
  if (trav->next != NULL)
    {
      trav->next->prev = trav->prev;
    }
  if (trav->prev != NULL)
    {
      trav->prev->next = trav->next;
    }
  freestudentinfo (trav);
  return;
}

//freeDBLL is a simple helper function which will be called in the exit (input 5), in the main. The function
// will be free all the chars and make sure head and tail are null.
// function takes in nothing.
void
freeDBLL ()
{
  struct node *traverse = head;
  while (traverse != NULL)
    {
      struct node *temp = traverse;
      traverse = traverse->next;
      free (temp->lastname);
      free (temp->firstname);
      free (temp->status);
      free (temp);
    }
  head = tail = NULL;
  return;
}

// Main function, takes in all previously created functions and is called depending on the users
// desires. 
// function takes in nothing :)
int
main ()
{
  char input[BUFFERSIZE];
  int marker = 1;
  while (marker == 1)
    {
      printf ("To begin please read the following options\n");
      printf ("------------------------------------------\n");
      printf ("press (1) to add student to list\n");
      printf ("press (2) to delete student from list\n");
      printf ("press (3) to print the list from beginning to end\n");
      printf ("press (4) to print the list from end to beginning\n");
      printf ("press (5) to exit the application\n");
      fgets (input, BUFFERSIZE, stdin);
      if (input[0] == '1')
	{
	  makeNewStudent ();
	}
      if (input[0] == '2')
	{
	  deletestudent ();
	}
      if (input[0] == '3')
	{
	  printf ("Students in order: \n");
	  printf ("-------------------\n");
	  printIO ();
	  printf ("\n");
	  printf ("\n");
	}
      if (input[0] == '4')
	{
	  printf ("Students in reverse order: \n");
	  printf ("---------------------------\n");
	  printBackwards ();
	  printf ("\n");
	  printf ("\n");
	}
      if (input[0] == '5')
	{
	  freeDBLL ();
	  marker = 0;
	    }
    }
  return 0;
}
