#include <stdio.h>
#define maxium 1000
typedef struct {
	float TL, GT, DG;
	int PA, SL;
	char TEN[20];
	
} balo;
void readFile(char filename[], balo balo[],int *n, float *w, int option) {
	//chu y khoang trang
	FILE *file = fopen(filename, "r");
	if(file == NULL) {
		printf("Loi mo file!");
		return;
	}
	fscanf(file, "%f", w);
	int i = 0;
	switch (option) {
		case 1:
			while(!feof(file)){
				fscanf(file, "%f%f%[^\n]", &balo[i].TL, &balo[i].GT, &balo[i].TEN);
				balo[i].DG = balo[i].GT/balo[i].TL;
				balo[i].SL = maxium;
				i++;
			}
			*n = i;
			break;
		case 2:
			while(!feof(file)){
				fscanf(file, "%f%f%d%[^\n]", &balo[i].TL, &balo[i].GT, &balo[i].SL,&balo[i].TEN);
				balo[i].DG = balo[i].GT/balo[i].TL;
				i++;
			}
			*n = i;
			break;
		case 3:
			while(!feof(file)){
				fscanf(file, "%f%f%[^\n]", &balo[i].TL, &balo[i].GT, &balo[i].TEN);
				balo[i].DG = balo[i].GT/balo[i].TL;
				balo[i].SL = 1;
				i++;
			}
			*n = i;
			break;
	}
	fclose(file);
}
void Tao_nut_goc(float w, float *TLConLai, float *CT, float *GiaLNTT, float *TGT, float Don_Gia_Lon_Nhat) {
	*TGT = 0.0;
	*TLConLai = w;
	*CT = *TLConLai*Don_Gia_Lon_Nhat;
	*GiaLNTT = 0.0;
}
void Cap_Nhat_PA_TNTT(float TGT, float *GiaLNTT, int x[], balo *dsBalo, int n) {
	int i;
	if(*GiaLNTT < TGT) {
		*GiaLNTT = TGT;
		for(i = 0; i < n; i++) {
			dsBalo[i].PA = x[i];
		}
	}
}
void Nhanh_Can(int i, float *TGT, float *CT, float *TLConLai, float *GiaLNTT, int x[], balo *dsBalo, int n) {
	int j;
	int phuong_an = *TLConLai/dsBalo[i].TL;
	while(phuong_an > dsBalo[i].SL) {
		phuong_an--;
	}
	for(j = phuong_an; j >= 0; j--) {
		*TGT += dsBalo[i].GT*j;
		*TLConLai -= j*dsBalo[i].TL;
		if(*CT > *GiaLNTT) {
			x[i] = j;
			if(i == n - 1 || *TLConLai == 0.0) {
				Cap_Nhat_PA_TNTT(*TGT, GiaLNTT, x, dsBalo, n);
			} else {
				Nhanh_Can(i + 1, TGT, CT, TLConLai, GiaLNTT, x, dsBalo, n);
			}
		}
		x[i] = 0;
		*TGT -= j*dsBalo[i].GT;
		*TLConLai += j*dsBalo[i].TL;
		
	}
}
void printBalo(balo dsBalo[], int n) {
	int i;
	for(i = 0; i < n;i++) {
		printf("%f ", dsBalo[i].TL);
	}
}
float max_DG(balo dsBalo[], int n) {
	int i = 0;
	float max = dsBalo[i].DG;
	for(i = 0; i < n; i++) {
		if(max < dsBalo[i].DG) {
			max = dsBalo[i].DG;
		}
	}
}
int main() {
	balo dsBalo[100];
	int n, i;
	char filename[20];
	float w, TGT, TLConLai, GiaLNTT, CT;
	int option;
	int x[n];
	printf("Nhap vao ten file: ");
	scanf("%s", filename);
	printf("Nhap vao dang bai: \n1. Khong gioi han.\n2. Chi co mot so luong nhat dinh.\n3. Chi co 1.\nLua chon: ");
	scanf("%d", &option);
	readFile(filename, dsBalo, &n, &w, option);
	Tao_nut_goc(w, &TLConLai, &CT, &GiaLNTT, &TGT, max_DG(dsBalo, n));
	Nhanh_Can(0, &TGT, &CT, &TLConLai, &GiaLNTT, x, dsBalo, n);
	float sum_gt = 0, sum_tl = 0;
	for(i = 0; i < n; i++) {
		sum_gt += dsBalo[i].PA*dsBalo[i].GT;
		sum_tl += dsBalo[i].PA*dsBalo[i].TL;
		printf("%d\t%s\n", dsBalo[i].PA, dsBalo[i].TEN);
		
	}
	printf("Tong gia tri: %f\n", sum_gt);
	printf("Tong trong luong: %f", sum_tl);
	return 0;
}
