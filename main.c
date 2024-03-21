//Jehad Hamayel
//1200348
//sec: 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MaxNumberOfCities 200
#define INT_MAX_infinte 2147483647
#define MaxNumOfChar 40
#define numOfCharInLine 200
struct Dijkstra_Matrix//Define a new type of Dijkstra_Matrix data
{
    int numOfCities ;
    char cities [MaxNumberOfCities][MaxNumOfChar];
    int adjacency_Matrix [MaxNumberOfCities][MaxNumberOfCities];
} ;
struct Dijkstra_Matrix dijks;//Define a variant of the streak

int isInteger(char []);//Method to Check if the Integer
int isExist(char []);//Method to check if the city Exist
int getIndex (char []);//Method to Get The Index Of the city in the array
void loadCitiesFile ();//Method to load Cities From File
void shortestPathCount(char []);//Method To Get The Shortest Path between each two cities
int getIndxOfTable (char x[MaxNumOfChar]);////Method To get The Index for city in node Table
int getMinCost(int [], int []);//Method to get the index of minimum Cost
void printFullPath (char []);//Method To print Full Path between To cities
void printInFile(char []);//Method To print Full Path between To cities in the file
//Define matrices to work in
char node[MaxNumberOfCities][MaxNumOfChar];
int known[MaxNumberOfCities];
int cost[MaxNumberOfCities];
char parent[MaxNumberOfCities][MaxNumOfChar];
char path[MaxNumberOfCities][MaxNumOfChar];
int costtt[MaxNumberOfCities];

int main()
{
    printf("-------------------------------------<<<<<<Welcome to my project>>>>>>-------------------------------------\n\n");
    char opch[10];
    int True=1,readedFile=0,sourse=0,destination=0;
    char sourceCity[MaxNumOfChar],destinationCity[MaxNumOfChar];
    while(True) //Create a loop that displays options for operations and call functions.
    {
        printf("Enter the number of the option that you want:\n\n");
        printf("1. Load cities.\n");
        printf("2. Enter source city.\n");
        printf("3. Enter destination city.\n");
        printf("4. exit.\n\n");
        printf("Choose an option:");

        fflush(stdin);//In order not to take Inter as a character
        gets(opch);
        if(isInteger(opch)) //Check if the entry is a number
        {
            int op=atoi(opch);
            printf("\n-------------------------------------------------------------\n\n");
            switch(op)
            {
            case 1:
                if(!readedFile) //Check if it is read or not
                {
                    loadCitiesFile();//Calling load Cities File Method
                    printf("-------------------------------------------------------------\n\n");
                    readedFile=1;//File has been read
                }
                else
                {
                    printf("The file has already been read\n\n");
                    printf("-------------------------------------------------------------\n\n");
                }
                break;
            case 2:
                if(readedFile)
                {

                    printf("Enter source city Please:");
                    fflush(stdin);
                    gets(sourceCity);
                    if(getIndex(sourceCity)!=-1)
                    {
                        shortestPathCount(sourceCity);//Calling shortest Path Count Method
                        printf("\nPlease Enter 3 For Entering destination city\n\n");
                        printf("-------------------------------------------------------------\n\n");
                        sourse=1;
                    }
                    else
                    {
                        printf("This city does not exist \n\n");
                        printf("-------------------------------------------------------------\n\n");
                    }

                }
                else
                    printf("Please Read The File\n\n");
                break;
            case 3:
                if(readedFile)
                {
                    if(sourse)
                    {
                        printf("Enter destination city Please:");
                        fflush(stdin);
                        gets(destinationCity);
                        if(strcasecmp(sourceCity,destinationCity)!=0)
                        {
                            if(cost[getIndxOfTable(destinationCity)]==INT_MAX_infinte)
                                printf("We Can't reach it\n\n");
                        else
                            if(getIndex(destinationCity)!=-1)
                            {
                                printf("\nthe full route of the shortest path including the distance between each two cities and the total shortest cost:\n\n");
                                printFullPath(destinationCity);//Calling print Full Path Method
                                destination=1;
                                printf("\n\n-------------------------------------------------------------\n\n");
                            }
                            else
                            {
                                printf("This city does not exist successfully\n\n");
                                printf("-------------------------------------------------------------\n\n");
                            }
                        }
                        else
                        {
                            printf("You Enter Source City and Destination City same Name\n\n");
                            printf("-------------------------------------------------------------\n\n");
                        }

                    }
                    else
                        printf("Please Enter source city first\n\n");
                }
                else
                    printf("Please Read The File\n\n");
                break;

            case 4://exit the Program
                if(readedFile)
                {
                    printInFile(destinationCity);//Calling print In File Method
                    if(destination&&sourse)
                        printf("The Data Hava Printed \n\n");
                    else
                        printf("You Don't Enter Sourse Or Destination\n\n");
                }
                else
                {
                    printf("There Is No Data \n\n");
                }
                printf("-------------------------------------<<<<<<Thank You, Goodbey>>>>>>-------------------------------------\n\n");
                return 0;
                break;
            default :
                printf("Choose a correct number\n\n");
                printf("-------------------------------------------------------------\n\n");
            }
        }
        else
        {
            printf("\nPlease Choose a correct number\n\n");
            printf("-------------------------------------------------------------\n\n");
        }

    }

}
int isInteger(char word[])  //Method to check if he was trafficked or not
{
    int index ;
    for(index=0; index<strlen(word); index++)
    {
        if(!isdigit(word[index]))
            return 0;
    }
    return 1;
}
void loadCitiesFile ()
{
    dijks.numOfCities=1;
    strcpy(dijks.cities[0],"");
    int dis;
    FILE *in;//Define file
    char inf[numOfCharInLine],*token,temp1[MaxNumOfChar],temp2[MaxNumOfChar];
    int isEmpty=1;
    in = fopen("cities.txt","r");//Make the file in read
    if(in!=NULL) //Check if the file exists
    {

        while(fgets(inf,numOfCharInLine,in)!=NULL) //while loop for reading from file
        {
            token = strtok(inf,"\t");//String up to \t
            strcpy(temp1,token);
            if(!isExist(token))
            {
                strcpy(dijks.cities[dijks.numOfCities],token);//Copy the string and place it in the required variable
                dijks.numOfCities++;
            }

            token = strtok(NULL,"\t");//String up to \t
            strcpy(temp2,token);
            if(!isExist(token))
            {
                strcpy(dijks.cities[dijks.numOfCities],token);//Copy the string and place it in the required variable
                dijks.numOfCities++;

            }

            token = strtok(NULL,"\t");//String up to \t
            int sizeOfCh = strlen(token);
            char distance[15] ;
            strncpy(distance,token,(sizeOfCh-2)) ;
            distance[(sizeOfCh-2)]='\0';
            dis = atoi(distance);
            //Store in the Matrix
            dijks.adjacency_Matrix[getIndex(temp1)][getIndex(temp2)]=dis;
            dijks.adjacency_Matrix[getIndex(temp2)][getIndex(temp1)]=dis;
            isEmpty=0;
        }
        if(isEmpty) //Check if the file is empty or not
        {
            printf("\n-------------------------------------------------------------\n\n");
            printf("The File is empty\n\n");

        }
        else
        {
            printf("The file has been read successfully\n\n");
        }
        fclose(in);//close file
    }
    else
        printf("File not found\n\n");
    fclose(in); //close file
}
int isExist(char city[])
{
    int i;
    for(i =1; i<dijks.numOfCities; i++)
    {
        //chack if it is Exist
        if(strcasecmp(dijks.cities[i],city)==0)
            return 1;
    }
    return 0;
}
int getIndex (char city[])
{
    int i;
    for(i =1; i<dijks.numOfCities; i++)
    {
        //return the index of city
        if(strcasecmp(dijks.cities[i],city)==0)
            return i;
    }
    return -1;
}
void shortestPathCount(char sourceCity[MaxNumOfChar])
{
    int i,j,in,indx,index;
    //Setting initial values for the table
    strcpy(node[1],sourceCity);
    known[1]=0;
    cost[1]=0;
    strcpy(parent[1],"");
    //Create a new table, especially to know the cost
    for(i=1,j=2; i<dijks.numOfCities&&j<dijks.numOfCities; i++,j++)
    {
        if(strcasecmp(dijks.cities[i],sourceCity)!=0)
        {
            strcpy(node[j],dijks.cities[i]);
            known[j]=0;//that mean if the node is visited or not
            cost[j]=INT_MAX_infinte;
            strcpy(parent[j],"");
        }
        else
            j--;
    }
    //
    for(i=1; i<dijks.numOfCities; i++)
    {
        //Geting the index of the minimum cast
        in= getMinCost(known,cost);
        index =getIndex(node[in]);
        for(j=1; j<dijks.numOfCities; j++)
        {
            //chack if there is distance between cities
            if(dijks.adjacency_Matrix[index][j]!=0)
            {
                indx=getIndxOfTable(dijks.cities[j]);
                //chack for the best cost
                if((cost[indx]>(dijks.adjacency_Matrix[index][j]+cost[in]))&&known[indx]==0)
                {
                    //make update of the cost and the parent of node
                    cost[indx]=dijks.adjacency_Matrix[index][j]+cost[in];
                    strcpy(parent[indx],dijks.cities[index]);
                }
            }
        }
        //make it visited
        known[in]=1;
    }

}
int getIndxOfTable (char x[MaxNumOfChar])
{
    int i;
    for(i =1; i<dijks.numOfCities; i++)
    {
        if(strcasecmp(node[i],x)==0)
            return i;
    }
    return -1;
}
int getMinCost(int known[dijks.numOfCities], int cost[dijks.numOfCities])
{
    int index=1,minCost,i;
    minCost=INT_MAX_infinte;
    for(i=1; i<dijks.numOfCities; i++)
    {
        //get the index of the minimum cost
        if(known[i]==0&&cost[i]<minCost)
        {
            index=i;
            minCost=cost[i];
        }
    }
    return index;
}
void printFullPath (char destinationCity[MaxNumOfChar])
{
    int i,j;
    //Cities Path Compilation
    int index = getIndxOfTable(destinationCity);
    strcpy(path[0],destinationCity);
    costtt[0]=cost[index];

    for(i=1; i<dijks.numOfCities; i++)
    {
        if(strcasecmp(node[1],node[getIndxOfTable(parent[index])])!=0)
        {
            strcpy(path[i],node[getIndxOfTable(parent[index])]);
            costtt[i]=cost[getIndxOfTable(parent[index])];
            index=getIndxOfTable(parent[index]);
        }
        else
        {
            j=i;
            break;
        }
    }
    strcpy(path[j],node[1]);
    costtt[j]=cost[1];
    for(i=j; i>0; i--)
    {
        //Printing the data for the required information
        printf("from %s to %s by cost: %dkm\n",path[i],path[i-1],(costtt[i-1]-costtt[i]));
    }
    printf("\nThe Totle Cost From %s To %s is : %dkm\n",path[j],path[0],costtt[0]);
}
void printInFile(char destinationCity[MaxNumOfChar]) //function definition.
{
    //Method for writing to a file for the data
    FILE * out;
    out = fopen("shortest_path.txt","w");
    int i,j;
    int index = getIndxOfTable(destinationCity);
    strcpy(path[0],destinationCity);
    costtt[0]=cost[index];
    //Cities Path Compilation
    for(i=1; i<dijks.numOfCities; i++)
    {
        if(strcasecmp(node[1],node[getIndxOfTable(parent[index])])!=0)
        {
            strcpy(path[i],node[getIndxOfTable(parent[index])]);
            costtt[i]=cost[getIndxOfTable(parent[index])];
            index=getIndxOfTable(parent[index]);
        }
        else
        {
            j=i;
            break;
        }
    }
    strcpy(path[j],node[1]);
    costtt[j]=cost[1];
    for(i=j; i>0; i--)
    {
        //Printing the data for the required information
        fprintf(out,"from %s to %s by cost: %dkm\n",path[i],path[i-1],(costtt[i-1]-costtt[i]));
    }
    fprintf(out,"\nThe Totle Cost From %s To %s is : %dkm\n",path[j],path[0],costtt[0]);
    fclose(out);
}
