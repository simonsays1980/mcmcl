/* 
 * File:   CSVReaderData.h
 * Author: simonzehnder
 *
 * Created on May 17, 2012, 5:14 PM
 */

#ifndef CSV_DATA_READER_H
#define	CSV_DATA_READER_H

#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include "reader.h"

using namespace std;
using namespace boost;

class csv_data_reader : public reader {
public: 
    virtual ~csv_data_reader() {};
    virtual void read (string &path) {
        
        string _line;
        vector<double> _data;
        int _len = 0;
        int _num;
        
        ifstream in(path.c_str());
        if(in.fail()) {
            cout << "File cannot be found!" << endl;
            return;
        }
        
        char_separator<char> sep(",");
        tokenizer<char_separator<char> > tok(_line, sep);
        
        while(in.good() && getline(in, _line)) {
            tok.assign(_line, sep);
            for (tokenizer<char_separator<char> >::iterator it = tok.begin(); it != tok.end(); ++it) {
                _data.push_back(lexical_cast<double>(*it));    
            }
            ++_len;
        }
        _num = _data.size() / _len;
        
        cout << _len << _num << endl;
        in.close();
        
        
        
        
        
        
    }
};

#endif	/* CSVREADERDATA_H */

