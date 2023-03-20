//Davydov Danil d.davydov@innopolis.university
import java.util.Scanner;

public class Main{
    public static void main(String[] args) {
        int lines;
        int players;
        Scanner scanner = new Scanner(System.in);
        lines = scanner.nextInt();
        players = scanner.nextInt();
        if(players > lines){
            players = lines;
        }
        Player[] array = new Player[lines];
        for(int i = 0; i < lines; ++i){
            String name = scanner.next();
            int score = scanner.nextInt();
            array[i] = new Player(name, score);
        }
        array = mergeSort(array, lines);

        for(int i = 0; i < players; ++i){
            System.out.print(array[i].getName());
            System.out.print(" ");
            System.out.println(array[i].getScore());
        }
    }
    static Player[] mergeSort(Player[] array, int n){
        if (n > 1){
            Player[] arr1 = new Player[n/2];
            Player[] arr2 = new Player[n/2 + n%2];
            for(int i = 0; i < n/2; ++i){
                arr1[i] = array[i];
            }
            for(int i = n/2; i < n; ++i){
                arr2[i-n/2] = array[i];
            }
            arr1 = mergeSort(arr1, n/2);
            arr2 = mergeSort(arr2, n/2 + n%2);
            Player[] newArr = new Player[n];
            int a = 0, b = 0;
            for(int i = 0; i < n; ++i){
                if(arr1[a].getScore() >= arr2[b].getScore()) {
                    newArr[i] = arr1[a];
                    a++;
                    if(a >= n/2) {
                        for( int k = b; k < n/2+n%2; ++k){
                            ++i;
                            newArr[i] = arr2[k];
                        }
                    }
                } else {
                    newArr[i] = arr2[b];
                    b++;
                    if(b >= n/2+n%2) {
                        for( int k = a; k < n/2; ++k){
                            ++i;
                            newArr[i] = arr1[k];
                        }
                    }
                }
            }
            return newArr;
        }
        return array;
    }

}
class Player{
    private String name;
    private int score;
    public Player(String givenName, int givenScore){
        name = givenName;
        score = givenScore;
    }
    public int getScore(){
        return score;
    }
    public String getName(){
        return name;
    }
}
