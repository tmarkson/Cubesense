double DistancePointEllipse
	(
	double dU, double dV,		// test point (u,v)
	double dA, double dB,		// ellipse is (x/a)^2 + (y/b)^2 = 1
	const double dEpsilon,		// zero tolerance for Newton’s method
	const int iMax,				// maximum iterations in Newton’s method
	int& riIFinal,				// number of iterations used
	double& rdX, double& rdY	// a closest point (x,y)
);

int geometryInit();
double geometrySin(double angle);
double geometryCos(double angle);
double geometryArcTan(double ratio);

#define GEOMETRY_PI 3.14159265359