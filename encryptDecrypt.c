    /*************************************************/
   /*              KEITH MACINNIS                   */
  /*                                               */
 /*         Network Security Playground           */
/*************************************************/
/*************************************************/
/*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int line_skip(); /* Read the standard input to the end of the line. */
int line_copy(); /* Read the standard input to the end of the line
        and copy to the standard output. */
int pause();   /* Ask user to press Enter to continue. */
int read_line(char line[], int len); /* Read at most len characters
          from the standard input and
          ignore the rest of the line. */
void encrypt();  /* Encrpts a ceasar  */
void decrypt();  /* Decrypts a caesar */
void bruteForce();  /*displays all possible decyptions */
void expand();  /*expand a set */
void diffieHellamn(); /*Encodes a diffie hellamn exchange by acpeting a p and q value, creating to random values <=16, genearitng sa,sb, derives the diffie hellman secret.*/ 

int main() {
  int option;

  for (;;) {
    printf("\n-- ED V 1.6 --\n");
    printf("1: Caesar Encrypt\n");
    printf("2: Caesar Decrypt\n");
    printf("3: Caesar Brute Force\n");
    printf("4: RSA Expanded Series\n");
    printf("5: Diffie Hellman Exchange\n");
    printf("0: Exit\n\n");

    printf("Enter an option: ");
    if ( scanf("%d", &option) != 1 ) {
      if ( feof(stdin) ) break;
      printf("Invalid option: "); line_copy(); pause();
      continue;
    }

    /* Read the rest of the line after option number.  Usually, it is
       just one new-line character */
    line_skip(); 

    if (option == 0) break;

    switch(option) {
    case 1: encrypt();                               break;
    case 2: decrypt();                               break;
    case 3: bruteForce();                            break;
    case 4: expand();                                break;
    case 5: diffieHellamn();                         break;

    default:
      printf("Incorrect option: %d\n", option); pause();
    }
  }
  printf("Bye!\n");
  return 0;
}

void diffieHellamn() {
for (;;) {
  long long int p,g;
  long long int secret_alice, secret_bob, transfer_alice, transfer_bob;
  long long int a,b; /*as the order a line executes isn't guarenteed, we need to space out our equestion a bit. These hold calculated power values*/
  long long int aliceResult,bobResult;

  printf("Enter your p value: ");
  if ( scanf("%lld", &p) != 1) {
    if ( feof(stdin) ) break;
    printf("Invalid option: "); line_copy(); pause();
    continue;
  }
  printf("Enter your g value: ");
  if ( scanf("%lld", &g) != 1) {
    if ( feof(stdin) ) break;
    printf("Invalid option: "); line_copy(); pause();
    continue;
  }

  secret_alice = rand() %17 +1;
  secret_bob = rand() %17 +1;
  printf("Alice picked #%lld and Bob the #%lld\n",secret_alice,secret_bob);
  a = pow(g, secret_alice);
  b = pow(g, secret_bob);
  transfer_alice = fmod(a , p);
  transfer_bob = fmod(b , p);

  printf("Alice and Bob have exchanged Keys.\n(TA= %lld TB= %lld)\n",transfer_alice,transfer_bob);
  
  aliceResult = pow(transfer_bob , secret_alice );
  aliceResult = fmod (aliceResult, p);
    printf("Alice computes: %lld", aliceResult);
  bobResult = pow(transfer_alice, secret_bob);
  bobResult = fmod (bobResult, p);
    printf(", Bob computes: %lld", bobResult);
  
  return;
}}

void encrypt() {
for (;;) {
  int key;
  char stringToEncrpt[256];
  printf("Enter your string(255 char max): ");
  read_line(stringToEncrpt,256);
  printf("Collected String: '%s'\n",stringToEncrpt);
  printf("Enter your key[1-25]: ");
  if ( scanf("%d", &key) != 1 || key > 25 || key < 1) {
    if ( feof(stdin) ) break;
    printf("Invalid option: "); line_copy(); pause();
    continue;
  }

  int i=0;int k=0;

  while (stringToEncrpt[i] != '\0') {
    if (stringToEncrpt[i]!=32)
      stringToEncrpt[i] += key; 
    i++;  
  }/*ENCRPYED */
  
  while (stringToEncrpt[k] != '\0') {
    if (stringToEncrpt[k] > 90)
        stringToEncrpt[k] -=26; /* CLEANS RESULTS */
    k++;
  }

  printf("Encrypted String: %s", stringToEncrpt);

  return;
}
}

void decrypt() {
for (;;) {
  int key;
  char stringToDecrpt[256];
  printf("Enter your string(255 char max): ");
  read_line(stringToDecrpt,256);
  printf("Collected String: '%s'\n",stringToDecrpt);
  printf("Enter your key[1-25]: ");
  if ( scanf("%d", &key) != 1 || key > 25 || key < 1) {
    if ( feof(stdin) ) break;
    printf("Invalid option: "); line_copy(); pause();
    continue;
  }

  int i=0;int k=0;

  while (stringToDecrpt[i] != '\0') {
     if ( stringToDecrpt[i]!=32)
        stringToDecrpt[i] -= key; i++;  /*DECRPYED */
  }
  
  while (stringToDecrpt[k] != '\0') {
    if (stringToDecrpt[k] < 65 && stringToDecrpt[k]!=32)
        stringToDecrpt[k] +=26; k++; /* CLEANS RESULTS */
  }

  printf("Decrypted String: %s", stringToDecrpt);

  return;
}
}

void bruteForce() {
  for (;;) {
    char stringToDecrpt[256];
    char workingCopyToDecrpt[256];
    printf("Enter your string(255 char max): ");
    read_line(stringToDecrpt,256);
    printf("Collected String: '%s'\n",stringToDecrpt);

    int key=1;
    while (key<26) {
      int i=0;int k=0;
      strcpy(workingCopyToDecrpt, stringToDecrpt);
      while (workingCopyToDecrpt[i] != '\0') {
        if (workingCopyToDecrpt[i] != 32)
          workingCopyToDecrpt[i] -= key; /*DECRPYED */
        i++; 
      }
      
      while (workingCopyToDecrpt[k] != '\0') {
        if (workingCopyToDecrpt[k] < 65 && workingCopyToDecrpt[k] != 32)
            workingCopyToDecrpt[k] +=26; /* CLEANS RESULTS */
        k++;
      }
    printf("Decrypted String #%d: %s\n", key, workingCopyToDecrpt);  
    key++;
    }

    return;
  }
}

void expand() {
for (;;) {
  int n;
  int base;
  
  printf("Enter your upper limit on n: ");
  if ( scanf("%d", &n) != 1) {
    if ( feof(stdin) ) break;
    printf("Invalid option: "); line_copy(); pause();
    continue;
  }

  printf("Enter your base: ");
  if ( scanf("%d", &base) != 1) {
    if ( feof(stdin) ) break;
    printf("Invalid option: "); line_copy(); pause();
    continue;
  }

  int i=1;
  while (i<n) {
    printf("Expanded Series #%d: %d\n", i,(base*i - (i-1)));
    i++;  
  }
  
  return;
}}




/*HELPER FUNCTIONS*/

int read_line(char line[], int len) {
  int ch, i = 0;

  while ((ch = getchar()) != '\n' && ch != EOF) 
    if (i < len) 
      line[i++] = toupper(ch);
  
  line[i] = '\0';
  return i;
}

int line_copy() {
  int ch;
  while ( (ch=getchar()) != '\n' && ch != EOF )
    putchar(ch);

  putchar('\n');
  return ch != EOF;
}

int line_skip() {
  int ch;
  while ( (ch=getchar()) != '\n' && ch != EOF )
    ;
  return ch != EOF;
}

int pause() {
  printf("\nPress Enter to continue...");
  return line_skip();
}
