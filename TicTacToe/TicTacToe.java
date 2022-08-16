import java.util.Scanner;

public class TicTacToe {

    public static String[][] addMove(String[][] table, int rowChosen, int colChosen, int playerNum) {
        int rowSelected = 0;
        int colSelected = 0;
        
        if (rowChosen == 1) {
            rowSelected = 0;
        }
        else if (rowChosen == 2) {
            rowSelected = 2;
        }
        else if (rowChosen == 3) {
            rowSelected = 4;
        }

        if (colChosen == 1) {
            colSelected = 0;
        }
        else if (colChosen == 2) {
            colSelected = 2;
        }
        else if (colChosen == 3) {
            colSelected = 4;
        }

        if (playerNum == 1) {
            table[rowSelected][colSelected] = "X";
        }
        else {
            table[rowSelected][colSelected] = "O";
        }
        return table;
    }

    public static void printTable(String[][] table) {
        for (int i = 0; i < 5; i++) {
            for (int n = 0; n < 5; n++) {
                if (table[i][n] == null) {
                    table[i][n] = " ";
                }
                System.out.print(table[i][n]);
            }
            System.out.println();
        }
    }

    public static boolean checkEmpty(String[][] table, int rowChosen, int colChosen) {
        int rowSelected = 0;
        int colSelected = 0;
        
        if (rowChosen == 1) {
            rowSelected = 0;
        }
        else if (rowChosen == 2) {
            rowSelected = 2;
        }
        else if (rowChosen == 3) {
            rowSelected = 4;
        }

        if (colChosen == 1) {
            colSelected = 0;
        }
        else if (colChosen == 2) {
            colSelected = 2;
        }
        else if (colChosen == 3) {
            colSelected = 4;
        }

        if (table[rowSelected][colSelected] == " ") {
            return true;
        } 
        else {
            return false;
        }
    }


    public static int winner(String[][] table) {
        int winner = 0;
        String lineOne = table[0][0] + table[0][2] + table[0][4];
        String lineTwo = table[2][0] + table[2][2] + table[2][4];
        String lineThree = table[4][0] + table[4][2] + table[4][4];
        String lineFour = table[0][0] + table[2][0] + table[4][0];
        String lineFive = table[0][2] + table[2][2] + table[4][2];
        String lineSix = table[0][4] + table[2][4] + table[4][4];
        String lineSeven = table[0][0] + table[2][2] + table[4][4];
        String lineEight = table[0][4] + table[2][2] + table[4][0];

        if (lineOne.equals("XXX") || lineTwo.equals("XXX") || lineThree.equals("XXX") || lineFour.equals("XXX")) {
            winner = 1;
        }
        else if (lineFive.equals("XXX") || lineSix.equals("XXX") || lineSeven.equals("XXX") || lineEight.equals("XXX")) {
            winner = 1;
        }
        if (lineOne.equals("OOO") || lineTwo.equals("OOO") || lineThree.equals("OOO") || lineFour.equals("OOO")) {
            winner = 2;
        }
        else if (lineFive.equals("OOO") || lineSix.equals("OOO") || lineSeven.equals("OOO") || lineEight.equals("OOO")) {
            winner = 2;
        }

        return winner;
    } 

    public static void main(String[] args) {

        int rows = 5;
        int columns = 5;
        String[][] table = new String[rows][columns];
        Scanner scan = new Scanner(System.in);
        String player1;
        String player2;
        int player1Row;
        int player1Col;
        int player2Row;
        int player2Col;
        int maxMove = 9;
        int currentMove = 0;

        // Setting up the layout of the board
        table[0][1] = " | ";
        table[0][3] = " | ";
        table[2][1] = " | ";
        table[2][3] = " | ";
        table[4][1] = " | ";
        table[4][3] = " | ";

        table[1][0] = "-";
        table[1][2] = "-";
        table[1][4] = "-";
        table[3][0] = "-";
        table[3][2] = "-";
        table[3][4] = "-";
        
        table[1][1] = " + ";
        table[1][3] = " + ";
        table[3][1] = " + ";
        table[3][3] = " + ";

        System.out.println("Welcome to TicTacToe 3x3 (java language version)!");
        System.out.println("This was made by Lê Anh Minh (Minh Le for short)");
        System.out.println("The rule is simple.");
        System.out.println("Choose the row and column you wish to place your piece.");
        System.out.println("Please enter integers for the row and column you want to place your piece.");
        System.out.println("The integers you enter should be between 1 and 3.");
        System.out.println("Otherwise, the input is invalid and your turn is skipped.");
        System.out.println("Player1 is X and player2 is O");
        System.out.println("Here is table for review: ");
        System.out.println();

        // Shows table
        printTable(table);

        System.out.println();
        System.out.println("Lets start by entering the name of players!");
        System.out.println();

        // Setting players' names
        System.out.print("Player1, enter your name: ");
        player1 = scan.nextLine();
        System.out.print("Player2, enter your name: ");
        player2 = scan.nextLine();
        System.out.println();

        while(true) {

            // Player1's turn
            System.out.println(player1 + ", enter your move: ");
            System.out.print("Row: ");
            player1Row = scan.nextInt();
            System.out.print("Column: ");
            player1Col = scan.nextInt();
            System.out.println();

            // Check if space is empty and valid
            if ((player1Row <= 3 && player1Col <= 3) && (player1Row >= 1 && player1Col >= 1) && (checkEmpty(table, player1Row, player1Col) == true)) {
                // If move is valids, add move to table
                addMove(table, player1Row, player1Col, 1);
                currentMove += 1;
            }
            else {
                System.out.println();
                System.out.println("Invalid move!");
                System.out.println("Your turn is skipped.");
            }

            // Showing the table after the move
            System.out.println();
            printTable(table);
            System.out.println();

            // Check if player1 won
            if (winner(table) == 1) {
                System.out.println(player1 + " won the game.");
                System.out.println();
                break;
            }

            // Check if there are space left in table
            if (currentMove >= maxMove) {
                break;
            }

            // Player2's turn
            System.out.println(player2 + ", enter your move: ");
            System.out.print("Row: ");
            player2Row = scan.nextInt();
            System.out.print("Column: ");
            player2Col = scan.nextInt();
            System.out.println();

            // Check if space is empty and valid
            if ((player2Row <= 3 && player2Col <= 3) && (player2Row >= 1 && player2Col >= 1) && (checkEmpty(table, player2Row, player2Col) == true)) {
                // If move is valids, add move to table
                addMove(table, player2Row, player2Col, 2);
                currentMove += 1;
            }
            else {
                System.out.println();
                System.out.println("Invalid move!");
                System.out.println("Your turn is skipped.");
            }

            // Showing the table after the move
            System.out.println();
            printTable(table);
            System.out.println();

            // Check if player2 won
            if (winner(table) == 2) {
                System.out.println(player2 + " won the game.");
                System.out.println();
                break;
            }

            // Check if there are space left in table
            if (currentMove >= maxMove) {
                break;
            }

        }

        // Check if game tied
        if (currentMove >= maxMove && winner(table) != 1 && winner(table) != 2) {
            System.out.println();
            System.out.println("The game ended as a draw.");
            System.out.println();
        }

        scan.close();
        System.out.println("The game has ended.");
        System.out.println("Thank you for playing!");
        System.out.println();
    }
}
