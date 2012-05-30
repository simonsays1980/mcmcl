/**
 *
 * @file argument_maker.h
 * @author Lars Simon Zehnder
 * 
 * @created My 19, 2012, 3:53 PM
 * 
 * @brief Converts parameters and data values into
 *        arguments.
 * 
 * Important interface class that is used in defining statistical
 * models in mcmcl. %argument_makers accept raw values of parameters 
 * as inputs and convert them into arguments for @ref mcmc_likelihoods. 
 * Examples: if y_{i,j} ~N(mu_{i}, sigma^2), and {y, mu, sigma} are 
 * all @ref mcmc_parameters, an identity_argument will generally be used
 * to create the y argument, a group_argument will be used to make 
 * an array of mu the same length as y and with mu_{i} matched with each
 * of the y_{ij}s, and another group_argument will be used to make an 
 * array of the same length as y, each of whose values is the scalar 
 * sigma.
 * 
 * @see mcmc_parameter
 * @see basic_mcmc_bond
 * @see mcmc_likelihood
 * 
 */
#ifndef ARGUMENT_MAKER_H
#define	ARGUMENT_MAKER_H

#include <vector>

class argument_maker {
public:
    /**
     * 
     * @brief Default destructor.
     * 
     */
    virtual ~argument_maker() {};
    
    /**
     * 
     * @brief Computes the argument for a certain parameter vector.
     * @param _params Input parameters for which the argument should 
     *        be computed.
     * 
     * This the basic function to be implemented by every class
     * inheriting from this interface. 
     * 
     * @see constant_argument
     * @see identity_argument
     * @see group_argument
     * 
     */
    virtual std::vector<double> getArgument (std::vector<std::vector<double> > const &params) {return params[0];};
    
};

#endif	/* ARGUMENT_MAKER_H */

