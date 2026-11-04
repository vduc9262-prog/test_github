
#include <stdio.h>
#include <string.h>

#define MAX_ZONES 10
#define MAX_QRS 100

struct TicketZone {
    int zone_id;
    char zone_name[20];
    float ticket_price;
    int total_capacity;
    int sold_tickets;
};

struct QrCheckIn {
    char qr_code[20];
    int zone_id;
    int is_used;
};

/* Khai bao prototype */
float tinhGiaVe(float ticket_price, int is_early_bird);

int timKhuVuc(const struct TicketZone zones[],
              int total_zones, int zone_id);

int banVe(struct TicketZone zones[], int total_zones,
          int zone_id, int quantity, int is_early_bird,
          float *total_amount);

int checkInQR(struct QrCheckIn qrs[],
              int total_qrs, const char *qr_code);

int main() {
    struct TicketZone zones[MAX_ZONES] = {
        {1, "VIP", 2000000, 5, 3},
        {2, "GA", 800000, 10, 2}
    };

    struct QrCheckIn qrs[MAX_QRS] = {
        {"QR001", 1, 0},
        {"QR002", 1, 0},
        {"QR003", 2, 0}
    };

    int total_zones = 2;
    int total_qrs = 3;
    float total_amount = 0;

    printf("=== TICKETBOX LIVE CONCERT ===\n");

    /* Test 1: So luong am */
    printf("\nTEST 1: Mua -2 ve\n");
    banVe(zones, total_zones, 1, -2, 0, &total_amount);

    /* Test 2: Vuot gioi han 4 ve */
    printf("\nTEST 2: Mua 5 ve\n");
    banVe(zones, total_zones, 2, 5, 0, &total_amount);

    /* Test 3: Vuot suc chua khu VIP */
    printf("\nTEST 3: Mua 3 ve VIP khi chi con 2 cho\n");
    banVe(zones, total_zones, 1, 3, 0, &total_amount);

    /* Test 4: Ma khu vuc khong ton tai */
    printf("\nTEST 4: Mua ve khu vuc 99\n");
    banVe(zones, total_zones, 99, 1, 0, &total_amount);

    /* Test 5: Ban ve thanh cong, ap dung Early Bird */
    printf("\nTEST 5: Mua 2 ve GA, co Early Bird\n");
    if (banVe(zones, total_zones, 2, 2, 1,
              &total_amount) == 1) {
        printf("Tong tien: %.0f VND\n", total_amount);
    }

    /* Test 6: Check-in thanh cong */
    printf("\nTEST 6: Check-in QR001\n");
    checkInQR(qrs, total_qrs, "QR001");

    /* Test 7: Quet lai QR da su dung */
    printf("\nTEST 7: Quet lai QR001\n");
    checkInQR(qrs, total_qrs, "QR001");

    /* Test 8: QR khong ton tai */
    printf("\nTEST 8: Check-in QR999\n");
    checkInQR(qrs, total_qrs, "QR999");

    /* Test 9: Danh sach khu vuc rong */
    printf("\nTEST 9: Danh sach khu vuc rong\n");
    banVe(zones, 0, 1, 1, 0, &total_amount);

    /* Test 10: Danh sach QR rong */
    printf("\nTEST 10: Danh sach QR rong\n");
    checkInQR(qrs, 0, "QR001");

    /* Hien thi ton kho sau cac giao dich */
    printf("\n=== TON KHO SAU KIEM THU ===\n");

    for (int i = 0; i < total_zones; i++) {
        printf("Khu %s: da ban %d/%d ve\n",
               zones[i].zone_name,
               zones[i].sold_tickets,
               zones[i].total_capacity);
    }

    return 0;
}

/* Tinh gia ve sau giam gia */
float tinhGiaVe(float ticket_price, int is_early_bird) {
    if (is_early_bird == 1) {
        return ticket_price * 0.85f;
    }

    return ticket_price;
}

/* Tim khu vuc theo ma */
int timKhuVuc(const struct TicketZone zones[],
              int total_zones, int zone_id) {
    if (total_zones <= 0) {
        return -1;
    }

    for (int i = 0; i < total_zones; i++) {
        if (zones[i].zone_id == zone_id) {
            return i;
        }
    }

    return -1;
}

/* Xu ly giao dich ban ve */
int banVe(struct TicketZone zones[], int total_zones,
          int zone_id, int quantity, int is_early_bird,
          float *total_amount) {
    int viTri;
    float giaVe;

    *total_amount = 0;

    if (quantity < 1 || quantity > 4) {
        printf("Loi: So luong mua phai tu 1 den 4 ve!\n");
        return 0;
    }

    if (is_early_bird != 0 && is_early_bird != 1) {
        printf("Loi: Trang thai Early Bird khong hop le!\n");
        return 0;
    }

    if (total_zones <= 0) {
        printf("Loi: Danh sach khu vuc dang rong!\n");
        return 0;
    }

    viTri = timKhuVuc(zones, total_zones, zone_id);

    if (viTri == -1) {
        printf("Loi: Khong tim thay khu vuc %d!\n", zone_id);
        return 0;
    }

    if (zones[viTri].sold_tickets < 0 ||
        zones[viTri].total_capacity < 0 ||
        zones[viTri].sold_tickets >
        zones[viTri].total_capacity) {
        printf("Loi: Du lieu ton kho khong hop le!\n");
        return 0;
    }

    if (zones[viTri].sold_tickets + quantity >
        zones[viTri].total_capacity) {
        printf("Loi: Khu %s khong du ve!\n",
               zones[viTri].zone_name);
        return 0;
    }

    giaVe = tinhGiaVe(zones[viTri].ticket_price,
                      is_early_bird);

    *total_amount = giaVe * quantity;
    zones[viTri].sold_tickets += quantity;

    printf("Ban ve thanh cong: %d ve khu %s\n",
           quantity, zones[viTri].zone_name);

    return 1;
}

/* Check-in QR mot lan duy nhat */
int checkInQR(struct QrCheckIn qrs[],
              int total_qrs, const char *qr_code) {
    if (total_qrs <= 0) {
        printf("Loi: Danh sach QR dang rong!\n");
        return 0;
    }

    for (int i = 0; i < total_qrs; i++) {
        if (strcmp(qrs[i].qr_code, qr_code) == 0) {
            if (qrs[i].is_used == 1) {
                printf("Canh bao: QR %s da duoc su dung!\n",
                       qr_code);
                return 0;
            }

            qrs[i].is_used = 1;

            printf("Check-in thanh cong QR %s!\n", qr_code);
            return 1;
        }
    }

    printf("Loi: Ma QR %s khong ton tai!\n", qr_code);
    return 0;
}
