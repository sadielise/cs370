//----------------------------------------------------
//CS370 Partial Code for PA1
//Author: Ibrahim Lazrig
//Students: Sadie Henry
//This program maintains the records of a student club by storing them in a file and organizing them in a linked list.
//The program allows the user to add, delete, or view members of the club and sort them according to student fields.
//----------------------------------------------------

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <getopt.h>


#define DEBUG 0

// Defining the records structure for students' Systems Club membership list
typedef struct _StudClub
{
  int Id;
  char fName[20];
  char lName[20];
  char Email[40];
  int yearsAtCSU;
  
  
  struct _StudClub *next;
} StudClub;



//------------------------------------------------------
// Display the menu and return the user choices
char Menu(void)
{
char ch;
do{
printf("\n Main Menu");
printf("\n ------------------");
printf("\n1- Add Student");
printf("\n2- Delete Student");
printf("\n3- List All Members");
printf("\n4- Save data to file & exit");
printf("\n -------------------------------");
printf("\n Enter your choice(1-4):");
ch=getchar();


} while(ch>'4' || ch<'1');
return ch;
}

//------------------------------------------------------
//Function to Add members info to the linked list
//@parameters :
// listHead : Pointer to the head of the list. [Q1: We need a pointer to pointer in this function, Why? Because we are not using a dummy for the
// head of the linked list, so we need to have a pointer to point to the first element. We also may need to change the header of the linked list
// so we need to have a pointer to it.]
// id,fn,ln, gpa, email : Member's id,first name, last name, GPA, and email respectively
// sortIndx : The field number used for sorting the list, 1 is id, 2 is first name, and 3 is last name.
// order: 0 if descending order, 1 if ascending

int AddMember(StudClub **listHead,int id,char *fn,char *ln, int yearsAtCSU, char *email,  int sortIndx, int order)
{
// [Q2: This function has too many value parameters id,fn,ln,... etc. Is there a better way to pass 
//  those values? if Yes, write a prototype for it.]
/*
int AddMember(StudClub **listHead, struct StudClub stud, int sortIndx, int order){
	
	// get student info from the struct that was passed to the function
}

*/
	StudClub *current=*listHead,*prev,*newNode;
	int locFound=0;

// Your code to check if member id already exists
//.......Your code Goes here................
	while (current){
		if(current->Id == id){
			printf("ERROR: A student with the same ID already exists.");
			return 0;
		}
		current = current->next;
	}

// Code to create new node and populate it with data. 
//.......Your code Goes here.................
	newNode = (struct _StudClub *)malloc(sizeof (struct _StudClub));
	newNode->Id = id;
	strcpy(newNode->fName,fn);
	strcpy(newNode->lName,ln);
	strcpy(newNode->Email,email);
	newNode->yearsAtCSU = yearsAtCSU;
	
	/*free(fn);
	free(ln);
	free(email);*/

// Code  to add to an empty list
//.......Your code Goes here.................
	if(listHead == NULL){
	listHead = &newNode;
	}

// code to find the apppropriate position of the new record in the list based on
// the sorting field.
// Hint:  You should keep track of pointers to the previous and next 
// nodes you will use to insert a new record
 	
	else {
		current=*listHead;
		prev=current;
		
//.......Your code Goes here.................
		if(sortIndx == 1){
			while(locFound == 0){
				if(current == NULL){
					locFound = 1;
				}
				// descending
				else if(order == 0){
					if(current->Id > id){
						prev = current;
						current = current->next;
					}
					else{
						locFound = 1;
					}
				}
				// ascending
				else{
					if(current->Id < id){
						prev = current;
						current = current->next;
					}
					else{
						locFound = 1;
					}
				}
			}
		}
					

		if(sortIndx == 2){
			while(locFound == 0){
				if(current == NULL){
					locFound = 1;
				}
				// descending	
				else if(order == 0){
					if(strcasecmp(fn, current->fName) < 0){
						prev = current;
						current = current->next;
					}
					else{
						locFound = 1;
					}
				}
				// ascending
				else{
					if(strcasecmp(fn, current->fName) > 0){
						prev = current;
						current = current->next;
					}
					else{
						locFound = 1;
					}
				}
			}
		}
		
	
		if(sortIndx == 3){
			while(locFound == 0){
				if(current == NULL){
					locFound = 1;
				}
				// descending	
				else if(order == 0){
					if(strcasecmp(ln, current->lName) < 0){
						prev = current;
						current = current->next;
					}
					else{
						locFound = 1;
					}
				}
				// ascending
				else{
					if(strcasecmp(ln, current->lName) > 0){
						prev = current;
						current = current->next;
					}
					else{
						locFound = 1;
					}
				}
			}
		}


	// Now to add the new record : 
	// there are 2 cases:
	// 1- if the record is to be inserted at the beginning of the list
	// 		Hint: you need to change the list header pointer	

	// 2-If not at the beginning, then it would be inserted after some record
	//	   based on the order. 
	//.......Your code Goes here.................
	
		if(*listHead == current){
			*listHead = newNode;
			newNode->next = current;
		}
		else{
			prev->next = newNode;
			newNode->next = current;
		}
	
	}

	return 1;

}
	

//------------------------------------------------------
// Function to read members' info from a file and add them to the
// members linked list sorted based on the sortIndx
// Use the function AddMember
//@ Params:
// fileName : the file to read from. The file contains members info separated by 
//		commas and/or spaces  and each line belongs to a member.
// list: Pointer to the head of the list. [Q3: We need a pointer to pointer in this function, Why? Because we are modifying the
// linked list and we don't have a dummy header. We may need to modify the list header when we add a member, so we need a pointer
// to the list header.] 
// sortIndx : The field number used for sorting the list, 1 is id, 2 is first name, and 3 is last name.
// @Return:
//  1 on success and 0 on failure. 
int readfile (char *fileName, StudClub **list, int sortIndx, int order)
{

  FILE *fd;
  char fn[20],ln[20],email[40];
  int id;
  int years;
  char create;

  if (DEBUG)
    printf ("Entering readfile\n");

  fd = fopen (fileName, "r");
  if (!fd){
  	printf("The file you entered does not exist. Would you like to create it? Y/N\n");	
		create = getchar();
		if(create == 'Y'){
		 	fd = fopen(fileName, "w");
 		}
 		else{
 			return 0;
 		}
	}
	
// loop through the file and read the data
// line by line,  call the AddMember function to add the member to the list	
	
//.......Your code Goes here.................
  char line[500];
	while(fgets(line, 500, fd) != NULL){
	
		if (sscanf(line, "%d,%s %s ,%s ,%d", &id,fn,ln,email,&years) == 0){
			printf("ERROR: Incorrect format in file.");
			return 0;
		}

		AddMember(list, id, fn, ln, years, email, sortIndx, order);
	}
    
 //close the file   
  fclose (fd);
	return 1;
}

//------------------------------------------------------
//function to write data from the list to a text file
// fileName : the file to Write to. Each record of the data is written as separated by commas and/or spaces
//               and each record is written in a seprate line. 

// list: The head of the list pointer. Q4: We didn't use a pointer to pointer in this function, Why? Becuase we're not trying 
// to change the data in the list, just print it. Therefore we can reference the head of the list directly since we just need 
// to get information from it, not modify it.
void writefile (char *fileName, StudClub *list)
{

  FILE *fd;
  StudClub *p=list;
  if (DEBUG)
    printf ("Entering writefile\n");
  fd = fopen (fileName, "w");
 
// loop through THE LINKED list and write the records to the file
// line by line
  
//.......Your code Goes here.................

	while(p != NULL){

		fprintf(fd, "%d,%s %s ,%s ,%d\n", p->Id,p->fName,p->lName,p->Email,p->yearsAtCSU);
		p = p->next;
		
	}
		
  fclose (fd);
  return;

}

// Function to delete a member data from the list using his Id
//@ Params:
//
// Stdlist: Pointer to the head of the members list. [Q5: We need a pointer to pointer in this function, Why? Because we may be deleting the 
// header of the list. Thus, we need a pointer to the header of the list so that we can point to a different pointer if we delete the
// head of the list.]
// id : The Id of the member whose data is to be deleted.
// @Return:
//  1 on sucsses and 0 on failure. 
//------------------------------------------------------

int deleteMember(int id,StudClub **StdList)
{

	StudClub *current=*StdList,*prev;
	
	// [what about deleting from an empty list? Handle appropriately.]	
	//.......Your code Goes here.................
	if(current == NULL){
		printf("ERROR: Cannot delete student from an empty list.");
		return 0;
	}		
		
	// what if the record to be deleted is at the head of the list
	//.......Your code Goes here.................
	if(current->Id == id){
		*StdList = current->next;
		free(current);
		return 1;
	}	
	
	// Not the in the front, OK we need to find it and keep track of
	// the pointers to the previous and next records
	// then delete it if found.

	while(current!=NULL)
	{
		if(current->Id==id)
		{
		 prev->next=current->next;
		 free(current);
		return 1;
		 
		}
	prev=current;
	current=current->next;
	}
	
	
// Not found! OK this means delete wasn't sucssesful. Return 0.
printf("\n Member id not found !");
return 0;
}

//function to free all malloc-ed memory
//@params: Pointer to the header of the list
void deleteAllMembers(StudClub **StdList)
{
	StudClub *current=*StdList;
	StudClub *temp=*StdList;
	while(temp != NULL){
		temp = current->next;
		deleteMember(current->Id, StdList);
		current = temp;	
	}
}
	

//------------------------------------------------------
//function to display members' info
//@params:
// Pointer to the header of the list
void displayMembersList(StudClub *listHead)
{
	StudClub *p=listHead;
	printf("\n%-9s %-20s %-20s %-10s %-40s","MemberId","first Name","last name"," Years@CSU","    E-mail");
	printf("\n------------------------------------------------------------------------------------------------------------------");
	while(p!=NULL){  
		printf("\n%-9d %-20s %-20s %-10d %-40s",p->Id,p->fName,p->lName,p->yearsAtCSU,p->Email);
		p=p->next;
	}

}

//------------------------------------------------------
//Main function:
// parses the command line parameters, defines the header of the list,
// initializes the list with data from the file provided with the command line
// then displays the menu, and calls other functions based
// on user choices.
int main(int argc, char **argv)
{
	char ch;
	char fileName[30];
	int sort=0;
	int c;
	int sortIndx=1;
	StudClub *MembersList=NULL;  // the list header is declared and initialized with NULL
	int id;
	char fn[20],ln[20],email[40];
	int years;

// start parsing the command line parameters

  //int opterr = 0;
  if(argc<2) {
  fprintf (stderr, "Usage: members -f inputfile.txt [-s fileName] [-a] \n");
		return 0;
  }
  while ((c = getopt (argc, argv, "f:s:a")) != -1)
    switch (c){
    
      case 'f':   // the user provided the file and its name should be in the optarg
             // Complete the code to get the file name 
	          // ..............complete this code.....................
				strcpy(fileName, optarg);         
			break;
			
      case 's':  // the user provided the sorting field, we need to check the optarg
      			// and set the sortIndx accordingly
				if (strcmp(optarg,"Id")==0) sortIndx=1;
				else if (strcmp(optarg,"fName")==0)  sortIndx=2;
				else if (strcmp(optarg, "lName")==0)  sortIndx=3; //  ................ complete this if  statement........
				else{
					sortIndx=1;
					printf("\n unknown index field, default (ID) assumed");
				}			
			break;
			
      case 'a':   // the sorting direction (ascending or descending)
                  //is not used in this code, you need to figure out how and where to use it ?
				sort = 1;
			break;
     
      case '?':   //there was an error
				if (optopt == 'f' || optopt == 's' )
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
					fprintf (stderr, "Usage: members -f inputfile.txt [-s fName] [-a] \n");
			return 0;
     
		}

 // now initialize the list with data from the file provided by the user
 // .......... your code goes here..........................
 	
	int read = readfile(fileName, &MembersList, sortIndx, sort);
	if(read == 0){
		return 0;
 	}
 	
	do{

		ch=Menu();

		switch (ch)
			{
			case '1': printf("\n Enter Member info. to add ");
				  printf("\n Id:");
				scanf("%d",&id);
				  printf("\n First name:");
				scanf("%s",fn);
				  printf("\n Last name:");
				scanf("%s",ln);
				  printf("\n years at CSU:");
				scanf("%d",&years);
				printf("\n E-mail:");
				scanf("%s",email);

				 // call the function AddMember with these inputs
				 //......complete the function call.................
				 
				int add = AddMember(&MembersList, id, fn, ln, years, email, sortIndx, sort);
				if(add == 0)
					return 0;			
				break;
				  
			case '2': printf("\n Enter Member Id to delete :");
				scanf("%d",&id);
					// call the function deleteMember with this input id 
				 //......complete the function call.................
				deleteMember(id, &MembersList);
				break;
				
			case '3': 
				displayMembersList(MembersList);
				break;
				
			case '4': 
				writefile (fileName, MembersList);
				deleteAllMembers(&MembersList);
				break;
		 
		}

	} while(ch!='4');

}

