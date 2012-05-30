/* 
 * File:   Reader.h
 * Author: simonzehnder
 *
 * Created on May 15, 2012, 4:22 PM
 */
#ifndef READER_H
#define	READER_H


using namespace std;

class reader {
public:
    
    virtual ~reader(){};
    //numa_vector<numa_vector<Datatype>* > 
    virtual void read(string& path){};
    
    
};

#endif	/* READER_H */

