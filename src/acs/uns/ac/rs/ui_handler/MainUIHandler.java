package acs.uns.ac.rs.ui_handler;

import java.io.IOException;
import java.util.Scanner;

public class MainUIHandler {

    public static Scanner sc = new Scanner(System.in);
    private final ParcelaUIHandler parcelaUIHandler = new ParcelaUIHandler();

    public void printMenu(){
        System.out.println("Opcija:");
        System.out.println("1. - Rukovanje parcelama");
        System.out.println("0. - Exit");
    }


    public void handleMainMenu() throws IOException {
        int answer;

        do {
            printMenu();
            answer = sc.nextInt();

            if (answer == 1) {
                parcelaUIHandler.handleParcelaMenu();
            } else {
                System.out.println("Enter a valid option");
            }
        } while (answer != 0);
    }
}
