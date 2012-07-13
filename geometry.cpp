#include "stdafx.h"
#include "math.h"
#include "geometry.h"


double geometryTableSin[360];
double geometryTableCos[360];
double geometryTableArcTan[20000];

int geometryInit()
{
	int i;
	for(i=0;i<359;i++)
	{
		geometryTableSin[i]=sin(i*GEOMETRY_PI/180);
		geometryTableCos[i]=cos(i*GEOMETRY_PI/180);
	}
	for(i=0;i<20000;i++)
	{
		geometryTableArcTan[i]=atan((double)(i/100-100))*180/GEOMETRY_PI;
	}
	return 1;
}
double geometrySin(double angle)
{
	return geometryTableSin[((int)angle)%360];
}
double geometryCos(double angle)
{
	return geometryTableCos[((int)angle)%360];
}
double geometryArcTan(double ratio)
{
	ratio=ratio*100;
	if (ratio<-10000)
		ratio=-10000;
	if (ratio>9999)
		ratio=9999;

//	return geometryTableArcTan[(int)ratio+10000];
return atan((double)ratio/100)*180/GEOMETRY_PI;

}
//----------------------------------------------------------------------------
double DistancePointEllipseSpecial (double dU, double dV, double dA, double dB, const double dEpsilon, const int iMax, int& riIFinal, double& rdX, double& rdY)
{
	// initial guess
	double dT = dB*(dV - dB);
	// Newton’s method
	int i;
	for (i = 0; i < iMax; i++)
	{
		double dTpASqr = dT + dA*dA;
		double dTpBSqr = dT + dB*dB;
		double dInvTpASqr = 1.0/dTpASqr;
		double dInvTpBSqr = 1.0/dTpBSqr;
		double dXDivA = dA*dU*dInvTpASqr;
		double dYDivB = dB*dV*dInvTpBSqr;
		double dXDivASqr = dXDivA*dXDivA;
		double dYDivBSqr = dYDivB*dYDivB;
		double dF = dXDivASqr + dYDivBSqr - 1.0;
		if (dF < dEpsilon)
		{
			// F(t0) is close enough to zero, terminate the iteration
			rdX = dXDivA*dA;
			rdY = dYDivB*dB;
			riIFinal = i;
			break;
		}
		double dFDer = 2.0*(dXDivASqr*dInvTpASqr + dYDivBSqr*dInvTpBSqr);
		double dRatio = dF/dFDer;
		if (dRatio < dEpsilon)
		{
			// t1-t0 is close enough to zero, terminate the iteration
			rdX = dXDivA*dA;
			rdY = dYDivB*dB;
			riIFinal = i;
			break;
		}
		dT += dRatio;
	}
	if (i == iMax)
	{
		// method failed to converge, let caller know
		riIFinal = -1;
		return -9999;
	}
	double dDelta0 = rdX - dU, dDelta1 = rdY - dV;
	return sqrt(dDelta0*dDelta0 + dDelta1*dDelta1);
}

//----------------------------------------------------------------------------
double DistancePointEllipse
	(
	double dU, double dV,		// test point (u,v)
	double dA, double dB,		// ellipse is (x/a)^2 + (y/b)^2 = 1
	const double dEpsilon,		// zero tolerance for Newton’s method
	const int iMax,				// maximum iterations in Newton’s method
	int& riIFinal,				// number of iterations used
	double& rdX, double& rdY	// a closest point (x,y)
)
{
	// special case of circle
	
	/*
	if (fabs(dA-dB) < dEpsilon)
	{
		double dLength = sqrt(dU*dU+dV*dV);
		return fabs(dLength - dA);
	}
	*/
	// reflect U = -U if necessary, clamp to zero if necessary
	bool bXReflect;
	if (dU > dEpsilon)
	{
		bXReflect = false;
	}
	else 
		if (dU < -dEpsilon)
		{
			bXReflect = true;
			dU = -dU;
		}
		else
		{
			bXReflect = false;
			dU = 0.0;
		}
	// reflect V = -V if necessary, clamp to zero if necessary
	bool bYReflect;
	if (dV > dEpsilon)
	{
		bYReflect = false;
	}
	else
		if (dV < -dEpsilon)
		{
			bYReflect = true;
			dV = -dV;
		}
		else
		{
			bYReflect = false;
			dV = 0.0;
		}
	// transpose if necessary
	double dSave;
	bool bTranspose;
	if (dA >= dB)
	{
		bTranspose = false;
	}
	else
	{
		bTranspose = true;
		dSave = dA;
		dA = dB;
		dB = dSave;
		dSave = dU;
		dU = dV;
		dV = dSave;
	}
	double dDistance;
	if (dU != 0.0)
	{
		if (dV != 0.0)
		{
			dDistance = DistancePointEllipseSpecial(dU,dV,dA,dB,dEpsilon,iMax,
			riIFinal,rdX,rdY);
		}
		else
		{
			double dBSqr = dB*dB;
			if (dU < dA - dBSqr/dA)
			{
				double dASqr = dA*dA;
				rdX = dASqr*dU/(dASqr-dBSqr);
				double dXDivA = rdX/dA;
				rdY = dB*sqrt(fabs(1.0-dXDivA*dXDivA));
				double dXDelta = rdX - dU;
				dDistance = sqrt(dXDelta*dXDelta+rdY*rdY);
				riIFinal = 0;
			}
			else
			{
				dDistance = fabs(dU - dA);
				rdX = dA;
				rdY = 0.0;
				riIFinal = 0;
			}
		}
	}
	else
	{
		dDistance = fabs(dV - dB);
		rdX = 0.0;
		rdY = dB;
		riIFinal = 0;
	}
	if (bTranspose)
	{
		dSave = rdX;
		rdX = rdY;
		rdY = dSave;
	}
	if (bYReflect)
	{
		rdY = -rdY;
	}
	if (bXReflect)
	{
		rdX = -rdX;
	}
	return dDistance;
}

/*
//----------------------------------------------------------------------------
int main ()
{
// The ellipse is (x/2)^2 + (y/1)^2 = 1. Compute distances for points
// (u,v) with |u| <= 3 and |v| <= 3.
double dA = 2.0, dB = 1.0;
const double dEpsilon = 1e-08;
const int iMax = 32;
double dUMin = -3.0, dUMax = 3.0;
double dVMin = -3.0, dVMax = 3.0;
double dU, dV, dX, dY, dDistance;
int iX, iY, iIFinal, iMaxIFinal = 0;
const int iXBound = 256, iYBound = 256;
ImageDouble2D kImage(iXBound,iYBound);
ImageInt2D kIndex(iXBound,iYBound);
for (iY = 0; iY < iYBound; iY++)
{
dV = dVMin + (dVMax-dVMin)*iY/iYBound;
for (iX = 0; iX < iXBound; iX++)
{
dU = dUMin + (dUMax-dUMin)*iX/iXBound;
dDistance = DistancePointEllipse(dU,dV,dA,dB,dEpsilon,iMax,
iIFinal,dX,dY);
kImage(iX,iY) = dDistance;
kIndex(iX,iY) = iIFinal;
if (iIFinal > iMaxIFinal)
{
iMaxIFinal = iIFinal;
}
}
}
// The point (umax,vmax) has maximal distance. Color the image so that
// points inside the ellipse are blue with intensity proportional to
// distance. Color points outside red with intensity proportional to
// distance.
double dMaxDistance = kImage(255,0);
ImageRGB82D kColor(iXBound,iYBound);
ImageDouble2D kTest(iXBound,iYBound);
for (iY = 0; iY < iYBound; iY++)
{
dV = dVMin + (dVMax-dVMin)*iY/iYBound;
11
for (iX = 0; iX < iXBound; iX++)
{
dU = dUMin + (dUMax-dUMin)*iX/iXBound;
dDistance = kImage(iX,iY);
double dURatio = dU/dA;
double dVRatio = dV/dB;
double dTest = dURatio*dURatio + dVRatio*dVRatio - 1.0;
kTest(iX,iYBound-1-iY) = dTest;
unsigned char ucGray;
if (dTest > 0.0)
{
ucGray = (unsigned char)(255.0f*dDistance/dMaxDistance);
kColor(iX,iY) = GetColor24(ucGray,0,0);
}
else
{
ucGray = (unsigned char)(255.0f*dDistance);
kColor(iX,iY) = GetColor24(0,0,ucGray);
}
}
}
// draw ellipse
iMaxIFinal++;
for (iY = 1; iY < iYBound-1; iY++)
{
for (iX = 1; iX < iXBound-1; iX++)
{
if (kTest(iX,iY) <= 0.0)
{
if (kTest(iX-1,iY-1) > 0.0
|| kTest(iX ,iY-1) > 0.0
|| kTest(iX+1,iY-1) > 0.0
|| kTest(iX-1,iY ) > 0.0
|| kTest(iX+1,iY ) > 0.0
|| kTest(iX-1,iY+1) > 0.0
|| kTest(iX ,iY+1) > 0.0
|| kTest(iX+1,iY+1) > 0.0)
{
kColor(iX,iY) = GetColor24(128,128,128);
kIndex(iX,iY) = iMaxIFinal;
}
}
}
}
kImage.Save("distance.im");
kIndex.Save("index.im");
kColor.Save("color.im");
return 0;
12
}
//----------------------------------------------------------------------------

*/