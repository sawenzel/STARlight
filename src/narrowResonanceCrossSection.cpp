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
//
//
//
///////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <cmath>

#include "starlightconstants.h"
#include "narrowResonanceCrossSection.h"


using namespace std;
using namespace starlightConstants;


//______________________________________________________________________________
narrowResonanceCrossSection::narrowResonanceCrossSection(const beamBeamSystem&  bbsystem)
	:photonNucleusCrossSection(bbsystem)
{
	_narrowYmax = inputParametersInstance.maxRapidity();
	_narrowYmin = -1.0*_narrowYmax;
	_narrowNumY = inputParametersInstance.nmbRapidityBins();
	_Ep         = inputParametersInstance.protonEnergy();	
}


//______________________________________________________________________________
narrowResonanceCrossSection::~narrowResonanceCrossSection()
{ }


//______________________________________________________________________________
void
narrowResonanceCrossSection::crossSectionCalculation(const double)  // _bwnormsave (unused)
{
	// This subroutine calculates the vector meson cross section assuming
	// a narrow resonance.  For reference, see STAR Note 386.
  
	// double Av,Wgp,cs,cvma;
	double W,dY;
	double y1,y2,y12,ega1,ega2,ega12;
	// double t,tmin,tmax;
	double csgA1,csgA2,csgA12,int_r,dR,rate;
	double tmp;
	// double ax,bx;
	double Eth;
	int    J,NY;
	// int    K,NGAUSS;
  
	NY   =  _narrowNumY;
	dY   = (_narrowYmax-_narrowYmin)/double(NY);
  
	cout<<" Using Narrow Resonance ..."<<endl;
  
	W = getChannelMass();
	Eth=0.5*(((W+protonMass)*(W+protonMass)-
	          protonMass*protonMass)/(_Ep+sqrt(_Ep*_Ep-protonMass*protonMass)));
  
	cout<<" gamma+nucleon  Threshold: "<<Eth<<endl;
	int_r=0.;
  
	tmp = 0.0;
  
	for(J=0;J<=(NY-1);J++){
    
		y1  = _narrowYmin + double(J)*dY;
		y2  = _narrowYmin + double(J+1)*dY;
		y12 = 0.5*(y1+y2);
    
		ega1  = 0.5*W*exp(y1);
		ega2  = 0.5*W*exp(y2);
		ega12 = 0.5*W*exp(y12);
    
		if(ega1 < Eth)   
			continue;
		if(ega2 > maxPhotonEnergy()) 
			continue;

		csgA1=getcsgA(ega1,W);
    
		// Middle Point                      =====>>>
		csgA12=getcsgA(ega12,W); 

		// Second Point                      =====>>>
		csgA2=getcsgA(ega2,W);
    
		// Sum the contribution for this W,Y.
		dR  = ega1*photonFlux(ega1)*csgA1;
		dR  = dR + 4.*ega12*photonFlux(ega12)*csgA12;
		dR  = dR + ega2*photonFlux(ega2)*csgA2;
		tmp = tmp+2.*dR*(dY/6.);
		dR  = dR*(dY/6.);

		// cout<<" y: "<<y12<<" egamma: "<<ega12<<" flux: "<<photonFlux(ega12)<<" sigma_gA: "<<10000000.*csgA12<<" dsig/dy (microb): "<<10000.*dR/dY<<endl;

		// The 2 accounts for the 2 beams
		if(getbbs().beam1().A()==getbbs().beam2().A()){
			dR  = 2.*dR;
		}
		int_r = int_r+dR;
	}
	rate=luminosity()*int_r;
	cout<<" Cross section (mb): " <<10.*int_r<<endl;
}
