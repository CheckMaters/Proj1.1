#include "simpleCSVsorter.h"
#include "mergesort.c"


int main(int argc, char ** argv){
    FILE *f;
    f = fdopen(0,"r");
    //f = fopen("movie_metadata.csv","r");
    if(f==NULL){
        printf("Cannot find file.\n");
        exit(0);
    }
    if(argc != 3){
	printf("Must have only 3 arguments.\n");
	exit(0);
    }
    char *rline = NULL;
    size_t size = 0;
    ssize_t read;
    char *word;
    const char delim[2] = ",";
    int rows = 0;
    
    char sort[strlen(argv[2])+1];
    strcpy(sort,argv[2]);
    //printf("%d %s",argc,argv[2]);
    

    const char *entry[categories];
    while((read=getline(&rline,&size,f))!=-1){
           
            //printf("%s\n", rline);
            //exception if user inputs category not found
            char data[strlen(rline)+1];
            strcpy(data,rline);
            //printf("ROW: %d\n",rows);
            splitWord(data,rows,sort);
            //printf("%s\n", data);
            rows = rows + 1;
            memset(data,0,sizeof(data));
    }
    printLL();
    mergeSort(&sortingList);
    printAssocData();

    //printf("Categories: %d | Rows %d | Sorting Column: %d\n | Type: words\n", categories,(rows-1),sortingIndex,dataType);


}
