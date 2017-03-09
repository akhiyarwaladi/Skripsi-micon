void hitung(float awal, int temp){

	int n = 2;
	float Er[n], dEr[n];
	float HPSp = 5.0;
	float f1 = 0.83;
	float f2 = 1.00;
	float Um = 1.00;
	float __Uk[n];
	float HPc[n] = {awal, temp};
	double dur1, dur2;

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
	return __Uk[0], __Uk[1];
}
