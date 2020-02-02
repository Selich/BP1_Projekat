package acs.uns.ac.rs.model;

public class Parcela {


    private Integer evidencioniBroj;
    private String nazivKatasterskeOpstine;
    private Integer povrsina;
    private String tip;

    public Parcela() {
        super();
    }

    public Parcela(String row) {
        String[] fields = row.split(",");
        this.evidencioniBroj = Integer.parseInt(fields[0]);
        this.nazivKatasterskeOpstine = fields[1];
        this.tip = fields[2];
        this.povrsina = Integer.parseInt(fields[3]);
    }

    public Parcela(Integer evidencioniBroj, String nazivKatasterskeOpstine, Integer pParcele, String tipParcele) {
        super();
        this.evidencioniBroj = evidencioniBroj;
        this.nazivKatasterskeOpstine = nazivKatasterskeOpstine;
        this.povrsina = pParcele;
        this.tip = tipParcele;
    }
    public Integer getEvidencioniBroj() {
        return evidencioniBroj;
    }

    public void setEvidencioniBroj(Integer evidencioniBroj) {
        this.evidencioniBroj = evidencioniBroj;
    }

    public String getNazivKatasterskeOpstine() {
        return nazivKatasterskeOpstine;
    }

    public void setNazivKatasterskeOpstine(String nazivKatasterskeOpstine) {
        this.nazivKatasterskeOpstine = nazivKatasterskeOpstine;
    }

    public Integer getPovrsina() {
        return povrsina;
    }

    public void setPovrsina(Integer povrsina) {
        this.povrsina = povrsina;
    }

    public String getTip() {
        return tip;
    }

    public void setTip(String tip) {
        this.tip = tip;
    }

}
