/**
 *
 * @file mcmc_update.h
 * @author Lars Simon Zehnder
 * 
 * @created May 19, 2012, 3:51 PM
 *  
 * @brief Interface class that defines all possible steps in a 
 *        MCMC algorithm
 * 
 * This interface class defines all possible steps in an MCMC
 * algorithm. The critical method is, naturally, 
 * @ref mcmc_update::update(), which generates a new value of 
 * the unknown parameters. The other methods are related to 
 * diagnostic output, including numbers of accepted moves.
 * 
 */
#ifndef MCMC_UPDATE_H
#define	MCMC_UPDATE_H

class mcmc_update {
public:
    
    /**
     * 
     * @brief Standard destructor.
     * 
     */
    virtual ~mcmc_update() {};
    
    /**
     * 
     * @brief Defines the update process of a certain object.
     * 
     * Defines the update process of a certain component
     * of the mcmc procedure represented by an object.
     * 
     */
    virtual void update() {};
    
    /**
     * 
     * @brief  Informs about acceptance of a step in the algorithm.
     * @return void.
     * 
     * Information about the acceptance of a certain step in the 
     * mcmc procedure can be used for performance analysis in 
     * regard to convergence of the posterior distribution
     * 
     */
    virtual std::string accepted() {
    	std::string out = "accepted";
    	return out;
    };
    
    /**
     * 
     * @brief Writes update into an output file.
     * 
     * If implemented this function is used to write 
     * the actual output into a provided output file.
     * 
     */
    virtual void updateOutput() {};
    
    /**
     * 
     * @brief Finishes an update step.
     * 
     * If implemented an update step can be finished, 
     * i.e. objects can be deleted or distributed.
     * 
     */
    virtual void finish() {};
};

#endif	/* MCMCUPDATE_H */

