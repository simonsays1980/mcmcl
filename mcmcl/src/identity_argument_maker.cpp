/**
 * 
 * @file identity_argument_maker.cpp
 * @author Lars Simon Zehnder
 * 
 * @created May 19, 2012, 5:55 PM
 * 
 * @brief This class is used to take the values of a 
 *        parameter and send them without alteration to 
 *        @ref mcmc_likelihood. 
 * 
 * The class inherits directly from @ref argument_maker
 * interface class.
 * 
 * @see argument_maker
 * @see mcmc_likelihood
 * 
 */

#include "identity_argument_maker.h"

/**
 * 
 * @brief Custom constructor
 * @param which Identifies the parameter for which the identity argument should
 *        hold.
 * 
 */
identity_argument_maker::identity_argument_maker(int const &which) : which(which) {};

/**
 * 
 * @brief Copy constructor.
 * @param idarg Other %identity_argument_maker from which %this should be constructed. 
 * 
 */
identity_argument_maker::identity_argument_maker(identity_argument_maker const &idarg) {
    this->which = idarg.which;
}

/**
 * 
 * @brief Default destructor.
 * 
 */
identity_argument_maker::~identity_argument_maker() {};

/**
 * 
 * @brief  Converts the parameters into the constant argument.
 * @param  params Parameters to be changed by the argument. 
 * @return Argument.
 * 
 * Inherited from argument_maker.
 * 
 * @see argument_maker
 * 
 */
std::vector<double> identity_argument_maker::getArgument(std::vector<std::vector<double> > const &params) {
    std::vector<double> temp(params[which]);
    
    return temp;
}

/**
 *
 * @brief Custom assignment operator.
 * @param other Other %identity_argument_maker object.
 *
 * Assigns the other identity_argument_maker to this.
 */
identity_argument_maker& identity_argument_maker::operator=(identity_argument_maker const &other) {
	identity_argument_maker temp(other);
	swap(temp);

	return *this;
}

/**
 *
 * @brief Swaps the value from other to this.
 * @param other.
 *
 */
void identity_argument_maker::swap(identity_argument_maker const &other) {
	this->which = other.which;
}
