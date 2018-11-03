#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
FILE *fptr,*fmem,*fborrow;

struct book
{
    char tittle [128];
    char auth[128];
    char publisher[128];
    char isbn[128];
    char date[128];
    int copies; //constant
    int copiesAvailable;
    char category[128];
    int countborrowing;
};

struct address
{
    char building[8];
    char street[24];
    char city[16];
};

struct member
{
    char first[16];
    char last[16];
    int id;
    struct address adr;
    int phoneNumber;
    int age;
    char email[64];
};

struct time
{
    int day;
    int month;
    int year ;
};

struct borrowing
{
    char isbnb[128];
    int idb;
    struct time borrowing;
    struct time dueDate;
    struct time returning;
};
typedef struct book books;
typedef struct member members;
typedef struct borrowing borrow;
borrow brr[100];
books b[100];
members m[100];
int n=0;
int n2=0;
int n_borrow=0;

//Function to count number of lines
int linecount(FILE *pt)
{
    int x=0;
    char c;
    fscanf(pt,"%c",&c);
    while(!feof(pt))
    {
        if(c=='\n')
            x++;
        fscanf(pt,"%c",&c);

    }
    rewind(pt);
    return x;
}

//Function to load book data into array
int loadBooks()
{
    fptr=fopen("Book.txt","r");
    if (fptr!=NULL)
    {
        int x=linecount(fptr);
        while(n!=x)
        {
            fscanf(fptr,"%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,],%d\n",b[n].tittle,b[n].auth,b[n].publisher,b[n].isbn,b[n].date,&b[n].copies,&b[n].copiesAvailable,b[n].category,&b[n].countborrowing);
            n++;
        }
        fclose(fptr);
    }
    else
    {
        printf("FILE IS EMPTY ");
        return 0;
    }
    return n;
}

//Function to load members from file to array
int loadMembers()
{
    fmem=fopen("members.txt","r");

    if(fmem!=NULL)
    {
        int x=linecount(fmem);
        while (n2!=x)
        {
            fscanf(fmem,"%[^,],%[^,],%d,%[^,],%[^,],%[^,],%d,%d,%s",m[n2].first,m[n2].last,&m[n2].id,m[n2].adr.building,m[n2].adr.street,m[n2].adr.city,&m[n2].phoneNumber,&m[n2].age,m[n2].email);
            fscanf(fmem,"\n");
            n2++;
        }
        fclose(fmem);
    }
    else
    {
        printf(" The File Is Empty");
        return 0 ;
    }
    return n2;
}
//Function to load borrowed data from file to array
int loadBorrow()
{
    fborrow=fopen("borrowing.txt","r");
    if(fborrow!=NULL)
    {
        int x=linecount(fborrow);
        while (n_borrow!=x)
        {
            fscanf(fborrow,"%[^,],%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",brr[n_borrow].isbnb,&brr[n_borrow].idb,&brr[n_borrow].borrowing.day,&brr[n_borrow].borrowing.month,&brr[n_borrow].borrowing.year,&brr[n_borrow].dueDate.day,&brr[n_borrow].dueDate.month,&brr[n_borrow].dueDate.year,&brr[n_borrow].returning.day,&brr[n_borrow].returning.month,&brr[n_borrow].returning.year);
            fscanf(fborrow,"\n");
            n_borrow++;
        }
        fclose(fborrow);
    }
    else
        perror("Can't open file");
    return n_borrow;
}
//Function to add a new member
void addMembers ()
{
    int count,id,flag=0;
    fflush(stdin); //to cancel any input entered before
    printf("Please Enter First Name: ");
    gets_without_newline(m[n2].first);
    printf("Please Enter Last Name: ");
    gets_without_newline(m[n2].last);
//check if id already exists
    do
    {flag=0;
        printf("Please Enter Member Id: ");
        scanf("%d",&id);
        for (count=0; count<n2; count++)
        {
            if(id==m[count].id)
            {
                flag=1;
                break;
            }

        }
    }
    while(flag);

    m[n2].id=id;

    fflush(stdin);
    printf("Please Enter building: ");
    gets_without_newline(m[n2].adr.building);
    printf("Please Enter street :");
    gets_without_newline(m[n2].adr.street);
    printf("Please Enter city:");
    gets_without_newline(m[n2].adr.city);
    printf("Please Enter phone number: ");
    scanf("%d",&m[n2].phoneNumber);
    printf("Please Enter age: ");
    scanf("%d",&m[n2].age);
    fflush(stdin);
    printf("Please Enter Email Address: ");
    gets_without_newline(m[n2].email);
    n2++;
}

//Function to save books data into file
void saveBooks()
{
    fptr=fopen("Book.txt","w");
    int i;

    for (i=0; i<n; i++)
    {
        fprintf(fptr,"%s,%s,%s,%s,%s,%d,%d,%s,%d",b[i].tittle,b[i].auth,b[i].publisher,b[i].isbn,b[i].date,b[i].copies,b[i].copiesAvailable,b[i].category,b[i].countborrowing);
        fprintf(fptr,"\n");
    }
    fclose(fptr);
}

//Function to save members data into file
void saveMembers()
{
    fmem=fopen("members.txt","w");
    int i;
    for(i=0; i<n2; i++)
    {
        fprintf(fmem,"%s,%s,%d,%s,%s,%s,%d,%d,%s",m[i].first,m[i].last,m[i].id,m[i].adr.building,m[i].adr.street,m[i].adr.city,m[i].phoneNumber,m[i].age,m[i].email);
        fprintf(fmem,"\n");
    }
    fclose(fmem);

}

//Function to save borrowing data into file

void saveBorrows()
{
    fborrow=fopen("borrowing.txt","w");
    int i;
    for(i=0; i<n_borrow; i++)
    {
        fprintf(fborrow,"%s,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",brr[i].isbnb,brr[i].idb,brr[i].borrowing.day,brr[i].borrowing.month,brr[i].borrowing.year,brr[i].dueDate.day,brr[i].dueDate.month,brr[i].dueDate.year,brr[i].returning.day,brr[i].returning.month,brr[i].returning.year);
        fprintf(fborrow,"\n");
    }
    fclose(fborrow);
}

//Function to add new book into system
void add_new_book()
{

    printf("Book tittle :");
    fflush(stdin);
    gets_without_newline(b[n].tittle);
    printf("Author : ");
    gets_without_newline(b[n].auth);
    printf("Publisher : ");
    gets_without_newline(b[n].publisher);

//check if isbn is repeated
    char isbn[128];
    int i,flag;
    do
    {
        flag=0;
        printf("ISBN : ");
        gets(isbn);
        for(i=0; i<n; i++)
        {
            if(strcmp(b[i].isbn,isbn)==0)
            {
                printf("another one :");
                flag=1;
            }
            else flag=0;
        }
    }
    while(flag);

    strcpy(b[n].isbn,isbn);
    printf("Date of Publishing :");
    gets_without_newline(b[n].date);
    printf("Copies : ");
    scanf("%d",&b[n].copies);
    printf("Copies available: ");
    scanf("%d",&b[n].copiesAvailable);
    fflush(stdin);
    printf("Category : ");
    gets_without_newline(b[n].category);
    n++;
}
//Function to search for book in the array by title
void search_by_tittle()
{
    char search[50];
    books temp[100];
    printf("Please enter book title : ");
    gets(search);
    strlwr(search);
    int i;

    for(i=0; i<n; i++)
    {
        strcpy(temp[i].tittle,b[i].tittle);

        strlwr(temp[i].tittle);
        if(strstr(temp[i].tittle,search))
        {
            printf(" book title:  %s ,author : %s  isbn:  %s category: %s \n",b[i].tittle,b[i].auth,b[i].isbn,b[i].category);
        }
    }
}

//Function to search for book in the array by author
void search_by_author()
{
    char search[50];
    books temp[100];
    printf("Please enter author name : ");
    gets(search);
    strlwr(search);
    int i;

    for(i=0; i<n; i++)
    {
        strcpy(temp[i].auth,b[i].auth);

        strlwr(temp[i].auth);
        if(strstr(temp[i].auth,search))
        {
            printf(" book: title:  %s ,author : %s  isbn:  %s category: %s \n",b[i].tittle,b[i].auth,b[i].isbn,b[i].category);
        }
    }
}

//Function to search for book in the array by category
void search_by_category()
{
    char search[50];
    books temp[100];
    printf("Please enter category  : ");
    gets(search);
    strlwr(search);
    int i;

    for(i=0; i<n; i++)
    {
        strcpy(temp[i].category,b[i].category);

        strlwr(temp[i].category);
        if(strstr(temp[i].category,search))
        {
            printf(" book: title:  %s ,author : %s  isbn:  %s category: %s \n",b[i].tittle,b[i].auth,b[i].isbn,b[i].category);
        }
    }
}

//Function to search for book in the array by isbn
void search_by_isbn()
{
    int index=getIsbn();
    printf(" book: title:  %s ,auth : %s  isbn:  %s category: %s \n",b[index].tittle,b[index].auth,b[index].isbn,b[index].category);
}

//Funcction that controls the search for books in general
void ultimate_search()
{
    int option;
    printf("enter number of the option you desire: \n");
    printf("[1] BY BOOK TITLE\n[2] BY AUTHOR NAME\n[3] BY CATEGORY\n[4] BY ISBN\n");
    scanf("%d",&option);
    fflush(stdin);
    //different options for search
    switch(option)
    {
    case(1) :
        search_by_tittle();
        break;
    case(2) :
        search_by_author();
        break;
    case(3):
        search_by_category();
        break;
    case(4) :
        search_by_isbn();
        break;
    }

}

//function to search for ISBN from books and get its index
int getIsbn()
{
    int i;
    char isbns[20];
    printf("\nPlease enter book isbn : ");
    scanf("%s",isbns);
    for(i=0; i<n; i++)
    {
        int result=strcmp (isbns,b[i].isbn);
        if(result==0)
        {
            break;
        }
    }
    return i;
}

//function to search for ISBN from borrowed books and get its index
int getIsbnb()
{
    int i;
    char isbns[20];
    printf("Please enter isbn of the book : ");
    scanf("%s",isbns);
    for(i=0; i<n_borrow; i++)
    {
        int result=strcmp(isbns,brr[i].isbnb);
        if(result==0)
        {
            break;
        }
    }
    return i;
}

//funtion to change existing number of copies
void changeCopy()
{
    int index=getIsbn();
    int add;
    printf("Enter new number of copies :");
    scanf("%d",&add);
    b[index].copiesAvailable+=add;
    b[index].copies+=add;
}

//function to delete a book from the array of books
void deletebook(int k)
{
    int i=k;
    while(i<(n-1))
    {
        b[i]=b[i+1];
        i++;
    }
    n=n-1;
}

//function to compare today's date with the entered date
int compare_dates(struct time date2)
{
    time_t t;
    t=time(NULL);
    struct tm* tm=localtime(&t);
    if(tm->tm_year+1900>date2.year
       ||tm->tm_year+1900==date2.year&&tm->tm_mon+1>date2.month
       ||tm->tm_year+1900==date2.year&&tm->tm_mon+1==date2.month&&tm->tm_mday>date2.day)
        return 1;
    else
        return -1;
}

//function that controls borrowing
void borrowing()
{
    int j,flag=0;
    int y,i,counter=0;
    time_t t;
    t=time(NULL);
    struct tm*tm=localtime(&t);
    y=getIsbn();
    strcpy(brr[n_borrow].isbnb,b[y].isbn);
    printf("Please enter member ID: ");
    scanf("%d",&brr[n_borrow].idb);
//check if member exists
    for(j=0; j<n2; j++)
    {
        if(brr[n_borrow].idb==m[j].id)
            flag=1;
    }


    if(flag==0)
    {
        printf(" member doesnot exist\n");
    }

    else
    {
//we have to count if the user has already borrowed 3 books
        for(i=0; i<n_borrow; i++)
        {
            if (brr[n_borrow].idb==brr[i].idb)
                counter++;

        }
// if member has already borrowed 3 books he can't borrow others
        if(counter==3||counter>3&&brr[i].returning.day==0)
            printf(" you cannot borrow another book\n");
        else
        {
            if(b[y].copiesAvailable==0)
            {
                printf("No copies available for borrowing from this book\n");

            }
            else
            {
                brr[n_borrow].borrowing.day=tm->tm_mday;
                brr[n_borrow].borrowing.month=tm->tm_mon+1;
                brr[n_borrow].borrowing.year=tm->tm_year+1900;

                b[y].copiesAvailable--;
                b[y].countborrowing++;
                t+=7*24*60*60;
                tm=localtime(&t);

                brr[n_borrow].dueDate.day=tm->tm_mday;
                brr[n_borrow].dueDate.month=tm->tm_mon+1;
                brr[n_borrow].dueDate.year=tm->tm_year+1900;

                brr[n_borrow].returning.day=0;
                brr[n_borrow].returning.month=0;
                brr[n_borrow].returning.year=0;
                n_borrow++;
            }
        }
    }

}

//function to return a books and generates today's date into returning date
void return_book()
{
    int i,j,z;

    time_t t=time(NULL);
    struct tm tm = *localtime(&t);

    z=getIsbnb();
    brr[z].returning.day=tm.tm_mday;
    brr[z].returning.month=tm.tm_mon+1;
    brr[z].returning.year=tm.tm_year+1900;

    int k;
    for(i=0; i<n; i++)
    {
        k=strcmp(brr[z].isbnb,b[i].isbn);
        if(k==0)
            b[i].copiesAvailable++;
    }
}

//function to remove member
void remove_member()
{
    int i,j,k,borrowed=0,search,flag=0;

    printf("Please enter member ID: ");
    scanf("%d",&search);

    for(j=0; j<n_borrow; j++)
    {
        if(search==brr[j].idb)
        {
            if(brr[j].returning.day==0)
            {
                borrowed=1;
                break;
            }
        }
    }
    //check if the member has returned all his books
    if(borrowed==1)
    {
        printf("This member has to return all books first\n");
    }
    else
    {
        for(k=0; k<n2; k++)
        {
            if(search==m[k].id)
                break;
        }

        i=k;
        while(i < (n2-1))
        {
            m[i]=m[i+1];
            i++;
        }

        n2=n2-1;
    }
}

//function to arrange books descending to get the most famous 5 books
void most_famous()
{
    int i,j;
    books x[100];
    books temp[100];
    for(i=0; i<n; i++)
    {
        strcpy(temp[i].tittle,b[i].tittle);
        strcpy(temp[i].auth,b[i].auth);
        strcpy(temp[i].publisher,b[i].publisher);
        temp[i].copies=b[i].copies;
        temp[i].copiesAvailable=b[i].copiesAvailable;
        strcpy(temp[i].category,b[i].category);
        temp[i].countborrowing=b[i].countborrowing;

    }

    for (i=0; i<(n-1); i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            if(b[j].countborrowing<b[j+1].countborrowing)
            {
                temp[j]=b[j];
                b[j]=b[j+1];
                b[j+1]=temp[j];
            }
        }
    }

    printf("most popular books are: \n");

    for(i=0; i<5; i++)
        printf("title:  %s , isbn: %s \n",b[i].tittle,b[i].isbn);


}


//function to get string without adding a new line
void gets_without_newline(char* str)
{
    fgets(str,128,stdin);
    str[strlen(str) - 1] = '\0';
}

//function to control if there are any books that haven't been returned after the due date
void overdue_books()
{
    int i,result;
    for(i=0; i<n_borrow; i++)
    {
        if(brr[i].returning.day==0)
        {
            result=compare_dates(brr[i].dueDate);
            if(result==1)
                printf("BOOK WITH ISBN %s IS OVERDUE \n",brr[i].isbnb);
        }
    }
}

//function to display books in the array
void DisplayBooks()
{
    int i;
    printf("BOOKS: \n");
    for(i=0; i<n; i++)
    {
        printf("%s,%s,%s,%s,%s,%d,%d,%s,%d",b[i].tittle,b[i].auth,b[i].publisher,b[i].isbn,b[i].date,b[i].copies,b[i].copiesAvailable,b[i].category,b[i].countborrowing);
        printf("\n");

    }
}

//function to display members in the array
void DisplayMembers()
{
    int i;
    printf("MEMBERS: \n");
    for(i=0; i<n2; i++)
    {
        printf("%s,%s,%d,%s,%s,%s,%d,%d,%s",m[i].first,m[i].last,m[i].id,m[i].adr.building,m[i].adr.street,m[i].adr.city,m[i].phoneNumber,m[i].age,m[i].email);
        printf("\n");
    }

}

//function to display Borrowing info in the array
void DisplayBorrows()
{
    int i;
    printf("BORROWS: \n");
    for(i=0; i<n_borrow; i++)
    {
        printf("%s,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",brr[i].isbnb,brr[i].idb,brr[i].borrowing.day,brr[i].borrowing.month,brr[i].borrowing.year,brr[i].dueDate.day,brr[i].dueDate.month,brr[i].dueDate.year,brr[i].returning.day,brr[i].returning.month,brr[i].returning.year);
        printf("\n");
    }
}


int main()
{

    loadBooks();
    loadMembers();
    loadBorrow();


    int s;

    //generating menu

    while(1)
    {
        printf("choose an order from this menu: \n");
        printf("_______________________________ \n");
        printf("\n[1] BOOK MANAGEMENT \n");
        printf("[2] MEMBER MANAGEMENT \n");
        printf("[3] BORROW MANAGEMENT \n");
        printf("[4] ADMINISTRATIVE ACTIONS \n");
        printf("[5] DISPLAY BOOKS\n");
        printf("[6] DISPLAY MEMBERS\n");
        printf("[7] DISPLAY BORROWS\n");
        printf("[8] SAVE\n");
        printf("[9] QUIT\n");

        scanf("%d",&s);
        switch(s)
        {
        case(1):
        {

            printf("\n[1] ADD NEW BOOK\n");
            printf("[2] SEARCH FOR A BOOK\n");
            printf("[3] DELETE A BOOK\n");
            printf("[4] ADD NEW COPIES\n");

            int bookOpiton;
            scanf("%d",&bookOpiton);

            switch(bookOpiton)
            {
            case(1):
                printf("operation chosen is number 1: \n");
                add_new_book();
                break;

            case(2):
                printf("operation chosen is number 2: \n");
                ultimate_search();
                break;

            case(3):
                printf("operation chosen is number 3: \n");
                int k=getIsbn();
                deletebook(k);

                break;

            case(4):

                printf("operation chosen is number 4: \n");

                changeCopy();
                break;


            }
            break;
        }
        case(2):
        {
            printf("\n[1] ADD NEW MEMBER\n");
            printf("[2] REMOVE MEMBER\n");
            int memberOption;
            scanf("%d",&memberOption);
            switch(memberOption)
            {
            case(1):
                addMembers();
                break;
            case(2):
                remove_member();
                break;
            }
            break;
        }
        case(3):
        {
            printf("\n[1] BORROW\n");
            printf("[2] RETURN\n");
            int borrowOption;
            scanf("%d",&borrowOption);


            switch(borrowOption)
            {
            case(1):
                borrowing();
                break;
            case(2):
                return_book();
                break;
            }
            break;
        }
        case(4):
        {
            printf("\n[1] OVERDUE BOOKS\n");
            printf("[2] MOST FAMOUS BOOKS\n");
            int adminOption;
            scanf("%d",&adminOption);
            switch(adminOption)
            {
            case(1):
                overdue_books();
                break;
            case(2):
                most_famous();
                break;
            }
            break;
        }
        case(5):
            DisplayBooks();
            break;
        case(6):
            DisplayMembers();
            break;
        case(7):
            DisplayBorrows();
            break;

        case(8):
            saveBooks();
            saveMembers();
            saveBorrows();
            break;

        case(9):
            printf("ALL changes you made will be discarded \n if you exit please make sure you save \n enter 1 to confirm 0 to return \n");
            int x=0;
            scanf("%d",&x);
            if(x==1)
            {
                exit(0);
            }
            break;
        }

    }

    return 0;
}
