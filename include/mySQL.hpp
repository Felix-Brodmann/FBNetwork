#ifndef FBNETWORK_MYSQL_HPP
#define FBNETWORK_MYSQL_HPP

#include <cstring>
#include <mysql/mysql.h>
#include <string>
#include <variant>
#include <vector>
#include "constants.hpp"
#include "exceptions.hpp"

namespace FBNetwork
{
    /**
     * @brief The MySQL class provides an interface for interacting with a MySQL database.
     * @details This class provides an interface for interacting with a MySQL database. It allows users to execute queries, check for the
     * existence of records, and retrieve records from the database.
     * @version 1.0.0
     */
    class MySQL
    {
    private:
        MYSQL_ROW                  m_row;
        std::shared_ptr<MYSQL>     m_connection = nullptr;
        std::shared_ptr<MYSQL_RES> m_result     = nullptr;
        std::string                m_socket     = "";
        std::string                m_user       = "";
        std::string                m_password   = "";
        std::string                m_database   = "";
        std::string                m_host       = "";
        port                       m_port       = 0;

        /**
         * @brief Sets the connection for the MySQL object.
         * @details This function sets the connection for the MySQL object to the specified connection.
         * @param t_connection A pointer to the MYSQL object representing the connection.
         * @version 1.0.0
         */
        void setConnection(std::shared_ptr<MYSQL> t_connection);

        /**
         * @brief Sets the result for the MySQL object.
         * @details This function sets the result for the MySQL object to the specified result.
         * @param t_result A pointer to the MYSQL_RES object representing the result.
         * @version 1.0.0
         */
        void setResult(std::shared_ptr<MYSQL_RES> t_result);

        /**
         * @brief Sets the row for the MySQL object.
         * @details This function sets the row for the MySQL object to the specified row.
         * @param t_row A pointer to the MYSQL_ROW object representing the row.
         * @version 1.0.0
         */
        void setRow(const MYSQL_ROW t_row);

        /**
         * @brief Sets the socket for the MySQL object.
         * @details This function sets the socket for the MySQL object to the specified socket.
         * @param t_socket The socket to be set.
         * @version 1.0.0
         */
        void setSocket(const std::string &t_socket);

        /**
         * @brief Sets the user for the MySQL object.
         * @details This function sets the user for the MySQL object to the specified user.
         * @param t_user The user to be set.
         * @version 1.0.0
         */
        void setUser(const std::string &t_user);

        /**
         * @brief Sets the password for the MySQL object.
         * @details This function sets the password for the MySQL object to the specified password.
         * @param t_password The password to be set.
         * @version 1.0.0
         */
        void setPassword(const std::string &t_password);

        /**
         * @brief Sets the database for the MySQL object.
         * @details This function sets the database for the MySQL object to the specified database.
         * @param t_database The database to be set.
         * @version 1.0.0
         */
        void setDatabase(const std::string &t_database);

        /**
         * @brief Sets the host for the MySQL object.
         * @details This function sets the host for the MySQL object to the specified host.
         * @param t_host The host to be set.
         * @version 1.0.0
         */
        void setHost(const std::string &t_host);

        /**
         * @brief Sets the port for the MySQL object.
         * @details This function sets the port for the MySQL object to the specified port.
         * @param t_port The port to be set.
         * @version 1.0.0
         */
        void setPort(port t_port);

        /**
         * @brief Retrieves the connection.
         * @details This function returns the connection that was set using the `setConnection` function.
         * @return The connection.
         * @version 1.0.0
         */
        std::shared_ptr<MYSQL> getConnection() const;

        /**
         * @brief Retrieves the result.
         * @details This function returns the result that was set using the `setResult` function.
         * @return The result.
         * @version 1.0.0
         */
        std::shared_ptr<MYSQL_RES> getResult() const;

        /**
         * @brief Retrieves the row.
         * @details This function returns the row that was set using the `setRow` function.
         * @return The row.
         * @version 1.0.0
         */
        MYSQL_ROW getRow() const;

        /**
         * @brief Retrieves the socket.
         * @details This function returns the socket that was set using the `setSocket` function.
         * @return The socket.
         * @version 1.0.0
         */
        std::string getSocket() const;

        /**
         * @brief Retrieves the user.
         * @details This function returns the user that was set using the `setUser` function.
         * @return The user.
         * @version 1.0.0
         */
        std::string getUser() const;

        /**
         * @brief Retrieves the password.
         * @details This function returns the password that was set using the `setPassword` function.
         * @return The password.
         * @version 1.0.0
         */
        std::string getPassword() const;

        /**
         * @brief Retrieves the database.
         * @details This function returns the database that was set using the `setDatabase` function.
         * @return The database.
         * @version 1.0.0
         */
        std::string getDatabase() const;

        /**
         * @brief Retrieves the host.
         * @details This function returns the host that was set using the `setHost` function.
         * @return The host.
         * @version 1.0.0
         */
        std::string getHost() const;

        /**
         * @brief Retrieves the port.
         * @details This function returns the port that was set using the `setPort` function.
         * @return The port.
         * @version 1.0.0
         */
        port getPort() const;

        /**
         * @brief Executes the specified query.
         * @details This function executes the specified query.
         * @param t_query The query to be executed.
         * @param t_params The parameters to be bound to the query.
         * @return A pointer to the `MYSQL_RES` object representing the result of the query.
         * @throws `InvalidArgumentException` If the query is empty.
         * @throws `MySQLRuntimeException` If the query could not be executed.
         * @version 1.0.0
         */
        std::shared_ptr<MYSQL_RES> executePreparedStatement(const std::string &t_query, const std::vector<SQL::parameter> &t_params) const;

    public:
        /**
         * @brief Constructs a new MySQL object, running on the local machine.
         * @details This constructor creates a new MySQL object with the specified socket, user, password, and database.
         * @param t_socket The socket to be set.
         * @param t_user The user to be set.
         * @param t_password The password to be set.
         * @param t_database The database to be set.
         * @throws `InvalidArgumentException` If the socket, user, password, or database is empty
         * @throws `MySQLCreationException` If the connection could not be established.
         * @version 1.0.0
         */
        MySQL(const std::string &t_socket, const std::string &t_user, const std::string &t_password, const std::string &t_database);
        /**
         * @brief Constructs a new MySQL object, running on the specified host.
         * @details This constructor creates a new MySQL object with the specified host, user, password, database, and port.
         * @param t_host The host to be set. (The IP address of the MySQL server)
         * @param t_user The user to be set.
         * @param t_password The password to be set.
         * @param t_database The database to be set.
         * @param t_port The port to be set.
         * @throws `InvalidArgumentException` If the host, user, password, or database is empty or the port is less than 0 or greater than
         * 65535.
         * @throws `MySQLCreationException` If the connection could not be established.
         * @version 1.0.0
         */
        MySQL(const std::string &t_host, const std::string &t_user, const std::string &t_password, const std::string &t_database,
              port t_port);
        /**
         * @brief Destructor for the MySQL class.
         * @details This destructor is responsible for cleaning up any resources used by the MySQL class. It is automatically called when an
         * object of the MySQL class goes out of scope or is explicitly deleted.
         * @version 1.0.0
         */
        ~MySQL();

        /**
         * @brief Checks if a record exists in the specified table with the specified value in the specified column.
         * @details This function checks if a record exists in the specified table with the specified value in the specified column.
         * @param t_table The table to check.
         * @param t_column The column to check.
         * @param t_value The value to check.
         * @return True if the record exists, false otherwise.
         * @throws `InvalidArgumentException` If the table or column is empty.
         * @throws `MySQLRuntimeException` If the statement or binding failed.
         * @version 1.0.0
         */
        bool has(const std::string &t_table, const std::string &t_column, const SQL::parameter t_value) const;

        /**
         * @brief Checks if a record has the specified values in the specified columns.
         * @details This function checks if a record has the specified values in the specified columns.
         * @param t_table The table to check.
         * @param t_column The first column to check.
         * @param t_value The first value to check.
         * @param t_column2 The second column to check.
         * @param t_value2 The second value to check.
         * @return True if the record exists, false otherwise.
         * @throws `InvalidArgumentException` If the table or columns are empty.
         * @throws `MySQLRuntimeException` If the statement or binding failed.
         * @version 1.0.0
         */
        bool match(const std::string &t_table, const std::string &t_column, const SQL::parameter t_value, const std::string &t_column2,
                   const SQL::parameter t_value2) const;

        /**
         * @brief Retrieves the values from the table `t_table` and column `t_column`, where the specified column `t_column2` has the
         * specified value `t_value2`.
         * @details This function retrieves the values from the specified table and column. It returns a vector of strings containing the
         * values.
         * @param t_table The table to retrieve from.
         * @param t_column The column to retrieve from.
         * @param t_column2 The column to check.
         * @param t_value2 The value to check.
         * @return A vector of strings containing the values.
         * @throws `InvalidArgumentException` If the table or columns are empty.
         * @throws `MySQLRuntimeException` If the statement or binding failed.
         * @version 1.0.0
         */
        std::vector<std::string> getWhere(const std::string &t_table, const std::string &t_column, const std::string &t_column2,
                                          const SQL::parameter t_value2) const;

        /**
         * @brief Retrieves the values from the table `t_table` and column `t_column`.
         * @details This function retrieves the values from the specified table and column. It returns a vector of strings containing the
         * values.
         * @param t_table The table to retrieve from.
         * @param t_column The column to retrieve from.
         * @return A vector of strings containing the values.
         * @throws `InvalidArgumentException` If the table or column is empty.
         * @throws `MySQLRuntimeException` If the statement or binding failed.
         * @version 1.0.0
         */
        std::vector<std::string> get(const std::string &t_table, const std::string &t_column) const;

        /**
         * @brief Inserts a new row into the specified table with the given columns and values.
         * @details This function inserts a new row into the specified table with the given columns and values.
         * @param t_table The name of the table to insert into.
         * @param t_columns The list of column names for the new row.
         * @param t_values The list of values for the new row.
         * @throws `InvalidArgumentException` If the table or columns are empty or the sizes of the columns and values do not match.
         * @throws `MySQLRuntimeException` If the statement or binding failed.
         */
        void insert(const std::string &t_table, const std::vector<std::string> t_columns, const std::vector<SQL::parameter> t_values);

        /**
         * @brief Updates the given colums with the given values in the specified table, where the specified column has the
         * specified value.
         * @details This function updates the specified entry in the specified table with the given columns and values.
         * @param t_table The name of the table to update.
         * @param t_columns The list of column names to update.
         * @param t_values The list of values to update.
         * @param t_column The column to check.
         * @param t_value The value to check.
         * @throws `InvalidArgumentException` If the table or columns are empty, the column is empty, or the sizes of the columns and values
         * do not match.
         * @throws `MySQLRuntimeException` If the statement or binding failed.
         * @version 1.0.0
         */
        void updateWhere(const std::string &t_table, const std::vector<std::string> t_columns, const std::vector<SQL::parameter> t_values,
                         const std::string &t_column, const SQL::parameter t_value);

        /**
         * @brief Deletes the specified entry in the specified table where the specified column has the specified value.
         * @details This function deletes the specified entry in the specified table where the specified column has the
         * specified value.
         * @param t_table The name of the table to delete from.
         * @param t_column The column to check.
         * @param t_value The value to check.
         * @throws `InvalidArgumentException` If the table or column is empty.
         * @throws `MySQLRuntimeException` If the statement or binding failed.
         * @version 1.0.0
         */
        void deleteWhere(const std::string &t_table, const std::string &t_column, const SQL::parameter t_value);
    };
}  // namespace FBNetwork

#endif