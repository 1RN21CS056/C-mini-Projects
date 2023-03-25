//IMPLIMENTATION OF ATM SIMULATOR BY DHANUSH M AND ESHWAR K
#include<stdio.h>
#include<stdlib.h>
// This struct represents an account with name, account number, balance, and password.
typedef struct Account
{
    char name[20];
    int account_no;
    float balance;
    int password;
} account;

// This struct represents a node in a linked list of accounts.
struct node
{
    account a;
    struct node *link;
};
typedef struct node* NODE;

// This function allocates memory for a new node and returns it.
NODE getnode()
{
    NODE x = (NODE)malloc(sizeof(struct node));
    if(x == NULL)
    {
        printf("Memory is not available.\n");
        exit(0);  
    }
    return x;
}

// This function inserts a new account at the front of the linked list.
NODE insert_front(NODE first, account ele)
{
    NODE temp = getnode();
    temp->a = ele;
    temp->link = first;
    return temp;
}

// This function creates a new account and inserts it at the front of the linked list.
NODE create_account(NODE first)
{
    account a;
    printf("Enter Name: ");
    scanf("%s", a.name);
    printf("Enter Account No: ");
    scanf("%d", &a.account_no);
    printf("create a password:");
    scanf("%d",&a.password);
    printf("Enter Initial Cash to be Deposited: ");
    scanf("%f", &a.balance);
    first = insert_front(first, a);
    printf("Account created successfully!\n");
    return first;
}

// This function writes the accounts in the linked list to a file.
void write_to_file(NODE first)
{
    FILE *fp;
    fp=fopen("accountt.txt","w+");
    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    while(first != NULL)
    {
        fwrite(&first->a, sizeof(account), 1, fp);
        fseek(fp, 0, SEEK_END);
        first = first->link;
    }
    fclose(fp);
}

// This function reads accounts from a file and inserts them at the front of the linked list.
NODE read_from_file(NODE first)
{
    FILE *fp;
    fp=fopen("accountt.txt","r+");
    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return first;
    }
    account a;

    while(fread(&a, sizeof(account), 1, fp) != 0)
    {
        printf("Name: %s\n",a.name);
        printf("Account No: %d\n",a.account_no);
        printf("Balance: %f\n\n",a.balance);
    
    }
    fclose(fp);
    return first;
}

   // This function adds an amount to the balance of an account in the linked list.
   void deposit(NODE first) 
{
    int account_no;
    float amount;
    printf("\nEnter Account Number: ");
    scanf("%d", &account_no);
    NODE cur = first;
    while (cur != NULL) 
    {
        if (cur->a.account_no == account_no) 
        {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);
            cur->a.balance += amount;
            printf("\nAmount deposited successfully!\n");
            write_to_file(first);
            return;
        }
        cur = cur->link;
    }
    printf("\nInvalid account number!\n");
}

//withdrawal from the account 
void withdraw(NODE first) 
{
    int account_no,enteredpassword;
    float amount;
    printf("\nEnter Account Number: ");
    scanf("%d", &account_no);
    NODE cur = first;
    while (cur != NULL) 
    {
        if (cur->a.account_no == account_no) 
        {
             printf("Enter password:");
             scanf("%d",&enteredpassword);
            if(cur->a.password==enteredpassword)
            {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);
            if (amount > cur->a.balance)
            {
                printf("\n---Insufficient balance!---\n");
            }
             else 
            {
                cur->a.balance -= amount;
                printf("\nAmount withdrawn successfully!\n");
                write_to_file(first);
                
            }
            return;
            }
             else
             {
                printf("-------Oops!!-wrong password-------\n");
                return;
             }
        }
         cur = cur->link;
    }
    printf("\nInvalid account number!\n");
}
  
  //checking the balance amount for a particular account
  void checkbalance(NODE first)
{
    int account_no,entered_password;
    printf("Enter account number to check balance:\n");
    scanf("%d",&account_no);
    NODE cur=first;
    while(cur!=NULL)
    {
        if (cur->a.account_no == account_no) 
        {
            printf("Enter password:");
             scanf("%d",&entered_password);
             if(cur->a.password==entered_password)
             {
            printf("account balance:%f\n",cur->a.balance);
            return;
             }
             else
             {
                printf("-------Oops!!-wrong password-------\n");
                return;
             }
        }
        cur=cur->link;

    }
    printf("\n----Oops!!Error!!-Invalid account number!----\n");
}

//to deleting the created account
NODE delete_account(NODE first, int account_no)
{
    NODE prev = NULL, cur = first;
    while (cur != NULL) 
    {
        if (cur->a.account_no == account_no) 
        {
            if (prev == NULL) // if the account to be deleted is the first node
            {
                first = cur->link;
            } 
            else 
            {
                prev->link = cur->link;
            }
            printf("\n------Account deleted successfully!--------\n");
            free(cur);
            write_to_file(first);
            return first;
        }
        prev = cur;
        cur = cur->link;
    }
    printf("\n----Oops!!Error!!-Invalid account number!----\n");
    return first;
}


int main()
{
    NODE first = NULL;
    int account_no;
    int choice;
    while (1) 
    {
        printf("\t***************");
        printf("\n********ATM SIMULATOR********\n");
        printf("1. Add Account into file\n");
        printf("2. Read Account from file\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. check balance\n");
        printf("6. Delete Account\n");
        printf("7. Exit\n");
        printf("**********************\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                first = create_account(first);
                write_to_file(first);
                break;
            case 2:
                read_from_file(first);
                break;
            case 3:
                deposit(first);
                break;
            case 4:
                withdraw(first);
                break;
            case 5:
                checkbalance(first);
                break;
            case 6:
                printf("Enter Account Number to Delete: ");
                scanf("%d", &account_no);
                first = delete_account(first, account_no);
                break;
            case 7:
                printf("\nExiting...\n");
                exit(0);
            default:
                printf("\nInvalid choice!\n");
        }
    }
return 0;
}