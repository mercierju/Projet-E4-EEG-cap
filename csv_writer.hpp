#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

/**
   Usage:
   auto csv = CSVWriter(path_to_the_csv_to_create, width_of_columns);
   csv << "aaa" << 3 << true << 3.14; // write things in the 4 first columns of the first line
   csv.new_line(); // start a new line
   csv << "bbb" << 0 << false << 2.0; // write things in the 4 first columns of the second line

   // that's it nothing complicated
   
 */
struct CSVWriter
{
private:
    std::ofstream _file;
    bool _line_start = true;
    size_t _col_width;
public:
    CSVWriter() = delete;
    CSVWriter(const std::string & path, size_t col_width=0):
        _col_width(col_width)
    {
        _file.open(path);
    }
    ~CSVWriter()
    {
        _file.close();
    }

    template<typename T>
    CSVWriter &
    operator<<(const T rhs)
    {
        if (!_line_start)
        {
            _file << ",";
        }
        else
        {
            _line_start = false;
        }
        _file << std::setw(_col_width) << rhs;
        return *this;
    }
    CSVWriter & new_line()
    {
        _file << std::endl;
        _line_start = true;
        return *this;
    }
};

