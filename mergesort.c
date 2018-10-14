struct dataEntries* sortPartitions(struct dataEntries* l1, struct dataEntries* l2);
void partitionListForSort(struct dataEntries* head, struct dataEntries** l1, struct dataEntries** l2);
void mergeSort(struct dataEntries **list);

//main mergeSort function
void mergeSort(struct dataEntries **list){

    struct dataEntries *tempSort = *list;
    struct dataEntries *l1;
    struct dataEntries *l2;
    //Base Case
    if((tempSort==NULL)||(tempSort->next==NULL)){
        return;
    }
    //performs recursive partitions and the sorts those partitions
    partitionListForSort(tempSort,&l1,&l2);
    mergeSort(&l1);
    mergeSort(&l2);
    *list = sortPartitions(l1,l2);
}
//Sort list
struct dataEntries *sortPartitions(struct dataEntries *l1, struct dataEntries *l2){
    struct dataEntries *finalLL = NULL;
    //Base Case to return the data of the list that is not null
    if(l1 == NULL){
        return l2;
    }else if(l2 == NULL){
        return l1;
    }
    //simple comparisons that advance the list that is less than the other recursively
    //depending on the data type that is being dealt with (numbers or letters)
    // 1 means the data entries are numbers and 0 means the data entries are words
    if(dataType == 1){
        if(l1->sortName->data<=l2->sortName->data){
            finalLL = l1;
            finalLL->next = sortPartitions(l1->next,l2);
        }else{
            finalLL = l2;
            finalLL->next = sortPartitions(l1,l2->next);
        }
    }else{
        if(strcmp(l1->sortName->dataToSort,l2->sortName->dataToSort)<=0){
            finalLL = l1;
            finalLL->next = sortPartitions(l1->next,l2);
        }else{
            finalLL = l2;
            finalLL->next = sortPartitions(l1,l2->next);
        }
    }
    return  finalLL;
}
//Partitions List
void partitionListForSort(struct dataEntries *head, struct dataEntries **l1, struct dataEntries **l2){
    struct dataEntries *first;
    struct dataEntries *second;
    second = head;
    //Base case
    if(head == NULL || head->next){
        *l1 = head;
        *l2 = NULL;
    }else{
        //One pointer progresses when not null
        //and the other pointer progresses based off of the first pointer
        //this helps split the list
        second = head;
        first = head->next;
        while(first!=NULL){
            first = first->next;
            if(first!=NULL){
                second = second->next;
                first = first->next;
            }
        }
    }
    *l1 = head;
    *l2 = second->next;
    second->next = NULL;
}
