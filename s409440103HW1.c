#include <stdio.h>

// Test whether the exists
// name ���ɦW
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

    printf("�п�J�ɦW: ");
    scanf("%s", &target);
    int access = check_file(target);
    int choose;
    // �ɮפ��s�b 
    while (!access) {
        printf("�ɮפ��s�b�C(1:���} 2:��Ū)");
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

    printf("��J�s�ɦW: ");
    scanf("%s", &check_file);
    access = check_file(target);

    while (access) {
        printf("�ɮפw�s�b (1:���s��J, 2:�л\�쥻�ɮ�, 3:���}): ");
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

