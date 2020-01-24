package acs.uns.ac.rs.ui_handler;

import java.util.Scanner;

public class MainUIHandler {

    public static Scanner sc = new Scanner(System.in);

    // private final RadnikUIHandler radnikUIHandler = new RadnikUIHandler();


    public void handleMainMenu(){
        String answer;


        do {
            System.out.println("Opcija:");
            System.out.println("1. - Rukovanje parcelama:");
            answer = sc.nextLine();


            switch (answer){
                case "1":
                    // todo handler
                    // radnikUIHandler.handleRadnikMenu();
                    break;
                case "2":
                    // todo handler
                    break;
                case "3":
                    // todo handler
                    break;
                default:
                    System.out.println("Enter a valid option");
            }
        } while (!answer.equals("0"));
    }
}
