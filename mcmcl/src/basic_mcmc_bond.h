/**
 * 
 * @file basic_mcmc_bond.h
 * @author Lars Simon Zehnder
 * 
 * @created May 18, 2012, 6:40 PM
 *  
 * @brief Fundamental class in mcmcl, that defines a 
 *        statistical model. 
 * 
 * A bond first consists of one or more parameters.   
 * It also includes one or more ArgumentMakers, which convert the 
 * values of the parameters into arguments for the Likelihood function.  
 * The %basic_mcmc_bond consists on default only of an 
 * @ref identity_argument_maker, and an @ref mcmc_likelihood. 
 * When @ref basic_mcmc_bond::compute is called, the parameters are prepared
 * by the @ref argument_makers and then the old value is subtracted from the 
 * new likelihood value. 
 * Likelihood is a bad name actually, as the function is not restrained on a
 * standard likelihood function. It can be as well only a part of a 'true'
 * likelihood function. 
 * 
 * @see mcmc_bond
 * @see mcmc_likelihood
 * @see argument_maker
 * 
 */
#ifndef BASIC_MCMC_BOND_H
#define	BASIC_MCMC_BOND_H

#include "mcmc_bond.h"
#include "mcmc_parameter.h"
#include "identity_argument_maker.h"
#include "mcmc_likelihood.h"
#include "argument_maker.h"

class basic_mcmc_bond : public mcmc_bond {
public:
    
    /**
     * 
     * @brief Custom constructor.
     * @param lik Likelihood function to be computed for this bond. 
     * @param par Parameters to be part of the likelihood function.
     * 
     */
    basic_mcmc_bond(mcmc_likelihood const &lik, std::vector<mcmc_parameter> const &par) : 
    lik(lik), par(par) {
        
    }
    
    /**
     * @brief Main constructor
     * @param argm argm Vector of type @ref argument_maker holding transformations
     *        for parameters.
     * @param lik Log-likelihood function used in this bond.
     * @param par Parameters relevant for the bond. 
     * 
     * Note, that all @ref mcmc_parameter add the bond into their bond list. 
     * On the other side the bond adds all these parameters to its parameter list.
     * 
     */
    basic_mcmc_bond(std::vector<argument_maker> argm, mcmc_likelihood lik,
    std::vector<mcmc_parameter> par) {
        this->argms = argm;
        this->lik = lik;
        this->par = par;
        size_t i; 
        for(i = 0; i < par.size(); ++i){
            par[i].addBond(*this, i);
        }
    }
    /**
     * 
     * @brief Default destructor.
     * 
     */
    virtual ~basic_mcmc_bond () {};
    
    /**
     * @brief Does all necessary steps for preparing the 
     *        parameters to get altered through their 
     *        corresponding @ref argument_maker.
     * 
     * Note, that par is a vector of @ref mcmc_parameter and 
     * mcmc_parameter::value is a double vector of the respective 
     * parameter values. 
     * 
     * @see argument_maker
     * 
     */
    virtual void prepareArgs() {
        for(size_t i = 0; i < par.size(); ++i) {
            preargs.push_back(par[i].value);
        }
    }
    /**
     * 
     * @brief Subtracts the %current_value of the bond from the
     *        the new value.
     * 
     * To ensure performance the current value of a bond is always
     * hold in the %basic_mcmc_bond object. 
     * 
     */
    virtual void subtractOld() {
        if(this->value_computed) {
            this->logr -= current_value;
        } else {
            for (size_t i = 0; i < am.size(); ++i) {
                args[i] = am[i].getArgument(preargs);
            }
            this->value_computed = true;
            current_value = lik.compute(args);
            logr -= current_value;
        }
    }
    
    /**
     * 
     * @brief  Computes all necessary steps to update the bond.
     * @param  whatami Determines the affiliation to the appropriate 
     *         @ref mcmc_parameter vector.
     * @param  newpar The new proposal for the parameter in turn. 
     * @param  which Defines the entry in the parameter vector for which the 
     *         change in bond should be determined. 
     * @return The computed bond value.
     * 
     * For all steps (stages) of the process see the comment 
     * on @ref stage1().
     * 
     */
    virtual double compute(int whatami, double newpar, int which) {
        stage1();
        changeParameters(whatami, newpar, which);
        addNew();

        return logr;
    }
    
    /**
     * 
     * @brief If the current value is accepted this function updates the 
     *        current_value of the bond. 
     * 
     * The function is usually called by a class implementing the interface 
     * class  @ref mcmc_update.
     * 
     * @see mcmc_update.
     * 
     */
    virtual void revise() {
        current_value = new_value;
    }
    
    /**
     *
     * @brief Container collecting all %argument_makers to be
     *        used.
     * 
     * Note that @link argument_maker is an interface class from
     * which all other %argument_maker specializations inherit, 
     * i.e. all kinds of argument_makers can be stored. 
     * 
     * @see argument_maker
     * @see constant_argument_maker
     * @see group_argument_maker
     * 
     */
    std::vector<argument_maker> argms;
    
    /**
     * @brief The likelihood function determining the model. 
     * 
     */
    mcmc_likelihood lik;
    
    /**
     * @brief Parameters used in this %mcmc_bond.
     *  
     */
    std::vector<mcmc_parameter> par;
    
private:
    
    /**
     * 
     * @brief Performs first steps of the bond computation.
     * 
     * Altogether there are three steps: 
     *  1. Set the log-value to its initial state = zero. 
     *     Prepare all parameters (nodes) for their transformation
     *     through @link argument_makers. And subtract the old log-
     *     value from the new one 
     *  2. Set the relevant parameters (nodes) to be changed. 
     *  3. Calculate the logged difference of the bond.
     * 
     */
    void stage1() {
        logr = 0;
        prepareArgs();
        subtractOld();
    }
    
    /**
     * 
     * @brief Stores the relevant parameters to be changed into the %preargs
     *        vector.
     * @param whatami Indicates which @ref mcmc_parameter is relevant to 
     *        compute the bond.
     * @param cand the proposed candidate for the parameter in turn.
     * @param which The parameter which is in turn.
     * 
     * Remember in the %preargs are several columns (%vectors) as there maybe
     * several parameter vectors belonging to a bond.
     * Note also, that %whatami is the integer vector in @ref mcmc_parameter 
     * that is relevant for the bond, i.e. that became the %mcmc_bond added.  
     * 
     */
    void changeParameters(int const whatami, double const cand, int const which) {
        preargs[whatami][which] = cand;
    }
    
    /**
     * 
     * @brief Calculates the value of the likelihood for the new value proposed.
     * 
     * The function first transforms the parameters values (data values) via 
     * the appropriate @ref argument_maker. 
     * Then the transformed values are used in the likelihood term to be added to the 
     * %basic_mcmc_bond::logr value. 
     * 
     */
    void addNew() {
        for(size_t i = 0; i < args.size(); ++i) {
            new_args[i] = am[i].getArgument(preargs); 
        }   
        new_value = lik.compute(new_args);
        logr += new_value;
    }
    
    /**
     * @brief Determines if the bond has been already computed. 
     * 
     */
    bool value_computed;
    
    /**
     * @brief Stores the value of the logged bond. 
     * 
     */
    double logr;
    
    /**
     * @brief Stores the current value of the bond.
     * 
     */
    double current_value;
    
    /**
     * @brief Stores the new value of the bond.
     * 
     * The new value is the value for the proposed 
     * parameters.
     * 
     */
    double new_value;
    
    /**
     * 
     * @brief Stores the @link argument_makers for preparing
     *        the parameters.
     *    
     * @see argument_maker
     * 
     */
    std::vector<argument_maker> am;
    
    /**
     * 
     * @brief Stores the prepared values for computing the 
     *        the bond.
     * 
     */
    std::vector<std::vector<double> > args;
    
    /**
     * 
     * @brief Stores the parameters before preparing them via
     *        @link argument_maker.
     * 
     * @see argument_maker
     * 
     */
    std::vector<std::vector<double> > preargs;
    
    /**
     * @brief Stores the new parameters (nodes) after being prepared
     *        for bond computation.
     * 
     */
    std::vector<std::vector<double> > new_args;
};
#endif	/* BASIC_MCMC_BOND_H */

