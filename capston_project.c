#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define PENALTY_PER_DAY 5
#define BORROW_PERIOD 7

void start_project();
void verification();
void mainmenu();
void addbook();
void viewbook();
void searchbook();
void deletbook();
void close_project();
void registration();
 void borrowbook();
 void  returnbook();
void panelty();
int calculatePenalty(time_t borrowDate);


struct Bookinfo{
int id;
char name[20];
char author[20];
int quantity;
int borrowed;
time_t borrowDate;
};

struct reg{
    char name[30];
    char profession[30];
    char mail[30];
    char pass[30];
};

struct Bookinfo q;
struct reg e;

FILE *file, *file2,*file4;

int a=1;
int main(){
start_project();
}


void mainmenu(){
system("cls");
int n;
printf("\n\n \t\t****************MAIN MENU****************\n");

printf("\n \t\t 1.add book.\n");
printf("\n \t\t 2.view book list.\n");
printf("\n \t\t 3.search book.\n");
printf("\n \t\t 4.delete book.\n");
printf("\n \t\t 5.borrow book.\n");
printf("\n \t\t 6.return book.\n");
printf("\n \t\t 7.penalty .\n");
printf("\n \t\t 8.exit.\n");

printf("\t\t******************************\n");
printf("Enter your choice:");
scanf("%d",&n);
if(n==1){
    addbook();
}
    else if(n==2){
       viewbook();
    }
    else if(n==3){
       searchbook();
    }
    else if(n==4){
        deletbook();
    }
    else if(n==5){
        borrowbook();
   }
    else if(n==6){
        returnbook();
    }
    else if(n==7){
        panelty();
    }

     else if(n==8){
        close_project();
    }
    else{
    printf("your choice is wrong!\n Try again....\n");
}

fflush(stdin);
getchar();

mainmenu();
}

void addbook(){
    system("cls");
    int d,count = 0;
printf("\n \t\t******************ADD BOOK******************\n");
file = fopen("Add_newbook.txt","ab+");

printf("\t\t Enter ID: ");
fflush(stdin);
scanf("%d",&d);
rewind(file);
while(fread(&q,sizeof(q),1,file)== 1){
    if(d == q.id){
    printf("\n\n\t\t \033[1;31mThis ID no book is already in library....\n\033[0m");
    count=1;
    }
}
if(count == 1){
        fflush(stdin);
    getchar();
mainmenu();
}
q.id = d;

printf("\n\t\t Enter name: ");
fflush(stdin);
scanf("%s",q.name);

printf("\n\t\t Enter author: ");
fflush(stdin);
scanf("%s",q.author);

printf("\n\t\t Enter Quantity: ");
fflush(stdin);
scanf("%d",&q.quantity);
q.borrowed=0;

fseek(file,0,SEEK_END);
fwrite(&q,sizeof(q),1,file);

//fprintf(file, "%d %s %s %d\n",q.id, q.name, q.author, q.quantity);
fclose(file);
printf("\n\t\t The book is added succesfully!");

fflush(stdin);
    getchar();

    mainmenu();
}

void viewbook(){
   int count = 0;
system("cls");
printf("\n\n\t\t**************View Book List**************\n");
printf("\n\n\tId\t Name\tAuthor\tQuantity");
file = fopen("Add_newbook.txt","r");

while(fread(&q, sizeof(q), 1, file) == 1){
    printf("\n\t%d\t%s\t%s\t%d\t%d\n",q.id,q.name,q.author,q.quantity,q.borrowed);

     count = count+q.quantity;
}
printf("\n\t\tTotal book's in library: %d\n",count);
printf("\tPlease press enter.....\n");
fflush(stdin);
getchar();
mainmenu();
}

void searchbook(){
    int r,count = 0;


system("cls");
printf("\n\n\t\t ***************Search Book***************\n");
printf("\n\\t\tSearching...\n");
//printf("\n\n\t\tId\tName\tAuthor\tQuantity\n");

file = fopen("Add_newbook.txt","r");

printf("\n\t\t Enter Id : ");

scanf("%d",&r);

while(fread(&q,sizeof(q),1,file) == 1){
    if(r == q.id){
            printf("\n\t\tThe Book is found!\n");
            printf("\t\tID:%d",q.id);
            printf("\n\t\tName:%s",q.name);
            printf("\n\t\tAuthor:%s",q.author);
            printf("\n\t\tQuantity:%d",q.quantity);

            count = 1;

}
}
if(count == 0){
    printf("\n\n\t\t\033[1;31m Book is not found!\033[0m");
}
printf("\n\t\tPlease press enter...");
fflush(stdin);
getchar();
mainmenu();
}

void deletbook(){
    int z,count=0;

system("cls");
printf("\n\n\t\t***************** Delete Book From Library *****************\n");
printf("Enter Id for delete book : ");
scanf("%d",&z);

file = fopen("Add_newbook.txt","r");
rewind(file);
while(fread(&q, sizeof(q), 1 ,file) == 1){

    if(z == q.id){
        printf("\n\t\tBook is available!");
        printf("\n\t\tBook name : %s",q.name);
       count = 1;
    }
}
if(count == 0){
    printf("\n\t\tBook is not available!");
}
else{
    file2 = fopen("delete.txt","wb");
    rewind(file);
    while(fread(&q , sizeof(q),1 , file) == 1){
          if(z != q.id){
              fseek(file2, ftell(file2)-sizeof(q),0);
            fwrite(&q , sizeof(q) , 1, file2);
          }
          }
          fclose(file);
          fclose(file2);

          remove("Add_newbook.txt");

          rename("delete.txt","Add_newbook.txt");

          file = fopen("Add_newbook","r");
          fclose(file);
}
printf("\n\n\t\tPlease press enter...");
fflush(stdin);
getchar();
mainmenu();
}

void borrowbook() {
    int id, found = 0;

    printf("\n\n\t\t*************** Borrow Book ***************\n");
    file = fopen("Add_newbook.txt", "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("\t\t Enter Book ID to Borrow: ");
    scanf("%d", &id);

    while (fread(&q, sizeof(q), 1, file) == 1) {
        if (q.id == id && q.quantity > q.borrowed) {
                q.borrowDate = time(NULL);
            q.borrowed++;
            fseek(file, -sizeof(q), SEEK_CUR);
            fwrite(&q, sizeof(q), 1, file);
            printf("\n\t\t\033[1;32mBook borrowed successfully!\033[0m\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n\t\t\033[1;31mBook not available or out of stock.\033[0m\n");
    }

    fclose(file);
}

void returnbook() {
    int id, found = 0;

    printf("\n\n\t\t*************** Return Book ***************\n");
    file = fopen("Add_newbook.txt", "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("\t\t Enter Book ID to Return: ");
    scanf("%d", &id);

    while (fread(&q, sizeof(q), 1, file) == 1) {
        if (q.id == id && q.borrowed > 0) {
            int penalty = calculatePenalty(q.borrowDate);
            q.borrowed--;
            fseek(file, -sizeof(q), SEEK_CUR);
            fwrite(&q, sizeof(q), 1, file);

            printf("\n\t\t\033[1;32mBook returned successfully!\033[0m\n");
            if (penalty > 0) {
                printf("\t\tPenalty for late return: %d taka\n", penalty);
            } else {
                printf("\t\tNo penalty applied.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n\t\t\033[1;31mInvalid Book ID or no borrowed copies to return.\033[0m\n");
    }
    fclose(file);
}


int calculatePenalty(time_t borrowDate) {
    time_t now = time(NULL);
    int daysBorrowed = (now - borrowDate) / (24 * 60 * 60);
    if (daysBorrowed > BORROW_PERIOD) {
        return (daysBorrowed - BORROW_PERIOD) * PENALTY_PER_DAY;
    }
    return 0;
}

void panelty() {
    printf("\n\n\t\t*************** Penalty Rules ***************\n");
    printf("\t\t Borrowing Period: %d days\n", BORROW_PERIOD);
    printf("\t\t Penalty Per Day After Period: %d units\n", PENALTY_PER_DAY);
    printf("\n\t\t*********************************************\n");
    printf("\n\t\tPress Enter to return to the main menu...");
    fflush(stdin);
    getchar();
    mainmenu();
}

void close_project(){
system("cls");
printf("\n\n\t\tThis is our library management projet\n");
printf("\n\n\t\t Thank You for visiting this library management project!\n");

printf("\n\n\t\tPlease press enter...\n");

fflush(stdin);
getchar();

exit(0);

}


void verification(){
file4 = fopen("registration_process.txt","r");
if (file4 == NULL) {
        printf("\033[1;31mError: Unable to open file.\033[0m\n");
        exit(1);
    }
rewind(file4);
while(fread(&e,sizeof(e),1,file4)== 1){
  char mail1[30];
  char pwd1[15];
  printf("\n\t\t Enter Your Mail:") ;
  scanf("%s",mail1);
  printf("\n\t\t Enter Your Passwoed:") ;
  scanf("%s",pwd1);
  if(strcmp(e.pass,pwd1)==0&&strcmp(e.mail,mail1)==0){
    printf("Match Password and mail!\n");
    printf("Login Successfully\n");
printf("Press any key...\n");
fclose(file4);
  }
  else{
    if(a==3){
        exit(0);
    }
    printf("\033[1;31mWrong password %d to 3\n",a);
    printf("Try again\n\033[0m");
    a++;
    fflush(stdin);
    getchar();

    verification();
  }
  fflush(stdin);
  getchar();

  mainmenu();
}
}


start_project(){
    system("cls");
printf("\n\n\t\t\t\t********************LIBRARY MANAGEMENT PROJECT********************\n");
int t;
printf("\n\t\t 1. Registration.\n");
printf("\n\t\t 2. Login.\n");
printf("\n\t\t 3. Exit.\n");
printf("\n\t\tEnter Your Choise:");
scanf("%d",&t);
if(t==1){
    registration();
}
else if(t==2){
    verification();
}
else if(t==3){
    exit(0);}
else{
    printf("\n\t\t Your Choise id Wrong..\n");
}
printf("\n\t\tPlease press enter\n");
fflush(stdin);
getchar();
start_project();
}


void registration(){
    char s[30];


printf("\n \t\t******************Registration******************\n");
file4 = fopen("registration_process.txt","a+");

if(!file4){
    printf("Error opening file!\n");
    return;
}
printf("\t\t Enter mail: ");
fflush(stdin);
scanf("%s",s);
rewind(file4);
while(fread(&e,sizeof(e),1,file4) == 1){
    if(strcmp(e.mail,s)==0){
    printf("\n\n\t\t \033[1;31mThis mail  is already used....\n\033[0m");
   fclose(file4);
    return;


}
}

strcpy(e.mail , s);
printf("\t\t Enter Name: ");
fflush(stdin);
scanf("%s",e.name);

printf("\t\t Enter profession: ");
fflush(stdin);
scanf("%s",e.profession);

printf("\t\t Enter Pass: ");
fflush(stdin);
scanf("%s",e.pass);

fseek(file4,0,SEEK_END);
fwrite(&e,sizeof(e),1,file4);

fclose(file4);
printf("\n\t\t The registration process is done succesfully!");


}


