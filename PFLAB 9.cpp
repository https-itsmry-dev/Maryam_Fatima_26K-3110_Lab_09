#include <stdio.h>
int calculateTotal(int *ptr, int size);
int deposit(int balance, int amount);
int withdraw(int balance, int amount);
int processTransaction(int balance, int amount, int (*operation)(int, int));

int main()
{
//variables for TASK 1
	int balance[5] = {15000, 25000, 18000, 32000, 12000};
	int *ptr;
	int customer, newBalance;
//variables for TASK 2
	int transactions[2][3] = {{120000, 150000, 180000}, {200000, 170000, 220000}};
	int (*rowPtr)[3];
	int transactionTotal[2];

// variables for TASK 3 and TASK 4
	int branch1[3] = {15000, 23000, 32000};
	int branch2[4] = {12000, 21000, 27000, 35000};
	int *branches[2]; 
	int sizes[2] = {3, 4};
	int branchTotal[2];
	int total1, total2;

//variables for TASK 5 and TASK 6
	int currentBalance, depositAmount, withdrawAmount;
	int (*operation)(int, int); 
	int i, j;

	printf("This is a program written in C to practise pointers (Bank Management System)");

//TASK 1
	printf("\n\n========== TASK 1: Basic Pointers and Account Balance Management ==========");
	printf("\n\n----- Customer Balances -----");
	for (i = 0; i < 5; i++)
	{
		printf("\nCustomer %d: Rs. %d", i + 1, balance[i]);
	}

	do
	{
		printf("\n\nEnter the customer number (1 to 5): ");
		scanf("%d", &customer);
		if (customer < 1 || customer > 5)
		{
			printf("Invalid Customer Number Entered, please try again");
		}
	} while (customer < 1 || customer > 5);
	printf("\nThe customer number entered by the user is: %d", customer);

	ptr = &balance[customer - 1];

	printf("\n\n----- Before Updating -----");
	printf("\nBalance of Customer %d (using pointer): Rs. %d", customer, *ptr);
	printf("\nMemory address of the balance: %p", (void*)ptr);

	do
	{
		printf("\n\nEnter the new balance: ");
		scanf("%d", &newBalance);
		if (newBalance < 0)
		{
			printf("Invalid Balance Entered, it cannot be negative");
		}
	} while (newBalance < 0);
	printf("\nThe new balance entered by the user is: %d", newBalance);

	*ptr = newBalance; 
	printf("\n\n----- After Updating -----");
	printf("\nBalance of Customer %d (using pointer): Rs. %d", customer, *ptr);
	printf("\nBalance of Customer %d (using array): Rs. %d", customer, balance[customer - 1]);
	printf("\nMemory address of the balance: %p", (void*)ptr);
	if (newBalance == 0)
	{
		printf("\nNote: The account of Customer %d is now empty", customer);
	}
	else if (newBalance < 5000)
	{
		printf("\nNote: The account of Customer %d has a low balance", customer);
	}

	printf("\n\n----- All Balances After Updating -----");
	for (i = 0; i < 5; i++)
	{
		printf("\nCustomer %d: Rs. %d", i + 1, balance[i]);
	}

//TASK 2
	printf("\n\n\n========== TASK 2: Pointer to a 2D Array ==========");
	rowPtr = transactions; 

	for (i = 0; i < 2; i++)
	{
		transactionTotal[i] = 0;
		printf("\n\n----- Branch %d -----", i + 1);
		printf("\nAddress of the row: %p", (void*)(rowPtr + i));
		for (j = 0; j < 3; j++)
		{
			printf("\nMonth %d: Rs. %d", j + 1, *(*(rowPtr + i) + j));
			transactionTotal[i] = transactionTotal[i] + *(*(rowPtr + i) + j);
		}
		printf("\nTotal transactions of Branch %d: Rs. %d", i + 1, transactionTotal[i]);
	}

	if (transactionTotal[0] > transactionTotal[1])
	{
		printf("\n\nBranch 1 has more total transactions");
	}
	else if (transactionTotal[1] > transactionTotal[0])
	{
		printf("\n\nBranch 2 has more total transactions");
	}
	else
	{
		printf("\n\nBoth branches have equal total transactions");
	}
//TASK 3
	printf("\n\n\n========== TASK 3: Array of Pointers ==========");
	branches[0] = branch1;
	branches[1] = branch2;

	for (i = 0; i < 2; i++)
	{
		branchTotal[i] = 0;
		printf("\n\n----- Branch %d -----", i + 1);
		for (j = 0; j < sizes[i]; j++)
		{
			printf("\nCustomer %d: Rs. %d | Address: %p", j + 1, *(branches[i] + j), (void*)(branches[i] + j));
			branchTotal[i] = branchTotal[i] + *(branches[i] + j);
		}
		printf("\nTotal balance of Branch %d: Rs. %d", i + 1, branchTotal[i]);
	}
//TASK 4
	printf("\n\n\n========== TASK 4: Passing an Array to a Function ==========");
	total1 = calculateTotal(branch1, 3);
	total2 = calculateTotal(branch2, 4);
	printf("\n\nTotal balance of Branch 1 (using calculateTotal): Rs. %d", total1);
	printf("\nTotal balance of Branch 2 (using calculateTotal): Rs. %d", total2);

	if (total1 > total2)
	{
		printf("\n\nBranch 1 has the higher total balance");
	}
	else if (total2 > total1)
	{
		printf("\n\nBranch 2 has the higher total balance");
	}
	else
	{
		printf("\n\nBoth branches have the same total balance");
	}

//TASK 5
	printf("\n\n\n========== TASK 5: Function Pointers ==========");
	do
	{
		printf("\n\nEnter the current balance: ");
		scanf("%d", &currentBalance);
		if (currentBalance < 0)
		{
			printf("Invalid Balance Entered, it cannot be negative");
		}
	} while (currentBalance < 0);
	printf("\nThe balance entered by the user is: %d", currentBalance);

	do
	{
		printf("\n\nEnter the amount to deposit: ");
		scanf("%d", &depositAmount);
		if (depositAmount <= 0)
		{
			printf("Invalid Amount Entered, it must be greater than 0");
		}
	} while (depositAmount <= 0);

	operation = deposit;
	currentBalance = operation(currentBalance, depositAmount);
	printf("\nDeposit successful!");
	printf("\nUpdated balance after deposit: Rs. %d", currentBalance);

	do
	{
		printf("\n\nEnter the amount to withdraw: ");
		scanf("%d", &withdrawAmount);
		if (withdrawAmount <= 0)
		{
			printf("Invalid Amount Entered, it must be greater than 0");
		}
	} while (withdrawAmount <= 0);

	if (withdrawAmount > currentBalance)
	{
		printf("\nInsufficient Balance, withdrawal failed");
		printf("\nBalance remains: Rs. %d", currentBalance);
	}
	else
	{
		operation = withdraw;
		currentBalance = operation(currentBalance, withdrawAmount);
		printf("\nWithdrawal successful!");
		printf("\nUpdated balance after withdrawal: Rs. %d", currentBalance);
	}

//TASK 6
	printf("\n\n\n========== TASK 6: Passing Function Pointers as Arguments ==========");
	do
	{
		printf("\n\nEnter the current balance: ");
		scanf("%d", &currentBalance);
		if (currentBalance < 0)
		{
			printf("Invalid Balance Entered, it cannot be negative");
		}
	} while (currentBalance < 0);
	printf("\nThe balance entered by the user is: %d", currentBalance);

	do
	{
		printf("\n\nEnter the amount to deposit: ");
		scanf("%d", &depositAmount);
		if (depositAmount <= 0)
		{
			printf("Invalid Amount Entered, it must be greater than 0");
		}
	} while (depositAmount <= 0);
	currentBalance = processTransaction(currentBalance, depositAmount, deposit);
	printf("\nDeposit successful!");
	printf("\nUpdated balance after deposit: Rs. %d", currentBalance);

	do
	{
		printf("\n\nEnter the amount to withdraw: ");
		scanf("%d", &withdrawAmount);
		if (withdrawAmount <= 0)
		{
			printf("Invalid Amount Entered, it must be greater than 0");
		}
	} while (withdrawAmount <= 0);

	if (withdrawAmount > currentBalance)
	{
		printf("\nInsufficient Balance, withdrawal failed");
		printf("\nBalance remains: Rs. %d", currentBalance);
	}
	else
	{
		currentBalance = processTransaction(currentBalance, withdrawAmount, withdraw);
		printf("\nWithdrawal successful!");
		printf("\nUpdated balance after withdrawal: Rs. %d", currentBalance);
	}
	return 0;
}

int calculateTotal(int *ptr, int size)
{
	int i, total = 0;
	for (i = 0; i < size; i++)
	{
		total = total + *(ptr + i); 
	}
	return total;
}

int deposit(int balance, int amount)
{
	return balance + amount;
}

int withdraw(int balance, int amount)
{
	return balance - amount;
}

int processTransaction(int balance, int amount, int (*operation)(int, int))
{
	int result;
	result = operation(balance, amount); 
	return result;
}
