/* 
 * File:   DataFrame.h
 * Author: simonzehnder
 *
 * Created on May 15, 2012, 3:33 PM
 */

#ifndef DATA_FRAME_H
#define	DATA_FRAME_H

#include "mcmc_input.h"
#include <mpfr.h>
#include "GLOBAL_VARS.h"

template<Datatype>
class data_frame : mcmc_input {
    public: 
        data_frame(string path, mpfr_prec_t precision = GLOBAL_VARS::MPFR_PREC_DEFAULT);
        data_frame(const data_frame &_dataf);
        ~data_frame();
        
        numa_vector<int> intValued(string name);
        numa_vector<Datatype> realValued(string name, mpfr_prec_t precision = GLOBAL_VARS::MPFR_PREC_DEFAULT);
        
    private:
        void readData(string path) {
            
        };
            
};

#endif	/* DATAFRAME_H */

