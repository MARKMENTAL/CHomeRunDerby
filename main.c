#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void hitscenarios(int hrlength){
    if (hrlength == 0){printf("The batter swings and misses...\n");}
    if (hrlength < 100){printf("A poorly hit ground ball rolls forward...\n");}
    if (hrlength > 100 && hrlength < 200){printf("A decently hit ball flies over the inner outfield...\n");}
    if (hrlength > 200 && hrlength < 300){printf("A nicely hit ball flies over the outfield...\n");}
    if (hrlength > 300 && hrlength < 400){printf("The batter swings hard and the ball is hit deep into the outfield.. Will it be a home run?...\n");}
    if (hrlength > 400){printf("The ball is absolutely crushed! It is a no doubt home run as it lands deep in the stands...\n");}
}


int homerunrng(int lower, int upper){
    // generates number between lower and upper parameters
    int num = (rand() % (upper - lower));
    return num;
}


int swing(int homeruns, int pitches)
{
    // sets seed for the pseudo rng
    srand(time(0));
    // 0 to 500ft is passed as a limit for the rng
    int hrlength = homerunrng(0,500);

    hitscenarios(hrlength);

    printf("The ball was hit %d feet. \n",hrlength);

    // if rng is greater than 350 its a home run
    if (hrlength > 350){
        homeruns+=1;
        printf("Its a home run! \n");
    }
    
    // triggers when rng is under or = to 350
    else{printf("Ball was not hit far enough to be a home run.\n");}

    pitches-=1;
    printf("Pitches Remaining: %i\n", pitches);
    return homeruns;
}


void hr(int homeruns, int pitches){
   printf("Home runs hit: %d\n", homeruns);
   printf("Pitches Remaining: %d\n", pitches);
}


void coregame(char choice, int homeruns, int pitches, int running, int highscore){
     while (running == 1){
        // setting program to stop running once pitches are depleted
        if (pitches == 1){running = 0;}
        printf("Welcome to CHomeRunDerby! press 0 to swing, 1 to check number of home runs and pitches remaining\n");
        // scanf needs a pointer to reassign choice thus &choice
        scanf("%s",&choice);
  
        // if choice is out of the given bounds end program
        if (choice != '0' && choice != '1' ) {printf("Invalid input, please follow the instructions\n");}
  
        // choice is being used to select a function that represents a game mode
        if(choice == '0'){
            homeruns = swing(homeruns, pitches);
            // depletes a pitch after the function has run
            pitches -= 1;
        }

        if(choice == '1'){hr(homeruns, pitches);}

    }

    // prints total home runs hit and comments on your performance
    printf("Final Score: %d\n", homeruns);


    if (homeruns > highscore){
        printf("Congratulaions! you got the high score. Try again if you think you can go higher.\n");
        highscore = homeruns;
    }

    if (homeruns > 5){printf("Congrats on the slugging!\n");}

    printf("Current High Score: %i\n", highscore);

    char restart;
    printf("Try Again?(y/n)\n");
    scanf("%s", &restart);

    // if char restart equals the yes choice then rerun coregame function to restart
    // most of the variables have changed in a way unintuitive to a new game
    // such as homeruns so most of them are re-initialized in the parameter
    if (restart == 'y' || restart == 'Y'){coregame(0,0,10,1,highscore);}

    char save;
    printf("Save Results to txt?(y/n) program will ask for each time you played\n");
    scanf("%s", &save);

    if (save == 'y' || save == 'Y'){
        FILE *fileprint;
        fileprint = fopen("scores.txt", "a+");
        fprintf(fileprint, "Home Run Derby Score: %i\n" , homeruns );
        fclose(fileprint);
    }

}


int main()
{
    // using unsigned variables because it uses less memory
    unsigned char choice;
    unsigned int homeruns = 0;
    unsigned int pitches = 10;
    unsigned int running = 1;
    unsigned int highscore = 0;
    coregame(choice,homeruns,pitches,running,highscore);
    return 0;
}