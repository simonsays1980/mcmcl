/**
 *
 * @file mcmc_likelihood.h
 * @author Lars Simon Zehnder
 * 
 * @created May 19, 2012, 2:52 PM
 * 
 * @brief The functional form of logs in the posterior. 
 * 
 * This interface class is used for logs of likelihoods as well as
 * for priors, so the name maybe misleading.
 *  
 */
#ifndef MCMC_LIKELIHOOD_H
#define	MCMC_LIKELIHOOD_H

#include <vector>

class mcmc_likelihood {
public:
    
    /**
     * 
     * @brief Default destructor.
     */
    virtual ~mcmc_likelihood() {};
    
    /**
     * 
     * @brief Computes the likelihood of the model.
     * @param args A rectangular vector of arguments.
     * 
     * The arguments are assumed be ordered together in
     * equal-sized vectors, e.g. for the Gaussian likelihood
     * the first vector contains the observations, the second 
     * vector contains the means for each observation and the 
     * third column contains the standard deviation for each
     * observation.
     * Classes using the @ref argument_maker interface class
     * are used to arrange this. 
     * 
     * @see argument_maker 
     * 
     */
    virtual double compute (std::vector<std::vector<double> > args) {
    	double temp = 0;
    	return temp;
    };
};
#endif	/* MCMC_LIKELIHOOD_H */

