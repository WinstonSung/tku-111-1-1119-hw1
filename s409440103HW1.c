#include <stdio.h>

// Test whether the exists
// name 表檔名
int check_file(char* target) {
    FILE *file = fopen(target, "rb");
    if (!file) {
        return 0;
    }

    fclose(file);
    return 1;
}

int main() {
    FILE* file;
    FILE* copy;

    char buffer[100];
    char target[100];

    printf("請輸入檔名: ");
    scanf("%s", &target);
    int access = check_file(target);
    int choose;
    // 檔案不存在 
    while (!access) {
        printf("檔案不存在。(1:離開 2:重讀)");
        scanf("%d", &choose);
        if (choose == 1) {
            printf("Program ended\n");
            return 0;
        } else if (choose == 2) {
	        printf("File name: ");
	        scanf("%s", &target);
	        access = check_file(target);
    	} else {
        	printf("ERROR!");
        	return -1;
        }
    }
    file = fopen(target, "rb");
    if (!file) {
		return -1;
	}

    printf("輸入新檔名: ");
    scanf("%s", &target);
    access = check_file(target);

    while (access) {
        printf("檔案已存在 (1:重新輸入, 2:覆蓋原本檔案, 3:離開): ");
        scanf("%d", &choose);
		if (choose == 1) {
	        printf("New file name: ");
	        scanf("%s", &target);
	        access = check_file(target);
        } else if (choose == 2) {
            break;
        } else if (choose == 3) {
            printf("Exit processing\n");
            return 0;
        } else {
        	printf("ERROR!");
        	return -1;
        }
    }
    copy = fopen(target, "wb");
    if (!copy) {
        fclose(copy);
        return -1;
    }

    int counter;
    do {
        counter = fread(buffer, 1, 100, file);
        fwrite(buffer, 1, counter, copy);
    } while (counter == 100);

    fclose(file);
    fclose(copy);
    return 0;
}
