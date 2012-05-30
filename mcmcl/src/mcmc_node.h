/**
 *
 * @file mcmc_node.cpp
 * @author Lars Simon Zehnder
 * 
 * @created May 19, 2012, 2:40 PM
 * 
 * @brief Defines a data carrying object.
 * 
 * The %mcmc_node is the basic interface class 
 * for all objects in %mcmcl that are to be intended
 * to carry data. One basic inheriting class is 
 * @ref mcmc_parameter.
 * 
 * @see mcmc_parameter
 * 
 */
#ifndef MCMC_NODE_H
#define	MCMC_NODE_H
#include <vector>

class mcmc_node {
    public:
        
        /**
         * 
         * @brief Default destructor.
         * 
         */
        virtual ~mcmc_node() {};
        
        /**
         * 
         * @brief Adds an @ref mcmc_bond to the this node. 
         * 
         * Every node consists of either data or parameters. 
         * Both are used in certain terms of the likelihood. 
         * The terms are represented in within mcmcl as classes
         * inheriting from the @ref mcmc_bond interface class.
         * 
         * @see mcmc_bond
         * 
         */
        virtual void addBond(){};
         
        /**
         *
         * @brief Holds the values of either parameters or data.
         * 
         */
        std::vector<double> value;        
};
#endif	/* MCMCNODE_H */

