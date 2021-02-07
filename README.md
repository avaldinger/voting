Voting Apps
==== 

Two small applications written in C as part of the [![CS50 Badge](https://img.shields.io/badge/-CS50-red)](https://cs50.harvard.edu) class problem sets.

Table of content
----
* [General info](#general-info)
* [Setup](#setup)
* [Technologies](#technologies)

### General info

Voting simulator programs written in C. The applications can be used to simulate two different voting systems:
 * Plurality: In this version voters can only vote for one candidate and the candidate with the most votes wins the election. If multiple candidates received the highest amount of votes the election ends in a tie.
 * Runoff: This program simulates a ranked-choice voting system:
    * Each voter can vote for 3 candidates
    * If one of the candidates have at least 50% of the votes the candidate wins the election
    * If that's not the case a run-off election follows
    * The candidate with the fewest number of votes gets eliminated
    * The 2nd ranked candidate gets the extra vote for that ballot
    * The run-off repeats itself until there is a winner or the election end in a tie


### Setup

The application can be run locally or using the [![CS50 Badge](https://img.shields.io/badge/-CS50-red)](https://cs50.harvard.edu) <a href="https://ide.cs50.io">IDE</a> after logging in with your GitHub account.

To run the program:
 1. It needs to be compiled: 
  * `$ make plurality.c`
  * `$ make runoff.c`
 2. Started with the names of the candidates as arguments: 
  * `$ ./plurality candidates names`
  * `$ ./runoff candidates names`
 3. Enter number of voters and vote: 
    * `Plurality: Number of voters: 3 - Vote: Candidate`
    * `Runoff: Number of voters: 5 - Rank 1: Candidate1  Rank 2: Candidate2 Rank 3: Candidate3`
 
### Technologies
 
 Libraries:
 * stdio.h
 * <a href="https://github.com/cs50/libcs50">cs50.h</a>
 * string.h
 * ctype.h
 * stdlib.h
 * [![C](https://img.shields.io/badge/-C-blue)](https://www.cprogramming.com/)
