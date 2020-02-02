package acs.uns.ac.rs.ui_handler;


import acs.uns.ac.rs.dao.CsvFile;
import acs.uns.ac.rs.service.ParcelaService;

import java.io.File;
import java.io.IOException;
import java.util.Scanner;


public class ParcelaUIHandler {

    public static Scanner sc = new Scanner(System.in);
    public static final ParcelaService parcelaService = new ParcelaService();
    public CsvFile csvFile;

    public void printMenu(){
        System.out.println("Opcija:");
        System.out.println("1. - Read .csv");
        System.out.println("2. - Write .csv");
        System.out.println("0. - Exit");
    }


    public void handleParcelaMenu() throws IOException {
        int answer;

        do {
            printMenu();
            answer = sc.nextInt();

            switch (answer){
                case 1:
                    csvFile = parcelaService.readCsv();
                case 2:
                    parcelaService.writeCsv();
            }

        } while (answer != 0);
    }
}
