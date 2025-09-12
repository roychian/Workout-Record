#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>

#define MOVE_LEN 30

typedef struct wish_node
{
    char name[MOVE_LEN];
    int sets, weight, number;
    struct wish_node *next;
}wish;

void add_record();
void feedback(int index_of_date,int index_of_move);
void print_record(int month, int day);
void sort_record();

wish *add_bucketlist(wish *wish_list, char *word, int sets, int weight);
wish *delete_bucketlist(wish *wish_list, char *word);
void search_bucketlist(wish *wish_list,int class);
void print_bucketlist(wish *wish_list);
void sort_bucketlist(wish *wish_list);


int level;
int NUM_OF_MOVE=24;

//structure
struct move
{
    int label;
    char name[MOVE_LEN];
    int set, weight, number;
};
struct diet_record
{
    int carbon, protein, water; // Records the intake of carbohydrates, protein, and water for the day
};
struct record
{
    int month, day,move_count;
    struct move move[10];
    struct diet_record diet;
};
//structure


//external
struct record training_record[100];
wish *my_wishlist=NULL;
struct move all_move[50];
//external



int main(int argc, char *argv[])
{
    


    //====================================setup initial data====================================
    FILE *FILE_check_move=fopen("./data.txt","a+");
    if(FILE_check_move==NULL)
    {
        printf("(fail)\n");
    }
    int i=0;
    while(fscanf(FILE_check_move,"%d %s %d %d %d",&all_move[i].label,&all_move[i].name,&all_move[i].set,&all_move[i].weight,&all_move[i].number)!=EOF)
    {
        i++;
    }
    //====================================setup initial data====================================

    //====================================Beginning & enter body data====================================
    int operation;
    int body_weight;
    float height,bodyfat;
    float ffmi;

    printf("==============================================>\n");//add in begining of any part 
    printf("Welcome to the \"Fitness Advisor\"!");
    printf(" Our goal is to help you:\n(1)Arrange the training schedule.\n(2)Record your training life.\n(3)Give feedback to approve your training.\n\n");
    printf("Before start you training life,we want to know your exercise goal and your body strengh.\n");
    printf("Please enter you height, weight and bodyfat(percentage%%) so we can calculate the appropriate load and sets for you!\n");
    printf("(We will use your weight and bodyfat to calculate the FFMI: (weight-weight*bodyfat)/height^2 )\n") ;
    
    printf("==============================================>\n");
    printf("Please enter your weight(kg), height(cm) and bodyfat(%%) respectively.\n");
    scanf("%d %f %f",&body_weight,&height,&bodyfat);
    bodyfat/=100;
    height/=100;
    ffmi=(body_weight-(body_weight*bodyfat))/((height)*(height));
    printf("Your FFMI is %d",(int)ffmi);
    (ffmi<17) ? printf("(weak).\n") : (17<=ffmi && ffmi<=21) ? printf("(normal).\n") : printf("(strong).\n");

    printf("==============================================>\n");
    printf("Please enter the level you want for training\n");
    printf("(1)Keep healthy with appropriate exercise!\n");
    printf("(2)Become stronger with advanced training!\n");
    printf("(3)Push the envelope!Challenge your body!\n");
    while(1)
    {
        scanf("%d",&level);
        if(level>=3 && level<=1)
        {
            printf("Please choose the level from 1 to 3!\n");
        }
        else
        {
            break;
        }
    }
    printf("You choose the level %d!\n",level);
    //====================================beginning & enter body data====================================


    //====================================set weight with level and FFMI====================================
    for (int i = 0; i < 24; i++)
    {
        all_move[i].weight*=(ffmi<17) ? 1 : (17<=ffmi && ffmi<=21) ? 1.5 : 2;
    }
    for (int i = 0; i < 24; i++)
    {
        all_move[i].weight*=(level==1) ? 1 : (level==2) ? 1.5 : 2 ;
        all_move[i].weight-=all_move[i].weight%5;
    }
    //====================================set weight====================================



    while(1)//====================================main proggram====================================
    {
        printf("==============================================>\n");
        printf("You are in the menu.\n");
        printf("Which operaion you want to do?\n");
        printf("....[1] check all movements\n");
        printf("....[2] check the training record\n");
        printf("....[3] check the bucketlist\n");
        printf("....[4] exit\n");
        while(scanf("%d",&operation) && (operation<=0 || operation >=5))//invalid operation
        {
            printf("Please choose operation from 1 to 4 !\n");
            printf("Which operaion you want to do?\n");
            continue;
        }
        
        //====================================end whole proggram====================================
        if(operation==4)
        {
            printf("Wish you become healthier and stronger!\n");
            printf("==============================================>\n");
            exit(1);
        }
        //====================================end whole proggram====================================

        //====================================check movements====================================
        if(operation==1)
        {
            printf("==============================================>\n");
            printf("You can check all movements now !\n");
            printf("Movements are classify into the following six class:\n");
            printf("....[1] Chest\n");
            printf("....[2] Leg\n");
            printf("....[3] Back\n");
            printf("....[4] Shoulder\n");
            printf("....[5] Arm\n");
            printf("....[6] Core exercise\n");
            printf("You can enter [7] to add bucketlist,\n");
            printf("[8] to add record and [9] to back to the menu.\n");
            while(1)//choose which part to check
            {
                printf("Please choose which part you want to check (1 ~ 6) and 7,8,9 for other action\n");
                scanf("%d",&operation);
                if(operation>=10 || operation<=0)//invalid operation
                {
                    printf("Please choose operation from 1 to 9 !\n");
                    continue;
                }
                else if(operation==9)
                {
                    printf("(Quit checking the movement!)\n");
                    break;
                }
                else if(operation<7 && operation>0)
                {
                    char part[10];
                    printf("All movement of \n");
                    if(operation>=1 && operation<=3)//chest to back
                        operation==1? strcpy(part,"chest"):(operation==2? strcpy(part,"Leg"):strcpy(part,"Back"));
                    else//shoulder to body
                        operation==4? strcpy(part,"Shoulder"):(operation==5? strcpy(part,"Arm"):strcpy(part,"Core"));
                    printf("----------Name-----------Sets---Weight---Reps--\n");
                    for (int i = 0 ; i < NUM_OF_MOVE; i++)
                    {
                        if(all_move[i].label==operation)
                        {
                            printf("%-25s %d %8d %7d\n", all_move[i].name,all_move[i].set,all_move[i].weight,all_move[i].number);
                            //up to 25 character
                        }
                        
                    }
                    printf("-----------------------------------------------\n");
                    printf("(Please close the windows to continue the proggram.)\n");
                    //====================================set SDL====================================
                    SDL_Init(SDL_INIT_VIDEO);
                    SDL_Window* window = SDL_CreateWindow("Movement Demonstration", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, 0);
                    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


                    char imagePath[256];
                    sprintf(imagePath, "./pictures/%s%d.png",part, 1); // Update the path based on the frame number
                    SDL_Surface* imageSurface=IMG_Load(imagePath);
                    if (imageSurface == NULL) {
                        printf("Failed to load image: %s\n", IMG_GetError());
                        return 1;
                    }

                    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
                    SDL_FreeSurface(imageSurface);


                    int windowWidth=720;
                    int windowHeight=480;
                    SDL_Rect srcRect; // Source rectangle for the image

                    
                    srcRect.x = 0;
                    srcRect.y = 0;
                    srcRect.w = imageSurface->w; // Width of the image
                    srcRect.h = imageSurface->h; // Height of the image

                    SDL_Rect dstRect; // Destination rectangle for rendering
                    dstRect.x = 0;
                    dstRect.y = 0;
                    dstRect.w = windowWidth; // Width of the window
                    dstRect.h = windowHeight; // Height of the window

                    // Calculate the scaling factor for the image
                    float scaleX = (float)dstRect.w / srcRect.w;
                    float scaleY = (float)dstRect.h / srcRect.h;

                    // Calculate the scaled dimensions of the image
                    int scaledWidth = srcRect.w * scaleX;
                    int scaledHeight = srcRect.h * scaleY;

                    // Center the scaled image within the window
                    dstRect.x = (windowWidth - scaledWidth) / 2;
                    dstRect.y = (windowHeight - scaledHeight) / 2;
                    dstRect.w = scaledWidth;
                    dstRect.h = scaledHeight;

                    // Render the scaled image
                    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);

                    //====================================set SDL====================================

                    

                    SDL_Event event;
                    int currentFrame = 0;
                    int totalFrames = 3; // Total number of frames in the animation
                    int running=1;
                    int change=1;
                    //end create window
                    while (running) 
                    {
                        
                        while (SDL_PollEvent(&event)) {
                            if (event.type == SDL_QUIT) {
                                running=0;
                                break;
                            }
                        }
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
                        
                        SDL_RenderPresent(renderer);
                        SDL_Delay(500); // Adjust the delay to control the animation speeds

                        currentFrame = (currentFrame + change);
                        // Update the image frame
                        if(currentFrame==3)
                            change=-1;
                        else if(currentFrame==1)
                            change=1;
                        
                        
                        sprintf(imagePath, "./pictures/%s%d.png",part, currentFrame); // Update the path based on the frame number
                        imageSurface = IMG_Load(imagePath);
                        SDL_DestroyTexture(texture);
                        texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
                        SDL_FreeSurface(imageSurface);
                    }
                    SDL_DestroyTexture(texture);
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();

                }
                else if(operation==7)//add bucketlist
                {

                    printf(">---------------------------------------------<\n");
                    printf("Add new bucketlist!\n");
                    int count;
                    printf("Enter the number of data you want to add:\n");
                    scanf("%d",&count);
                    for(int i=0;i<count;i++)
                    {
                        printf("Please enter the name of movement, sets and load you wish to do.\n");
                        char tem_name[MOVE_LEN];
                        int tem_weight,tem_sets;
                        scanf("%s %d %d",&tem_name,&tem_sets,&tem_weight);
                        my_wishlist=add_bucketlist(my_wishlist,tem_name,tem_sets,tem_weight);
                    }
                    printf(">---------------------------------------------<\n");
                    
                }
                else if(operation==8)//add record
                {
                    add_record();
                }
            }//choose which part to check
        }
        //====================================check movements====================================

        //====================================training record====================================
        else if(operation==2)
        {
            printf("==============================================>\n");
            printf("You can check your training records and add new records here!\n");
            while(1)//choose which part to check
            {
                printf("Which action you want to do\n");
                printf("....[1] Add new record\n");
                printf("....[2] Check the record\n");
                printf("....[3] Sort a record\n");
                printf("You can enter [4] to back to the menu\n");
                while(scanf("%d",&operation) && (operation>=5 || operation<=0))
                {
                    printf("Please choose operation from 1 to 4 !\n");//invalid operation
                }
                if(operation==4)
                {
                    printf("(Quit record system!)\n");
                    break;
                }
                else if(operation==1)//add record
                {
                    add_record();
                }
                else if(operation==2)//print record
                {
                    int month,day;
                    printf("-----------------------------------------------\n");
                    printf("Enter the month and day you want to check(EX 6 15)\n");
                    scanf("%d %d",&month,&day);
                    print_record(month,day);
                }
                else if(operation==3)
                {
                    sort_record();
                }

            }
        }
        //====================================training record====================================

        //====================================bucketlist====================================
        else if(operation==3)
        {
            printf("==============================================>\n");
            printf("You can manage and check your bucketlist here!\n");
            while(1)
            {
                printf("Which action you want to do?\n");
                printf("....[1] Add new bucketlist\n");
                printf("....[2] Delete a bucketlist\n");
                printf("....[3] Search a bucketlist\n");
                printf("....[4] Check the bucketlist\n");
                printf("You can enter [5] to back to the menu\n");
                while(scanf("%d",&operation) && (operation>=6 || operation<=0))
                {
                    printf("Please choose operation from 1 to 5 !\n");//invalid operation
                }
                if(operation==5)
                {
                    printf("(Quit bucketlist system!)\n");
                    break;
                }
                if(operation==1)
                {
                    printf(">---------------------------------------------<\n");
                    printf("Add new bucketlist!\n");
                    int count;
                    printf("Enter the number of data you want to add:\n");
                    scanf("%d",&count);
                    for(int i=0;i<count;i++)
                    {
                        printf("Please enter the name of movement, sets and load you wish to do.\n");
                        char tem_name[MOVE_LEN];
                        int tem_weight,tem_sets;
                        scanf("%s %d %d",&tem_name,&tem_sets,&tem_weight);
                        my_wishlist=add_bucketlist(my_wishlist,tem_name,tem_sets,tem_weight);
                    }
                    printf(">---------------------------------------------<\n");
                }
                else if(operation==2)
                {
                    printf(">---------------------------------------------<\n");
                    printf("Delete a bucketlist!\n");
                    printf("Enter the name of movement and delete it if it exist.\n");
                    char tem_name[MOVE_LEN];
                    scanf("%s",&tem_name);
                    my_wishlist=delete_bucketlist(my_wishlist,tem_name);
                }
                else if(operation==3)
                {
                    printf(">---------------------------------------------<\n");
                    printf("Search a bucketlist!\n");
                    printf("Enter the name of movement class.\n");
                    printf("....[1] Chest [2] Leg [3] Back [4] Shoulder [5] Arm [6] Core\n");
                    int tem_class;
                    scanf("%d",&tem_class);
                    search_bucketlist(my_wishlist,tem_class);
                }
                else if(operation==4)
                {
                    printf(">---------------------------------------------<\n");
                    printf("Check a bucketlist!\n");
                    printf("Here is your bucketlist:\n");
                    print_bucketlist(my_wishlist);
                }

                /*
                else if(operation==5)
                {
                    printf(">---------------------------------------------<\n");
                    sort_bucketlist(my_wishlist);
                    printf("The bucketlist has been sorted by part !\n");
                    printf("Want to check right now?\n");
                    printf("[1] Yes [2] No\n");
                    if(operation==1)
                    {
                        printf("-----------------------------------------------\n");
                        printf("Check a bucketlist!\n");
                        printf("Here is your bucketlist:\n");
                        print_bucketlist(my_wishlist);
                    }
                }*/
                
            }
            
        }
        //====================================bucketlist====================================
    }
    
}

void add_record()
{
    printf(">---------------------------------------------<\n");
    printf("Add new record.\n");
    printf("Please enter the month and day(EX: 6 15)\n");

    // Enter new training record
    struct record new_record;

    //training_record.move_count=0;
    scanf("%d %d", &new_record.month, &new_record.day);

    printf("Enter the number of data (up to 10 per day):\n");
    scanf("%d", &new_record.move_count);
    printf("-----------------------------------------------\n");
    // Validate the input
    if (new_record.move_count < 1 || new_record.move_count > 10)
    {
        printf("Invalid number of sets. Please enter a value between 1 and 10.\n");
        return;
    }

    for (int i = 0; i < new_record.move_count; i++)
    {
        printf("Enter the %d-th data\n",i+1);
        printf("Enter the movement name, sets, load and repetitions:\n");
        scanf("%s", &new_record.move[i].name); // Enter move
        scanf("%d", &new_record.move[i].set); // Enter set
        scanf("%d", &new_record.move[i].weight); // Enter weight
        scanf("%d", &new_record.move[i].number); // Enter number
    }

    int operation;
    printf("Done! Do you want to record the diet diary?\n");
    printf("[1]Yes [2]No,finish adding record.\n");
    
    while(1)
    {
        scanf("%d",&operation);
        if(operation>=3 && operation<=0)
        {
            printf("Please choose operation from 1 to 2 !\n");
            continue;
        }
        else if(operation==2)
        {
            new_record.diet.carbon=0;
            new_record.diet.protein=0;
            new_record.diet.water=0;
            printf("(Finish adding.)\n");
            printf("-----------------------------------------------\n");
            break;
        }
        else
        {
            printf("Enter the carbohydrate(g),protein(g) and water(ml) you intake that day.");
            printf("(EX:300 40 2000)\n");
            scanf("%d %d %d", &new_record.diet.carbon,&new_record.diet.protein,&new_record.diet.water); // Enter carbohydrate,protein,waterintake
            printf("Done!\n");
            printf("-----------------------------------------------\n");
            break;
        }
    }
    

    

    // Add the new training record to the training log
    int i;
    for (i = 0; i < 100; i++)
    {
        if (training_record[i].month == 0 || training_record[i].day == 0)
        {
            training_record[i] = new_record;
            break;
        }
    }

    printf("Feed back:\n");
    for(int j=0;j<new_record.move_count;j++)
    {
            feedback(i,j);//i:today,j:the movement;
    }
    printf(">---------------------------------------------<\n");
    // Call the feedback function to provide feedback
}
void feedback(int index_of_date,int index_of_move)
{
    int prev_index = index_of_date - 1;
    int rest_days = 30*(training_record[index_of_date].month - training_record[prev_index].month)+training_record[index_of_date].day - training_record[prev_index].day;
    int my_volume=training_record[index_of_date].move[index_of_move].set*training_record[index_of_date].move[index_of_move].weight*training_record[index_of_date].move[index_of_move].number;
    int expected_volume;

    //get expected_volume
    for(int i=0;i<NUM_OF_MOVE;i++)
    {
        if(strcmp(training_record[index_of_date].move[index_of_move].name,all_move[i].name)==0)
        {
            training_record[index_of_date].move[index_of_move].label=all_move[i].label;
            expected_volume=all_move[i].number*all_move[i].set*all_move[i].weight;
            break;
        }
    }
    //get expected_volume

    //volume feedback
    if(my_volume<(expected_volume/2))//too light
    {
        printf("The expeced volume of \"%s\" is %d (your training volume is %d,too low),enhance the intensity!\n",training_record[index_of_date].move[index_of_move].name,expected_volume,my_volume);
    }
    else if(my_volume>expected_volume*2)
    {
        printf("The expeced volume of \"%s\" is %d (your training volume is %d,too high),decrease the intensity!\n",training_record[index_of_date].move[index_of_move].name,expected_volume,my_volume);
    }
    else
    {
        printf("The expeced volume of \"%s\" is %d (your training volume is %d,normal).Keep going!\n",training_record[index_of_date].move[index_of_move].name,expected_volume,my_volume);
    }
    //volume feedback

    if (index_of_date > 0)
    {

        // Find the previous training record for the same body part
        int same_body_part_index = -1;
        for (int i = prev_index; i >= 0; i--)//run all training record
        {
            for (int j = 0; j < training_record[prev_index].move_count; j++)
            {
                // Compare the labels of training movements
                //index_of_date: today,i: latest day with same class,j:the move
                if (training_record[index_of_date].move[index_of_move].label == training_record[i].move[j].label)
                {
                    same_body_part_index = i;
                    break;
                }
            }

            //rest day
            if (same_body_part_index != -1)
            {
                int rest_days_since_last_same_body_part = training_record[index_of_date].day - training_record[same_body_part_index].day-1;
                
                //rest day
                // Assuming the expected rest days is 1
                const char *part[6] = {"Chest", "Legs", "Back", "Shoulders", "Arms", "Core"};
                //printf("(rest day:%d)",rest_days_since_last_same_body_part);
                if (rest_days_since_last_same_body_part < level)//need rest
                {
                    printf("....WARING!! You trained \"%s\" too hard! Please Take some break!!\n",part[training_record[index_of_date].move[index_of_move].label-1]);
                }
                else
                {
                    printf("You have enough rest on %s.\n",part[training_record[index_of_date].move[index_of_move].label-1]);//no need rest
                }
                break;
            }
            //rest day
        }

        // Assuming the expected rest days is 1
    }
    else
    {
        //printf("No previous training record found. Keep up the good work!\n");
    }
}
void print_record(int month, int day)
{
    // Input a date and output the training records for that date  
    for (int i = 0; i < 100; i++)
    {
        if (training_record[i].month == month && training_record[i].day == day)
        {
            // Found a matching record
            printf(">----------------------------------------------<\n"); 
            printf("Here is the training Record on %d/%d:\n", month, day);
            // Output the training records for that date

            printf("----------Name-----------Sets---Weight---Reps--\n");
            for (int j = 0; j < training_record[i].move_count; j++)
            {
                
                printf("%-25s %d %8d %7d\n", training_record[i].move[j].name,training_record[i].move[j].set,training_record[i].move[j].weight,training_record[i].move[j].number);       
            }
            printf("-----------------------------------------------\n"); 

            printf("Diet record:\n");
            printf("Carbon Intake  %dg\n", training_record[i].diet.carbon);
            printf("Protein Intake %dg\n", training_record[i].diet.protein);
            printf("Water Intake   %dml\n", training_record[i].diet.water);
            printf(">----------------------------------------------<\n"); 
            return;
        }
    }
    printf("(No training record on %d/%d.)\n", month, day);
}
void sort_record()
{
    printf(">----------------------------------------------<\n"); 
    printf("Sort a record by body_part!\n");
    printf("Enter the month and day(EX: 6 15)\n");
    int month,day;
    scanf("%d %d",&month,&day);
    int index;
    for(index=0;index<100;index++)
    {
        if(training_record[index].month==month && training_record[index].day==day)
        {
            break;
        }
    }
    if(index==100)
    {
        printf("No record on %d/%d!\n",month,day);
        return;
    }  
    for(int i=0;i<training_record[index].move_count-1;i++)
    {
        for(int j=0;j<training_record[index].move_count-1;j++)
        {
            if(training_record[index].move[j].label > training_record[index].move[j+1].label)
            {
                struct move tem=training_record[index].move[j];
                training_record[index].move[j]=training_record[index].move[j+1];
                training_record[index].move[j+1]=tem;
            }
        }
    }
    printf("Record has been sorted by body_part!\n");
    printf("Want yo check now?\n");
    printf("[1] Yes [2] No\n");
    int op;
    scanf("%d",&op);
    if(op==1)
    {
        print_record(month,day);
        return;
    }
    printf(">----------------------------------------------<\n"); 
}

wish *add_bucketlist(wish *wish_list, char *word, int sets, int weight)
{
    wish *new_wish = malloc(sizeof(wish));//new node

    //set the label
    for(int i=0;i<NUM_OF_MOVE;i++)
    {
        if(strcmp(word,all_move[i].name)==0)//find the data
        {
            new_wish->number=all_move[i].label;
            break;
        }
        new_wish->number=6;
    }
    //set the label

    if(wish_list == NULL)//first wish_list
    {
        strcpy(new_wish->name,word);
        new_wish->sets = sets;
        new_wish->weight = weight;

        new_wish->next=NULL;
        wish_list = new_wish;
        printf("Successfully Added !\n");
        
        return new_wish;

    }

    //other input 
    new_wish->next=wish_list;
    strcpy(new_wish->name, word);
    new_wish->sets = sets;
    new_wish->weight = weight;
    
    printf("Successfully Added !\n");
    return new_wish;
    
}
wish *delete_bucketlist(wish *wish_list, char *word)
{
    wish *prev = NULL, *cur;
    for (cur = wish_list; cur != NULL && strcmp(cur->name, word) != 0; prev=cur, cur = cur->next);//find the movement
    if(cur==NULL)
        {
            printf("There isn't %s in bucketlist!",word);
            return wish_list;
        }
    if(prev==NULL)
    {
        wish_list = wish_list->next;
        return wish_list;
    }
        
    else
        prev->next = cur->next;
    return wish_list;
    free(cur);//
    printf("Done!\n");
    printf("-----------------------------------------------\n");
}
void search_bucketlist(wish *wish_list,int class)
{
    //find the same class of int "class"
    wish *cur = wish_list;
    int find_suc=0;
    for (cur = wish_list; cur != NULL; cur = cur->next)
    {
        if (cur->number==class)//find it
        {
            if(find_suc==0)
            {
                printf("Here is the movement you wish to do:\n");
                printf("----------Name-----------Sets---Weight--\n");//find the same class
                find_suc=1;
            }
            printf("%-25s %d %8d\n",cur->name,cur->weight,cur->sets);
        }
    }
    if(find_suc==0)//no found
    {
        const char *part[6] = {"Chest", "Legs", "Back", "Shoulders", "Arms", "Core"};
        printf("No bucketlist of class %s.\n",part[class-1]);
    }
    printf(">---------------------------------------------<\n");   
    return;
    
}
void print_bucketlist(wish *wish_list)
{
    const char *part[6] = {"Chest", "Legs", "Back", "Shoulders", "Arms", "Core"};
    wish *cur = wish_list;
    printf("----------Name-----------------Class----Sets---Weight--\n");   
    for (cur = wish_list; cur != NULL; cur = cur->next)
    {
        printf("%-25s %10s %6d %7d\n", cur->name,part[cur->number-1],cur->sets,cur->weight);
    }
    printf(">---------------------------------------------<\n");   
}
void sort_bucketlist(wish *wish_list)
{
    wish *cur = wish_list;
    for (cur = wish_list; cur->next != NULL; cur = cur->next)
    {
        if(cur == NULL)
            break;
        else if(cur->number == cur->next->number)
            continue;
        else if(cur->number > cur->next->number)
        {
            wish *temp = cur->next;
            cur->next = cur;
            cur = temp;
        }
    }
    printf("Sort Done !\n");
}
