#include "../include/mySQL.hpp"

void FBNetwork::MySQL::setConnection(std::shared_ptr<MYSQL> t_connection)
{
    m_connection = t_connection;
}

void FBNetwork::MySQL::setResult(std::shared_ptr<MYSQL_RES> t_result)
{
    if (getResult() != nullptr)
    {
        mysql_free_result(m_result.get());
    }
    m_result = t_result;
}

void FBNetwork::MySQL::setRow(const MYSQL_ROW t_row)
{
    m_row = t_row;
}

void FBNetwork::MySQL::setSocket(const std::string &t_user)
{
    m_user = t_user;
}

void FBNetwork::MySQL::setUser(const std::string &t_user)
{
    m_user = t_user;
}

void FBNetwork::MySQL::setPassword(const std::string &t_password)
{
    m_password = t_password;
}

void FBNetwork::MySQL::setDatabase(const std::string &t_database)
{
    m_database = t_database;
}

void FBNetwork::MySQL::setHost(const std::string &t_host)
{
    m_host = t_host;
}

void FBNetwork::MySQL::setPort(FBNetwork::port t_port)
{
    m_port = t_port;
}

std::shared_ptr<MYSQL> FBNetwork::MySQL::getConnection() const
{
    return m_connection;
}

std::shared_ptr<MYSQL_RES> FBNetwork::MySQL::getResult() const
{
    return m_result;
}

MYSQL_ROW FBNetwork::MySQL::getRow() const
{
    return m_row;
}

std::string FBNetwork::MySQL::getSocket() const
{
    return m_socket;
}

std::string FBNetwork::MySQL::getUser() const
{
    return m_user;
}

std::string FBNetwork::MySQL::getPassword() const
{
    return m_password;
}

std::string FBNetwork::MySQL::getDatabase() const
{
    return m_database;
}

std::string FBNetwork::MySQL::getHost() const
{
    return m_host;
}

FBNetwork::port FBNetwork::MySQL::getPort() const
{
    return m_port;
}

std::shared_ptr<MYSQL_RES> FBNetwork::MySQL::executePreparedStatement(const std::string                 &t_query,
                                                                      const std::vector<SQL::parameter> &t_params) const
{
    if (t_query.empty())
    {
        throw InvalidArgumentException("Query is empty.");
    }
    MYSQL_STMT *stmt = mysql_stmt_init(getConnection().get());
    if (stmt == NULL)
    {
        throw MySQLRuntimeException("Statement initialization failed.");
    }

    if (mysql_stmt_prepare(stmt, t_query.c_str(), t_query.length()) != 0)
    {
        mysql_stmt_close(stmt);
        throw MySQLRuntimeException("Statement preparation failed.");
    }

    std::vector<MYSQL_BIND> bind(t_params.size());
    memset(bind.data(), 0, bind.size() * sizeof(MYSQL_BIND));

    for (size_t i = 0; i < t_params.size(); ++i)
    {
        const auto &param = t_params[i];
        if (std::holds_alternative<std::string>(param))
        {
            const auto &str       = std::get<std::string>(param);
            bind[i].buffer_type   = MYSQL_TYPE_STRING;
            bind[i].buffer        = (char *)str.c_str();
            bind[i].buffer_length = str.length();
        }
        else if (std::holds_alternative<int>(param))
        {
            int value             = std::get<int>(param);
            bind[i].buffer_type   = MYSQL_TYPE_LONG;
            bind[i].buffer        = &value;
            bind[i].buffer_length = sizeof(int);
        }
        else if (std::holds_alternative<double>(param))
        {
            double value          = std::get<double>(param);
            bind[i].buffer_type   = MYSQL_TYPE_DOUBLE;
            bind[i].buffer        = &value;
            bind[i].buffer_length = sizeof(double);
        }
        else if (std::holds_alternative<MYSQL_TIME>(param))
        {
            MYSQL_TIME time       = std::get<MYSQL_TIME>(param);
            bind[i].buffer_type   = MYSQL_TYPE_DATETIME;
            bind[i].buffer        = &time;
            bind[i].buffer_length = sizeof(MYSQL_TIME);
        }
        else if (std::holds_alternative<std::vector<char>>(param))
        {
            const auto &vec       = std::get<std::vector<char>>(param);
            bind[i].buffer_type   = MYSQL_TYPE_LONG_BLOB;
            bind[i].buffer        = (char *)vec.data();
            bind[i].buffer_length = vec.size();
        }
    }

    if (mysql_stmt_bind_param(stmt, bind.data()) != 0)
    {
        mysql_stmt_close(stmt);
        throw MySQLRuntimeException("Statement binding failed.");
    }

    if (mysql_stmt_execute(stmt) != 0)
    {
        mysql_stmt_close(stmt);
        throw MySQLRuntimeException("Statement execution failed.");
    }

    std::shared_ptr<MYSQL_RES> result        = std::shared_ptr<MYSQL_RES>(mysql_stmt_result_metadata(stmt));
    bool                       isSelectQuery = (t_query.find("SELECT") == 0);
    if (result == NULL && isSelectQuery)
    {
        mysql_stmt_close(stmt);
        throw MySQLRuntimeException("Result metadata failed.");
    }
    if (mysql_stmt_store_result(stmt) != 0)
    {
        mysql_free_result(result.get());
        mysql_stmt_close(stmt);
        throw MySQLRuntimeException("Result storage failed.");
    }
    if (mysql_stmt_num_rows(stmt) == 0)
    {
        mysql_free_result(result.get());
        mysql_stmt_close(stmt);
        return nullptr;
    }
    mysql_stmt_store_result(stmt);
    mysql_stmt_close(stmt);
    return result;
}

FBNetwork::MySQL::MySQL(const std::string &t_socket, const std::string &t_user, const std::string &t_password,
                        const std::string &t_database)
{
    if (t_socket.empty())
    {
        throw InvalidArgumentException("Socket is empty.");
    }
    if (t_user.empty())
    {
        throw InvalidArgumentException("User is empty.");
    }
    if (t_password.empty())
    {
        throw InvalidArgumentException("Password is empty.");
    }
    if (t_database.empty())
    {
        throw InvalidArgumentException("Database is empty.");
    }
    setHost("localhost");
    setUser(t_user);
    setPassword(t_password);
    setDatabase(t_database);
    setPort(3306);
    setSocket(t_socket);
    setConnection(std::shared_ptr<MYSQL>(mysql_init(NULL)));
    if (getConnection() == NULL)
    {
        throw MySQLCreationException("Connection failed. Initialize failed.");
    }
    if (mysql_real_connect(getConnection().get(), getHost().c_str(), getUser().c_str(), getPassword().c_str(), getDatabase().c_str(),
                           getPort(), getSocket().c_str(), CLIENT_MULTI_STATEMENTS) == NULL)
    {
        throw MySQLCreationException("Connection failed. Real connect failed.");
    }
}

FBNetwork::MySQL::MySQL(const std::string &t_host, const std::string &t_user, const std::string &t_password, const std::string &t_database,
                        port t_port)
{
    if (t_host.empty())
    {
        throw InvalidArgumentException("Host is empty.");
    }
    if (t_user.empty())
    {
        throw InvalidArgumentException("User is empty.");
    }
    if (t_password.empty())
    {
        throw InvalidArgumentException("Password is empty.");
    }
    if (t_database.empty())
    {
        throw InvalidArgumentException("Database is empty.");
    }
    if (t_port < 0 || t_port > 65535)
    {
        throw InvalidArgumentException("Port is invalid.");
    }
    setHost(t_host);
    setUser(t_user);
    setPassword(t_password);
    setDatabase(t_database);
    setPort(t_port);
    setConnection(std::shared_ptr<MYSQL>(mysql_init(NULL)));
    if (getConnection() == NULL)
    {
        throw MySQLCreationException("Connection failed. Initialize failed.");
    }
    if (mysql_real_connect(getConnection().get(), getHost().c_str(), getUser().c_str(), getPassword().c_str(), getDatabase().c_str(),
                           getPort(), NULL, CLIENT_MULTI_STATEMENTS) == NULL)
    {
        throw MySQLCreationException("Connection failed. Real connect failed. Error: " + std::string(mysql_error(getConnection().get())));
    }
}

FBNetwork::MySQL::~MySQL()
{
    if (getResult() != nullptr)
    {
        mysql_free_result(getResult().get());
        setResult(nullptr);
    }
    if (getConnection() != nullptr)
    {
        mysql_close(getConnection().get());
        setConnection(nullptr);
    }
}

bool FBNetwork::MySQL::has(const std::string &t_table, const std::string &t_column, const SQL::parameter t_value) const
{
    if (t_table.empty())
    {
        throw InvalidArgumentException("Table is empty.");
    }
    if (t_column.empty())
    {
        throw InvalidArgumentException("Column is empty.");
    }
    std::shared_ptr<MYSQL_RES>  result = nullptr;
    std::string                 query  = "SELECT * FROM " + t_table + " WHERE " + t_column + " = ?;";
    std::vector<SQL::parameter> params = {t_value};
    try
    {
        result = executePreparedStatement(query, params);
    }
    catch (const MySQLRuntimeException &e)
    {
        if (result != NULL)
        {
            mysql_free_result(result.get());
        }
        throw e;
    }
    if (result == nullptr)
    {
        return false;
    }

    return true;
}

bool FBNetwork::MySQL::match(const std::string &t_table, const std::string &t_column, const SQL::parameter t_value,
                             const std::string &t_column2, const SQL::parameter t_value2) const
{
    if (t_table.empty())
    {
        throw InvalidArgumentException("Table is empty.");
    }
    if (t_column.empty())
    {
        throw InvalidArgumentException("Column is empty.");
    }
    if (t_column2.empty())
    {
        throw InvalidArgumentException("Column2 is empty.");
    }
    std::shared_ptr<MYSQL_RES>  result = NULL;
    std::string                 query  = "SELECT * FROM " + t_table + " WHERE " + t_column + " = ? AND " + t_column2 + " = ?;";
    std::vector<SQL::parameter> params = {t_value, t_value2};
    try
    {
        result = executePreparedStatement(query, params);
    }
    catch (const MySQLRuntimeException &e)
    {
        if (result != NULL)
        {
            mysql_free_result(result.get());
        }
        throw e;
    }
    if (result == nullptr)
    {
        return false;
    }
    return true;
}

std::vector<std::string> FBNetwork::MySQL::getWhere(const std::string &t_table, const std::string &t_column, const std::string &t_column2,
                                                    const SQL::parameter t_value2) const
{
    if (t_table.empty())
    {
        throw InvalidArgumentException("Table is empty.");
    }
    if (t_column.empty())
    {
        throw InvalidArgumentException("Column is empty.");
    }
    if (t_column2.empty())
    {
        throw InvalidArgumentException("Column2 is empty.");
    }
    std::string                 query  = "SELECT " + t_column + " FROM " + t_table + " WHERE " + t_column2 + " = ?;";
    std::vector<SQL::parameter> params = {t_value2};
    std::vector<std::string>    resultString;
    std::shared_ptr<MYSQL_RES>  result = NULL;
    MYSQL_ROW                   row;
    try
    {
        result = executePreparedStatement(query, params);
    }
    catch (const MySQLRuntimeException &e)
    {
        if (result != NULL)
        {
            mysql_free_result(result.get());
        }
        throw e;
    }
    if (result == 0)
    {
        return SQL::EMPTY_RESULT;
    }
    while ((row = mysql_fetch_row(result.get())) != NULL)
    {
        resultString.push_back(row[0]);
    }
    return resultString;
}

std::vector<std::string> FBNetwork::MySQL::get(const std::string &t_table, const std::string &t_column) const
{
    if (t_table.empty())
    {
        throw InvalidArgumentException("Table is empty.");
    }
    if (t_column.empty())
    {
        throw InvalidArgumentException("Column is empty.");
    }
    std::shared_ptr<MYSQL_RES> result = NULL;
    std::string                query  = "SELECT " + t_column + " FROM " + t_table + ";";
    std::vector<std::string>   resultString;
    MYSQL_ROW                  row;
    try
    {
        result = executePreparedStatement(query, {});
    }
    catch (const MySQLRuntimeException &e)
    {
        if (result != NULL)
        {
            mysql_free_result(result.get());
        }
        throw e;
    }
    if (result == 0)
    {
        return SQL::EMPTY_RESULT;
    }
    while ((row = mysql_fetch_row(result.get())) != NULL)
    {
        resultString.push_back(row[0]);
    }
    return resultString;
}

void FBNetwork::MySQL::insert(const std::string &t_table, const std::vector<std::string> t_columns,
                              const std::vector<SQL::parameter> t_values)
{
    if (t_table.empty())
    {
        throw InvalidArgumentException("Table is empty.");
    }
    if (t_columns.empty())
    {
        throw InvalidArgumentException("Columns are empty.");
    }
    if (t_values.empty())
    {
        throw InvalidArgumentException("Values are empty.");
    }
    if (t_columns.size() != t_values.size())
    {
        throw InvalidArgumentException("Columns and values are not the same size.");
    }
    std::string query = "INSERT INTO " + t_table + " (";
    for (std::string column : t_columns)
    {
        query += column + ",";
    }
    query = query.substr(0, query.length() - 1);
    query += ") VALUES (";
    for (SQL::parameter value : t_values)
    {
        query += "?,";
    }
    query = query.substr(0, query.length() - 1);
    query += ");";
    try
    {
        executePreparedStatement(query, t_values);
    }
    catch (const MySQLRuntimeException &e)
    {
        throw e;
    }
}

void FBNetwork::MySQL::updateWhere(const std::string &t_table, const std::vector<std::string> t_columns,
                                   const std::vector<SQL::parameter> t_values, const std::string &t_column, const SQL::parameter t_value)
{
    if (t_table.empty())
    {
        throw InvalidArgumentException("Table is empty.");
    }
    if (t_columns.empty())
    {
        throw InvalidArgumentException("Columns are empty.");
    }
    if (t_values.empty())
    {
        throw InvalidArgumentException("Values are empty.");
    }
    if (t_column.empty())
    {
        throw InvalidArgumentException("Column is empty.");
    }
    if (t_columns.size() != t_values.size())
    {
        throw InvalidArgumentException("Columns and values are not the same size.");
    }
    std::string query = "UPDATE " + t_table + " SET ";
    for (size_t i = 0; i < t_columns.size(); ++i)
    {
        query += t_columns[i] + " = ?,";
    }
    query = query.substr(0, query.length() - 1);
    query += " WHERE " + t_column + " = ?;";
    std::vector<SQL::parameter> params = t_values;
    params.push_back(t_value);
    try
    {
        executePreparedStatement(query, params);
    }
    catch (const MySQLRuntimeException &e)
    {
        throw e;
    }
}

void FBNetwork::MySQL::deleteWhere(const std::string &t_table, const std::string &t_column, const SQL::parameter t_value)
{
    if (t_table.empty())
    {
        throw InvalidArgumentException("Table is empty.");
    }
    if (t_column.empty())
    {
        throw InvalidArgumentException("Column is empty.");
    }
    std::string                 query  = "DELETE FROM " + t_table + " WHERE " + t_column + " = ?;";
    std::vector<SQL::parameter> params = {t_value};
    std::shared_ptr<MYSQL_RES>  result = NULL;
    try
    {
        result = executePreparedStatement(query, params);
    }
    catch (const MySQLRuntimeException &e)
    {
        if (result != NULL)
        {
            mysql_free_result(result.get());
        }
        throw e;
    }
}