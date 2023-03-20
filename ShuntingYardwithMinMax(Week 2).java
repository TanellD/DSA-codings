//Davydov Danil d.davydov@innopolis.university
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;


public class Main{
    public static void main(String[] args) {
        Stack<String> stack = new LinkedStack<>();
        Scanner scanner1 = new Scanner(System.in);
        String line = scanner1.nextLine();
        Scanner scanner = new Scanner(line);
        String temp;
        while (scanner.hasNext()){
            temp = scanner.next();
            if(temp.charAt(0) <= '9' && temp.charAt(0) >= '0'){
                System.out.print(temp + " ");
            } else if(temp.equals("max") || temp.equals("min")){
                stack.push(temp);
            } else if (temp.equals("(")){
                stack.push(temp);
            } else if (temp.equals(")")) {
                while(!stack.peek().equals("(")){
                    System.out.print(stack.peek() + " ");
                    stack.pop();
                }
                stack.pop();
                if(!stack.isEmpty() && (stack.peek().equals("max") || stack.peek().equals("min"))){
                    System.out.print(stack.peek() + " ");
                    stack.pop();
                }
            }  else if(!temp.equals(" ") && !temp.equals(",")){
                int precedence = precedence(temp);
                while(!stack.isEmpty() && precedence(stack.peek()) >= precedence){
                    System.out.print(stack.peek() + " ");
                    stack.pop();
                }
                stack.push(temp);
            } else if (temp.equals(",")){
                while(!stack.isEmpty() && !stack.peek().equals("(")){
                    System.out.print(stack.peek() + " ");
                    stack.pop();
                }

            }
        }
        while(!stack.isEmpty()){
            System.out.print(stack.peek() + " ");
            stack.pop();
        }

    }
    static int precedence(String str){
        switch(str){
            case "+":
                return 0;
            case "-":
                return 0;
            case "*":
                return 1;
            case "/":
                return 1;
            default:
                return -1;
        }
    }

}
interface Stack<T>{
    void push(T e);
    void pop();
    T peek();
    int size();
    boolean isEmpty();
}

class LinkedStack<T> implements Stack<T>{
    LinkedList<T> elements;

    public LinkedStack(){
        elements = new LinkedList<T>();
    }
    public void push(T e){
        elements.add(e);
    }
    public void pop(){
        elements.remove(elements.size()-1);
    }
    public T peek(){
        return elements.get(elements.size()-1);
    }
    public int size(){
        return elements.size();
    }
    public boolean isEmpty(){
        return elements.isEmpty();
    }
}
