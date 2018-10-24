/*Hello, Im Caghan Koksal,This program designed to create 3 linkedlist and 1 one of them Transaction LinkedList contains header of 2 other LinkedList.One of them stores incomming balance other stores outgoing balance.
This program intented to create transactions by user and  calculating remaining money of users.Transactions used for money transfer between accounts.
 for contact:caghankoksal@sabanciuniv.edu
*/
/
#include<iostream>
#include"linkedList.h"
#include<fstream>
#include<sstream>
using namespace std;

//PROTOTYPES FOR SAFETY
int hashfun(transactionNode *newT, int prev_hval, int PoW);
int mine(transactionNode *newT, transactionNode* bchain, int& hval, int& PoW, int threshold);
void printRemainingMoney(transactionNode*blockchain, string user);
void AddToLast_ofOUtputList(transactionNode*&AddedNode, double balance);
int LastElementDeleter_Ýnput(inputNode*head);
int LastElementDeleter(outputNode*head);
transactionNode* InsertLast(transactionNode*&blockchain, transactionNode*&NewAddedNode);
void printBlockchain(transactionNode*blockchain);
void AddTransaction(transactionNode*blockchain);






int hashfun(transactionNode *newT, int prev_hval, int PoW)// Taken from HW Task
{
	int hval = (prev_hval + 1111) * (PoW + 1111);

	outputNode * outPtr = newT->outputList;

	while (outPtr) {

		hval += outPtr->amount;
		string str = outPtr->sendTo;

		for (int i = 0; i < str.length(); i++) {

			hval += ((int)str[i]);
		}

		outPtr = outPtr->nextO;

	}

	inputNode * inPtr = newT->inputList;

	while (inPtr)
	{
		hval += inPtr->transactionId;

		hval += inPtr->outputLocation;

		inPtr = inPtr->nextI;

	}
	return (hval % 137);

}

int mine(transactionNode *newT, transactionNode* bchain, int& hval, int& PoW, int threshold)// Taken from HW Task
{
	transactionNode* tmp = bchain;

	int prev_hval = 0;

	while (tmp) {

		prev_hval = tmp->hval;
		tmp = tmp->nextT;

	}

	PoW = 1;

	while ((hval = hashfun(newT, prev_hval, PoW)) >= threshold)
	{

		cout << "Trying to find a hash value..." << "hash: " << hval << " PoW: " << PoW << endl;

		PoW++;

	}
	return PoW;

}

void printRemainingMoney(transactionNode*blockchain, string user)// intented to Print Remaining Money of User
{
	double expenses = 0;// expenses of User
	double income = 0;// income
	transactionNode*ptr = blockchain;// head pointer

	transactionNode*ptr2 = blockchain;//Also head pointer
	outputNode*income_calculator;// For calculating output's which are income

	outputNode* expense_calculator;// For calculating output's which are expense

	cout << "Write the name you want to search";// taken name from user
	cin >> user;



	while (ptr != NULL)
	{
		if (ptr->owner == user)// the situation transaction own to Searched person
		{
			expense_calculator = ptr->outputList;//expenses calculator shows transactions outputs

			while (expense_calculator != NULL)
			{
				if (ptr->owner == user)
				{
									
					expenses += expense_calculator->amount;//
				}
				if (expense_calculator->nextO != NULL)
					expense_calculator = expense_calculator->nextO;
				else
				{
					break;
				}
			}

		}
		if (ptr->nextT != NULL)
		{
			ptr = ptr->nextT;
		}

		else if (ptr->nextT == NULL)
		{
			break;
		}

	}

	while (ptr2 != NULL)
	{

		income_calculator = ptr2->outputList;
		while (income_calculator != NULL)
		{
			//KENDÝNDEN KENDÝNE YOLLAYAN PARAYI ALMIYOR OLABÝLÝR
			if (income_calculator->sendTo == user)
			{
				income += income_calculator->amount;// stores incomes
				income_calculator = income_calculator->nextO;//goes next node
			}
			else
			{
				income_calculator = income_calculator->nextO;//goes next node
			}

		}
		ptr2 = ptr2->nextT;
		
		
	}

	cout <<user<<"'s wallet :" <<income - expenses;
}

void AddToLast_ofOUtputList(transactionNode*&AddedNode, double balance)// To Send back the money which are not used by user

{
	outputNode*ReturnBalance = new outputNode;//last output node which will go back to transaction's owner

	outputNode*ReturnTemp = AddedNode->outputList;//
	outputNode*ReturnTemp2 = AddedNode->outputList;

	ReturnBalance->amount = balance;//remaing money attained to Return Balance's amount
	ReturnBalance->sendTo = AddedNode->owner;


	if (AddedNode->outputList == NULL)
	{
		AddedNode->outputList = ReturnBalance;


	}
	else
	{
		while (ReturnTemp != NULL)
		{
			ReturnTemp2 = ReturnTemp;//to store the tail
			ReturnTemp = ReturnTemp->nextO;


		}
		ReturnTemp2->nextO= ReturnBalance;
		ReturnBalance->nextO = NULL;

	}

}



int LastElementDeleter_Ýnput(inputNode*head)// One of my reading algorithm creates node but does not fill this .Because of these nodes are redundant
//I wrote these function to delete these redundant nodes


{
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		inputNode*temp;
		inputNode*temp2;
		temp = head;
		while (temp->nextI->nextI != NULL)// to find the 2 nodes before nulll
		{
			temp = temp->nextI;
		}
		temp2 = temp->nextI;
		temp->nextI = NULL;
		free(temp2);
	}
	return 0;



}

int LastElementDeleter(outputNode*head)//THe same reason with upside
{
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		outputNode*temp;
		outputNode*temp2;
		temp = head;
		while (temp->nextO->nextO != NULL)
		{
			temp = temp->nextO;
		}
		temp2 = temp->nextO;
		temp->nextO = NULL;
		free(temp2);
	}
	return 0;
}

transactionNode* InsertLast(transactionNode*&blockchain, transactionNode*&NewAddedNode)//To Add New Transaction Node to the end of  Transaction Node input
{
	transactionNode*temp = blockchain;
	transactionNode*ptr = blockchain;
	if (blockchain == NULL)
	{

		blockchain = NewAddedNode;
		return NewAddedNode;
	}
	else
	{

		while (temp != NULL)
		{
			ptr = temp;
			temp = temp->nextT;
		}
		ptr->nextT = NewAddedNode;
		NewAddedNode->nextT = nullptr;
		



	}
}

void printBlockchain(transactionNode*blockchain)//TO Print All blockchain

{

	transactionNode*T_Touring = blockchain;// second key for head pointer of TRANSACTÝON NODE;

	outputNode*reader;
	inputNode*i_reader;


	while (T_Touring != NULL)
	{
		i_reader = T_Touring->inputList;//ÝnputList pointer
		reader = T_Touring->outputList;//OutputList Pointer

		cout << "Transaction id:" << T_Touring->tid<<" ";
		cout << "owner:" << T_Touring->owner<<" " ;
		cout << "hash:" << T_Touring->hval<<" ";
		cout << "PoW:" << T_Touring->PoW << endl;
		cout << "InputList" << endl;

		while (i_reader != NULL)
		{
			cout << "Tid :" << i_reader->transactionId;
			cout << "Location :" << i_reader->outputLocation;
			cout << endl;

			if (i_reader->nextI != NULL)
				i_reader = i_reader->nextI;
			else
			{
				break;
			}
		}

		cout << "OutputList" << endl;
		while (reader != NULL)
		{

			cout << "Amount :" << reader->amount << " ";
			cout << "Send To :" << reader->sendTo;
			cout << endl;
			if (reader->nextO != NULL)
				reader = reader->nextO; // to move around outputList LinkedList;
			else
				break;

		}
		
		T_Touring = T_Touring->nextT;// To move around LinkedList of Transaction node;
	}
}


void AddTransaction(transactionNode*blockchain)
{

	string k;
	string readen_first = "";
	string storage_first = "";
	string owner_newTransaction;//to take owner's name

	////////////////////////////////////////////
	transactionNode*add_Node = new transactionNode;

	//////////////////////////////////////


	cout << "Input the owner of the transaction :" << endl;
	//cin >> owner_newTransaction;
	cin.ignore();
	getline(cin, owner_newTransaction);
	//owner_newTransaction=owner_newTransaction.substr(0,)
	//cin >> owner_newTransaction;
	
	add_Node->owner =owner_newTransaction;

	cout << "Write the input list in form of" << endl;
	cout << "'transactionId_1 outLocation_1 transactionId_2 outLocation_2#'" << endl;
	cout<<"put # after all the inputs finish:" << endl;


	do
	{
		//cin.ignore();
		getline(cin, k);
		storage_first += k;
	} while (k.at(k.length() - 1) != '#');

	istringstream parser(storage_first);
	int i_counter = 0;


	inputNode*i_pointer = new inputNode;
	add_Node->inputList = i_pointer;


	while (readen_first != "#")//When readen is not #
	{

		inputNode*temp = new inputNode;
		i_pointer->nextI = temp;
		temp->nextI = NULL;



		for (int k = 0; k < 2; k++)
		{

			parser >> readen_first;//parser reads data

			if ((i_counter % 2 == 0) && ('0' <= (readen_first.at(0))) && ((readen_first.at(0) <= '9')))// since we took 2 data in row to understand is it first data or second ý used modulus
			{
				i_counter++;
				i_pointer->transactionId = stoi(readen_first);//if its first data of 2 data its transaction id 

			}
			else if ((i_counter % 2 == 1) && ('0' <= (readen_first.at(0))) && ((readen_first.at(0) <= '9')))// since we took 2 data in row to understand is it first data or second ý used modulus
			{
				i_counter++;
				i_pointer->outputLocation = stoi(readen_first);// second read data is output location
			}
		}
		i_pointer = temp;
	}

	LastElementDeleter_Ýnput(add_Node->inputList); // evertime upper codes creates last 2 nodes empty
	LastElementDeleter_Ýnput(add_Node->inputList);

	//we filled input List

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "Write the outputList in the form of  'amount_1 sentTo_1 amont_2 sendTo_2#'" << endl;


	string readen2 = "";
	string p;
	string storage_second = "";

	int o_counter = 0;

	do
	{
		getline(cin, p);
		storage_second += p;
	} while (p.at(p.length() - 1) != '#');// when last element is not #



	istringstream parser2(storage_second);
	outputNode*o_pointer = new outputNode;
	add_Node->outputList = o_pointer;

	while (readen2 != "#")
	{

		outputNode*temp2 = new outputNode;
		o_pointer->nextO = temp2;
		temp2->nextO = NULL;



		for (int k = 0; k < 2; k++)// to read 2 by 2 
		{

			parser2 >> readen2;


			if ((o_counter % 2 == 0) && (('0' <= (readen2.at(0)) && (readen2.at(0) <= '9'))))// modulus for understand is it first of second data
			{
				o_counter++;
				o_pointer->amount = stoi(readen2);//if it is first data it is amound

			}
			else if ((o_counter % 2 == 1) && ('A' <= readen2.at(0) && readen2.at(0) <= 'z'))
			{
				o_counter++;
				o_pointer->sendTo = readen2;// if its second data its send to
			}
		}
		o_pointer = temp2;
	}

	LastElementDeleter(add_Node->outputList);
	LastElementDeleter(add_Node->outputList); // upside algorithm creates 2 empty node
	// to delete these I used these functions

	////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	//INPUTCHECK PART


	//1.All inputs should belong to owners transaction 
	bool first_check = true;// to check owner
	inputNode*investigator;
	investigator = add_Node->inputList;// investigator shows new transaction node's  inputList


	while (!(investigator == NULL))
	{
		transactionNode*transaction_roller = blockchain;// transaction_roller show head 
		outputNode*output_roller;
		for (int j = 0; j < (investigator->transactionId) - 1; j++)//to move till the searched transaction

		{
			if (!(transaction_roller->nextT == NULL))
			{
				transaction_roller = transaction_roller->nextT;

			}
		}
		output_roller = transaction_roller->outputList;
		for (int m = 0; m < (investigator->outputLocation) - 1; m++)//to go outputLocation of searched one
		{
			if (!(output_roller->nextO == NULL))
				output_roller = output_roller->nextO;
		}

		if (!(output_roller->sendTo == add_Node->owner))// to understand is the transaction owner and money's owner same person or not
		{
			first_check = false;
			cout << "Invalýd T: input owner is not right!";
			break;

		}

		investigator = investigator->nextI;// to go next inputNode


	}


	//2.Every output should be used at most once
// THis part is written for understand do user is using same input twice

	inputNode*checkerÝnputOnce;
	bool check2 = true;// Ýt will be false when double spending detected 
		
	inputNode*checker3 = add_Node->inputList;//checker 3 shows new Node's inputList
	transactionNode*T_Stroller = blockchain;// shows head of Transaction Node 
	while (check2 == true)
	{


		while (T_Stroller->owner != add_Node->owner)// to find the existing transaction of same owner
		{
			if (T_Stroller->nextT != NULL)
			{
				T_Stroller = T_Stroller->nextT;// goes new transaction node
			}
			if (T_Stroller->nextT == NULL)
			{
				break;
			}


		}

		while (checker3 != NULL)///checks input list same or not
		{

			if (T_Stroller->owner == add_Node->owner)// when we find new Transactions owner
			{
				if (T_Stroller->inputList->transactionId == checker3->transactionId)// /when we find same with new Transaciton input
				{
					if (T_Stroller->inputList->outputLocation == checker3->outputLocation)// if the same transactions outputlocations are same it means double spending happened
					{
						check2 = false;
						cout << "DOUBLE SPENDING DETECTED";
					}

				}

				if (checker3->nextI != NULL)
				{
					checker3 = checker3->nextI;//to go next inputNode
				}
				else if (checker3->nextI == NULL)
				{
					break;
				}

			}
			if (T_Stroller->nextT == NULL)//TO FÝNÝSH THE LOOP 
			{
				break;
			}


		}
		if (T_Stroller->nextT == NULL)//TO FÝNÝSH THE LOOP 
		{
			break;
		}
	}

	//3.Total input must be larger or equal to  total output




	double income = 0, balance = 0, expense = 0;
	// income is what user earn 
	//expense is what user send 
	//balance is difference of earn and sen


	
	inputNode*input_checker_balance = add_Node->inputList;//shows new Transaction nodes input List head
	transactionNode*transaction_checker_balance = NULL;
	//outputNode*output_checker_balance = transaction_checker_balance->outputList;//since transaction_checker balance will change in downside codes this will change but now shows 
	outputNode*output_checker_balance=NULL;

	//input_checker_balance
	while (input_checker_balance != NULL)
	{
		transaction_checker_balance = blockchain;//head of main transaction

	//	output_checker_balance = transaction_checker_balance->outputList;
		//for (int j = 0; j < (add_Node->inputList->transactionId) - 1; j++)//to find the transaction Npde
		for(int j=0;j<(input_checker_balance->transactionId)-1;j++)
		{
			if (transaction_checker_balance->nextT != NULL)
				transaction_checker_balance = transaction_checker_balance->nextT;
		}
		output_checker_balance = transaction_checker_balance->outputList;
		for (int i = 0; i < (input_checker_balance->outputLocation) - 1; i++)//to find found Transaction node's outputNode
		//for (int i = 0; i < (add_Node->inputList->outputLocation) - 1; i++)//to find found Transaction node's outputNode
		{
			//output_checker_balance = transaction_checker_balance->outputList;
			
			if (output_checker_balance->nextO != NULL)
				output_checker_balance = output_checker_balance->nextO;

		}
		//income += output_checker_balance->amount;// to calculate found income
		income += output_checker_balance->amount;// to calculate found income



		if (input_checker_balance->nextI != NULL)
		{
			input_checker_balance = input_checker_balance->nextI;//to go next Ýnput Node
		}
		else
		{
			break;
		}


	}

	/// BURDA HATA VAR 1.YÝ BULDUKTAN SONRA ÝKÝNCÝYÝ BULMAYACAK 

	outputNode*expensefinder = add_Node->outputList;

	bool check3 = true;

	while (expensefinder != NULL)
	{
		expense += add_Node->outputList->amount;
		if (expensefinder->nextO != NULL)
			expensefinder = expensefinder->nextO;//to find expenses
		else
		{
			break;
		}
	}

	
	balance = income - expense;





	int number = 1;// since first transformation added already 

	transactionNode*counter = blockchain;
	while (counter != NULL)//// TO FÝND tid of New Node by checking All Transaction Nodes
	{
		if (counter->nextT != NULL)
		{
			counter = counter->nextT;
			number++;
		}
		else
		{
			number++;//if next transaction does not exist it will be our next therefore we need to increase tid ;
			break;
		}

	}

	add_Node->tid = number;

	int hval, PoW;
	
	if (!(check2 == false || first_check == false))
	{
		if (balance < 0)// if user try expense more than input's
		{
			check3 = false;
			cout << "Invalid T : total output > total input!";
		}
		else if (balance == 0)// when user use at
		{
			check3 = true;

			
		}
		else if (balance > 0)// if user expense less than he got 
		{
			check3 = true;

		}

		if (!(check3 == false))// when user have enough money
		{

			mine(add_Node, blockchain, hval, PoW, 10);// calculetes POW and Hval

			add_Node->hval = hval;

			add_Node->PoW = PoW;

			if (balance == 0)
			{
				InsertLast(blockchain, add_Node);// To add New Node at the end of Transaction LinkedList
				cout << "We succesfully added transaction";
			}

			
			else if (balance > 0)//situation for when user got more than he/she expense
			{
				cout << "We succesfully added transaction";
				InsertLast(blockchain, add_Node);
				AddToLast_ofOUtputList(add_Node, balance);// add new outputNode to the end of Output LinkedList 
			}

		}
	}
}
int main()
{
	fstream input;
	istringstream iss;

	string read;// where it stores readen data
	string filename = "input.txt";

	input.open(filename.c_str());//opens file in c style
	string transaction_owner, str;
	int hash_rate, PoW;
	int counter = 0;//this is for while reading file to understand read thing money or person

	input >> transaction_owner;//since 1 account can not be more than 1 owner
	input >> hash_rate;
	input >> PoW;

	transactionNode*blockchain = new transactionNode;// creates first output Node;

	blockchain->nextT = NULL;// before adding new transaction for SAFETY

	outputNode*head = new outputNode; // head pointer of first outputNode which will be written by reading text 
	blockchain->outputList = head;

	outputNode*ali = head;// For safety third 

	int i = 1;
	while (!input.eof())// when input not at the end of file;
	{
		outputNode*temp = new outputNode;// temp pointer which shows outputNode to

		ali->nextO = temp;
		temp->nextO = NULL;


		for (int k = 0; k < 2; k++)
		{

			input >> str;


			if (counter % 2 == 0)
			{
				//temp->amount = stoi(str);
				ali->amount = stoi(str);
			}
			else if (counter % 2 == 1)
			{
				//temp->sendTo = str;

				ali->sendTo = str;

			}

			counter++;

		}
		ali = temp;
		//ali->nextO = NULL;

	}
	LastElementDeleter(head);// for deleting last outputNode  of first transaction 


	blockchain->owner = transaction_owner;
	blockchain->PoW = PoW;
	blockchain->tid = 1;
	blockchain->hval = hash_rate;
	blockchain->nextT;
	blockchain->inputList = nullptr;// for first transaction there is no input List

	string user;
	while (true)

	{

		cout << endl;

		cout << "******************************************************" << endl

			<< "***** 0	- EXIT PROGRAM								****" << endl
			<< "***** 1	- PRINT BLOCKCHAIN							****" << endl
			<< "***** 2	- PRINT REMAINING MONEY OF A USER					****" << endl
			<< "***** 3	- ADD A TRANSACTION							****" << endl

			<< "********************************************************" << endl;
		cout << endl;

		int option;

		cout << "Pick an option from above (int number from 0 to 3): "; cin >> option;

		switch (option)

		{
		case 0:

			cout << "PROGRAM EXITING ... " << endl;

			system("pause");
			exit(0);

		case 1:

			printBlockchain(blockchain);
			break;

		case 2:

			printRemainingMoney(blockchain, user);

			break;
		case 3:

			AddTransaction(blockchain);

			break;
		default:

			cout << "INVALID OPTION!!! Try again" << endl;

		}//switch
	}//while (true)





	system("pause");
	return 0;
}
