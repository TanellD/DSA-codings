//Davydov Danil d.davydov@innopolis.university
import java.util.Scanner;

public class Main{
    public static void main(String[] args) {
        int lines;
        Scanner scanner = new Scanner(System.in);
        lines = scanner.nextInt();
        int[] array = new int[lines];
        for(int i = 0; i < lines; ++i){
            array[i] = scanner.nextInt();
        }
        array = mergeSort(array, lines);

        for(int i = 0; i < lines; ++i){
            System.out.print(array[i]);
            System.out.print(" ");
        }
    }
    static int[] mergeSort(int[] array, int n){
        if (n > 1){
            int[] arr1 = new int[n/2];
            int[] arr2 = new int[n/2 + n%2];
            for(int i = 0; i < n/2; ++i){
                arr1[i] = array[i];
            }
            for(int i = n/2; i < n; ++i){
                arr2[i-n/2] = array[i];
            }
            arr1 = mergeSort(arr1, n/2);
            arr2 = mergeSort(arr2, n/2 + n%2);
            int[] newArr = new int[n];
            int a = 0, b = 0;
            for(int i = 0; i < n; ++i){
                if(arr1[a] < arr2[b]) {
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
