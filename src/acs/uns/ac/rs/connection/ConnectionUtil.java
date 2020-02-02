package acs.uns.ac.rs.connection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectionUtil {

    private static Connection instance = null;


    @Deprecated
    public static Connection getConnection() throws SQLException {
        if (instance == null || instance.isClosed()){
            try {
                Class.forName(ConnectionParams.DRIVER).newInstance();
                instance = DriverManager.getConnection(
                        ConnectionParams.LOCAL_CONNECTION_STRING,
                        ConnectionParams.USERNAME,
                        ConnectionParams.PASSWORD);
            } catch (IllegalAccessException | ClassNotFoundException | InstantiationException e) {
                e.printStackTrace();
            }
        }
        return instance;
    }
}
