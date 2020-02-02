package acs.uns.ac.rs.dao.impl;

import acs.uns.ac.rs.connection.ConnectionUtil;
import acs.uns.ac.rs.dao.CRUDDao;
import acs.uns.ac.rs.dao.ParcelaDAO;
import acs.uns.ac.rs.model.Parcela;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class ParcelaDAOImpl implements ParcelaDAO {


    @Override
    public int count() throws SQLException {
        String query = "select count(*) from parcela";

        try (
           Connection connection = ConnectionUtil.getConnection();
           PreparedStatement preparedStatement = connection.prepareStatement(query);
           ResultSet resultSet = preparedStatement.executeQuery()
        ){
            if(resultSet.next()){
                return resultSet.getInt((1));
            } else return -1;
        }
    }

    @Override
    public void delete(Parcela entity) throws SQLException {
        String query = "delete from parcela where evidencioniBroj=?";

        try (
                Connection connection = ConnectionUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(query);
        ){
            preparedStatement.setInt(1, entity.getEvidencioniBroj());
            preparedStatement.executeUpdate();
        }

    }

    @Override
    public void deleteAll() throws SQLException {
        String query = "delete from parcela";
        try (
                Connection connection = ConnectionUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(query);
        ){
            preparedStatement.executeUpdate();
        }
    }

    @Override
    public void deleteById(Integer id) throws SQLException {
        String query = "delete from parcela where evidencioniBroj=?";

        try (
                Connection connection = ConnectionUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(query);
        ){
            preparedStatement.setInt(1, id);
            preparedStatement.executeUpdate();
        }

    }

    @Override
    public boolean existsById(Integer id) throws SQLException {
        String query = "select * from parcela where evidencioniBroj=?";

        try (
                Connection connection = ConnectionUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(query);
        ){
            preparedStatement.setInt(1, id);
            try(ResultSet resultSet = preparedStatement.executeQuery()){
                return resultSet.isBeforeFirst();
            }
        }
    }

    @Override
    public Iterable<Parcela> findAll() throws SQLException {
        String query = "select evidencioniBroj, nazivKatasterskeOpstine, tip, povrsina from parcela";
        List<Parcela> parcelaList = new ArrayList<Parcela>();
        try (
                Connection connection = ConnectionUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(query);
                ResultSet resultSet = preparedStatement.executeQuery();
        ){
            while(resultSet.next()){
                Parcela parcela = new Parcela(
                        resultSet.getInt(1),
                        resultSet.getString(2),
                        resultSet.getInt(3),
                        resultSet.getString(4)
                );
                parcelaList.add(parcela);
            }
        } catch (Exception e){
            e.printStackTrace();
        }
        return parcelaList;
    }

    @Override
    public Parcela findById(Integer id) throws SQLException {
        String query = "select evidencioniBroj, nazivKatasterskeOpstine, tip, povrsina from parcela where evidencioniBroj=?";
        Parcela parcela = null;
        try (
                Connection connection = ConnectionUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(query);
        ) {
            preparedStatement.setInt(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.isBeforeFirst()) {
                    resultSet.next();
                    parcela = new Parcela(
                            resultSet.getInt(1),
                            resultSet.getString(2),
                            resultSet.getInt(3),
                            resultSet.getString(4)
                    );
                }
            }
        }
        return parcela;
    }

    @Override
    public void save(Parcela entity) throws SQLException {
        String insertQuery = "insert into parcela (nazivKatasterskeOpstine, tip, povrsina) values (?, ?, ?)";
        String updateQuery = "update parcela set nazivKatasterskeOpstine=?, tip=?, povrsina=? where evidencioniBroj=?";

        int i = 1;
        try(
            Connection connection = ConnectionUtil.getConnection();
            PreparedStatement preparedStatement = connection.prepareStatement(
                    existsById((entity.getEvidencioniBroj())) ? updateQuery : insertQuery
            ))
        {
            preparedStatement.setString(i++, entity.getNazivKatasterskeOpstine());
            preparedStatement.setString(i++, entity.getTip());
            preparedStatement.setInt(i++, entity.getPovrsina());
            preparedStatement.executeUpdate();
        }
    }

    @Override
    public void insert(Parcela entity) throws SQLException {
        String insertQuery = "insert into parcela (evidencioniBroj, nazivKatasterskeOpstine, tip, povrsina) values (?, ?, ?)";
        int i = 1;
        try(
                Connection connection = ConnectionUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement( insertQuery ))
        {
            preparedStatement.setString(i++, entity.getNazivKatasterskeOpstine());
            preparedStatement.setString(i++, entity.getTip());
            preparedStatement.setInt(i++, entity.getPovrsina());
            preparedStatement.setInt(i++, entity.getEvidencioniBroj());
            preparedStatement.executeUpdate();
        }
    }
    @Override
    public void update(Parcela entity) throws SQLException {
        String updateQuery = "update parcela set nazivKatasterskeOpstine=?, tip=?, povrsina=? where evidencioniBroj=?";
        int i = 1;
        try(
                Connection connection = ConnectionUtil.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(updateQuery))
        {
            preparedStatement.setString(i++, entity.getNazivKatasterskeOpstine());
            preparedStatement.setString(i++, entity.getTip());
            preparedStatement.setInt(i++, entity.getPovrsina());
            preparedStatement.setInt(i++, entity.getEvidencioniBroj());
            preparedStatement.executeUpdate();
        }
    }
}
