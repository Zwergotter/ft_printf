#include <stdio.h>

void	bullshit(void)
{
	printf("%lll4rhhhbr\n"); //affiche tout ce qu'il y a apres des options valides mais qui n'ont pas de specifier
	//retour : "   rhhhbr" - espaces: 4 soit longueur donnee
	printf("%llll\n");
	// retour : ""
	printf("%llll d\n");
	// retour : " 73832"
	printf("%v");
	// retour : "" - rien
	printf("%llll d\n", 42);
	// retour : " 42"
	printf("%v\n");
	// retour : "" - plusieurs retours a la ligne
	printf("%dllrhhhbr\n", 42);
	//retour 42llrhhhbr
	printf("%");
	// retour : "" - rien
	printf("%llll.1045.-hhjjzzllldzzr\n", 42); //est alle jusqu'au spe.
	// retour "42zzr"
	printf("%l%t");;
	printf("@moulitest: %.o %.0o\n", 0, 0);
	printf("%#010.o\n", 1);
	printf("%kkjgc\n");

	/*d TESTS*/
	printf("@moulitest:%d\n", 42);
	printf("@moulitest:%d\n", -42);
	printf("@moulitest:before %d after\n", 42);
	printf("@moulitest:%d%d%d%d%d\n", 1, -2, 3, -4, 5);
	printf("@moulitest:a%db%dc%dd\n", 1, -2, 3);

	/*Mix test*/
	// printf("%s %C %d %p %x %% %S", "bonjour ", L'該', 42, &free, 42, L"لحم خنزير");

	/*Length test*/
	printf("%ld,%ld\n", 0, 42);
	printf("%lld,%lld\n", 0, 42);
	printf("%hd,%hd\n", 0, 42);
	printf("%hhd,%hhd\n", 0, 42);

	/*Precision test*/
	printf("%.4d\n", 424242);
	printf("%.4d\n", -424242);
	printf("%15.4d\n", 424242);
	printf("%8.4d\n", -424242424);
}

int main()
{
	bullshit();
	return (0);
}