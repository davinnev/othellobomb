# Othello Bomb
### Play Othello with a twist!

Group No.: 55  
Group members: ISTIMUR Kevin Indrayana (3035918701) | VALERIA Davinne (3035898913)  
Topic: Othello Bomb  
Link: https://github.com/davinnev/othellobomb  

Game Description:  
Othello is a two-player strategy board game played on a square uncheckered board. Players will take turns placing disks on the board (beginning with the player who has the black disc). Any disk of the opponent's color that is bounded by the current player's disk in the horizontal, vertical, or diagonal will be flipped over to the current player's color. When the board is full, or the user chooses to quit, the game is over. At the end of the game, the player with the most disks with his assigned color facing up is declared the winner. In this Othello game, there is a slight modification where there will be bombs placed on the map at random, which may benefit or harm the players.

Rules:
1. Players are allowed to determine the board size from 6x6 to 10x10 and must be an even number. The board shape is a square.
2. Aside from board size, players are also able to determine the number of bombs. There are 3 types of bomb:
      a. Bomb 1/The Evil Bomb: Once a player decides to put the disk on the square containing this bomb, the bomb will clear out all disks located in the 
         same column and row (e.g. if an evil bomb is located in (0, 4), all the disks on the first row and fifth column will be wiped out).
      b. Bomb 2/The Silly Bomb: Once a player decides to put the disk on the square containing this bomb, the bomb will reverse the disk color, applicable 
         to all the disks that have been placed on the board.
      c. Bomb 3/The Nice Bomb: Once a player decides to put the disk on the square containing this bomb, the player is allowed to make another move.
	       The bombs will be placed randomly and the number of three types of bomb might not be equal in a single round. The players are not allowed to know 
         the bombs’ location.
3. The game will begin by putting 4 disks in the middle of the board (2 white on top left and bottom right, 2 black on top right and bottom left).
4. The player with black disk will make the first move. If there is/are white disk(s) bounded by black disks on both sides, the player with black disk can 
   acquire the white disk(s) and make it/them black. The same applies for the player with white disk.
5. If one player no longer has any more possible move, the other player will continue moving until the opponent is possible to make a move again.
6. The game finishes when the board has been fully filled.
7. At the end of the game, the program will count the total number of black and white disks. The player with more disks wins.

Features:
1. Generation of random game sets or events:   
	We use stdlib.h library to use rand() function to generate random positions of the bombs which are 	distinct in every game (by using srand(time(NULL), time function from time.h library).
2. Data structures for storing game status:  
	We use 2D array for the board that will store the disk (denoted by either ◦ (unicode number: &#9702) or • (unicode number: &#8226)).
3. Dynamic memory management:   
	 User can choose the number of tiles for the board, then we will make a dynamic 2D array (using new) that will store the disks according to user  
   preferences .
4. File input/output (e.g., for saving personal record):  
	The program uses fstream library to utilize fin and fout in order to store the leaderboard. Every player name is unique, and if he/she wins the game and 
  beat his/her own personal record, the program will update the newest record in leaderboard.txt. If the name is not yet written in the leaderboard, the 
  program will add it. The fout process is very useful to write a new record, whereas fin is very useful to compare the previous and latest record.
  As the board size is uncertain, the program calculates how much of the board is filled by the winner's disk (in percentage).
5. Program codes in multiple files:   
	- The main file (main.cpp) which consists of the game flow from the beginning to the end will be separated into one separate file.
	- The mechanism and effect of Bomb1 (bomb1.cpp) and Bomb2 (bomb2.cpp) will be stored in different files.
	- The main file and the bomb files are linked using header files (bomb1.h and bomb2.h).

List of non-standard C++ Libraries:
None

Compilation and execution instructions:
1. Clone this repo to your local computer
2. Compile the program using Makefile on the terminal, by inserting commands:
   $ make othellobomb
      ...
   $ ./othellobomb
3. If you are prompted for board size, it means that the game have started successfully.

Additional notes:
1. Players
- Player 1 is the same as the player with white disk
- Player 2 is the same as the player with black disk
2. Bombs
- Bomb 1 is the same as The Evil Bomb
- Bomb 2 is the same as The Silly Bomb
- Bomb 3 is the same as The Nice Bomb
3. Some commit comments were added not directly when the commits are done, hence maybe they are not explicitly shown. You can check it in the "Commits" section.
