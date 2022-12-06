# Bass-Cat

PROJECT REQUIREMENTS
- polymorphism found in BattleScores.cpp / calculateScore()
- many functions are modularized well but some still exceed 50 lines

HOW TO PLAY

1. Menu
Select menu options with number keys

2. Calibrate
At the end of the simple drum intro, press [Space] to line up the game with the music
The calibration menu says press [Esc] to retry but I forgot that's also the key to close
the window and I have not updated it

3. Menu
Player 1 press [1, 2, 3, 4] to select options
Player 2 press [H, J, K, L] to select options
Both players will select options at the same time, similar to rock paper scissors
Immediately once the menu closes, input begins

Combat Options:
ATTACK
    Match your input to the DRUMS
    Effect: deal damage based on your rhythm score
BLOCK
    Match your input to the PIANO
    Effect: reduce incoming opponent damage, might be nice if they're using a MAGIC ATTACK
BUILD METER
    Match your input to the BASS
    Effect: build meter which can be spent to use MAGIC ATTACK
MAGIC ATTACK
    Match your input to the SAX
    Effect 1: deal high damage by expending meter
    Effect 2: if meter is empty, deal damage by expending your own health

4. Input
Match your input to the appropriate instrument
Input lasts for 2 measures of music
Input ends when the menu reappears
Warning: if your chosen instrument isn't playing at the time of input, you will have no effect
         Be smart about when to choose attacks based on the state of the song
Input may be difficult considering that there is no visual stimulus representing incoming notes
at this current time

5. Effect
Health bars and special meters will update at the end of input

6. Victory
Results screen will show at the end of battle
Press [Esc] to exit game