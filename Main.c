#include <stdio.h>
#include <string.h>

struct DauSach {
    int maSach;
    char ten[100];
    int soLuong;
    int giaBan;
};

struct DauSach ds[50];
int soLuongSach = 0;

int timTheoMa(int maCanTim){
    for(int i = 0; i < soLuongSach; i++){
        if(ds[i].maSach == maCanTim){
            return i;
        }
    }
    return -1;
}

void AddBook() {
    if (soLuongSach >= 50) {
        printf("Danh sach da day\n");
        return;
    }

    int maMoi;
    printf("Nhap ma dau sach: ");
    scanf("%d", &maMoi);

    if(timTheoMa(maMoi) != -1) {
        printf("Ma dau sach da ton tai\n");
        return;
    }

    ds[soLuongSach].maSach = maMoi;

    getchar();
    printf("Nhap ten dau sach: ");
    fgets(ds[soLuongSach].ten, sizeof(ds[soLuongSach].ten), stdin);
    ds[soLuongSach].ten[strcspn(ds[soLuongSach].ten, "\n")] = '\0';

    do {
        printf("Nhap so luong: ");
        scanf("%d", &ds[soLuongSach].soLuong);
        if (ds[soLuongSach].soLuong < 0){
            printf("Nhap lai so luong!\n");
        }
    } while(ds[soLuongSach].soLuong < 0);

    do {
        printf("Nhap gia ban: ");
        scanf("%d", &ds[soLuongSach].giaBan);
        if (ds[soLuongSach].giaBan < 0) {
            printf("Nhap lai gia ban!\n");
        }
    } while(ds[soLuongSach].giaBan < 0);

    soLuongSach++;
    printf("Them dau sach thanh cong\n");
}

void RenderBook() {
    if(soLuongSach == 0) {
        printf("Danh sach rong\n");
        return;
    }

    printf("%-10s %-30s %-10s %-15s %-15s\n", "Ma", "Ten dau sach", "So luong", "Gia ban", "Thanh tien");
    for(int i = 0; i < soLuongSach; i++) {
        int thanhTien = ds[i].soLuong * ds[i].giaBan;
        printf("%-10d %-30s %-10d %-15d %-15d\n", ds[i].maSach, ds[i].ten, ds[i].soLuong, ds[i].giaBan, thanhTien);
    }
}

void UpdateBook() {
    if(soLuongSach == 0) {
        printf("Danh sach rong\n");
        return;
    }

    int ma;
    printf("Nhap ma dau sach can sua: ");
    scanf("%d", &ma);

    int viTri = timTheoMa(ma);
    if(viTri == -1) {
        printf("Khong tim thay dau sach\n");
        return;
    }

    getchar();
    printf("Nhap ten dau sach moi: ");
    fgets(ds[viTri].ten, sizeof(ds[viTri].ten), stdin);
    ds[viTri].ten[strcspn(ds[viTri].ten, "\n")] = '\0';

    do {
        printf("Nhap so luong moi: ");
        scanf("%d", &ds[viTri].soLuong);
        if (ds[viTri].soLuong < 0) {
            printf("Nhap lai so luong!\n");
        }
    } while(ds[viTri].soLuong < 0);

    do {
        printf("Nhap gia ban moi: ");
        scanf("%d", &ds[viTri].giaBan);
        if (ds[viTri].giaBan < 0) {
            printf("Nhap lai gia ban!\n");
        }
    } while(ds[viTri].giaBan < 0);

    printf("Cap nhat thanh cong\n");
}

void DeleteBook() {
    if(soLuongSach == 0) {
        printf("Danh sach rong\n");
        return;
    }

    int ma;
    printf("Nhap ma dau sach can xoa: ");
    scanf("%d", &ma);

    int viTri = timTheoMa(ma);
    if(viTri == -1) {
        printf("Khong tim thay dau sach\n");
        return;
    }

    for(int i = viTri; i < soLuongSach - 1; i++) {
        ds[i] = ds[i + 1];
    }
    soLuongSach--;
    printf("Xoa thanh cong\n");
}

void SearchBook() {
    getchar();
    char tenTim[100];
    printf("Nhap ten dau sach can tim: ");
    fgets(tenTim, sizeof(tenTim), stdin);
    tenTim[strcspn(tenTim, "\n")] = '\0';

    int dem = 0;
    for(int i = 0; i < soLuongSach; i++) {
        if(strcmp(ds[i].ten, tenTim) == 0) {
            if(dem == 0) {
                printf("%-10s %-30s %-10s %-15s %-15s\n", "Ma", "Ten dau sach", "So luong", "Gia ban", "Thanh tien");
            }
            int thanhTien = ds[i].soLuong * ds[i].giaBan;
            printf("%-10d %-30s %-10d %-15d %-15d\n", ds[i].maSach, ds[i].ten, ds[i].soLuong, ds[i].giaBan, thanhTien);
            dem++;
        }
    }

    if(dem == 0) {
        printf("Khong tim thay dau sach\n");
    }
}

void Statistical() {
    if(soLuongSach == 0) {
        printf("Danh sach rong\n");
        return;
    }

    int tongGiaTri = 0;
    int soLuongSapHet = 0;
    int viTriMaxTien = 0;
    int maxTien = -1;

    for(int i = 0; i < soLuongSach; i++) {
        int thanhTien = ds[i].soLuong * ds[i].giaBan;
        tongGiaTri += thanhTien;

        if(ds[i].soLuong < 5) {
            soLuongSapHet++;
        }

        if(thanhTien > maxTien) {
            maxTien = thanhTien;
            viTriMaxTien = i;
        }
    }

    printf("Tong gia tri kho: %d\n", tongGiaTri);

    printf("Cac dau sach sap het hang (so luong < 5):\n");
    if (soLuongSapHet > 0) {
        printf("%-10s %-30s %-10s %-15s %-15s\n", "Ma", "Ten dau sach", "So luong", "Gia ban", "Thanh tien");
        for (int i = 0; i < soLuongSach; i++) {
            if (ds[i].soLuong < 5) {
                int thanhTien = ds[i].soLuong * ds[i].giaBan;
                printf("%-10d %-30s %-10d %-15d %-15d\n", ds[i].maSach, ds[i].ten, ds[i].soLuong, ds[i].giaBan, thanhTien);
            }
        }
    }
    printf("So dau sach sap het hang: %d\n", soLuongSapHet);

    printf("Dau sach co thanh tien lon nhat:\n");
    printf("%-10s %-30s %-10s %-15s %-15s\n", "Ma", "Ten dau sach", "So luong", "Gia ban", "Thanh tien");
    int thanhTienMax = ds[viTriMaxTien].soLuong * ds[viTriMaxTien].giaBan;
    printf("%-10d %-30s %-10d %-15d %-15d\n",
        ds[viTriMaxTien].maSach, ds[viTriMaxTien].ten, ds[viTriMaxTien].soLuong, ds[viTriMaxTien].giaBan, thanhTienMax);
}

int main() {
    int choice;
    do {
        printf("===== QUAN LY DAU SACH =====\n");
        printf("1. Them dau sach\n");
        printf("2. Hien thi danh sach dau sach\n");
        printf("3. Cap nhat dau sach theo ma\n");
        printf("4. Xoa dau sach theo ma\n");
        printf("5. Tim dau sach theo ten\n");
        printf("6. Thong ke kho hang\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");

        if (scanf("%d", &choice) != 1) {
            printf("Lua chon khong hop le\n");
            break;
        }
        getchar();

        switch (choice) {
            case 1:
                AddBook();
                break;
            case 2:
                RenderBook();
                break;
            case 3:
                UpdateBook();
                break;
            case 4:
                DeleteBook();
                break;
            case 5:
                SearchBook();
                break;
            case 6:
                Statistical();
                break;
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
        printf("\n");
    } while (choice != 0);

    return 0;
}