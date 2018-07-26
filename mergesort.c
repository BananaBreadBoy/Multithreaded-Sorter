#include "sorter_thread.h"

void mergeSort (record * movies, int target_col, int low, int high) { 
    int mid; 
    if (low < high) { 
        mid = low + (high - low)/2;
        mergeSort(movies, target_col, low, mid);
        mergeSort(movies, target_col, mid+1, high);
        merge(movies, low, mid, high, target_col);
    }
} 

void merge (record * movies, int low, int mid, int high, int target_col){

    char* temp1;
    char* temp2;
    int mergedSize = high - low + 1;
    record *temp = (record *)malloc(mergedSize * sizeof(record));
    int mergePos = 0;
    int leftPos = low;
    int rightPos = mid + 1;

    while (leftPos <= mid && rightPos <= high) { 

        switch (target_col) { 
            case 0: 
                if (strcmp(movies[leftPos].color, movies[rightPos].color) <= 0) { 
                    temp[mergePos++] = movies[leftPos++];
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                }
                break;
            case 1:
                if (strcmp(movies[leftPos].director_name, movies[rightPos].director_name) <= 0) { 
                    temp[mergePos++] = movies[leftPos++];
                }
                else { 
                temp[mergePos++] = movies[rightPos++];
                }
                break;
            case 2: 
                if (movies[leftPos].num_critic_for_reviews <= movies[rightPos].num_critic_for_reviews) { 
                  temp[mergePos++] = movies[leftPos++];
                }
                else { 
                temp[mergePos++] = movies[rightPos++];
                }
                break;
            case 3: 
                if (movies[leftPos].duration <= movies[rightPos].duration) { 
                   temp[mergePos++] = movies[leftPos++];
                }
                else { 
                temp[mergePos++] = movies[rightPos++];
                }
                break;
            case 4: 
                if (movies[leftPos].director_facebook_likes <= movies[rightPos].director_facebook_likes) { 
                    temp[mergePos++] = movies[leftPos++];
                }
                else { 
                temp[mergePos++] = movies[rightPos++];
                }
                break;
            case 5: 
                if (movies[leftPos].actor_3_facebook_likes <= movies[rightPos].actor_3_facebook_likes) { 
                    temp[mergePos++] = movies[leftPos++];
                }
                else { 
                temp[mergePos++] = movies[rightPos++];
                }
                break; 
            case 6:
                if (strcmp(movies[leftPos].actor_2_name, movies[rightPos].actor_2_name) <= 0) { 
                    temp[mergePos++] = movies[leftPos++];
                 
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                    
                }
                break; 
            case 7: 
                if (movies[leftPos].actor_1_facebook_likes <= movies[rightPos].actor_1_facebook_likes) { 
                    temp[mergePos++] = movies[leftPos++];
                 
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                    
                }
                break; 
            case 8: 
                if (movies[leftPos].gross <= movies[rightPos].gross) { 
                    temp[mergePos++] = movies[leftPos++];
                 
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                    
                }
                break;
            case 9: 
                if (strcmp(movies[leftPos].genres, movies[rightPos].genres) <= 0) { 
                    temp[mergePos++] = movies[leftPos++];
                 
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                    
                }
                break;
            case 10:
	            if (strcmp(movies[leftPos].actor_1_name, movies[rightPos].actor_1_name) <= 0) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            } 

	            break;  
            case 11:

                temp1 = strdup(movies[leftPos].movie_title);
                temp2 = strdup(movies[rightPos].movie_title);

                if(*temp1 == 34){ 

                size_t len = strlen(temp1);
                assert(len >= 2); // or whatever you want to do with short strings
                memmove(temp1, temp1+1, len-2);
                temp1[len-2] = 0;

                }

             if(*temp2 == 34){ 

                size_t len = strlen(temp2);
                assert(len >= 2); // or whatever you want to do with short strings
                memmove(temp2, temp2+1, len-2);
                temp2[len-2] = 0;

                }


                if (strcmp(temp1, temp2) <= 0) {
                    //printf("l-%s -- r-%s\n",movies[leftPos].movie_title,movies[rightPos].movie_title ); 
                    temp[mergePos++] = movies[leftPos++];
                 
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                    
                }
                break; 
            case 12: 
                if (movies[leftPos].num_voted_users <= movies[rightPos].num_voted_users) { 
                    temp[mergePos++] = movies[leftPos++];
                 
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                    
                }
                break; 
            case 13:
                if (movies[leftPos].cast_total_facebook_likes <= movies[rightPos].cast_total_facebook_likes) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break; 
            case 14: 
	            if (strcmp(movies[leftPos].actor_3_name, movies[rightPos].actor_3_name) <= 0) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break; 
            case 15:
	            if (movies[leftPos].facenumber_in_poster <= movies[rightPos].facenumber_in_poster) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break; 
            case 16: 
	            if (strcmp(movies[leftPos].plot_keywords, movies[rightPos].plot_keywords) <= 0) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break;
            case 17:
	            if (strcmp(movies[leftPos].movie_imdb_link, movies[rightPos].movie_imdb_link) <= 0) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break;  
            case 18:
	            if (movies[leftPos].num_user_for_reviews <= movies[rightPos].num_user_for_reviews) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break;
            case 19: 
	            if (strcmp(movies[leftPos].language, movies[rightPos].language) <= 0) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break; 
            case 20:
             	if (strcmp(movies[leftPos].country, movies[rightPos].country) <= 0) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break; 
            case 21: 
	            if (strcmp(movies[leftPos].content_rating, movies[rightPos].content_rating) <= 0) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break; 
            case 22: 
                if (movies[leftPos].budget <= movies[rightPos].budget) { 
                    temp[mergePos++] = movies[leftPos++];
                 
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                    
                }
                break; 
            case 23:
            	if (movies[leftPos].title_year <= movies[rightPos].title_year) { 
                    temp[mergePos++] = movies[leftPos++];
                 
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                    
                }
                break; 
            case 24: 
	            if (movies[leftPos].actor_2_facebook_likes <= movies[rightPos].actor_2_facebook_likes) { 
                    temp[mergePos++] = movies[leftPos++];
                 
                }
                else { 
                    temp[mergePos++] = movies[rightPos++];
                    
                }
                break;
            case 25:
	            if (movies[leftPos].imdb_score <= movies[rightPos].imdb_score) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break;
            case 26: 
	            if (movies[leftPos].aspect_ratio <= movies[rightPos].aspect_ratio) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break; 
            case 27: 
	            if (movies[leftPos].movie_facebook_likes <= movies[rightPos].movie_facebook_likes) { 
	                temp[mergePos++] = movies[leftPos++];
	                
	            }
	            else { 
	                temp[mergePos++] = movies[rightPos++];
	                
	            }

	            break; 
            default:
                printf("ERROR.\n");
                break;
        }
    }
    while (leftPos <= mid) { 
        temp[mergePos++] = movies[leftPos++]; 
    }
    while (rightPos <= high) { 
        temp[mergePos++] = movies[rightPos++];
    }

    assert(mergePos == mergedSize);

    for (mergePos = 0; mergePos < mergedSize; ++mergePos){
         movies[low + mergePos] = temp[mergePos];
     }

    free(temp);

}