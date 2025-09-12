# FP
This proggram is "Fitness Advisor",produced by team 14(banana_screaming).  
To execute the proggram,download the files,and open the file "FP-main\FP-main" in vscode,  
and compile it with "gcc -I src/include -L src/lib -o run FP_MAIN.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image",  
which will generate the "run.exe".And you can execute the proggram with that.

# Proggram structure
The proggram is divided into 4 part,initial profile,check all movement,training record and buckerlist.
1. initial profile
    enter some profile to setup the appropriate data of movement.
2. check all movement
    you can check all movement that are classified into six class(chest,leg,back,shoulder,arm,core).  
    There is a SDL window to demonstrate these movements.  
    (WARING! You have to close the SDL window before continue the proggram.)  
    You can also add record and add bucketlist here.
3. training record
    You can add record,output your record and sort it here.  
    After input the record,we will give you feedback about your training intensity and training frequency.  
    You can sort your data with the six class of movement.  
    (WARING! You can only input the data in order of     time(namely,next input will be at least one day after the last input).)
4. bucket list
    you can add bucketlist,delete bucketlist,search a class of movement in bucketlist,output all bucketlist here.