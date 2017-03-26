double distance(double rssi)
{
	double distance = pow(10.0, ((-45+rssi)/(10*1.8)));

	return distance;
}

double calcPositionX(double d1, double d2, double d3){
	double x1 = 2.0, x2 = 8.0, x3 = 2.0;
	double y1 = 2.0, y2 = 8.0, y3 = 8.0;
	double a[10][10] = {0.0}, c[10][10] = {0.0};

	a[0][0] = (d1*d1 - d2*d2) - (x1*x1 - x2*x2) - (y1*y1 - y2*y2);
	a[0][1] = 2.0 * (y2 - y1);
	a[1][0] = (d1*d1 - d3*d3) - (x1*x1 - x3*x3) - (y1*y1 - y3*y3);
	a[1][1] = 2.0 * (y3 - y1);
	double detA	= (a[0][0]*a[1][1]) - (a[1][0]*a[0][1]);
	
	c[0][0] = 2.0 * (x2 - x1);
	c[0][1] = 2.0 * (y2 - y1);
	c[1][0] = 2.0 * (x3 - x1);
	c[1][1] = 2.0 * (y3 - y1);
	double detC	= (c[0][0]*c[1][1]) - (c[1][0]*c[0][1]);
	printf("detA= %g ", detA);
	printf("detC= %g\n", detC);

	double X = detA / detC;
	return X;
}

double calcPositionY(double d1, double d2, double d3){
	double x1 = 2.0, x2 = 8.0, x3 = 2.0;
	double y1 = 2.0, y2 = 8.0, y3 = 8.0;	
	double b[10][10] = {0.0}, c[10][10] = {0.0};

	b[0][0] = 2.0 * (x2 - x1);
	b[0][1] = (d1*d1 - d2*d2) - (x1*x1 - x2*x2) - (y1*y1 - y2*y2);
	b[1][0] = 2.0 * (x3 - x1);
	b[1][1] = (d1*d1 - d3*d3) - (x1*x1 - x3*x3) - (y1*y1 - y3*y3);
	double detB	= (b[0][0]*b[1][1]) - (b[1][0]*b[0][1]);

	c[0][0] = 2.0 * (x2 - x1);
	c[0][1] = 2.0 * (y2 - y1);
	c[1][0] = 2.0 * (x3 - x1);
	c[1][1] = 2.0 * (y3 - y1);
	/*
	printf("c00= %g ", c[0][0]);
	printf("c01= %g ", c[0][1]);
	printf("c10= %g ", c[1][0]);
	printf("c11= %g ", c[1][1]);
	*/
	double detC	= (c[0][0]*c[1][1]) - (c[1][0]*c[0][1]);
	printf("detB= %g ", detB);
	printf("detC= %g\n", detC);
	
	double Y = detB / detC;
	return Y;
}