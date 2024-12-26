#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[100];
    int age;
} Student;
Student students[100];
int studentCount = 0;
const char *fileName = "students.dat";
void readFromFile() {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        studentCount = 0;
        return;
    }
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    fclose(file);
}
void writeToFile() {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
}
void displayStudents() {
    if (studentCount == 0) {
        printf("Danh sach sinh vien rong.\n");
        return;
    }
    printf("Danh sach sinh vien:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
    }
}
void addStudent() {
    if (studentCount >= 100) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    Student newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.id);
    printf("Nhap Ten: ");
    while (getchar() != '\n');
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
    printf("Nhap Tuoi: ");
    scanf("%d", &newStudent.age);
    students[studentCount++] = newStudent;
    writeToFile();
    printf("Them sinh vien thanh cong.\n");
}
void editStudent() {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Nhap Ten moi: ");
            while (getchar() != '\n');
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            printf("Nhap Tuoi moi: ");
            scanf("%d", &students[i].age);
            writeToFile();
            printf("Cap nhat thong tin thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}
void deleteStudent() {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            writeToFile();
            printf("Da xoa sinh vien co ID %d.\n", id);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}
void searchStudent() {
    char name[100];
    printf("Nhap ten sinh vien can tim: ");
    while (getchar() != '\n');
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Ket qua tim kiem:\n");
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].name, name)) {
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien voi ten '%s'.\n", name);
    }
}
void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].age > students[j].age) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    writeToFile();
    printf("Da sap xep danh sach sinh vien theo tuoi tang dan.\n");
}
void menu() {
    int choice;
    do {
        printf("\nMENU\n");
        printf("1.In danh sach sinh vien\n");
        printf("2.Them sinh vien\n");
        printf("3.Sua thong tin sinh vien\n");
        printf("4.Xoa sinh vien\n");
        printf("5.Tim kiem sinh vien\n");
        printf("6.Sap xep danh sach sinh vien\n");
        printf("7.Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                editStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long nhap lai.\n");
        }
    } while (choice != 7);
}
int main() {
    readFromFile();
    menu();
    return 0;
}

