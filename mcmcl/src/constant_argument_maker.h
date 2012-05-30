/**
 *
 * @file constant_argument_maker.h
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

#ifndef CONSTANT_ARGUMENT_MAKER_H
#define	CONSTANT_ARGUMENT_MAKER_H

#include "argument_maker.h"

class constant_argument_maker : public argument_maker {
public:

    /**
     * 
     * @brief Constructor
     * @param const_val Constant value for the argument.
     * 
     */
    constant_argument_maker(double const &const_val);

    /**
     * 
     * @brief Copy constructor
     * @param other Other %constant_argument_maker.
     * 
     */
    constant_argument_maker(constant_argument_maker const &other);

    /**
     * 
     * @brief Default destructor.
     * 
     */
    ~constant_argument_maker();

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
    std::vector<double> getArgument(std::vector<std::vector<double> > const &params);

    /**
     * 
     * @brief Standard assignment operator.
     * @param other. 
     * 
     * @return this. 
     */
    constant_argument_maker& operator=(constant_argument_maker const &other);

    /**
     * 
     * @brief Constant value, that is used in making the argument. 
     */
    double CONSTANT_VALUE;

private:

    /**
     * 
     * @brief Swaps the value from other to this.
     * @param other.
     * 
     */
    void swap(constant_argument_maker const &other);

};

#endif	/* CONSTANT_ARGUMENT_MAKER_H */

