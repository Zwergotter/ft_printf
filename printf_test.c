#include <stdio.h>

void d_test(void)
{
	const char *str;

	int neg;
	int	dec;
	int	cent;
	int dec_mill;

	neg = -1269;
	dec = 27;
	cent = 593;
	dec_mill = 16432;
	//test avec les flags
	str = "Test with 0 : neg is ~%0d~ dec is ~%0d~ cent is ~%0d~ dec_mill is ~%0d~\nTest with - : neg is ~%-d~ dec is ~%-d~ cent is ~%-d~ dec_mill is ~%-d~ \nTest with + : neg is ~%+d~ dec is ~%+d~ cent is ~%+d~ dec_mill is ~%+d~ \nTest with space : neg is ~% d~ dec is ~% d~ cent is ~% d~ dec_mill is ~% d~ \nTest with # : neg is ~%#d~ dec is ~%#d~ cent is ~%#d~ dec_mill is ~%#d~ \n\n";
	printf(" ------------------- neg is ~%d~ dec is ~%d~ cent is ~%d~ dec_mill is ~%d~ ------------------- \n\n", neg, dec, cent, dec_mill);
	printf(" ----------- ONLY FLAGS ----------- \n");
	printf(str, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill);
	str = "Test with 0 : neg is ~%05d~ dec is ~%05d~ cent is ~%05d~ dec_mill is ~%05d~\nTest with - : neg is ~%-5d~ dec is ~%-5d~ cent is ~%-5d~ dec_mill is ~%-5d~ \nTest with + : neg is ~%+5d~ dec is ~%+5d~ cent is ~%+5d~ dec_mill is ~%+5d~ \nTest with space : neg is ~% 5d~ dec is ~% 5d~ cent is ~% 5d~ dec_mill is ~% 5d~ \nTest with # : neg is ~%#5d~ dec is ~%#5d~ cent is ~%#5d~ dec_mill is ~%#5d~ \n\n";
	printf(" ----------- FLAGS WITH LENGTH 5 ----------- \n");
	printf(str, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill);
	str = "Test with 0 : neg is ~%010.5d~ dec is ~%010.5d~ cent is ~%010.5d~ dec_mill is ~%010.5d~\nTest with - : neg is ~%-10.5d~ dec is ~%-10.5d~ cent is ~%-10.5d~ dec_mill is ~%-10.5d~ \nTest with + : neg is ~%+10.5d~ dec is ~%+10.5d~ cent is ~%+10.5d~ dec_mill is ~%+10.5d~ \nTest with space : neg is ~% 10.5d~ dec is ~% 10.5d~ cent is ~% 10.5d~ dec_mill is ~% 10.5d~ \nTest with # : neg is ~%#10.5d~ dec is ~%#10.5d~ cent is ~%#10.5d~ dec_mill is ~%#10.5d~ \n\n";
	printf(" ----------- FLAGS WITH PRECISION 5 AND LENGTH 10 ----------- \n");
	printf(str, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill);
	str = "Test with 0 : neg is ~%05.10d~ dec is ~%05.10d~ cent is ~%05.10d~ dec_mill is ~%05.10d~\nTest with - : neg is ~%-5.10d~ dec is ~%-5.10d~ cent is ~%-5.10d~ dec_mill is ~%-5.10d~ \nTest with + : neg is ~%+5.10d~ dec is ~%+5.10d~ cent is ~%+5.10d~ dec_mill is ~%+5.10d~ \nTest with space : neg is ~% 5.10d~ dec is ~% 5.10d~ cent is ~% 5.10d~ dec_mill is ~% 5.10d~ \nTest with # : neg is ~%#5.10d~ dec is ~%#5.10d~ cent is ~%#5.10d~ dec_mill is ~%#5.10d~ \n\n";
	printf(" ----------- FLAGS WITH PRECISION 10 AND LENGTH 5 ----------- \n");
	printf(str, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill, neg, dec, cent, dec_mill);
}

// void	bullshit(void)
// {
// 	printf("%lll4rhhhbr\n"); //affiche tout ce qu'il y a apres des options valides mais qui n'ont pas de specifier
// 	//retour : "   rhhhbr" - espaces: 4 soit longueur donnee
// 	printf("%llll\n");
// 	// retour : ""
// 	printf("%llll d\n");
// 	// retour : " 73832"
// 	printf("%v");
// 	// retour : "" - rien
// 	printf("%llll d\n", 42);
// 	// retour : " 42"
// 	printf("%v\n");
// 	// retour : "" - plusieurs retours a la ligne
// 	printf("%dllrhhhbr\n", 42);
// 	//retour 42llrhhhbr
// 	printf("%");
// 	// retour : "" - rien
// 	printf("%llll.1045.-hhjjzzllldzzr\n", 42); //est alle jusqu'au spe.
// 	// retour "42zzr"
// 	printf("%l%t");;
// 	printf("@moulitest: %.o %.0o\n", 0, 0);
// 	printf("%#010.o\n", 1);
// 	printf("%kkjgc\n");

// 	/*d TESTS*/
// 	printf("@moulitest:%d\n", 42);
// 	printf("@moulitest:%d\n", -42);
// 	printf("@moulitest:before %d after\n", 42);
// 	printf("@moulitest:%d%d%d%d%d\n", 1, -2, 3, -4, 5);
// 	printf("@moulitest:a%db%dc%dd\n", 1, -2, 3);

// 	/*Mix test*/
// 	// printf("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير");

// 	/*Length test*/
// 	printf("%ld,%ld\n", 0, 42);
// 	printf("%lld,%lld\n", 0, 42);
// 	printf("%hd,%hd\n", 0, 42);
// 	printf("%hhd,%hhd\n", 0, 42);

// 	/*Precision test*/
// 	printf("%.4d\n", 424242);
// 	printf("%.4d\n", -424242);
// 	printf("%15.4d\n", 424242);
// 	printf("%8.4d\n", -424242424);
// }

int main()
{
	d_test();
	// bullshit();
	return (0);
}