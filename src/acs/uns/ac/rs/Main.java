package acs.uns.ac.rs;

import acs.uns.ac.rs.ui_handler.MainUIHandler;

import java.io.IOException;


public class Main {

    public static void main(String[] args) throws IOException {
        MainUIHandler mainUIHandler = new MainUIHandler();
        mainUIHandler.handleMainMenu();
    }
}
