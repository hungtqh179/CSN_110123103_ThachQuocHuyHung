#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char maSV[10];
    char hoTen[50];
    float diem;
} SinhVien;

typedef struct Node {
    SinhVien data;
    struct Node *prev;
    struct Node *next;
} Node;


Node* taoNode(SinhVien sv) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = sv;
    p->prev = p->next = NULL;
    return p;
}

void themCuoi(Node **head, Node **tail, SinhVien sv) {
    Node *p = taoNode(sv);
    if (*head == NULL)
        *head = *tail = p;
    else {
        (*tail)->next = p;
        p->prev = *tail;
        *tail = p;
    }
}

void hienThi(Node *head) {
    if (!head) {
        printf("\nDanh sach rong!\n");
        return;
    }
    Node *p = head;
    printf("\n%-10s %-25s %-10s\n", "MaSV", "Ho Ten", "Diem");
    printf("-----------------------------------------------\n");
    while (p != NULL) {
        printf("%-10s %-25s %-10.2f\n", p->data.maSV, p->data.hoTen, p->data.diem);
        p = p->next;
    }
}

void nhapDanhSach(Node **head, Node **tail) {
    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        SinhVien sv;
        printf("\n--- Sinh vien thu %d ---\n", i + 1);
        printf("Ma SV: "); gets(sv.maSV);
        printf("Ho ten: "); gets(sv.hoTen);
        printf("Diem thi: "); scanf("%f", &sv.diem);
        getchar();
        themCuoi(head, tail, sv);
    }
}


void sapXep(Node *head, int tangDan) {
    if (head == NULL) return;
    for (Node *i = head; i != NULL; i = i->next) {
        for (Node *j = i->next; j != NULL; j = j->next) {
            int dk = 0;
            if (tangDan && i->data.diem > j->data.diem)
                dk = 1;
            else if (!tangDan && i->data.diem < j->data.diem)
                dk = 1;

            if (dk) {
                SinhVien temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}


float timDiemMax(Node *head) {
    if (!head) return -1;
    float max = head->data.diem;
    for (Node *p = head->next; p; p = p->next)
        if (p->data.diem > max)
            max = p->data.diem;
    return max;
}

void hienThiMax(Node *head) {
    if (!head) {
        printf("Danh sach rong!\n");
        return;
    }

    float max = timDiemMax(head);
    printf("\nDiem cao nhat: %.2f\n", max);
    printf("%-10s %-25s %-10s\n", "MaSV", "Ho Ten", "Diem");
    printf("-----------------------------------------------\n");
    int count = 0;
    for (Node *p = head; p != NULL; p = p->next) {
        if (p->data.diem == max) {
            printf("%-10s %-25s %-10.2f\n", p->data.maSV, p->data.hoTen, p->data.diem);
            count++;
        }
    }
    printf("=> Co %d sinh vien dat diem cao nhat.\n", count);
}

void locSinhVien(Node *head) {
    printf("\nDanh sach sinh vien co diem >= 8.0:\n");
    printf("%-10s %-25s %-10s\n", "MaSV", "Ho Ten", "Diem");
    printf("-----------------------------------------------\n");
    int found = 0;
    for (Node *p = head; p != NULL; p = p->next)
        if (p->data.diem >= 8.0) {
            printf("%-10s %-25s %-10.2f\n", p->data.maSV, p->data.hoTen, p->data.diem);
            found = 1;
        }
    if (!found) printf("Khong co sinh vien nao co diem >= 8.0.\n");
}

void thongKe(Node *head) {
    int gioi = 0, kha = 0, tb = 0;
    for (Node *p = head; p != NULL; p = p->next) {
        if (p->data.diem >= 8.0) gioi++;
        else if (p->data.diem >= 6.5) kha++;
        else tb++;
    }
    printf("\nThong ke ket qua:\n");
    printf("Gioi: %d\n", gioi);
    printf("Kha : %d\n", kha);
    printf("TB  : %d\n", tb);
}


void chonGiaiThuong(Node *head) {
    if (head == NULL) {
        printf("\nDanh sach rong!\n");
        return;
    }
    sapXep(head, 0);
    Node *ds[500];
    int count = 0;
    for (Node *p = head; p != NULL; p = p->next)
        if (p->data.diem >= 8.0)
            ds[count++] = p;

    if (count == 0) {
        printf("\nKhong co sinh vien nao co diem >= 8.0, khong co sinh vien dat giai!\n");
        return;
    }
    float diemNhat = ds[0]->data.diem;
    float diemNhi = -1, diemBa = -1;
    for (int i = 0; i < count; i++) {
        float d = ds[i]->data.diem;
        if (diemNhi == -1 && d < diemNhat) diemNhi = d;
        if (diemBa == -1 && d < diemNhi && diemNhi != -1) diemBa = d;
    }
    printf("\n==== KET QUA TRAO GIAI ====\n");
    printf("%-10s %-25s %-10s %-20s\n", "MaSV", "Ho Ten", "Diem", "Giai Thuong");
    printf("-------------------------------------------------------------\n");
    int demKK = 0;
    for (int i = 0; i < count; i++) {
        float d = ds[i]->data.diem;
        const char *giai;
        if (d == diemNhat)
            giai = "Giai Nhat";
        else if (d == diemNhi)
            giai = "Giai Nhi";
        else if (d == diemBa)
            giai = "Giai Ba";
        else if (demKK < 5) { // t?i da 5 gi?i khuy?n khích
            giai = "Giai Khuyen Khich";
            demKK++;
        } else continue;

        printf("%-10s %-25s %-10.2f %-20s\n",
               ds[i]->data.maSV, ds[i]->data.hoTen, ds[i]->data.diem, giai);
    }
    printf("-------------------------------------------------------------\n");
    printf("Tong cong: %d sinh vien dat giai\n", count);
}
Node* timSinhVien(Node* head, char ma[]) {
    Node* p = head;
    while (p != NULL) {
        if (strcmp(p->data.maSV, ma) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}
void suaSinhVien(Node* head) {
    char ma[10];
    printf("\nNhap ma sinh vien can sua: ");
    fflush(stdin);
    gets(ma);

    Node* sv = timSinhVien(head, ma);
    if (sv == NULL) {
        printf("Khong tim thay sinh vien!\n");
        return;
    }

    printf("Nhap ho ten moi: ");
    fflush(stdin);
    gets(sv->data.hoTen);

    printf("Nhap diem moi: ");
    scanf("%f", &sv->data.diem);

    printf("Sua thong tin thanh cong!\n");
}
void xoaSinhVien(Node* &head) {
    char ma[10];
    printf("\nNhap ma sinh vien can xoa: ");
    fflush(stdin);
    gets(ma);
    Node* p = head;
    if (p != NULL && strcmp(p->data.maSV, ma) == 0) {
        head = p->next;
        if (head != NULL)
            head->prev = NULL;
        free(p);
        printf("Xoa thanh cong!\n");
        return;
    }
    while (p != NULL && strcmp(p->data.maSV, ma) != 0)
        p = p->next;

    if (p == NULL) {
        printf("Khong tim thay sinh vien!\n");
        return;
    }
    p->prev->next = p->next;
    if (p->next != NULL)
        p->next->prev = p->prev;
    free(p);
    printf("Xoa thanh cong!\n");
}



void giaiPhong(Node **head) {
    Node *p;
    while (*head != NULL) {
        p = *head;
        *head = (*head)->next;
        free(p);
    }
}


int main() {
    Node *head = NULL, *tail = NULL;
    int chon;
    do {
        printf("\n================ MENU =================\n");
        printf("1. Nhap danh sach sinh vien\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Sap xep theo diem (tang/giam)\n");
        printf("4. Tim sinh vien diem cao nhat\n");
        printf("5. Loc sinh vien co diem >= 8.0\n");
        printf("6. Thong ke ket qua\n");
        printf("7. Chon sinh vien dat giai thuong\n");
        printf("8. Sua thong tin sinh vien\n");
        printf("9. Xoa thong tin sinh vien\n");
        printf("0. Thoat\n");
        printf("======================================\n");
        printf("Chon chuc nang: ");
        scanf("%d", &chon);
        getchar();

        switch(chon) {
            case 1:
                nhapDanhSach(&head, &tail);
                break;
            case 2:
                hienThi(head);
                break;
            case 3: {
                int kieu;
                printf("\nChon kieu sap xep:\n1. Tang dan\n2. Giam dan\nLua chon: ");
                scanf("%d", &kieu);
                sapXep(head, (kieu == 1));
                printf("\nDa sap xep danh sach!\n");
                break;
            }
            case 4:
                hienThiMax(head);
                break;
            case 5:
                locSinhVien(head);
                break;
            case 6:
                thongKe(head);
                break;
            case 7:
                chonGiaiThuong(head);
                break;
            case 8:
    			suaSinhVien(head);
    			break;
			case 9:
    			xoaSinhVien(head);
    			break;
            case 0:
                printf("\nThoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while(chon != 0);
    giaiPhong(&head);
    return 0;
}

