#include <stdio.h>
#include <stdlib.h>

typedef struct customeracount {
    int accountnumber;
    char name[50];
    char address[100];
    char accountype[20];
    int mobilenumber;
    float balance;
} Account;

void Createaccount(FILE *file);
void Modifyaccount(FILE* file);
void Withdraw(FILE* file,FILE* WithdrawalFile);
void Deposit(FILE* file,FILE* DepositFile);
void Transferamount(FILE* file,FILE* TransferFile);
void ViewallAccounts(FILE *file);
void ViewTotalAmount(FILE* file);
void ViewWithdrawalHistory(FILE* WithdrawalFile);
void DepositHistory(FILE* DepositFile);
void TransferHistory(FILE* TransferFile);
int getLastAccountNumber(FILE* file);

int main() {
    int n;
    char ch;

    FILE* file;
    file = fopen("Customer.bin", "a+b");
    
    FILE* WithdrawalFile;
    WithdrawalFile = fopen("Withdrawals.bin","a+b");
    
    FILE* DepositFile;
    DepositFile = fopen("Deposits.bin","a+b");
    
    FILE* TransferFile;
    TransferFile = fopen("Transfers.bin","a+b");
    
    if (file == NULL || WithdrawalFile == NULL || DepositFile == NULL || TransferFile == NULL)
	{	printf("Error in file opening!\n");
        return 1;	}
	
	
	//menu
    do {
	    printf("\n----- Bank Management System -----\n");
	    printf("1. Create Account\n");
	    printf("2. Modify Account Info\n");
	    printf("3. Withdraw Cash\n");
	    printf("4. Deposit Cash\n");
	    printf("5. Transfer Amount\n");
	    printf("6. View All Accounts\n");
	    printf("7. View Total Amount in Bank\n");
	    printf("8. View Withdrawal History\n");
    	printf("9. View Deposit History\n");
    	printf("10. View Transfer History\n");
    	printf("11. Exit\n");
	    printf("----------------------------------\n");
	    printf("Enter your choice : ");
        scanf("%d", &n);

        switch (n) {
            case 1:
            	Createaccount(file);
                break;
                
            case 2:
                Modifyaccount(file);
                break;
                
            case 3:
            	Withdraw(file,WithdrawalFile);
            	break;
            	
            case 4:
            	Deposit(file,DepositFile);
            	break;
            	
            case 5:
            	Transferamount(file,TransferFile);
            	break;
            	
            case 6:
            	ViewallAccounts(file);
            	break;
            	
            case 7:
            	ViewTotalAmount(file);
            	break;
            	
            case 8:
            	ViewWithdrawalHistory(WithdrawalFile);
            	break;
            
            case 9:
            	DepositHistory(DepositFile);
            	break;
            	
            case 10:
            	TransferHistory(TransferFile);
            	break;
            	
            case 11:
            	break;
            	
            default:
            	printf("Invalid Input!\n");  
        }

        printf("Enter 'Y' or 'y' to continue: ");
        getchar();
        scanf("%c", &ch);
    } while (ch == 'Y' || ch == 'y');

    fclose(file);
    fclose(WithdrawalFile);

    return 0;
}

void Createaccount(FILE *file) {
    Account account;
    fseek(file, 0, SEEK_END);
    
 	int lastaccountnumber=getLastAccountNumber(file);
    account.accountnumber = (lastaccountnumber+1);

    printf("Enter Name: ");
    getchar();
    gets(account.name);
    

    printf("Enter address: ");
    //getchar();
    gets(account.address);

    printf("Enter account type (Current/Saving): ");
    //getchar();
    gets(account.accountype);
	
    printf("Enter mobile number: ");
    scanf("%d", &account.mobilenumber);

    printf("Enter opening balance: ");
    scanf("%f", &account.balance);

    fwrite(&account, sizeof(account), 1, file);
    
    printf("Account created successfully\n");
    printf("Your account number is: %d\n", account.accountnumber);
}

void Modifyaccount(FILE* file)
{
	Account account;
	
	FILE* temp;
	temp=fopen("Temp.bin","wb");
	fseek(file, 0, SEEK_SET);
	
	int accountnum;
	printf("Enter Account number : ");
	scanf("%d",&accountnum);
	
	int check=0;
	
	while(fread(&account,sizeof(account),1,file))
	{
		if(accountnum==account.accountnumber)
		{	check=1;
		
			printf("Enter new name : ");
			getchar();
			gets(account.name);
			
			printf("Enter new address : ");
			getchar();
			gets(account.address);
			
			printf("Enter new mobile number : ");
			scanf("%d",&account.mobilenumber);
			
			fwrite(&account,sizeof(account),1,temp);
		}
		else
		{
			fwrite(&account,sizeof(account),1,temp);
		}
	}
	fclose(file);
	fclose(temp);
	remove("Customer.bin");
	rename("Temp.bin","Customer.bin");
	
	file=fopen("Customer.bin","a+b");
	if(check==1)
	printf("Account information Modified Successfully\n");
	else
	printf("Invalid Account Number!\n");
}

void Withdraw(FILE* file,FILE* WithdrawalFile)
{
	Account account;
	
	int AccountNumber;
	float WithdrawalAmount;
	printf("Enter Account Number : ");
	scanf("%d",&AccountNumber);
	printf("Enter amount : ");
	scanf("%f",&WithdrawalAmount);
	
	FILE* temp;
	temp=fopen("Temp.bin","wb");
	fseek(WithdrawalFile , 0 , SEEK_END);
	fseek(file , 0 , SEEK_SET);
	
	while(fread(&account,sizeof(account),1,file))
	{
		if(account.accountnumber==AccountNumber)
		{	
			if(WithdrawalAmount>account.balance)
			{
				printf("Insufficient Balance!\n");
				fclose(temp);
				remove("Temp.bin");
				return;	
			}
			
			account.accountnumber=AccountNumber;
			account.balance -= WithdrawalAmount;
				
			fwrite(&account,sizeof(account),1,temp);	
			fwrite(&AccountNumber,sizeof(AccountNumber),1,WithdrawalFile);
			fwrite(&WithdrawalAmount,sizeof(WithdrawalAmount),1,WithdrawalFile);				
		}
		else
		{
			fwrite(&account,sizeof(account),1,temp);
		}
	}
	
	fclose(file);
	fclose(temp);
	remove("Customer.bin");
	rename("Temp.bin","Customer.bin");
	
	file=fopen("Customer.bin","a+b");
	
	printf("Cash Withdrawn Successfully\n");

}

void Deposit(FILE* file,FILE* DepositFile)
{
	Account account;
	
	int AccountNumber;
	float DepositAmount;
	printf("Enter Account Number : ");
	scanf("%d",&AccountNumber);
	printf("Enter amount : ");
	scanf("%f",&DepositAmount);
	
	FILE* temp;
	temp=fopen("Temp.bin","wb");
	fseek(DepositFile , 0 , SEEK_END);
	fseek(file , 0 , SEEK_SET);

	
	while(fread(&account,sizeof(account),1,file))
	{
		if(account.accountnumber==AccountNumber)
		{   
			account.accountnumber=AccountNumber;
			account.balance += DepositAmount;
				
			fwrite(&account,sizeof(account),1,temp);	
			fwrite(&AccountNumber,sizeof(AccountNumber),1,DepositFile);
			fwrite(&DepositAmount,sizeof(DepositAmount),1,DepositFile);				
		}
		else
		{
			fwrite(&account,sizeof(account),1,temp);
		}
	}
	
	fclose(file);
	fclose(temp);
	remove("Customer.bin");
	rename("Temp.bin","Customer.bin");
	
	file=fopen("Customer.bin","a+b");
	
	
	printf("Cash Deposited Successfully\n");

}

void Transferamount(FILE* file,FILE* TransferFile)
{
	Account account;
	
	int FromAccountNumber;
	int ToAccountNumber;
	float TransferAmount;
	printf("Enter Account Number to transfer from : ");
	scanf("%d",&FromAccountNumber);
	printf("Enter Account Number to transfer to : ");
	scanf("%d",&ToAccountNumber);
	
	fseek(file , 0 , SEEK_SET);
	
	int fromaccountfound=0,toaccountfound=0;
	
	while(fread(&account,sizeof(account),1,file))
	{
		if(account.accountnumber==FromAccountNumber)
		{	fromaccountfound=1;}
		
		if(account.accountnumber==ToAccountNumber)
		{	toaccountfound=1;}
	}
		
	
	if(fromaccountfound!=1 || toaccountfound!=1) 
	{
        printf("Account not found!\n");
        return;
    }
	
	printf("Enter amount : ");
	scanf("%f",&TransferAmount);
	
	FILE* temp;
	temp=fopen("Temp.bin","wb");
	fseek(TransferFile , 0 , SEEK_END);
	fseek(file , 0 , SEEK_SET);
	
	
	while(fread(&account,sizeof(account),1,file))
	{
		if(account.accountnumber==FromAccountNumber)
		{	
			if(account.balance<TransferAmount)
			{	
				printf("Insufficient Amount!\n");
				fclose(temp);
				remove("Temp.bin");
				return;
			}
			//account.accountnumber=FromAccountNumber;
			account.balance -= TransferAmount;
			fwrite(&account,sizeof(account),1,temp);	
		}
		if(account.accountnumber==ToAccountNumber)
		{	
			//account.accountnumber=ToAccountNumber;
			account.balance += TransferAmount;
			fwrite(&account,sizeof(account),1,temp);	
		}
		else
		{	
		fwrite(&account,sizeof(account),1,temp);
		}
	}
	
	
	fwrite(&FromAccountNumber,sizeof(FromAccountNumber),1,TransferFile);
	fwrite(&ToAccountNumber,sizeof(ToAccountNumber),1,TransferFile);
	fwrite(&TransferAmount,sizeof(TransferAmount),1,TransferFile);
	
	fclose(file);
	fclose(temp);
	remove("Customer.bin");
	rename("Temp.bin","Customer.bin");
	
	file=fopen("Customer.bin","a+b");
	printf("Cash Transferred Successfully\n");
}
		
void ViewallAccounts(FILE *file) 
{
    Account account;
   	
	fseek(file, 0, SEEK_SET);

    while (fread(&account, sizeof(account), 1, file)) {
        printf("Account number: %d\n", account.accountnumber);
        printf("Name: %s\n", account.name);
        printf("Address: %s\n", account.address);
        printf("Account type: %s\n", account.accountype);
        printf("Mobile Number: %d\n", account.mobilenumber);
        printf("Balance: %.2f\n", account.balance);
        printf(" --------- \n");
    }
}

void ViewTotalAmount(FILE* file)
{
	Account account;
	float TotalBalance=0;
	fseek(file , 0 , SEEK_SET);
	while(fread(&account,sizeof(account),1,file))
	{
		TotalBalance += account.balance;
	}
	
	printf("Total Balance in the Bank : %.3f\n",TotalBalance);
}

void ViewWithdrawalHistory(FILE* WithdrawalFile)
{
	int AccountNumber;
	float WithdrawalAmount;
	
	fseek(WithdrawalFile , 0 , SEEK_SET);
	
	printf("\n----- Withdrawal History -----\n");
	while(feof(WithdrawalFile)==0)
	{
		if(fread(&AccountNumber,sizeof(AccountNumber),1,WithdrawalFile))
		{
			printf("Account Number : %d\n",AccountNumber);
		}
		if(fread(&WithdrawalAmount,sizeof(WithdrawalAmount),1,WithdrawalFile))
		{
			printf("Withdrawn Amount : %.2f\n",WithdrawalAmount);
		}
		printf("-------------------------\n");
	}
}

void DepositHistory(FILE* DepositFile)
{
	int AccountNumber;
	float DepositAmount;
	
	fseek(DepositFile , 0 , SEEK_SET);
	
	printf("\n----- Deposit History -----\n");
	while(feof(DepositFile)==0)
	{
		if(fread(&AccountNumber,sizeof(AccountNumber),1,DepositFile))
		{
			printf("Account Number : %d\n",AccountNumber);
		}
		if(fread(&DepositAmount,sizeof(DepositAmount),1,DepositFile))
		{
			printf("Deposited Amount : %.2f\n",DepositAmount);
		}
		printf("-------------------------\n");
	}
}

void TransferHistory(FILE* TransferFile)
{
	int FromAccountNumber;
	int ToAccountNumber;
	float TransferAmount;
	
	fseek(TransferFile , 0 , SEEK_SET);
	
	printf("\n----- Transfer History -----\n");
	while(feof(TransferFile)==0)
	{
		if(fread(&FromAccountNumber,sizeof(FromAccountNumber),1,TransferFile))
		{
			printf("From Account Number : %d\n",FromAccountNumber);
		}
		if(fread(&ToAccountNumber,sizeof(ToAccountNumber),1,TransferFile))
		{
			printf("To Account Number : %d\n",ToAccountNumber);
		}
		if(fread(&TransferAmount,sizeof(TransferAmount),1,TransferFile))
		{
			printf("Transferred Amount : %.2f\n",TransferAmount);
		}
		printf("-------------------------\n");
	}
}

int getLastAccountNumber(FILE* file)
{
	Account account;
	
	int lastaccountnumber=0;
	
	fseek(file, 0 ,SEEK_SET);
	
	while(fread(&account, sizeof(account), 1, file)) {
		if(account.accountnumber>lastaccountnumber)
		{
			lastaccountnumber=account.accountnumber;
		}
	}
	return lastaccountnumber;
}
