/**
 * 
 * @file: mcmc_parameter.cpp
 * @author Lars Simon Zehnder
 * 
 * @created May 19, 2012, 1:36 PM
 * @ingroup mcmcl
 * 
 * @brief Stores any targets of the posterior.
 * 
 * Any quantity whose posterior distribution one seeks in %mcmcl
 * has its values stored in an %mcmc_parameter (or one of its
 * subclasses). A parameter has a value which can be a vector and 
 * which gets changed as the algorithm runs, a set of step sizes 
 * of the same length as the value, and a name. Also, since the 
 * %mcmc_parameter class implements the @ref mcmc_update interface
 * class, a parameter knows how to update itself. It does this by 
 * looping over its components, and for each one attempting to make
 * a Gaussian move according to a random walk Metropolis proposal.
 * 
 * @see mcmc_update
 * 
 */

#ifndef MCMC_PARAMETER_H
#define	MCMC_PARAMETER_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <vector>
#include <string>
#include "mcmc_update.h"
#include "mcmc_bond.h"
#include "mcmc_node.h"
#include "GLOBAL_VARS.h"

class mcmc_parameter : public mcmc_update, public mcmc_node {
public:
    
    /**
     * 
     * @brief Constructor 
     * @param initPar Initial parameters given as start values 
     *        to the algorithm.
     * @param mss Step sizes determining the update process of
     *        the parameters
     * @param name Name of an output file @ref name. 
     * 
     */
    mcmc_parameter(std::vector<double> const &initPar, std::vector<double> const &mss,
    std::string const &name) : value(initPar), mss(mss), name(name) {};
    
    /**
     * 
     * @brief Copy constructor.
     * @param other Other %mcmc_parameter object.
     * 
     * Copies the initial parameters, step sizes and the name of
     * the output file. These are the stateless indicators of
     * the %mcmc_parameter class interface.
     *
     */
    mcmc_parameter(mcmc_parameter const &other) {
        this->value = other.value;
        this->mss = other.mss;
        this->name = other.name;
    }
    
    /**
     * 
     * @brief Default destructor.
     * 
     */
    virtual ~mcmc_parameter() {};
    /**
     * @brief Informs about acceptance of a step in the algorithm
     * 
     * Information about the acceptance of a certain step in the 
     * mcmc procedure can be used for performance analysis in 
     * regard to convergence of the posterior distribution
     * 
     * @return Information of acceptance.
     *  
     */
    virtual std::string accepted() {
    	std::string out = "accepted";
    	return out;
    };
    
    /**
     * 
     * @brief Updates parameters 
     * 
     * Inherited from @ref mcmc_update interface class. Note, that
     * parameters are proposed and accepted independently from each 
     * other in this implementation.
     *  
     * @see mcmc_update.
     * 
     */
   virtual void update() {
        if(const_val) {
            return;
        }
        while(turn < value.size()) {
            candidate = proposal()[0];
            proposed[turn] = candidate;
            double ap = acceptanceP();
            if(ap > uni_dist(uni_gen)) {
                //takeStep();
            }
            ++turn;
        }
    }
    
    
    /**
     *
     * @brief Proposes a new candidate for the parameter at turn. 
     * 
     * This function returns a vector and it is intended 
     * to be overridden by inheriting classes. To enable inheriting 
     * classes of %mcmc_parameter to define multivariate candidate() 
     * functions a multivariate return value is provided. 
     * 
     * @return A proposal for new parameter value(s).
     */
    virtual std::vector<double> proposal() {
        double res = value[turn] +  dist(gen) * mss[turn];
        std::vector<double> temp(1, res);
        
        return temp;
    }
    
    /**
     * 
     * @brief Computes the acceptance probability for the newly 
     *        proposed parameter value that is in turn to be changed. 
     * 
     * Note that likelihood ratios are computed via @ref mcmc_bonds
     * and that they are used in logged form. This makes computation 
     * more efficient. 
     * The @ref mcmc_bond gets the index of %this - the %mcmc_parameter that 
     * handles over the new proposal @ref candidate and which of the 
     * parameters in %mcmc_parameter::value is in turn. 
     * 
     * @return Acceptance probability.
     * 
     */
    virtual double acceptanceP() {
        double lr = 0;
        for (size_t i = 0; i < bonds.size(); ++i) {
            lr += bonds[i].compute(whatami[i], candidate, turn);
        }
        
        return exp(lr);
    } 
    
    /**
     * 
     * @brief Changes all necessary variables after acceptance.
     * 
     * After a newly proposed parameter has been accepted the bonds
     * current value must be revised and the new parameter value has 
     * to be stored in its appropriate container %value. Furthermore,
     * the counter for acceptance is incremented by one for the 
     * parameter at hand. 
     * 
     */
    void takeStep() {
        value[turn] = candidate;
        for(size_t i = 0; i < bonds.size(); ++i) {
             bonds[turn].revise();    
        }
        ++accs[turn];
    }
    
    /**
     * 
     * @brief Adds a bond to the bond container.
     * @param bond An object inheriting from the 
     *        @ref mcmc_bond interface class.
     * @param which Identifies the corresponding parameter
     *        for which the bond should be relevant.
     * 
     * All bonds are stored to the @ref bonds vector. 
     * 
     */
    virtual void addBond(mcmc_bond const &bond, int const &which) {
        if(numbonds < GLOBAL_VARS_H::MCMC_MAX_BONDS) {
            bonds.push_back(bond);
            ++numbonds;
        }
    } 
    
    /**
     * 
     * @brief Cleans up and closes file streams. 
     * 
     */
    virtual void finish() {};
    
    /**
     * @brief Stores parameter values. 
     * 
     */
    std::vector<double> value;
    
    /**
     * 
     * @brief Step sizes for the parameters.
     * 
     * Stores the provided step sizes of the 
     * parameters. Step sizes take corresponding data 
     * types as their parameters.
     * 
     */
    std::vector<double> mss;
    
    /**
     *
     * @brief Filename into which the updated parameters
     *        should be stored.
     * 
     * If given, the updated parameters are stored via 
     * the inherited function @output() into a file called
     * <name>.out.
     */
    std::string name;
    
    /**
     * 
     * @brief Container for all bonds needed for the parameter update.
     * 
     */
    std::vector<mcmc_bond> bonds; 
    
    /**
     *
     * @brief Defining constant parameter.
     * 
     * Note: constant parameters are not being
     * updated. 
     * 
     */
    bool const_val;
    
    /**
     *
     * @brief Stores the number of acceptances for a certain
     *        parameter.
     * 
     * The number of acceptances for a parameter is important
     * for tuning an MCMC algorithm. 
     * 
     */
    std::vector<int> accs;
    
private:
    
    /**
     * 
     * @brief Temporary variable used in @link candidate().
     * 
     * To ensure performance the temporary variable should
     * not be constructed in each step and sub-step of the 
     * algorithm.
     *  
     */
    double candidate;  
    
    /**
     * 
     * @brief Container to store all temporary proposed values.
     * 
     * To ensure performance the temporary variable should
     * not be constructed in each step and sub-step of the 
     * algorithm.
     * 
     */
    std::vector<double> proposed;
    
    /**
     *
     * @brief Variable identifying which parameter is at turn
     *        to be updated.
     * 
     */
    size_t turn;
    
    /**
     * 
     * @brief Holds the number of bonds in the parameters update.
     * 
     */
    int numbonds;
    
    /**
     *
     * @brief Random number generator for the parameter proposal.
     * 
     * It is used a Mersenne-Twister algorithm from the boost random
     * library.
     * 
     */
    boost::random::mt19937 gen;
    
    /**
     *
     * @brief Random number generator for the parameter acceptance.
     * 
     * It is used a Mersenne-Twister algorithm from the boost random
     * library.
     * 
     */
    boost::random::mt19937 uni_gen;
    
    /**
     *
     * @brief Gaussian distribution object for the parameter proposal.
     * 
     * The Gaussian distribution is from the boost random library.
     * 
     */
    boost::random::normal_distribution<double> dist;
    
    /**
     *
     * @brief Gaussian distribution object for the parameter acceptance.
     * 
     * The uniform distribution is from the boost random library.
     * 
     */
    boost::random::uniform_01<double> uni_dist;
    
    /**
     *
     * @brief States for each bond its corresponding parameter. 
     * 
     * When a new @ref mcmc_bond is added to the bond vector %bonds, the 
     * %whatami vector holds the corresponding parameter for which this bond
     * is relevant.  
     * 
     * @see mcmc_bond 
     */
    std::vector<int> whatami;
};


#endif	/* MCMCPARAMETER_H */

