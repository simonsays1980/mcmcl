/* 
 * File:   MCMCInput.h
 * Author: simonzehnder
 *
 * Created on May 15, 2012, 3:27 PM
 */

#ifndef MCMC_INPUT_H
#define	MCMC_INPUT_H

#include <numav/numa_vector.h>
#include <mpfr.h>

template<Datatype>
class mcmc_input {
public:
    numa_vector<int> intValued(string name);
    numa_vector<Datatype> realValued(string name, mpfr_prec_t = MPFR_PREC_DEFAULT);
    
    int MPFR_PREC_DEFAULT = 53;
};

#endif	/* MCMCINPUT_H */

