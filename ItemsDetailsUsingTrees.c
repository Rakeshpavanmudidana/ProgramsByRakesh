// Items using Items Details using trees

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define FILE_NAME "ItemDetails.dat"
#define ItemMSG "Enter Items"
#define ID_LENGTH 20
#define NAME_LENGTH 50

struct ItemDetails
{
	char ItemId[ID_LENGTH];
	char ItemName[NAME_LENGTH];
	int ItemPrice;
	
}ItemDetails;

typedef struct ItemDetails ItemsDetails;

struct Node 
{
	struct Node *Left;

	ItemsDetails Record;


	struct Node *Right;
};
typedef struct Node Node;


Node *Root = NULL, *temperoryNode;

Node **NodePtrs;

clock_t StartTime, End;

FILE *FpItemsDetails;

int Count, Counter;

void showMenu();
Node* addItem(Node *, ItemsDetails);
void LoadList();
void showAllItems(Node*);
void updateItemDetails( Node** );
void removeItem( Node** );
void saveList();
void searchRecord(char* );
Node** getMatchingNode(char* ,Node**);


void printSucessMsg(char *Content, char *ItemId)
{
	printf("\nSucessfully %s item with id %s\n", Content, ItemId);
}


void printNoRecordFound()
{
	printf("\nThere is no items in the file.\n");
}

void printItemNotFound(char *ItemId)
{
	printf("\nItem with id %s not found.\n", ItemId);
}

char* getItemId()
{
	char *ItemId = (char*) malloc(sizeof(char) * ID_LENGTH);
	printf("Enter Item Id: ");
	scanf("%s", ItemId);

	return ItemId;
}


Node* creatNode(ItemsDetails ItemDetails)
{
	Node *NewChild = malloc(sizeof(Node));

	NewChild->Record = ItemDetails;

	NewChild->Left = NewChild->Right = NULL;
	return NewChild;
}


void showItem()
{
	printf("\n\t Item Id: %s\n", ItemDetails.ItemId);
	printf("\t Item Name: %s\n", ItemDetails.ItemName);
	printf("\t Item Price: %d\n", ItemDetails.ItemPrice);
}
void getItemDetails()
{

	printf("\n %s ID: ", ItemMSG);
	scanf("%s", ItemDetails.ItemId);

	printf("\n %s name: ", ItemMSG);
	scanf(" %[^\n]s", ItemDetails.ItemName);

	printf("\n %s Price: ", ItemMSG);
	scanf("%d", &ItemDetails.ItemPrice);
}

void callSaveList()
{
	FpItemsDetails = fopen(FILE_NAME, "w");

	saveList(Root);

	fclose(FpItemsDetails);
}

Node* findMin(Node* CurrentChild)
{
	while (CurrentChild->Left != NULL)
		CurrentChild = CurrentChild->Left;

	printf("%s\n", CurrentChild->Record.ItemId);

	return CurrentChild;
}

void main()
{
	
	temperoryNode = (Node*) malloc(sizeof(Node));

	LoadList();

	while(1)
	{
		showMenu();
	}

	free(temperoryNode);
}



void showMenu()
{
	int Choice;
	printf("\n 1. New Item\n 2. Show all Item\n 3. Search\n 4. Update Price\n 5. Remove Item\n 6. EXIT\n");
	printf("Enter your choice: ");
	scanf("%d", &Choice);

	switch (Choice)
	{
		case 1: getItemDetails();
				Root = addItem(Root, ItemDetails);
				callSaveList();
				printSucessMsg("created", ItemDetails.ItemId);
				break;

		case 2: Counter = 1;
				showAllItems(Root);
				break;

		case 3:	printf("To Search.\n");
				searchRecord(getItemId());
				break;

		case 4:	printf("\nTo update Item price\n");
		 		updateItemDetails( getMatchingNode( getItemId(), &Root ));
		 		callSaveList();
				break;

		case 5:	printf("\n To remove Item\n");
				char *ItemId = getItemId();
				removeItem(	 getMatchingNode(ItemId, &Root) );
				printSucessMsg("removed", ItemId);
				callSaveList();
				break;

		case 6: exit(0);

		default: printf("\n\tINVALID Choice\t\n\t TRY AGAIN\t");
				 break;

	}

}


void searchRecord(char* ItemId)
{
	Node **SearchedNode = getMatchingNode(ItemId, &Root);
	if (*SearchedNode)
	{
		ItemDetails = (*SearchedNode)->Record;
		showItem();
	}
	else
		printItemNotFound(ItemId);


}

void saveList(Node* CurrentChild)
{
	if (CurrentChild != NULL)
	{
		saveList(CurrentChild->Right);
		fwrite(&CurrentChild->Record, sizeof(ItemsDetails), 1, FpItemsDetails);

		saveList(CurrentChild->Left);
	}


}

void LoadList()
{
	FpItemsDetails = fopen(FILE_NAME, "r");

	while (fread(&ItemDetails, sizeof(ItemDetails), 1, FpItemsDetails))
		Root = addItem(Root, ItemDetails);

	fclose(FpItemsDetails);

}


Node* addItem(Node *CurrentChild, ItemsDetails ItemDetails)
{
	if (CurrentChild == NULL)
		return creatNode(ItemDetails);

	else if (strcmp( ItemDetails.ItemId, CurrentChild->Record.ItemId) > 0)
		CurrentChild->Left = addItem(CurrentChild->Left, ItemDetails);
	else
		CurrentChild->Right = addItem(CurrentChild->Right, ItemDetails);
	return CurrentChild;

}


void showAllItems(Node *CurrentChild)
{
	if (CurrentChild)
	{
		printf("\nItem: %d", Counter);
		showAllItems(CurrentChild->Right);
		ItemDetails = CurrentChild->Record;
		showItem();
		showAllItems(CurrentChild->Left);

	}


}


void updateItemDetails(Node** MatchedNode)
{
	if ( *MatchedNode )
	{
		printf("Enter new Item price: ");
		scanf("%d", &(*MatchedNode)->Record.ItemPrice);


		callSaveList();
		printSucessMsg("Updated", (*MatchedNode)->Record.ItemId);
	}


}
void removeItem( Node** MatchedNode)
{
	if (*MatchedNode != NULL)
	{
		Node *temp = *MatchedNode;
		if ((*MatchedNode)->Left == NULL) 
		{
		    *MatchedNode = (*MatchedNode)->Right;
	    }
	    else if ((*MatchedNode)->Right == NULL) 
	    {
	        *MatchedNode = (*MatchedNode)->Left;
	    }
		else 
		{
			Node* LastNode = findMin(((*MatchedNode)->Right));
			(*MatchedNode)->Record = LastNode->Record;
			removeItem( getMatchingNode(LastNode->Record.ItemId, &(*MatchedNode)->Right) );
			free(LastNode);

		}
		free(temp);

		callSaveList();
	}
        

}


Node** getMatchingNode(char *ItemId, Node** CurrentChildPtr  )
{
	if (*CurrentChildPtr  == NULL)
	{
		printItemNotFound(ItemId);
		return CurrentChildPtr;
	}

	if (!strcmp((*CurrentChildPtr)->Record.ItemId, ItemId))
		return 	CurrentChildPtr;

	else if (strcmp((*CurrentChildPtr)->Record.ItemId, ItemId) < 0)
		getMatchingNode( ItemId, &(*CurrentChildPtr)->Left);

	else if (strcmp((*CurrentChildPtr)->Record.ItemId, ItemId) > 0)
		getMatchingNode(ItemId, &(*CurrentChildPtr)->Right);

}