float pi = 3.141592654;

float fngrade(float X, float x1, float x2) ///fungsi trigonometri
{
	float fngrade = (X - x1) / (x2 - x1);
	return fngrade;
}

float theta(float f1, float Er, float dEr) ///fungsi menentukan kuadran 1,2,3,4
{
	float theta;
	if (dEr == 0) dEr = 0.00001;
    float sudut = atan(f1*dEr/Er) * 180/pi;
	if (Er > 0.00001 && dEr > 0) theta = sudut;
	else if (Er < 0.00001 && dEr > 0) theta = 180 - abs(sudut);
	else if (Er == 0.00001 && dEr > 0) theta = 180;
	else if (Er < 0.00001 && dEr < 0) theta = 180 + abs(sudut);
	else theta = 360 - abs(sudut);
	return theta;
}

float mN(float a) ///fungsi miuN
{
    float mN;
    if (a >= 0 && a <= 90) mN = 1;
    else if (a > 90 && a < 180) mN = fngrade(a, 180, 90);
    else if (a >= 180 && a <= 270) mN = 0;
    else mN = fngrade(a, 270, 360);
    return mN;
}

float Dk(float f1, float Er, float dEr) ///fungsi magnitude
{
    float Dk = sqrt(Er*Er + (f1*f1 * dEr*dEr));
    //printf("%f %f %f\n",f1,Er,dEr);
    return Dk;
}

float mD(float Dk, float f2) ///fungsi miuD
{
    float mD;
    if (Dk >= 0 && Dk <= f2) mD = fngrade(Dk, 0, f2);
    else mD = 1;
    return mD;
}

float Uk(float mN, float mD, float Um) ///fungsi Uk (hasil akhir)
{
    float Uk = ((1-(2*mN)*mD*Um));
    return Uk;
}

float hitung(float awal, float temp)
{
	int n = 2;
	float Er[n], dEr[n], HPc[n];
	float HPSp = 5.0;
	float f1 = 0.83;
	float f2 = 1.00;
	float Um = 1.00;
	float __Uk[n];
	
	HPc[0] = awal;
	HPc[1] = temp;
	for (int i=0; i<n; i++){
		Er[i] = HPc[i]-HPSp;
		printf("Er %f\n" , Er[i]);
	}
	for (int i=0; i<n; i++){
		if (i==0) dEr[i] = Er[i];
		else if (i==10) dEr[10] = 0;
		else dEr[i] = Er[i]-Er[i-1];
		printf("dEr %f\n" , dEr[i]);
	}
	for (int i = 0; i < n; i++){
		float _theta = theta(f1, Er[i], dEr[i]);
		float _Dk = Dk(f1, Er[i], dEr[i]);
		float _mN = mN(_theta);
		float _mD = mD(_Dk, f2);
		float _Uk = Uk(_mN, _mD, Um);

		__Uk[i] = _Uk;
	}
	for (int i = 0; i < n; i++){
		printf("Uk %f\n" , __Uk[i]);
	}
	return __Uk[1];
}

