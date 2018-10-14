#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct catNode{
    int index;
    struct catNode *next;
    char categoryName[];
};

struct sortData{
    double data;
    char dataToSort[];
};

struct dataEntries{
    int row;
    int dataType;
    struct sortData *sortName;
    struct dataEntries *next;
    char line[];
};

struct catNode* categoriesLL = NULL;
struct dataEntries* sortingList = NULL;

int categories = 0;
int sortingIndex = -1;
int dataType = -1;

//Function prototypes
void addCategory(char name[] , int index);
void setEntry(char word[], int index, char assocData[], int row, int numCheck);
void splitWord(char *line, int row, char sortCol[]);

int checkData(char data[]){
    int length = (int)strlen(data);
    int i;
    for(i = 0; i < length; i++){
        if(data[i]=='.'){
            continue;
        }
        if(!isdigit(data[i])){
            return 0;
        }
    }
    return 1;
}
char* trim(char space[]){
    int length = (int)strlen(space);
    int i, start = 0, end = 0, flag = 0, endFlag = 0;

    for(i = 0; i < length; i++){
        char temp = space[i];
        if(((temp >= 'a' && temp <='z')||(temp >= 'A' && temp <='Z')|| (temp >= '0' && temp <= '9')) && flag==0 ){
            start = i;
            flag = 1;
        }
        if(flag == 1 && ((i < length - 2)|| (space[length-1] >= 'a' && space[length-1] <='z')||(space[length-1] >= 'A' && space[length-1] <= 'Z')|| (space[length-1] >= '0' && space[length-1] <= '9'))){
            if((space[length-1] != ' ')){
                endFlag = 1;
                break;
            }
            if(((temp >= 'a' && temp <='z')||(temp >= 'A' && temp <='Z')|| (temp >= '0' && temp <= '9')) &&
               (space[i+1] == ' ' && !((space[i+2] >= 'a' && space[i+2] <='z')||(space[i+2] >= 'A' && space[i+2]<='Z')||(space[i+2]>= '0' && space[i+2] <= '9')))){
                end = i;
                break;
            }
        }
    }
    int endTrim = 0;
    if(endFlag == 1){
        endTrim = 0;
    }else{
        endTrim = length - end;
    }
    char trim[(length-start-endTrim+1)];
    if(endFlag == 1){
        memcpy(trim,&space[start],(size_t)(length-start));
        trim[length-start-endTrim+1] = '\0';
    }else{
        memcpy(trim,&space[start],(size_t)(length-start-endTrim+1));
        trim[length-start-(endTrim)+1] = '\0';
    }
    char *word = trim;
    return word;
}

//adds category to front of list
void addCategory(char name[] , int index){
    //printf("ADDING: %s\n", name);
    struct catNode *newCategory = malloc(sizeof(struct catNode) + sizeof(char)*strlen(name)+1);
    newCategory->index = index;
    strcpy(newCategory->categoryName,name);
    if(!categoriesLL){
        newCategory->next = NULL;
        categoriesLL = newCategory;
    }else{
        newCategory->next = NULL;
        struct catNode *temp = categoriesLL;
        while(temp!=NULL){

            if(temp->next == NULL){
                temp->next = newCategory;
                break;
            }
            temp = temp->next;
        }
        //newCategory->next = categoriesLL;
        //categoriesLL = newCategory;
    }
    categories++;
}
//Organizes the data in the Linked List
void setEntry(char word[], int index, char assocData[], int row,int numCheck){
    struct sortData *name = malloc(sizeof(struct sortData) + strlen(word)+1);
    struct dataEntries *newData = malloc(sizeof(struct dataEntries) + strlen(assocData)+1);
    newData->row = row;
    newData->next = NULL;
    newData->dataType = numCheck;
    if(!sortingList){
        newData->next = NULL;
        if(numCheck == 1){
            double tempNum = strtod(word,NULL);
            name->data = tempNum;
            //printf("%f\n",name->data);
        }else{
            strcpy(name->dataToSort,word);
        }
        newData->sortName = name;
        strcpy(newData->line,assocData);
        sortingList = newData;
        newData->row = row;
    }else{
        if(numCheck == 1){
            double tempNum = strtod(word,NULL);
            name->data = tempNum;
            //printf("%f\n",name->data);
        }else{
            strcpy(name->dataToSort,word);
        }
        newData->sortName=name;
        strcpy(newData->line,assocData);
        newData->next = sortingList;
        sortingList = newData;
        newData->row = row;
    }
}

void printAssocData(){
    //printf("Organized Data\n");
    struct dataEntries* ptr = sortingList;
    int count = 1;
    while(ptr!=NULL){
        /*if(dataType == 1){
            printf("%d: %lf \n ",ptr->row,ptr->sortName->data);
        }else{
            printf("%d: %s \n ",ptr->row,ptr->sortName->dataToSort);
        }*/
        printf("%s",ptr->line);
        ptr = ptr->next;
        count++;
    }
    //printf("NULL\n");
}
void printLL(){
    struct catNode* ptr = categoriesLL;
    while(ptr!=NULL){
        if(ptr->next == NULL){
            printf("%s",ptr->categoryName);
            break;
        }
        printf("%s,", ptr->categoryName);
        ptr = ptr->next;
    }

}


void splitWord(char *line, int row, char sortCol[]){
    //printf("%s\n",line);
    int length = sizeof(char) * strlen(line);
    int i,start = 0,index = 0, flag = 0, charLength = 0, quoteCheck = 0, numCheck = 0;
    for(i = 0; i < length;i++){
        //printf("%c \n",line[i]);
        char a = line[i];
        if(a == '"' && quoteCheck == 0){
            start = i+1;
            charLength = charLength -1;
            quoteCheck++;
        }else if( a == '"' && quoteCheck > 0){
            quoteCheck = 0;
            charLength = charLength - 1	;
            continue;
        }
        if(a ==','&& quoteCheck == 0){
            char word[charLength];
            if(index == 0){
                charLength = charLength + 1;
            }
            memcpy(word, &line[start], (size_t)(charLength-1) );
            word[charLength-1] = '\0';
            //printf("%s\n",word);
            if(row == 0){
                if(strcmp(sortCol,word)==0){
                    sortingIndex = index;
                }
                addCategory(word,index);
            }else{
                if(index==sortingIndex){
                    numCheck = checkData(word);
                    if(dataType < 0){
                        dataType = numCheck;
                    }
                    char *temp = trim(word);
                    char trimWord[strlen(temp)+1];

                    memcpy(trimWord,temp,strlen(temp));
                    trimWord[strlen(temp)] = '\0';
                    //printf("%s|%d\n",trimWord,(int)strlen(trimWord));
                    setEntry(trimWord,index,line,row,numCheck);
                    return;
                }
            }
            index = index + 1;
            start = i+1,charLength = 0; quoteCheck = 0;
            memset(word,0,sizeof(word));
        }
        charLength = charLength + 1;
    }
    char word[charLength];
    memcpy(word, &line[start], (size_t)(charLength-1) );
    word[charLength-1] = '\0';
    if(row == 0 ){
        addCategory(word,index);
    }else{
        numCheck = checkData(word);
        dataType = numCheck;
	setEntry(word,index,line,row,numCheck);
    }
    memset(line,0,sizeof(line));
}
