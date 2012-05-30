/**
 *
 * @file GLOBAL_VARS.h
 * @author Lars Simon Zehnder
 * 
 * @created May 18, 2012, 4:55 PM
 * 
 * @brief Contains all global variables 
 * 
 */
#ifndef GLOBAL_VARS_H
#define	GLOBAL_VARS_H

/**
 *
 * @brief Global tuning parameters for
 *        MPFR library
 */
extern const int MPFR_PREC_DEFAULT;

/**
 *
 * @brief Global tuning parameters for 
 *        MCMC library
 */
extern const int MCMC_MAX_BONDS;

#define GLOBAL_VAR_DEFS               \
     const int MPFR_PREC_DEFAULT = 53;\
                                      \
     const int MCMC_MAX_BONDS = 100;

#endif	/* GLOBALVARS_H */

