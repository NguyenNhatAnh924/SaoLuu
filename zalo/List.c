#include<stdio.h>

#define Maxlength 30
typedef int Position;
typedef int ElementType;

typedef struct {
	Position Last;
	ElementType Data[Maxlength];
}List;

void MakeNull(List *pL){
	pL->Last = 0;
}

int empty(List L){
	return L.Last == 0;
}

int full_List(List L){
	return L.Last == Maxlength;
}

Position First_List(List L){
	return 1;
}

Position End_List(List L){
	return L.Last + 1;
}

Position Next(Position P, List L){
	return P + 1;
}

Position Previous(Position P, List L){
	return P - 1;
}

void Insert_List(ElementType x, Position P, List *pL){
	int i;
	if(full_List(*pL)) printf("Danh sach day!\n");
	else if(P < 1 || P > pL->Last + 1) printf("Vi tri can chen khong hop le!\n");
	else {
		for(i = pL->Last ; i >= P; i--) pL->Data[i] = pL->Data[i-1];
		pL->Data[P-1] = x;
		pL->Last++;
	}
}

void Delete_List(Position P, List *pL){
	int i;
	if(empty(*pL)) printf("Danh sach rong!\n");
	else if(P < 1 || P > pL->Last) printf("Vi tri can xoa khong hop le!\n");
	else {
		for(i = P; i < pL->Last; i++) pL->Data[i-1] = pL->Data[i];
		pL->Last--;
	}
}

ElementType retrieve(Position P, List L){
	return L.Data[P-1];
}

/*Position locate(ElementType x, List L){
	Position P = First_List(L);
	while(P != End_List(L)){
		if(retrieve(P, L) == x) break;
		P = Next(P, L);
	}
   return P;
}*/
Position Locate(ElementType X, List L)
{ int Found=0;
  Position P = First_List(L);
  while ((P != End_List(L)) && (Found == 0))
    if (retrieve(P,L) == X) 
         Found = 1;
    else P = Next(P, L);
return P;
}

void Double_List(List *L){
	if(empty(*L)) printf("\n\ndanh sach rong");
	else {
		Position P = First_List(*L);
		while (P!=End_List(*L)){
			Position Q = Next(P, *L);
			while(Q!=End_List(*L)){
				if(retrieve(P,*L) == retrieve(Q,*L)) Delete_List(Q, L);
				else Q=Next(Q, *L);
				
			}
			P=Next(P, *L);
		}		
	}
}

void sapxeptangdan(List *L){
	if(empty(*L)) printf("\n\ndanh sach rong");
	else {
		int tam;
		Position P = First_List(*L);
		while (P!=End_List(*L)){
			Position Q = Next(P, *L);
			while(Q!=End_List(*L)){
				if(retrieve(P,*L) > retrieve(Q,*L)){
					tam = L->Data[P-1];
					L->Data[P-1] = L->Data[Q-1];
					L->Data[Q-1] = tam;
				}
				else Q=Next(Q, *L);
				
			}
			P=Next(P, *L);
		}		
		
	}
}
void read_List(List *pL){
	int n, x, i;
	printf("Nhap so phan tu cua danh sach: "); 	scanf("%d", &n);
	for(i = 1; i <= n; i++){
		printf("Nhap du lieu: "); scanf("%d", &x);
		Insert_List(x, End_List(*pL), pL);
	}
}

void print_List(List L){
	Position P = First_List(L);
	while(P != End_List(L)){
		printf("%d\t", retrieve(P, L));
		P = Next(P, L);
	}
	printf("\n");
}

int main(){
	List L; Position p; ElementType x;
	MakeNull(&L);
	read_List(&L);
	print_List(L);
	printf("\n Hay nhap vao vi tri can xoa: "); scanf("%d",&p);
	Delete_List(p, &L);
	printf("\n Danh sach sau khi xoa : ");
	print_List(L);
	printf("\n Hay nhap vao vi tri can chen: "); scanf("%d",&p);
	printf("\n Hay nhap vao gia tri chen   : "); scanf("%d",&x);
	Insert_List(x, p, &L);
	printf("\n Danh sach sau khi chen : ");
	print_List(L);
	printf("\n Nhap gia tri can tim trong ds: "); scanf("%d",&x);
	p=Locate(x,L);
	if (p==End_List(L))
	   printf("\n Khong tim thay %d trong danh sach L",x);
	else printf("\n %d duoc tim thay tai vi tri %d trong ds L",x,p);
    printf("\n Danh sach sau khi xoa phan tu trung nhau ");
	Double_List(&L);  // xoa phan tu trung trong ds
	print_List(L);
	printf("\n Danh sach sau khi sap xep: ");
    sapxeptangdan(&L);
    print_List(L);
	return 0;
}
