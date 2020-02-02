package acs.uns.ac.rs.dao;

import java.io.File;

public class CsvFile {
    private String name;

    public CsvFile(){}

    public CsvFile(String name, File file) {
        this.name = name;
        this.file = file;
    }

    private File file;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public File getFile() {
        return file;
    }

    public void setFile(File file) {
        this.file = file;
    }
}
