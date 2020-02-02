package acs.uns.ac.rs.service;

import acs.uns.ac.rs.dao.CsvFile;
import acs.uns.ac.rs.dao.ParcelaDAO;
import acs.uns.ac.rs.dao.impl.ParcelaDAOImpl;
import acs.uns.ac.rs.model.Parcela;

import java.io.*;
import java.sql.SQLException;
import java.util.Scanner;

public class ParcelaService {

    private BufferedReader br;
    private static final ParcelaDAO parcelaDAO = new ParcelaDAOImpl();


    public CsvFile readCsv(){
        CsvFile newFile = new CsvFile();
        Scanner sc = new Scanner(System.in);
        System.out.println("Unesite naziv datoteke:");
        String fileName = sc.nextLine();
        File file = new File("./csv/" + fileName);

        try(BufferedReader br = new BufferedReader(new FileReader(file))){
            String row;
            boolean header = true;
            System.out.println("Otvoren csv file");

            while((row = br.readLine()) != null){
                if(!header){
                    Parcela parcela = new Parcela(row);
                    if(parcelaDAO.existsById(parcela.getEvidencioniBroj())) {
                        System.out.println("Update: " + parcela);
                        parcelaDAO.update(parcela);
                    }else{
                        System.out.println("Insert: " + parcela);
                        parcelaDAO.insert(parcela);
                    }
                }
                header = false;
            }
        } catch (SQLException | IOException ex) {
            ex.printStackTrace();
        }
        return newFile;
    }

    public void writeCsv(){


    }




}
