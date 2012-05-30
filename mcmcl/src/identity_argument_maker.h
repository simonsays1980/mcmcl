/**
 *
 * @brief This class is used to take the values of a 
 *        parameter and send them without alteration to 
 *        @link mcmc_likelihood.
 * 
 * @author Lars Simon Zehnder
 * @see mcmc_likelihood
 *
 */
#ifndef IDENTITY_ARGUMENT_MAKER_H
#define	IDENTITY_ARGUMENT_MAKER_H

#include "argument_maker.h"

class identity_argument_maker : public argument_maker {
public:
    
	/**
	 *
	 * @brief Custom constructor.
	 *
	 */
    identity_argument_maker (int const &which);
    
    /**
     *
     * @brief Copy constructor
     * 
     */
    identity_argument_maker (identity_argument_maker const &idarg);
    
    
    /**
     *
     * @brief Default destructor
     * 
     */
    ~identity_argument_maker();
    
    /**
     *
     * @brief Converts the parameters into the constant argument.
     * 
     * Inherited from argument_maker.
     * 
     * @see argument_maker
     */
    std::vector<double> getArgument(std::vector<std::vector<double> > const &params); 
    
    /**
     *
     * @brief Custom assignment operator.
     * @param other Other %identity_argument_maker object.
     *
     * Assigns the other identity_argument_maker to this.
     */
    identity_argument_maker& operator=(identity_argument_maker const &other);

private:
    /**
     * @brief Stores the index of the vector to be given back in
     *        %identity_argument_maker::getArgument.
     */
    int which;

    /**
     *
     * @brief Swaps the value from other to this.
     * @param other.
     *
     */
    void swap(identity_argument_maker const &other);
};

#endif	/* IDENTITY_ARGUMENT_MAKER_H */

