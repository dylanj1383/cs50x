#include <stdio.h>
#include <cs50.h>

long power(int a, int b);
int get_ith_digit_from_right(long n, int i);
int get_ith_digit_from_left(long n, int i);
bool valid_checksum(long n);
int num_digits(long n);
bool amex_valid(long n);
bool mastercard_valid(long n);
bool visa_valid(long n);

int main(void){
    long n = get_long("Number: ");

    if (!valid_checksum(n)){
        printf("INVALID\n");
    }
    else if (amex_valid(n)){
        printf("AMEX\n");
    }
    else if (mastercard_valid(n)){
        printf("MASTERCARD\n");
    }
    else if (visa_valid(n)){
        printf("VISA\n");
    }
    else {
        printf("INVALID\n");
    }
}

bool amex_valid(long n){
    //Amex: start with 34--- or 37---; 15 digits
    int ndigits = num_digits(n);
    int d1 = get_ith_digit_from_left(n, 1);
    int d2 = get_ith_digit_from_left(n, 2);
    return d1 == 3 && (d2 == 4 || d2 == 7) && ndigits==15;
}

bool mastercard_valid(long n){
    //Mastercard: start with 51-55 inclusive; 16 digits
    int ndigits = num_digits(n);
    int d1 = get_ith_digit_from_left(n, 1);
    int d2 = get_ith_digit_from_left(n, 2);
    int pref = d1*10 + d2;
    return (51 <= pref && pref <= 55) && ndigits == 16;
}

bool visa_valid(long n){
    //Visa: start with 4; 13 or 16 digits
    int ndigits = num_digits(n);
    int d1 = get_ith_digit_from_left(n, 1);
    return (ndigits == 13 || ndigits == 16) && d1 == 4;
}

long power(int a, int b){
    long prod = 1;
    for (int i = 0; i < b; i++){
        prod *= a;
    }
    return prod;
}

int get_ith_digit_from_left(long n, int i){
    int ndigits = num_digits(n);
    return get_ith_digit_from_right(n, ndigits-i+1);
}

int get_ith_digit_from_right(long n, int i){
    // n=   ABCDEFGH
    // n%10 = H
    // n%100 = GH => n%100 - n%10 = GH - H = G0 => (n%100 - n%10)/10 = G0/10 = G

    //n%1000 = FGH => n%1000 - n%100 = FGH - GH = F00 => (n%1000-n%100)/100 = F00/100 = F

    // return (n%(10**i) - n%(10**i-1))/10**i-1
    long tim1 = power(10, i-1); //ten to the i minus 1
    long ti = tim1 * 10; //ten to the i

    return (n%ti - n%tim1)/(tim1);
}

int num_digits(long n){
    int num_digits = 0;

    while(n >= 1){
        n /= 10;
        num_digits ++;
    }
    return num_digits;
}

bool valid_checksum(long n){
    int checksum = 0;
    int digits = num_digits(n);

    for (int i = 1; i <= digits; i++){
        int ith_digit = get_ith_digit_from_right(n, i);
        if (i%2 == 0){
            int twoi = 2*ith_digit;
            checksum += twoi%10 + (twoi-twoi%10)/10; //sum 2 digit number
        }else{
            checksum += ith_digit;
        }
    }
    return checksum%10 == 0;
}