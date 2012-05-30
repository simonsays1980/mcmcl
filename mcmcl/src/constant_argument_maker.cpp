/**
 * 
 * @file constant_argument_maker.cpp
 * @author Lars Simon Zehnder
 * 
 * @created May 19, 2012, 3:55 PM
 * 
 * @brief Prepares parameters and data with a 
 *        constant-value transformation.
 * 
 * The parameters or the data are transformed into 
 * an equal-sized vector of a constant. 
 * 
 */


#include <vector>

#include "constant_argument_maker.h"

/**
 * 
 * @brief Constructor
 * @param const_val Constant value for the argument.
 * 
 */
constant_argument_maker::constant_argument_maker(double const &const_val) : CONSTANT_VALUE(const_val) {};

/**
 * 
 * @brief Copy constructor
 * @param other Other %constant_argument_maker.
 * 
 */
constant_argument_maker::constant_argument_maker(constant_argument_maker const &other) {
    this->CONSTANT_VALUE = other.CONSTANT_VALUE;
}

/**
 * 
 * @brief Default destructor.
 * 
 */
constant_argument_maker::~constant_argument_maker(){};

/**
 * 
 * @brief Computes the argument for a certain parameter vector.
 * @param params Input parameters for which the argument should 
 *        be computed.
 * @return Transformed parameter vector.
 * 
 * Inherited from the interface class @ref argument_maker.
 * 
 * @see argument_maker
 */
std::vector<double> constant_argument_maker::getArgument(std::vector<std::vector<double> > const &params) {
    std::vector<double> temp(params[0].size(), CONSTANT_VALUE);
    
    return temp;
}
 
/**
 * 
 * @brief Standard assignment operator.
 * @param other. 
 * 
 * @return this. 
 */
constant_argument_maker& constant_argument_maker::operator=(constant_argument_maker const &other) {
    constant_argument_maker temp(other);
    this->swap(temp);

    return *this;
}

/**
 * 
 * @brief Swaps the value from other to this.
 * @param other.
 * 
 */
void constant_argument_maker::swap(constant_argument_maker const &other) {
    this->CONSTANT_VALUE = other.CONSTANT_VALUE;
}

