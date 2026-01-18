#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// encryption algorithm
// It is said that gta:sa uses CRC32 algorithm to encrypt the cheatcodes.
// More precisely, gta:sa uses modified JamCRC algorithm instead of the original one, but it still works in my test.
uint32_t crc32_encrypt(char *cheatCode)
{
    uint32_t crc = 0xFFFFFFFF;

    size_t i = 0;
    while(cheatCode[i] != '\0')
    {
        uint8_t byte = cheatCode[i];
        crc = crc ^ byte;
        for (uint8_t j = 8; j > 0; j--)
        {
            crc = (crc >> 1) ^ (0xEDB88320 & (-(crc & 1)));
        }

        i++;
    }

    return crc ^ 0xFFFFFFFF;
}

int main(void)
{
    // scalable cheatcode input
    unsigned long len1;
    printf("Length of Original Cheat Code: ");
    scanf("%ld", &len1);
    char *cheatCodeOrig = malloc(len1 * sizeof(char) + 1);
    scanf("%s", cheatCodeOrig);

    unsigned long len2;
    printf("Length of Popular Cheat Code: ");
    scanf("%ld", &len2);
    char *cheatCodePop = malloc(len2 * sizeof(char) + 1);
    scanf("%s", cheatCodePop);
    
    // input validation
    printf("---------------------------------------- \n");
    printf("Original Cheat Code is: %s \n", cheatCodeOrig);
    printf("Popular Cheat Code is: %s \n", cheatCodePop);

    // inverse our cheatcodes
    // This is because gta:sa reads the input buffer inversely.
    // e.g. string "WWWSSAAD" will be read as "DAASSWWW".
    char *invOrig = malloc(len1 * sizeof(char) + 1);
    for (int i = 0; i < len1; i++)
    {
        invOrig[i] = cheatCodeOrig[len1 - 1 - i];
    }
    invOrig[len1] = '\0';

    char *invPop = malloc(len2 * sizeof(char) + 1);
    for (int i = 0; i < len2; i++)
    {
        invPop[i] = cheatCodePop[len2 - 1 - i];
    }
    invPop[len2] = '\0';

    // final output
    printf("---------------------------------------- \n");
    printf("Original Cheat Code's Hash is: " "%" PRIx32 "\n", crc32_encrypt(invOrig));
    printf("Popular Cheat Code's Hash is: " "%" PRIx32 "\n", crc32_encrypt(invPop));
    printf("---------------------------------------- \n");

    // compare two cheatcodes
    if (crc32_encrypt(invOrig) == crc32_encrypt(invPop))
    {
        printf("equivalent!\n");
    }
    else
    {
        printf("not equivalent!\n");
    }

    free(cheatCodeOrig);
    free(invOrig);
    free(cheatCodePop);
    free(invPop);
}
