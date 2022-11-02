Names: Minh Le, Chang Jin

Our tournament bot name: LEXI

Evaluation function: Until it reach the states where there are 3 or more in a row, most of it would just be 1 or 2 in a row. Since the 0 around it counts as a potential move, disregarding the turn, each 0 would be count towards the streak as a "potential score" for the players.

The cases that are meant to be test are case where there are only one move left for each player which will lead to a draw by having the same score > 0 (ensuring it is making an efficient choice), an empty board, and a board with obsticles.

Noteworthy resource: No, except for the slides which help me visualized the functions.

Other notes: everything seems to be working fine