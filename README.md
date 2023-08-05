# tic-tac-toe
decided to build tictactoe again in c++

this project took a bit of time. 
for instance i first built the local tic tac toe that is in the final version on aug 2.
i used an incredible amount of help from cppforschool and it would be irresponsible to mention otherwise.

after this (aug 3) i decided to attempt to build one against the computer. again i used the main basics from the previous.
however with changing how the computer would respond. firstly, building if else statements to defend against a win.
afterwards i made it so the computer could win, and polished it. 

eventually i reached a problem with the computer choosing random. see what i intended was for the computer to play you as an 
advesary. so when you would choose anything other than the middle box, it would go for it. to create the most trouble. however when
creating a pc_rand() function i came across many problems. especially when overviewing others code, as i didn't know how to add it into
my program. i even learned a bit about recursive functions. however one stackoverflow comment mentioned to use it as a last option. and 
i knew i could write the function, however it always had a problem whether checking if the spot was already held by a mark. i also landed
on stackoverflow to create a vector and just list the possible moves there. i decided to make this vector a local one, one the function would
make every time as not to save any progress. this way each time the for loop plays, the function will only choose from those possible options.

this "random" problem spanned the entiretiy of aug 3 night and aug 4 morning.

now on aug 4, i decided to polish the game. and went into a rabbit hole of finishing it.

after solving the random problem, i developed an easy and hard mode. so the player could choose whether to play against random or the if-else
statements i had developed prior. to do this i just used if-else statements as usually and allowed for a new bool isRandom to determine.
- see previously i had finished the defend, win, and rand function (rand function at the time being 1,2,3,... if-else), that it would play each move.
  meaning i had to have bool modifers that would only go.
  i.e. if win plays, set victory = true, do not play defend function, do not play random function
       if win cannot play, victory = false, play defend function, set defend = true if possible,
       do or do not play random function based on defend.
these previous steps allowed for an easy add of the easy hard mode based on prior knowledge

after this i allowed for rematching. throughout my research, i was scared to add this because i saw many using classes and various functions
whereas mine just ran on a loop until a win or draw was found. 

to progress further, i seperately made the main gameplay loop into a seperate function and playing it once and than another time in a do-while loop.
this do-while loop was only played while restart=true. i created a seperate function to ask the user if they would want to play again. meaning it would start
again from the game function, asking easy or hard, and doing the gameplay loop until win != -1 and the function ran its course.

a little mistake here caused a lot of stress later, originally the code was similar to this ---

bool restart = false;

gameplay loop(){
...code...
}
ask for rematch(){
yes = true
no = false
}

do {
gameplay();
} while (restart == true);


so this is how i setup my code. and i guess while testing and debugging i never actually wanted to end the game right away.
anyway.

after this i developed to add local.
to do this i just made a local game function and made the necessary changes. which either meant making new variables to track
both games. or retracing my steps and using previous code to allow for local. 
anyway at a point i believed i was finished and i came across a bug. i could not stop the game right away. it would always do a restart, 
no matter my choice. i did plenty of cout << restarts (wouldn't be surprised if one is still in the code). anyway i couldn't solve it for a
good hour. until i decided just to remove first game and rematch function that runs naturally. and just initialize restart = false.

this ended up solving my problem.

thus ending my battle with this very beginner project.
although as one tiktok creator mentioned, this project is to teach me pointers and arrays. i believe i still have more to learn and to
be honest still don't know what pointers are. althought this project was fun to make. i came across many times where i rather do things my way first,
just to be different, and then ultimately using whatever resources i had to try and build it. 

i believe the final project has a good amount of polish. on to the next.
