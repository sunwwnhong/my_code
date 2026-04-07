 /*
 * Spd15_Estimate.h
 *
 *  Created on: 2020Äê4ÔÂ23ÈÕ
 *      Author: zhuxc
 */
 #ifndef Spd15_Estimate_H
#define Spd15_Estimate_H
 
  
 typedef struct {
		double	 u[2];							 
        double   y[2];                           
        double   Theta[2];                       
		double   Phi[2];			             
		double   yError;		                 
        double   Tau[2][2];                      
        double   yEstimated;                     
        double   TauPhi[2];
        double   denomi;
        double   Lamda;                          
        double   LamdaInv;
         double   Intero;                         
        double   Friction;                       
}RLSSTRUCT;
extern RLSSTRUCT RLSv;
 extern void Estimate_Main( void );
extern void Estimate_Init( void );
extern void ParamEst_Calc( void );
extern void EstimateSpdUpdate( void );
extern void EstimateTimeUpdate( void );
 #endif
 
