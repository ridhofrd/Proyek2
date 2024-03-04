#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mainDataMenfess() {
    // Buka file
    FILE *file = fopen("DataMenfess.txt", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        return 1;
    }

    // Baca dan tampilkan data dari file
    printf("ID\tFrom\tTo\tMessage\n");
    printf("---------------------------------\n");
    int id;
    char from[100], to[100], message[100], method[100], key[100];
    while (fscanf(file, "%d %s %s %s %s %[^\n]", &id, from, to, method, key, message) != EOF) {
        // Tampilkan pesan
        printf("%d\t%s\t%s\t%s\n", id, from, to, message);
    }

    // Tutup file
    fclose(file);

    int choice;
    do {
        // Meminta input menu dari pengguna
        printf("\nMenu:\n");
        printf("1. Dekripsi pesan\n");
        printf("2. Kembali ke menu utama\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                // Meminta input ID dari pengguna
                printf("\nMasukkan ID: ");
                int input_id;
                scanf("%d", &input_id);

                // Buka file kembali untuk mencari pesan berdasarkan ID yang dimasukkan
                file = fopen("DataMenfess.txt", "r");
                if (file == NULL) {
                    printf("File tidak dapat dibuka.\n");
                    return 1;
                }

                // Cari pesan sesuai ID yang dimasukkan
                int found = 0;
                while (fscanf(file, "%d %s %s %s %s %[^\n]", &id, from, to, method, key, message) != EOF) {
                    if (id == input_id) {
                        printf("\nPesan dengan ID %d:\n", id);
                        printf("From: %s\n", from);
                        printf("To: %s\n", to);
                        printf("Message: %s\n", message);

                        // Meminta input key dari pengguna
                        printf("Masukkan key: ");
                        char input_key[100];
                        scanf("%s", input_key);

                        // Membandingkan key yang dimasukkan dengan key yang ada di file
                        if (strcmp(input_key, key) == 0) {
                            printf("Key yang dimasukkan benar.\n");
                        } else {
                            printf("Key yang dimasukkan salah.\n");
                            printf("Menu:\n");
                            printf("1. Kembali ke data menfess\n");
                            printf("2. Kembali ke menu utama\n");
                            printf("Pilih menu: ");
                            int sub_choice;
                            scanf("%d", &sub_choice);
                            if (sub_choice == 2) {
                                printf("Kembali ke menu utama");
                            }
                        }

                        found = 1;
                        break;
                    }
                }

                // Jika pesan tidak ditemukan
                if (!found) {
                    printf("\nPesan dengan ID %d tidak ditemukan.\n", input_id);
                }

                // Tutup file
                fclose(file);
                break;
            }
            case 2:
                printf("Kembali ke menu utama");
                break;
            default:
                printf("\nMenu yang dimasukkan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 2);

    return 0;
}

