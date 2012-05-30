/*
 * @file mcmc_bond.h
 * @author Lars Simon Zehnder
 * 
 * @created May 19, 2012, 2:22 PM
 * 
 * @brief Defines a term in the posterior.
 * 
 * Interface class that defines terms in the posterior distribution.
 * A statistical model is considered to be a product of %mcmc_bonds.
 * The critical methods are the compute methods, which calculate 
 * differences of logged values of the terms, at the proposed new value
 * of the parameters minus the current value. Main inheriting class is
 * @ref basic_mcmc_bond. 
 * 
 * @see basic_mcmc_bond
 *
 */
#ifndef MCMC_BOND_H
#define	MCMC_BOND_H
#include <vector>

class mcmc_bond {
public:
    
    /*
     * @brief Default destructor.
     * 
     */
    virtual ~mcmc_bond() {};
    
    /*
     * @brief Computes the difference in the posterior term.
     * @param whatami Indicates the corresponding parameter for which
     *        the bond is relevant.
     * @param newpar The newly proposed parameter candidate with which the 
     *        bond should be computed. 
     * @param which The index of the parameter in @ref mcmc_parameter::value.
     * 
     * This function computes the log likelihood and returns its value for
     * the bond.
     * 
     */
    virtual double compute(int whatami, double newpar, int which) {return newpar;};
    
    /*
     * @brief Revises the bond's current value to the new value.
     * 
     * To ensure performance %mcmc_bonds are holding their current
     * value until the next replication of the algorithm. If the 
     * newly proposed parameter value is accepted the bonds current
     * value is revised. Otherwise the current value remains for the 
     * next replication. 
     * 
     */
    virtual void revise() {};
};

#endif	/* MCMCBOND_H */

