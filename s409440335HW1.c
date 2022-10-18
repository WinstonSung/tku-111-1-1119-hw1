/**
 * @title s409440335HW1
 * @course 111-1 1119 Operating System; Teacher: WEI, HSIN-WEN
 * @task HW 1
 * @link https://iclass.tku.edu.tw/course/214705/learning-activity#/1327486
 * @author 409440335 SUNG, CHIEN-CHANG
 * @date 2022-10-08 -- 2022-10-18
 * @desc Copy files
 */

/**
 * Define
 * - MAXSTR The max string length of file name
 */
#define MAXSTR 240

/**
 * Include
 * - stdio
 *   - type FILE
 *   - function fclose
 *   - function fgets
 *   - function fopen
 *   - function printf
 * - string
 *   - function strcmp
 *   - function strcpy
 *   - function strcspn
 */
#include <stdio.h>
#include <string.h>

/**
 * Structure fcopy
 *
 * @member int status The status code
 *  - 0 Exit
 *  - 1 Wait for defining fsource
 *  - 2 Wait for defining ftarget
 *  - 3 Wait for copy (create)
 *  - 4 Wait for force copy (overwrite)
 * @member char[] sourceName The file name of the source file.
 *  Lengh of file name should be less than 240 bytes.
 *  File name should allow whitespaces.
 *  File type should allow binary files.
 *  File should be readable.
 * @member unsigned long sourceFileLen The file length of the source file.
 * @member FILE* fSource
 * @member char[] targetName The file name of the target file.
 *  Lengh of file name should be less than 240 bytes.
 *  File name should allow whitespaces.
 *  File type should allow binary files.
 *  File should be writable.
 * @member FILE* fSource
 */
struct fcopy {
	int iStatus;
	char sourceName[MAXSTR];
	unsigned long sourceFileLen;
	FILE *fSource;
	char targetName[MAXSTR];
	FILE *fTarget;
};

/**
 * 1. Prompt for user to input the source file name, if the file doesn't
 *  exist then user can:
 *   (a) re-enter the correct file name, or
 *   (b) abort the execution.
 *
 * Lengh of file name should be less than 240 bytes.
 * File name should allow whitespaces.
 * File should be readable.
 *
 * @param struct fcopy* wgFcp
 * @return int status code
 *  - 0 No error
 *  - -1 Empty input
 *  - -2 Re-enter the corrrect file name
 */
int wfGetSourceFile(struct fcopy *wgFcp) {
	/* Initialize variables */
	char fname[MAXSTR] = {'\0'};
	char mMode[MAXSTR] = {'\0'};

	printf("Please enter the source file name for copy:\n");
	printf("> ");
	/* Use fgets for file name(s) containing whitespace(s) */
	fgets(fname, MAXSTR, stdin);
	/* Strip off '\n' */
	fname[strcspn(fname, "\r\n")] = '\0';

	/* Check whether the input is empty. */
	if (!fname || fname[0] == '\0') {
		wgFcp->iStatus = 1;
		return -1;
	}

	/**
	 * Check whether the file is readable.
	 * - true: File exists and readable.
	 * - false: File not found, no memory leak since 'file' == NULL.
	 *   fclose(file) would cause an error.
	 */
	if ((wgFcp->fSource = fopen(fname, "rb")) != NULL) {
		fclose(wgFcp->fSource);
		strcpy(wgFcp->sourceName, fname);
		wgFcp->iStatus = 2;
		return 0;
	}

	/**
	 * File is unreadable: mode options.
	 *  (a) Re-enter the correct file name.
	 *  (b) Abort the execution.
	 */
	printf("Error: Not a valid file, file does not exist or is unreadable.\n");
	printf("Please enter one of the following modes:\n");
	printf("- \"a\" Re-enter the correct file name (default)\n");
	printf("- \"b\" Abort the execution\n");
	printf("> ");
	fgets(mMode, MAXSTR, stdin);
	/* Strip off '\n' */
	mMode[strcspn(mMode, "\r\n")] = '\0';
	if (strcmp(mMode, "b") == 0) {
		wgFcp->iStatus = 0;
		return 0;
	}
	/* if (strcmp(mMode, "a") == 0) */
	wgFcp->iStatus = 1;

	return -2;
}

/**
 * 2. Prompt for user to input the destination file name, if there is a
 *  file with the samename as input, then user can select one of the
 *  following operations:
 *   (a) enter another file name, or
 *   (b) overwrite the original file, or
 *   (c) exit the program.
 *
 * @param struct fcopy* wgFcp
 * @return int status code
 *  - 0 No error
 *  - -1 Empty input
 *  - -2 Enter another file name
 */
int wfGetTargetFile(struct fcopy *wgFcp) {
	/* Initialize variables */
	char fname[MAXSTR] = {'\0'};
	char mMode[MAXSTR] = {'\0'};

	printf("Please enter the target file name to copy:\n");
	printf("> ");
	/* Use fgets for file name(s) containing whitespace(s) */
	fgets(fname, MAXSTR, stdin);
	/* Strip off '\n' */
	fname[strcspn(fname, "\r\n")] = '\0';

	/* Check whether the input is empty. */
	if (!fname || fname[0] == '\0') {
		wgFcp->iStatus = 2;
		return -1;
	}

	/* Check whether source == target. */
	if (strcmp(fname, wgFcp->sourceName) == 0) {
		printf("Error: Target file cannot be the source file.\n");
		wgFcp->iStatus = 2;
		return -2;
	}

	/**
	 * Check whether the file exists (is readable).
	 * Check whether the file is writable would create a blank file for
	 *  non-existent files, so no additional write permission checks are
	 *  included here.
	 * - true: File exists (is readable). Check whether to overwrite.
	 * - false: File not found, no memory leak since 'file' == NULL.
	 *   fclose(file) would cause an error.
	 */
	if ((wgFcp->fTarget = fopen(fname, "rb")) != NULL) {
		/**
		 * File does not exist but is unwritable: mode options.
		 *  (a) Enter another file name.
		 *  (b) Overwrite the original file.
		 *  (c) Exit the program.
		 */
		fclose(wgFcp->fTarget);
		printf("Warning: Specified target file already exists.\n");
		printf("Please enter one of the following modes:\n");
		printf("- \"a\" Enter another file name (default)\n");
		printf("- \"b\" Overwrite the original file\n");
		printf("- \"c\" Exit the program\n");
		printf("> ");
		fgets(mMode, MAXSTR, stdin);
		/* Strip off '\n' */
		mMode[strcspn(mMode, "\r\n")] = '\0';
		if (strcmp(mMode, "b") == 0) {
			strcpy(wgFcp->targetName, fname);
			wgFcp->iStatus = 4;
			return 0;
		} else if (strcmp(mMode, "c") == 0) {
			wgFcp->iStatus = 0;
			return 0;
		}
		wgFcp->iStatus = 2;
		return -2;
	}
	strcpy(wgFcp->targetName, fname);
	wgFcp->iStatus = 3;

	return 0;
}

/**
 * 3. Copy the content of the source file to the destination file.
 *
 * @param struct fcopy* wgFcp
 * @return int status code
 *  - 0 No error
 *  - -1 Source file unreadable
 *  - -2 Target file unwritable
 */
int wfCopyFile(struct fcopy *wgFcp) {
	/* Initialize variables */
	unsigned long counter;
	wgFcp->fSource = fopen(wgFcp->sourceName, "rb");
	if (wgFcp->fSource == NULL) {
		wgFcp->iStatus = 1;
		printf("Error: Not a valid source file, file does not exist or is unreadable.\n");
		return -1;
	}
	wgFcp->fTarget = fopen(wgFcp->targetName, "rb");
	if (wgFcp->fTarget != NULL && wgFcp->iStatus != 4) {
		/* To-do */
	}
	wgFcp->fTarget = fopen(wgFcp->targetName, "wb");
	if (wgFcp->fTarget == NULL) {
		fclose(wgFcp->fSource);
		wgFcp->iStatus = 2;
		printf("Error: Not a valid target file name, file is unwritable.\n");
		return -2;
	}

	/* Check file legnth */
	fseek(wgFcp->fSource, 0, SEEK_END);
	wgFcp->sourceFileLen = ftell(wgFcp->fSource);
	fseek(wgFcp->fSource, 0, SEEK_SET);

	for (counter = 0; counter < wgFcp->sourceFileLen; counter++) {
		fputc(fgetc(wgFcp->fSource), wgFcp->fTarget);
	}

	/* After copy completed */
	fclose(wgFcp->fSource);
	fclose(wgFcp->fTarget);
	wgFcp->iStatus = 0;
	printf("Success: Specified file copied.\n");

	return 0;
}

/**
 * Main function
 *
 * @return int status code
 *  - 0 No error
 *  - -1 Error: invalid status
 */
int main(void) {
	/* Initialize variables */
	char mPause[MAXSTR] = {'\0'};
	struct fcopy wgFcp;
	wgFcp.iStatus = 1;

	while (wgFcp.iStatus != 0) {
		if (wgFcp.iStatus == 1) {
			wfGetSourceFile(&wgFcp);
		} else if (wgFcp.iStatus == 2) {
			wfGetTargetFile(&wgFcp);	
		} else if (wgFcp.iStatus == 3 || wgFcp.iStatus == 4) {
			wfCopyFile(&wgFcp);
		} else {
			/* Error: invalid status */
			printf("Error: Invalid status.\n");
			printf("Press enter to exit. ");
			fgets(mPause, MAXSTR, stdin);

			return -1;
		}
	}

	/* pause */
	printf("Press enter to exit. ");
	fgets(mPause, MAXSTR, stdin);

	return 0;
}
