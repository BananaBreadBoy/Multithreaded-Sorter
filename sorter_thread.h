#ifndef SORTER_H_
#define SORTER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

typedef struct row {
    char * color;
    char * director_name;
    int num_critic_for_reviews;
    int duration;
    int director_facebook_likes;
    int actor_3_facebook_likes;
    char * actor_2_name;
    int actor_1_facebook_likes;
    int gross;
    char * genres;
    char * actor_1_name;
    char * movie_title;
    int num_voted_users;
    int cast_total_facebook_likes;
    char * actor_3_name;
    int facenumber_in_poster;
    char * plot_keywords;
    char * movie_imdb_link;
    int num_user_for_reviews;
    char * language;
    char * country;
    char * content_rating;
    unsigned long int budget;
    int title_year;
    int actor_2_facebook_likes;
    double imdb_score;
    double aspect_ratio;
    int movie_facebook_likes;
} record; 

typedef struct threadingVars{
    char colname[500];
    char CSVpath[500];
    int colSort;
} Variables;

static const char* const movieColumns[] = { 
	"color", 
	"director_name", 
	"num_critic_for_reviews", 
	"duration",
    "director_facebook_likes",
    "actor_3_facebook_likes", 
    "actor_2_name",
    "actor_1_facebook_likes", 
    "gross", 
    "genres", 
    "actor_1_name",
    "movie_title", 
    "num_voted_users", 
    "cast_total_facebook_likes",
    "actor_3_name", 
    "facenumber_in_poster", 
    "plot_keywords",
    "movie_imdb_link", 
    "num_user_for_reviews", 
    "language",
    "country", 
    "content_rating", 
    "budget", 
    "title_year",
    "actor_2_facebook_likes", 
    "imdb_score", 
    "aspect_ratio",
    "movie_facebook_likes"
}; 

char * nulTok (char * str, char const * delims); 

char * trimSpaces (char * str); 

void mergeSort (record * movies, int target_col, int low, int high);

void merge (record * movies, int low, int mid, int high, int target_col);

int columnCheck(char * column); 

int isDirectory(char * path); 

void directory (char * path);

void * threadSort(void * sortParameters);

void sorter(char * csvfilepath);  

int checkpath(char * outputdir);

int validCSV(char * row);

void * threadDirectory (void * sortParameters);

void printfile (record * sortedfile, char * outputDir, int counter, char * columnName);

#endif