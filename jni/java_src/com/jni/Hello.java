package com.jni;
public class Hello{

public static Integer count =0;

private static Hello instance = new Hello();

public static void hi(String args[]){
    count++;
    System.out.println("      -----method hi from class Hello-----This method was called for the "+count+ " 'th time.");
    System.out.println("           -----method hi from class Hello-----got parameter:"+args[0]);
    System.out.println("The hashcode of THE private Static Hello instance is : "+ instance.hashCode());
}

public static void main(String args[]){
    hi(args);

}


}
