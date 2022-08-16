import java.util.Scanner;
import java.util.Random;
import java.util.ArrayList;
import java.util.HashSet;

public class Hangman {

    public static void main(String[] args) {

        String[] words = {"anime", "manga", "imouto", "programming", "hangman", "classroom", "project"};

        Scanner userInput = new Scanner(System.in);
        Random rand = new Random();
        ArrayList<Character> wordGuessed = new ArrayList<Character>();
        HashSet<Character> letters = new HashSet<Character>();

        int randomInt = rand.nextInt(words.length);
        String wordChosen = words[randomInt];
        int wordChosenLength = wordChosen.length();
        int wrongAttempRemaining = 6;
        int correctGuess = 0;

        char[] charConvertor = wordChosen.toCharArray();
        char[] setUpBlock = charConvertor.clone();
        for (int i = 0; i < wordChosenLength; i++) {
            setUpBlock[i] = '_';
        }
        
        System.out.println();
        System.out.println("Welcome to Hangman!");
        System.out.println("As usual, you got 6 lives to try and guess the missing letters.");
        System.out.println("For each wrong guess, you will lose a live.");
        System.out.println("There will be hints for the word.");
        System.out.println("Enjoy!");
        System.out.println();

        if (wrongAttempRemaining > 0) {

            while (wrongAttempRemaining > 0 && correctGuess != wordChosenLength) {

                System.out.println("Hint: There are " + wordChosenLength + " letters.");

                for (int n = 0; n < wordGuessed.size(); n++) {
                    letters.add(wordGuessed.get(n));
                }

                System.out.println("Word guessed: " + letters);
                System.out.println("You have " + wrongAttempRemaining + " lives remaining.");
                System.out.println();
                System.out.println(setUpBlock);
                System.out.println();
                char guess = userInput.next().charAt(0);
                System.out.println();

                if (wordChosen.indexOf(guess) >= 0) {

                    for (int index = 0; index < wordChosenLength; index++) {
                        if (guess == charConvertor[index] && letters.contains(guess) == false) {
                            setUpBlock[index] = guess;
                            correctGuess += 1;
                            wordGuessed.add(guess);
                        }
                    }

                    if (letters.contains(guess) == true) {
                        System.out.println("Invalid guess.");
                        System.out.println();
                    }

                } else {
                    wrongAttempRemaining -= 1;
                    wordGuessed.add(guess);
                }

                if (correctGuess == wordChosenLength) {
                    System.out.println("The word is: " + wordChosen);
                    System.out.println("You guessed all the letters correctly!");
                }
            }
            
        }

        if (wrongAttempRemaining == 0) {
            System.out.println("Out of lives, you lost!");
        }

        System.out.println();
        System.out.println("Thank you and good bye!");
        System.out.println();

        userInput.close();
    }
    
}