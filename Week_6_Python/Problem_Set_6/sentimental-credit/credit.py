def main():
    num = input("Number: ")

    ##incase int() raises an error
    if not valid_checksum(num):
        print("INVALID")
        return

    if amex_valid(num):
        print("AMEX")
        return
    
    if mastercard_valid(num):
        print("MASTERCARD")
        return
    
    if visa_valid(num):
        print("VISA")
        return
    
    print("INVALID")

def amex_valid(num: str) -> bool:
    return len(num) == 15 and num[0] == '3' and num[1] in "47"

def mastercard_valid(num: str) -> bool:
    return len(num) == 16 and num[0] == '5' and num[1] in "12345"

def visa_valid(num: str) -> bool:
    return len(num) in (13, 16) and num[0] == '4'

def valid_checksum(num: str) -> bool:
    checksum = 0
    n = len(num)

    for i in range(n):
        if (i%2):
            twoi: int = 2*int(num[n-i-1])
            checksum += int(twoi%10 + (twoi-twoi%10)/10)
        else: ##i starts at end, so when i = 0 the digit is 1; i%2 = 0 means digitnum%2=1
            checksum += int(num[n-i-1])
        
    return checksum%10 == 0



main()