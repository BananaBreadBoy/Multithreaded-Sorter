#include "sorter_thread.h"

/* Global variables for threads*/
pthread_t * allThreads;
int threadIndex=0;

record * movies; //data contained in a single csv

int columnToSort;

int counter;

Variables * parameters;

pthread_mutex_t lock;

int checkpath (char * odir) { 
	char * temp; 
	temp=strdup(odir);
	int result; 
	result = (temp && *temp && temp[strlen(temp) - 1] == '/') ? 0 : 1;
	return result;
}

void printfile (record * sortedfile, char * outputDir, int counter, char * columnName) { 
	char * token = "AllFiles-sorted-";
    char * outputfile=(char*)malloc(sizeof(char*)*200);
    strcpy(outputfile,outputDir);
    strcat(outputfile,"/");
    strcat(outputfile,token);
    strcat(outputfile,columnName);
    strcat(outputfile,".csv");	

    FILE * output = fopen(outputfile,"w");
	if (output == NULL) {
		printf("WRONG FILENAME.\n");
		exit(1);
	}
    
    int x;
	for (x=0;x<counter;x++){
		fprintf(output,"%s,",movies[x].color);
		fprintf(output,"%s,",movies[x].director_name);
		fprintf(output,"%d,",movies[x].num_critic_for_reviews);
		fprintf(output,"%d,",movies[x].duration);
		fprintf(output,"%d,",movies[x].director_facebook_likes);
		fprintf(output,"%d,",movies[x].actor_3_facebook_likes);
		fprintf(output,"%s,",movies[x].actor_2_name);
		fprintf(output,"%d,",movies[x].actor_1_facebook_likes);
		fprintf(output,"%d,",movies[x].gross);
		fprintf(output,"%s,",movies[x].genres); 
		fprintf(output,"%s,",movies[x].actor_1_name);
		fprintf(output,"%s,",movies[x].movie_title);
		fprintf(output,"%d,",movies[x].num_voted_users);
		fprintf(output,"%d,",movies[x].cast_total_facebook_likes);
		fprintf(output,"%s,",movies[x].actor_3_name);
		fprintf(output,"%d,",movies[x].facenumber_in_poster );
		fprintf(output,"%s,",movies[x].plot_keywords);
		fprintf(output,"%s,",movies[x].movie_imdb_link);
		fprintf(output,"%d,",movies[x].num_user_for_reviews);
		fprintf(output,"%s,",movies[x].language);
		fprintf(output,"%s,",movies[x].country);
		fprintf(output,"%s,",movies[x].content_rating);
		fprintf(output,"%lu,",movies[x].budget);
		fprintf(output,"%d,",movies[x].title_year);
		fprintf(output,"%d,",movies[x].actor_2_facebook_likes);
		fprintf(output,"%f,",movies[x].imdb_score);
		fprintf(output,"%f,",movies[x].aspect_ratio);
		fprintf(output,"%d\n",movies[x].movie_facebook_likes);
	}
}

void * threadDirectory (void * sortParameters) {
	pthread_mutex_lock(&lock); 

	Variables * data = (Variables *) sortParameters; 

	char * path = (char *) malloc(sizeof(char *)*500);
	strcpy(path, data->CSVpath);

    directory(path);

    pthread_mutex_unlock(&lock); 

    pthread_exit(NULL);
}

void directory (char * path) {


  DIR * dirp; 
  struct dirent *dirptr; 
  dirp = opendir(path); 
  if(dirp==NULL){
  	fprintf(stderr, "Invalid directory path entered, please enter a correct path\n" );
  }

  while (dirptr = readdir(dirp)) {
  	char * temp;
    temp=(char*) malloc(strlen(path)+strlen(dirptr->d_name)+3);
    strcpy(temp,path);
    strcat(temp,"/");
    strcat(temp,dirptr->d_name);
    struct stat st; 
    stat(temp, &st); 

    if (strcmp(dirptr->d_name, ".") == 0 || strcmp(dirptr->d_name, "..") == 0) { 
      continue;
    }

    else if (isDirectory(temp)) {

    	Variables dirVar;
    	strcpy(dirVar.CSVpath,temp);

    	parameters[threadIndex] = dirVar;
    	pthread_create(&allThreads[threadIndex],NULL,threadDirectory,&parameters[threadIndex]);
    	threadIndex+=1;
    	//printf("%d\n",threadIndex );
    	free(temp); 
    }
    else {
      	int len = strlen(temp); 
      	if (temp[len-3] == 'c' && temp[len-2] == 's' && temp[len-1] == 'v' && !strstr(temp, "-sorted-")) { 
    		Variables csvVar;
    		strcpy(csvVar.CSVpath, temp); 

    		parameters[threadIndex] = csvVar;
    		pthread_create(&allThreads[threadIndex], NULL, threadSort, &parameters[threadIndex]);
    		threadIndex+=1;
    		//printf("%d\n",threadIndex );
    		free(temp);
    	}
    }
  }
  closedir(dirp);
}

void * threadSort(void * sortParameters){
	Variables * sorterPara = (Variables*)sortParameters;
	char * path = (char*)malloc(sizeof(char *)*500);

	strcpy(path,sorterPara->CSVpath);
	sorter(path);

	pthread_exit(NULL);
}

void sorter(char * csvfilepath){
	pthread_mutex_lock(&lock);

	FILE *fp;
	fp=fopen(csvfilepath,"r");
	char * line = NULL;
	size_t size = 0;
	ssize_t linelen = 0; 
	getline(&line,&size,fp);
	int validityCheck;
	char * firstRow;
	firstRow=strdup(line);



	validityCheck=validCSV(firstRow);

	while (linelen = getline(&line, &size, fp) > 0){
		if (counter == 0) {
			movies = malloc(sizeof(record));
		}
		else {
			movies = realloc(movies, sizeof(record)*(counter+1));
		}

		char* tokenizer=nulTok(line,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].color = strdup(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].director_name = strdup(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].num_critic_for_reviews = atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].duration=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].director_facebook_likes=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].actor_3_facebook_likes=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].actor_2_name = strdup(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].actor_1_facebook_likes=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].gross=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].genres=strdup(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].actor_1_name = strdup(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].movie_title = strdup(tokenizer);

		int check = 0;
		if(*movies[counter].movie_title == 34) check = 1;
		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);

		
		if(check==1){

			while(check == 1){
					movies[counter].movie_title = realloc(movies[counter].movie_title, strlen(movies[counter].movie_title) + 2 + strlen(tokenizer));
					movies[counter].movie_title = strcat(movies[counter].movie_title,",");
					movies[counter].movie_title = strcat(movies[counter].movie_title, tokenizer);

					if(*(tokenizer + strlen(tokenizer) - 1) == 34) check = 0;
					tokenizer = nulTok(NULL, ",");
					tokenizer=trimSpaces(tokenizer);

			}
			movies[counter].num_voted_users=atoi(tokenizer);
		}
		else {
			movies[counter].num_voted_users=atoi(tokenizer);
		}


		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].cast_total_facebook_likes=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].actor_3_name= strdup(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].facenumber_in_poster=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].plot_keywords = strdup(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].movie_imdb_link=strdup(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].num_user_for_reviews=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].language = strdup(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].country = strdup(tokenizer);

		tokenizer = nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].content_rating = strdup(tokenizer);
		
		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].budget=atol(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].title_year=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].actor_2_facebook_likes=atoi(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].imdb_score=atof(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].aspect_ratio=atof(tokenizer);

		tokenizer=nulTok(NULL,",");
		tokenizer=trimSpaces(tokenizer);
		movies[counter].movie_facebook_likes=atoi(tokenizer);

		counter++;
	}

	pthread_mutex_unlock(&lock);

}

int isDirectory(char * path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return 0; 
    }
    return S_ISDIR(statbuf.st_mode);
}

int columnCheck(char * column){
	int i;
	for(i=0;i<28;i++){
		if(strcmp(column,movieColumns[i])==0){
			return i;

		}
	}
	return -1;
}

int validCSV(char * row){
	char * temp;
	temp=strdup(row);
	char * tokenTest;
	tokenTest=strtok(row,",");
	int valid_check=0;
	valid_check+=1;
	while(tokenTest!=NULL){
		tokenTest=strtok(NULL,",");
		valid_check+=1;
	}
	return valid_check;
}

char * nulTok (char * str, char const * delims) {
  static char  * src = NULL;
  char  *  p,  * ret = 0;

  if (str != NULL)
    src = str;

  if (src == NULL)
    return NULL;

  if ((p = strpbrk (src, delims)) != NULL) {
    *p  = 0;
    ret = src;
    src = ++p;

  } else if (*src) {
    ret = src;
    src = NULL;
  }
  return ret;
}

char * trimSpaces (char * str) { 
  char * end; 
  // Trim leading space
    while(isspace((unsigned char)*str)) {
      str++;
    } 

    if(*str == 0) { //In case the entire string is just spaces
      return str;
    }  

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) {
      end--;
    }

    // Write new null terminator
    *(end+1) = 0;

    return str;
}

int main(int argc, char ** argv){

	if (argc<3 || argc>7){
		fprintf(stderr, "%s\n","Invalid arguments entered." );
	}

	int i;
	char * currDir = getcwd(0,0);
	char * outputDir = getcwd(0,0);
	char * columnName;
	int check; 

	for(i=0;i<argc;i++){
		if(strcmp("-c",argv[i])==0){
			columnName=argv[i+1];
			columnToSort=columnCheck(columnName);
		}
		if(strcmp("-d",argv[i])==0){
			currDir = argv[i+1];
		}
		if(strcmp("-o",argv[i])==0){
			outputDir = argv[i+1];
		}
	}

	allThreads=(pthread_t *)malloc(sizeof(pthread_t)*1024);
	parameters=(struct threadingVars * ) malloc (sizeof(Variables)*1024);

	directory(currDir);
	printf("Initial PID: %ld\n", allThreads[0]);
        printf("TIDS of all child threads:");
        for(i=0; i<threadIndex; i++) {
                printf("%ld, ", allThreads[i]);
                pthread_join(allThreads[i],NULL);
        }
    printf("\nTotal number of threads: %d\n",threadIndex);
    mergeSort(movies,columnToSort,0,counter-1);
    printfile(movies,outputDir,counter,columnName);

    pthread_mutex_destroy(&lock);

    return 0;
}
