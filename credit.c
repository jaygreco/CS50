#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0

//check those credit card numbers, kids!

//card type definition
typedef enum {
    AMEX = 0,
    MASTERCARD = 1,
    VISA = 2,
    CARD_INVALID = -1
} card_type_t;

//string reverse
char* strrev(char *str)
{
    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}

void _printCardType(card_type_t card) {
    #if DEBUG
    printf("DEBUG: Card type: ");
    #endif
    switch (card) {
        case AMEX:
            printf("AMEX\n");
            break;

        case MASTERCARD:
            printf("MASTERCARD\n");
            break;

        case VISA:
            printf("VISA\n");
            break;

        case CARD_INVALID:
            printf("INVALID\n");
            break;

        default:
            break;
    }
}

//helper to check card length based on type
//unsafe
bool _checkCardLength(char* cardNumber, card_type_t cardType) {
        switch (cardType) {
        case AMEX:
            if (strlen(cardNumber) == 15) return true;
            break;

        case MASTERCARD:
            if (strlen(cardNumber) == 16) return true;
            break;

        case VISA:
            if (strlen(cardNumber) == 13 || strlen(cardNumber) == 16) return true;
            break;

        default:
            break;

    }
    return false;
}

//helper to return card type
//returns card type based on the card number.
//checks the card length, returns INVALID if the card
//length does not match the card type.
//unsafe
card_type_t _cardType(char* cardNumber) {
    //segment based on first digit first, since it's the easiest
    if (cardNumber[0] == '4' && _checkCardLength(cardNumber, VISA)) {
        return VISA;
    }

    //slice off first 2 digits
    char digits[3];
    digits[0] = cardNumber[0];
    digits[1] = cardNumber[1];
    digits[2] = '\0';

    int first2 = atoi(digits);
    #if DEBUG
    printf("DEBUG: first two card digits are %d\n", first2);
    #endif

    if ((first2 == 34 || first2 == 37) && _checkCardLength(cardNumber, AMEX)) {
        return AMEX;
    }

    if ((first2 >= 51 && first2 <= 55) && _checkCardLength(cardNumber, MASTERCARD)) {
        return MASTERCARD;
    }

    return CARD_INVALID;
}

//unsafe
bool _checkCard(char* cardNumber) {
    //first, find required array size starting at second card number
    //yay one-liners!
    int len = (int)ceil(((double)strlen(cardNumber)-1)/2.0);

    //reverse string to make starting at second-to-last easiest
    strrev(cardNumber);

    #if DEBUG
    printf("DEBUG: required array length for odd digits is: %d\n", len);
    #endif

    //Loop through every other digit until the end of a card number, adding them to an array
    char oddDigits[len+1];

    int i = 0;
    for (int j=1; j<strlen(cardNumber); j+=2, i++) {
        oddDigits[i] = cardNumber[j];
    }
    //add null term
    oddDigits[i] = '\0';

    #if DEBUG
    printf("DEBUG: odd card numbers are: %s\n", oddDigits);
    #endif

    //multiply each by 2 and add result by each digit
    int oddDigitsSum = 0;
    for (i=0; i<len; i++) {
        int temp = 2* ((int)(oddDigits[i]) - 48);
        if (temp > 9) {
            //temp is 10 or greater. Add 1 to the sum and subtract 10 before taking mod
            oddDigitsSum++;
            temp -= 10;
        }
        oddDigitsSum += (temp%10);
    }

    #if DEBUG
    printf("DEBUG: odd digits sum: %d\n", oddDigitsSum);
    #endif

    //add sum of all even digits
    int evenDigitsSum = 0;
    #if DEBUG
    printf("DEBUG: even card numbers are: ");
    #endif
    for (i=0; i<strlen(cardNumber); i+=2) {
        evenDigitsSum += ((int)cardNumber[i]) - 48;
        #if DEBUG
        printf("%c", cardNumber[i]);
        #endif
    }
    #if DEBUG
    printf("\n");
    #endif

    #if DEBUG
    printf("DEBUG: even digits sum: %d\n", evenDigitsSum);
    #endif

    if ((evenDigitsSum + oddDigitsSum) % 10 == 0) {
        //card number is valid!
        #if DEBUG
        printf("DEBUG: card number is valid!\n");
        #endif
        return true;
    }

    #if DEBUG
    printf("DEBUG: card number is NOT valid!\n");
    #endif
    return false;
}

int main(void) {
    char cardStr[40];

    long long in = get_long_long("Number: ");

    #if DEBUG
    printf("DEBUG: raw long entered is %lld\n", in);
    #endif

    //convert long to an indexed array of chars (string)
    sprintf(cardStr, "%lld", in);

    #if DEBUG
    printf("DEBUG: converted input is %s\n", cardStr);
    printf("DEBUG: length of card number is %d\n", (int)strlen(cardStr));
    #endif

    //Do the actual checks on the card number, card length, and card type.
    card_type_t cardType = _cardType(cardStr);
    if ((cardType != CARD_INVALID) && _checkCard(cardStr)) {
        _printCardType(cardType);
    }
    else {
        _printCardType(CARD_INVALID);
    }

    return 0;
}