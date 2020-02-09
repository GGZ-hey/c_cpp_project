#include<stdio.h>
#include<string.h>
#include<strlib.h>

#define MaxWord 20

static void PigLatin(char *word, char buffer[], int buffersize);
static char *FindFirstVowel(char *word);

int main() {
	char word[20];
	char translationbuffer[MaxWord + 1];
	scanf_s("%s", &word, 20);
	PigLatin(word, translationbuffer, MaxWord + 1);
	printf("·­ÒëÎª%s\n",translationbuffer);
}

void PigLatin(char *word, char buffer[], int buffersize) {
	char *vp;
	int wordLength;
	wordLength = strlen(word);
	vp = FindFirstVowel(word);
	if (vp == word) {
		wordLength += 3;
	}
	else if (vp != NULL) {
		wordLength += 2;
	}
	if (wordLength > buffersize) {
		printf("»º³åÇøÒç³ö£¡");
		exit(0);
	}
	if (vp == NULL) {
		strcpy_s(buffer,21, word);
	}
	else if (vp == word) {
		strcpy_s(buffer, 21, word);
		strcat_s(buffer,21, "way");
	}
	else if (vp != NULL) {
		strcpy_s(buffer, 21, vp);
		strncat_s(buffer,21, word, vp - word);
		strcat_s(buffer, 21,"ay");
	}
}

char *FindFirstVowel(char *word) {
	char *cp;
	for (cp = word; *cp != '\0'; cp++) {
		if (*cp == 'a' || *cp == 'e' || *cp == 'i' || *cp == 'o' || *cp == 'u' || *cp == 'A' || *cp == 'E' || *cp == 'I' || *cp == 'O' || *cp == 'U') return(cp);
	}
	return(NULL);
}