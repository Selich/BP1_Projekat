package acs.uns.ac.rs.model;

public class Parcela {

    private String evidencioniBroj;
    private String nazivKatasterskeOpstine;
    private Integer pParcele;
    private String tipParcele;

    public Parcela() {
        super();
    }

    public Parcela(String evidencioniBroj, String nazivKatasterskeOpstine, Integer pParcele, String tipParcele) {
        super();
        this.evidencioniBroj = evidencioniBroj;
        this.nazivKatasterskeOpstine = nazivKatasterskeOpstine;
        this.pParcele = pParcele;
        this.tipParcele = tipParcele;
    }

    public String getEvidencioniBroj() {
        return evidencioniBroj;
    }

    public void setEvidencioniBroj(String evidencioniBroj) {
        this.evidencioniBroj = evidencioniBroj;
    }

    public String getNazivKatasterskeOpstine() {
        return nazivKatasterskeOpstine;
    }

    public void setNazivKatasterskeOpstine(String nazivKatasterskeOpstine) {
        this.nazivKatasterskeOpstine = nazivKatasterskeOpstine;
    }

    public Integer getpParcele() {
        return pParcele;
    }

    public void setpParcele(Integer pParcele) {
        this.pParcele = pParcele;
    }

    public String getTipParcele() {
        return tipParcele;
    }

    public void setTipParcele(String tipParcele) {
        this.tipParcele = tipParcele;
    }
}
