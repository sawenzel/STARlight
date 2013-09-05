///////////////////////////////////////////////////////////////////////////
//
//    Copyright 2010
//
//    This file is part of starlight.
//
//    starlight is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    starlight is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with starlight. If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////
//
// File and Version Information:
// $Rev::                             $: revision of last commit
// $Author::                          $: author of last commit
// $Date::                            $: date of last commit
//
// Description:
//     this class covers a coliding beam system SK
//
//
//
///////////////////////////////////////////////////////////////////////////


#ifndef BEAMBEAMSYSTEM_H
#define BEAMBEAMSYSTEM_H


#include "nucleus.h"
#include "beam.h"
#include <vector>

class beamBeamSystem
{

public:

	beamBeamSystem(const beam&            beam1,
	               const beam&            beam2,
	               const inputParameters& parameters);
	beamBeamSystem(const inputParameters& parameters);
	~beamBeamSystem();

	const beam& beam1() const { return _beam1; }  ///< returns beam particle 1
	const beam& beam2() const { return _beam2; }  ///< returns beam particle 2

	//	double getluminosity();
	double probabilityOfBreakup(const double D) const;
	
	double cmsBoost() const { return _cmsBoost; }
	
	double beamLorentzGamma() const { return _beamLorentzGamma; }
	
	void init(const inputParameters &p);

private:
	void generateBreakupProbabilities();
	//	int _ibreakup;//temporary solution until read in parameters are done
	double probabilityOfHadronBreakup(const double impactparameter);
	double probabilityOfPhotonBreakup(const double impactparameter, const int mode);

	double _pHadronBreakup;
	double _pPhotonBreakup;
	//inputParameters inputbbs;
	//		double luminosity;

	double _beamLorentzGamma;  ///< Lorentz gamma factor of beams in collider frame
	int    _beamBreakupMode;   ///< \brief breakup mode for beam particles
	                           ///<
	                           ///< 1 = hard sphere nuclei (b > 2R),
	                           ///< 2 = both nuclei break up (XnXn),
	                           ///< 3 = a single neutron from each nucleus (1n1n),
	                           ///< 4 = neither nucleon breaks up (with b > 2R),
	                           ///< 5 = no hadronic break up (similar to option 1, but with the actual hadronic interaction)
	               
	beam   _beam1;             ///< beam particle 1
	beam   _beam2;             ///< beam particle 2

	double _cmsBoost;	   ///< Rapidity boost of the CMS wrt the lab system
	
	std::vector<double> _breakupProbabilities; ///< Vector containing breakup probabilities for impact parameters
	double _breakupImpactParameterStep; ///< Step size in the calculation of the breakup probs
	double _breakupCutOff;  ///< Cut off for minimum impact parameter probability
};


#endif  // BEAMBEAMSYSTEM_H
