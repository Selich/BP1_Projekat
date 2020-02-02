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
    private ParcelaDAOImpl parcelaDAO;


    public CsvFile readCsv(){
        CsvFile newFile = new CsvFile();
        Scanner sc = new Scanner(System.in);
        File file;
        System.out.println("Unesite naziv datoteke:");

        String fileName = sc.nextLine();

        file = new File("../csv/" + fileName);

        try(BufferedReader br = new BufferedReader(new FileReader(file))){
            String row;
            boolean header = true;

            while((row = br.readLine()) != null){
                if(!header){
                    Parcela parcela = new Parcela(row);
                    if(parcelaDAO.existsById(parcela.getEvidencioniBroj())) {
                        System.out.println("Update: " + parcela);
                    }else{
                        System.out.println("Insert: " + parcela);
                    }
                    }
                }
            } catch (SQLException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return newFile;
    }

    public void writeCsv(){

    }




}
